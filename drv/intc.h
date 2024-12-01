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
#ifndef INTC_H
#define INTC_H

#include "f1c100s.h"


/** Interrupt Vector Register */
typedef union {
    struct {
        uint32_t RO : 2;
        uint32_t INTC_VECTOR_ADDR : 30;
    } bit;
    uint32_t word;
} Vector_t;


/** Interrupt Base Address Register */
typedef union {
    struct {
        uint32_t RO : 2;
        uint32_t INTC_BASE_ADDR : 30;
    } bit;
    uint32_t word;
} BASEADDR_t;

/** NMI Interrupt Control Register */
typedef union {
    struct {
        uint32_t NMI_SRC_TYPE : 2;
        uint32_t RESV : 30;
    } bit;
    uint32_t word;
} NMIIC_t;

/** Interrupt IRQ Pending 0 Register */
typedef union {
    struct {
        uint32_t INTC_PEND0 : 32;
    } bit;
    uint32_t word;
} IRQ_PEND0_t;

/** Interrupt IRQ Pending 1 Register */
typedef union {
    struct {
        uint32_t INTC_PEND1 : 32;
    } bit;
    uint32_t word;
} IRQ_PEND1_t;

/** Interrupt Enable 0 Register */
typedef union {
    struct {
        uint32_t INTC_EN0 : 32;
    } bit;
    uint32_t word;
} IRQ_EN0_t;

/** Interrupt Enable 1 Register */
typedef union {
    struct {
        uint32_t INTC_EN1 : 32;
    } bit;
    uint32_t word;
} IRQ_EN1_t;

/** Interrupt Mask Register 0 */
typedef union {
    struct {
        uint32_t INTC_MASK0 : 32;
    } bit;
    uint32_t word;
} IRQ_MASK0_t;

/** Interrupt Mask Register 1 */
typedef union {
    struct {
        uint32_t INTC_MASK1 : 32;
    } bit;
    uint32_t word;
} IRQ_MASK1_t;

/** Interrupt Response Register 0 */
typedef union {
    struct {
        uint32_t INTC_RESP0 : 32;
    } bit;
    uint32_t word;
} IRR0_t;

/** Interrupt Response Register 1 */
typedef union {
    struct {
        uint32_t INTC_RESP1 : 32;
    } bit;
    uint32_t word;
} IRR1_t;

/** Interrupt Fast Forcing Register 0 */
typedef union {
    struct {
        uint32_t INTC_FF0 : 32;
    } bit;
    uint32_t word;
} IFF0_t;

/** Interrupt Fast Forcing Register 1 */
typedef union {
    struct {
        uint32_t INTC_FF1 : 32;
    } bit;
    uint32_t word;
} IFF1_t;

/** Interrupt Source Priority Register 0 */
typedef union {
    struct {
        uint32_t RESV1 : 2;
        uint32_t IRQ1_PRIO : 2;
        uint32_t IRQ2_PRIO : 2;
        uint32_t IRQ3_PRIO : 2;
        uint32_t IRQ4_PRIO : 2;
        uint32_t IRQ5_PRIO : 2;
        uint32_t IRQ6_PRIO : 2;
        uint32_t IRQ7_PRIO : 2;
        uint32_t IRQ8_PRIO : 2;
        uint32_t IRQ9_PRIO : 2;
        uint32_t IRQ10_PRIO : 2;
        uint32_t IRQ11_PRIO : 2;
        uint32_t IRQ12_PRIO : 2;
        uint32_t IRQ13_PRIO : 2;
        uint32_t IRQ14_PRIO : 2;
        uint32_t IRQ15_PRIO : 2;
    } bit;
    uint32_t word;
} ISP0_t;


/** Interrupt Source Priority Register 1 */
typedef union {
    struct {
        uint32_t IRQ16_PRIO : 2;
        uint32_t IRQ17_PRIO : 2;
        uint32_t IRQ18_PRIO : 2;
        uint32_t IRQ19_PRIO : 2;
        uint32_t IRQ20_PRIO : 2;
        uint32_t IRQ21_PRIO : 2;
        uint32_t IRQ22_PRIO : 2;
        uint32_t IRQ23_PRIO : 2;
        uint32_t IRQ24_PRIO : 2;
        uint32_t IRQ25_PRIO : 2;
        uint32_t IRQ26_PRIO : 2;
        uint32_t IRQ27_PRIO : 2;
        uint32_t IRQ28_PRIO : 2;
        uint32_t IRQ29_PRIO : 2;
        uint32_t IRQ30_PRIO : 2;
        uint32_t IRQ31_PRIO : 2;
    } bit;
    uint32_t word;
} ISP1_t;

/** Interrupt Source Priority Register 2 */
typedef union {
    struct {
        uint32_t IRQ32_PRIO : 2;
        uint32_t IRQ33_PRIO : 2;
        uint32_t IRQ34_PRIO : 2;
        uint32_t IRQ35_PRIO : 2;
        uint32_t IRQ36_PRIO : 2;
        uint32_t IRQ37_PRIO : 2;
        uint32_t IRQ38_PRIO : 2;
        uint32_t IRQ39_PRIO : 2;
        uint32_t IRQ40_PRIO : 2;
        uint32_t IRQ41_PRIO : 2;
        uint32_t IRQ42_PRIO : 2;
        uint32_t IRQ43_PRIO : 2;
        uint32_t IRQ44_PRIO : 2;
        uint32_t IRQ45_PRIO : 2;
        uint32_t IRQ46_PRIO : 2;
        uint32_t IRQ47_PRIO : 2;
    } bit;
    uint32_t word;
} ISP2_t;

/** Interrupt Source Priority Register 3 */
typedef union {
    struct {
        uint32_t IRQ48_PRIO : 2;
        uint32_t IRQ49_PRIO : 2;
        uint32_t IRQ50_PRIO : 2;
        uint32_t IRQ51_PRIO : 2;
        uint32_t IRQ52_PRIO : 2;
        uint32_t IRQ53_PRIO : 2;
        uint32_t IRQ54_PRIO : 2;
        uint32_t IRQ55_PRIO : 2;
        uint32_t IRQ56_PRIO : 2;
        uint32_t IRQ57_PRIO : 2;
        uint32_t IRQ58_PRIO : 2;
        uint32_t IRQ59_PRIO : 2;
        uint32_t IRQ60_PRIO : 2;
        uint32_t IRQ61_PRIO : 2;
        uint32_t IRQ62_PRIO : 2;
        uint32_t IRQ63_PRIO : 2;
    } bit;
    uint32_t word;
} ISP3_t;


enum {
    IRQ_PRIO_0,     // lowest
    IRQ_PRIO_1,
    IRQ_PRIO_2,
    IRQ_PRIO_3,     // highest
};

/** Interrupt Control Register */
typedef struct {
    __IO Vector_t    VECTOR;
    __IO BASEADDR_t  BASE_ADDR;
    __IO uint32_t    RESV1;
    __IO NMIIC_t     NMI_CTRL;
    __IO uint32_t    PEND[4];
    __IO uint32_t    EN[4];
    __IO uint32_t    MASK[4];
    __IO uint32_t    RESP[4];
    __IO uint32_t    FF[4];
    __IO uint32_t    PRIO[4];
} INTC_t;


/** prototype function */
int IRQ_Init(uint8_t irq_src, uint8_t prio);
/** end of prototype function */

#endif /** INTC_H */
