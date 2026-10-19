#!/usr/bin/env python3
"""
COMPSYS 303 Version B - board log checker (test T0, standard library only).

Checks every evidence/board_logs/B_*.txt console log (or the files given as arguments)
against the shared pass criteria of the test plan (Part II, section 0):

  1. LEDR is always one of 33, 34, 36, 12, 20, 97, 140.
  2. Every change is in the allowed set
         33 -> 34|97   97 -> 33|34   34 -> 36   36 -> 12|140|33|97
         12 -> 20|140  140 -> 12|20  20 -> 36
     97 -> 34 and 140 -> 20 are legal only after a Task 3 configuration commit
     (a green shorter than the walk).
  3. Safety: one lamp per direction, never green/yellow in both directions at
     once, and a walk light only with its own direction's green.
  4. Every phase lasts ceil(T / TIMER_MS) timer events (TIMER_MS read from the
     log header). A green that had a walk ends with the remainder
     ceil(T / TIMER_MS) - ceil(WALK_TIME / TIMER_MS).
     Exempt: an all-red phase that is LONGER than nominal (Task 3 hold or a
     configuration commit) - it is reported, not failed.
     After the first such commit the expected time-outs switch to the values
     of an optional header line "# Config: t1,t2,t3,t4,t5,t6" (milliseconds).
     Task 3 packets sent during a run are marked "# ... sent ...: <packet>" (escapes
     written as \r and \n). From each VALID packet (six 1-4 digit fields in
     milliseconds, none of them 0 - the chart's own validity rule) on a
     marker line, every later phase may also last that packet's count; a
     longer all-red is still exempt, a shorter one still fails.

Lines before the first "Version B running" of each program start are skipped
(they are left over in the JTAG UART FIFO from the previous run), as are the
startup line "LEDR -1 -> 33" and any line cut off when the log was stopped.

Usage:  python check_board_log.py [log files...]     (exit code 1 on any violation)

AI Use Declaration: Harold and Lucas designed the system and made all design decisions. They
discussed the structure of the code with Claude (Anthropic), which helped write parts of
this file; Harold and Lucas reviewed, tested and verified all of it.
"""

import math
import re
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
LOGS = ROOT / "evidence" / "board_logs"
CHART = ROOT / "VersionB" / "TrafficLight_VersionB.sctx"

PHASE_RE = re.compile(
    r"^LEDR\s+(-?\d+)\s+->\s+(-?\d+)\s*\|\s*previous phase\s+(\d+)\s+us\s*\|"
    r"\s*(\d+)\s+ticks\s*\|\s*(\d+)\s+timer events\s*$")
SETTINGS_RE = re.compile(r"TIMER_MS = (\d+).*TIMER_PERIOD_MS = (\d+)")
CONFIG_RE = re.compile(r"^#\s*Config:\s*([\d\s,]+)$")
SENT_RE = re.compile(r"^#.*\bsent\b[^:]*:\s*(\S+)")   # "sent: p" or "sent during green (33): p"
PACKET_RE = re.compile(r"^\d{1,4}(,\d{1,4}){5}$")
NAMES = ("T1", "T2", "T3", "T4", "T5", "T6")
START_MARK = "Version B running"

ALLOWED_VALUES = {33, 34, 36, 12, 20, 97, 140}
ALLOWED = {33: {34, 97}, 97: {33, 34}, 34: {36}, 36: {12, 140, 33, 97},
           12: {20, 140}, 140: {12, 20}, 20: {36}}
AFTER_CONFIG_ONLY = {(97, 34), (140, 20)}

# Which time-out the phase that ENDS with a -> b lasted (a is the phase's LEDR).
PHASE_TIMEOUT = {(33, 34): "T1", (33, 97): "T1", (97, 33): "WALK_TIME", (97, 34): "T1",
                 (34, 36): "T2", (12, 20): "T4", (12, 140): "T4", (140, 12): "WALK_TIME",
                 (140, 20): "T4", (20, 36): "T5"}
WALK_BEFORE = {(33, 34): (97, 33), (12, 20): (140, 12)}

NS = {1: "G", 2: "Y", 4: "R"}
EW = {8: "G", 16: "Y", 32: "R"}


def is_raw_log(path):
    """Only raw console logs: their first line says so (summaries are skipped)."""
    with path.open(encoding="utf-8", errors="replace") as f:
        return "raw nios2-terminal output" in f.readline()


def chart_timeouts():
    text = CHART.read_text(encoding="utf-8")
    return {n: int(re.search(r"const int %s = (\d+)" % n, text).group(1))
            for n in ("T1", "T2", "T3", "T4", "T5", "T6", "WALK_TIME")}


