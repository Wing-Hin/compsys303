# Report facts (Version B) - numbers and their sources

All times measured on the DE2-115 with timer_1 (50 MHz timestamp) unless noted. Paths relative to
`evidence/`; board logs `B_*.txt` and `B_summary.md` are in `board_logs/`, the PC suite in `pc_suite/`.
Regenerate the derived files with `scripts/analyse_logs.py` and `scripts/export_figure_data.py`.

## Platform and build

| Fact | Value | Source |
|---|---|---|
| FPGA / CPU | Cyclone IV E EP4CE115F29C7, Nios II/f at 50 MHz, program in SDRAM | `../VersionB/COMPSYS303_Lab1/nios2_system.sopcinfo`, `../VersionB/COMPSYS303_Lab1/software/traffic_b_bsp/system.h` |
| Timer event source | timer_0 (HAL system clock, 1 ms tick), `alt_alarm` every `TIMER_PERIOD_MS` | `../VersionB/COMPSYS303_Lab1/software/traffic_b/main.c` |
| Program storage | Reset vector in SDRAM (0x00800000); program about 98 KB; on-chip RAM 30 KB (30720 B); no EPCS flash controller in the Qsys system. So the `.pof` holds only the FPGA hardware and the `.elf` is downloaded over JTAG after power-up | `../VersionB/COMPSYS303_Lab1/software/traffic_b_bsp/system.h` (ALT_CPU_RESET_ADDR, ONCHIP_MEM_SPAN), `nios2-download` output |
| Stopwatch | timer_1 timestamp, 32-bit at 50 MHz, wraps every 85.9 s (CONT bit set in `main.c`) | `main.c`, `B_C3_task3_exit.txt` line 12 |
| ELF size | text 91988 B, data 7388 B, bss 388 B (about 98 KB), current build (Task 3 in ms, JTAG-console packet input); 0 build warnings | `nios2-elf-size traffic_b.elf` |
| Build warnings | 0 (BSP and app, also from a fresh clone) | `final_test_results.md` D4 |
| KIELER compile, both charts | 0 errors; "Instantaneous loop detected!" for every chart (plus clock `...SD` VariableStore notes in Version A). Caused by KIELER's expansion of during actions (B) and clocks (A): a delayed loop without them compiles silently, a real all-immediate loop is an error with no code | `kieler_warning/results.txt`, `final_test_results.md` A1, B3, B11 |
| Version A vs B structure | the A/B pair (Tasks 1-4 combined): time constants equal (A s x 1000 = B ms), normalised charts identical; only difference the 6-line `ArmedCheck`/`ArmedTick` camera wake-up block in the combined A chart | `diff_A_B.py`, `final_test_results.md` B2 |

## Task 1 timing at the default 10 ms (E2b)

| Fact | Value | Source |
|---|---|---|
| Events per phase | 600 / 200 / 50 / 600 / 200 / 50, every phase | `B_task1_10ms.txt`, `figures/phases.csv` |
| Mean measured G-R / Y-R / R-R (NS) | 6000.082 / 1999.954 / 500.078 ms | `figures/phases.csv` (E2b) |
| Mean measured R-G / R-Y / R-R (EW) | 6000.021 / 1999.900 / 500.010 ms | `figures/phases.csv` (E2b) |
| Worst mean error | 0.100 ms (R-Y) | `figures/phases.csv` |
| Largest jitter (max - min) | 0.754 ms (G-R) | `B_summary.md` |
| Phases measured | 63 | `B_summary.md` |

## Timer-rate experiments

| Experiment | Phases (ms) | Worst mean error | Largest jitter | Ticks per event | Ticks without an event | Source |
|---|---|---|---|---|---|---|
| E2a, 1 ms | 6000 / 2000 / 500 | 0.129 ms | 1.194 ms | 2.14 | 53.24 % | `B_E2_1ms.txt` |
| E2b, 10 ms | 6000 / 2000 / 500 | 0.100 ms | 0.754 ms | 21.81 | 95.41 % | `B_task1_10ms.txt` |
| E2c, 100 ms | 6000 / 2000 / 500 | 0.193 ms | 0.810 ms | 219.40 | 99.54 % | `B_E2_100ms.txt` |
| E3, 300 ms | 6000 / **2100** / **600** | 0.221 ms | 0.531 ms | 658.27 | 99.85 % | `B_E3_300ms.txt` |
| E4, chart 10 / main.c 20 ms | **12000 / 4000 / 1000** | 0.296 ms | 0.335 ms | 43.64 | 97.71 % | `B_E4_rescale.txt` |

