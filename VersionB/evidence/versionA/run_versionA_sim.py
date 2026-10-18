#!/usr/bin/env python3
"""
COMPSYS 303 Version A - headless KIELER simulation regression (tests A2-A11, A13-A17).

What it runs: the simulator that KIELER itself generates for "Netlist-based
Simulation (C)" (compilation system de.cau.cs.kieler.sccharts.simulation.netlist.c),
built from the committed TrafficLight_VersionA.sctx with the KIELER command-line
compiler from the VS Code extension. That simulator is the program the KIELER
simulation view drives: one JSON line of inputs per tick in, one JSON line of
outputs out (the chart's print() messages appear as plain text lines).

Time: Dynamic mode is reproduced the way KIELER's dynamic ticking works - the
next tick is taken when the chart's own wake-up time sleepT is due, and deltaT
is the time that has actually passed:
  * A2 runs in REAL TIME (sleep for sleepT on the wall clock, pass the measured
    elapsed time as deltaT), so its phase errors are genuine host timing errors
    and are exported for the Version A vs Version B figure.
  * A3-A11 use exact virtual time (deltaT = sleepT), so they finish in seconds.
When the chart requests no wake-up (sleepT = 0, or KIELER's default 1000 s, e.g.
in the Task 3 hold) the driver keeps ticking every 0.1 s - except in STRICT
Dynamic mode (A8, A14, A15), where nothing ticks without a wake-up or an input,
exactly as in KIELER's dynamic ticking. A missing wake-up then shows as a failure.
A14/A15 count those ticks (the computational-effort comparison, brief Section 4).
A16/A17 run the standalone Part 1 charts Task1_VersionA / Task2_VersionA.
Task 3 packet values are milliseconds (1..9999); a 0 field is invalid (A13).
Buttons are one-tick pulses with deltaT = 0 (as in TASK3.md / TASK4.md);
Task 3 characters are sent one per tick, only while configReady is true.

Writes, next to this script:
  A_results.txt             PASS/FAIL per test with the numbers that prove it
  trace_<id>.jsonl          every tick: t, deltaT, inputs, outputs, messages
  A2_realtime_phases.csv    A2 phase durations (for figures/make_figures.m)

Usage:  python run_versionA_sim.py [--sim path\\to\\simulation.exe]
        (without --sim the simulator is built with KIELER; needs java and the
         kieler.keith-vscode extension)

AI Use Declaration: The design and all design decisions were made by Harold and Lucas.
This simulation driver was written with the assistance of a generative AI tool (Claude,
Anthropic), then reviewed, tested and verified by Harold and Lucas.
"""

import argparse
import csv
import glob
import json
import os
import shutil
import subprocess
import sys
import tempfile
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
CHART = ROOT / "TrafficLight_VersionA.sctx"
TASK1_CHART = ROOT / "Task1_VersionA.sctx"
TASK2_CHART = ROOT / "Task2_VersionA.sctx"
SYSTEM = "de.cau.cs.kieler.sccharts.simulation.netlist.c"
EPS = 1e-6
POLL = 0.1                 # step used when the chart requests no wake-up
NO_DEADLINE = 1000.0       # KIELER writes sleepT = 1000.0 at the start of every tick
OUT = HERE                 # set from --out in main()

G_R, Y_R, RR, R_G, R_Y = 33, 34, 36, 12, 20
NS_WALK, EW_WALK = 97, 140


# ---------------------------------------------------------------- simulator
def build_simulator(workdir, chart):
    jars = glob.glob(os.path.expanduser(
        "~/.vscode/extensions/kieler.keith-vscode-*/server/kieler-language-server.jar"))
    if not jars:
        sys.exit("KIELER language server jar not found; pass --sim")
    out, gen = Path(workdir) / "out", Path(workdir) / "gen"
    out.mkdir(parents=True)                # with one input, -o is a file unless the folder exists
    gen.mkdir(parents=True)
    cmd =["java", "-cp", sorted(jars)[-1], "de.cau.cs.kieler.kicool.cli.KielerCompilerCLI",
           "-s", SYSTEM, "-g", str(gen), "-o", str(out), str(chart)]
    r = subprocess.run(cmd, capture_output=True, text=True)
    exe = out / "simulation.exe"
    if r.returncode != 0 or not exe.exists():
        sys.exit("KIELER build failed:\n" + r.stdout[-2000:] + r.stderr[-2000:])
    warnings = sorted({l.strip() for l in (r.stdout + r.stderr).splitlines()
                       if "loop" in l.lower() or "warn" in l.lower() or "VariableStore" in l})
    return str(exe), warnings


