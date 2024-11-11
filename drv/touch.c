/***
 * @file        touch.c
 * 
 * @brief       driver for sun4i touchscreen using adc 
 * 
 */
#include "touch.h"

struct ts_data tp;


// void __attribute__((interrupt("IRQ"))) irq_handler (void)
// {
//     if (TP->INT_FIFO_STAT & FIFO_DATA_PENDING) {
//         TP->INT_FIFO_STAT = (1<<16);

//     }
// }

int tp_init(void)
{
    u32 reg = 0;

    TP->INT_FIFO_CTRL = TEMP_IRQ_EN(1) | DATA_IRQ_EN(1) | FIFO_TRIG(1) | 
                        FIFO_FLUSH(1) | TP_UP_IRQ_EN(1);

    /*
	 * Select HOSC clk, clkin = clk / 6, adc samplefreq = clkin / 8192,
	 * t_acq = clkin / (16 * 64)
	 */
	TP->CTRL_REG0 = ADC_CLK_SEL(0) | ADC_CLK_DIV(2) | FS_DIV(7) | T_ACQ(63);

    /*
	 * tp_sensitive_adjust is an optional property
	 * tp_mode = 0 : only x and y coordinates, as we don't use dual touch
     * 0000: least sensitive
     * ....
     * 1111: Most sensitive
	 */
    TP->CTRL_REG2 = TP_SENSITIVE_ADJUST(12) | TP_MODE_SELECT(0);

    /*
	 * Enable median and averaging filter, optional property for
	 * filter type.
     * 00: 4/2
     * 01: 5/3
     * 10: 8/4
     * 11: 16/8
	 */
    TP->CTRL_REG3 = FILTER_EN(1) | FILTER_TYPE(0);

    TP->INT_TPR = TEMP_ENABLE(1) | TEMP_PERIOD(1953);

    reg = STYLUS_UP_DEBOUN(5) | STYLUS_UP_DEBOUN_EN(1);
    reg |= TP_MODE_EN(1);
    TP->CTRL_REG1 = reg;

    TP->INT_FIFO_CTRL = TEMP_IRQ_EN(1);

    /** IRQ init */
    INT->BASE_ADDR = 0;
    INT->MASK[0] = ~(1 << IRQ_TP);
    INT->MASK[1] = 0xFFFFFFFF;
    INT->EN[0] = (1 << IRQ_TP);
    INT->EN[1] = 0;

    return 0;
}