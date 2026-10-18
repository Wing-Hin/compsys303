# Version B (Tasks 1–4): step-by-step guide

Version B is the same controller as Version A with a different notion of time. The chart has no clocks. A Nios II interval timer raises an interrupt every `TIMER_MS` milliseconds, `main.c` turns each interrupt into one `timerTick` input, and each timed state counts those events. Everything else (states, LED words, regions, request handling, parser, camera logic) is copied from Version A unchanged. That is the point the brief makes in §2: "design the light-switching logic once; only the timing mechanism should differ".

> **Deadline check.** The course handout lists *Assignment 1 submission: 19 Oct 2026*. The brief says the exact dates are on Canvas. Check Canvas today. If the deadline really is tomorrow, follow the critical path: Steps 1, 3, 4, 6, 7, 8, 10, then as much of Step 9 as time allows. Step 2 and Step 5 are useful but optional.

## Files in this folder

| File | What it is | Status |
|---|---|---|
| `Task1_VersionB.sctx` | Task 1 converted to Version B. Use it as the pattern for every other conversion | given (review it) |
| `nios/main.c` | Glue code: timer ISR → `timerTick`, keys/switches/UART → inputs, `LEDR` → red LEDs, evidence log | given (review it) |
| `nios/pc_test.c` | Runs the generated chart on your PC with a fake timer, before you touch the board | given |
| `Task2_VersionB.sctx` | Task 2 converted (Step 5) | you write |
| `TrafficLight_VersionB.sctx` | Tasks 1–4 combined, the chart you demo (Step 6) | given (review it; the Step 6 list is the diff against Version A) |

The given files carry an AI-use declaration. Keep it, and add one to the charts you write if you use AI help (the handout says undeclared AI code counts as misconduct).

---

## 0. The idea in two pictures

**Architecture (the reactive interface the brief asks for in §1.2):**

```
 Nios II interval timer (timer_0 = HAL system clock, 1 ms)
        |  alt_alarm fires every TIMER_PERIOD_MS
        v
  timer_isr():  pendingEvents++          <- the external timing reference
        |
        v                       main loop, runs as fast as it can
  +------------------------------------------------------------------+
  | 1 Sensor   timerTick = take ONE pending event (0 or 1)           |
  |            KEY0/KEY1/KEY2, SW1..SW0, one UART byte               |
  | 2 Control  tick(&d)          <- KIELER-generated SCChart code    |
  | 3 Plant    d.LEDR -> leds_red; log every LEDR change             |
  +------------------------------------------------------------------+
```

This is the SensorStage → ControllerStage → PlantStage skeleton of brief §1.3, with the loop iteration as the delayed edge.

**How one phase is timed (P = `TIMER_MS`, N = number of events needed):**

```
timer events   |       |       |       |       |       |
loop ticks     ||||||||||||||||||||||||||||||||||||||||||||  (hundreds per event)
c              0       1       2  ...  N-1     N -> leave on this tick
               ^ phase entered on an event tick (entry: c = 0)
```

The guard `c * TIMER_MS >= T` needs N = ⌈T / P⌉ events. So:

- a phase entered **on** an event tick (every normal light change) lasts exactly N · P,
- a phase or timer started **between** events (a button press, a UART commit, a vehicle arriving) lasts between (N − 1) · P and N · P, so it can end up to one period **early**,
- if P does not divide T, the time-out is rounded **up** to N · P.

That is the "quantisation error of up to one full tick period" of brief §1.2. It contrasts with your Version A evidence, where phases were always slightly late (+13 to +78 ms) and never early. Keep this in mind for the report.

---

## 1. Decisions to make first (yours, with the defaults the templates use)

Talk these through with Lucas. The templates use the recommended option; if you pick another, change the templates to match.

