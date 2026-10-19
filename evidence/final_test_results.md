# COMPSYS303 final test results

Status per test ID of the final test plan: **PASS**, **FAIL**, **PENDING** or **N/A**, with the
evidence. Paths are relative to `evidence/`: board logs (raw `nios2-terminal` output, `B_*.txt`) are in
`board_logs/`, every one checked by `scripts/check_board_log.py` (T0); `versionA/` holds the Version A
simulation, `pc_suite/` the PC test suite. Rows marked **[re-run on the final files, 19 Oct 18:15]** were repeated on the final
submission files (the tidied zip layout); all other rows record the run named in them.

## Inputs the plan refers to

| Item | Finding |
|---|---|
| Stand-alone Task 1 / Task 2 charts | `Task1_VersionA/B.sctx` and `Task2_VersionA/B.sctx` were removed before submission (2026-10-19): Tasks 1-4 are submitted as one combined chart per version (`VersionA/TrafficLight_VersionA.sctx`, `VersionB/TrafficLight_VersionB.sctx`). Their own tests (A16, A17, B9, B10) were dropped with them. |
| Version A `.ktrace` traces, `check_ktrace.py` | Not found. Replaced by the headless KIELER simulation `versionA/run_versionA_sim.py` (A2-A11, A13-A15) with JSON traces. |

## T0 - log checker

| ID | P | Status | Evidence |
|---|---|---|---|
| T0 | M | PASS | **[re-run on the final files, 19 Oct 18:15]** `check_board_log.py` over all 22 raw board logs: 2172 phases, 0 violations. Negative test with a synthetic bad log: all 6 violation kinds detected (count, change, value, safety, short all-red, 97->34 without a commit); a synthetic Task 3 commit log is accepted. The checker also reads the `# ... sent ...: <packet>` markers: a phase may last the count of any **valid** packet (six 1-4 digit fields in ms, none 0) sent earlier in that log (approved rule change). Re-run negative test: wrong counts still fail without a marker, after a valid packet and after an invalid (ignored) packet; a short all-red still fails. |

## A. Version A - simulator regression

`versionA/run_versionA_sim.py` builds KIELER's own netlist C simulator from each chart and drives it
in Dynamic mode (results in `versionA/A_results.txt`, one JSON trace per test). **Strict** Dynamic mode
(A8, A14, A15) ticks only on the chart's own wake-up (`sleepT`) or an input, exactly as KIELER does.

