# COMPSYS303: final tasks and test plan (for Claude Code)

**Purpose:** finish everything left before submission, and prove with tests that Version A (simulator) and Version B (DE2-115) meet every requirement in the brief. Work through **Part I** in order. **Part II** is the test plan that Part I refers to by test ID.

Record every result in `VersionB\evidence\final_test_results.md` under the test IDs: PASS / FAIL / PENDING / N/A, plus the evidence file or log line.

## Ground rules

- Never change chart logic (any `.sctx` state, transition or guard) or `main.c` behaviour without showing me the diff and getting my OK. For header- or comment-only edits, show the diff, then apply them.
- When a step needs a physical action (switch, key, cable, lab PC), stop, tell me exactly what to do, and wait.
- Don't delete files. Move anything obsolete into `VersionB\_to_delete\` and list what you moved.
- Commit after each part that changes the repo (message `Final: <part>`). Don't push until Part 9.
- Keep the board tethered (original Lab 1 `.sof`) unless a step says otherwise. Don't use the USB-Blaster from any other program meanwhile.
- If a test fails, stop and show me the failing case, the evidence and your diagnosis. Don't edit the design to make a test pass without my OK; the expectation may be the thing that's wrong, so say which you think it is.

---

# Part I: tasks

## Part 1: repo completeness (auto)
1. Commit `VersionB\COMPSYS303_Lab1\nios2_system.qsys` and `nios2_system.sopcinfo`. Also commit `COMPSYS303_Lab1.qpf`, `.qsf`, `.bdf` and `DE2_115_pin_assignments.csv` if they aren't tracked yet. Check that `.gitignore` doesn't exclude anything needed to rebuild.
2. Confirm `VersionB\nios\main.c` and `software\traffic_b\main.c` are byte-identical.

## Part 2: AI declarations (tests D7, A12)
1. List every submitted source file (6 `.sctx`, `main.c`, `pc_test.c`, every `.py` and `.c` script) and print each one's current AI-use declaration, or "MISSING".
2. Propose wording for each file in this form: *"AI Use Declaration: The design and all design decisions were made by Harold and Lucas. \<file-specific: which parts were written with AI assistance, naming every tool used: Claude (Anthropic) and/or OpenAI Codex\>, then reviewed, tested and verified by Harold and Lucas."* Note that `TASK3.md` and `TASK4.md` say Tasks 3–4 of the Version A combined chart were done with OpenAI Codex, but that header currently mentions only Claude.
3. Wait for my approval, then apply. Comments only.

## Part 3: static checks (auto): tests B1–B7
Run B1–B7.
- For B2, write `VersionB\evidence\diff_A_B.py`. It should normalise the expected timing differences and print any remaining structural differences. The only expected one is `ArmedCheck`.
- For B5, regenerate `TrafficLight_B.c/.h` from the committed chart and confirm the `pc_test` output matches the committed version.

## Part 4: log checker (auto): test T0
Write `VersionB\evidence\check_board_log.py` (standard library only, with an AI declaration) using the rules in Part II §0. Run it on every `evidence\B_*.txt` log and report any violations.

## Part 5: PC scripted suite (auto): test B8, cases S1–S29
Write `VersionB\nios\pc_suite.c`. It should drive the generated `TrafficLight_B` code with scripted inputs, exactly as `main.c` would:
- a timer event every 7 ticks;
- button presses that last several ticks;
- UART characters fed one per tick, and only when `configReady` was true after the previous tick.

Implement every case S1–S29 as a named test with asserts, and print PASS/FAIL per case plus a total. Build it with gcc and run it.

## Part 6: board tests (needs me): tests in Part II §C
Run every C-row that isn't already marked *done*. Log each one to `evidence\B_C<section>_*.txt` and run `check_board_log.py` on it. Before each test, confirm the switch state by JTAG.
- **C3 (UART):** first ask me whether an RS-232 or USB-serial cable is connected. If yes, find the COM port and use pyserial at 115200 8N1 for C3.2–C3.8. If no, mark C3.2–C3.8 *PENDING – needs cable* and carry on.
- **C5.3:** start the 15-minute unattended run and do other parts while it runs.

