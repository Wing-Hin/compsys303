# Task 4: red-light camera (Version A, C simulation)

Open `TrafficLight_VersionA.sctx` and choose **Netlist-based Simulation (C)**.
Restart the simulation after editing the chart so the new input/output interface
is generated. The controller now accepts task values 1 through 4.

## How the camera works

The new `Camera` region runs alongside the lights, pedestrian request handlers,
and configuration parser. It never changes the light outputs or phase clock.

1. A rising edge on `vehicleButton` toggles vehicle presence: first press enters,
   second press leaves. Release the button between presses. Holding it true
   counts only once. Presence is tracked in every mode so switching modes does
   not invent a departure or arrival.
2. In Task 4, if a vehicle is present while either direction is yellow, the
   camera resets its own clock and prints `Camera activated`.
3. If the vehicle remains for `CAMERA_DWELL` seconds, it prints `Snapshot taken`
   and increments `snapshots`. The default dwell is 1 second, a named constant
   near the phase timing defaults.
4. A departure prints `Vehicle left` in Task 4 and cancels a running timer.
   Departures are processed before the deadline check, so leaving exactly on
   the expiry tick prevents a snapshot.
5. Only one snapshot is taken per vehicle visit. A departure and subsequent
   arrival permit another snapshot. A timer already armed continues beyond
   yellow if necessary; switching out of Task 4 cancels it.

Interpretation used: a vehicle must be present during yellow to start the
camera timer. An empty intersection does not print an activation. A vehicle
arriving partway through yellow starts its allowed dwell at arrival. This makes
the unspecified arrival/yellow ordering explicit for the design report.

## Changes to mode selection

- Task 4 activates only through the existing all-red mode selection states.
- It includes pedestrian operation and permits valid timing packets to be
  applied at all-red, just like Task 3.
- Entering Task 4 does not force a configuration wait: current/default timings
  remain usable immediately. Entering Task 3 still requires a fresh pending
  packet as before. Timings persist across mode changes.

## Inputs and outputs added

| Name | Meaning |
|---|---|
| `vehicleButton` | Input: true/false press and release; each new press toggles presence. |
| `vehiclePresent` | Output: vehicle currently in the intersection. |
| `cameraArmed` | Output: a camera dwell timer is running. |
| `cameraActivated` | Output pulse: the camera started this tick. |
| `snapshotTaken` | Output pulse: a snapshot was taken this tick. |
| `vehicleLeft` | Output pulse: a vehicle departed in Task 4 this tick. |
| `snapshots` | Output: total snapshots since reset. |

The three message indicators last one tick; use the history column to inspect
past pulses. The exact required messages are printed using SCCharts `print`.
The strings use `\\n` in the SCChart to produce a C newline escape correctly
with this installed KIELER version. KIELER's simulation output redirects plain
message lines separately from the JSON variable updates.

## Quick demonstration

1. Start with `task = 4`, `vehicleButton = false`, `configValid = false`, both
   pedestrian inputs false, and `deltaT = 1`.
2. Step until `activeTask = 4` (first all-red, after the initial NS green/yellow).
3. Set `vehicleButton = true` and Step with `deltaT = 0`: a vehicle enters.
4. Set `vehicleButton = false` and Step to release the button. Do not press it
   again yet: the next press means the vehicle leaves.
5. Restore `deltaT = 1` and step until EW yellow (`LEDR = 20`). The activation
   pulse becomes true and the camera prints `Camera activated`.
6. Advance another second. Expect `snapshotTaken = true`, `snapshots = 1`, and
   `Snapshot taken` in the simulation output.
7. Press the vehicle button again. Expect `vehiclePresent = false` and the
   `Vehicle left` message. Release it afterward.

For the cancellation test, repeat but make the vehicle leave before the dwell
expires; use `deltaT = 0.25` for finer control. Expect no snapshot.

## Verification and limitations

- Parsed and compiled with KIELER's C netlist compiler; generated C built and
  executed with the installed Quartus GCC compiler.
- 11,078 camera test ticks passed, including both yellow phases, a held button,
  entry during yellow, early departure, departure exactly at expiry, one
  snapshot per visit, a second visit, inactive modes, Task 4 configuration,
  simultaneous pedestrian inputs, and deterministic randomized button inputs.
- A separate three-second dwell variant verified that the timer survives the
  end of yellow and that leaving Task 4 cancels it.
- A 10,000-tick regression run matched the previous chart's light outputs,
  active mode, and timing values for modes 1-3 with pedestrian inputs.
- KIELER retains the baseline's two instantaneous-loop warnings and clock
  VariableStore warnings; the additional camera clock has the same kind of
  VariableStore warning. GCC compiled the tested generated code successfully.
- The existing Task 3 first-tick character issue remains: initialize with
  `configValid = false` before sending a packet.
- This is Version A using clocks. Version B's Nios II timer-event implementation
  is still required for the final assignment. Negative/non-finite elapsed time,
  hardware debounce, and zero-duration yellow phases are not camera guarantees.
  Use positive yellow durations so a yellow phase is observable to the camera.

Task 4 design, implementation, documentation and checks were assisted by
OpenAI Codex. Review the design choices and record assistance accurately.
