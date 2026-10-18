/*
 * COMPSYS 303 Version B - scripted PC test suite (test B8, cases S1-S29).
 *
 * Drives the KIELER-generated TrafficLight_B code exactly as main.c does on the
 * Nios II, with no board and no human:
 *   - one timer event every 7 ticks (6 idle ticks in between);
 *   - button "presses" are held for several ticks;
 *   - UART characters are fed one per tick, and only when configReady was
 *     true after the previous tick (the same handshake as main.c).
 * Every tick is also checked against the board-log rules (test plan Part II,
 * section 0): legal LEDR values, legal LEDR changes, and activeTask may only
 * change inside an all-red (on a tick that starts or ends with LEDR 36).
 * Each case then asserts its own outcome.
 *
 * Build and run (from VersionB/nios, gcc from MinGW):
 *   gcc -O2 -Wall -c -include pc_suite_print.h -I../COMPSYS303_Lab1/software/traffic_b ^
 *       ../COMPSYS303_Lab1/software/traffic_b/TrafficLight_B.c -o TrafficLight_B_suite.o
 *   gcc -O2 -Wall -I../COMPSYS303_Lab1/software/traffic_b pc_suite.c TrafficLight_B_suite.o -o pc_suite
 *   ./pc_suite          (exit code 0 = every case passed)
 *
 * Default time-outs at TIMER_MS = 10: G 600, Y 200, R-R 50, walk 400,
 * camera dwell 100 timer events.
 *
 * AI Use Declaration: The design and all design decisions were made by Harold and Lucas.
 * This test suite was written with the assistance of a generative AI tool (Claude,
 * Anthropic), then reviewed, tested and verified by Harold and Lucas.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "TrafficLight_B.h"

/* ------------------------------------------------------------------ */
/* Chart print() capture (TrafficLight_B.c is built with pc_suite_print.h) */
static int msgActivated, msgSnapshot, msgLeft;

int suite_printf(const char *fmt, ...)
{
    char buf[160];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    if (strstr(buf, "Camera activated")) msgActivated++;
    else if (strstr(buf, "Snapshot taken")) msgSnapshot++;
    else if (strstr(buf, "Vehicle left")) msgLeft++;
    return (int) strlen(buf);
}

/* ------------------------------------------------------------------ */
/* Simulated board (the main.c loop)                                    */
#define EVENT_EVERY 7
#define MAXTR 400000
#define MAXREC 256

typedef struct { int from, to; long events, tick; } Tr;

static TickData d;
static long tickNo, events;
static int taskIn, nsHold, ewHold, carHold, noTimer, readyPrev;
static char uart[8192];
static size_t uartLen, uartPos;
static int lastLEDR;
static long phaseStart;
static Tr tr[MAXTR];
static int ntr;
static long actTick[MAXREC], actEv[MAXREC], snapTick[MAXREC], snapEv[MAXREC];
static int actLEDR[MAXREC], nact, nsnap, nleft;
static int appliedT1[MAXREC], appliedLEDR[MAXREC], napplied;
static long violations;
static char firstViolation[200];

static void violation(const char *fmt, ...)
{
    va_list ap;
    if (violations++ == 0) {
        va_start(ap, fmt);
        vsnprintf(firstViolation, sizeof firstViolation, fmt, ap);
        va_end(ap);
    }
}

static int legalValue(int v)
{
    return v == 33 || v == 34 || v == 36 || v == 12 || v == 20 || v == 97 || v == 140;
}

static int legalChange(int a, int b)
{
    switch (a) {
    case -1:  return b == 33;
    case 33:  return b == 34 || b == 97;
    case 97:  return b == 33 || (b == 34 && d.configApplied > 0);
    case 34:  return b == 36;
    case 36:  return b == 12 || b == 140 || b == 33 || b == 97;
    case 12:  return b == 20 || b == 140;
    case 140: return b == 12 || (b == 20 && d.configApplied > 0);
    case 20:  return b == 36;
    }
    return 0;
}

static void simReset(void)
{
    memset(&d, 0, sizeof d);
    reset(&d);
    tickNo = events = 0;
    taskIn = 1;
    nsHold = ewHold = carHold = noTimer = readyPrev = 0;
    uartLen = uartPos = 0;
    lastLEDR = -1;
    phaseStart = 0;
    ntr = nact = nsnap = nleft = napplied = 0;
    msgActivated = msgSnapshot = msgLeft = 0;
    violations = 0;
    firstViolation[0] = 0;
}

