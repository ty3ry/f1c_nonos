/******************************************************************************
 * @brief   driver for f1c100/200 interrupt controller
 *  
 *          Interrupt controller (INTC) handles all interrupt sources connected 
 *          to it. It has a set of registers for managing interrupt sources 
 *          and interrupt behavior. 
 *          It provides a priority controller for serving higher interrupt 
 *          even if a lower interrupt is serving. 
 *          It also provides a fast forcing way for these interrupt sources 
 *          which desire to have a fast interrupt request to CPU though they 
 *          don't generate pending
 * 
 * @author  c_e (cosmas.es08@gmail.com)
 * 
 * @date    2024/12/1
 * 
 *****************************************************************************/
#include "intc.h"

/**
 * INT->BASE_ADDR = 0;
  INT->MASK[0] = ~(1 << IRQ_TIM0);
  INT->MASK[1] = 0xFFFFFFFF;
  INT->EN[0] = (1 << IRQ_TIM0);
  INT->EN[1] = 0;
 */

uint8_t init_mask = 0;

/**
 * @brief   init interrupt controller
 * @param   irq_src interrupt source
 */
int IRQ_Init(uint8_t irq_src, uint8_t prio)
{
    INTC_t *pintc = INT;
    uint32_t prio_mask = 0;

    if (irq_src > IRQ_NUM-1)
    {
        return -1;
    }

    if (!init_mask) {
        init_mask = 1;
        pintc->MASK[0] = 0xFFFFFFFF;
        pintc->MASK[1] = 0xFFFFFFFF;
    }

    prio_mask = ~(irq_src*2);

    pintc->BASE_ADDR.bit.INTC_BASE_ADDR = 0x00;

    if (irq_src < 32) {
        pintc->MASK[0] &= ~(1<<irq_src);
        pintc->EN[0] |= (1<<irq_src);

    } else if (irq_src < 64) {
        pintc->MASK[1] &= ~(1<<irq_src);
        pintc->EN[1] |= (1<<irq_src);
    }

    /** priority */
    if (irq_src < 16) {
        pintc->PRIO[0] |= (pintc->PRIO[0] & prio_mask) | (1<<irq_src); 
    }
    else if (irq_src < 32) {
        pintc->PRIO[1] |= (pintc->PRIO[1] & prio_mask) | (1<<irq_src); 
    }
    else if (irq_src < 48) {
        pintc->PRIO[2] |= (pintc->PRIO[2] & prio_mask) | (1<<irq_src); 
    }
    else if (irq_src < 64) {
        pintc->PRIO[3] |= (pintc->PRIO[3] & prio_mask) | (1<<irq_src); 
    }

    return 0;
}