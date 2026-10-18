#!/usr/bin/env python3
"""
COMPSYS 303 Version B - board log analysis (standard library only).

Parses every evidence/B_*.txt console log written by nios2-terminal:
    LEDR a -> b | previous phase N us | T ticks | E timer events
    camera dwell measured: N us
and writes evidence/B_summary.md with, per experiment and per phase:
intended ms, count, mean / min / max measured ms, mean error, jitter
(max - min), mean ticks, mean events, ticks per event and the share of
ticks that carried no timer event.

Usage (from anywhere):  python analyse_logs.py

The intended duration of a phase is the chart time-out rounded UP to a whole
number of timer events, times the real timer period:
    events   = ceil(T / TIMER_MS)          (chart side, compiled into the C)
    intended = events * TIMER_PERIOD_MS    (main.c side, the real alarm rate)
which covers quantisation (E3) and the main.c-only rescale (E4).

AI Use Declaration: The experiment design and all decisions were made by Harold and Lucas.
This script was written with the assistance of a generative AI tool (Claude, Anthropic),
then reviewed and run by Harold and Lucas.
"""

import math
import re
import statistics
from pathlib import Path

HERE = Path(__file__).resolve().parent
CHART = HERE.parent / "TrafficLight_VersionB.sctx"
OUT = HERE / "B_summary.md"

PHASE_RE = re.compile(
    r"^LEDR\s+(-?\d+)\s+->\s+(-?\d+)\s*\|\s*previous phase\s+(\d+)\s+us\s*\|"
    r"\s*(\d+)\s+ticks\s*\|\s*(\d+)\s+timer events\s*$")
DWELL_RE = re.compile(r"camera dwell measured:\s*(\d+)\s*us")
START_MARK = "Version B running"
SETTINGS_RE = re.compile(r"TIMER_MS = (\d+).*TIMER_PERIOD_MS = (\d+)")

# Order and meaning of each LEDR transition: (a, b) -> (phase name, time-out name)
PHASES = [
    ((33, 34), "G-R  NS green", "T1"),
    ((97, 33), "G-R  NS walk", "WALK_TIME"),
    ((34, 36), "Y-R  NS yellow", "T2"),
    ((36, 12), "R-R  after NS", "T3"),
    ((36, 140), "R-R  after NS (EW walk next)", "T3"),
    ((12, 20), "R-G  EW green", "T4"),
    ((140, 12), "R-G  EW walk", "WALK_TIME"),
    ((20, 36), "R-Y  EW yellow", "T5"),
    ((36, 33), "R-R  after EW", "T6"),
    ((36, 97), "R-R  after EW (NS walk next)", "T6"),
]
PHASE_INFO = {ab: (name, tname) for ab, name, tname in PHASES}
PHASE_ORDER = {ab: i for i, (ab, _, _) in enumerate(PHASES)}
# A green that had a walk ends with the walk's remainder, not the full time-out.
AFTER_WALK = {(33, 34): (97, 33), (12, 20): (140, 12)}

EXPERIMENTS = {
    "B_task1_10ms": "Part 1 / E2b: Task 1 baseline, 10 ms",
    "B_E2_1ms": "E2a: 1 ms timer",
    "B_E2_100ms": "E2c: 100 ms timer",
    "B_E3_300ms": "E3: 300 ms timer (quantisation)",
    "B_E4_rescale": "E4: chart 10 ms, main.c 20 ms (rescale)",
    "B_E6_camera_100ms": "E6: camera dwell, 100 ms",
    "B_functional_checks": "Part 2: functional-check log",
    "B_restored_10ms": "Restore check: defaults after experiments",
}


def chart_constants():
    """Read the time-out constants from the chart (TIMER_MS comes from each log header)."""
    text = CHART.read_text(encoding="utf-8")
    consts = {}
    for name in ("T1", "T2", "T3", "T4", "T5", "T6", "WALK_TIME", "CAMERA_DWELL"):
        m = re.search(r"const int %s = (\d+)" % name, text)
        consts[name] = int(m.group(1))
    return consts


def parse_log(path):
    """Return (timer_ms, period_ms, phases, dwells, restarts) for one log file."""
    timer_ms = period_ms = None
    phases, dwells = [], []
    restarts = 0
    started = False
    prev = None
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        line = line.rstrip("\r")
        if line.startswith("#"):
            m = SETTINGS_RE.search(line)
            if m:
                timer_ms, period_ms = int(m.group(1)), int(m.group(2))
            continue
        if START_MARK in line:
            # Text before the marker on this line is left over in the JTAG UART
            # FIFO from the previous run, so the whole line is skipped.
            started, prev = True, None
            restarts += 1
            continue
        if not started:
            continue
        m = PHASE_RE.match(line)
        if m:
            a, b, us, ticks, events = (int(g) for g in m.groups())
            if a == -1:                      # startup line, not a phase
                prev = None
                continue
            phases.append({"ab": (a, b), "us": us, "ticks": ticks,
                           "events": events, "after": prev})
            prev = (a, b)
            continue
        m = DWELL_RE.search(line)
        if m:
            dwells.append(int(m.group(1)))
    return timer_ms, period_ms, phases, dwells, restarts


