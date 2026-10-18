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
| T0 | M | PASS | `check_board_log.py` over all 13 raw logs: 0 violations (680 phases). Negative test with a synthetic bad log: all 6 violation kinds detected (count, change, value, safety, short all-red, 97->34 without a commit); a synthetic Task 3 commit log is accepted. |

## A. Version A - simulator regression

| ID | P | Status | Evidence |
|---|---|---|---|
| A1 | M | PASS | KIELER CLI, netlist C and netlist simulation C systems, committed charts: 0 errors. Messages: "Instantaneous loop detected!" (expected) and "ValuedObject ...SD is contained in the model but not in VariableStore" for the clocks' sleep-deadline helpers (`cSD`, `wNSSD`, `wEWSD`, `cameraClockSD`) - informational: those helpers are not listed in the simulator's data table. |
| A2 | M | PENDING | Needs a KIELER Dynamic-mode trace (no `.ktrace` in the repo). |
| A3 | M | PENDING | as A2 |
| A4 | M | PENDING | as A2 |
| A5 | S | PENDING | as A2 |
| A6 | M | PENDING | as A2 |
| A7 | M | PENDING | as A2 |
| A8 | M | PENDING | as A2 |
| A9 | M | PENDING | as A2 |
| A10 | M | PENDING | as A2 |
| A11 | M | PENDING | as A2 |
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
| C2.3 | M | PENDING | Part 6. |
| C2.4 | S | PENDING | Part 6. |
| C2.5 | S | PENDING | Part 6. |
| C2.6 | M | PENDING | Part 6. |
| C3.1 | M | PASS | `B_functional_retest_task3.txt` (switches 0x00002): no change after `34 -> 36` for ~55 s; console then showed the hold ended at 55.3 s (14120 events) when SW0 was raised. |
| C3.2-C3.8 | M/S | PENDING | Needs an RS-232 / USB-serial cable (this PC has no COM port). |
| C4.1 | M | PASS | `B_functional_retest_task4.txt`: Camera activated, Snapshot taken, dwell 999207 us. |
| C4.2 | M | PASS | same file: `Vehicle left`. |
| C4.3 | M | PASS | same file: Camera activated, Vehicle left, no snapshot. |
| C4.4 | S | PASS | `B_E6_camera_100ms_yellow.txt`: 959.5 / 944.0 / 936.1 ms (band 900-1000); `B_E6_camera_100ms.txt`: armed at yellow start 999.07-999.31 ms. |
| C4.5 | S | PENDING | Part 6. |
| C4.6 | M | PENDING | Part 6. |
| C4.7 | M | PENDING | Part 6. |
| C5.1 | M | PENDING | Part 6. |
| C5.2 | M | PENDING | Part 6. |
| C5.3 | M | PENDING | Part 6 (15 min unattended). |
| C5.4 | S | PENDING | Part 6. |
| C5.5 | N | PENDING | Part 6. |

## D. Submission readiness

| ID | Status | Evidence |
|---|---|---|
| D1 | PENDING | Lab PC (full licence). |
| D2 | PENDING | Lab PC. |
| D3 | PENDING | After D1. |
| D4 | PASS | `git clone` of commit `774e0a2` into `%TEMP%\cs303_fresh`; Nios II command-line tools only: `nios2-bsp-generate-files --settings=settings.bsp --bsp-dir=.`, `make` (BSP), `make` (traffic_b): 0 errors, 0 warnings, **no manual edits**. Regeneration changed only "Generated:" timestamps and the recorded `BspGeneratedLocation`. ELF section sizes identical to the working-copy build (text 92408, data 7388, bss 388). The Quartus hardware rebuild needs `qsys-generate` first (generated `nios2_system/` HDL is not tracked) - part of D1. |
| D5 | PENDING | Part 7. |
| D6 | PENDING | Part 8. |
| D7 | PASS | Commit `774e0a2`: AI Use Declaration in all 5 charts, both `main.c` (identical), `pc_test.c`, `pc_suite.c`, `pc_suite_print.h`, `analyse_logs.py`, `check_board_log.py`, `diff_A_B.py`, `board_test.v`, `COMPSYS303_Lab1_diag.v`. The KIELER-generated `TrafficLight_B.c/.h` carry none (regenerated files; to be stated in the README). |
| D8 | PENDING | Part 8. |
| D9 | PENDING | Part 8. |
| D10 | PENDING | Report (group). |
| D11 | PENDING | Group. |
| D12 | PENDING | Part 9. |
