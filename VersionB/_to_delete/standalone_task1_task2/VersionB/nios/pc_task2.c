/*
 * COMPSYS 303 Version B - PC test of the standalone Task 2 chart
 * (VersionB/Task2_VersionB.sctx, cases P1-P7).
 *
 * Drives the KIELER-generated Task2_PedestrianTrafficLight_B code the way
 * main.c (CHART 2) does on the Nios II: one timer event every 7 ticks, button
 * presses held for several ticks. Every LEDR change is checked against the
 * legal values and changes of the board-log rules (Task 2 subset).
 *
 * Build and run (from VersionB/nios, gcc from MinGW), after generating the
 * chart with KIELER (Netlist-based Compilation (C)) into task2_gen/:
 *   gcc -O2 -Wall -Itask2_gen pc_task2.c task2_gen/Task2_PedestrianTrafficLight_B.c -o pc_task2
 *   ./pc_task2          (exit code 0 = every case passed)
 *
 * Default time-outs at TIMER_MS = 10: G 600, Y 200, R-R 50, walk 400 events;
 * a green with a walk ends 200 events after the walk.
 *
 * AI Use Declaration: All design decisions were made by Harold and Lucas. Harold and
 * Lucas discussed the structure with generative AI tools and implemented the project
 * by hand, with parts written with the assistance of Claude (Anthropic) and ChatGPT
 * (OpenAI). This test harness was written with the assistance of Claude (Anthropic),
 * then reviewed, tested and verified by Harold and Lucas.
 */
#include <stdio.h>
#include <string.h>
#include "Task2_PedestrianTrafficLight_B.h"

#define EVENT_EVERY 7
#define MAXTR 4000

typedef struct { int from, to; long events; } Tr;

static TickData d;
static long tickNo, events, phaseStart;
static int nsHold, ewHold, lastLEDR;
static Tr tr[MAXTR];
static int ntr, violations, caseFails, totalPass, totalFail;

static int legalChange(int a, int b)
{
    switch (a) {
    case -1:  return b == 33;
    case 33:  return b == 34 || b == 97;
    case 97:  return b == 33;
    case 34:  return b == 36;
    case 36:  return b == 12 || b == 140 || b == 33 || b == 97;
    case 12:  return b == 20 || b == 140;
    case 140: return b == 12;
    case 20:  return b == 36;
    }
    return 0;
}

static void simReset(void)
{
    memset(&d, 0, sizeof d);
    reset(&d);
    tickNo = events = phaseStart = 0;
    nsHold = ewHold = 0;
    lastLEDR = -1;
    ntr = violations = 0;
}

static void step(void)
{
    d.timerTick = (tickNo % EVENT_EVERY == 3);
    d.NSraised = nsHold > 0; if (nsHold > 0) nsHold--;
    d.EWraised = ewHold > 0; if (ewHold > 0) ewHold--;
    tick(&d);
    if (d.timerTick) events++;
    if (d.LEDR != lastLEDR) {
        if (!legalChange(lastLEDR, d.LEDR)) {
            violations++;
            printf("      tick %ld: illegal change %d -> %d\n", tickNo, lastLEDR, d.LEDR);
        }
        if (ntr < MAXTR) {
            tr[ntr].from = lastLEDR; tr[ntr].to = d.LEDR; tr[ntr].events = events - phaseStart;
            ntr++;
        }
        phaseStart = events;
        lastLEDR = d.LEDR;
    }
    tickNo++;
}

static int waitTr(int a, int b, long maxTicks)
{
    for (long i = 0; i < maxTicks; i++) {
        int n = ntr;
        step();
        if (ntr > n && (a == -2 || tr[ntr - 1].from == a) && (b == -2 || tr[ntr - 1].to == b))
            return 1;
    }
    return 0;
}

#define LONG 200000L
#define CHECK(cond, ...) do { if (!(cond)) { caseFails++; printf("      FAIL: "); printf(__VA_ARGS__); printf("\n"); } } while (0)

/* Duration (events) of the phase that ended with a -> b, searching from index i0. */
static long phase(int a, int b, int i0)
{
    for (int i = i0; i < ntr; i++)
        if (tr[i].from == a && tr[i].to == b) return tr[i].events;
    return -1;
}