**D1. How `main.c` ticks the chart.**
*Recommended:* a free-running loop. Every loop iteration is one tick, and `timerTick` is true on a tick only if an interrupt arrived. This is genuine multiform time: the chart reacts to buttons at once and to time only when an event is present. It also gives the best Section 4 evidence, since you can show thousands of ticks per phase against N events per phase against 6 ticks per cycle for Version A.
*Alternative:* tick only when an event arrives (uniform ticks). This is simpler, but every tick then carries `timerTick = true`, the "signal" becomes the tick itself, and buttons are sampled only every P.

**D2. Where the count happens.**
*Recommended:* a counter per timed thing (`c`, `wNS`, `wEW`, `camCount`). Reset it in the entry action (`c = 0`) and increment it in a **non-immediate** during action of the state that rests while waiting (`during if timerTick do c++`). This is exactly how brief §1.2 describes Version B ("its own counter variable, reset on entry"). Because a non-immediate during skips the entry tick, the event that ended the previous phase is not counted again.
*Rejected alternative:* one root-level `during if timerTick do c++`. SCCharts orders an absolute write (`c = 0`) before a relative write (`c++`) in the same tick, so on every phase change c would end at 1 and every phase would come out one period short. This is a good answer to have ready for the interview.

**D3. The timer rate.** `const int TIMER_MS = 10` in every Version B chart, plus `#define TIMER_PERIOD_MS 10` in `main.c`. They must be equal. The only time they differ is the brief's rescale check (Step 9, E4). 10 ms gives 1700 events per 17 s cycle and a 10 ms worst-case quantisation. Time-outs are stored as integer **milliseconds** (T3 = 0.5 s cannot be an int in seconds). Version B needs no floats at all, which matters on a Nios II without an FPU.

**D4. Board mapping (goes in the README).**

| Board | Chart | Note |
|---|---|---|
| SW1..SW0 | `task` = value + 1 | 00 = Task 1, 01 = Task 2, 10 = Task 3, 11 = Task 4 |
| KEY0 | `NSraised` | keys are active low; inverted in main.c |
| KEY1 | `EWraised` | |
| KEY2 | `vehicleButton` | press = enter, next press = leave (DE2-115 keys are hardware-debounced) |
| KEY3 | system reset | wired to `reset_reset_n` in Lab 1 |
| LEDR7..LEDR0 | `LEDR` | bits 5..0 lamps (Table 1), 6 NS walk, 7 EW walk |
| RS-232 UART, 115200 8N1 | `configChar`/`configValid` | Task 3 packets from a PC terminal |
| JTAG UART console | `print(...)` + evidence log | Task 4 messages appear here |

---

## 2. Step 1: Task 1 Version B chart

Open `Task1_VersionB.sctx` next to your `Task1_VersionA.sctx` and check that the diff is only these mechanical changes:

| Version A | Version B |
|---|---|
| `@ClocksUseSD` | deleted (no clocks) |
| `const float T1 = 6.0` (s) | `const int T1 = 6000` (ms), plus `const int TIMER_MS = 10` |
| *(deltaT from the simulator)* | `input bool timerTick` |
| `clock c = 0.0` | `int c = 0` (made an `output` here only so you can watch it) |
| `entry do c = 0.0; LEDR = …` | `entry do c = 0; LEDR = …` **and** `during if timerTick do c++` |
| `c >= T1` | `c * TIMER_MS >= T1` |

The states, the LED words, the immediate transitions and the single delayed transition RR2 → GR are identical. Copy it into your KIELER workspace project and check that it compiles with **Netlist-based Compilation (C)** (the compiler Lab 2 §7.4 uses for Nios II code).

Two things to be able to explain:

1. **Why the guard reads the incremented c in the same tick.** KIELER turns the during action into an inner region whose self-loop runs before the state's weak-abort transition is checked, so the transition sees the value counted in that tick. No dependency cycle arises: only the Lights region reads or writes c.
2. **Why the delayed transition is still needed.** The count does not change on the entry tick, so a time-out of 0 would let the cycle run through all six states in one tick. RR2 → GR being delayed prevents that (brief §1.3).

## 3. Step 2: check it on the PC (optional, about 30 min)

