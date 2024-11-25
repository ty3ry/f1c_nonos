/******************************************************************************
 * @file     	touch.c
 * 
 * @brief		  driver for allwinner touch panel
 * 				    The controller is a 4-wire resistive touch screen controller, 
 * 				    includes 12-bit resolution A/D converter. Especially, it
 * 				    provides the ability of dual touch detection. 
 * 				    The controller through the implementation of the two A/D 
 * 				    conversion has been identified by the location of the screen 
 * 				    of single touch, in addition to measurable increase in pressure 
 * 				    on the touch screen 
 * 
 * @author		c_e (cosmas.es08@gmail.com) 
 * @note 		  refer to linux device driver 
 * 				    https://github.com/torvalds/linux/blob/master/drivers/input/touchscreen/sun4i-ts.c
 * 
 *****************************************************************************/
#include "sys.h"

#define IRQ_EN (1)

TouchPanel_t *touch_panel;


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
      printf("x: %d y: %d\n", tp.pt.x, tp.pt.y);
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
  printf("FIFO Stat: 0x%08x\n", TP->INT_FIFO_STAT);
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


/******************************** new methode **********************************/
/**
 * @brief   touch panel init
 */
int touch_panel_init(void)
{
  touch_panel = TP;

  /** set gpio for TP */
  //PA->CFG0 = 0x00002222;

  /*
   * Select HOSC clk, clkin = clk / 6, adc samplefreq = clkin / 8192,
   * t_acq = clkin / (16 * 64)
   */
  touch_panel->tpctrl0.bit.TACQ = 63;
  touch_panel->tpctrl0.bit.FS_DIV = 7;
  touch_panel->tpctrl0.bit.ADC_CLK_DIVIDER = 2;
  touch_panel->tpctrl0.bit.ADC_CLK_SEL = 0;

  touch_panel->tpctrl2.bit.TP_SENS_ADJUST = 15;
  touch_panel->tpctrl2.bit.TP_FIFO_MODE_SELECT = 0;

  touch_panel->tpctrl3.bit.FILTER_EN = 1;
  touch_panel->tpctrl3.bit.FILTER_TYPE = 1;
  
  touch_panel->tp_int_ctrl.bit.TP_DATA_IRQ_EN = 1;
  touch_panel->tp_int_ctrl.bit.TP_FIFO_TRIG_LEVEL = 1;
  touch_panel->tp_int_ctrl.bit.TP_FIFO_FLUSH = 1;
  touch_panel->tp_int_ctrl.bit.TP_UP_IRQ_EN = 1;

  touch_panel->tpctrl1.bit.STYLUS_UP_DEBOUNCE = 5;
  touch_panel->tpctrl1.bit.STYLUS_UP_DEBOUNCE_EN = 1;
  touch_panel->tpctrl1.bit.ADC_CHAN0_SELECT = 1;
  touch_panel->tpctrl1.bit.ADC_CHAN1_SELECT = 1;
  touch_panel->tpctrl1.bit.ADC_CHAN2_SELECT = 1;
  touch_panel->tpctrl1.bit.ADC_CHAN3_SELECT = 1;
  touch_panel->tpctrl1.bit.TP_EN = 1;

// #if (IRQ_EN)
//   /** IRQ init */
//   INT->BASE_ADDR = 0;
//   INT->MASK[0] = ~(1 << IRQ_TP);
//   INT->MASK[1] = 0xFFFFFFFF;
//   INT->EN[0] = (1 << IRQ_TP);
//   INT->EN[1] = 0;
// #endif

  return 0;

}

/***
 * @brief   IRQ Handler
 */
void touch_panel_irq_handler(void)
{
  uint32_t reg_val;

  if (!touch_panel)
    return;

  reg_val = touch_panel->tp_int_stat.word;

  /*if (reg_val & TEMP_DATA_PENDING) {
    tp.temp_data = TP->T_DATA;
  }*/

  if (touch_panel->tp_int_stat.bit.FIFO_DATA_PENDING1)
  {
    tp.pt.x = touch_panel->tp_data.bit.TP_DATAX;
    tp.pt.y = touch_panel->tp_data.bit.TP_DATAX;

    if (!tp.ignore_fifo_data)
    {
      printf("x: %d y: %d\n", tp.pt.x, tp.pt.y);
      tp.ready = 1;
    }
    else
    {
      tp.ignore_fifo_data = false;
    }
  }

  if (touch_panel->tp_int_stat.bit.TP_UP_PENDING1)
  {
    tp.ignore_fifo_data = true;
    tp.ready = 0;
  }

  touch_panel->tp_int_stat.word = reg_val;

}

/**
 * @brief   touch panel read result
 */
int touch_panel_read(struct point *p)
{
  if (tp.ready)
  {
    p->x = tp.pt.x;
    p->y = tp.pt.y;
    return 1;
  }

  return 0;
}