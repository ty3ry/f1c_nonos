/******************************************************************************
 * @brief   driver for f1c100/200 timer
 *          Timer 0/1/2 can take their inputs from LOSC or OSC24M. 
 *          They provide the operating system’s scheduler interrupt. 
 *          It is designed to offer maximum accuracy and efficient management, 
 *          even for systems with long or short response time.
 *          They provide 32-bit programmable down-counter and work in auto-reload mode 
 *          or no-reload mode
 * 
 * @author  c_e (cosmas.es08@gmail.com)
 * 
 * @date    2024/11/23
 * 
 *****************************************************************************/
#include "sys.h"

TIMER_t *tmr_cfg = 0;

/**
 * @brief   timer 0 init
 */
int TIM0_Init(uint32_t psc, uint32_t interval, uint8_t irq_en)
{
    if (!tmr_cfg)
        tmr_cfg = (TIMER_t*) TIM;

    tmr_cfg->T0_INTV.bit.TMR0_INTV_VALUE = interval;
    tmr_cfg->T0_CURV.bit.TMR0_CUR_VALUE = 0;
    tmr_cfg->T0_CTRL.bit.TMR0_CLK_PRES = psc;
    tmr_cfg->T0_CTRL.bit.TMR0_RELOAD = TMR_NO_RELOAD;
    tmr_cfg->T0_CTRL.bit.TMR0_CLK_SRC = TMR_CLK_SRC_OSC24M;
    tmr_cfg->T0_CTRL.bit.TMR0_MODE = TMR_MODE_CONT;
    tmr_cfg->T0_CTRL.bit.TMR0_EN = 1;
    tmr_cfg->IE.bit.TMR0_IRQ_EN = irq_en;

    return 0;
}

/**
 * @brief   timer 1 init
 */
int TIM1_Init(uint32_t psc, uint32_t interval, uint8_t irq_en)
{
    if (!tmr_cfg)
        tmr_cfg = (TIMER_t*) TIM;

    tmr_cfg->T1_INTV.bit.TMR1_INTV_VALUE = interval;
    tmr_cfg->T1_CURV.bit.TMR1_CUR_VALUE = 0;
    tmr_cfg->T1_CTRL.bit.TMR1_CLK_PRES = psc;
    tmr_cfg->T1_CTRL.bit.TMR1_RELOAD = TMR_NO_RELOAD;
    tmr_cfg->T1_CTRL.bit.TMR1_CLK_SRC = TMR_CLK_SRC_OSC24M;
    tmr_cfg->T1_CTRL.bit.TMR1_MODE = TMR_MODE_CONT;
    tmr_cfg->T1_CTRL.bit.TMR1_EN = 1;
    tmr_cfg->IE.bit.TMR1_IRQ_EN = irq_en;

    return 0;
}

/**
 * @brief   timer 2 init
 */
int TIM2_Init(uint32_t psc, uint32_t interval, uint8_t irq_en)
{
    if (!tmr_cfg)
        tmr_cfg = (TIMER_t*) TIM;

    tmr_cfg->T2_INTV.bit.TMR2_INTV_VALUE = interval;
    tmr_cfg->T2_CURV.bit.TMR2_CUR_VALUE = 0;
    tmr_cfg->T2_CTRL.bit.TMR2_CLK_PRES = psc;
    tmr_cfg->T2_CTRL.bit.TMR2_RELOAD = TMR_NO_RELOAD;
    tmr_cfg->T2_CTRL.bit.TMR2_CLK_SRC = TMR_CLK_SRC_OSC24M;
    tmr_cfg->T2_CTRL.bit.TMR2_MODE = TMR_MODE_CONT;
    tmr_cfg->T2_CTRL.bit.TMR2_EN = 1;
    tmr_cfg->IE.bit.TMR2_IRQ_EN = irq_en;

    return 0;

}


TIMER_t *get_tim_handler(void)
{
    return (tmr_cfg);
}