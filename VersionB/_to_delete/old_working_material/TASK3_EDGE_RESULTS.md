# Task 3 edge-case review

Tested the saved `TrafficLight_VersionA.sctx` through the installed KIELER
netlist Java compiler and executed the generated Java. Unsaved VS Code edits
and the live simulation were not changed. This is a broad automated review,
not an exhaustive proof over every input sequence.

## Results

- Existing suite: 18,534 assertions passed.
- Extended suite: 19 of 20 scenario groups passed; one startup failure remains.
- Extended run executed 1,632,812 assertions (including the failing assertion).
- The same five compiler warnings remain as in the original Part 1 baseline.

## Startup failure

If `configValid = true` and the first character is supplied on the very first
tick after reset, the parser drops that character. `Receive` checks
`pre(configReady)`, whose previous-tick value is not true on that initialization
tick, even though the initialized output subsequently advertises readiness.

Reproduction: reset, set `task = 3`, `configValid = true`, `configChar = 56`,
`deltaT = 0`, and tick once. The parser's `digits` and `number` remain zero
instead of becoming 1 and 8. Sending the rest of the packet then produces an
invalid packet due to the missing first digit.

Workaround: take one initialization tick with `configValid = false`, then send
characters only when the displayed `configReady` is true. Waiting until Task 3
holds all-red already satisfies this condition. No controller fix was applied
as part of this check; the test intentionally remains failing.

## Mode-switch observation (not a parser failure)

At 2 of 192 tested phase offsets, switching from Task 3 to Task 2 on the last
red tick changed `activeTask` and left red in the same synchronous tick. Example:
`LEDR = 36`, `c = 0.875`, then a tick with `deltaT = 0.125` ends with mode 2 and
`LEDR = 12`. The switch is executed in the internal all-red decision states.

Thus it satisfies an internal-state interpretation of "switch only in R-R",
but does not guarantee that the output on the mode-change tick is still red.
A stricter whole-tick red guarantee would require an implementation change.
Zero red durations can similarly pass through red without a visible red output
tick. Configuration commits themselves explicitly hold red for their commit tick.

## Passing coverage

- All byte values except LF in each of six numeric fields (LF separately tested).
- Empty fields, signs, spaces, decimal points, non-digits, 1-4 digits, fifth
  digits, leading zeros, zero, 9999, and CR ignored within the packet.
- 2,000 deterministic randomized packets checked against an independent regex.
- Pauses between characters, incomplete packets, repeated LF, invalid packets
  after a successful configuration, a 10,000-character corrupt packet, recovery.
- Packets queued before Task 3 and updates at 192 phase offsets.
- Successive packets sent as soon as readiness returns; pending-packet protection
  is also covered by the original suite.
- Invalid task values, switching at 192 offsets, and all 64 combinations of
  zero/one-second phase durations without an instantaneous execution hang.
- Three complete cycles measured at 0.125-second steps for 8,3,1,8,3,1 timings.
- Simultaneous pedestrian requests and held buttons with one-second greens.
- Reset after configuration and a partial packet; zero elapsed-time ticks.
- Coarse 100-second elapsed-time steps maintain safe lamp combinations. This
  does not imply accurate phase durations under such coarse sampling.

## Limits and assumptions

Inputs must use finite, nonnegative elapsed time. Negative/NaN/infinite `deltaT`
is outside the intended runtime contract and was not validated. Zero-duration
phases are syntactically accepted by the packet format, but may not remain
visible for a full tick. Use positive timings for the normal demonstration.
Dynamic tick scheduling, Nios II Version B, Task 4, hardware button bounce, and
multi-billion-event counter overflow are not validated by this suite.

Run the extended suite:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File ./tests/run_task3.ps1 -EdgeCases
```

The nonzero exit status is expected until the first-tick failure is fixed.