/* One tick: sensor stage, tick(&d), then bookkeeping and rule checks. */
static void step(void)
{
    int prevActive = d.activeTask, prevApplied = d.configApplied, startLEDR = d.LEDR;
    int a0 = msgActivated, s0 = msgSnapshot, l0 = msgLeft;

    d.timerTick = noTimer ? 0 : (tickNo % EVENT_EVERY == 3);
    d.task = taskIn;
    d.NSraised = nsHold > 0;       if (nsHold > 0) nsHold--;
    d.EWraised = ewHold > 0;       if (ewHold > 0) ewHold--;
    d.vehicleButton = carHold > 0; if (carHold > 0) carHold--;
    d.configValid = 0;
    if (readyPrev && uartPos < uartLen) {          /* main.c: one byte, only when ready */
        d.configChar = (unsigned char) uart[uartPos++];
        d.configValid = 1;
    }

    tick(&d);

    readyPrev = d.configReady;
    if (d.timerTick) events++;
    /* Mode changes happen inside the all-red. Entering R-R (Y -> RR -> Select)
     * and leaving a finished R-R (Select -> Config -> Exit) are immediate, so
     * the change may fall on the tick that enters or the tick that leaves
     * the all-red: the tick must START or END with LEDR 36. */
    if (tickNo > 0 && d.activeTask != prevActive && startLEDR != 36 && d.LEDR != 36)
        violation("tick %ld: activeTask %d -> %d on a tick %d -> %d without all-red",
                  tickNo, prevActive, d.activeTask, startLEDR, d.LEDR);
    if (d.configApplied != prevApplied && napplied < MAXREC) {
        appliedT1[napplied] = d.t1;
        appliedLEDR[napplied++] = d.LEDR;
    }
    if (d.LEDR != lastLEDR) {
        if (!legalValue(d.LEDR)) violation("tick %ld: illegal LEDR %d", tickNo, d.LEDR);
        if (!legalChange(lastLEDR, d.LEDR))
            violation("tick %ld: illegal change %d -> %d", tickNo, lastLEDR, d.LEDR);
        if (ntr < MAXTR) {
            tr[ntr].from = lastLEDR; tr[ntr].to = d.LEDR;
            tr[ntr].events = events - phaseStart; tr[ntr].tick = tickNo;
            ntr++;
        }
        phaseStart = events;
        lastLEDR = d.LEDR;
    }
    if (msgActivated > a0 && nact < MAXREC) {
        actTick[nact] = tickNo; actEv[nact] = events; actLEDR[nact++] = d.LEDR;
    }
    if (msgSnapshot > s0 && nsnap < MAXREC) {
        snapTick[nsnap] = tickNo; snapEv[nsnap++] = events;
    }
    if (msgLeft > l0) nleft++;
    tickNo++;
}

static void runTicks(long n) { while (n-- > 0) step(); }

static void runEvents(long n)
{
    long target = events + n;
    while (events < target) step();
}

/* Step until a new transition a -> b is recorded (a or b may be -2 = any). */
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

static Tr *lastTr(void) { return &tr[ntr - 1]; }

static void send(const char *s)
{
    size_t n = strlen(s);
    if (uartPos == uartLen) uartPos = uartLen = 0;
    if (uartLen + n < sizeof uart) {
        memcpy(uart + uartLen, s, n);
        uartLen += n;
    }
}

/* Index of the first transition a -> b at or after index k, or -1. */
static int findTr(int a, int b, int k)
{
    for (int i = k; i < ntr; i++)
        if (tr[i].from == a && tr[i].to == b) return i;
    return -1;
}

/* ------------------------------------------------------------------ */
/* Test framework                                                       */
static int caseFails, totalPass, totalFail;

#define CHECK(cond, ...) do { if (!(cond)) { \
        printf("      check failed (line %d): ", __LINE__); printf(__VA_ARGS__); printf("\n"); \
        caseFails++; } } while (0)
#define CHECK_RULES() CHECK(violations == 0, "%ld rule violation(s), first: %s", violations, firstViolation)

#define LONG 200000L     /* generous upper bound for one wait, in ticks */

/* Next transition out of the current phase; returns its 'to' value. */
static int nextTo(void) { return waitTr(-2, -2, LONG) ? lastTr()->to : -99; }