def intended(consts, tname, timer_ms, period_ms, after_walk):
    """Intended (events, ms) for a phase."""
    events = math.ceil(consts[tname] / timer_ms)
    if after_walk:
        events -= math.ceil(consts["WALK_TIME"] / timer_ms)
    return events, events * period_ms


def fmt(x, nd=1):
    return "-" if x is None else f"{x:.{nd}f}"


def summarise(consts):
    out = ["# Version B board timing summary", "",
           "Generated by `analyse_logs.py` from the raw `B_*.txt` console logs.",
           "Times are measured on the board with timer_1 (50 MHz timestamp). "
           "Intended = ceil(T / TIMER_MS) * TIMER_PERIOD_MS. "
           "Error = mean measured - intended. Jitter = max - min. "
           "Idle share = ticks that carried no timer event / all ticks.", ""]
    logs = sorted(HERE.glob("B_*.txt"),
                  key=lambda p: list(EXPERIMENTS).index(p.stem) if p.stem in EXPERIMENTS else 99)
    for path in logs:
        timer_ms, period_ms, phases, dwells, restarts = parse_log(path)
        title = EXPERIMENTS.get(path.stem, path.stem)
        out += [f"## {title}", "",
                f"File `{path.name}`: chart TIMER_MS = {timer_ms}, main.c TIMER_PERIOD_MS = {period_ms}, "
                f"{len(phases)} phases, {restarts} program start(s).", ""]
        if not phases and not dwells:
            out += ["No phase lines found.", ""]
            continue

        groups = {}
        for p in phases:
            walk = AFTER_WALK.get(p["ab"]) == p["after"] and p["after"] is not None
            groups.setdefault((p["ab"], walk), []).append(p)

        out += ["| Phase | LEDR | Intended ms (events) | n | Mean ms | Min ms | Max ms | "
                "Mean error ms | Jitter ms | Mean ticks | Mean events | Ticks/event | Idle share |",
                "|---|---|---|---|---|---|---|---|---|---|---|---|---|"]
        tot_ticks = tot_events = tot_us = 0
        for (ab, walk) in sorted(groups, key=lambda k: (PHASE_ORDER.get(k[0], 99), k[1])):
            g = groups[(ab, walk)]
            ms = [p["us"] / 1000.0 for p in g]
            ticks = [p["ticks"] for p in g]
            events = [p["events"] for p in g]
            tot_ticks += sum(ticks)
            tot_events += sum(events)
            tot_us += sum(p["us"] for p in g)
            name, tname = PHASE_INFO.get(ab, (f"{ab[0]} -> {ab[1]}", None))
            if walk:
                name += " (after walk)"
            if tname and timer_ms and period_ms:
                ev_i, ms_i = intended(consts, tname, timer_ms, period_ms, walk)
                intended_s, err = f"{ms_i} ({ev_i})", statistics.mean(ms) - ms_i
            else:
                intended_s, err = "-", None
            mt, me = statistics.mean(ticks), statistics.mean(events)
            out.append(
                f"| {name} | {ab[0]}->{ab[1]} | {intended_s} | {len(g)} | {statistics.mean(ms):.3f} | "
                f"{min(ms):.3f} | {max(ms):.3f} | {fmt(err, 3)} | {max(ms) - min(ms):.3f} | "
                f"{mt:.1f} | {me:.1f} | {fmt(mt / me if me else None, 2)} | "
                f"{fmt(100.0 * (1 - sum(events) / sum(ticks)) if sum(ticks) else None, 2)} % |")
        if tot_ticks:
            out += ["", f"All phases: {tot_ticks} ticks, {tot_events} timer events, "
                        f"{tot_ticks / (tot_us / 1e6):.0f} ticks/s, "
                        f"{tot_ticks / tot_events:.2f} ticks per event, "
                        f"{100.0 * (1 - tot_events / tot_ticks):.2f} % of ticks without a timer event."]
        if dwells:
            ms = [d / 1000.0 for d in dwells]
            target = math.ceil(consts["CAMERA_DWELL"] / timer_ms) * period_ms if timer_ms else None
            out += ["", "| Camera dwell | n | Mean ms | Min ms | Max ms | Jitter ms | Chart dwell ms |",
                    "|---|---|---|---|---|---|---|",
                    f"| measured | {len(ms)} | {statistics.mean(ms):.3f} | {min(ms):.3f} | {max(ms):.3f} | "
                    f"{max(ms) - min(ms):.3f} | {target} |"]
        out.append("")
    return "\n".join(out)


def main():
    consts = chart_constants()
    OUT.write_text(summarise(consts), encoding="utf-8")
    print(f"wrote {OUT}")


if __name__ == "__main__":
    main()