**Quick check in KIELER.** Temporarily set `TIMER_MS = 1000`. Each tick with `timerTick` true now stands for 1 s, so the phases need 6, 2, 1, 6, 2, 1 events (T3 = 500 rounds up to 1 event). Step the simulation by hand. Set `timerTick` true on some ticks and false on others, and confirm that the phase only advances on ticks with `timerTick` true. Put `TIMER_MS` back to 10 afterwards.

**Longer check with gcc.** Generate the C code (Step 3d below), save the header as `sccharts.h` and the source as `sccharts.c` next to `nios/pc_test.c`, and run:

```
gcc pc_test.c sccharts.c -o pc_test
./pc_test
```

You should see 600, 200, 50, 600, 200, 50 events per phase. The tick numbers between changes are 7 times larger, because there is one event every 7 ticks. The same harness works for the combined chart later (it leaves `task` at 0, so the chart stays in Task 1; set `d.task` in the loop to test the others).

## 4. Step 3: Nios II project (about 1–2 h the first time)

**a) Hardware.** Reuse your Lab 1 Quartus project unchanged (`nios2_system.qsys`/`.sopcinfo`: timer_0, timer_1, keys, switches, leds_red, uart, jtag_uart, lcd). Program `lab1.sof` with Tools → Programmer → USB-Blaster → Start.

**b) Application + BSP.** Start *Nios II Software Build Tools for Eclipse (Quartus Prime 18.1)* (your workspace `C:\Users\harol\sbt4e-18.1-workspace` is fine).
File → New → Nios II Application and BSP from Template → SOPC Information File = your `nios2_system.sopcinfo`, CPU = `cpu`, project name e.g. `traffic_b`, template **Blank Project** → Finish. You get `traffic_b` and `traffic_b_bsp`.

**c) BSP settings (important).** Right-click `traffic_b_bsp` → Nios II → BSP Editor → Main → Settings → Common → hal:
- `sys_clk_timer` = **timer_0** (drives `alt_alarm`, our timing reference)
- `timestamp_timer` = **timer_1** (an independent stopwatch for the evidence log)
- `stdout`/`stderr`/`stdin` = **jtag_uart**

Generate → Exit, then right-click the BSP → Build Project. Open `traffic_b_bsp/system.h` and check that the names `main.c` uses exist: `LEDS_RED_BASE`, `KEYS_BASE`, `SWITCHES_BASE`, `UART_NAME`. If yours differ, change `main.c`, not the hardware.

**d) Generate the chart code.** In KIELER open `Task1_VersionB.sctx` → Kieler Compiler view → select **Netlist-based Compilation (C)** → compile → click the **C Code** box → *Open in Editor*. Copy the header into a new header file `traffic_b/sccharts.h` and the source into a new source file `traffic_b/sccharts.c` (right-click project → New → Header File / Source File, Lab 2 §8.1). In `sccharts.c`, change the generated `#include "….h"` line to `#include "sccharts.h"`.

Open `sccharts.h` and read the `TickData` struct. The input/output fields should carry your chart names (`timerTick`, `LEDR`, …), and bools appear as `char`. If a name differs, fix it in `main.c`.

**e) main.c.** New → Source File `main.c`, paste `nios/main.c`, and set `#define CHART 1` for Task 1. Read it top to bottom; you will be asked about it. The parts that matter most:
- `timer_isr` only does `pendingEvents++` and returns the period. It runs inside the timer interrupt, so it must stay short.
- `take_timer_event` disables interrupts around the read-modify-write of `pendingEvents`, because the ISR writes it too. It hands the chart at most one event per tick, so if a `printf` blocks for a few ms, events queue up instead of being lost.
- `alarmTicks = TIMER_PERIOD_MS * alt_ticks_per_second() / 1000`: `alt_alarm` counts system-clock ticks (1 ms each here), not milliseconds.

**f) Build and run.** Right-click `traffic_b` → Build Project → Run As → Nios II Hardware. If it complains about the system ID or timestamp, open Run Configurations → Target Connection, tick both "Ignore mismatched …" boxes, and refresh connections.