/* ------------------------------------------------------------------ */
/* Task 1                                                               */
static void S1(void)
{
    static const int seq[6][3] = {{33, 34, 600}, {34, 36, 200}, {36, 12, 50},
                                  {12, 20, 600}, {20, 36, 200}, {36, 33, 50}};
    simReset();
    taskIn = 1;
    while (ntr < 31 && tickNo < 2000000) step();
    CHECK(ntr >= 31, "only %d transitions", ntr);
    for (int i = 1; i <= 30 && i < ntr; i++) {
        const int *e = seq[(i - 1) % 6];
        CHECK(tr[i].from == e[0] && tr[i].to == e[1] && tr[i].events == e[2],
              "transition %d: %d -> %d after %ld events, expected %d -> %d after %d",
              i, tr[i].from, tr[i].to, tr[i].events, e[0], e[1], e[2]);
    }
    CHECK_RULES();
}

/* ------------------------------------------------------------------ */
/* Task 2 - pedestrians                                                 */
static void S2(void)
{
    simReset(); taskIn = 2;
    CHECK(waitTr(36, 12, LONG), "no R-G in Task 2");
    runTicks(50); nsHold = 5;
    CHECK(waitTr(36, 97, LONG), "no NS walk at the next G-R");
    CHECK(waitTr(97, 33, LONG) && lastTr()->events == 400, "NS walk lasted %ld events", lastTr()->events);
    CHECK(waitTr(33, 34, LONG) && lastTr()->events == 200, "green remainder %ld events", lastTr()->events);
    CHECK_RULES();
}

static void S3(void)
{
    simReset(); taskIn = 2;
    CHECK(waitTr(36, 33, LONG), "no G-R in Task 2");
    runTicks(50); ewHold = 5;
    CHECK(waitTr(36, 140, LONG), "no EW walk at the next R-G");
    CHECK(waitTr(140, 12, LONG) && lastTr()->events == 400, "EW walk lasted %ld events", lastTr()->events);
    CHECK(waitTr(12, 20, LONG) && lastTr()->events == 200, "green remainder %ld events", lastTr()->events);
    CHECK_RULES();
}

static void S4(void)
{
    int k, iew, ins;
    simReset(); taskIn = 2;
    CHECK(waitTr(34, 36, LONG), "no R-R");          /* Task 2 takes effect here */
    runTicks(20);
    nsHold = ewHold = 5;                             /* both pressed together in R-R */
    k = ntr;
    runEvents(600 + 200 + 50 + 600 + 200 + 50 + 100);
    iew = findTr(36, 140, k);
    ins = findTr(36, 97, k);
    CHECK(iew >= 0, "EW walk not served");
    CHECK(ins >= 0, "NS walk not served");
    CHECK(iew >= 0 && ins > iew, "walks not in successive greens (EW %d, NS %d)", iew, ins);
    CHECK(iew >= 0 && tr[iew + 1].from == 140 && tr[iew + 1].events == 400, "EW walk length");
    CHECK(ins >= 0 && ins + 1 < ntr && tr[ins + 1].from == 97 && tr[ins + 1].events == 400, "NS walk length");
    CHECK_RULES();
}

static void S5(void)
{
    int before;
    simReset(); taskIn = 2;
    CHECK(waitTr(36, 12, LONG), "no R-G");
    runTicks(10);
    before = d.nsRequests;
    nsHold = 300 * EVENT_EVERY;                      /* held for 3 s = 300 timer events */
    CHECK(waitTr(36, 97, LONG), "no NS walk");
    CHECK(d.nsRequests == before + 1, "held button counted %d times", d.nsRequests - before);
    CHECK(waitTr(97, 33, LONG) && lastTr()->events == 400, "walk length");
    CHECK(waitTr(20, 36, LONG), "no R-R");
    CHECK(nextTo() == 33, "a second walk was served for one held press");
    CHECK_RULES();
}

static void S6(void)
{
    int before;
    simReset(); taskIn = 2;
    CHECK(waitTr(36, 12, LONG), "no R-G");
    runTicks(10);
    before = d.nsRequests;
    for (int p = 0; p < 3; p++) { nsHold = 5; runTicks(20); }
    CHECK(d.nsRequests == before + 3, "%d presses counted", d.nsRequests - before);
    CHECK(waitTr(36, 97, LONG), "no NS walk");
    CHECK(waitTr(97, 33, LONG) && lastTr()->events == 400, "walk length");
    CHECK(waitTr(20, 36, LONG), "no R-R");
    CHECK(nextTo() == 33, "more than one walk for three presses");
    CHECK_RULES();
}

