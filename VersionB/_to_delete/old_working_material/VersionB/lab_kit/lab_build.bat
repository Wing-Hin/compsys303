@echo off
rem ==========================================================================
rem COMPSYS303 Version B - licensed lab build (Quartus Prime 18.1 with a Nios II licence)
rem
rem   Double-click, or run from a Command Prompt in this folder:   lab_build.bat
rem   Steps: 0 version check, 1 Qsys HDL, 2 full compile, 3 LICENCE CHECK,
rem          4 .pof (EPCS64), 5 .sopcinfo, 6 BSP + traffic_b.elf (if Nios II EDS), 7 take-home list
rem   Everything is logged to lab_build_log.txt in this folder.
rem
rem AI Use Declaration: The design and all design decisions were made by Harold and Lucas.
rem This build script was written with the assistance of a generative AI tool (Claude,
rem Anthropic), then reviewed, tested and verified by Harold and Lucas.
rem ==========================================================================
setlocal EnableExtensions EnableDelayedExpansion
cd /d "%~dp0"
set "KIT=%~dp0"
set "KIT=%KIT:~0,-1%"
set "LOG=%KIT%\lab_build_log.txt"
echo COMPSYS303 lab build  %DATE% %TIME%  on %COMPUTERNAME%  in %KIT%> "%LOG%"

rem ---------- locate Quartus: QUARTUS_ROOTDIR first, then PATH ----------
set "QROOT="
if defined QUARTUS_ROOTDIR if exist "%QUARTUS_ROOTDIR%\bin64\quartus_sh.exe" set "QROOT=%QUARTUS_ROOTDIR%"
if defined QROOT goto :found_quartus
for %%X in (quartus_sh.exe) do set "QSH=%%~$PATH:X"
if not defined QSH goto :no_quartus
for %%D in ("%QSH%") do set "QROOT=%%~dpD.."
:found_quartus
set "QBIN=%QROOT%\bin64"
call :log "Quartus found in %QROOT%"

rem ---------- 0. version ----------
call :step "0. Quartus version"
"%QBIN%\quartus_sh.exe" --version >> "%LOG%" 2>&1
findstr /c:"Version " "%LOG%"
findstr /c:"Version 18.1" "%LOG%" >nul
if errorlevel 1 ( call :log "ABORT: this is not Quartus Prime 18.1 - use the 18.1 install the course uses." & goto :failed )

rem ---------- 1. Qsys HDL ----------
call :step "1. qsys-generate nios2_system.qsys (Verilog synthesis files)"
set "QSYSGEN=%QROOT%\sopc_builder\bin\qsys-generate.exe"
if not exist "%QSYSGEN%" ( call :log "ERROR: qsys-generate not found at %QSYSGEN%" & goto :failed )
"%QSYSGEN%" nios2_system.qsys --synthesis=VERILOG --output-directory=nios2_system >> "%LOG%" 2>&1
if errorlevel 1 ( call :log "ERROR: qsys-generate failed - see lab_build_log.txt. Missing IP? See LAB_CHECKLIST.md" & goto :failed )
if not exist "nios2_system\synthesis\nios2_system.qip" ( call :log "ERROR: nios2_system\synthesis\nios2_system.qip was not generated" & goto :failed )
call :log "Qsys HDL generated."

rem ---------- 2. full compile ----------
call :step "2. quartus_sh --flow compile COMPSYS303_Lab1   (several minutes)"
"%QBIN%\quartus_sh.exe" --flow compile COMPSYS303_Lab1 >> "%LOG%" 2>&1
if errorlevel 1 ( call :log "ERROR: compilation failed - see lab_build_log.txt" & goto :failed )
findstr /c:"Full Compilation was successful" "%LOG%"

rem ---------- 3. LICENCE CHECK ----------
call :step "3. LICENCE CHECK"
set "LICFAIL="
if exist "output_files\*_time_limited.sof" (
  set "LICFAIL=1"
  call :log "LICENCE CHECK FAILED: output_files contains a *_time_limited.sof (OpenCore Plus evaluation build)."
)
rem Evaluation-only messages and the IP table's "License Type = OpenCore Plus" column.
rem (The analysis-settings row "Intel FPGA IP Evaluation Mode ; Enable" is in every build, so it is not used.)
findstr /i /n /c:"Evaluation Mode feature is turned on" /c:"will use the Intel FPGA IP Evaluation Mode" /c:"will stop functioning" /c:"Hardware Evaluation feature is turned on" output_files\*.rpt > "%KIT%\licence_check_hits.txt" 2>nul
findstr /i /n /r /c:"; *OpenCore Plus *;" output_files\*.rpt >> "%KIT%\licence_check_hits.txt" 2>nul
set "HITS=0"
for %%A in ("%KIT%\licence_check_hits.txt") do set "HITS=%%~zA"
if not "%HITS%"=="0" (
  set "LICFAIL=1"
  call :log "LICENCE CHECK FAILED: the compile reports mention Evaluation Mode / OpenCore Plus (first lines below, all in licence_check_hits.txt):"
  findstr /n "^" "%KIT%\licence_check_hits.txt" | findstr /b "[1-5]:"
  findstr /n "^" "%KIT%\licence_check_hits.txt" | findstr /b "[1-5]:" >> "%LOG%"
)
if defined LICFAIL (
  call :log "*****************************************************************"
  call :log "*  NOT A LICENSED BUILD - no .pof can be made from this .sof.    *"
  call :log "*  Check Tools - License Setup for the Nios II licence 6AF7_00A2 *"
  call :log "*  and ask the TA. Do NOT switch to Nios II/e without asking.    *"
  call :log "*****************************************************************"
  goto :failed
)
if not exist "output_files\COMPSYS303_Lab1.sof" ( call :log "ERROR: output_files\COMPSYS303_Lab1.sof not found" & goto :failed )
call :log "LICENSED BUILD OK"

