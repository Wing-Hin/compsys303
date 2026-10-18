#!/usr/bin/env python3
"""
COMPSYS 303 - where KIELER's "Instantaneous loop detected!" warning comes from.

Every controller chart compiles with that warning, although each of its loops
has a delayed transition (brief Section 1.3). This script compiles four tiny
charts and the five controller charts with KIELER's netlist C compiler
(de.cau.cs.kieler.sccharts.netlist, warnings on) and records the messages and
whether C code was generated:
  W1 delayed loop, no during, no clock    -> expected: no message
  W2 W1 + a during-action counter (B)     -> expected: warning, code generated
  W3 W1 timed by a clock (A)              -> expected: warning, code generated
  W4 all-immediate loop                   -> expected: warning + error, no code
So the warning is produced by KIELER's expansion of during actions (Version B)
and clocks (Version A); a real missing delayed transition is an ERROR (W4).

Usage:  python run_kieler_warning.py      (writes results.txt next to this script)

AI Use Declaration: The design and all design decisions were made by Harold and Lucas.
This check script was written with the assistance of a generative AI tool (Claude,
Anthropic), then reviewed, tested and verified by Harold and Lucas.
"""

import glob
import os
import re
import subprocess
import sys
import tempfile
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
CHARTS = sorted(HERE.glob("W*.sctx")) + [
    ROOT / "Task1_VersionA.sctx", ROOT / "Task2_VersionA.sctx", ROOT / "TrafficLight_VersionA.sctx",
    ROOT / "VersionB" / "Task1_VersionB.sctx", ROOT / "VersionB" / "Task2_VersionB.sctx",
    ROOT / "VersionB" / "TrafficLight_VersionB.sctx"]
ANSI = re.compile(r"\x1b\[[0-9;]*m")


def main():
    jars = glob.glob(os.path.expanduser(
        "~/.vscode/extensions/kieler.keith-vscode-*/server/kieler-language-server.jar"))
    if not jars:
        sys.exit("KIELER language server jar not found")
    lines = [f"KIELER netlist C compile, warnings on (-w), {time.strftime('%Y-%m-%d %H:%M:%S %z')}", ""]
    with tempfile.TemporaryDirectory() as tmp:
        for i, chart in enumerate(CHARTS):
            out, gen = Path(tmp) / f"o{i}", Path(tmp) / f"g{i}"
            out.mkdir()
            r = subprocess.run(["java", "-cp", sorted(jars)[-1], "de.cau.cs.kieler.kicool.cli.KielerCompilerCLI",
                                "-w", "-s", "de.cau.cs.kieler.sccharts.netlist", "-g", str(gen), "-o", str(out),
                                str(chart)], capture_output=True, text=True)
            msgs = sorted({ANSI.sub("", l).strip() for l in (r.stdout + r.stderr).splitlines() if l.strip()})
            code = sorted(p.name for p in out.glob("*.c"))
            lines.append(f"{chart.relative_to(ROOT)}")
            lines.append(f"    C code generated: {', '.join(code) if code else 'NO'}")
            for m in msgs:
                lines.append(f"    message: {m}")
            print("\n".join(lines[-2 - len(msgs):]), flush=True)
    (HERE / "results.txt").write_text("\n".join(lines) + "\n", encoding="utf-8")
    return 0


if __name__ == "__main__":
    sys.exit(main())