static void S7(void)
{
    simReset(); taskIn = 2;
    CHECK(waitTr(36, 33, LONG), "no G-R in Task 2");
    runTicks(50); nsHold = 5;                        /* during its own green */
    CHECK(nextTo() == 34 && lastTr()->from == 33 && lastTr()->events == 600,
          "current green changed: %d -> %d after %ld events", lastTr()->from, lastTr()->to, lastTr()->events);
    CHECK(waitTr(20, 36, LONG), "no R-R");
    CHECK(nextTo() == 97, "walk not served in the next G-R");
    CHECK_RULES();
}

static void S8(void)
{
    simReset(); taskIn = 2;
    CHECK(waitTr(36, 12, LONG), "no R-G");
    runTicks(10); nsHold = 5;                        /* request in Task 2 */
    runTicks(100); taskIn = 1;                       /* Task 1 from the next R-R */
    CHECK(waitTr(20, 36, LONG), "no R-R");
    CHECK(nextTo() == 33 && d.activeTask == 1, "Task 1 green: LEDR %d, activeTask %d", d.LEDR, d.activeTask);
    taskIn = 2;                                      /* back to Task 2 */
    CHECK(waitTr(36, 97, LONG), "retained request not served after returning to Task 2");
    CHECK(waitTr(97, 33, LONG) && lastTr()->events == 400, "walk length");
    CHECK_RULES();
}

/* ------------------------------------------------------------------ */
/* Mode selection                                                       */
static void S9(void)
{
    int changes = 0, prev;
    simReset();
    prev = d.activeTask;
    for (int p = 0; p < 240; p++) {
        waitTr(-2, -2, 6000);                        /* next phase (or 6000 ticks in a Task 3 hold) */
        runTicks(3 + (p * 37) % 300);                /* somewhere inside that phase */
        taskIn = 1 + (p * 7 + p / 4) % 4;            /* 1..4, changed in every phase */
        if (d.activeTask != prev) { changes++; prev = d.activeTask; }
    }
    runTicks(20000);
    CHECK(changes >= 40, "only %d activeTask changes observed", changes);
    CHECK_RULES();                                   /* includes: activeTask changes only at LEDR 36 */
}

static void S10(void)
{
    static const int bad[3] = {0, 5, 99};
    simReset(); taskIn = 2;
    CHECK(waitTr(34, 36, LONG) && d.activeTask == 2, "Task 2 not active");
    for (int k = 0; k < 3; k++) {
        taskIn = bad[k];
        for (int r = 0; r < 4; r++) CHECK(waitTr(-2, 36, LONG), "no R-R with task = %d", bad[k]);
        runTicks(500);
        CHECK(d.activeTask == 2, "task = %d changed activeTask to %d", bad[k], d.activeTask);
    }
    CHECK_RULES();
}

/* ------------------------------------------------------------------ */
/* Task 3 - configuration over the UART                                 */
static int enterTask3Hold(void)
{
    simReset(); taskIn = 3;
    if (!waitTr(34, 36, LONG)) return 0;
    runTicks(3000);
    return d.LEDR == 36 && d.waitingConfig && d.activeTask == 3;
}

static void expectPhases(const int (*seq)[3], int n, const char *what)
{
    for (int i = 0; i < n; i++) {
        int ok = waitTr(seq[i][0], seq[i][1], LONG);
        CHECK(ok && lastTr()->events == seq[i][2], "%s: %d -> %d after %ld events, expected %d",
              what, seq[i][0], seq[i][1], ok ? lastTr()->events : -1L, seq[i][2]);
    }
}

static const int CFG_8_3_1[6][3] = {{12, 20, 800}, {20, 36, 300}, {36, 33, 100},
                                    {33, 34, 800}, {34, 36, 300}, {36, 12, 100}};

static void S11(void)
{
    CHECK(enterTask3Hold(), "no Task 3 hold");
    send("8,3,1,8,3,1\n");
    CHECK(waitTr(36, 12, LONG), "not resumed after a valid packet");
    CHECK(d.configApplied == 1 && napplied == 1 && appliedLEDR[0] == 36, "commit not at R-R");
    CHECK(d.t1 == 8000 && d.t2 == 3000 && d.t3 == 1000 && d.t4 == 8000 && d.t5 == 3000 && d.t6 == 1000,
          "time-outs %d %d %d %d %d %d", d.t1, d.t2, d.t3, d.t4, d.t5, d.t6);
    expectPhases(CFG_8_3_1, 6, "8,3,1");
    CHECK_RULES();
}