class Sim:
    """One KIELER simulator process; keeps simulated time t (seconds)."""

    def __init__(self, exe, name, inputs=None):
        self.p = subprocess.Popen([exe], stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                                  text=True, bufsize=1)
        self.name, self.t = name, 0.0
        self.idle = 0.0                        # strict-mode time not yet passed to the chart
        self.ticks = 0                         # reactions computed
        self.inp = inputs if inputs is not None else {
            "task": 1, "NSraised": False, "EWraised": False, "vehicleButton": False,
            "configChar": 0, "configValid": False}
        self.out, msgs = self._read()          # values after reset, before the first tick
        self.trace = []
        self.changes = []                      # (t, from, to) LEDR changes
        self.msgs = []                         # (t, text)
        self.applied = []                      # (t, LEDR) when configApplied changes
        self.task_changes = []                 # (t, LEDR before, LEDR after, old, new)

    def _read(self):
        msgs = []
        while True:
            line = self.p.stdout.readline()
            if not line:
                raise RuntimeError("simulator exited")
            line = line.strip()
            if line.startswith("{"):
                d = json.loads(line)
                d.pop("#interface", None)
                return d, msgs
            if line:
                msgs.append(line)

    def tick(self, dt, **inputs):
        before = self.out
        self.inp.update(inputs)
        sent = dt + self.idle
        self.p.stdin.write(json.dumps(dict(self.inp, deltaT=sent)) + "\n")
        self.p.stdin.flush()
        self.out, msgs = self._read()
        self.t += dt
        self.idle = 0.0
        self.ticks += 1
        if self.trace and self.out["LEDR"] != before["LEDR"] or not self.trace:
            self.changes.append((self.t, before.get("LEDR", -1) if self.trace else -1, self.out["LEDR"]))
        if self.trace and self.out.get("activeTask") != before.get("activeTask"):
            self.task_changes.append((self.t, before["LEDR"], self.out["LEDR"],
                                      before["activeTask"], self.out["activeTask"]))
        if self.trace and self.out.get("configApplied") != before.get("configApplied"):
            self.applied.append((self.t, self.out["LEDR"]))
        for m in msgs:
            self.msgs.append((self.t, m))
        keep = {k: self.out.get(k) for k in ("LEDR", "activeTask", "sleepT", "configReady", "waitingConfig",
                                             "configApplied", "configRejected", "t1", "t2", "t3", "t4",
                                             "t5", "t6", "vehiclePresent", "cameraArmed", "snapshots")}
        self.trace.append({"t": round(self.t, 9), "deltaT": sent, "in": dict(self.inp), "out": keep, "msgs": msgs})
        return self.out

    # ---- helpers -------------------------------------------------------
    def run_until(self, t_end, realtime=False, strict=False):
        """Dynamic-mode stepping up to simulated time t_end. strict: no wake-up
        requested -> no tick at all (time just passes), as in KIELER's dynamic ticks."""
        while self.t < t_end - EPS:
            sleep_t = self.out.get("sleepT") or 0
            if strict and not 0 < sleep_t < NO_DEADLINE:
                self.idle += t_end - self.t        # idle: nothing would wake the chart; the
                self.t = t_end                     # next tick's deltaT includes this time
                break
            # No wake-up requested (e.g. the Task 3 hold): keep ticking in 0.1 s steps
            # instead of jumping, so a commit or a mode change is seen when it happens.
            dt = min(sleep_t if 0 < sleep_t < NO_DEADLINE else POLL, t_end - self.t)
            if realtime:
                start = time.perf_counter()
                time.sleep(dt)
                dt = time.perf_counter() - start
            self.tick(dt)

    def run_for(self, seconds, realtime=False, strict=False):
        self.run_until(self.t + seconds, realtime, strict)

    def run_until_ledr(self, value, limit=200.0):
        """Step until LEDR changes to value (returns the time) or the limit."""
        t_end = self.t + limit
        n = len(self.changes)
        while self.t < t_end - EPS:
            self.run_for(min(self.out.get("sleepT") or 1.0, t_end - self.t) or 1.0)
            if any(c[2] == value for c in self.changes[n:]):
                return next(c[0] for c in self.changes[n:] if c[2] == value)
        return None

    def pulse(self, name):
        self.tick(0, **{name: True})
        self.tick(0, **{name: False})

    def send(self, text):
        for ch in text:
            guard = 0
            while not self.out.get("configReady"):
                self.tick(0, configValid=False)
                guard += 1
                if guard > 1000:
                    raise RuntimeError("configReady stayed false")
            self.tick(0, configChar=ord(ch), configValid=True)
        self.tick(0, configValid=False)

    def phases_after(self, t0):
        """[(a, b, duration of a)] for the LEDR changes a -> b after the first change at/after t0
        (the same convention as the board logs: the phase that ENDS with a -> b)."""
        ch = [c for c in self.changes if c[0] >= t0 - EPS]
        return [(ch[i][1], ch[i][2], ch[i][0] - ch[i - 1][0]) for i in range(1, len(ch))]

    def save(self):
        with (OUT / f"trace_{self.name}.jsonl").open("w") as f:
            for e in self.trace:
                f.write(json.dumps(e) + "\n")
        self.p.stdin.close()
        self.p.wait(timeout=10)


