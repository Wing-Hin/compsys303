# Fallback: switch the CPU to Nios II/e (only if no Nios II/f licence is available)

**Do not apply unless agreed.** Nios II/e is free in Quartus Lite, so the compile is not time-limited
and a `.pof` can be made without a licence. The cost is speed: /e has no pipeline, caches or hardware
multiplier, so the main loop runs several times slower than on /f, and all timing evidence must be
re-measured on the new CPU.

## 1. Change the CPU (one parameter)

`VersionB/COMPSYS303_Lab1/nios2_system.qsys`, module `cpu` (`altera_nios2_gen2`):

```
<parameter name="impl" value="Fast" />      becomes      <parameter name="impl" value="Tiny" />
```

Preferably make the change in the GUI so Platform Designer updates the dependent settings:
Tools > Platform Designer > open `nios2_system.qsys` > double-click `cpu` > **Main** tab >
select **Nios II/e** > Finish. The cache sizes, the bit-31 cache bypass and the hardware multiplier
settings no longer apply. Keep the reset and exception vectors on `sdram.s1` and keep every
peripheral, base address and IRQ unchanged. Check with **System > Show System With Platform Designer
Interconnect**, or compare the old and new `system.h` (step 4).

## 2. Regenerate and recompile the hardware

1. Platform Designer: **Generate > Generate HDL** (Synthesis: Verilog), then **File > Save**.
   Command line: `qsys-generate nios2_system.qsys --synthesis=VERILOG --output-directory=nios2_system`.
2. Quartus: **Processing > Start Compilation** (`quartus_sh --flow compile COMPSYS303_Lab1`).
3. Check `output_files` holds **`COMPSYS303_Lab1.sof`** with no `_time_limited` suffix, and that the
   map report has no "Evaluation Mode feature is turned on" warning. `lab_kit/lab_build.bat` step 3
   does exactly this check.
4. `.pof`: `quartus_cpf -c -d EPCS64 output_files\COMPSYS303_Lab1.sof output_files\COMPSYS303_Lab1.pof`.

## 3. Rebuild the software

```
cd VersionB/COMPSYS303_Lab1/software/traffic_b_bsp
nios2-bsp-generate-files --settings=settings.bsp --bsp-dir=.     # picks up the new CPU from the .sopcinfo
make clean && make
cd ../traffic_b
make clean && make
```

`main.c` and the chart need no change: the program does not depend on the caches (all I/O uses
`IORD`/`IOWR`), and the BSP compiler flags switch to software multiply automatically.

## 4. Check before re-measuring

- Diff `traffic_b_bsp/system.h` against the /f version: only the `ALT_CPU_*` / `NIOS2_*` CPU lines
  may change (implementation `"tiny"`, no caches). The base addresses of `keys`, `switches`,
  `leds_red`, `timer_0`, `timer_1`, `uart` and `jtag_uart`, and the IRQs, must be unchanged.
- `pc_suite` and the static checks (B1-B8) are unaffected.

## 5. Evidence that must be re-run on Nios II/e

Use new file names, so the Nios II/f evidence stays intact (for example `B_e_task1_10ms.txt`).

| Re-run | Why |
|---|---|
| **C1.1 / E2b baseline 10 ms**, at least 3 cycles | main timing result; the event counts must stay exactly 600/200/50 |
| **E2a 1 ms, E2c 100 ms** | the rate experiment. **1 ms may not keep up**: if the loop makes fewer than one tick per timer event, events queue in `pendingEvents`, phases stretch and E2a fails. Record the measured ticks per event; a backlog is a result to report, not something to hide |
| E3 300 ms, E4 rescale | cheap to repeat; show quantisation and rescaling are unchanged |
| Task 2/4 smoke test (one walk, one camera snapshot) | confirms the slower loop still samples the buttons and the camera dwell |
| D1-D3, `make_submission.ps1` | the submitted `.sof`/`.pof`/`.sopcinfo` are the /e build |

Then run `check_board_log.py`, `analyse_logs.py` and `export_figure_data.py`, update `B_summary.md`,
the figures, `report_facts.md` and `final_test_results.md`, and state in each log header which CPU was used.

## 6. Sentence for the report

> "Because the Quartus Prime Lite licence available to us does not cover the Nios II/f core (its
> build is an OpenCore Plus time-limited image that cannot be written to flash), the submitted
> hardware uses the free Nios II/e core. The SCChart and the timer-event interface are unchanged; we
> re-measured the timing on Nios II/e (Section X): at the 10 ms timer period the loop still makes about
> N reactions per timer event, while at 1 ms <result>."

## AI use

The design and all design decisions were made by Harold and Lucas. This fallback note was written
with the assistance of a generative AI tool (Claude, Anthropic), then reviewed by Harold and Lucas.