static void S12(void)
{
    CHECK(enterTask3Hold(), "no Task 3 hold");
    send("8,3,1,8,3,1\r\n");
    CHECK(waitTr(36, 12, LONG), "not resumed after a CRLF packet");
    CHECK(d.configApplied == 1 && d.configRejected == 0, "applied %d rejected %d", d.configApplied, d.configRejected);
    expectPhases(CFG_8_3_1, 6, "CRLF 8,3,1");
    CHECK_RULES();
}

static void S13(void)
{
    static const char *pk[5] = {"1,2,3\n", "1,2,3,4,5,6,7\n", "12345,1,1,1,1,1\n", "1,,1,1,1,1\n", "a,1,1,1,1,1\n"};
    CHECK(enterTask3Hold(), "no Task 3 hold");
    for (int k = 0; k < 5; k++) {
        int r0 = d.configRejected;
        send(pk[k]);
        runTicks(3 * (long) strlen(pk[k]) + 100);
        CHECK(d.configRejected == r0 + 1, "\"%.*s\" rejected %d times", (int) strlen(pk[k]) - 1, pk[k], d.configRejected - r0);
        CHECK(d.LEDR == 36 && d.waitingConfig && d.configApplied == 0, "lights left red after a bad packet");
    }
    CHECK(d.t1 == 6000 && d.t2 == 2000 && d.t3 == 500 && d.t4 == 6000 && d.t5 == 2000 && d.t6 == 500,
          "time-outs changed by bad packets");
    CHECK_RULES();
}

static void S14(void)
{
    CHECK(enterTask3Hold(), "no Task 3 hold");
    send("zz9,,\n8,3,1,8,3,1\n");
    CHECK(waitTr(36, 12, LONG), "did not recover");
    CHECK(d.configRejected == 1 && d.configApplied == 1 && d.t1 == 8000, "rejected %d applied %d t1 %d",
          d.configRejected, d.configApplied, d.t1);
    CHECK_RULES();
}

static void S15(void)
{
    CHECK(enterTask3Hold(), "no Task 3 hold");
    send("0008,03,1,8,3,1\n");
    CHECK(waitTr(36, 12, LONG), "leading-zero packet not applied");
    CHECK(d.t1 == 8000 && d.t2 == 3000 && d.t3 == 1000 && d.t4 == 8000, "time-outs %d %d %d %d", d.t1, d.t2, d.t3, d.t4);
    CHECK_RULES();
}

static void S16(void)
{
    static const int seq[4][3] = {{33, 34, 800}, {34, 36, 300}, {36, 12, 100}, {12, 20, 200}};
    CHECK(enterTask3Hold(), "no Task 3 hold");
    send("8,3,1,8,3,1\n");
    CHECK(waitTr(36, 33, LONG), "no G-R after the first packet");
    runTicks(100);
    send("2,1,1,2,1,1\n");                           /* during green */
    runTicks(300);
    CHECK(d.pending1 == 2 && d.t1 == 8000 && d.configApplied == 1, "applied before the next R-R (t1 %d)", d.t1);
    expectPhases(seq, 4, "packet during green");
    CHECK(d.configApplied == 2 && appliedLEDR[1] == 36, "second commit not at R-R");
    CHECK_RULES();
}

static void S17(void)
{
    simReset(); taskIn = 1;
    runTicks(100);
    send("8,3,1,8,3,1\n");                           /* received while still in Task 1 */
    runTicks(300);
    CHECK(d.pending1 == 8 && d.configApplied == 0 && d.t1 == 6000, "applied in Task 1");
    taskIn = 3;
    CHECK(waitTr(-2, 36, LONG), "no R-R");
    CHECK(waitTr(36, -2, 2000), "held instead of applying the waiting packet");
    CHECK(lastTr()->events == 100 && d.configApplied == 1 && d.t1 == 8000,
          "first Task 3 R-R: %ld events, applied %d, t1 %d", lastTr()->events, d.configApplied, d.t1);
    CHECK_RULES();
}

