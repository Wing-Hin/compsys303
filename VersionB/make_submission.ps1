<#
COMPSYS 303 - build the submission zip group_<N>.zip from the repository.

  powershell -ExecutionPolicy Bypass -File VersionB\make_submission.ps1 -Group 7 -DryRun
  powershell -ExecutionPolicy Bypass -File VersionB\make_submission.ps1 -Group 7
  powershell -ExecutionPolicy Bypass -File VersionB\make_submission.ps1 -Group 7 -Sof -IncludeElf
  options: -IncludeElf (add traffic_b.elf; fails if it is not built), -Pof <path>, -Out <zip path>,
           -Sof (submission with the board-tested time-limited .sof instead of a .pof, plus
                 VersionB/run_board.bat; see README "Programming files"),
           -Draft (no .pof yet: packs the time-limited .sof, writes group_<N>_draft.zip)

Included (repository-relative paths are kept inside the zip):
  * README.md (start here)
  * the SCCharts: VersionA/TrafficLight_VersionA.sctx and VersionB/TrafficLight_VersionB.sctx
  * docs/TASK3.md, docs/TASK4.md
  * software/traffic_b and software/traffic_b_bsp sources, settings and Makefiles
    (no obj/, *.map, *.objdump, libhal_bsp.a; traffic_b.elf only with -IncludeElf)
  * nios2_system.sopcinfo - REQUIRED
  * the .pof (default VersionB/COMPSYS303_Lab1/output_files/COMPSYS303_Lab1.pof) - REQUIRED,
    or with -Sof: VersionB/COMPSYS303_Lab1/output_files/COMPSYS303_Lab1_time_limited.sof - REQUIRED
    (must be the board-tested build: SHA-256 and Platform Designer generation ID are checked)
    and VersionB/run_board.bat
  * evidence/ (README.md index, final_test_results.md, report_facts.md, board_logs/, versionA/,
    figures/, pc_suite/, scripts/, kieler_warning/)
    including versionA/ (headless KIELER simulation of Version A: A_results.txt, traces)
Excluded everywhere: db/, incremental_db/, .metadata/, obj/, Hello_lab1*, _to_delete/,
  board_test output, TASK3_EDGE_RESULTS.md, __pycache__/.

AI Use Declaration: Harold and Lucas designed the system and made all design decisions. They
discussed the structure of the code with Claude (Anthropic), which helped write parts of
this file; Harold and Lucas reviewed, tested and verified all of it.
#>
param(
    [Parameter(Mandatory = $true)][int]$Group,
    [switch]$DryRun,
    [switch]$IncludeElf,
    [switch]$Draft,
    [switch]$Sof,
    [string]$Pof = "VersionB\COMPSYS303_Lab1\output_files\COMPSYS303_Lab1.pof",
    [string]$Out = ""
)
$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $PSScriptRoot
if ($Sof -and $Draft) { Write-Host "ERROR: -Sof and -Draft cannot be combined." -ForegroundColor Red; exit 1 }

# The .sof every board test in evidence/board_logs used (Quartus checksum 0x008CFF92, assembled
# Fri Aug 21 14:38:23 2026) and the Platform Designer generation it was compiled from
# (nios2_system.sopcinfo AUTO_GENERATION_ID = GENERATION_ID in the compile's .sld/.jdi).
$sofRel = "VersionB\COMPSYS303_Lab1\output_files\COMPSYS303_Lab1_time_limited.sof"
$testedSofSha256 = "D11CD8F5E0924DC9990390FE9C7BE95E8AF5F9531CFF8BD0CC3A2C47C62E6A10"
$testedGenerationId = "1786080893"
$sopcRel = "VersionB\COMPSYS303_Lab1\nios2_system.sopcinfo"
$zipName = if ($Draft) { "group_${Group}_draft.zip" } else { "group_$Group.zip" }
if (-not $Out) { $Out = Join-Path $root $zipName }

function Rel([string]$full) { return $full.Substring($root.Length + 1) }

$exclude = '\\(db|incremental_db|\.metadata|obj|_to_delete|__pycache__)\\|Hello_lab1|board_test\\output_files|TASK3_EDGE_RESULTS\.md$'

$files = New-Object System.Collections.Generic.List[string]
function Add-Files($items) { foreach ($i in $items) { if ($i -and (Rel $i.FullName) -notmatch $exclude) { $files.Add($i.FullName) } } }

# Charts
Add-Files (Get-Item (Join-Path $root "VersionA\TrafficLight_VersionA.sctx"))
Add-Files (Get-Item (Join-Path $root "VersionB\TrafficLight_VersionB.sctx"))
# README and the Version A Task 3 / Task 4 notes it refers to
Add-Files (Get-Item (Join-Path $root "README.md"))
Add-Files (Get-Item (Join-Path $root "docs\TASK3.md"))
Add-Files (Get-Item (Join-Path $root "docs\TASK4.md"))
# Nios II application and BSP
$sw = Join-Path $root "VersionB\COMPSYS303_Lab1\software"
if ($IncludeElf -and -not (Test-Path (Join-Path $sw "traffic_b\traffic_b.elf"))) {
    Write-Host "ERROR: -IncludeElf but traffic_b.elf is not built: $(Join-Path $sw 'traffic_b\traffic_b.elf')" -ForegroundColor Red
    exit 1
}
Add-Files (Get-ChildItem -Path (Join-Path $sw "traffic_b") -Recurse -File -Force |
    Where-Object { $_.Extension -notin ".map", ".objdump", ".o", ".d" -and ($IncludeElf -or $_.Extension -ne ".elf") })