## 5. Step 4: Task 1 on the board

LEDR0..5 should cycle G-R → Y-R → R-R → R-G → R-Y → R-R. The Nios II Console prints one line per change, for example:

```
LEDR  33 ->  34 | previous phase  6000xxx us |  NNNNNNN ticks |    600 timer events
```

Keep the console window open while running: the JTAG UART blocks `printf` when nobody reads it. Copy about 3 cycles of the log into `evidence/B_task1_10ms.txt`. This is your first Section 4 evidence.

## 6. Step 5: Task 2 Version B (about 30 min)

Copy `Task2_VersionA.sctx` to `Task2_VersionB.sctx` and apply the Step 1 recipe, plus the walk timers:

1. Header, chart name `Task2_PedestrianTrafficLight_B`, delete `@ClocksUseSD`, add the AI declaration.
2. Constants: int milliseconds, `WALK_TIME = 4000`, and add `TIMER_MS = 10`. Add `input bool timerTick`.
3. `clock c` → `int c = 0`. Inside GR, `clock wNS = 0.0` → `int wNS = 0`; the same for `wEW` in RG.
4. Every `c = 0.0` → `c = 0`, and `wNS = 0.0`/`wEW = 0.0` → `= 0`.
5. Add `during if timerTick do c++` to GR, YR, RR1, RG, RY, RR2.
6. Give WalkNS a during, and do the same for WalkEW with `wEW`:
   ```
   state WalkNS "NS walk light on" {
       entry do LEDR = EW_R + NS_G + NS_PED    // 97
       during if timerTick do wNS++
   }
   ```
7. Guards: `c >= T1` → `c * TIMER_MS >= T1` (all six), and `wNS >= WALK_TIME` → `wNS * TIMER_MS >= WALK_TIME` (the same for EW).
8. NSRequest/EWRequest: unchanged. They are not timed.

On the board, use `#define CHART 2`. Press KEY0 during R-G: the next G-R lights LEDR6 for 4 s (the log shows 97 → 33 after 400 events). Press KEY1 and check LEDR7 (140) in the next R-G. Note that GR and the walk are now two counters counting the **same** event stream, which is the Task 4 point in miniature.

## 7. Step 6: Tasks 1–4 combined, `TrafficLight_VersionB.sctx` (about 1.5 h)

Copy your current `TrafficLight_VersionA.sctx` and edit it. Line numbers refer to the Version A file as it is in your repo now.

**Interface and constants**
- L1–9: new header (Version B, timer events instead of deltaT, board mapping) plus an AI declaration that covers **all** the help you used. TASK3.md/TASK4.md say Tasks 3/4 were done with OpenAI Codex, and the current header only mentions Claude, so fix this in the Version A file too.
- L11: delete `@ClocksUseSD`. L12: `scchart TrafficLight_B`.
- L15–21: `const int` in ms (6000, 2000, 500, 6000, 2000, 500, `WALK_TIME = 4000`), and add `const int TIMER_MS = 10`.
- L23: `const int CAMERA_DWELL = 1000`.
- L26: `output int t1 = T1, t2 = T2, …` (active time-outs, now in ms).
- Add `input bool timerTick` next to the other inputs.
- L57: `clock cameraClock = 0.0` → `output int camCount = 0`.
- L72: `clock c = 0.0` → `output int c = 0` (output so you can watch it; `wNS`/`wEW` stay plain `int` because `output` is only allowed at root level).