static void S18(void)
{
    CHECK(enterTask3Hold(), "no Task 3 hold");
    send("8,3,1,8,3,1\n");
    CHECK(waitTr(36, 12, LONG), "first packet not applied");
    taskIn = 1;
    CHECK(waitTr(-2, 36, LONG) && waitTr(36, -2, LONG) && d.activeTask == 1, "did not leave Task 3");
    taskIn = 3;
    CHECK(waitTr(-2, 36, LONG), "no R-R");
    {
        int n = ntr;
        runTicks(20000);
        CHECK(ntr == n && d.LEDR == 36 && d.waitingConfig, "re-entered Task 3 without waiting for a new packet");
    }
    send("2,1,1,2,1,1\n");
    CHECK(waitTr(36, -2, LONG) && d.t1 == 2000 && d.configApplied == 2, "new packet not applied");
    CHECK_RULES();
}

static void S19(void)
{
    simReset(); taskIn = 1;
    runTicks(100);
    send("8,3,1,8,3,1\n2,1,1,2,1,1\n");               /* second packet straight after the first */
    runTicks(500);
    CHECK(d.pending1 == 8 && d.configReady == 0 && uartPos == 12,
          "second packet not blocked (pending1 %d, ready %d, consumed %d)", d.pending1, d.configReady, (int) uartPos);
    taskIn = 3;
    runEvents(3000);
    CHECK(napplied == 2 && appliedT1[0] == 8000 && appliedT1[1] == 2000,
          "commits %d: t1 %d then %d", napplied, appliedT1[0], appliedT1[1]);
    CHECK(uartPos == uartLen && d.configRejected == 0, "characters lost or corrupted");
    CHECK_RULES();
}

/* ------------------------------------------------------------------ */
/* Task 4 - camera                                                      */
static int task4Ready(void)
{
    simReset(); taskIn = 4;
    return waitTr(36, 12, LONG) && d.activeTask == 4;   /* R-G in Task 4 */
}

static void S20(void)
{
    CHECK(task4Ready(), "Task 4 not active");
    runTicks(50); carHold = 5;                       /* enters in green, stays */
    CHECK(waitTr(12, 20, LONG), "no yellow");
    runTicks(2);
    CHECK(nact == 1 && actLEDR[0] == 20 && actTick[0] == lastTr()->tick, "not activated at yellow start");
    runEvents(150);
    CHECK(nsnap == 1 && snapEv[0] - actEv[0] == 100, "snapshot after %ld events", nsnap ? snapEv[0] - actEv[0] : -1L);
    CHECK_RULES();
}

static void S21(void)
{
    CHECK(task4Ready(), "Task 4 not active");
    CHECK(waitTr(12, 20, LONG), "no yellow");
    runTicks(30 * EVENT_EVERY + 2);                  /* mid-yellow, between two timer events */
    carHold = 5;
    runEvents(150);
    CHECK(nact == 1 && actLEDR[0] == 20, "not armed during yellow");
    CHECK(nsnap == 1 && snapEv[0] - actEv[0] == 100, "snapshot after %ld events", nsnap ? snapEv[0] - actEv[0] : -1L);
    CHECK(nsnap == 1 && snapTick[0] - actTick[0] < 100 * EVENT_EVERY,
          "%ld ticks from arming: not fewer than 100 timer periods", snapTick[0] - actTick[0]);
    CHECK_RULES();
}

static void S22(void)
{
    CHECK(task4Ready(), "Task 4 not active");
    runTicks(50); carHold = 5;
    CHECK(waitTr(12, 20, LONG) && (runTicks(2), nact == 1), "not activated");
    runEvents(50); carHold = 5;                      /* leaves before the dwell ends */
    runEvents(300);
    CHECK(nleft == 1 && nsnap == 0, "left %d, snapshots %d", nleft, nsnap);
    CHECK_RULES();
}

/* Leave on exactly the tick of the 100th dwell event (and a control one tick later). */
static void leaveAtDeadline(long offset, int *snaps, int *lefts)
{
    long first, target;
    task4Ready();
    runTicks(50); carHold = 5;
    waitTr(12, 20, LONG);
    runTicks(2);
    first = actTick[0] + 1;
    first += (3 - first % EVENT_EVERY + EVENT_EVERY) % EVENT_EVERY;  /* first event tick after arming */
    target = first + 99L * EVENT_EVERY + offset;                    /* tick of the 100th event (+offset) */
    while (tickNo < target) step();
    carHold = 5;
    runEvents(300);
    *snaps = nsnap; *lefts = nleft;
}

