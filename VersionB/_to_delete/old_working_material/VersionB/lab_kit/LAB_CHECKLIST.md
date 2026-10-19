# Lab PC checklist - licensed build of the COMPSYS303 Version B hardware

Goal: a licensed `COMPSYS303_Lab1.sof` + `COMPSYS303_Lab1.pof` (+ `nios2_system.sopcinfo`, `traffic_b.elf`).
Copy the whole `lab_kit` folder (or unzip `lab_kit.zip`) to a local folder with **no spaces** in its path,
e.g. `C:\temp\lab_kit`.

## 1. Before building (2 minutes)

- [ ] Quartus **Help > About**: version **18.1**.
- [ ] Quartus **Tools > License Setup**: the licensed AMPP/MegaCore list includes **Nios II (6AF7_00A2)**.
- [ ] Optional: **Tools > Platform Designer** > open `nios2_system.qsys` - no missing components
      (it needs the University Program IP `altera_up_avalon_sys_sdram_pll`). Close without saving.

If License Setup shows **no Nios II licence**: ask the TA. **Do not switch to Nios II/e** without telling Harold
(see `FALLBACK_NIOS2E.md` in the repo).

## 2. Build (about 5 minutes)

- [ ] Double-click `lab_build.bat` (or run it from a Command Prompt in the folder).
      If it says `quartus_sh.exe was not found`: open **Nios II Command Shell** (or the Quartus 18.1
      command prompt) from the Start menu, `cd` to the folder, run `lab_build.bat` there.
- [ ] It must print **`LICENSED BUILD OK`**, then the `.pof` size (several MB), then **`BUILD FINISHED OK`**.
- [ ] If it prints `NOT A LICENSED BUILD` or `BUILD FAILED`: keep `lab_build_log.txt` and
      `licence_check_hits.txt`, show the TA.

## 3. Optional: on-board check (needs a DE2-115 + USB-Blaster)

- [ ] SW1..SW0 = 00 (all switches down).
- [ ] Programmer: Hardware = USB-Blaster, Mode = **JTAG**, add `output_files\COMPSYS303_Lab1.sof`, **Start**.
      No OpenCore Plus window should appear (licensed image, no tether).
- [ ] Nios II Command Shell in the kit folder: `nios2-download -g output_files/traffic_b.elf`, then `nios2-terminal`.
- [ ] Watch one Task 1 cycle: 600 / 200 / 50 timer events per phase in the console.

## 4. Optional: flash check (D2)

- [ ] The slide switch labelled **RUN/PROG** on the board (not one of SW0-SW17) to **PROG**.
- [ ] Programmer: Mode = **Active Serial Programming**, add `output_files\COMPSYS303_Lab1.pof`, tick
      Program/Configure, **Start**.
- [ ] RUN/PROG back to **RUN**, power-cycle the board: the FPGA loads from flash without programming.
- [ ] `nios2-download -g output_files/traffic_b.elf` - the lights cycle. (The `.pof` holds only the hardware;
      the program lives in SDRAM and must be downloaded after every power-up.)

## 5. Before leaving - COPY RESULTS TO USB / OneDrive

- [ ] `output_files\COMPSYS303_Lab1.sof`
- [ ] `output_files\COMPSYS303_Lab1.pof`
- [ ] `output_files\nios2_system.sopcinfo`
- [ ] `output_files\traffic_b.elf` (if step 6 built it)
- [ ] `output_files\*.flow.rpt` and `lab_build_log.txt`
- [ ] Easiest: copy the whole `output_files` folder + `lab_build_log.txt`. At home put them in
      `VersionB\lab_results\`.
- [ ] If you did section 3 or 4, note the result (and a photo of the board) for D2.
