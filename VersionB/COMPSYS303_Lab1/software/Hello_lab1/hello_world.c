#include <stdio.h>
#include <system.h>
#include <altera_avalon_pio_regs.h>
#include <alt_types.h>
#include <sys/alt_irq.h>
#include <sys/alt_alarm.h>

#include "cs303-2-115-test/sccharts.h"

/* Which lab demo to build: 0 = section 6 counter, 1 = section 8 ABRO */
#define DEMO_ABRO 0

#define KEY2_MASK 0x4
#define KEY1_MASK 0x2
#define KEY0_MASK 0x1

#if DEMO_ABRO

/* Section 8.2: ABRO on Nios II.
 * A = Key2, B = Key1, R = Key0, O = Red LED 0. */
int main(void)
{
    TickData data;
    reset(&data);

    while (1) {
        /* keys are active low: invert so 1 == pressed */
        int keys = ~IORD_ALTERA_AVALON_PIO_DATA(KEYS_BASE);
        data.A = (keys >> 2) & 1;   /* Key2 */
        data.B = (keys >> 1) & 1;   /* Key1 */
        data.R = (keys >> 0) & 1;   /* Key0 */

        tick(&data);

        IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, data.O ? 0x1 : 0x0);
    }
    return 0;
}

#else /* section 6 counter demo */

volatile int counter = 0;
volatile int dirty   = 1;

static alt_alarm timer;

void key_isr(void* context, alt_u32 id)
{
    int edges = IORD_ALTERA_AVALON_PIO_EDGE_CAP(KEYS_BASE);
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEYS_BASE, 0);

    if (edges & KEY0_MASK) { counter++; dirty = 1; }
}

alt_u32 alarm_isr(void* context)
{
    int keys = IORD_ALTERA_AVALON_PIO_DATA(KEYS_BASE);
    // active low: 0 == pressed
    if ((keys & KEY1_MASK) == 0) {
        counter++;
        dirty = 1;
    }
    // reschedule
    return alt_ticks_per_second() / 2;
}

int main(void)
{
    FILE* lcd = fopen(LCD_NAME, "w");

    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEYS_BASE, 0);   // clear stale edges
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEYS_BASE, KEY0_MASK);
    alt_irq_register(KEYS_IRQ, NULL, key_isr);
    alt_alarm_start(&timer, alt_ticks_per_second() / 2, alarm_isr, NULL);
    while (1) {
        if (dirty) {
            dirty = 0;
            if (lcd) {
                fprintf(lcd, "\033[2JCount: %d", counter);
                fflush(lcd);
            }
            printf("Count: %d\n", counter);
        }
    }
    return 0;
}

#endif
