@echo off
rem ==========================================================================
rem COMPSYS303 Version B - start the traffic light on the DE2-115 with one command
rem
rem   Double-click, or from a Command Prompt:   VersionB\run_board.bat [cable]
rem   (cable defaults to USB-Blaster; "jtagconfig" lists the cable names)
rem
rem   1. quartus_pgm programs COMPSYS303_Lab1\output_files\COMPSYS303_Lab1_time_limited.sof
rem      over JTAG in a separate window. That window is the OpenCore Plus tether
rem      (Quartus Lite + Nios II/f): keep it open, closing it stops the Nios II.
rem   2. nios2-download -g COMPSYS303_Lab1\software\traffic_b\traffic_b.elf
rem      (run through the Nios II Command Shell)
rem   3. nios2-terminal: the JTAG UART console. Ctrl-C leaves it; the lights keep
rem      running while the tether window is open.
rem
rem   Needs Quartus Prime 18.1 (Lite is enough) with the Nios II EDS, the board
rem   powered, the USB-Blaster cable in the BLASTER port and RUN/PROG on RUN.
rem   Paths are relative to this file, as in the repository and in group_N.zip.
rem
rem AI Use Declaration: The design and all design decisions were made by Harold and Lucas.
rem This script was written with the assistance of a generative AI tool (Claude,
rem Anthropic), then reviewed, tested and verified by Harold and Lucas.
rem ==========================================================================
setlocal EnableExtensions
if "%~1"==":tether" goto :tether

set "SOF=%~dp0COMPSYS303_Lab1\output_files\COMPSYS303_Lab1_time_limited.sof"
set "ELFDIR=%~dp0COMPSYS303_Lab1\software\traffic_b"
set "CABLE=USB-Blaster"
if not "%~1"=="" set "CABLE=%~1"
set "TLOG=%TEMP%\cs303_run_board_tether.log"

rem ---------- tools: QUARTUS_ROOTDIR / SOPC_KIT_NIOS2 first, then the default installs ----------
set "QROOT="
if defined QUARTUS_ROOTDIR if exist "%QUARTUS_ROOTDIR%\bin64\quartus_pgm.exe" set "QROOT=%QUARTUS_ROOTDIR%"
if not defined QROOT if exist "C:\intelFPGA_lite\18.1\quartus\bin64\quartus_pgm.exe" set "QROOT=C:\intelFPGA_lite\18.1\quartus"
if not defined QROOT if exist "C:\intelFPGA\18.1\quartus\bin64\quartus_pgm.exe" set "QROOT=C:\intelFPGA\18.1\quartus"
if not defined QROOT (
  echo ERROR: Quartus not found. Set QUARTUS_ROOTDIR, for example C:\intelFPGA_lite\18.1\quartus
  goto :failed
)
set "QBIN=%QROOT%\bin64"
set "NIOS2EDS="
if defined SOPC_KIT_NIOS2 if exist "%SOPC_KIT_NIOS2%\Nios II Command Shell.bat" set "NIOS2EDS=%SOPC_KIT_NIOS2%"
if not defined NIOS2EDS for %%D in ("%QROOT%\..\nios2eds") do if exist "%%~fD\Nios II Command Shell.bat" set "NIOS2EDS=%%~fD"
if not defined NIOS2EDS (
  echo ERROR: Nios II EDS not found. Set SOPC_KIT_NIOS2, for example C:\intelFPGA_lite\18.1\nios2eds
  goto :failed
)

rem ---------- files (paths are echoed outside ( ) blocks: a folder may be named "group_14 (1)") ----------
if exist "%SOF%" goto :have_sof
echo ERROR: missing %SOF%
goto :failed
:have_sof
if exist "%ELFDIR%\traffic_b.elf" goto :have_elf
echo ERROR: missing %ELFDIR%\traffic_b.elf
echo        Build it first: see README.md, Running Version B - Build.
goto :failed
:have_elf
tasklist /fi "imagename eq quartus_pgm.exe" 2>nul | find /i "quartus_pgm.exe" >nul
if not errorlevel 1 (
  echo ERROR: quartus_pgm.exe is already running - an earlier tether or Programmer session.
  echo        Close that window first, then run run_board.bat again.
  goto :failed
)

rem ---------- 1. program the .sof, tether in its own window ----------
echo [1/3] Programming the .sof over JTAG, cable %CABLE%
echo       %SOF%
if exist "%TLOG%" del "%TLOG%"
start "COMPSYS303 OpenCore Plus tether - KEEP OPEN" cmd /c ""%~f0" :tether"
set /a WAITED=0
:wait_cfg
ping -n 2 127.0.0.1 >nul
set /a WAITED+=1
findstr /c:"Configuration succeeded" "%TLOG%" >nul 2>&1 && goto :configured
findstr /b /c:"Error" "%TLOG%" >nul 2>&1 && goto :pgm_error
if %WAITED% geq 60 goto :pgm_error
goto :wait_cfg

:configured
type "%TLOG%"
echo.
echo       FPGA configured. The tether window must stay open from now on.
ping -n 3 127.0.0.1 >nul

rem ---------- 2. download and start the program ----------
echo.
echo [2/3] nios2-download -g traffic_b.elf
pushd "%ELFDIR%"
call "%NIOS2EDS%\Nios II Command Shell.bat" nios2-download -g traffic_b.elf
set "RC=%ERRORLEVEL%"
popd
if not "%RC%"=="0" (
  echo ERROR: nios2-download failed, exit code %RC%. Is the tether window still open?
  goto :failed
)

rem ---------- 3. console ----------
echo.
echo [3/3] nios2-terminal - Ctrl-C to leave. The lights keep running while the tether window is open.
echo.
"%QBIN%\nios2-terminal.exe"
echo.
echo nios2-terminal closed. The traffic light keeps running while the tether window is open:
echo close that window to stop it. To start again, close it and run run_board.bat again.
endlocal
exit /b 0

:pgm_error
echo.
if exist "%TLOG%" type "%TLOG%"
echo.
echo ERROR: the .sof was not configured. Check: board powered, USB-Blaster cable in the BLASTER
echo        port, RUN/PROG on RUN, no other program using the USB-Blaster, cable name %CABLE%.
echo        Close the tether window before trying again.
goto :failed

:failed
echo run_board.bat FAILED.
pause
endlocal
exit /b 1

rem ---------- tether window: runs until it is closed or the JTAG link breaks ----------
:tether
echo This window holds the OpenCore Plus tether for the time-limited .sof
echo (Quartus Lite cannot make a licence-free image of a Nios II/f design).
echo KEEP IT OPEN while you use the board: closing it stops the Nios II.
echo quartus_pgm messages go to %TLOG%
echo.
"%QBIN%\quartus_pgm.exe" -c "%CABLE%" -m jtag -o "p;%SOF%" > "%TLOG%" 2>&1
echo.
echo quartus_pgm has ended - the tether is gone and the Nios II has stopped:
type "%TLOG%"
pause
exit /b