| Fact | Value | Source |
|---|---|---|
| E3 quantisation | T2 2000 -> 7 events x 300 = 2100 ms; T3 500 -> 2 x 300 = 600 ms; T1 6000 -> 20 x 300 = 6000 ms | `B_E3_300ms.txt` |
| E4 rescale | only `TIMER_PERIOD_MS` changed: every phase doubles, event counts unchanged (600/200/50) | `B_E4_rescale.txt` |
| Main-loop rate | 2138-2194 ticks/s, independent of the timer period | `B_summary.md` ("All phases" lines) |
| All figures | (a)-(d) | `figures/*.png`, data `figures/phases.csv`, `figures/dwell.csv` |

## Pedestrians, camera, configuration

| Fact | Value | Source |
|---|---|---|
| Walk duration | 400 events, measured 3999.73-4000.36 ms | `B_functional_retest.txt`, `B_C2_task2.txt`, `B_C4_task4.txt` |
| Green remainder after a walk | 200 events (2000 ms) | same files |
| Camera dwell, car present at yellow start, 10 ms | 999.207, 999.321, 998.947, 999.474 ms | `B_functional_retest_task4.txt`, `B_C4_task4.txt`, `B_C5_modes.txt` |
| E6 (i) dwell armed at yellow start, 100 ms | 999.074, 999.294, 999.309, 999.226 ms (10 events) | `B_E6_camera_100ms.txt`, `figures/dwell.csv` |
| E6 (ii) dwell, car entered during yellow, 100 ms | 959.501, 943.968, 936.105 ms (band 900-1000) | `B_E6_camera_100ms_yellow.txt`, `figures/dwell.csv` |
| Dwell measured about 0.8 ms short | `main.c` prints the LEDR line before starting the dwell stopwatch | `B_E6_camera_100ms.txt` |
| Task 3 hold | held 131 s (13097 events; the console prints 45.07 s because the stopwatch wraps at 85.9 s), then resumed at once on SW 00 | `B_C3_task3_exit.txt` line 12 |
| First green after leaving a hold | 5997.2 ms (600 events; the exit falls between two timer events) | `B_C3_task3_exit.txt` |
| Task 3 packet format | six values in **milliseconds** 1..9999, a 0 field is invalid; same packets in A and B (decision with reasons in `final_test_results.md`) | `final_test_results.md` decision |
| Task 3 packets on the board | sent over the JTAG UART console (USB-Blaster cable, no RS-232 adapter); C3.2-C3.6, C3.8-C3.11 pass on the current build | `B_C3_jtag_packets.txt`, `final_test_results.md` C3 |
| Valid packet from a hold | `8000,3000,1000,8000,3000,1000` -> hold ends, then 800 / 300 / 100 events, 7999.821 / 2999.857 / 1000.154 ms | `B_C3_jtag_packets.txt` lines 14-21 |
| Packet during green | sent 2 s into the EW green: that green and its yellow keep 800 / 300, commit in the next R-R, then 200 / 100 / 100 | `B_C3_jtag_packets.txt` lines 22-29 |
| Invalid packets | `1,2,3`, two packets with a 0 field, and `12345,1,1,1,1,1` rejected; lights still held / unchanged; parser recovers | `B_C3_jtag_packets.txt` lines 12-15, 30-43 |
| Defaults by packet | `6000,2000,500,6000,2000,500` -> exactly 600 / 200 / 50 events (500.317 ms all-red) | `B_C3_jtag_packets.txt` lines 58-70 |
| Quantisation of odd values (B) | `1234,567,89,4321,765,98` -> 124 / 57 / 9 / 433 / 77 / 10 events = ceil(T / 10 ms); 1240.059 / 569.638 / 90.389 / 4329.627 / 770.076 / 100.176 ms | `B_C3_jtag_packets.txt` lines 71-79 |
| Two packets back to back | both committed in the same all-red; the second commit came just after the first timer event and restarted the count: all-red 101 events instead of 100 (safe direction); first packet never visible | `B_C3_jtag_packets.txt` line 48, `final_test_results.md` finding |
| Tasks 1, 2, 4 on the current build (R1) | Task 1 600/200/50; NS and EW walks 400 events then 200; snapshot after 999.327 ms, one per visit; leaving within 1 s: no snapshot | `B_R1_tasks124_current_build.txt`, `final_test_results.md` R1 |