## Part 7: fresh-clone build (auto, then me): tests D4–D5
1. `git clone` the repo (a local path is fine) into `%TEMP%\cs303_fresh`.
2. In the clone, using only the Nios II command-line tools: run `nios2-bsp-generate-files` from `traffic_b_bsp\settings.bsp`, `make` the BSP, then `make` traffic_b. It must build with **no manual edits**. Report every edit you would have needed (absolute paths, missing files and so on). Fix each one in the repo, not the clone, commit, and re-clone until it builds clean.
3. Ask me before downloading the fresh `.elf` to the board (D5), then check Task 1 runs.

## Part 8: submission package (auto, except the .pof)
1. **Top-level `README.md`** for the zip. It should include:
   - group members and what each folder is;
   - how to run Version A (KIELER, Dynamic mode) and Version B (program the `.sof`/`.pof`, build, download);
   - the board mapping: SW1..0 select the task, KEY0 NS walk, KEY1 EW walk, KEY2 vehicle, KEY3 reset, the LEDR bits, RS-232 at 115200 8N1 with the packet format, and the JTAG console;
   - "Version A = simulator, Version B = board";
   - known limitations: the time-limited `.sof` needs the tether, JTAG `printf` may block with no console attached, and Task 3 values are integer seconds.
2. **`VersionB\make_submission.ps1`**, which builds `group_N.zip` (ask me for N).
   - Include **only:** the 6 `.sctx`; the `traffic_b` and `traffic_b_bsp` sources, settings and Makefiles (no `obj/`; the `.elf` is optional); `nios2_system.sopcinfo`; the `.pof` (fail loudly if it's missing); `README.md`; and `evidence\` (the A `.ktrace` files and `check_ktrace.py`, the B logs, `B_summary.md`, `final_test_results.md`, `figures\` and the scripts).
   - Exclude `db/`, `incremental_db/`, `.metadata/`, `Hello_lab1*`, `_to_delete\`, the board_test outputs and `TASK3_EDGE_RESULTS.md`.
   - Run it in dry-run mode and show me the file list and total size.
3. The `.pof` can't be made from the time-limited `.sof`. Give me the exact lab-PC steps (open `COMPSYS303_Lab1.qpf` → full compile → File > Convert Programming Files → `.pof`, EPCS64, Active Serial) and tell me where to put the `.pof` so `make_submission.ps1` picks it up.

## Part 9: report evidence pack and wrap-up
1. **Figures** with matplotlib, in `evidence\figures\` (PNG, labelled axes, units):
   - (a) measured vs intended phase duration per experiment (E2a/E2b/E2c/E3/E4);
   - (b) phase error (ms) per phase at 1/10/100/300 ms;
   - (c) ticks per timer event and the share of idle ticks;
   - (d) E6 camera dwell, armed at yellow start vs entered during yellow, with the 900–1000 ms band;
   - (e) Version A (from the Part 1 `.ktrace` evidence) vs Version B phase errors, side by side.
2. **`evidence\report_facts.md`:** every number the report needs, each with the file it came from. Facts and sources only, no prose.
3. **Final summary:** a table of every test ID with its status, what is still PENDING and why, and the commits made. Then ask me before `git push`.

---

# Part II: test plan

**Priority:** **M** = must pass before submitting · **S** = should · **N** = nice to have. Rows marked *(done)* already passed on 18–19 Oct; re-check them only with the log checker.

## 0. Pass criteria shared by every board test

**Allowed LEDR values:** 33 (G-R), 34 (Y-R), 36 (R-R), 12 (R-G), 20 (R-Y), 97 (G-R + NS walk), 140 (R-G + EW walk). Any other value is a FAIL.

**Allowed LEDR changes** (anything else is a FAIL):

```
33 -> 34 | 97      97 -> 33 | 34      34 -> 36      36 -> 12 | 140 | 33 | 97
12 -> 20 | 140     140 -> 12 | 20     20 -> 36
```

The changes 36→140 and 36→97 are legal: when a pending request exists, the green state and its walk start in the same tick. The change 97→34 is legal only when a Task 3 configuration made the green shorter than the walk.

**Safety:** neither direction is ever green or yellow while the other is green or yellow. This follows from the allowed set; check it anyway.

**T0 (auto, M): log checker.** Have Claude Code write `evidence/check_board_log.py` (standard library only, with an AI-use declaration). It should parse every `B_*.txt` log and fail on any illegal value or change, and on any phase whose event count ≠ ⌈T / TIMER_MS⌉. Phases ended by a mode change or a configuration commit are exempt from the count check. Run it on every log in this plan.

---

## A. Version A: simulator regression (KIELER)

Use your existing traces where they already cover a test. Only re-run what changed or was never tested.

| ID | P | Test | Expected | Status |
|---|---|---|---|---|
| A1 | M | Compile `Task1_VersionA`, `Task2_VersionA`, `TrafficLight_VersionA` | No errors; only the known instantaneous-loop warnings | |
| A2 | M | Task 1 cycle, Dynamic mode, ≥ 2 cycles | 33,34,36,12,20,36 with 6 / 2 / 0.5 / 6 / 2 / 0.5 s | |
| A3 | M | Task 2: NS press in R-G | Next G-R shows 97 for 4 s, then 33 | |
| A4 | M | Task 2: EW press in G-R | Next R-G shows 140 for 4 s | |
| A5 | S | Task 2: press during its own green | Served in the next cycle, not the current one | |
| A6 | M | Combined: task change mid-green | `activeTask` changes only at R-R | |
| A7 | M | Combined: request retained across 2→1→2 | Walk still served when Task 2 returns (the bug found in the Part 1 audit) | |
| A8 | M | Task 3: valid packet `8,3,1,8,3,1⏎` | Applied at the next R-R; phases 8/3/1/8/3/1 s | |
| A9 | M | Task 3: invalid packet `1,2,3⏎` | `configRejected`+1; lights stay red | |
| A10 | M | Task 4: car present at yellow | "Camera activated", then "Snapshot taken" after 1 s | |
| A11 | M | Task 4: car leaves before 1 s | "Vehicle left", no snapshot | |
| A12 | M | AI declaration in all 3 Version A headers names **every** tool used (Claude **and** Codex) | Present and accurate | |

---

## B. Version B: static checks (PC, auto)

| ID | P | Test | Expected | Status |
|---|---|---|---|---|
| B1 | M | `TrafficLight_VersionB.sctx` lint | No `clock`, `float`, `deltaT` or `@ClocksUseSD`; all `go to` targets exist | |
| B2 | M | A ↔ B structural diff (normalise timing syntax, then diff) | Only timing lines and the documented `ArmedCheck` difference | |
| B3 | M | KIELER netlist-C compile of the **committed** chart | Same warnings as before, no errors | |
| B4 | M | Generated `TickData` vs `main.c` | Every field `main.c` uses exists; no `double` | |
| B5 | M | The `TrafficLight_B.c/.h` in `traffic_b` were generated from the committed chart | Regenerate and confirm behaviour matches (statement order may differ; compare `pc_test` output) | |
| B6 | M | `pc_test` (Task 1) | 600/200/50/600/200/50 events per phase | |
| B7 | S | `main.c` constants | `CHART 4`, `TIMER_PERIOD_MS 10`, chart `TIMER_MS = 10` | |

### B8 (auto, S): scripted PC test suite

Have Claude Code write `VersionB/nios/pc_suite.c`. It drives every chart input on a scripted timeline: a timer event every 7 ticks, and button "presses" lasting a few ticks. The generated chart code then runs these scenarios **with no board and no human**, and each case asserts its expected output. This catches logic errors before the demo.

| Case | Script | Assert |
|---|---|---|
| S1 | Task 1, 5 cycles | Legal sequence; exact event counts |
| S2 | Task 2, NS press during R-G | 97 for exactly 400 events at the next G-R |
| S3 | Task 2, EW press during G-R | 140 for 400 events at the next R-G |
| S4 | Task 2, both pressed together | Both walks served, each in its own green |
| S5 | Task 2, button held for 3 s | Counted as one request, so one walk |
| S6 | Task 2, three NS presses before green | One walk (all served together) |
| S7 | Task 2, NS press during its own green | No walk now; walk in the next G-R |
| S8 | Task 2 press, switch to 1 at R-R, back to 2 | Walk still served (request retained) |
| S9 | Task change at every phase | `activeTask` only changes on a tick with LEDR 36 |
| S10 | `task` = 0, 5, 99 | Treated as "keep the current mode"; no crash |
| S11 | Task 3 valid packet `8,3,1,8,3,1\n` | Commit at R-R; then 800/300/100 events |
| S12 | CRLF packet `8,3,1,8,3,1\r\n` | Same as S11 |
| S13 | Invalid: `1,2,3\n`, `1,2,3,4,5,6,7\n`, `12345,1,1,1,1,1\n`, `1,,1,1,1,1\n`, `a,1,1,1,1,1\n` | Each rejected (`configRejected`+1); timings unchanged |
| S14 | Garbage followed by a valid packet | Recovers; the valid packet applies |
| S15 | Leading zeros `0008,03,1,8,3,1\n` | Accepted as 8,3,1,8,3,1 |
| S16 | Valid packet sent during green | Not applied until the next R-R |
| S17 | Packet sent before entering Task 3 | Applied at the first R-R in Task 3 |
| S18 | Re-enter Task 3 after a commit | Waits for a **new** packet |
| S19 | Second packet before the first is committed | `configReady` false blocks it; no overwrite |
| S20 | Task 4: car enters in green, stays | Activated at yellow; snapshot after exactly 100 events |
| S21 | Task 4: car enters during yellow | Snapshot after 100 events counted from arming (fewer than 100 × 10 ms of real time; the PC can't show that) |
| S22 | Task 4: car leaves before the snapshot | "Vehicle left", no snapshot |
| S23 | Task 4: leaves on the same tick as the deadline | No snapshot (departure is processed first) |
| S24 | Task 4: one visit across two yellows | Only one snapshot per visit |
| S25 | Task 4: leave, then re-enter | A second snapshot is possible |
| S26 | Car present while switching from Task 4 to Task 1 | Armed camera cancelled; no snapshot in Task 1 |
| S27 | `vehicleButton` held for 50 ticks | Counts as one press (edge-triggered) |
| S28 | 1 000 000 ticks with random inputs (fixed seed) | Never an illegal LEDR value or change (the T0 rules) |
| S29 | Ticks with no timer event only | Nothing advances; the lights never change |

---

## C. Version B: board tests (DE2-115)

Set-up: the board is tethered and the console is logged to a file. Before each test, confirm the switches with a live JTAG read, as you did when checking the inputs.

### C1 Task 1 timing

| ID | P | Test | Expected | Status |
|---|---|---|---|---|
| C1.1 | M | 10 ms, ≥ 3 cycles | Legal sequence; 600/200/50 events; error < 1 ms *(done: `B_task1_10ms.txt`)* | |
| C1.2 | S | E2/E3/E4 rate experiments | *(done: `B_E2_*`, `B_E3`, `B_E4`)* | |
| C1.3 | M | `check_board_log.py` over every B log | No violations | |

### C2 Task 2 (SW = 01)

| ID | P | Test | Expected | Status |
|---|---|---|---|---|
| C2.1 | M | KEY0 in R-G | 97 for 400 events *(done)* | |
| C2.2 | M | KEY1 in G-R | 140 for 400 events *(done)* | |
| C2.3 | M | KEY0 + KEY1 together in R-R | Both walks, in successive greens | |
| C2.4 | S | KEY0 held for 3 s | One walk | |
| C2.5 | S | KEY0 pressed during G-R (its own green) | Walk in the **next** G-R | |
| C2.6 | M | KEY0 in R-G, set SW = 00 before R-R, then SW = 01 | Walk served once Task 2 returns | |

### C3 Task 3 (SW = 10, RS-232 cable, 115200 8N1)

| ID | P | Test | Expected | Status |
|---|---|---|---|---|
| C3.1 | M | Enter Task 3 | Holds at 36 *(done: held about 55 s)* | |
| C3.2 | M | Send `8,3,1,8,3,1\r\n` | Resumes; phases 8000/3000/1000 ms (800/300/100 events) | |
| C3.3 | M | Send `1,2,3\r\n` after re-entering Task 3 | Stays red (rejected) | |
| C3.4 | M | Then send a valid packet | Recovers and resumes | |
| C3.5 | S | Send `2,1,1,2,1,1\n` (LF only) during green | Applied at the next R-R, not immediately | |
| C3.6 | S | Send `12345,1,1,1,1,1\n` | Rejected | |
| C3.7 | M | Switch to SW = 00 while waiting in Task 3 | Leaves the red hold; normal cycle with the last committed timings | |
| C3.8 | S | Send the same packet twice quickly | Both handled; nothing lost or corrupted | |

### C4 Task 4 (SW = 11)

| ID | P | Test | Expected | Status |
|---|---|---|---|---|
| C4.1 | M | Car in during green, wait for yellow | Activated, then snapshot at about 1000 ms *(done)* | |
| C4.2 | M | KEY2 again | "Vehicle left" *(done)* | |
| C4.3 | M | Enter and leave within the dwell | No snapshot *(done)* | |
| C4.4 | S | Enter during yellow, at 100 ms | 900–1000 ms *(done: E6)* | |
| C4.5 | S | Car stays through two yellows | Only one snapshot | |
| C4.6 | M | Car present, switch to SW = 00 | No camera messages in Task 1 | |
| C4.7 | M | Pedestrian buttons in Task 4 | Walks still work (Task 4 includes pedestrians) | |

### C5 Mode switching and robustness

| ID | P | Test | Expected | Status |
|---|---|---|---|---|
| C5.1 | M | Every switch change 1↔2↔3↔4, made mid-green | Takes effect only at LEDR 36; legal sequence throughout | |
| C5.2 | M | KEY3 (reset) mid-cycle | Restarts cleanly at G-R | |
| C5.3 | M | Run for 15 min unattended | No freeze; timestamps still sensible after 85.9 s (the timer_1 fix) | |
| C5.4 | S | Hammer KEY0–KEY2 for 30 s | No crash; only legal LEDR values | |
| C5.5 | N | Console closed while running | Note the result (JTAG `printf` may block). Document it as a limitation, not a bug | |

---

## D. Submission readiness (M unless marked)

| ID | Test | Expected | Status |
|---|---|---|---|
| D1 | Full-licence compile of `COMPSYS303_Lab1.qpf` on a lab PC | `COMPSYS303_Lab1.sof` with **no** `_time_limited` suffix | |
| D2 | `.pof` generated (EPCS64, Active Serial) | File exists; optionally program the flash, power-cycle and check the design loads | |
| D3 | `.sopcinfo` in the zip is the same build as the `.sof`/`.pof` | Same generation timestamp | |
| D4 | **Fresh-clone build**: clone the repo to a new folder, import the projects, Generate BSP, build `traffic_b` | Builds with no edits; proves the zip is self-contained | |
| D5 | Fresh-clone run | The `.elf` from D4 runs Task 1 correctly on the board | |
| D6 | README states SW1..0 = task, KEY0/1/2, KEY3 = reset, UART settings, and "Version A = simulator, Version B = board" | Present | |
| D7 | AI declaration in every submitted source: 6 `.sctx`, `main.c`, `pc_test.c`, any scripts | Present and accurate (every tool named) | |
| D8 | Zip `group_N.zip` contains: 6 `.sctx`; `traffic_b` + `traffic_b_bsp` (no `obj/`, `*.elf` optional); `.pof`; `.sopcinfo`; README; evidence (A `.ktrace`, B logs, `B_summary.md`) | Checklist ticked | |
| D9 | No stray files in the zip: `db/`, `incremental_db/`, `.metadata/`, `TASK3_EDGE_RESULTS.md`, debug folders | Clean | |
| D10 | Report PDF: designs, both timing mechanisms, Section 4 (all 5 points, with evidence), difficulties, future work, hours table, workload table (Member 1 / Member 2) | All sections present; about 5 pages | |
| D11 | Interview preparation: both members can explain the per-state counting, the RR-Wait counting, `pre()` handshakes, the timer ISR + queue, and the A-vs-B results | Rehearsed | |
| D12 | Push to the remote | Off-laptop backup exists | |

---

## Minimum before submitting

At least: **all M rows in B and C, C3.2–C3.4 (needs the cable), D1–D10.** If you are short of time, the S-cases in B8 run without the board and catch logic regressions fastest.