| ID | P | Status | Evidence |
|---|---|---|---|
| A1 | M | PASS | KIELER CLI, netlist C and netlist simulation C systems, both charts: 0 errors. Messages: "Instantaneous loop detected!" and, for clocks, "ValuedObject ...SD is contained in the model but not in VariableStore" (`cSD`, `wNSSD`, `wEWSD`, `cameraClockSD`). Both explained by `kieler_warning/` (B11): the warning comes from KIELER's expansion of clocks / during actions, not from a loop without a delayed transition. |
| A2 | M | PASS | **[re-run on the final files, 19 Oct 18:15]** (A2-A15: 13/13 again; A2's real-time jitter +0.1..+0.5 ms on the re-run, the committed run below is the one in the report) Real-time Dynamic stepping, 2 cycles: 33,34,36,12,20,36 x2 at 6/2/0.5/6/2/0.5 s, errors +0.2..+0.6 ms (PC sleep jitter). Trace `trace_A2_task1_realtime.jsonl`. |
| A3 | M | PASS | NS press in R-G -> next G-R 97 for 4.0 s, then 33. `trace_A3_ns_press_in_RG.jsonl`. |
| A4 | M | PASS | EW press in G-R -> next R-G 140 for 4.0 s, then 12. `trace_A4_ew_press_in_GR.jsonl`. |
| A5 | S | PASS | Press during its own G-R: that green 6.0 s without walk, walk at the next G-R. `trace_A5_press_in_own_green.jsonl`. |
| A6 | M | PASS | Task 1 -> 2 set mid-green (t = 10.5 s): activeTask changed at t = 16.5 s, on the tick entering R-R (LEDR 20 -> 36). `trace_A6_task_change_mid_green.jsonl`. |
| A7 | M | PASS | Request in Task 2, Task 1 green without walk, walk served after returning to Task 2. `trace_A7_request_retained_2_1_2.jsonl`. |
| A8 | M | PASS | `8000,3000,1000,8000,3000,1000` + LF (ms) in the hold, **strict** Dynamic mode: applied at R-R; the commit tick requests sleepT = 1 s and the all-red ends exactly 1.0 s after the commit; phases 8/3/1/8/3/1 s. (Before the commit-target fix the commit tick requested sleepT = 1000 = no wake-up, see finding.) `trace_A8_A9_A13_task3.jsonl`. |
| A9 | M | PASS | `1,2,3` + LF in the hold: configRejected 0 -> 1, lights stay 36, nothing applied. Same trace. |
| A10 | M | PASS | Car present at yellow -> 'Camera activated' at yellow start, 'Snapshot taken' exactly 1.0 s later; the activation tick requests sleepT = 1. `trace_A10_camera_snapshot.jsonl`. |
| A11 | M | PASS | Car leaves 0.5 s after activation -> 'Vehicle left', no snapshot. `trace_A11_car_leaves_early.jsonl`. |
| A12 | M | PASS | Commit `774e0a2` (Part 2, wording approved): `TrafficLight_VersionA.sctx` declares Claude (Tasks 1-2) and OpenAI Codex (Task 3 parser, Task 4 camera). Resolved by the group (2026-10-19): all design decisions were made by Harold and Lucas; `TASK3.md` now says so and credits Codex for the Task 3 code, documentation and tests only. |
| A13 | M | PASS | New: `6000,2000,0,...` (0 in a middle field, comma path) and `...,2000,0` (0 in the last field, LF path) in the hold: configRejected 1 -> 3, lights stay 36, nothing applied. Same trace as A8. |
| A14 | M | PASS | New (computational effort): Task 1, 10 cycles (170 s), strict Dynamic mode: **61 reactions** for 60 LEDR changes = 6.1 per 17 s cycle, every phase exact. Version B at 10 ms computes about 2,180 reactions per second, 37,067-37,072 per Task 1 cycle (`B_task1_10ms.txt`, `B_summary.md`). `trace_A14_ticks_task1.jsonl`. |
| A15 | M | PASS | New: Task 4, about 2 cycles with a car and a snapshot, strict Dynamic mode: **19 reactions** (4 of them the button pulses); snapshot 1.0 s after activation. Two independent clocks; a tick only when one of them expires or an input arrives. `trace_A15_ticks_task4.jsonl`. |

## B. Version B - static checks

| ID | P | Status | Evidence |
|---|---|---|---|
| B1 | M | PASS | No `clock`, `float`, `deltaT`, `@ClocksUseSD` in code (comments excluded); 32 states, all 59 `go to` transitions (30 distinct targets) resolve. |
| B2 | M | PASS | **[re-run on the final files, 19 Oct 18:15]** `diff_A_B.py` over the A/B pair (Tasks 1-4 combined): every time constant equal (A s x 1000 = B ms); the normalised charts are identical. The only documented difference is the A-only camera wake-up block (`ArmedCheck` + `ArmedTick`, 6 lines) in the combined chart; the Task 3 conversion `/ MS_PER_S` (A only, packets are ms) is normalised. |
| B3 | M | PASS | Both charts compiled with `de.cau.cs.kieler.sccharts.netlist`: exit 0; Version B charts give only "Instantaneous loop detected!" (from the during actions, B11). |
| B4 | M | PASS | All 11 `TickData` fields used by `main.c` exist (EWraised, LEDR, NSraised, cameraActivated, configChar, configReady, configValid, snapshotTaken, task, timerTick, vehicleButton); no `double`. |
| B5 | M | PASS | `TrafficLight_B.c/.h` regenerated from the current chart (Task 3 in ms, 0 rejected, commit to `RRnExit`) and committed with it. The generated fallback of the new two-transition `RRnConfig` is correct (`_g84 && !_cg78`): the camera-style KIELER guard bug does not recur. |
| B6 | M | PASS | `pc_test`: 600/200/50/600/200/50 events per phase. |
| B7 | S | PASS | `main.c`: `CHART 4`, `TIMER_PERIOD_MS 10`; chart `TIMER_MS = 10`. |
| B8 | S | PASS | **[re-run on the final files, 19 Oct 18:15]** Strict C99 (`-std=c99 -Wall`): 0 warnings. `pc_suite/pc_suite.c`, output in `pc_suite/pc_suite_results.txt`: **30/30** cases pass (packets in ms; S13 now 7 invalid packets incl. two with a 0 field; S28: 1,000,000 random ticks, 537 LEDR changes, 92 commits, 70 rejects, 14 snapshots, 0 rule violations; **S30** (was the informational X1): 1,000,000 random ticks whose packets have 0 fields: 216 rejects, 34 commits, no 0 time-out applied, 0 rule violations). Mode-change rule used: activeTask changes only inside an all-red, i.e. on a tick that starts or ends with LEDR 36 (approved). |
| B11 | S | PASS | New: `kieler_warning/run_kieler_warning.py` -> `kieler_warning/results.txt`. A delayed loop compiles silently (W1); the same loop with a during counter (W2, Version B style) or a clock (W3, Version A style) gives exactly "Instantaneous loop detected!" and still generates code; an all-immediate loop (W4) gives the warning **plus** "The SCG is NOT asc-schedulable!" and no code. Both controller charts behave like W2/W3. |

### Finding (fixed): 0-second time-outs (was X1)

The Task 3 parser accepted `0`. With a 0 yellow or all-red the lights skipped that phase (random run:
`33 -> 36`, `12 -> 36`, `140 -> 36` = green straight to red; `33 -> 140` = NS green to EW green in one tick).
**Fixed (2026-10-19):** a 0 field now makes the packet invalid (`digits > 0 && number > 0` in the comma
and LF transitions, Version A and B identical). Evidence: A13, S13, S30, C3.11.

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
| C3.1 | M | PASS | `B_functional_retest_task3.txt` (switches 0x00002): no change after `34 -> 36` for ~55 s; re-confirmed in `B_C3_task3_exit.txt` (hold of 13097 events = 131 s) and `B_C3_jtag_packets.txt` (hold of 3053 events while two invalid packets were rejected). |
| C3.2 | M | PASS | `B_C3_jtag_packets.txt` (current build; switches 0x00002; packets in **ms** over the JTAG UART console, sent by an automated driver that marks each packet in the log): held at 36, `8000,3000,1000,8000,3000,1000\r\n` (line 14) -> hold ends (line 15: 3053 events), then 800/300/100 events every phase (7999.821 / 2999.857 / 1000.154 ms, lines 16-21). |
| C3.3 | M | PASS | Same log line 12: `1,2,3\r\n` in the hold -> no change for 8 s; rejected. |
| C3.4 | M | PASS | Same log lines 12-15: after the rejected packets of C3.3 and C3.11 the valid packet of C3.2 ends the hold: the parser recovered. |
| C3.5 | S | PASS | Same log line 22: `2000,1000,1000,2000,1000,1000\n` (LF only) sent 2 s into the EW green (12): that green and its yellow kept 800/300 (lines 23-24), the commit happened in the next R-R (100 events, line 25), then 200/100/100 (lines 26-29). Matches S16. |
| C3.6 | S | PASS | Same log line 30: `12345,1,1,1,1,1\n` -> 13 phases of 200/100/100 unchanged (lines 31-43); rejected, and the parser kept working (C3.8 next). |
| C3.7 | M | PASS | `B_C3_task3_exit.txt` (switches 0x00002): hold at 36 (13097 events = 131 s), SW 00 -> left at once, then 600/200/50/600/200/50 with the default (last committed) time-outs. The first green after the hold is 5997.2 ms: leaving the hold happens between two timer events (same quantisation as E6 ii). |
| C3.8 | S | PASS | Same log line 44: `8000,3000,1000,8000,3000,1000\n` twice in one write -> both committed in the same all-red (line 48: **101** events - the second commit came just after the first timer event and restarted the all-red count, the safe direction, see finding), then 800/300/100 every phase (lines 49-57). |
| C3.9 | S | PASS | New: same log line 58: `6000,2000,500,6000,2000,500\n` -> the **defaults restored exactly**, 600/200/50 (500.317 ms all-red, lines 61-70). Not possible with the earlier seconds format. |
| C3.10 | S | PASS | New: same log line 71: `1234,567,89,4321,765,98\n` -> 124/57/9/433/77/10 events = ceil(T / 10 ms): measured 1240.059 / 569.638 / 90.389 / 4329.627 / 770.076 / 100.176 ms (lines 74-79): Version B rounds every time-out up to whole timer events. |
| C3.11 | M | PASS | New: same log line 13: `6000,2000,0,6000,2000,500\n6000,2000,500,6000,2000,0\n` in the hold -> no change for 8 s: both packets with a 0 field rejected. |
| C4.1 | M | PASS | `B_functional_retest_task4.txt`: Camera activated, Snapshot taken, dwell 999207 us. |
| C4.2 | M | PASS | same file: `Vehicle left`. |
| C4.3 | M | PASS | same file: Camera activated, Vehicle left, no snapshot. |
| C4.4 | S | PASS | `B_E6_camera_100ms_yellow.txt`: 959.5 / 944.0 / 936.1 ms (band 900-1000); `B_E6_camera_100ms.txt`: armed at yellow start 999.07-999.31 ms. |
| C4.5 | S | PASS | `B_C4_task4.txt` (switches 0x00003): one car, Camera activated + Snapshot taken (999.3 ms) at the first yellow, then 4 more yellows with no camera messages. |
| C4.6 | M | PASS | `B_C4_task4.txt`: car entered while Task 1 was active - no camera messages over several yellows; CPU state read by gdb afterwards (vehiclePresent 1); on returning to Task 4 the car was photographed at the first yellow (`12 -> 20`, 998.9 ms), proving it was tracked but ignored in Task 1. |
| C4.7 | M | PASS | `B_C4_task4.txt`: in Task 4, KEY0 -> `36 -> 97`/`97 -> 33` (400), KEY1 -> `36 -> 140`/`140 -> 12` (400). |
| C5.1 | M | PASS | `B_C5_modes.txt`: mid-green change 4 -> 3: the green (600) and yellow (200) finished, the hold began only at the all-red; 3 -> 1 left the hold; 1 -> 2, 2 -> 4, 4 -> 1 mid-green: legal sequence throughout (T0: 0 violations), the task-specific loop rate changes only after an all-red. The exact rule is proven on the PC (S9). |
| C5.2 | M | PASS | `B_C5_modes.txt`: KEY3 during an EW green -> new `Version B running`, `-1 -> 33`, full 600-event G-R, normal cycle. |
| C5.3 | M | PASS | `B_C5_15min.txt`: 324 phases over 918 s (15.3 min) unattended, one program start (no freeze/reset); every phase within -0.41..+0.43 ms of nominal, the last 20 within 0.34 ms; stopwatch sum 918.0 s = 91800 events x 10 ms; T0 clean. |
| C5.4 | S | PASS | `B_C5_modes.txt`: about 30 s of random KEY0-KEY2 presses in Task 4: both walks and a snapshot served, no freeze, T0 0 violations. |
| C5.5 | N | PASS (limitation noted) | `B_C5_console.txt`: console closed for ~50 s: no freeze, timing exact, buffered output delivered on re-attach with no gap. The HAL JTAG UART buffer is finite (default 2 KB, about 70 s of output) - documented limitation. |

### R1 - regression of Tasks 1, 2 and 4 on the current build

C1, C2, C4 and C5 were run with the earlier build. The current build changes only the Task 3 paths, and
R1 re-runs the main cases on it: `B_R1_tasks124_current_build.txt` (switch moves and key presses by Harold,
marked by `#` lines; T0: 237 phases, 0 violations).

| ID | P | Status | Evidence |
|---|---|---|---|
| R1.1 | M | PASS | Task 3 hold at start (4733 events, switches 10); SW1 down (00) -> hold left, Task 1 at 600/200/50 events every phase (lines 12-52). |
| R1.2 | M | PASS | SW0 up (01, Task 2), KEY0 -> next NS green `36 -> 97`, walk 400 events (4000.197 ms), then 200 (lines 95-97). |
| R1.3 | M | PASS | KEY1 -> next EW green `36 -> 140`, walk 400 events (3999.798 ms), then 200 (lines 124-126). A second EW walk two cycles later (lines 137-139) means a second KEY1 press was registered during the plain EW green of line 132; each request was served once. |
| R1.4 | M | PASS | SW1 up (11, Task 4), KEY2 in a green -> `Camera activated` at the yellow, `Snapshot taken` after 999.327 ms; no camera message at the following yellows (one snapshot per visit); KEY2 -> `Vehicle left` (lines 177-198). |
| R1.5 | M | PASS | Car leaving within 1 s of the activation: `Camera activated`, `Vehicle left`, no snapshot (lines 248-250). The try before (lines 238-242) left after the 1 s dwell and was photographed (999.297 ms), also correct. |

## D. Submission readiness

| ID | Status | Evidence |
|---|---|---|
| D1 | N/A | Quartus Prime **Lite** has no Nios II/f licence: a full compile only gives the OpenCore Plus `COMPSYS303_Lab1_time_limited.sof`, so a build without `_time_limited` is not possible with our tools. The submission packs the board-tested `.sof` instead (README *Programming files*); the hardware was not recompiled. |
| D2 | N/A | No `.pof` can be made from a time-limited (OpenCore Plus) `.sof`. A `.pof` would not hold the program anyway: the Nios II runs from SDRAM, so `traffic_b.elf` is downloaded over JTAG after every power-up. Replaced by `VersionB/run_board.bat` (program the `.sof` with the tether in its own window, `nios2-download -g traffic_b.elf`, `nios2-terminal`). |
| D3 | N/A (checked for the `.sof`) | No D1/D2 build, so the same check was made for the submitted `.sof`: `nios2_system.sopcinfo` `AUTO_GENERATION_ID` = 1786080893 (Platform Designer generation 2026-08-07 17:34:53) = `GENERATION_ID` in the `.sld` and `.jdi` of the compile that wrote the `.sof` (assembled 2026-08-21 14:38:23, Quartus checksum 0x008CFF92, the checksum in `board_input_test.txt`; SHA-256 `d11cd8f5e0924dc9990390fe9c7be95e8af5f9531cff8bd0cc3a2c47c62e6a10`). `make_submission.ps1 -Sof` refuses any other `.sof` or `.sopcinfo`. |
| D4 | PASS | **[re-run on the final files, 19 Oct 18:15]** Built from the **extracted `group_14.zip`** (`nios2-bsp-generate-files`, BSP `make`, app `make`): 0 errors, 0 warnings, text 91988 / data 7388 / bss 388, and `.entry`/`.exceptions`/`.text`/`.rodata`/`.rwdata` byte-identical to the shipped board-tested `traffic_b.elf`. Earlier: `git clone` of commit `774e0a2` into `%TEMP%\cs303_fresh`; Nios II command-line tools only: `nios2-bsp-generate-files --settings=settings.bsp --bsp-dir=.`, `make` (BSP), `make` (traffic_b): 0 errors, 0 warnings, **no manual edits**. Current build (Task 3 in ms): 0 warnings, text 91988, data 7388, bss 388. The Quartus hardware rebuild needs `qsys-generate` first (generated `nios2_system/` HDL is not tracked) - part of D1. |
| D5 | PASS | `B_D5_fresh_clone.txt`: the fresh-clone ELF ran Task 1 (switches 0x00000): 22 phases at 600/200/50 events, within 0.4 ms; T0 clean. |
| D6 | PASS | Top-level `README.md`: how the task and the timing version are selected, SW1..0 = task, KEY0/KEY1/KEY2, KEY3 = reset, LEDR bits, RS-232 115200 8N1 + JTAG console, Task 3 packet format (ms, 0 invalid), "Version A = simulator, Version B = board", known limitations, group members' full names and UPIs. |
| D7 | PASS | AI Use Declaration in both charts, both `main.c` (identical), `pc_test.c`, `pc_suite.c`, `pc_suite_print.h`, `analyse_logs.py`, `check_board_log.py`, `diff_A_B.py`, `run_versionA_sim.py`, `run_kieler_warning.py`, `make_submission.ps1`, `run_board.bat`, `board_test.v`. The KIELER-generated `.c/.h` carry none (regenerated files). |
| D8 | PASS | **[re-run on the final files, 19 Oct 18:15]** `VersionB/make_submission.ps1 -Group 14 -Sof -IncludeElf`: `group_14.zip`, **249 files**, 7.0 MB uncompressed, no ERROR/WARNING. Layout: `README.md`; `VersionA/TrafficLight_VersionA.sctx`; `VersionB/` (`TrafficLight_VersionB.sctx`, `run_board.bat`, `COMPSYS303_Lab1/` with `nios2_system.sopcinfo` (generation ID 1786080893), the board-tested `.sof` (SHA-256 D11CD8F5..., checked) and `software/traffic_b` (with `traffic_b.elf`) + `software/traffic_b_bsp` without build outputs); `docs/` (TASK3.md, TASK4.md); `evidence/` (README index, final_test_results.md, report_facts.md, board_logs/, versionA/, figures/, pc_suite/, scripts/, kieler_warning/). Extracted copy audited: every file identical to the repository, no `_to_delete`, `db`, `obj`, build outputs, stand-alone Task 1/2 charts or report PDF; `check_board_log.py` and `diff_A_B.py` pass when run inside it. Longest path: 93 characters. |
| D9 | PASS | Dry-run list contains no `db/`, `incremental_db/`, `.metadata/`, `obj/`, `Hello_lab1*`, `_to_delete/`, board_test outputs or `TASK3_EDGE_RESULTS.md`. |
| D10 | DONE | Report `COMPSYS303_Group14_Report.pdf` (6 pages, 12 pt, Table III agreed by Harold and Lucas), handed in separately on Canvas as the brief requires; every number is in `report_facts.md` with its source. |
| D11 | PENDING | Demonstration and interview in Week 12 (both members). |
| D12 | PASS | Pushed to `origin` (github.com/Wing-Hin/compsys303); see the last push in the git log. |

## Known limitations found while testing

* The microsecond stopwatch (timer_1, 32-bit at 50 MHz) wraps every 85.9 s, so a **single** phase longer
  than that (a Task 3 hold) is reported 85.9 s short in the console; its timer-event count is correct.
* The JTAG UART output is buffered by the HAL (about 2 KB); with no console attached for longer than
  that, output is lost or `printf` can briefly delay the loop.
* The time-limited (OpenCore Plus) `.sof` stops the Nios II if the JTAG tether is interrupted (seen
  once at 00:13: Quartus Error 209059); re-configuring the `.sof` restores it.
* Task 3 values are 1..9999 ms (4 digits), so one phase can be configured to at most 9.999 s.
* Leaving a Task 3 hold, or a car arriving mid-yellow, happens between two timer events, so the first
  phase (or the camera dwell) afterwards is up to one timer period short (10 ms at 10 ms, 100 ms in E6).
* Task 3 bytes are read from RS-232 first, then from the JTAG console: send a packet on one port at a
  time (two packets arriving together would have their bytes mixed).

## Decision: Task 3 packet values in milliseconds (2026-10-19)

The brief gives the packet format `#,#,#,#,#,#[\r]\n` with `#` "a 1-4 digit integer time-out value" and says
it is the same format as the original hardware assignment; it gives no unit. The first design read the values as
**seconds**. That could not express the default 0.5 s all-red (the defaults could never be restored by a packet),
gave a meaningless range of up to 9999 s (2.8 h), and needed a `* 1000` conversion in Version B, whose time-outs are
integer milliseconds. Values are now **milliseconds** (1..9999): `6000,2000,500,6000,2000,500` restores the defaults
exactly (C3.9), Version B uses the values unchanged, Version A divides by `MS_PER_S = 1000.0`. Both versions accept
the same packets (B2). Old seconds-format evidence was moved to `VersionB/_to_delete/`.

## Finding: two Task 3 packets in one all-red (C3.8)

During an all-red the chart re-checks the mailbox every tick (`RR1Wait -> RR1Select -> RR1Config`). With two
packets back to back, the first is committed when the all-red starts, which frees the mailbox; the parser then
reads the second (about 30 ticks) and it is committed in the **same** all-red. The first packet's values are never
visible in a green. Nothing is lost: the second packet can only be read after the first is committed. This is
within the brief (values change only in R-R; the newest valid packet wins). A commit later in an all-red resets its
count (`c = 0`), so that all-red lasts longer than t3 (the safe direction): on the board 101 events instead of 100
(C3.8, line 48). No change made.

## Finding (fixed): Version A camera never took a snapshot (A10, A11)

* `TrafficLight_VersionA.sctx` (commit `9ceac57` added the `ArmedCheck` state for the Dynamic-mode wake-up).
  `ArmedCheck` has two immediate transitions to the **same** target (`NextCameraTick`), one guarded by the clock
  (`cameraClock >= CAMERA_DWELL`). KIELER's netlist code for it is
  `_g200 = ... || (_g203 && _cg205) || (_g203 && _cg205) || ...` - the fallback should be `(_g203 && !_cg205)`.
  While the clock is below 1 s the region therefore never re-enters `NextCameraTick`: the Camera region stops after
  'Camera activated', so no snapshot and no departure are ever seen.
* Fix (applied with approval): `ArmedCheck`'s fallback goes to a separate state `ArmedTick`, identical to
  `NextCameraTick`. The activation tick then requests sleepT = 1 and the snapshot comes exactly 1.0 s later
  (A10, A11); B2 treats ArmedCheck + ArmedTick as the documented A-only block.

## Finding (fixed): Version A Task 3 commit tick requested no wake-up (A8)

On the tick that applied a valid packet the commit went straight to `RRnWait`, so no clock guard was evaluated and
the chart left sleepT at KIELER's no-deadline value 1000 s: in pure Dynamic mode the new all-red ended only when some
other tick happened. **Fixed (2026-10-19):** the commit now goes to `RRnExit`, whose guard `!waitingConfig && c >= t3`
(t6) is false on that tick (c = 0 and every value is at least 1 ms, so the all-red stays visible) and requests the
wake-up t3 later. A8 now passes in strict Dynamic mode (sleepT = 1 s on the commit tick, all-red exactly 1.0 s).
Version B got the identical change (B2); its behaviour is unchanged (PC suite 30/30, C3 on the board). The generated
code of the new two-transition `RRnConfig` was checked for the camera-style guard bug (B5).