## Future work

| Item | Reason | Source |
|---|---|---|
| Boot the software from flash (EPCS controller + boot copier) | the board currently needs `nios2-download` after power-up | `../VersionB/COMPSYS303_Lab1/nios2_system.qsys` (no EPCS controller), `system.h` |

## Verification

| Fact | Value | Source |
|---|---|---|
| PC scripted suites | combined chart 30 / 30 (`pc_suite.c`) | `pc_suite_results.txt` |
| Random run (S28) | 1,000,000 ticks: 537 LEDR changes, 92 commits, 70 rejects, 14 snapshots, 0 rule violations | `pc_suite_results.txt` |
| 0 time-outs | earlier parser accepted 0: 17 rule violations in a random run (yellow / all-red skipped, e.g. `33 -> 140`); now rejected: S30 random run with 0 fields, 216 rejects, 0 violations | `pc_suite_results.txt` S30, `final_test_results.md` finding |
| Board-log checker (T0) | all 22 raw `B_*.txt` logs, 2172 phases: 0 violations | `check_board_log.py` output, `final_test_results.md` T0 |
| Fresh-clone build | builds with no manual edits; same ELF section sizes | `final_test_results.md` D4 |
| Board inputs | board-only test passed; live JTAG trace: SW0 -> 0x00001, SW17 -> 0x20000, KEY0 -> keys 0x6 (original image) | `board_input_test.txt` |
| Test status | per test ID | `final_test_results.md` |

## Version A (headless KIELER simulation)

| Fact | Value | Source |
|---|---|---|
| Simulator | KIELER's own *Netlist-based Simulation (C)* (`de.cau.cs.kieler.sccharts.simulation.netlist.c`), built from the committed chart | `versionA/run_versionA_sim.py` |
| A-tests | 13 / 13 pass (A2-A11, A13-A15) | `versionA/A_results.txt` |
| Reactions per Task 1 cycle | Version A (strict Dynamic): 6.1 per 17 s cycle (61 for 10 cycles); Version B at 10 ms: about 2,180 per second, 37,067-37,072 per Task 1 cycle (1,700 with a timer event), 95.4 % of them without a timer event | `versionA/A_results.txt` A14, `B_summary.md` |
| Reactions with Task 4 | Version A: 19 reactions for about 2 cycles with a car and a snapshot (2 clocks, 4 button ticks) | `versionA/A_results.txt` A15 |
| Camera bug found by A10/A11 | ArmedCheck's two transitions to one target compiled to one guard; fixed with a separate ArmedTick target | `final_test_results.md`, finding |
| Version A phase error, real-time Dynamic stepping on the PC | +0.15 .. +0.64 ms over 12 phases (always late: the host wakes after the deadline) | `versionA/A2_realtime_phases.csv`, `figures/e_versionA_vs_versionB.png` |
| Version B phase error at 10 ms | about -0.3 .. +0.4 ms, centred on 0 | `figures/phases.csv` (E2b) |
| Camera dwell in Version A | exactly 1.0 s in simulated time | `final_test_results.md` A10 |
| Task 3 commit tick wake-up | fixed: the commit tick requests sleepT = t3 (1 s in A8); the all-red ends exactly 1.0 s later in strict Dynamic mode (before: sleepT = 1000 = no wake-up) | `versionA/trace_A8_A9_A13_task3.jsonl`, `final_test_results.md` finding |