Add-Files (Get-ChildItem -Path (Join-Path $sw "traffic_b_bsp") -Recurse -File -Force |
    Where-Object { $_.Name -ne "libhal_bsp.a" -and $_.Extension -notin ".o", ".d" })
# System description (required in every mode)
$sopcPath = Join-Path $root $sopcRel
if (-not (Test-Path $sopcPath)) { Write-Host "ERROR: .sopcinfo NOT FOUND: $sopcPath" -ForegroundColor Red; exit 1 }
Add-Files (Get-Item $sopcPath)
# Evidence and PC test sources
Add-Files (Get-ChildItem -Path (Join-Path $root "evidence") -Recurse -File)

# -Sof: the submission carries the board-tested time-limited .sof (Quartus Lite cannot make a
# .pof of a Nios II/f design) and run_board.bat. It must be byte-identical to the tested image
# and the .sopcinfo must come from the same Platform Designer generation.
# Otherwise the .pof is mandatory for the real submission. -Draft packs the time-limited
# development .sof in its place so the rest of the package can be checked early.
$pofOk = $false
if ($Sof) {
    $sofPath = Join-Path $root $sofRel
    if (-not (Test-Path $sofPath)) { Write-Host "ERROR: .sof NOT FOUND: $sofPath" -ForegroundColor Red; exit 1 }
    $sofSha = (Get-FileHash -Algorithm SHA256 -LiteralPath $sofPath).Hash
    if ($sofSha -ne $testedSofSha256) {
        Write-Host "ERROR: $sofRel is not the board-tested .sof" -ForegroundColor Red
        Write-Host "       SHA-256 $sofSha, expected $testedSofSha256" -ForegroundColor Red
        exit 1
    }
    $genId = if ((Get-Content -Raw -LiteralPath $sopcPath) -match '<parameter name="AUTO_GENERATION_ID">\s*<type>[^<]*</type>\s*<value>(\d+)</value>') { $Matches[1] } else { "(none)" }
    if ($genId -ne $testedGenerationId) {
        Write-Host "ERROR: $sopcRel generation ID $genId does not match the .sof build ($testedGenerationId)" -ForegroundColor Red
        exit 1
    }
    $files.Add($sofPath)
    $runBoard = Join-Path $root "VersionB\run_board.bat"
    if (-not (Test-Path $runBoard)) { Write-Host "ERROR: VersionB\run_board.bat NOT FOUND" -ForegroundColor Red; exit 1 }
    $files.Add($runBoard)
} else {
    $pofPath = if ([System.IO.Path]::IsPathRooted($Pof)) { $Pof } else { Join-Path $root $Pof }
    $pofOk = Test-Path $pofPath
    if ($pofOk) { $files.Add((Resolve-Path $pofPath).Path) }
}
if ($Draft -and -not $pofOk) {
    $draftSof = Join-Path $root $sofRel
    if (Test-Path $draftSof) { $files.Add($draftSof) }
}

$list = $files | Sort-Object -Unique
$total = 0
"Submission $zipName - " + $list.Count + " files" + $(if ($DryRun) { " (dry run)" } else { "" })
foreach ($f in $list) {
    $len = (Get-Item $f).Length
    $total += $len
    "{0,10:N0}  {1}" -f $len, (Rel $f)
}
"{0,10:N0}  bytes in total ({1:N1} MB, uncompressed)" -f $total, ($total / 1MB)

if (-not (Test-Path (Join-Path $root "evidence\figures"))) { Write-Warning "evidence\figures\ not found." }
if (-not (Test-Path (Join-Path $root "evidence\versionA\A_results.txt"))) {
    Write-Warning "No Version A simulation evidence (run evidence\versionA\run_versionA_sim.py)."
}
if ($Sof) {
    ""
    "Programming file: board-tested time-limited .sof (SHA-256 $sofSha), .sopcinfo generation ID $genId"
    if (-not $IncludeElf) { Write-Warning "run_board.bat needs traffic_b.elf: add -IncludeElf for the submission." }
} elseif (-not $pofOk -and $Draft) {
    Write-Host ""
    Write-Host "DRAFT: no .pof - the time-limited .sof is packed instead. NOT FOR SUBMISSION." -ForegroundColor Yellow
} elseif (-not $pofOk) {
    Write-Host ""
    Write-Host "ERROR: .pof NOT FOUND: $pofPath" -ForegroundColor Red
    Write-Host "       Make it on a licensed lab PC (see README.md) and place it there, or pass -Pof <path>." -ForegroundColor Red
    Write-Host "       (-Draft builds a check package with the time-limited .sof instead.)" -ForegroundColor Red
    if (-not $DryRun) { exit 1 }
}
if ($DryRun) { exit $(if ($Sof -or $pofOk -or $Draft) { 0 } else { 1 }) }

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