**Lights region**
- GR (L77–96): `clock wNS` → `int wNS = 0`; entry `c = 0`; add `during if timerTick do c++`; L84 `wNS = 0`; WalkNS gets `during if timerTick do wNS++`; L90 guard `wNS * TIMER_MS >= WALK_TIME`.
- L98: `if c * TIMER_MS >= t1 go to YR` (still the one delayed edge of the main cycle).
- YR: entry `c = 0`, add the during, and L103 guard `c * TIMER_MS >= t2`.
- RR1 (L105): entry `c = 0`. **No** during here: RR1 is left immediately without a trigger, and KIELER discards a during in such a state anyway.
- L120–122, the commit: `t1 = pre(pending1) * MS_PER_S; … t6 = pre(pending6) * MS_PER_S; …; c = 0` with `const int MS_PER_S = 1000`. Packets stay in **integer seconds**, as in Version A, so the two versions accept the same packets.
- L127: `!waitingConfig && c * TIMER_MS >= t3`.
- **L130, the important one:** the all-red loop RR1Select → RR1Config → RR1Exit → RR1Wait → (next tick) RR1Select is re-entered every tick, so a `during` on RR1Wait would never fire (a non-immediate during skips the entry tick, and every tick is an entry tick there). Count on the delayed edge instead:
  ```
  state RR1Wait
      if timerTick do c++ go to RR1Select
      go to RR1Select
  ```
  The counting edge runs first in the tick, then the immediate chain checks `c`, so the all-red ends on the right event. The event that ended R-Y is not counted (RR1Wait's edges are delayed).
- Mirror all of this for RG / WalkEW / RY / RR2 / RR2Config (L175–177) / RR2Exit (L182) / RR2Wait (L185).

**Camera region**
- L278: `cameraArmed && camCount * TIMER_MS >= CAMERA_DWELL`.
- L282: `do camCount = 0; cameraArmed = true; …`.
- L286: same pattern as RR1Wait, since NextCameraTick is also re-entered every tick:
  ```
  state NextCameraTick
      if timerTick && cameraArmed do camCount++ go to SampleVehicle
      go to SampleVehicle
  ```

**Unchanged:** NSRequest, EWRequest, the Configuration parser, mode selection, and the vehicle edge logic. None of them is timed.

Compile with Netlist-based Compilation (C). Expect the same two "Instantaneous loop detected!" warnings as Version A, but the clock VariableStore warnings should be gone. Paste the code into `sccharts.c`/`.h` as in Step 3d, set `#define CHART 4`, build, and run. With SW1..0 = 00 it must behave like Task 1.

## 8. Step 7: Task 3 on the board

1. Either connect the DE2-115 RS-232 port to the PC (USB-serial adapter) and open PuTTY → Serial, COMx, 115200, 8N1, flow control **None**, or use only the USB-Blaster cable: `main.c` also reads packets from the JTAG UART console (`nios2-terminal`). The C3 board tests used the second route, feeding `nios2-terminal`'s input from a file so every byte is exact (Nios II Command Shell):
   ```
   : > packets.txt
   tail -f packets.txt | nios2-terminal | tee log.txt
   printf '8,3,1,8,3,1\r\n' >> packets.txt      # from a second shell, one line per packet
   ```
   Typing into `nios2-terminal` directly also works, but Enter may send only CR: end each packet with **Ctrl+J** (LF) unless you have checked that Enter sends LF.
2. SW1..0 = 10 (Task 3). At the next R-R the lights hold all-red (`waitingConfig`).
3. Send `8,3,1,8,3,1` followed by CR LF. PuTTY's Enter sends only CR, which the parser ignores, so finish the packet with **Ctrl+J** (LF). A script is more reliable for repeat tests:
   ```python
   import serial                      # pip install pyserial
   s = serial.Serial("COM5", 115200)
   s.write(b"8,3,1,8,3,1\r\n")
   ```
4. The lights resume and the log shows phases of 8000/3000/1000 ms. Also try an invalid packet (`1,2,3\n`, which should leave the lights red), a valid packet sent during green (it applies only at the next R-R), and switching back to Task 1/2/4.

`main.c` feeds at most one byte per tick, and only when `configReady` was true after the previous tick. Bytes that arrive meanwhile wait in the HAL UART driver's buffer, which holds a full packet. This is the "future UART interface must buffer bytes" item from your TASK3.md, now done. Because `d` starts zeroed, the first tick never carries a character, so the first-tick issue in TASK3_EDGE_RESULTS.md cannot occur on the board.

## 9. Step 8: Task 4 on the board

SW1..0 = 11. Press KEY2 (vehicle enters) during green, release it, and wait for yellow. The console should print `Camera activated`, then `Snapshot taken` 1 s later together with `camera dwell measured: …`. Press KEY2 again for `Vehicle left`. Repeat with a departure before the second is up (no snapshot), and with the vehicle entering **during** yellow. In that last case the dwell starts between two events, so at P = 100 ms it measures 900–1000 ms instead of exactly 1000. That is concrete Task 4 evidence of the alignment effect.

## 10. Step 9: Section 4 evidence (about 2 h)

Run each experiment, save the console log under `evidence/`, and note the settings in the file name.

| # | Experiment | Settings | What to show |
|---|---|---|---|
| E1 | Equivalence | Task 1 and Task 4, P = 10 | same LED sequence as your Version A traces (33, 34, 36, 12, 20, 36; walks 97/140) |
| E2 | Accuracy vs rate | P = 1, 10, 100 (change chart **and** main.c) | measured phase vs intended; jitter = spread over ≥ 3 cycles |
| E3 | Quantisation | P = 300 | T3 → 600 ms (+100), T2 → 2100 ms (+100), T1 → 6000 ms (0): error = ⌈T/P⌉·P − T |
| E4 | Rescale (brief §2.1) | chart `TIMER_MS = 10`, main.c `TIMER_PERIOD_MS = 20` | every duration doubles: the chart only counts events |
| E5 | Computational effort | any | ticks per phase vs timer events per phase, from the log; Version A needed 6 ticks per 17 s cycle |
| E6 | Two concurrent timers | Task 4, P = 100 | camera armed at yellow start: exactly 1000 ms; vehicle arriving mid-yellow: 900–1000 ms |

For E5, compute the share of wasted work as 1 − events/ticks. At P = 10 a cycle is 1700 events, but the free-running loop computes far more ticks than that. With uniform ticking it would still be 1700 ticks, against 6 for Version A with dynamic ticks. Link this to the brief's "counting a frequent timing signal vs reacting only when a clock expires".

## 11. Step 10: submission checklist

- **.pof:** Quartus → File → Convert Programming Files → type *Programmer Object File (.pof)*, configuration device **EPCS64**, mode *Active Serial*, SOF Data → Add File → your `.sof` → Generate.
- **Zip `group_N.zip`:** all `.sctx` (A: Task1, Task2, TrafficLight; B: Task1, Task2, TrafficLight); the `traffic_b` and `traffic_b_bsp` folders (you may run Project → Clean first to drop build outputs); the `.pof` and `.sopcinfo`; a README with the D4 mapping table and "Version A = simulator charts, Version B = board charts" (the brief asks which input selects which task and which selects the timing version); the evidence (A `.ktrace` files and B console logs).
- **AI declarations** in every chart and in `main.c`, naming every tool you used.
- **The report PDF** is submitted separately.

## 12. Troubleshooting

| Symptom | Likely cause |
|---|---|
| Lights never change, console prints "No system clock timer" | BSP `sys_clk_timer` is none. Set it to timer_0, regenerate and rebuild the BSP |
| All phases k times too long/short | `TIMER_MS` (chart) ≠ `TIMER_PERIOD_MS` (main.c) |
| Compile error on `d.xxx` | generated field name differs: check `TickData` in `sccharts.h`; or `CHART` does not match the pasted chart |
| `sccharts.c` cannot find a header | the generated `#include` still names the model header; change it to `"sccharts.h"` |
| KIELER: dependency cycle / cannot sort regions | a counter is read or written outside its own region. Keep `c`/`wNS`/`wEW` inside Lights and `camCount` inside Camera |
| Board freezes when the console is closed | JTAG UART `printf` blocks; keep the Nios II Console open |
| Nothing arrives over UART | wrong COM port, flow control not None, or the packet has no LF (use Ctrl+J or the script) |
| Run As fails with a system ID mismatch | Run Configurations → Target Connection → tick both Ignore boxes |
