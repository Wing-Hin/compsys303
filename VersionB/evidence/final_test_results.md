# COMPSYS303 final test results

Status per test ID of the final test plan: **PASS**, **FAIL**, **PENDING** or **N/A**, with the
evidence. Board logs are raw `nios2-terminal` output in `VersionB/evidence/B_*.txt`; every one is
checked by `check_board_log.py` (T0).

## Inputs the plan refers to that do not exist in the repo

| Item | Finding |
|---|---|
| 6th `.sctx` (`Task2_VersionB.sctx`) | Not found anywhere under the user folders. The repo has 5 project charts: `Task1_VersionA`, `Task2_VersionA`, `TrafficLight_VersionA`, `VersionB/Task1_VersionB`, `VersionB/TrafficLight_VersionB` (`cs303_lab/cs303_lab2.sctx` is the Lab 2 file). |
| Version A `.ktrace` traces, `check_ktrace.py` | Not found. A2–A11 have no committed simulator evidence yet. |

## T0 - log checker

| ID | P | Status | Evidence |
|---|---|---|---|
| T0 | M | PASS | `check_board_log.py` over all 20 raw board logs (after Part 6): 1854 phases, 0 violations. Negative test with a synthetic bad log: all 6 violation kinds detected (count, change, value, safety, short all-red, 97->34 without a commit); a synthetic Task 3 commit log is accepted. |

## A. Version A - simulator regression