static void S23(void)
{
    int s, l;
    leaveAtDeadline(0, &s, &l);
    CHECK(s == 0 && l == 1, "leave on the deadline tick: snapshots %d, left %d", s, l);
    CHECK_RULES();
    leaveAtDeadline(1, &s, &l);                      /* control: one tick later */
    CHECK(s == 1 && l == 1, "control (one tick later): snapshots %d, left %d", s, l);
    CHECK_RULES();
}

static void S24(void)
{
    CHECK(task4Ready(), "Task 4 not active");
    runTicks(50); carHold = 5;                       /* stays through R-Y and the next Y-R */
    CHECK(waitTr(12, 20, LONG) && waitTr(33, 34, LONG) && waitTr(34, 36, LONG), "cycle stalled");
    CHECK(nact == 1 && nsnap == 1, "activations %d, snapshots %d over two yellows", nact, nsnap);
    CHECK_RULES();
}

static void S25(void)
{
    CHECK(task4Ready(), "Task 4 not active");
    runTicks(50); carHold = 5;
    runEvents(1000);
    CHECK(nsnap == 1, "first snapshot");
    carHold = 5; runTicks(20);                       /* leaves */
    CHECK(waitTr(36, 33, LONG), "no G-R");
    runTicks(50); carHold = 5;                       /* re-enters */
    CHECK(waitTr(34, 36, LONG), "no R-R");
    CHECK(nleft == 1 && nact == 2 && nsnap == 2, "left %d, activations %d, snapshots %d", nleft, nact, nsnap);
    CHECK_RULES();
}

static void S26(void)
{
    CHECK(task4Ready(), "Task 4 not active");
    CHECK(waitTr(12, 20, LONG), "no yellow");
    runEvents(150);                                  /* 50 yellow events left */
    carHold = 5; runTicks(10);
    CHECK(nact == 1 && d.cameraArmed, "not armed");
    taskIn = 1;                                      /* Task 1 from the next R-R */
    for (int k = 0; k < 6; k++) CHECK(waitTr(-2, 36, LONG), "no R-R");
    CHECK(d.activeTask == 1 && !d.cameraArmed && nsnap == 0 && nact == 1,
          "Task 1: armed %d, snapshots %d, activations %d", d.cameraArmed, nsnap, nact);
    CHECK_RULES();
}

static void S27(void)
{
    CHECK(task4Ready(), "Task 4 not active");
    runTicks(50); carHold = 50;                      /* held for 50 ticks */
    runTicks(100);
    CHECK(d.vehiclePresent && nleft == 0, "present %d, left %d", d.vehiclePresent, nleft);
    CHECK(waitTr(12, 20, LONG) && (runTicks(2), nact == 1), "one press did not give one vehicle");
    CHECK_RULES();
}

/* ------------------------------------------------------------------ */
/* Robustness                                                           */
static unsigned int rng = 303u;
static unsigned int rnd(void) { rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5; return rng; }

static void randomRun(long ticks, int allowZero, long *nTr, int *nCommit)
{
    static const char junk[] = "0123456789,,\r\nab";
    char pkt[64];
    simReset();
    rng = 303u;
    for (long i = 0; i < ticks; i++) {
        unsigned int r = rnd();
        if (r % 1500 == 0) taskIn = (int) (rnd() % 6);          /* 0..5 includes invalid values */
        if (r % 700 == 1 && !nsHold) nsHold = 1 + rnd() % 30;
        if (r % 700 == 2 && !ewHold) ewHold = 1 + rnd() % 30;
        if (r % 900 == 3 && !carHold) carHold = 1 + rnd() % 30;
        if (r % 4000 == 4 && uartPos == uartLen) {
            if (rnd() % 10 < 7) {                                /* well-formed packet */
                int lo = allowZero ? 0 : 1;
                snprintf(pkt, sizeof pkt, "%d,%d,%d,%d,%d,%d\n",
                         lo + (int) (rnd() % 12), lo + (int) (rnd() % 4), lo + (int) (rnd() % 3),
                         lo + (int) (rnd() % 12), lo + (int) (rnd() % 4), lo + (int) (rnd() % 3));
            } else {                                             /* garbage line */
                int n = 1 + rnd() % 20, k;
                for (k = 0; k < n; k++) pkt[k] = junk[rnd() % (sizeof junk - 1)];
                pkt[k++] = '\n'; pkt[k] = 0;
            }
            send(pkt);
        }
        step();
    }
    *nTr = ntr; *nCommit = d.configApplied;
}

