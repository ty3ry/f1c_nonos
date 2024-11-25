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
#ifndef TIMER_H
#define TIMER_H

// Timer IRQ enable register
typedef union {
    struct {
        uint32_t TMR0_IRQ_EN : 1;       // TMR0_IRQ_EN.
                                        // Timer 0 Interrupt Enable.
                                        // 0: No effect,
                                        // 1: Timer 0 Interval Value reached interrupt enable

        uint32_t TMR1_IRQ_EN : 1;       // TMR1_IRQ_EN.
                                        // Timer 1 Interrupt Enable.
                                        // 0: No effect,
                                        // 1: Timer 1 Interval Value reached interrupt enable

        uint32_t TMR2_IRQ_EN : 1;       // TMR2_IRQ_EN.
                                        // Timer 2 Interrupt Enable.
                                        // 0: No effect,
                                        // 1: Timer 2 Interval Value reached interrupt enable

    } bit;
    uint32_t word;
} TIM_IRQ_Enable_t;

// Timer IRQ status register
/**
 * TMRn_IRQ_PEND.
 * Timer 0 IRQ Pending. Set 1 to the bit will clear it.
 * 0: No effect,
 * 1: Pending, timer 0 interval value is reached.
 */
typedef union {
    struct {
        uint32_t TMR0_IRQ_PEND : 1;    
        uint32_t TMR1_IRQ_PEND : 1;  
        uint32_t TMR2_IRQ_PEND : 1;     
    } bit;
    uint32_t word;
} TIM_IRQ_Status_t;


#endif /** end of TIMER_H */