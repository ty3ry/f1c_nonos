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


/** timer 0 control register */
typedef union {
    struct {
        uint32_t TMR0_EN : 1;
        uint32_t TMR0_RELOAD : 1;
        uint32_t TMR0_CLK_SRC : 2;
        uint32_t TMR0_CLK_PRES : 3;
        uint32_t TMR0_MODE : 1;
        uint32_t RESV : 24;
    } bit;
    uint32_t word;
}TMR0_Ctrl_t;

/** Timer 0 interval value register */
typedef union {
    struct {
        uint32_t TMR0_INTV_VALUE : 32;
    } bit;
    uint32_t word;
}TMR0_Interval_t;

/*** timer 0 current value register */
typedef union {
    struct {
        uint32_t TMR0_CUR_VALUE : 32;
    } bit;
    uint32_t word;
}TMR0_Currval_t;

/** Timer 1 control register */
typedef union {
    struct {
        uint32_t TMR1_EN : 1;
        uint32_t TMR1_RELOAD : 1;
        uint32_t TMR1_CLK_SRC : 2;
        uint32_t TMR1_CLK_PRES : 3;
        uint32_t TMR1_MODE : 1;
        uint32_t RESV : 24;
    } bit;
    uint32_t word;
}TMR1_Ctrl_t;

/** Timer 1 interval value register */
typedef union {
    struct {
        uint32_t TMR1_INTV_VALUE : 32;
    } bit;
    uint32_t word;
}TMR1_Interval_t;

/*** timer 1 current value register */
typedef union {
    struct {
        uint32_t TMR1_CUR_VALUE : 32;
    } bit;
    uint32_t word;
}TMR1_Currval_t;


/** Timer 2 control register */
typedef union {
    struct {
        uint32_t TMR2_EN : 1;
        uint32_t TMR2_RELOAD : 1;
        uint32_t TMR2_CLK_SRC : 2;
        uint32_t TMR2_CLK_PRES : 3;
        uint32_t TMR2_MODE : 1;
        uint32_t RESV : 24;
    } bit;
    uint32_t word;
}TMR2_Ctrl_t;

/** Timer 2 interval value register */
typedef union {
    struct {
        uint32_t TMR2_INTV_VALUE : 32;
    } bit;
    uint32_t word;
}TMR2_Interval_t;

/*** timer 2 current value register */
typedef union {
    struct {
        uint32_t TMR2_CUR_VALUE : 32;
    } bit;
    uint32_t word;
}TMR2_Currval_t;


/** AVS counter control register */
typedef union {
    struct {
        uint32_t AVS_CNT0_EN : 1;
        uint32_t AVS_CNT1_EN : 1;
        uint32_t RESV1 : 6;
        uint32_t AVS_CNT0_PS : 1;
        uint32_t AVS_CNT1_PS : 1;
        uint32_t RESV2 : 22;
    } bit;
    uint32_t word;
}AVS_CountCtrl_t;

/** AVS counter 0 register */
typedef union {
    struct {
        uint32_t AVS_CNT0 : 32;
    } bit;
    uint32_t word;
}AVS_CNT0_t;


/** AVS counter 1 register */
typedef union {
    struct {
        uint32_t AVS_CNT1 : 32;
    } bit;
    uint32_t word;
}AVS_CNT1_t;


/** AVS counter divisor register */
typedef union {
    struct {
        uint32_t AVS_CNT0_D : 12;
        uint32_t RESV1 : 4;
        uint32_t AVS_CNT1_D : 12;
        uint32_t RESV2 : 4;
    } bit;
    uint32_t word;
}AVS_CNTDIV_t;

/*** watchdog IRQ Enable register */
typedef union {
    struct {
        uint32_t WDOG_IRQ_EN : 1;
        uint32_t RESV : 31;
    } bit;
    uint32_t word;
}WDG_IRQ_t;

/*** watchdog status register */
typedef union {
    struct {
        uint32_t WDOG_IRQ_PEND : 1;
        uint32_t RESV : 31;
    } bit;
    uint32_t word;
}WDG_STAT_t;

/** Wathcdog control register */
typedef union {
    struct {
        uint32_t WDOG_RSTART : 1;
        uint32_t WDOG_KEY_FIELD : 12;
        uint32_t RESV : 19;
    } bit;
    uint32_t word;
}WDG_Ctrl_t;


/** Watchdog configuration register */
typedef union {
    struct {
        uint32_t WDOG_CONFIG : 2;
        uint32_t RESV : 30;
    } bit;
    uint32_t word;
}WDG_CFG_t;


/** Watchdog mode register */
typedef union {
    struct {
        uint32_t WDOG_EN : 1;
        uint32_t RESV1 : 4;
        uint32_t WDOG_INTV_VALUE : 4;
        uint32_t RESV2 : 23;
    } bit;
    uint32_t word;
}WDG_MODE_t;

/**
 * TIMER register
 */
typedef struct {
    TIM_IRQ_Enable_t    IE;
    TIM_IRQ_Status_t    IS;
    uint32_t            RESV1[2];
    TMR0_Ctrl_t         T0_CTRL;
    TMR0_Interval_t     T0_INTV;
    TMR0_Currval_t      T0_CURV;
    uint32_t            RESV2;
    TMR1_Ctrl_t         T1_CTRL;
    TMR1_Interval_t     T1_INTV;    
    TMR1_Currval_t      T1_CURV;
    uint32_t            RESV3;
    TMR2_Ctrl_t         T2_CTRL;
    TMR2_Interval_t     T2_INTV;
    TMR2_Currval_t      T2_CURV;
    uint32_t            RESV4[17];
    AVS_CountCtrl_t     AVS_CTRL;
    AVS_CNT0_t          AVS_CNT0;
    AVS_CNT1_t          AVS_CNT1;
    AVS_CNTDIV_t        AVS_DIV;
    uint32_t            RESV5[4];
    WDG_IRQ_t           WDG_IE;
    WDG_STAT_t          WDG_IS;
    uint32_t            RESV6[2];
    WDG_Ctrl_t          WDG_CTRL;
    WDG_CFG_t           WDG_CFG;
    WDG_MODE_t          WDG_MODE;
} TIMER_t;


#endif /** end of TIMER_H */
