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
        uint32_t RESV : 29; 
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


/** TIMER ID */
enum {
    TIMER0 = 0,
    TIMER1,
    TIMER2,
};

/** timer reload */
enum {
    TMR_NO_RELOAD = 0,
    TMR_RELOAD_EN,      // After the bit is set, 
                        // it can not be written again before it’s cleared automatically
};

/** timer clock source */
enum {
    TMR_CLK_SRC_LOSC = 0,
    TMR_CLK_SRC_OSC24M,
};

/** timer prescaller */
enum {
    TMR_CLK_PSC_1 = 0,
    TMR_CLK_PSC_2,
    TMR_CLK_PSC_4,
    TMR_CLK_PSC_8,
    TMR_CLK_PSC_16,
    TMR_CLK_PSC_32,
    TMR_CLK_PSC_64,
    TMR_CLK_PSC_128,
};

/** timer mode */
enum {
    TMR_MODE_CONT = 0,
    TMR_MODE_SINGLE,
};

/** timer function pointer, used for timer IRQ */
typedef void (*tmr_irq_func_t)(void);

/**
 * TIMER register
 */
typedef struct {
    __IO TIM_IRQ_Enable_t    IE;
    __IO TIM_IRQ_Status_t    IS;
    __IO uint32_t            RESV1[2];
    __IO TMR0_Ctrl_t         T0_CTRL;
    __IO TMR0_Interval_t     T0_INTV;
    __IO TMR0_Currval_t      T0_CURV;
    __IO uint32_t            RESV2;
    __IO TMR1_Ctrl_t         T1_CTRL;
    __IO TMR1_Interval_t     T1_INTV;    
    __IO TMR1_Currval_t      T1_CURV;
    __IO uint32_t            RESV3;
    __IO TMR2_Ctrl_t         T2_CTRL;
    __IO TMR2_Interval_t     T2_INTV;
    __IO TMR2_Currval_t      T2_CURV;
    __IO uint32_t            RESV4[17];
    __IO AVS_CountCtrl_t     AVS_CTRL;
    __IO AVS_CNT0_t          AVS_CNT0;
    __IO AVS_CNT1_t          AVS_CNT1;
    __IO AVS_CNTDIV_t        AVS_DIV;
    __IO uint32_t            RESV5[4];
    __IO WDG_IRQ_t           WDG_IE;
    __IO WDG_STAT_t          WDG_IS;
    __IO uint32_t            RESV6[2];
    __IO WDG_Ctrl_t          WDG_CTRL;
    __IO WDG_CFG_t           WDG_CFG;
    __IO WDG_MODE_t          WDG_MODE;
} TIMER_t;

/** prototype function */
int TIM0_Init(uint32_t psc, uint32_t interval, uint8_t irq_en);
int TIM1_Init(uint32_t psc, uint32_t interval, uint8_t irq_en);
int TIM2_Init(uint32_t psc, uint32_t interval, uint8_t irq_en);
TIMER_t *get_tim_handler(void);
/** end of prototype function */

#endif /** end of TIMER_H */
