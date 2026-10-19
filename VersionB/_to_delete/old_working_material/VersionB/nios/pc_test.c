/*
 * COMPSYS 303 - Version B desktop rehearsal (no board needed).
 *
 * Runs the KIELER-generated chart code on the PC with a fake timer: one
 * timer event every EVENT_EVERY ticks, idle ticks in between, exactly like
 * the free-running loop on the Nios II. Prints every change of LEDR with the
 * number of timer events the previous phase lasted.
 *
 * Build (from VersionB/nios, gcc from MinGW or the Quartus/Nios shell):
 *     gcc -I../COMPSYS303_Lab1/software/traffic_b pc_test.c ^
 *         ../COMPSYS303_Lab1/software/traffic_b/TrafficLight_B.c -o pc_test
 *     ./pc_test
 *
 * Expected with TIMER_MS = 10 and the default time-outs:
 *     GR 600, YR 200, RR 50, RG 600, RY 200, RR 50 events per phase
 * (the very first phase can show one extra event, see the guide).
 *
 * AI Use Declaration: The design and all design decisions were made by Harold and Lucas.
 * This PC rehearsal harness was written with the assistance of a generative AI tool
 * (Claude, Anthropic), then reviewed, tested and verified by Harold and Lucas.
 */
#include <stdio.h>
#include <string.h>
#include "TrafficLight_B.h"

#define TIMER_MS     10      /* must match the chart */
#define EVENT_EVERY  7       /* one timer event every 7 ticks: 6 idle ticks between */
#define TOTAL_TICKS  300000L

int main(void)
{
    TickData d;
    memset(&d, 0, sizeof d);
    reset(&d);

    int  lastLEDR = -1;
    long events = 0, phaseStartEvent = 0;

    for (long i = 0; i < TOTAL_TICKS; i++) {
        d.timerTick = (i % EVENT_EVERY == 3);
        tick(&d);
        if (d.timerTick) events++;

        if (d.LEDR != lastLEDR) {
            long n = events - phaseStartEvent;
            printf("tick %7ld  LEDR %3d -> %3d  previous phase: %5ld events = %6ld ms\n",
                   i, lastLEDR, d.LEDR, n, n * TIMER_MS);
            lastLEDR = d.LEDR;
            phaseStartEvent = events;
        }
    }
    return 0;
}