static void P1(void)
{
    static const int seq[6][3] = {{33, 34, 600}, {34, 36, 200}, {36, 12, 50}, {12, 20, 600}, {20, 36, 200}, {36, 33, 50}};
    simReset();
    for (int k = 0; k < 18; k++) {
        const int *s = seq[k % 6];
        CHECK(waitTr(s[0], s[1], LONG), "no %d -> %d", s[0], s[1]);
        CHECK(tr[ntr - 1].events == s[2], "%d -> %d after %ld events, expected %d", s[0], s[1], tr[ntr - 1].events, s[2]);
    }
}

static void P2(void)
{
    simReset();
    CHECK(waitTr(36, 12, LONG), "no R-G");
    for (int i = 0; i < 1000; i++) step();
    nsHold = 5;                                         /* NS press in R-G */
    CHECK(waitTr(36, 97, LONG), "no NS walk at the next G-R");
    int i0 = ntr;
    CHECK(waitTr(33, 34, LONG), "no yellow after the walk");
    CHECK(phase(97, 33, i0) == 400 && phase(33, 34, i0) == 200, "walk %ld, rest of green %ld events (want 400, 200)",
          phase(97, 33, i0), phase(33, 34, i0));
}

static void P3(void)
{
    simReset();
    for (int i = 0; i < 1000; i++) step();
    ewHold = 5;                                         /* EW press in G-R */
    CHECK(waitTr(36, 140, LONG), "no EW walk at the next R-G");
    int i0 = ntr;
    CHECK(waitTr(12, 20, LONG), "no yellow after the walk");
    CHECK(phase(140, 12, i0) == 400 && phase(12, 20, i0) == 200, "walk %ld, rest of green %ld events (want 400, 200)",
          phase(140, 12, i0), phase(12, 20, i0));
}

static void P4(void)
{
    simReset();
    for (int i = 0; i < 1000; i++) step();
    nsHold = ewHold = 5;                                /* both in G-R */
    CHECK(waitTr(36, 140, LONG), "no EW walk");
    CHECK(waitTr(36, 97, LONG), "no NS walk at the following G-R");
}

static void P5(void)
{
    simReset();
    CHECK(waitTr(36, 12, LONG), "no R-G");
    nsHold = 3000;                                      /* held across a whole green */
    CHECK(waitTr(36, 97, LONG), "no NS walk");
    while (nsHold > 0) step();
    CHECK(waitTr(36, 33, LONG), "no plain G-R in the next cycle (one press served twice)");
}

static void P6(void)
{
    simReset();
    for (int i = 0; i < 700; i++) step();
    nsHold = 5;                                         /* NS press in its own green */
    int i0 = ntr;
    CHECK(waitTr(33, 34, LONG), "no yellow");
    CHECK(phase(33, 34, i0) == 600, "own green %ld events, expected 600 (no walk mid-green)", phase(33, 34, i0));
    CHECK(waitTr(36, 97, LONG), "walk not served at the next G-R");
}

static void P7(void)
{
    simReset();
    for (long i = 0; i < 300000; i++) {
        if (i % 2311 == 5) nsHold = 4;
        if (i % 3373 == 9) ewHold = 4;
        step();
    }
    CHECK(ntr > 50, "too few changes (%d)", ntr);
}

typedef struct { const char *id, *what; void (*fn)(void); } Case;
static const Case cases[] = {
    {"P1", "no presses, 3 cycles: 600/200/50 events", P1},
    {"P2", "NS press in R-G: next G-R 97 for 400, then 33 for 200", P2},
    {"P3", "EW press in G-R: next R-G 140 for 400, then 12 for 200", P3},
    {"P4", "both pressed together: both walks", P4},
    {"P5", "button held across a green: one walk", P5},
    {"P6", "NS press in its own green: walk at the next G-R", P6},
    {"P7", "300,000 ticks of periodic presses: legal changes only", P7},
};

int main(void)
{
    int n = (int) (sizeof cases / sizeof cases[0]);
    printf("pc_task2: Task2_PedestrianTrafficLight_B, timer event every %d ticks\n", EVENT_EVERY);
    for (int i = 0; i < n; i++) {
        caseFails = 0;
        printf("  %-3s %-58s\n", cases[i].id, cases[i].what);
        cases[i].fn();
        if (violations) { caseFails++; printf("      FAIL: %d illegal LEDR change(s)\n", violations); }
        printf("       -> %s\n", caseFails ? "FAIL" : "PASS");
        if (caseFails) totalFail++; else totalPass++;
    }
    printf("\nTOTAL: %d passed, %d failed, of %d\n", totalPass, totalFail, n);
    return totalFail ? 1 : 0;
}
