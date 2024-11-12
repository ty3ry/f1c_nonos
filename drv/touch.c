/***
 * @file        touch.c
 *
 * @brief       driver for sun4i touchscreen using adc
 *
 */
#include "touch.h"

#define IRQ_EN (1)

struct ts_data tp = {
  .ignore_fifo_data = true,
  .ready = false
};


void tp_irq_handler(void)
{
  u32 reg_val;

  reg_val = TP->INT_FIFO_STAT;
  
  if (reg_val & TEMP_DATA_PENDING) {
    tp.temp_data = TP->T_DATA;
  }

  if (reg_val & FIFO_DATA_PENDING)
  {
    tp.pt.x = TP->DATA;
    tp.pt.y = TP->DATA;

    if (!tp.ignore_fifo_data)
    {
      //printf("x: %d y: %d\n", tp.pt.x, tp.pt.y);
      tp.ready = 1;
    }
    else
    {
      tp.ignore_fifo_data = false;
    }
  }

  if (reg_val & TP_UP_PENDING)
  {
    tp.ignore_fifo_data = true;
    tp.ready = 0;
  }

  TP->INT_FIFO_STAT = reg_val;
}

/**
 * @brief   touch panel init
 */
int tp_init(void)
{
  u32 reg = 0;

  /** set gpio for TP */
  PA->CFG0 = 0x00002222;

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
  TP->CTRL_REG2 = TP_SENSITIVE_ADJUST(15) | TP_FIFO_MODE_SELECT(0);

  /*
   * Enable median and averaging filter, optional property for
   * filter type.
   * 00: 4/2
   * 01: 5/3
   * 10: 8/4
   * 11: 16/8
   */
  TP->CTRL_REG3 = FILTER_EN(1) | FILTER_TYPE(1);

  TP->INT_TPR = TEMP_ENABLE(1) | TEMP_PERIOD(1953);

  TP->INT_FIFO_CTRL = /*TEMP_IRQ_EN(1) | */ DATA_IRQ_EN(1) | FIFO_TRIG(1) |
                      FIFO_FLUSH(1) | TP_UP_IRQ_EN(1) /*| TP_DOWN_IRQ_EN(1)*/;

  reg = STYLUS_UP_DEBOUN(5) | STYLUS_UP_DEBOUN_EN(1) | ADC_CHAN_SELECT(0xf);
  reg |= TP_EN(1);
  TP->CTRL_REG1 = reg;

#if (IRQ_EN)
  /** IRQ init */
  INT->BASE_ADDR = 0;
  INT->MASK[0] = ~(1 << IRQ_TP);
  INT->MASK[1] = 0xFFFFFFFF;
  INT->EN[0] = (1 << IRQ_TP);
  INT->EN[1] = 0;
#endif

  return 0;
}

int tp_read(struct point *p)
{
  if (tp.ready)
  {
    p->x = tp.pt.x;
    p->y = tp.pt.y;

    return 1;
  }

  return 0;
}