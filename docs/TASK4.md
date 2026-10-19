# Task 4: red-light camera (Version A and Version B)

Both combined charts contain the same `Camera` region: `VersionA/TrafficLight_VersionA.sctx` times the dwell
with a Timed SCCharts clock, `VersionB/TrafficLight_VersionB.sctx` counts Nios II timer events. Task 4
is selected with `task = 4` (simulator) or SW1..0 = `11` (board) and includes the pedestrian lights.

## Behaviour

The `Camera` region (`SampleVehicle`, `ReportLeave`, `CheckCamera`, `NextCameraTick`) runs alongside
Lights, the two request regions and the parser. It reads `LEDR` and `activeTask` but never writes them.

1. Each rising edge of `vehicleButton` toggles vehicle presence: the first press is a car entering,
   the next a car leaving. Holding the button counts once. Presence is tracked in every mode.
2. In Task 4, if a car is present while either direction is yellow (`LEDR` 34 or 20) and it has not
   been photographed on this visit, the camera starts its dwell timer and prints `Camera activated`.
3. If the car is still there after `CAMERA_DWELL` (1 s, a named constant), it prints `Snapshot taken`.
4. When the car leaves it prints `Vehicle left` and cancels a running timer. The departure is checked
   before the deadline in the same tick, so a car leaving exactly on the deadline is not photographed.
5. One snapshot per visit; a new visit can be photographed again. An armed timer keeps running after
   the yellow ends; leaving Task 4 cancels it.

Interpretation used: the camera is armed only for a car that is in the intersection during a yellow.
A car arriving partway through a yellow starts its dwell when it arrives.

## Version A: a second clock

`cameraClock` is reset at activation and the guard `cameraClock >= CAMERA_DWELL` gives the snapshot,
independently of the phase clock `c`. In Dynamic mode the chart only reacts when a guard can become
true, so the activation tick goes through `ArmedCheck`, which evaluates the dwell guard and makes KIELER
request a wake-up 1 s later. Its fallback goes to the separate state `ArmedTick`: with both transitions
to the same target, KIELER generated the same guard for both and the region stopped (see
`evidence/final_test_results.md`, finding for A10/A11).

## Version B: counting the same event stream

There is no clock. `camCount` is reset at activation and counted on the delayed transition out of
`NextCameraTick` when `timerTick && cameraArmed`; the snapshot guard is
`camCount * TIMER_MS >= CAMERA_DWELL` (100 events at 10 ms). The phase counter `c` and `camCount` count
the same external signal for two purposes at once (brief Section 2.4). A car arriving between two
events sees a partial first period, so its dwell can end up to one timer period early (936-960 ms at a
100 ms timer, `evidence/board_logs/B_E6_camera_100ms_yellow.txt`).

## Interface

| Name | Meaning |
|---|---|
| `vehicleButton` | input: press and release; each new press toggles presence |
| `vehiclePresent` | output: a car is in the intersection |
| `cameraArmed` | output: the dwell timer is running |
| `cameraActivated`, `snapshotTaken`, `vehicleLeft` | one-tick output pulses with the three messages |
| `snapshots` | output: snapshots since reset |

The messages are printed with SCCharts `print` (`\\n` in the chart gives the C newline escape with this
KIELER version). On the board they appear in the `nios2-terminal` console.

## Running it

**Version A (KIELER, VS Code):** simulate `VersionA/TrafficLight_VersionA.sctx` with **Netlist-based Simulation
(C)**. Set `task = 4` and step until `activeTask = 4` (the first all-red). In a green, set
`vehicleButton` true for one step with `deltaT = 0`, then false. Step on: at the next yellow
`Camera activated`, 1 s later `Snapshot taken`; press the button again for `Vehicle left`. For no
snapshot, press it again within 1 s of the activation (use `deltaT = 0.25`).

**Version B (DE2-115):** SW1..0 = `11`. Press KEY2 in a green (car enters): at the yellow the console
prints `Camera activated` and about 1 s later `Snapshot taken`; KEY2 again prints `Vehicle left`.
Pressing KEY2 again within 1 s of the yellow gives `Camera activated` and `Vehicle left`, no snapshot.

## Evidence

- Version A: `evidence/versionA/A_results.txt` - A10 (snapshot exactly 1.0 s after
  activation), A11 (early departure, no snapshot), A15 (reactions with a car).
- Version B on the PC: `evidence/pc_suite/pc_suite.c` cases S20-S27.
- Version B on the board: C4.1-C4.7, E6 and R1.4-R1.5 in `evidence/final_test_results.md`
  (e.g. dwell 999.3 ms at 10 ms in `evidence/board_logs/B_R1_tasks124_current_build.txt`).

## Authorship

Harold and Lucas designed Task 4 and made all design decisions. They discussed the structure of the
code with OpenAI Codex and Claude (Anthropic), which helped write parts of the Task 4 code, its
checks and this document; Harold and Lucas reviewed, tested and verified all of it.
