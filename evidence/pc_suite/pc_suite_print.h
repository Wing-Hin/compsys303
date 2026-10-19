/*
 * COMPSYS 303 Version B - force-included when compiling the generated
 * TrafficLight_B.c for pc_suite.c, so the chart's print(...) calls are
 * counted by pc_suite.c instead of written to the console. The generated
 * file itself is not modified.
 *
 * AI Use Declaration: Harold and Lucas designed the system and made all design decisions.
 * They discussed the structure of the code with Claude (Anthropic), which helped write
 * parts of this file; Harold and Lucas reviewed, tested and verified all of it.
 */
#include <stdio.h>
int suite_printf(const char *fmt, ...);
#define printf suite_printf