| ID | P | Status | Evidence |
|---|---|---|---|
| A1 | M | PASS | KIELER CLI, netlist C and netlist simulation C systems, committed charts: 0 errors. Messages: "Instantaneous loop detected!" (expected) and "ValuedObject ...SD is contained in the model but not in VariableStore" for the clocks' sleep-deadline helpers (`cSD`, `wNSSD`, `wEWSD`, `cameraClockSD`) - informational: those helpers are not listed in the simulator's data table. |
| A2 | M | PASS | Real-time Dynamic stepping, 2 cycles: 33,34,36,12,20,36 x2 at 6/2/0.5/6/2/0.5 s, errors +0.1..+0.6 ms (PC sleep jitter). `versionA/A_results.txt`, trace in `versionA/trace_A2_task1_realtime.jsonl`. |
| A3 | M | PASS | NS press in R-G -> next G-R 97 for 4.0 s, then 33. `versionA/A_results.txt`, trace in `versionA/trace_A3_ns_press_in_RG.jsonl`. |
| A4 | M | PASS | EW press in G-R -> next R-G 140 for 4.0 s, then 12. `versionA/A_results.txt`, trace in `versionA/trace_A4_ew_press_in_GR.jsonl`. |
| A5 | S | PASS | Press during its own G-R: that green 6.0 s without walk, walk at the next G-R. `versionA/A_results.txt`, trace in `versionA/trace_A5_press_in_own_green.jsonl`. |
| A6 | M | PASS | Task 1 -> 2 set mid-green (t = 10.5 s): activeTask changed at t = 16.5 s, on the tick entering R-R (LEDR 20 -> 36). `versionA/A_results.txt`, trace in `versionA/trace_A6_task_change_mid_green.jsonl`. |
| A7 | M | PASS | Request in Task 2, Task 1 green without walk, walk served after returning to Task 2. `versionA/A_results.txt`, trace in `versionA/trace_A7_request_retained_2_1_2.jsonl`. |
| A8 | M | PASS (Dynamic-mode caveat) | `8,3,1,8,3,1` + LF applied at R-R; phases 8/3/1/8/3/1 s. The commit tick requests no wake-up (sleepT = 1000, KIELER's no-deadline value), so in pure Dynamic mode the new all-red only ends when another tick arrives (the driver polls every 0.1 s when no deadline is requested). `versionA/A_results.txt`, trace in `versionA/trace_A8_A9_task3.jsonl`. |
| A9 | M | PASS | `1,2,3` + LF in the hold: configRejected 0 -> 1, lights stay 36, nothing applied. `versionA/A_results.txt`, trace in `versionA/trace_A8_A9_task3.jsonl`. |
| A10 | M | **FAIL** | 'Camera activated' at yellow start, but **no 'Snapshot taken'**: after `ArmedCheck` the Camera region stops (see finding below). With the proposed fix: snapshot exactly 1.0 s after activation. `versionA/A_results.txt`, trace in `versionA/trace_A10_camera_snapshot.jsonl`. |
| A11 | M | **FAIL** | Same cause: the car leaving after 0.5 s is not seen ('Vehicle left' 0). With the proposed fix: 'Vehicle left' 1, no snapshot. `versionA/A_results.txt`, trace in `versionA/trace_A11_car_leaves_early.jsonl`. |
| A12 | M | PASS | Commit `774e0a2` (Part 2, wording approved): `TrafficLight_VersionA.sctx` now declares Claude (Tasks 1-2) and OpenAI Codex (Task 3 parser, Task 4 camera); `Task1/Task2_VersionA` declare Claude. Open question for the group: `TASK3.md` says Codex assisted with Task 3 "design decisions", while the declaration says all design decisions were made by Harold and Lucas. |

## B. Version B - static checks

| ID | P | Status | Evidence |
|---|---|---|---|
| B1 | M | PASS | No `clock`, `float`, `deltaT`, `@ClocksUseSD` in code (comments excluded); 32 states, all 59 `go to` transitions (30 distinct targets) resolve. |
| B2 | M | PASS | `diff_A_B.py`: all 8 time constants equal (A s x 1000 = B ms); after normalising the timing syntax only the 5 lines of the documented `ArmedCheck` state differ. |
| B3 | M | PASS | Committed chart (from `git show HEAD`) compiled with `de.cau.cs.kieler.sccharts.netlist`: exit 0, only "Instantaneous loop detected!". |
| B4 | M | PASS | All 11 `TickData` fields used by `main.c` exist (EWraised, LEDR, NSraised, cameraActivated, configChar, configReady, configValid, snapshotTaken, task, timerTick, vehicleButton); no `double`. |
| B5 | M | PASS | Regenerated `TrafficLight_B.c/.h` from the committed chart: byte-identical to the committed files; `pc_test` and the Task 2 scenario outputs identical. |
| B6 | M | PASS | `pc_test`: 600/200/50/600/200/50 events per phase. |
| B7 | S | PASS | `main.c`: `CHART 4`, `TIMER_PERIOD_MS 10`; chart `TIMER_MS = 10`. |
| B8 | S | PASS | `VersionB/nios/pc_suite.c`, output in `pc_suite_results.txt`: 29/29 cases pass (S28: 1,000,000 random ticks, 437 LEDR changes, 90 commits, 66 rejects, 13 snapshots, 0 rule violations). Mode-change rule used: activeTask changes only inside an all-red, i.e. on a tick that starts or ends with LEDR 36 (entering R-R and leaving a finished R-R are immediate transitions; approved). |

### Finding from the extra case X1 (not in the plan): 0-second time-outs

The Task 3 parser accepts `0` as a value. With a 0 s yellow or all-red the lights skip that phase
(observed in a random run: `33 -> 36`, `12 -> 36`, `140 -> 36` = green straight to red;
`33 -> 140` = NS green to EW green in one tick). Only reachable by sending zeros over RS-232.
**Decision: documented as a limitation** (every Task 3 value must be at least 1 s); no chart change.
A parser change that rejects 0 remains possible with the group's OK.

## C. Version B - board tests (DE2-115)

| ID | P | Status | Evidence |
|---|---|---|---|
| C1.1 | M | PASS | `B_task1_10ms.txt`: 63 phases, 600/200/50 events, worst mean error 0.10 ms; T0 clean. |
| C1.2 | S | PASS | `B_E2_1ms.txt`, `B_E2_100ms.txt`, `B_E3_300ms.txt`, `B_E4_rescale.txt` (see `B_summary.md`); T0 clean. |
| C1.3 | M | PASS | T0 over every B log: 0 violations. |
| C2.1 | M | PASS | `B_functional_retest.txt`: `36 -> 97`, `97 -> 33` after 400 events. |
| C2.2 | M | PASS | `B_functional_retest.txt`: `36 -> 140`, `140 -> 12` after 400 events. |
| C2.3 | M | PASS | `B_C2_task2.txt` (switches 0x00001): KEY0+KEY1 together at the all-red -> `36 -> 140`/`140 -> 12` (400) then `36 -> 97`/`97 -> 33` (400) in the next green. A first attempt registered only KEY1 (edge capture 0x6, no KEY0 bit) and correctly gave only the EW walk. |
| C2.4 | S | PASS | `B_C2_task2.txt`: KEY0 held 3 s in R-G -> one NS walk (400 events); the next two NS greens plain `36 -> 33`. |
| C2.5 | S | PASS | `B_C2_task2.txt`: KEY0 during an NS green without a walk -> that green `33 -> 34` after 600 (no walk), next NS green `36 -> 97`. Note: a press while the walk light is already on is absorbed by the running walk (nsServed is updated when the walk ends). |
| C2.6 | M | PASS | `B_C2_task2.txt`: request made, Task 1 active (0 walks in lines 245-297; Task 1 tick rate), SW0 back up -> first Task 2 NS green `36 -> 97`, `97 -> 33` after 400 events. |
| C3.1 | M | PASS | `B_functional_retest_task3.txt` (switches 0x00002): no change after `34 -> 36` for ~55 s (the end of that hold was seen on an unlogged console only); re-confirmed in `B_C3_task3_exit.txt`: hold of 13097 events (131 s), left at once on SW 00. |
| C3.2-C3.6, C3.8 | M/S | PENDING - needs cable | No RS-232 / USB-serial adapter: this PC has no COM port. Parser behaviour covered on the PC by S11-S19. |
| C3.7 | M | PASS | `B_C3_task3_exit.txt` (switches 0x00002): hold at 36 (13097 events = 131 s), SW 00 -> left at once, then 600/200/50/600/200/50 with the default (last committed) time-outs. The first green after the hold is 5997.2 ms: leaving the hold happens between two timer events (same quantisation as E6 ii). |
| C4.1 | M | PASS | `B_functional_retest_task4.txt`: Camera activated, Snapshot taken, dwell 999207 us. |
| C4.2 | M | PASS | same file: `Vehicle left`. |
| C4.3 | M | PASS | same file: Camera activated, Vehicle left, no snapshot. |
| C4.4 | S | PASS | `B_E6_camera_100ms_yellow.txt`: 959.5 / 944.0 / 936.1 ms (band 900-1000); `B_E6_camera_100ms.txt`: armed at yellow start 999.07-999.31 ms. |
| C4.5 | S | PASS | `B_C4_task4.txt` (switches 0x00003): one car, Camera activated + Snapshot taken (999.3 ms) at the first yellow, then 4 more yellows with no camera messages. |
| C4.6 | M | PASS | `B_C4_task4.txt`: car entered while Task 1 was active - no camera messages over several yellows; CPU state read by gdb afterwards (vehiclePresent 1); on returning to Task 4 the car was photographed at the first yellow (`12 -> 20`, 998.9 ms), proving it was tracked but ignored in Task 1. |
| C4.7 | M | PASS | `B_C4_task4.txt`: in Task 4, KEY0 -> `36 -> 97`/`97 -> 33` (400), KEY1 -> `36 -> 140`/`140 -> 12` (400). |
| C5.1 | M | PASS | `B_C5_modes.txt`: mid-green change 4 -> 3: the green (600) and yellow (200) finished, the hold began only at the all-red; 3 -> 1 left the hold; 1 -> 2, 2 -> 4, 4 -> 1 mid-green: legal sequence throughout (T0: 0 violations), the task-specific loop rate changes only after an all-red. The tick rate is too noisy to time each change exactly; the exact rule is proven on the PC (S9). |
| C5.2 | M | PASS | `B_C5_modes.txt`: KEY3 during an EW green -> new `Version B running`, `-1 -> 33`, full 600-event G-R, normal cycle. |
| C5.3 | M | PASS | `B_C5_15min.txt`: 324 phases over 918 s (15.3 min) unattended, one program start (no freeze/reset); every phase within -0.41..+0.43 ms of nominal, the last 20 within 0.34 ms (well after the 85.9 s stopwatch period, so the timer_1 fix holds); stopwatch sum 918.0 s = 91800 events x 10 ms; T0 clean. |
| C5.4 | S | PASS | `B_C5_modes.txt`: about 30 s of random KEY0-KEY2 presses in Task 4: both walks and a snapshot served, no freeze, T0 0 violations. |
| C5.5 | N | PASS (limitation noted) | `B_C5_console.txt`: console closed 01:54:06 for ~50 s: no freeze, timing exact, and the buffered output (~50 s) was delivered on re-attach with no gap. The HAL JTAG UART buffer is finite (default 2 KB, about 70 s of output): beyond that output is dropped or printf briefly delays the loop - documented limitation. |

## D. Submission readiness

| ID | Status | Evidence |
|---|---|---|
| D1 | PENDING | Lab PC (full licence). |
| D2 | PENDING | Lab PC. Check: RUN/PROG -> PROG, Programmer in Active Serial Programming mode, program the `.pof`; RUN/PROG -> RUN; power-cycle -> FPGA loads from flash without programming -> `nios2-download -g traffic_b.elf` -> lights cycle. The `.pof` holds only the hardware; the Nios II program runs from SDRAM. |
| D3 | PENDING | After D1. |
| D4 | PASS | `git clone` of commit `774e0a2` into `%TEMP%\cs303_fresh`; Nios II command-line tools only: `nios2-bsp-generate-files --settings=settings.bsp --bsp-dir=.`, `make` (BSP), `make` (traffic_b): 0 errors, 0 warnings, **no manual edits**. Regeneration changed only "Generated:" timestamps and the recorded `BspGeneratedLocation`. ELF section sizes identical to the working-copy build (text 92408, data 7388, bss 388). The Quartus hardware rebuild needs `qsys-generate` first (generated `nios2_system/` HDL is not tracked) - part of D1. |
| D5 | PASS | `B_D5_fresh_clone.txt`: the fresh-clone ELF ran Task 1 (switches 0x00000): 22 phases at 600/200/50 events, within 0.4 ms; T0 clean. |
| D6 | PASS | Top-level `README.md`: SW1..0 = task, KEY0/KEY1/KEY2, KEY3 = reset, LEDR bits, RS-232 115200 8N1 + packet format, JTAG console, "Version A = simulator, Version B = board", known limitations. Group members' full names and UPIs still to fill in. |
| D7 | PASS | Commit `774e0a2`: AI Use Declaration in all 5 charts, both `main.c` (identical), `pc_test.c`, `pc_suite.c`, `pc_suite_print.h`, `analyse_logs.py`, `check_board_log.py`, `diff_A_B.py`, `board_test.v`, `COMPSYS303_Lab1_diag.v`. The KIELER-generated `TrafficLight_B.c/.h` carry none (regenerated files; to be stated in the README). |
| D8 | PENDING | `VersionB/make_submission.ps1 -DryRun`: 216 files, 1.8 MB (5 charts - no 6th exists; traffic_b + traffic_b_bsp without obj/; sopcinfo; README; evidence incl. figures). Fails loudly until the `.pof` exists; group number N still needed. |
| D9 | PASS | Dry-run list contains no `db/`, `incremental_db/`, `.metadata/`, `obj/`, `Hello_lab1*`, `_to_delete/`, board_test outputs or `TASK3_EDGE_RESULTS.md`. |
| D10 | PENDING | Report (group). |
| D11 | PENDING | Group. |
| D12 | PASS | Pushed to `origin` (github.com/Wing-Hin/compsys303): `fcc6427..7743789 main -> main`; remote `main` = local HEAD `7743789`. |

## Known limitations found while testing

* The microsecond stopwatch (timer_1, 32-bit at 50 MHz) wraps every 85.9 s, so a **single** phase longer
  than that (a Task 3 hold) is reported 85.9 s short in the console; its timer-event count is correct.
* The JTAG UART output is buffered by the HAL (about 2 KB); with no console attached for longer than
  that, output is lost or `printf` can briefly delay the loop.
* The time-limited (OpenCore Plus) `.sof` stops the Nios II if the JTAG tether is interrupted (seen
  once at 00:13: Quartus Error 209059); re-configuring the `.sof` restores it.
* Task 3 values are integer seconds and must be at least 1 s (0 s skips yellow/all-red, see X1).
* Leaving a Task 3 hold, or a car arriving mid-yellow, happens between two timer events, so the first
  phase (or the camera dwell) afterwards is up to one timer period short (10 ms at 10 ms, 100 ms in E6).

## Finding: Version A camera never takes a snapshot (A10, A11)

* `TrafficLight_VersionA.sctx` (commit `9ceac57` added the `ArmedCheck` state for the Dynamic-mode wake-up).
  `ArmedCheck` has two immediate transitions to the **same** target (`NextCameraTick`), one guarded by the clock
  (`cameraClock >= CAMERA_DWELL`). KIELER's netlist code for it is
  `_g200 = ... || (_g203 && _cg205) || (_g203 && _cg205) || ...` - the fallback should be `(_g203 && !_cg205)`.
  While the clock is below 1 s the region therefore never re-enters `NextCameraTick`: the Camera region stops after
  'Camera activated', so no snapshot and no departure are ever seen.
* Before `ArmedCheck` (commit `732f462`) the snapshot works (1 s after activation with deltaT = 1) but the
  activation tick requests the wake-up at the end of yellow (sleepT = 2), which is what `ArmedCheck` was meant to fix.
* Proposed minimal fix (tested on a copy, 10/10 A-tests pass): send `ArmedCheck`'s fallback to a separate state
  `ArmedTick` that is identical to `NextCameraTick` (`go to SampleVehicle`). The activation tick then requests
  sleepT = 1 and the snapshot comes exactly 1.0 s later. **Not applied: chart change awaiting approval.**

## Finding: Version A Task 3 commit tick requests no wake-up (A8)

On the tick that applies a valid packet the chart leaves sleepT at KIELER's default 1000 s, so in pure Dynamic mode the
new all-red ends only when another tick happens (an input change or a manual step). With manual/periodic stepping
(as `TASK3.md` describes) the timings are correct. Documented; no change proposed yet.