def safety(v):
    """Return a problem string, or None if LEDR value v is a safe lamp pattern."""
    ns = [NS[b] for b in NS if v & b]
    ew = [EW[b] for b in EW if v & b]
    if len(ns) != 1 or len(ew) != 1:
        return f"LEDR {v}: not exactly one lamp per direction"
    if ns[0] in "GY" and ew[0] in "GY":
        return f"LEDR {v}: both directions green/yellow"
    if v & 64 and ns[0] != "G":
        return f"LEDR {v}: NS walk without NS green"
    if v & 128 and ew[0] != "G":
        return f"LEDR {v}: EW walk without EW green"
    if v & ~0xFF:
        return f"LEDR {v}: unexpected bits"
    return None


def show(exps):
    """One expected count as before, several as '600 or 800'."""
    return " or ".join(str(e) for e in sorted(exps))


def sent_packets(line):
    """Time-outs (ms) of every valid packet on a '# ... sent:' marker line."""
    m = SENT_RE.match(line.strip())
    if not m:
        return []
    out = []
    for packet in m.group(1).split("\\n"):
        packet = packet.replace("\\r", "")
        if PACKET_RE.match(packet) and all(int(x) > 0 for x in packet.split(",")):
            out.append(dict(zip(NAMES, (int(x) for x in packet.split(",")))))  # milliseconds
    return out


def check(path, defaults):
    lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
    timer_ms = None
    config = None
    for line in lines:
        if line.startswith("#"):
            m = SETTINGS_RE.search(line)
            if m:
                timer_ms = int(m.group(1))
            m = CONFIG_RE.match(line.strip())
            if m:
                config = [int(x) for x in m.group(1).replace(" ", "").split(",") if x]  # milliseconds
    if timer_ms is None:
        return [f"{path.name}: no TIMER_MS in header"], [], 0

    timeouts = dict(defaults)
    committed = False
    started = START_MARK not in "\n".join(lines)     # a log attached without a download
    prev = None          # previous transition (a, b) within this program start
    violations, notes, checked = [], [], 0

    alts = []            # time-outs of the valid packets sent so far in this log

    def expected(name, walk):
        """Allowed event counts: current time-outs, or any packet sent so far."""
        out = set()
        for t in [timeouts] + alts:
            ev = math.ceil(t[name] / timer_ms)
            if walk:
                ev -= math.ceil(t["WALK_TIME"] / timer_ms)
            out.add(ev)
        return out

    for no, line in enumerate(lines, 1):
        for packet in sent_packets(line):
            alts.append(dict(defaults, **packet))
            committed = True
        if START_MARK in line:
            started, prev = True, None
            continue
        if not started:
            continue
        m = PHASE_RE.match(line.strip())
        if not m:
            continue
        a, b, us, ticks, events = (int(g) for g in m.groups())
        where = f"{path.name}:{no}"
        if a == -1:                                   # startup line
            prev = (a, b)
            continue
        checked += 1
        for v in (a, b):
            if v not in ALLOWED_VALUES:
                violations.append(f"{where}: illegal LEDR value {v}")
            problem = safety(v)
            if problem:
                violations.append(f"{where}: unsafe {problem}")
        if b not in ALLOWED.get(a, set()):
            violations.append(f"{where}: illegal change {a} -> {b}")
        elif (a, b) in AFTER_CONFIG_ONLY and not committed:
            violations.append(f"{where}: {a} -> {b} is legal only after a Task 3 configuration commit")

        # Event count of the phase that just ended.
        if a == 36:
            rr = "T3" if prev and prev[1] == 36 and prev[0] == 34 else "T6"
            exps = expected(rr, False)
            if events in exps:
                pass
            elif events > min(exps):
                notes.append(f"{where}: all-red lasted {events} events (> {show(exps)}): Task 3 hold or "
                             f"configuration commit - exempt")
                if config and not committed:
                    timeouts.update(dict(zip(NAMES, config)))
                    notes.append(f"{where}: expected time-outs switched to # Config: {config} ms")
                committed = committed or config is not None
            else:
                violations.append(f"{where}: all-red {rr} lasted {events} events, expected {show(exps)}")
        else:
            name = PHASE_TIMEOUT.get((a, b))
            if name:
                walk = WALK_BEFORE.get((a, b)) == prev
                exps = expected(name, walk)
                if events not in exps:
                    violations.append(f"{where}: {a} -> {b} after {events} events, expected {show(exps)}"
                                      + (" (green remainder after walk)" if walk else ""))
        prev = (a, b)
    return violations, notes, checked


def main(argv):
    files = [Path(p) for p in argv] or sorted(p for p in LOGS.glob("B_*.txt") if is_raw_log(p))
    defaults = chart_timeouts()
    total_v = 0
    for f in files:
        v, n, checked = check(f, defaults)
        total_v += len(v)
        status = "PASS" if not v else f"FAIL ({len(v)} violation(s))"
        print(f"{f.name:38s} {checked:4d} phases  {status}")
        for line in v:
            print("    VIOLATION", line)
        for line in n:
            print("    note     ", line)
    print(f"\n{len(files)} log(s), {total_v} violation(s):", "PASS" if total_v == 0 else "FAIL")
    return 0 if total_v == 0 else 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