# ---------------------------------------------------------------- tests
RESULTS = []


def check(test, ok, detail):
    RESULTS.append((test, "PASS" if ok else "FAIL", detail))


def a2(exe):
    s = Sim(exe, "A2_task1_realtime")
    s.tick(0, task=1)
    s.run_for(2 * 17.0 + 0.2, realtime=True)
    seq = [(a, b) for a, b, _ in s.phases_after(0)][:12]
    want = [(33, 34), (34, 36), (36, 12), (12, 20), (20, 36), (36, 33)] * 2
    nominal = {(33, 34): 6.0, (34, 36): 2.0, (36, 12): 0.5, (12, 20): 6.0, (20, 36): 2.0, (36, 33): 0.5}
    durs = s.phases_after(0)[:12]
    errs = [d - nominal[(a, b)] for a, b, d in durs]
    with (OUT / "A2_realtime_phases.csv").open("w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["from", "to", "intended_ms", "measured_ms", "error_ms"])
        for (a, b, d), e in zip(durs, errs):
            w.writerow([a, b, nominal[(a, b)] * 1000, f"{d * 1000:.3f}", f"{e * 1000:.3f}"])
    ok = seq == want and all(abs(e) < 0.2 for e in errs)
    check("A2", ok, f"2 cycles in real time: sequence {'33,34,36,12,20,36 x2' if seq == want else seq}; "
          f"durations 6/2/0.5/6/2/0.5 s with errors {min(errs) * 1000:+.1f}..{max(errs) * 1000:+.1f} ms "
          f"(host sleep jitter)")
    s.save()


def a3(exe):
    s = Sim(exe, "A3_ns_press_in_RG")
    s.tick(0, task=2)
    s.run_until_ledr(R_G)                           # R-G in Task 2 (taken over at the first R-R)
    s.run_for(1.0)
    s.pulse("NSraised")
    t97 = s.run_until_ledr(NS_WALK)
    s.run_for(4.5)
    walk = [d for a, b, d in s.phases_after(t97 or 0) if a == NS_WALK]
    ok = t97 is not None and walk and abs(walk[0] - 4.0) < EPS
    check("A3", ok, f"NS press in R-G -> next G-R shows 97 for {walk[0] if walk else '-'} s, then 33")
    s.save()


def a4(exe):
    s = Sim(exe, "A4_ew_press_in_GR")
    s.tick(0, task=2)
    s.run_until_ledr(RR)
    s.run_until_ledr(G_R)                           # G-R in Task 2
    s.run_for(1.0)
    s.pulse("EWraised")
    t140 = s.run_until_ledr(EW_WALK)
    s.run_for(4.5)
    walk = [d for a, b, d in s.phases_after(t140 or 0) if a == EW_WALK]
    ok = t140 is not None and walk and abs(walk[0] - 4.0) < EPS
    check("A4", ok, f"EW press in G-R -> next R-G shows 140 for {walk[0] if walk else '-'} s, then 12")
    s.save()


def a5(exe):
    s = Sim(exe, "A5_press_in_own_green")
    s.tick(0, task=2)
    s.run_until_ledr(RR)
    t_g = s.run_until_ledr(G_R)                     # own green, no walk
    s.run_for(1.0)
    s.pulse("NSraised")
    s.run_until_ledr(Y_R)
    cur = [(a, b, d) for a, b, d in s.phases_after(t_g) if a == G_R][:1]
    nxt = s.run_until_ledr(NS_WALK, limit=20.0)
    ok = cur and cur[0][1] == Y_R and abs(cur[0][2] - 6.0) < EPS and nxt is not None
    check("A5", ok, f"press during its own G-R: current green {cur[0][2] if cur else '-'} s without walk, "
          f"walk at the next G-R ({'yes' if nxt else 'no'})")
    s.save()


def a6(exe):
    s = Sim(exe, "A6_task_change_mid_green")
    s.tick(0, task=1)
    s.run_until_ledr(R_G)
    s.run_for(2.0)                                  # mid-green
    s.tick(0, task=2)
    t_change = s.t
    s.run_for(10.0)
    ch = [c for c in s.task_changes if c[0] >= t_change - EPS]
    ok = len(ch) == 1 and (ch[0][1] == RR or ch[0][2] == RR)            # only inside the all-red
    check("A6", ok, f"task 1 -> 2 set mid-green at t={t_change:.1f} s; activeTask changed at t={ch[0][0]:.1f} s "
          f"on a tick LEDR {ch[0][1]} -> {ch[0][2]}" if ch else "activeTask never changed")
    s.save()


def a7(exe):
    s = Sim(exe, "A7_request_retained_2_1_2")
    s.tick(0, task=2)
    s.run_until_ledr(R_G)
    s.run_for(1.0)
    s.pulse("NSraised")                             # request in Task 2
    s.tick(0, task=1)                               # Task 1 from the next R-R
    t1g = s.run_until_ledr(G_R)
    no_walk = s.out["LEDR"] == G_R and s.out["activeTask"] == 1
    s.tick(0, task=2)                               # back to Task 2
    t97 = s.run_until_ledr(NS_WALK, limit=30.0)
    ok = no_walk and t97 is not None
    check("A7", ok, f"request made in Task 2, Task 1 green at t={t1g:.1f} s without walk, walk served at "
          f"t={t97:.1f} s after returning to Task 2" if t97 else "walk not served after returning to Task 2")
    s.save()


def a8_a9_a13(exe):
    s = Sim(exe, "A8_A9_A13_task3")
    s.tick(0, task=3)
    s.run_until_ledr(RR)
    s.run_for(5.0)
    held = s.out["LEDR"] == RR and s.out["waitingConfig"]
    rej0 = s.out["configRejected"]
    s.send("1,2,3\n")                               # A9: invalid
    s.run_for(10.0)
    a9 = s.out["configRejected"] == rej0 + 1 and s.out["LEDR"] == RR and s.out["configApplied"] == 0
    check("A9", held and a9, f"'1,2,3' + LF in the Task 3 hold: configRejected {rej0} -> {s.out['configRejected']}, "
          f"lights still 36 after 10 s, nothing applied")
    rej1 = s.out["configRejected"]
    s.send("6000,2000,0,6000,2000,500\n")           # A13: a 0 field (comma path) ...
    s.send("6000,2000,500,6000,2000,0\n")           # ... and a 0 last field (LF path)
    s.run_for(10.0)
    a13 = s.out["configRejected"] == rej1 + 2 and s.out["LEDR"] == RR and s.out["configApplied"] == 0
    check("A13", a13, f"'6000,2000,0,...' and '...,2000,0' + LF in the hold: configRejected {rej1} -> "
          f"{s.out['configRejected']}, lights still 36, nothing applied (0 would skip a safety phase)")
    t_send = s.t
    s.send("8000,3000,1000,8000,3000,1000\n")       # A8: valid (milliseconds)
    s.run_for(30.0, strict=True)                    # pure Dynamic: only the chart's own wake-ups tick
    ph = s.phases_after(t_send)
    got = [(a, b, round(d, 6)) for a, b, d in ph[:6]]
    want = [(12, 20, 8.0), (20, 36, 3.0), (36, 33, 1.0), (33, 34, 8.0), (34, 36, 3.0), (36, 12, 1.0)]
    at_rr = bool(s.applied) and s.applied[0][1] == RR
    commit = next((e for e in s.trace if e["out"]["configApplied"]), None)
    commit_sleep = commit["out"]["sleepT"] if commit else None
    first_rr = (next((c[0] for c in s.changes if c[0] >= t_send - EPS and c[1] == RR), None) - commit["t"]
                if commit else None)
    ok = got == want and at_rr and commit_sleep is not None and abs(commit_sleep - 1.0) < EPS \
        and first_rr is not None and abs(first_rr - 1.0) < EPS
    check("A8", ok, f"'8000,3000,1000,8000,3000,1000' + LF, strict Dynamic mode: applied at R-R "
          f"({'yes' if at_rr else 'no'}); the commit tick requests sleepT = {commit_sleep} s, the all-red ends "
          f"{first_rr if first_rr is None else round(first_rr, 6)} s after the commit; phases "
          f"{[d for _, _, d in got]} s")
    s.save()


def count_ticks(s, seconds, what):
    """Strict Dynamic run: (ticks, LEDR changes, exact durations?) over `seconds`."""
    n0, c0, t0 = s.ticks, len(s.changes), s.t
    s.run_for(seconds, strict=True)
    return s.ticks - n0, len(s.changes) - c0


def a14(exe):
    s = Sim(exe, "A14_ticks_task1")
    s.tick(0, task=1)
    ticks, changes = count_ticks(s, 10 * 17.0, "task 1")
    durs = s.phases_after(0)
    nominal = {(33, 34): 6.0, (34, 36): 2.0, (36, 12): 0.5, (12, 20): 6.0, (20, 36): 2.0, (36, 33): 0.5}
    exact = all(abs(d - nominal[(a, b)]) < EPS for a, b, d in durs)
    ok = exact and changes >= 59 and ticks <= 2 * changes + 2
    check("A14", ok, f"Task 1, 10 cycles (170 s) in strict Dynamic mode: {ticks} reactions for {changes} LEDR "
          f"changes = {ticks / 10:.1f} per 17 s cycle, every phase exact ({'yes' if exact else 'no'}). "
          f"Version B at 10 ms computes 2,050-2,200 reactions per second, about 35,000-37,000 per cycle "
          f"(B_summary.md)")
    s.save()


def a15(exe):
    s = Sim(exe, "A15_ticks_task4")
    s.tick(0, task=4)
    s.run_until_ledr(R_G)
    n0 = s.ticks
    s.run_for(1.0, strict=True)
    s.pulse("vehicleButton")                        # car enters in green, stays
    s.run_until_ledr(R_Y)
    s.run_for(17.0, strict=True)                    # yellow, camera dwell, snapshot, rest of the cycle
    s.pulse("vehicleButton")                        # leaves
    s.run_for(17.0, strict=True)
    ticks = s.ticks - n0
    snap = [t for t, m in s.msgs if "Snapshot taken" in m]
    act = [t for t, m in s.msgs if "Camera activated" in m]
    ok = len(act) == 1 and len(snap) == 1 and abs(snap[0] - act[0] - 1.0) < EPS and ticks < 60
    check("A15", ok, f"Task 4, about 2 cycles with a car and a snapshot in strict Dynamic mode: {ticks} reactions "
          f"(4 of them the button pulses); snapshot {snap[0] - act[0] if act and snap else '-'} s after "
          f"activation - two independent clocks, each tick only when one of them expires or an input arrives")
    s.save()


def a16(exe1):
    s = Sim(exe1, "A16_task1_chart", inputs={})
    s.tick(0)
    ticks, changes = count_ticks(s, 2 * 17.0 + 0.2, "task 1 chart")
    seq = [(a, b) for a, b, _ in s.phases_after(0)][:12]
    want = [(33, 34), (34, 36), (36, 12), (12, 20), (20, 36), (36, 33)] * 2
    nominal = {(33, 34): 6.0, (34, 36): 2.0, (36, 12): 0.5, (12, 20): 6.0, (20, 36): 2.0, (36, 33): 0.5}
    exact = all(abs(d - nominal[(a, b)]) < EPS for a, b, d in s.phases_after(0))
    check("A16", seq == want and exact, f"Task1_VersionA.sctx (Part 1), strict Dynamic mode: sequence "
          f"{'33,34,36,12,20,36 x2' if seq == want else seq}, durations exact ({'yes' if exact else 'no'}), "
          f"{ticks} reactions for {changes} changes")
    s.save()


def a17(exe2):
    s = Sim(exe2, "A17_task2_chart", inputs={"NSraised": False, "EWraised": False})
    s.tick(0)
    s.run_until_ledr(R_G)
    s.run_for(1.0)
    s.pulse("NSraised")
    t97 = s.run_until_ledr(NS_WALK)
    s.run_until_ledr(R_G)
    s.run_for(1.0)
    walk = [d for a, b, d in s.phases_after(t97 or 0) if a == NS_WALK]
    rest = [d for a, b, d in s.phases_after(t97 or 0) if (a, b) == (G_R, Y_R)]
    ok = t97 is not None and walk and abs(walk[0] - 4.0) < EPS and rest and abs(rest[0] - 2.0) < EPS
    check("A17", ok, f"Task2_VersionA.sctx (Part 1): NS press in R-G -> next G-R shows 97 for "
          f"{walk[0] if walk else '-'} s, then 33 for the remaining {rest[0] if rest else '-'} s")
    s.save()


def a10(exe):
    s = Sim(exe, "A10_camera_snapshot")
    s.tick(0, task=4)
    s.run_until_ledr(R_G)                           # Task 4 green
    s.run_for(1.0)
    s.pulse("vehicleButton")                        # car enters, stays
    s.run_until_ledr(R_Y)
    s.run_for(1.5)
    act = [t for t, m in s.msgs if "Camera activated" in m]
    snap = [t for t, m in s.msgs if "Snapshot taken" in m]
    yel = [c[0] for c in s.changes if c[2] == R_Y]
    ok = len(act) == 1 and len(snap) == 1 and abs(act[0] - yel[-1]) < EPS and abs(snap[0] - act[0] - 1.0) < EPS
    check("A10", ok, f"car present at yellow: 'Camera activated' at yellow start, 'Snapshot taken' "
          f"{snap[0] - act[0] if act and snap else '-'} s later")
    s.save()


def a11(exe):
    s = Sim(exe, "A11_car_leaves_early")
    s.tick(0, task=4)
    s.run_until_ledr(R_G)
    s.run_for(1.0)
    s.pulse("vehicleButton")                        # enters
    s.run_until_ledr(R_Y)
    s.run_for(0.5)
    s.pulse("vehicleButton")                        # leaves after 0.5 s
    s.run_for(3.0)
    act = [m for t, m in s.msgs if "Camera activated" in m]
    left = [m for t, m in s.msgs if "Vehicle left" in m]
    snap = [m for t, m in s.msgs if "Snapshot taken" in m]
    ok = len(act) == 1 and len(left) == 1 and not snap
    check("A11", ok, f"car leaves 0.5 s after activation: 'Vehicle left' {len(left)}, snapshots {len(snap)}")
    s.save()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--sim", help="existing simulation.exe (default: build with KIELER)")
    ap.add_argument("--chart", default=str(CHART), help="chart to build (default: the committed Version A)")
    ap.add_argument("--out", default=str(HERE), help="folder for results and traces")
    args = ap.parse_args()
    global OUT
    OUT = Path(args.out)
    OUT.mkdir(parents=True, exist_ok=True)
    tmp = tempfile.mkdtemp(prefix="versionA_sim_")
    if args.sim:
        exe, warnings = args.sim, ["(prebuilt simulator)"]
    else:
        exe, warnings = build_simulator(Path(tmp) / "combined", args.chart)
    exe1, _ = build_simulator(Path(tmp) / "task1", TASK1_CHART)
    exe2, _ = build_simulator(Path(tmp) / "task2", TASK2_CHART)
    for test in (a2, a3, a4, a5, a6, a7, a8_a9_a13, a10, a11, a14, a15):
        test(exe)
    a16(exe1)
    a17(exe2)
    lines = [f"Version A headless KIELER simulation ({SYSTEM}) of {args.chart}, "
             f"{time.strftime('%Y-%m-%d %H:%M:%S %z')}",
             "KIELER messages: " + ("; ".join(warnings) if warnings else "none"), ""]
    for test, status, detail in sorted(RESULTS, key=lambda r: int(r[0][1:])):
        lines.append(f"{test:4s} {status}  {detail}")
    passed = sum(1 for r in RESULTS if r[1] == "PASS")
    lines += ["", f"TOTAL: {passed} passed, {len(RESULTS) - passed} failed, of {len(RESULTS)}"]
    (OUT / "A_results.txt").write_text("\n".join(lines) + "\n", encoding="utf-8")
    print("\n".join(lines))
    shutil.rmtree(tmp, ignore_errors=True)
    return 0 if passed == len(RESULTS) else 1


if __name__ == "__main__":
    sys.exit(main())
