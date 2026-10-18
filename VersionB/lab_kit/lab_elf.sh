# COMPSYS303 Version B - step 6 of lab_build.bat, run inside the Nios II command shell.
# Regenerates the BSP from the freshly generated nios2_system.sopcinfo and builds traffic_b.elf.
# Usage: lab_elf.sh <kit folder>
#
# AI Use Declaration: The design and all design decisions were made by Harold and Lucas.
# This build script was written with the assistance of a generative AI tool (Claude,
# Anthropic), then reviewed, tested and verified by Harold and Lucas.
set -e
KIT="$1"
echo "== nios2-bsp-generate-files"
cd "$KIT/software/traffic_b_bsp"
nios2-bsp-generate-files --settings=settings.bsp --bsp-dir=.
echo "== make BSP"
make
echo "== make traffic_b"
cd "$KIT/software/traffic_b"
make
cp traffic_b.elf "$KIT/output_files/traffic_b.elf"
nios2-elf-size traffic_b.elf
