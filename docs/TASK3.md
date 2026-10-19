# Task 3: run-time configuration (Version A and Version B)

Both combined charts implement Tasks 1-4: `VersionA/TrafficLight_VersionA.sctx` (Timed SCCharts clocks, run in
the KIELER simulator) and `VersionB/TrafficLight_VersionB.sctx` (counts the Nios II `timerTick`, runs on
the DE2-115). The Task 3 logic is the same in both; only the unit conversion at the commit differs.

## Packet format

`#,#,#,#,#,#[\r]\n` - six integers of 1-4 digits, in **milliseconds**, **1 to 9999**, in the order
t1..t6 = G-R, Y-R, R-R, R-G, R-Y, R-R. Commas separate the values, CR is ignored and LF ends the packet.

| Packet | Result |
|---|---|
| `6000,2000,500,6000,2000,500` | valid: the default timing (6 s / 2 s / 0.5 s) |
| `8000,3000,1000,8000,3000,1000` | valid: 8 s / 3 s / 1 s |
| `0800,0300,0100,8000,3000,1000` | valid: leading zeros are allowed (800 ms, ...) |
| `1,2,3` | invalid: not six values |
| `12345,1,1,1,1,1` | invalid: five digits |
| `1,,1,1,1,1` or `a,1,1,1,1,1` | invalid: empty field / not a digit |
| `6000,2000,0,6000,2000,500` | invalid: a **0** field (a zero yellow or all-red would let green follow green) |

Version A divides each value by `MS_PER_S = 1000.0` (its time-outs are seconds). Version B uses the
values as they are (its time-outs are milliseconds) and therefore rounds each one up to whole timer
events: at `TIMER_MS = 10`, 1234 ms lasts 124 events = 1240 ms. Both versions accept the same packets.

## Design

1. **Named defaults, writable active values.** `T1..T6` stay constants at the top of the chart (brief
   Section 3); the guards compare the phase timer with the outputs `t1..t6`, which Task 3 overwrites.
2. **Configuration region** (`Receive`, `Classify`, `NextCharacter`, `Published`). It reads one ASCII
   character per tick from `configChar` when `configValid` is true. `number` accumulates digits,
   `digits` enforces the 4-digit limit and `field` counts the six values. `Receive` checks `configReady`
   directly (not `pre(configReady)`), so the first character after reset is not lost.
3. **Validation.** Any error marks the packet bad; the rest is discarded up to its LF, then parsing
   starts fresh. `configRejected` counts rejected packets.
4. **One-slot mailbox.** A valid packet is copied to `pending1..6`, `configSequence` is incremented and
   `configReady` goes false until Lights acknowledges it with `configApplied`. The sender must only
   send while `configReady` is true (backpressure); nothing can overwrite a waiting packet.
5. **Commit only in the all-red.** Each all-red runs `RRnSelect -> RRnConfig -> RRnExit -> RRnWait`
   (delayed) `-> RRnSelect`. `RRnConfig` applies a waiting packet when `activeTask >= 3` (Task 3 and
   Task 4): it reads the mailbox through `pre()`, copies all six values at once, resets the phase timer
   `c` (so the new all-red is held in full) and goes to `RRnExit`. Evaluating the exit guard in the
   commit tick makes Version A request its wake-up (`sleepT = t3` or `t6`), so the new all-red also
   ends on time in pure Dynamic mode. Every value is at least 1 ms, so the all-red is always visible.
6. **Delayed transitions.** One per loop: `GR -> YR` on the main cycle, `RRnWait -> RRnSelect` in each
   all-red loop, `NextCharacter -> Receive` and `Published -> Receive` in the parser.

## Mode rules

- `task` 1-4 selects the mode; other values are ignored (the current mode is kept). A change takes
  effect only in an all-red (`RRnSelect`).
- Entering Task 3 sets `waitingConfig`: the lights hold all-red until a valid packet is applied. A
  packet received earlier, in any mode, is applied at that all-red.
- After the commit Task 3 cycles normally; later valid packets are applied at the next all-red, and
  invalid ones leave the timing unchanged.
- Task 4 also applies valid packets at an all-red, but does not wait for one.
- Leaving Task 3 cancels the hold; re-entering Task 3 waits for a new packet. Timings persist across
  mode changes; a reset restores the defaults.
- `WALK_TIME` stays 4 s. A configured green shorter than that ends its walk when the green ends, so a
  walk light can never reach yellow.
- Two packets back to back are both committed in the same all-red (the second wins, first never
  visible); a commit late in an all-red restarts its count, so that all-red lasts longer (safe side).

## Running it

**Version A (KIELER, VS Code):** open `VersionA/TrafficLight_VersionA.sctx`, simulate with
**Netlist-based Simulation (C)**, and step manually while entering characters (`deltaT` in seconds).

1. Set `task = 3`, `configValid = false`, both request buttons false, and step with a positive
   `deltaT` until `activeTask = 3`, `LEDR = 36` and `waitingConfig = true` (the first all-red, 8 s).
2. Send `8000,3000,1000,8000,3000,1000` and LF, one character per step with `deltaT = 0`: set
   `configValid = true` and `configChar` to the ASCII code (`0` = 48, `1` = 49, `3` = 51, `8` = 56,
   `,` = 44, LF = 10), only while `configReady` is true. The 30 codes are
   `56 48 48 48 44  51 48 48 48 44  49 48 48 48 44  56 48 48 48 44  51 48 48 48 44  49 48 48 48 10`.
3. Set `configValid = false` and step: `configApplied = 1`, `t1..t6` = 8, 3, 1, 8, 3, 1 s and
   `sleepT = 1.0`; with positive `deltaT` the cycle resumes with the new timing.
4. Leave and re-enter Task 3, send `1,2,3` + LF: `configRejected` increments and the lights stay red.

**Version B (DE2-115):** SW1..0 = `10`. `main.c` feeds one byte per tick, only while `configReady`, from
the RS-232 UART (115200 8N1) or, if that has none, from the JTAG UART console. With only the
USB-Blaster cable, type the packet into `nios2-terminal` (there is no echo) and end it with **Ctrl+J**
(LF); the console then logs the new phases, e.g. 800/300/100 timer events.

## Evidence

- Version A: `evidence/versionA/A_results.txt` - A8 (valid packet, strict Dynamic mode, commit
  wake-up), A9 (invalid packet), A13 (0 fields); traces `trace_A8_A9_A13_task3.jsonl`.
- Version B on the PC: `evidence/pc_suite/pc_suite.c` cases S11-S19 and S30 (`pc_suite_results.txt`).
- Version B on the board: `evidence/board_logs/B_C3_jtag_packets.txt` (C3.2-C3.6, C3.8-C3.11) and
  `B_C3_task3_exit.txt` (C3.1, C3.7); results in `evidence/final_test_results.md`.

## Authorship

Harold and Lucas designed Task 3 and made all design decisions. They discussed the structure of the
code with OpenAI Codex and Claude (Anthropic), which helped write parts of the Task 3 code, its
tests and this document; Harold and Lucas reviewed, tested and verified all of it.
