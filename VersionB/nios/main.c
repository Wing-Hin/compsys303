/*
 * COMPSYS 303 Assignment - Version B glue code (Nios II, DE2-115)
 *
 * The reactive interface between the Nios II interval timer and the
 * KIELER-generated SCChart code (sccharts.c / sccharts.h).
 *
 *   timer interrupt  ->  pendingEvents++            (ISR, every TIMER_PERIOD_MS)
 *   main loop        ->  sample switches/keys/UART  (sensor stage)
 *                        timerTick = take one event
 *                        tick(&d)                   (controller stage)
 *                        write LEDR                 (plant stage)
 *
 * The chart never sees time, only the timerTick event: this is multiform time.
 * The loop runs freely, so most ticks carry no timer event; that difference
 * (ticks computed vs events counted) is logged for the Section 4 comparison.
 *
 * AI Use Declaration: The design and all design decisions were made by Harold and Lucas.
 * This glue code (timer interrupt and event queue, input sampling, UART feed and
 * evidence logging) was written with the assistance of a generative AI tool (Claude,
 * Anthropic), then reviewed, tested and verified by Harold and Lucas on the DE2-115.
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <system.h>
#include <alt_types.h>
#include <sys/alt_irq.h>
#include <sys/alt_alarm.h>
#include <sys/alt_timestamp.h>
#include <altera_avalon_pio_regs.h>
#include <altera_avalon_timer_regs.h>

/* ---------------------------------------------------------------------------
 * Which chart is linked in. Copy the matching generated pair from kieler-gen\
 * (named after the scchart) into this project, and only that pair:
 *   1 = Task1_VersionB.sctx         -> Task1_TrafficLight_B.c / .h
 *   2 = Task2_VersionB.sctx         -> Task2_PedestrianTrafficLight_B.c / .h
 *   4 = TrafficLight_VersionB.sctx  -> TrafficLight_B.c / .h   (Tasks 1-4)
 * ------------------------------------------------------------------------- */
#define CHART 4

#if CHART == 1
#include "Task1_TrafficLight_B.h"
#elif CHART == 2
#include "Task2_PedestrianTrafficLight_B.h"
#else
#include "TrafficLight_B.h"
#endif

/* The C-side copy of the timer rate. Keep it equal to TIMER_MS in the chart.
 * Changing ONLY this value is the brief's "rescale" check (Section 2.1).     */
#define TIMER_PERIOD_MS 10

/* Board mapping (document this in the README) */
#define KEY_NS    0x1   /* KEY0: NS pedestrian button   -> NSraised        */
#define KEY_EW    0x2   /* KEY1: EW pedestrian button   -> EWraised        */
#define KEY_CAR   0x4   /* KEY2: vehicle enter/leave    -> vehicleButton   */
#define SW_TASK   0x3   /* SW1..SW0: 00 = Task 1 ... 11 = Task 4           */
                        /* KEY3 is the hardware reset of the Nios II system */

/* ---------------------------------------------------------------------------
 * Timer interrupt: the external timing reference.
 * alt_alarm callbacks run inside the system-clock timer ISR, so keep it short.
 * ------------------------------------------------------------------------- */
static volatile alt_u32 pendingEvents = 0;  /* events not yet handed to the chart */
static alt_u32 alarmTicks = 1;              /* alarm period in system-clock ticks */

static alt_u32 timer_isr(void* context)
{
    (void) context;
    pendingEvents++;
    return alarmTicks;                      /* re-arm with the same period */
}

/* Hand at most one timer event to the chart per tick. If the loop was slow
 * (e.g. a printf blocked), events wait in pendingEvents instead of being lost. */
static char take_timer_event(void)
{
    char got = 0;
    alt_irq_context ctx = alt_irq_disable_all();   /* the ISR also writes pendingEvents */
    if (pendingEvents > 0) {
        pendingEvents--;
        got = 1;
    }
    alt_irq_enable_all(ctx);
    return got;
}

int main(void)
{
    TickData d = {0};
    reset(&d);

    /* Independent stopwatch for the evidence log (timer_1 as timestamp timer) */
    alt_u32 tsPerUs = 1;
    if (alt_timestamp_start() >= 0) {
        /* The HAL starts timer_1 one-shot: it counts down 2^32 cycles (85.9 s at
         * 50 MHz) once and then stops, so every later reading is the same. Set
         * CONT so it reloads and keeps running; unsigned differences of
         * alt_timestamp() then stay correct for any interval below 85.9 s. */
        IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_1_BASE,
            ALTERA_AVALON_TIMER_CONTROL_CONT_MSK | ALTERA_AVALON_TIMER_CONTROL_START_MSK);
        tsPerUs = alt_timestamp_freq() / 1000000u;
    } else {
        printf("No timestamp timer: set hal.timestamp_timer = timer_1 in the BSP\n");
    }

