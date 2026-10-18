<#
COMPSYS 303 - build the submission zip group_<N>.zip from the repository.

  powershell -ExecutionPolicy Bypass -File VersionB\make_submission.ps1 -Group 7 -DryRun
  powershell -ExecutionPolicy Bypass -File VersionB\make_submission.ps1 -Group 7
  options: -IncludeElf (add traffic_b.elf), -Pof <path>, -Out <zip path>

Included (repository-relative paths are kept inside the zip):
  * the SCCharts: *_VersionA.sctx (root) and VersionB/*_VersionB.sctx
  * README.md
  * software/traffic_b and software/traffic_b_bsp sources, settings and Makefiles
    (no obj/, *.map, *.objdump, libhal_bsp.a; traffic_b.elf only with -IncludeElf)
  * nios2_system.sopcinfo
  * the .pof (default VersionB/COMPSYS303_Lab1/output_files/COMPSYS303_Lab1.pof) - REQUIRED
  * VersionB/evidence/ (board logs, B_summary.md, final_test_results.md, figures/, scripts)
    and Version A traces/check_ktrace.py wherever they are found under evidence/
  * VersionB/nios/ PC test sources (main.c copy, pc_test.c, pc_suite.c, pc_suite_print.h)
Excluded everywhere: db/, incremental_db/, .metadata/, obj/, Hello_lab1*, _to_delete/,
  board_test output, TASK3_EDGE_RESULTS.md, __pycache__/.

AI Use Declaration: The design and all design decisions were made by Harold and Lucas.
This packaging script was written with the assistance of a generative AI tool (Claude,
Anthropic), then reviewed, tested and verified by Harold and Lucas.
#>
param(
    [Parameter(Mandatory = $true)][int]$Group,
    [switch]$DryRun,
    [switch]$IncludeElf,
    [string]$Pof = "VersionB\COMPSYS303_Lab1\output_files\COMPSYS303_Lab1.pof",
    [string]$Out = ""
)
$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $PSScriptRoot
if (-not $Out) { $Out = Join-Path $root "group_$Group.zip" }

function Rel([string]$full) { return $full.Substring($root.Length + 1) }

$exclude = '\\(db|incremental_db|\.metadata|obj|_to_delete|__pycache__)\\|Hello_lab1|board_test\\output_files|TASK3_EDGE_RESULTS\.md$'

$files = New-Object System.Collections.Generic.List[string]
function Add-Files($items) { foreach ($i in $items) { if ($i -and (Rel $i.FullName) -notmatch $exclude) { $files.Add($i.FullName) } } }

# Charts
Add-Files (Get-ChildItem -Path $root -Filter "*_VersionA.sctx" -File)
Add-Files (Get-ChildItem -Path (Join-Path $root "VersionB") -Filter "*_VersionB.sctx" -File)
# README
Add-Files (Get-Item (Join-Path $root "README.md"))
# Nios II application and BSP
$sw = Join-Path $root "VersionB\COMPSYS303_Lab1\software"
Add-Files (Get-ChildItem -Path (Join-Path $sw "traffic_b") -Recurse -File -Force |
    Where-Object { $_.Extension -notin ".map", ".objdump", ".o", ".d" -and ($IncludeElf -or $_.Extension -ne ".elf") })
Add-Files (Get-ChildItem -Path (Join-Path $sw "traffic_b_bsp") -Recurse -File -Force |
    Where-Object { $_.Name -ne "libhal_bsp.a" -and $_.Extension -notin ".o", ".d" })
# System description
Add-Files (Get-Item (Join-Path $root "VersionB\COMPSYS303_Lab1\nios2_system.sopcinfo"))
# Evidence and PC test sources
Add-Files (Get-ChildItem -Path (Join-Path $root "VersionB\evidence") -Recurse -File)
Add-Files (Get-ChildItem -Path (Join-Path $root "VersionB\nios") -File | Where-Object { $_.Extension -in ".c", ".h" })

# The .pof is mandatory
$pofPath = if ([System.IO.Path]::IsPathRooted($Pof)) { $Pof } else { Join-Path $root $Pof }
$pofOk = Test-Path $pofPath
if ($pofOk) { $files.Add((Resolve-Path $pofPath).Path) }

$list = $files | Sort-Object -Unique
$total = 0
"Submission group_$Group.zip - " + $list.Count + " files" + $(if ($DryRun) { " (dry run)" } else { "" })
foreach ($f in $list) {
    $len = (Get-Item $f).Length
    $total += $len
    "{0,10:N0}  {1}" -f $len, (Rel $f)
}
"{0,10:N0}  bytes in total ({1:N1} MB, uncompressed)" -f $total, ($total / 1MB)

if (-not (Test-Path (Join-Path $root "VersionB\evidence\figures"))) { Write-Warning "evidence\figures\ not found (Part 9 creates it)." }
if (-not (Get-ChildItem -Path (Join-Path $root "VersionB\evidence") -Recurse -Filter "*.ktrace" -ErrorAction SilentlyContinue)) {
    Write-Warning "No Version A .ktrace traces under VersionB\evidence\ (and no check_ktrace.py)."
}
if (-not $pofOk) {
    Write-Host ""
    Write-Host "ERROR: .pof NOT FOUND: $pofPath" -ForegroundColor Red
    Write-Host "       Make it on a licensed lab PC (see README.md) and place it there, or pass -Pof <path>." -ForegroundColor Red
    if (-not $DryRun) { exit 1 }
}
if ($DryRun) { exit $(if ($pofOk) { 0 } else { 1 }) }

Add-Type -AssemblyName System.IO.Compression, System.IO.Compression.FileSystem
if (Test-Path $Out) { Remove-Item $Out -Confirm:$false }
$zip = [System.IO.Compression.ZipFile]::Open($Out, [System.IO.Compression.ZipArchiveMode]::Create)
try {
    foreach ($f in $list) {
        $entry = (Rel $f) -replace '\\', '/'
        [System.IO.Compression.ZipFileExtensions]::CreateEntryFromFile($zip, $f, $entry, [System.IO.Compression.CompressionLevel]::Optimal) | Out-Null
    }
} finally { $zip.Dispose() }
"Wrote $Out ({0:N1} MB)" -f ((Get-Item $Out).Length / 1MB)