rem ---------- 4. .pof ----------
call :step "4. quartus_cpf: .sof to .pof (EPCS64)"
"%QBIN%\quartus_cpf.exe" -c -d EPCS64 output_files\COMPSYS303_Lab1.sof output_files\COMPSYS303_Lab1.pof >> "%LOG%" 2>&1
if errorlevel 1 ( call :log "ERROR: quartus_cpf failed - see lab_build_log.txt" & goto :failed )
for %%F in ("output_files\COMPSYS303_Lab1.pof") do call :log ".pof written: %%~zF bytes (expect several MB)"

rem ---------- 5. .sopcinfo ----------
call :step "5. copy nios2_system.sopcinfo next to the .pof"
copy /y "nios2_system.sopcinfo" "output_files\nios2_system.sopcinfo" >> "%LOG%" 2>&1
if errorlevel 1 ( call :log "ERROR: nios2_system.sopcinfo missing" & goto :failed )

rem ---------- 6. BSP + traffic_b.elf (optional) ----------
call :step "6. BSP and traffic_b.elf (needs the Nios II EDS)"
set "NEDS=%SOPC_KIT_NIOS2%"
if not defined NEDS set "NEDS=%QROOT%\..\nios2eds"
set "NBASH=%QBIN%\cygwin\bin\bash.exe"
if not exist "%NEDS%\sdk2\bin\nios2-bsp-generate-files.exe" goto :no_eds
if not exist "%NEDS%\nios2_command_shell.sh" goto :no_eds
if not exist "%NBASH%" goto :no_eds
set "SHELLOPTS=igncr"
set "CYGWIN=nodosfilewarning"
set "NSH=%NEDS:\=/%/nios2_command_shell.sh"
set "KITU=%KIT:\=/%"
"%NBASH%" -c "'%NSH%' bash '%KITU%/lab_elf.sh' '%KITU%'" >> "%LOG%" 2>&1
if exist "output_files\traffic_b.elf" ( call :log "traffic_b.elf built and copied to output_files" ) else ( call :log "WARNING: .elf build failed - see lab_build_log.txt; the .elf will be rebuilt at home" )
goto :takehome
:no_eds
call :log "Nios II EDS not found - .elf will be rebuilt at home"

rem ---------- 7. take-home list ----------
:takehome
call :step "7. TAKE THESE FILES HOME (USB / OneDrive)"
for %%F in (output_files\COMPSYS303_Lab1.sof output_files\COMPSYS303_Lab1.pof output_files\nios2_system.sopcinfo output_files\traffic_b.elf lab_build_log.txt) do (
  if exist "%%F" ( call :log "   %%~zF bytes   %%F" ) else ( call :log "   (not built)   %%F" )
)
for %%F in (output_files\*.flow.rpt) do call :log "   %%~zF bytes   %%F"
call :log "Simplest: copy the whole output_files folder and lab_build_log.txt."
call :log "BUILD FINISHED OK"
exit /b 0

:no_quartus
echo quartus_sh.exe was not found (QUARTUS_ROOTDIR is not set and it is not on PATH).>> "%LOG%"
echo.
echo  quartus_sh.exe was not found (QUARTUS_ROOTDIR is not set and it is not on PATH).
echo  Open the "Nios II Command Shell" (or "Quartus Prime 18.1 command prompt") from the
echo  Start menu, cd to this folder, and run lab_build.bat from there.
exit /b 2

:failed
call :log "BUILD FAILED - nothing to take home except lab_build_log.txt (show it to the TA)."
exit /b 1

rem ---------- helpers ----------
:step
echo.
echo ==== %~1
>> "%LOG%" echo.
>> "%LOG%" echo ==== %~1
exit /b 0

:log
echo %~1
>> "%LOG%" echo %~1
exit /b 0
