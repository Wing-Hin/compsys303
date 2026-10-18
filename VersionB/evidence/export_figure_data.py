#!/usr/bin/env python3
"""
COMPSYS 303 Version B - export the numbers behind the report figures (standard library only).

Reads the raw board logs with the same parser as analyse_logs.py and writes
  figures/phases.csv  one row per experiment and phase: intended ms, n, mean/min/max ms,
                      mean error, mean ticks, mean events, idle-tick share
  figures/dwell.csv   E6 camera dwells: case (armed at yellow start / entered during yellow), ms
figures/make_figures.m (MATLAB) turns them into the PNG figures.

Usage:  python export_figure_data.py

AI Use Declaration: The design and all design decisions were made by Harold and Lucas.
This export script was written with the assistance of a generative AI tool (Claude,
Anthropic), then reviewed, tested and verified by Harold and Lucas.
"""

import csv
import statistics
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import analyse_logs as al  # noqa: E402  (same folder; works with python -I too)

FIG = HERE / "figures"

EXPERIMENTS = [("E2a 1 ms", "B_E2_1ms"), ("E2b 10 ms", "B_task1_10ms"), ("E2c 100 ms", "B_E2_100ms"),
               ("E3 300 ms", "B_E3_300ms"), ("E4 rescale 10/20 ms", "B_E4_rescale")]
PHASE_ORDER = [(33, 34), (34, 36), (36, 12), (12, 20), (20, 36), (36, 33)]
DWELLS = [("armed at yellow start", "B_E6_camera_100ms"), ("entered during yellow", "B_E6_camera_100ms_yellow")]


def main():
    FIG.mkdir(exist_ok=True)
    consts = al.chart_constants()
    with (FIG / "phases.csv").open("w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["experiment", "timer_ms", "period_ms", "phase", "ledr", "intended_ms", "n",
                    "mean_ms", "min_ms", "max_ms", "mean_error_ms", "mean_ticks", "mean_events",
                    "ticks_per_event", "idle_share"])
        for label, stem in EXPERIMENTS:
            timer_ms, period_ms, phases, _, _ = al.parse_log(HERE / f"{stem}.txt")
            for ab in PHASE_ORDER:
                g = [p for p in phases if p["ab"] == ab]
                name, tname = al.PHASE_INFO[ab]
                _, intended = al.intended(consts, tname, timer_ms, period_ms, False)
                ms = [p["us"] / 1000.0 for p in g]
                ticks = sum(p["ticks"] for p in g)
                ev = sum(p["events"] for p in g)
                w.writerow([label, timer_ms, period_ms, name.strip(), f"{ab[0]}->{ab[1]}", intended, len(g),
                            f"{statistics.mean(ms):.4f}", f"{min(ms):.4f}", f"{max(ms):.4f}",
                            f"{statistics.mean(ms) - intended:.4f}", f"{ticks / len(g):.1f}",
                            f"{ev / len(g):.1f}", f"{ticks / ev:.3f}", f"{1 - ev / ticks:.5f}"])
    with (FIG / "dwell.csv").open("w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["case", "dwell_ms"])
        for label, stem in DWELLS:
            for d in al.parse_log(HERE / f"{stem}.txt")[3]:
                w.writerow([label, f"{d / 1000.0:.3f}"])
    print("wrote", FIG / "phases.csv", "and", FIG / "dwell.csv")


if __name__ == "__main__":
    main()
