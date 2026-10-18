# Report facts (Version B) - numbers and their sources

All times measured on the DE2-115 with timer_1 (50 MHz timestamp) unless noted. Paths relative to
`VersionB/evidence/`. Regenerate the derived files with `analyse_logs.py` and `export_figure_data.py`.

## Platform and build

| Fact | Value | Source |
|---|---|---|
| FPGA / CPU | Cyclone IV E EP4CE115F29C7, Nios II/f at 50 MHz, program in SDRAM | `../COMPSYS303_Lab1/nios2_system.sopcinfo`, `../COMPSYS303_Lab1/software/traffic_b_bsp/system.h` |
| Timer event source | timer_0 (HAL system clock, 1 ms tick), `alt_alarm` every `TIMER_PERIOD_MS` | `../COMPSYS303_Lab1/software/traffic_b/main.c` |
| Stopwatch | timer_1 timestamp, 32-bit at 50 MHz, wraps every 85.9 s (CONT bit set in `main.c`) | `main.c`, `B_C3_task3_exit.txt` line 12 |
| ELF size | text 92408 B, data 7388 B, bss 388 B (about 96 KB) | `final_test_results.md` D4 |
| Build warnings | 0 (BSP and app, also from a fresh clone) | `final_test_results.md` D4 |
| KIELER compile of the Version B chart | 0 errors, 1 warning "Instantaneous loop detected!" | `final_test_results.md` B3 |
| Version A vs B structure | 8 time constants equal (A s x 1000 = B ms); only difference the 5-line `ArmedCheck` state | `diff_A_B.py`, `final_test_results.md` B2 |

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
| Task 3 UART packets on the board | not tested - no RS-232 / USB-serial cable | `final_test_results.md` C3 |

## Verification

| Fact | Value | Source |
|---|---|---|
| PC scripted suite | 29 / 29 cases pass | `pc_suite_results.txt`, `../nios/pc_suite.c` |
| Random run (S28) | 1,000,000 ticks: 437 LEDR changes, 90 commits, 66 rejects, 13 snapshots, 0 rule violations | `pc_suite_results.txt` |
| 0-second time-outs (X1, extra) | 17 rule violations: yellow / all-red skipped (e.g. `140 -> 36`, `33 -> 140`) | `pc_suite_results.txt`, `final_test_results.md` |
| Board-log checker (T0) | all 20 raw `B_*.txt` logs, 1854 phases: 0 violations | `check_board_log.py` output, `final_test_results.md` T0 |
| Fresh-clone build | builds with no manual edits; same ELF section sizes | `final_test_results.md` D4 |
| Board inputs | board-only test passed; live JTAG trace: SW0 -> 0x00001, SW17 -> 0x20000, KEY0 -> keys 0x6 (original image) | `board_input_test.txt` |
| Test status | per test ID | `final_test_results.md` |
