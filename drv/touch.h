/***
 * @file     touch.h
 * 
 * @brief       header for touchscreen driver for sun4i 
 * 
 */
#ifndef TOUCH_H
#define TOUCH_H

#include "sys.h"

#define TP_CTRL0		    0x00
#define TP_CTRL1		    0x04
#define TP_CTRL2		    0x08
#define TP_CTRL3		    0x0c
#define TP_INT_FIFOC		0x10
#define TP_INT_FIFOS		0x14
#define TP_TPR			    0x18
#define TP_CDAT			    0x1c
#define TEMP_DATA		    0x20
#define TP_DATA			    0x24

/* TP_CTRL0 bits */
#define ADC_FIRST_DLY(x)	((x) << 24) /* 8 bits */
#define ADC_FIRST_DLY_MODE(x)	((x) << 23)
#define ADC_CLK_SEL(x)		((x) << 22)
#define ADC_CLK_DIV(x)		((x) << 20) /* 3 bits */
#define FS_DIV(x)		    ((x) << 16) /* 4 bits */
#define T_ACQ(x)		    ((x) << 0) /* 16 bits */

/* TP_CTRL1 bits */
#define STYLUS_UP_DEBOUN(x)	    ((x) << 12) /* 8 bits */
#define STYLUS_UP_DEBOUN_EN(x)	((x) << 9)
#define TOUCH_PAN_CALI_EN(x)	((x) << 6)
#define TP_DUAL_EN(x)		    ((x) << 5)
#define TP_MODE_EN(x)		    ((x) << 4)
#define TP_ADC_SELECT(x)	    ((x) << 3)
#define ADC_CHAN_SELECT(x)	    ((x) << 0)  /* 3 bits */

/* on sun6i, bits 3~6 are left shifted by 1 to 4~7 */
#define SUN6I_TP_MODE_EN(x)	    ((x) << 5)

/* TP_CTRL2 bits */
#define TP_SENSITIVE_ADJUST(x)	((x) << 28) /* 4 bits */
#define TP_MODE_SELECT(x)	    ((x) << 26) /* 2 bits */
#define PRE_MEA_EN(x)		    ((x) << 24)
#define PRE_MEA_THRE_CNT(x)	    ((x) << 0) /* 24 bits */

/* TP_CTRL3 bits */
#define FILTER_EN(x)		    ((x) << 2)
#define FILTER_TYPE(x)		    ((x) << 0)  /* 2 bits */

/* TP_INT_FIFOC irq and fifo mask / control bits */
#define TEMP_IRQ_EN(x)		    ((x) << 18)
#define OVERRUN_IRQ_EN(x)	    ((x) << 17)
#define DATA_IRQ_EN(x)		    ((x) << 16)
#define TP_DATA_XY_CHANGE(x)	((x) << 13)
#define FIFO_TRIG(x)		    ((x) << 8)  /* 5 bits */
#define DATA_DRQ_EN(x)		    ((x) << 7)
#define FIFO_FLUSH(x)		    ((x) << 4)
#define TP_UP_IRQ_EN(x)		    ((x) << 1)
#define TP_DOWN_IRQ_EN(x)	    ((x) << 0)

/* TP_INT_FIFOS irq and fifo status bits */
#define TEMP_DATA_PENDING	    (1<<18)
#define FIFO_OVERRUN_PENDING	(1<<17)
#define FIFO_DATA_PENDING	    (1<<16)
#define TP_IDLE_FLG		        (1<<2)
#define TP_UP_PENDING		    (1<<1)
#define TP_DOWN_PENDING		    (1<<0)

/* TP_TPR bits */
#define TEMP_ENABLE(x)		    ((x) << 16)
#define TEMP_PERIOD(x)		    ((x) << 0)  /* t = x * 256 * 16 / clkin */

struct ts_data {
	unsigned int irq;
	bool ignore_fifo_data;
    uint32_t *reg_mem;
	int temp_data;
	int temp_offset;
	int temp_step;
};

int tp_init(void);

#endif /** end of TOUCH_H */