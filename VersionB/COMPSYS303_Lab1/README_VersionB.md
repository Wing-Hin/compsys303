# Version B hardware and Nios II software (DE2-115)

This folder is the Lab 1 Nios II system reused as the hardware for Version B of the traffic-light assignment. Version B runs `TrafficLight_VersionB.sctx` (Tasks 1–4) on the Nios II, with the Nios II interval timer as the external time reference (multiform time).

## Hardware (unchanged from Lab 1)

`nios2_system.qsys`, Nios II/f at 50 MHz, program in SDRAM.

| Component | Used by Version B for |
|---|---|
| `timer_0` (1 ms) | HAL system clock: `alt_alarm` raises one `timerTick` every `TIMER_PERIOD_MS` (10 ms) |
| `timer_1` (1 ms) | HAL timestamp timer: independent stopwatch for the evidence log |
| `keys` (KEY2..0) | KEY0 = NS pedestrian, KEY1 = EW pedestrian, KEY2 = vehicle enter/leave |
| `switches` (SW17..0) | SW1..0 = task select (00 = Task 1, 01 = Task 2, 10 = Task 3, 11 = Task 4) |
| `leds_red` (LEDR17..0) | LEDR5..0 = traffic lamps (Table 1), LEDR6 = NS walk, LEDR7 = EW walk |
| `uart` (RS-232, 115200 8N1) | Task 3 configuration packets `#,#,#,#,#,#\n` (integer seconds) |
| `jtag_uart` | stdout: Task 4 messages and the timing log |
| `leds_green`, `lcd` | not used |

KEY3 is the system reset (`reset_reset_n`).

Top level: `COMPSYS303_Lab1.bdf`, with pins from `DE2_115_pin_assignments.csv` in `COMPSYS303_Lab1.qsf`.

## Tidy-up applied for Version B

- The top-level schematic now lives in the project folder (`COMPSYS303_Lab1.bdf`) instead of `db/`, which Quartus deletes on *Project → Clean Project*. The `.qsf` points to it.
- The SDRAM clock output pin is renamed to `DRAM_CLK`, so the standard pin assignment binds. The workaround assignment to `sdram_pll_sdram_clk_clk` was removed from the `.qsf`.
- The LCD backlight pin typo `LCD_BNON` is corrected to `LCD_BLON`. It was previously left unassigned.

These three changes take effect at the next Quartus compile. The existing `output_files/COMPSYS303_Lab1_time_limited.sof` was built before them and is still valid for development.

## Licence note

The `.sof` is **time-limited** (OpenCore Plus) because Quartus Lite has no Nios II/f licence. It runs only while the board stays connected to the Programmer, with the OpenCore Plus window open, and no `.pof` can be produced from it. For the submission, recompile `COMPSYS303_Lab1.qpf` on a licensed lab PC to get `COMPSYS303_Lab1.sof`, then convert it with File → Convert Programming Files → `.pof`, EPCS64, Active Serial.

## Software

| Project | Purpose |
|---|---|
| `software/traffic_b` | Version B application: `main.c` + KIELER-generated `TrafficLight_B.c/.h` |
| `software/traffic_b_bsp` | BSP: `sys_clk_timer = timer_0`, `timestamp_timer = timer_1`, stdio = `jtag_uart` |
| `software/Hello_lab1`, `Hello_lab1_bsp` | Lab 1/2 reference (ABRO demo). Delete once traffic_b runs |

`traffic_b` and `traffic_b_bsp` were created as copies of the Lab 1 projects, renamed, with these changes:

- BSP: `hal.timestamp_timer` set to `timer_1` in `settings.bsp`, and `ALT_TIMESTAMP_CLK` set to `TIMER_1` in `system.h`.
- App: the Makefile builds `main.c` + `TrafficLight_B.c` into `traffic_b.elf` against `../traffic_b_bsp`.

First-time setup in Nios II SBT: File → Import → General → Existing Projects into Workspace → root `software\` → tick `traffic_b` and `traffic_b_bsp`, but do not copy them into the workspace. Then right-click `traffic_b_bsp` → Nios II → Generate BSP.

## Run

1. Quartus Programmer → USB-Blaster → program the `.sof` (keep the OpenCore Plus window open).
2. Nios II SBT → build `traffic_b_bsp`, then `traffic_b` → Run As → Nios II Hardware. Tick both *Ignore mismatched system ID / timestamp* boxes, because there is no sysid component.
3. Watch LEDR and the Nios II Console.

## AI use

The tidy-up of this folder, `main.c` and this README were prepared with the assistance of a generative AI tool (Claude, Anthropic), then reviewed and tested by Harold and Lucas.
