# Task 3: runtime configuration (Version A)

Open `TrafficLight_VersionA.sctx` in KIELER / VS Code. It now implements Tasks
1-3. The standalone Task 1 and Task 2 files are unchanged. Task 4 and external
timer Version B are not implemented here.

> **Update (2026-10-19), applies to Version A and Version B:** packet values are
> now **milliseconds** (1..9999), so the defaults `6000,2000,500,6000,2000,500`
> (including the 0.5 s all-red) can be sent; Version A converts them to seconds
> (`/ MS_PER_S`), Version B uses them as they are. A **0** field now makes the
> packet invalid (a zero yellow or all-red would skip that safety phase). The
> commit goes to `RRnExit`, whose clock guard requests the wake-up `t3`/`t6`
> later, so the new all-red ends on time in pure Dynamic mode. The walkthrough
> below uses the new format; the current regression is
> `VersionB/evidence/versionA/run_versionA_sim.py` (A2-A11, A13-A15).

## What changed and why

1. **Writable timings.** `T1` through `T6` still define the initial defaults.
   New output variables `t1` through `t6` hold the active durations, in seconds
   (the packet's milliseconds divided by `MS_PER_S` = 1000.0).
   The light transition guards now compare the phase clock with these variables.
   A true constant cannot be overwritten at runtime, so this separates the
   brief's named defaults from the values Task 3 changes.

2. **A fourth concurrent region, `Configuration`.** It consumes a sequence of
   ASCII characters, equivalent to bytes arriving from UART later. This uses
   the brief's allowed sequence input rather than a simulator-specific string
   function. `number` accumulates digits, `digits` enforces the four-digit limit,
   and `field` tracks which of the six numbers is being read.

3. **Validation before publication.** Exactly six unsigned 1-4 digit numbers
   separated by commas are accepted. LF (ASCII 10) terminates the packet; CR
   (ASCII 13) is ignored. Empty fields, extra/missing fields, signs, spaces,
   decimal points, letters, and fifth digits invalidate the whole packet.
   After an error, characters are discarded through LF; the following packet
   starts fresh. `configRejected` increments when an invalid packet ends.

4. **A stable pending packet.** Only a valid LF-terminated packet is copied to
   `pending1` through `pending6`. `configSequence` identifies that packet and
   `configReady` becomes false. The parser cannot overwrite the pending packet
   before the lights acknowledge it. The sender must respect `configReady`.

5. **An all-red commit.** Both all-red phases now have explicit decision states:
   select the mode, check the pending packet, then decide whether red can end.
   Only the Lights region changes `t1` through `t6`. It reads `pre(pendingN)`
   and `pre(configSequence)`, copies all six values together, acknowledges with
   `configApplied`, and resets `c`. Thus the new all-red duration starts when
   the values are applied, rather than inheriting time already spent waiting.

6. **Delayed transitions.** The main cycle's delayed edge moved from
   `RR2 -> GR` to `GR -> YR`. The red decision loops and parser loops each have
   a delayed edge, preventing repeated processing within one synchronous tick.
   The generated-code regression test confirms the original positive-duration
   Tasks 1-2 behaviour for the tested inputs.

## Mode and timing decisions

- `task = 1`: basic traffic lights; `task = 2`: pedestrians;
  `task = 3`: pedestrians plus runtime configuration.
- Entering Task 3 takes effect in all-red and sets `waitingConfig = true`.
  The controller stays red until a valid pending packet is applied. A packet
  may be received in advance, including during green or another mode.
- After configuration, traffic continues normally. Further complete packets
  apply at the next all-red opportunity while Task 3 remains active. Partial
  or malformed later packets leave the active timings unchanged.
- Changing to Task 1 or 2 can cancel the all-red wait. Re-entering Task 3
  requires a new packet; an already-applied packet cannot release the wait.
- Values outside `task = 1..3` are ignored. Configured timings persist across
  mode changes; resetting the simulation restores defaults.
- Values are **integer milliseconds**, 1..9999. Leading zeros are accepted
  (`0800` = 800 ms). A **0** field is rejected: the brief fixes only the digit
  count, but a zero yellow or all-red would let green follow green, which a
  safety-relevant controller must not allow. Because every value is at least
  1 ms, a commit (which resets the clock) always keeps the all-red visible for
  that tick, and the exit guard requests the wake-up for the new duration.
- `WALK_TIME` stays 4 seconds. A configured green shorter than that ends its
  nested walk phase when green ends, so a walk light cannot extend into yellow.
- The single pending-packet slot intentionally uses backpressure rather than
  an unbounded queue. A future UART interface must buffer bytes while not ready.

## Try it in KIELER / VS Code

1. Open `TrafficLight_VersionA.sctx` and use **Simulation: Simulate current
   model with...** with your usual working Java simulation chain. Set simulation
   type to **Manual** while entering characters. Ensure `deltaT` is in seconds.
2. Set `task = 3`, `configValid = false`, and both request buttons false. Step
   forward with a positive `deltaT` until `activeTask = 3`, `LEDR = 36`, and
   `waitingConfig = true`. Default timings reach the first red after 8 seconds.
3. Send the packet `8000,3000,1000,8000,3000,1000\n` (milliseconds). Here `\n`
   means a single LF character, **not** a backslash followed by the letter n. On
   each step set `configValid` true and set `configChar` to the next ASCII code.
   You can use `deltaT = 0` for these input-only ticks.

   | Character | 0 | 1 | 3 | 8 | , | LF |
   |---|---|---|---|---|---|---|
   | `configChar` | 48 | 49 | 51 | 56 | 44 | 10 |

   so the 30 codes are `56 48 48 48 44  51 48 48 48 44  49 48 48 48 44`
   `56 48 48 48 44  51 48 48 48 44  49 48 48 48 10`.

   One step accepts one character. `configValid` may stay true across these
   consecutive steps, but that means **a new character is supplied every tick**.
   Set it false whenever no character is being sent. Send only if `configReady`
   was true after the previous tick. After LF, it becomes false temporarily.

4. Set `configValid = false` and step again. `configApplied` becomes 1,
   `waitingConfig` becomes false, and `t1..t6` become 8.0, 3.0, 1.0, 8.0, 3.0,
   1.0 s together (`sleepT` = 1.0 on that tick: the new all-red's wake-up).
   Following the acknowledgement, `configReady` returns true. With positive
   elapsed time, the controller holds the newly configured all-red duration
   and resumes the light cycle.
5. Try `1,2,3\n` (or `6000,2000,0,6000,2000,500\n`) after entering Task 3
   again. `configRejected` increments and the controller stays red. Then send a
   valid packet to release it.
6. Send another valid packet during green. Observe that the active durations
   and `configApplied` remain unchanged until the next all-red phase.

## Validation performed

The chart was parsed, validated and compiled using the actual KIELER language
server bundled with the installed `kieler.keith-vscode-0.3.0` extension, through
the `de.cau.cs.kieler.sccharts.netlist.java` compilation chain. The resulting
Java was compiled and executed, rather than testing a separate parser model.

The test run passed 18,534 assertions, including:

- 4,000 ticks matching the original combined Part 1 controller's lamp outputs
  and active mode, with changing modes and pedestrian requests;
- incomplete and malformed packets, recovery, CRLF, and leading zeros;
- zero and four-digit maximum values;
- atomic configuration during red, restarted red timing, and pending updates
  received during green;
- mailbox backpressure, cancellation and re-entry, and pedestrian safety with
  short configured green phases.

KIELER emits two `Instantaneous loop detected!` warnings and three clock
`VariableStore` warnings. The same five warnings are emitted for the original
Part 1 controller; the extension adds no warnings. These warnings have not
been eliminated. Tests use explicitly supplied elapsed time; an interactive
Dynamic-mode demonstration and formal verification have not been performed.

Run `powershell -NoProfile -ExecutionPolicy Bypass -File ./tests/run_task3.ps1`
to regenerate Java and repeat the tests (the policy option applies only to
this test process and does not change the machine's settings). The script
uses the locally installed KIELER jar and Android Studio JDK by default; paths
can be supplied as parameters. `tests/fixtures/TrafficLight_Part1.sctx` is the
original combined chart used as the regression reference. Generated files go
under `tmp/`, and are not assignment source deliverables.

## Authorship

The original Part 1 code contains the group's existing AI-use declaration.
All design decisions for the Task 3 extension were made by Harold and Lucas.
Its code, documentation and tests were written with the assistance of OpenAI
Codex, then reviewed, tested and verified by Harold and Lucas.