static void S28(void)
{
    long n; int c;
    randomRun(1000000L, 0, &n, &c);
    printf("      %ld LEDR changes, %d commits, %d rejects, %d snapshots, seed 303\n",
           n, c, d.configRejected, nsnap);
    CHECK(n > 200 && c > 0, "random run exercised too little (%ld changes, %d commits)", n, c);
    CHECK_RULES();
}

static void S29(void)
{
    simReset();
    noTimer = 1;
    for (long i = 0; i < 100000; i++) {
        if (i % 5000 == 10) taskIn = 1 + (int) (i / 5000) % 4;
        if (i % 3000 == 20) nsHold = ewHold = carHold = 5;
        step();
    }
    CHECK(ntr == 1 && d.LEDR == 33, "lights changed without timer events (%d transitions)", ntr);
    CHECK_RULES();
}

/* Extra (not in the plan): configuration values of 0 seconds. */
static void X1(void)
{
    long n; int c;
    randomRun(1000000L, 1, &n, &c);
    printf("      zero-second time-outs allowed: %ld rule violation(s) in %ld changes, first: %s\n",
           violations, n, violations ? firstViolation : "-");
}

/* ------------------------------------------------------------------ */
typedef struct { const char *id, *what; void (*fn)(void); } Case;

static const Case cases[] = {
    {"S1",  "Task 1, 5 cycles: legal sequence, exact event counts", S1},
    {"S2",  "Task 2, NS press in R-G: 97 for 400 events", S2},
    {"S3",  "Task 2, EW press in G-R: 140 for 400 events", S3},
    {"S4",  "Task 2, both pressed together: both walks", S4},
    {"S5",  "Task 2, button held 3 s: one walk", S5},
    {"S6",  "Task 2, three NS presses: one walk", S6},
    {"S7",  "Task 2, NS press in its own green: next G-R", S7},
    {"S8",  "Task 2 -> 1 -> 2: request retained", S8},
    {"S9",  "Task change in every phase: only at LEDR 36", S9},
    {"S10", "task = 0, 5, 99: current mode kept", S10},
    {"S11", "Task 3 valid packet: 800/300/100", S11},
    {"S12", "Task 3 CRLF packet: same as S11", S12},
    {"S13", "Task 3 five invalid packets rejected", S13},
    {"S14", "Task 3 garbage then valid packet", S14},
    {"S15", "Task 3 leading zeros", S15},
    {"S16", "Task 3 packet during green: next R-R", S16},
    {"S17", "Task 3 packet before entering Task 3", S17},
    {"S18", "Task 3 re-entered: waits for a new packet", S18},
    {"S19", "Task 3 second packet blocked, not lost", S19},
    {"S20", "Task 4 car in green: snapshot after 100 events", S20},
    {"S21", "Task 4 car enters in yellow: 100 events, < 100 periods", S21},
    {"S22", "Task 4 car leaves before the snapshot", S22},
    {"S23", "Task 4 leaves on the deadline tick: no snapshot", S23},
    {"S24", "Task 4 one visit, two yellows: one snapshot", S24},
    {"S25", "Task 4 leave and re-enter: second snapshot", S25},
    {"S26", "Task 4 -> 1 while armed: cancelled", S26},
    {"S27", "Task 4 button held 50 ticks: one press", S27},
    {"S28", "1,000,000 random ticks: T0 rules hold", S28},
    {"S29", "No timer events: lights never change", S29},
};

int main(void)
{
    int n = (int) (sizeof cases / sizeof cases[0]);
    printf("pc_suite: TrafficLight_B, timer event every %d ticks\n", EVENT_EVERY);
    for (int i = 0; i < n; i++) {
        caseFails = 0;
        printf("  %-4s %-58s ", cases[i].id, cases[i].what);
        fflush(stdout);
        printf("\n");
        cases[i].fn();
        printf("       -> %s\n", caseFails ? "FAIL" : "PASS");
        if (caseFails) totalFail++; else totalPass++;
    }
    printf("  X1   (extra, informational) random run with 0-second time-outs\n");
    X1();
    printf("\nTOTAL: %d passed, %d failed, of %d\n", totalPass, totalFail, n);
    return totalFail ? 1 : 0;
}