#if CHART == 4
    /* Task 3 packets come from either port: the RS-232 UART (DB9) or the
     * JTAG UART console (nios2-terminal over the USB-Blaster cable). */
    int cfgFd[2];
    cfgFd[0] = open(UART_NAME, O_RDONLY | O_NONBLOCK);
    cfgFd[1] = open(JTAG_UART_NAME, O_RDONLY | O_NONBLOCK);
    if (cfgFd[0] < 0) printf("RS-232 UART not opened: Task 3 input from the JTAG console only\n");
    if (cfgFd[1] < 0) printf("JTAG UART not opened: Task 3 input from RS-232 only\n");
#endif

    /* Start the external timer. alt_alarm counts system-clock ticks. */
    static alt_alarm alarm;
    alarmTicks = (TIMER_PERIOD_MS * alt_ticks_per_second()) / 1000u;
    if (alarmTicks == 0) alarmTicks = 1;
    if (alt_alarm_start(&alarm, alarmTicks, timer_isr, NULL) < 0) {
        printf("No system clock timer: set hal.sys_clk_timer = timer_0 in the BSP\n");
    }

    printf("Version B running: timer event every %d ms\n", TIMER_PERIOD_MS);

    int     lastLEDR      = -1;
    alt_u32 phaseStart    = alt_timestamp();
    alt_u32 ticksInPhase  = 0;
    alt_u32 eventsInPhase = 0;
#if CHART == 4
    char    lastActivated = 0, lastSnapshot = 0;
    alt_u32 cameraStart   = 0;
#endif

    while (1) {
        /* ---------- 1. Sensor stage: sample the board ---------- */
        d.timerTick = take_timer_event();

#if CHART >= 2
        alt_u32 keys = ~IORD_ALTERA_AVALON_PIO_DATA(KEYS_BASE) & 0x7;  /* keys are active low */
        d.NSraised = (keys & KEY_NS) != 0;
        d.EWraised = (keys & KEY_EW) != 0;
#endif
#if CHART == 4
        alt_u32 sw = IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE);
        d.task          = (int)(sw & SW_TASK) + 1;
        d.vehicleButton = (keys & KEY_CAR) != 0;

        /* Task 3: one byte per tick, and only when the chart said it was ready
         * after the previous tick. RS-232 is read first, then the JTAG console;
         * bytes wait in each HAL buffer. Send a packet on one port at a time. */
        d.configValid = 0;
        if (d.configReady) {
            char ch;
            int  i;
            for (i = 0; i < 2 && !d.configValid; i++) {
                if (cfgFd[i] >= 0 && read(cfgFd[i], &ch, 1) == 1) {
                    d.configChar  = (unsigned char) ch;
                    d.configValid = 1;
                }
            }
        }
#endif

        /* ---------- 2. Controller stage: one synchronous reaction ---------- */
        tick(&d);
        ticksInPhase++;
        if (d.timerTick) eventsInPhase++;

        /* ---------- 3. Plant stage: drive the lamps ---------- */
        IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, d.LEDR);

        /* ---------- Evidence log (JTAG UART console) ---------- */
        if (d.LEDR != lastLEDR) {
            alt_u32 now = alt_timestamp();
            alt_u32 us  = (now - phaseStart) / tsPerUs;   /* wraps safely below ~85 s */
            printf("LEDR %3d -> %3d | previous phase %8lu us | %7lu ticks | %6lu timer events\n",
                   lastLEDR, d.LEDR, (unsigned long) us,
                   (unsigned long) ticksInPhase, (unsigned long) eventsInPhase);
            lastLEDR      = d.LEDR;
            phaseStart    = now;
            ticksInPhase  = 0;
            eventsInPhase = 0;
        }
#if CHART == 4
        if (d.cameraActivated && !lastActivated) cameraStart = alt_timestamp();
        if (d.snapshotTaken && !lastSnapshot) {
            printf("  camera dwell measured: %lu us\n",
                   (unsigned long) ((alt_timestamp() - cameraStart) / tsPerUs));
        }
        lastActivated = d.cameraActivated;
        lastSnapshot  = d.snapshotTaken;
#endif
    }

    return 0;
}
