# Evidence (Group 14)

Evidence for the Version A versus Version B comparison of brief Section 4, plus the test records.
Version A was run in KIELER's own simulator; Version B was measured on the DE2-115.

| Folder / file | What it is |
|---|---|
| `versionA/` | **Version A simulator traces.** `A_results.txt` (13 tests, all PASS), one JSON trace per test (`trace_*.jsonl`: every tick's time, `deltaT`, inputs, outputs, messages), `A2_realtime_phases.csv`, and the driver `run_versionA_sim.py`, which builds KIELER's *Netlist-based Simulation (C)* from `VersionA/TrafficLight_VersionA.sctx` and steps it in Dynamic mode |
| `board_logs/` | **Version B board results.** Raw `nios2-terminal` logs `B_*.txt` (every light change with its measured duration, loop ticks and timer events) and `B_summary.md`, the statistics generated from them |
| `figures/` | The report figures (a)-(e), their data (`phases.csv`, `dwell.csv`) and `make_figures.m` |
| `pc_suite/` | 30 scripted test cases running the generated Version B code on a PC (`pc_suite.c`, results `pc_suite_results.txt`) |
| `scripts/` | `check_board_log.py` (checks every board log against the safety and timing rules), `analyse_logs.py` (writes `B_summary.md`), `export_figure_data.py`, `diff_A_B.py` (Version A and B charts identical apart from timing) |
| `kieler_warning/` | Why KIELER prints "Instantaneous loop detected!" for both charts although every loop has a delayed transition |
| `final_test_results.md` | Every test ID with its status and evidence |
| `report_facts.md` | Every number in the report with the file it comes from |

## Section 4 points and where the evidence is

| Section 4 point | Version A | Version B |
|---|---|---|
| 1. Correctness and equivalence | `versionA/A_results.txt` A2-A11 | `board_logs/B_task1_10ms.txt`, `B_C2_task2.txt`, `B_C4_task4.txt`; `scripts/diff_A_B.py` (same structure) |
| 2. Timing accuracy and jitter | A2 (real-time stepping), A14 (exact in simulated time) | `B_summary.md`; timer rate: `B_E2_1ms.txt`, `B_task1_10ms.txt`, `B_E2_100ms.txt`, `B_E3_300ms.txt`, `B_E4_rescale.txt`; alignment: `B_E6_camera_100ms*.txt`; `figures/` (a), (b), (e) |
| 3. Computational effort | A14, A15 (reactions in strict Dynamic mode) | ticks and timer events per phase in every log; `figures/` (c) |
| 4. Modelling clarity | the two charts (`VersionA/`, `VersionB/`), `scripts/diff_A_B.py` | |
| 5. Reconfiguration (Task 3) | A8, A9, A13 | `B_C3_jtag_packets.txt`, `B_C3_task3_exit.txt`; `pc_suite/` S11-S19, S30 |

## Board logs

| Log | Content |
|---|---|
| `B_task1_10ms.txt` | Task 1 baseline at 10 ms (63 phases) |
| `B_E2_1ms.txt`, `B_E2_100ms.txt`, `B_E3_300ms.txt` | the same at 1, 100 and 300 ms timer periods |
| `B_E4_rescale.txt` | chart 10 ms, `main.c` 20 ms: every phase doubles |
| `B_E6_camera_100ms.txt`, `B_E6_camera_100ms_yellow.txt` | camera dwell at 100 ms, armed at yellow start / car arriving during yellow |
| `B_C2_task2.txt` | Task 2 pedestrian cases |
| `B_C3_jtag_packets.txt`, `B_C3_task3_exit.txt` | Task 3 packets (milliseconds) over the JTAG console; Task 3 hold and exit |
| `B_C4_task4.txt` | Task 4 camera cases |
| `B_C5_modes.txt`, `B_C5_15min.txt`, `B_C5_console.txt` | mode changes and random presses, 15 minutes unattended, console detached |
| `B_D5_fresh_clone.txt` | the program built from a fresh clone |
| `B_R1_tasks124_current_build.txt` | Tasks 1, 2 and 4 re-run on the final build |
| `B_functional_*.txt`, `B_restored_*.txt`, `board_input_test.txt` | earlier functional checks, defaults restored after the experiments, board input check |

**Which build:** the Task 3 logs (`B_C3_*`) and `B_R1_*` were recorded with the final program; the other
logs with earlier builds, which differed only in Task 3 input handling (packet units, rejection of 0, the
commit target, and reading packets from the JTAG console as well as RS-232). The E2-E4 and E6 logs
deliberately use other timer periods (named in each log's header). Every log used the same board-tested
`.sof`.

## Re-running the checks

From the zip root, with Python 3 (and gcc for the PC suite, Java and the KIELER VS Code extension for
the simulation):

```
python evidence/scripts/check_board_log.py         # all board logs: 0 violations
python evidence/scripts/diff_A_B.py                # Version A vs B: PASS
python evidence/versionA/run_versionA_sim.py       # 13 Version A tests (A2 runs in real time)
```

The PC suite build commands are at the top of `pc_suite/pc_suite.c`.

`versionA/A_results.txt` and its traces are the run used in the report and in figure (e); its header
names the chart's location before it was moved to `VersionA/` for the submission. A re-run on the final
files gives the same 13/13 results; only A2, which runs on the PC's real-time clock, varies slightly
from run to run (+0.1 to +0.5 ms on the re-run, +0.2 to +0.6 ms in the committed run).

AI Use Declaration: Harold and Lucas designed the tests and made all design decisions. They
discussed the structure of the code with Claude (Anthropic), which helped write parts of this index
and the scripts listed here; Harold and Lucas reviewed, tested and verified all of it.
