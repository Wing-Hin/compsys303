/*
 * COMPSYS 303 Version B - force-included when compiling the generated
 * TrafficLight_B.c for pc_suite.c, so the chart's print(...) calls are
 * counted by pc_suite.c instead of written to the console. The generated
 * file itself is not modified.
 *
 * AI Use Declaration: The design and all design decisions were made by Harold and Lucas.
 * This test header was written with the assistance of a generative AI tool (Claude,
 * Anthropic), then reviewed, tested and verified by Harold and Lucas.
 */
#include <stdio.h>
int suite_printf(const char *fmt, ...);
#define printf suite_printf
