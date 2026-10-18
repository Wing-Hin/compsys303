#!/usr/bin/env python3
"""
COMPSYS 303 - structural diff of Version A against Version B (test B2).

Version A (TrafficLight_VersionA.sctx) times with SCCharts clocks in seconds;
Version B (VersionB/TrafficLight_VersionB.sctx) counts timer events in integer
milliseconds. This script removes exactly those expected timing differences
and prints whatever structural difference remains. The only expected
remainder is the ArmedCheck state (plus its fallback target ArmedTick), which
Version A needs for the Timed SCCharts wake-up and Version B does not.

Normalisation (each rule is a documented A/B timing difference):
  * comments, blank lines and @ClocksUseSD removed; chart names unified
  * A float seconds -> B int milliseconds: constant VALUES are compared after
    scaling A by 1000, then both become "const T NAME"
  * A "clock X = 0.0" and B "int X = 0" (timer counters) -> "TIMER X"
  * A cameraClock is B camCount
  * B "X * TIMER_MS >= Y" -> "X >= Y";  B "pre(pendingN) * MS_PER_S" -> "pre(pendingN)"
  * B-only event counting lines removed: TIMER_MS, MS_PER_S, input timerTick,
    "during if timerTick do X++", "if timerTick ... do X++ go to S"

Usage:  python diff_A_B.py        (exit code 0 = only expected differences)

AI Use Declaration: The design and all design decisions were made by Harold and Lucas.
This check script was written with the assistance of a generative AI tool (Claude,
Anthropic), then reviewed, tested and verified by Harold and Lucas.
"""

import difflib
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
A_FILE = ROOT / "TrafficLight_VersionA.sctx"
B_FILE = ROOT / "VersionB" / "TrafficLight_VersionB.sctx"

CONST_RE = re.compile(r"^const (float|int) (\w+) = ([\d.]+)$")
B_ONLY = [
    re.compile(r"^const int TIMER_MS = \d+$"),
    re.compile(r"^const int MS_PER_S = \d+$"),
    re.compile(r"^input\s+bool timerTick$"),
    re.compile(r"^during if timerTick do \w+\+\+$"),
    re.compile(r"^if timerTick( && \w+)? do \w+\+\+ go to \w+$"),
]
TIMER_VARS = r"(c|wNS|wEW|camCount)"


def clean(path):
    """Code lines without comments or surrounding whitespace."""
    out = []
    for raw in path.read_text(encoding="utf-8").splitlines():
        line = re.sub(r"//.*$", "", raw).strip()
        line = re.sub(r"\s+", " ", line)
        if line and line != "@ClocksUseSD":
            out.append(line)
    return out


def normalise(lines, version, consts):
    out = []
    for line in lines:
        if version == "B" and any(p.match(line) for p in B_ONLY):
            continue
        line = re.sub(r"^scchart TrafficLight_[AB] \{", "scchart TrafficLight {", line)
        m = CONST_RE.match(line)
        if m and m.group(2).isupper() and not m.group(2).startswith(("NS_", "EW_", "ASCII", "MAX_")):
            value = float(m.group(3)) * (1000 if version == "A" else 1)
            consts[m.group(2)] = value
            out.append("const T " + m.group(2))
            continue
        line = line.replace("cameraClock", "camCount")
        line = re.sub(r"\bclock (\w+) = 0\.0", r"TIMER \1", line)
        line = re.sub(r"\b(output )?int " + TIMER_VARS + r" = 0\b", r"TIMER \2", line)
        line = re.sub(r"\boutput (float|int) t1 =", "output T t1 =", line)
        line = re.sub(r"(\w+) \* TIMER_MS >=", r"\1 >=", line)
        line = re.sub(r"(pre\(pending\d\)) \* MS_PER_S", r"\1", line)
        line = re.sub(r"\b(\d+)\.0\b", r"\1", line)          # 0.0 -> 0
        out.append(line)
    return out


A_ONLY_STATES = ("state ArmedCheck", "state ArmedTick")


def strip_a_only(lines):
    """Remove Version A's documented camera wake-up states (Timed SCCharts only).

    ArmedCheck makes the activation tick request a wake-up CAMERA_DWELL later;
    ArmedTick is its separate fallback target. Version B counts timer events
    every tick and needs neither, so its activation goes straight to NextCameraTick."""
    out, removed, skipping = [], [], False
    for line in lines:
        if line in A_ONLY_STATES:
            skipping = True
        elif skipping and (line.startswith("state ") or line == "}"):
            skipping = False
        if skipping:
            removed.append(line)
            continue
        if "go to ArmedCheck" in line:
            removed.append(line)
            line = line.replace("go to ArmedCheck", "go to NextCameraTick")
        out.append(line)
    return out, removed


def main():
    ca, cb = {}, {}
    a, removed = strip_a_only(normalise(clean(A_FILE), "A", ca))
    b = normalise(clean(B_FILE), "B", cb)

    ok = True
    print(f"A: {A_FILE.relative_to(ROOT)}  ({len(a)} normalised lines)")
    print(f"B: {B_FILE.relative_to(ROOT)}  ({len(b)} normalised lines)\n")

    print("Constant values (A seconds x 1000 vs B milliseconds):")
    for name in sorted(set(ca) | set(cb)):
        va, vb = ca.get(name), cb.get(name)
        same = va is not None and vb is not None and abs(va - vb) < 1e-9
        ok &= same
        print(f"  {name:13s} A={va!s:>8}  B={vb!s:>8}  {'same' if same else 'DIFFERENT'}")

    print(f"\nDocumented Version A-only camera wake-up block removed ({len(removed)} lines):")
    for line in removed:
        print("  A only:", line)
    diff = [d for d in difflib.unified_diff(a, b, "A (normalised)", "B (normalised)", n=1, lineterm="")]
    changed = [d for d in diff if d[:1] in "+-" and not d.startswith(("+++", "---"))]
    print("\nRemaining structural differences:")
    print("\n".join(diff) if diff else "  (none)")
    print(f"\n{len(changed)} unexpected differing line(s).")
    ok &= not changed
    print("RESULT:", "PASS (only the expected timing and ArmedCheck/ArmedTick differences)" if ok else "FAIL")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
