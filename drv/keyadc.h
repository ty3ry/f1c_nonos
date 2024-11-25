/******************************************************************************
 * @brief   header for key adc driver 
 *          KEYADC is 6-bit resolution ADC for key application.
 *          the KEYADC can work up to 250Hz conversion rate
 * 
 * @author  c_e (cosmas.es08@gmail.com)
 * 
 * @date    2024/11/23
 * 
 *****************************************************************************/
#ifndef KEYADC_H
#define KEYADC_H


/***
 * key adc control register
 */
typedef union {
    struct {
        uint32_t keyadc_en : 1;             // key adc enable
                                            // 0: disable
                                            // 1: enable

        uint32_t RESV1 : 1;                 // reserved

        uint32_t sample_rate : 2;           // KEYADC_SAMPLE_RATE.
                                            // KEYADC Sample Rate
                                            // 00: 250 Hz
                                            // 01: 125 Hz
                                            // 10: 62.5 Hz
                                            // 11: 32.25 Hz

        uint32_t LEVELB_VOL : 2;            // LEVELB_VOL.
                                            // Level B Corresponding Data Value setting (the real voltage value)
                                            // 00: 0x3C (~1.9v)
                                            // 01: 0x39 (~1.8v)
                                            // 10: 0x36 (~1.7v)
                                            // 11: 0x33 (~1.6v)

        uint32_t KEYADC_HOLD_EN : 1;        // KEYADC_HOLD_EN.
                                            // KEYADC Sample hold Enable
                                            // 0: Disable
                                            // 1: Enable

        uint32_t KEY_ADC_HOLD_KEY_EN : 1;   // KEY_ADC_HOLD_KEY_EN
                                            // KEY_ADC Hold Key Enable
                                            // 0: Disable
                                            // 1: Enable

        uint32_t LEVELA_B_CNT : 4;          // LEVELA_B_CNT.
                                            // Level A to Level B time threshold select, judge ADC convert value in level A
                                            // to level B in n+1 samples

        uint32_t KEY_MODE_SELECT : 2;       // KEY_MODE_SELECT.
                                            // Key Mode Select:
                                            // 00: Normal Mode
                                            // 01: Single Mode
                                            // 10: Continue Mode

        uint32_t RESV2 : 2;                 // reserved

        uint32_t CONT_TIME_SELECT : 4;      // CONTINUE_TIME_SELECT.
                                            // Continue Mode time select, one of 8*(N+1) sample as a valuable sample
                                            // data

        uint32_t RESV3 : 2;                 // reserved
        uint32_t RESV4 : 2;                 // reserved
        uint32_t FIRST_CONVERT_DLY : 8;     // ADC first convert delay setting, ADC is delayed by n samples

    } bit;
    uint32_t word;
} KEYADC_ctrl_t;

/**
 *  key adc interrupt control register
 */
typedef union {
    struct {
        uint32_t IRQ_EN : 1;                // ADC0_DATA_IRQ_EN.
                                            // ADC 0 Data IRQ Enable
                                            // 0: Disable
                                            // 1: Enable

        uint32_t KEYDOWN_EN : 1;            // ADC0_KEYDOWN_EN
                                            // ADC 0 Key Down Enable
                                            // 0: Disable
                                            // 1: Enable

        uint32_t HOLD_IRQ_EN : 1;           // ADC0_HOLD_IRQ_EN.
                                            // ADC 0 Hold Key IRQ Enable
                                            // 0: Disable
                                            // 1: Enable

        uint32_t ALRDY_HOLD_IRQ_EN : 1;     // ADC0_ALRDY_HOLD_IRQ_EN.
                                            // ADC 0 Already Hold IRQ Enable
                                            // 0: Disable
                                            // 1: Enable

        uint32_t KEYUP_IRQ_EN : 1;          // ADC0_KEYUP_IRQ_EN.
                                            // ADC 0 Key Up IRQ Enable
                                            // 0: Disable
                                            // 1: Enable
        uint32_t RESV : 27;

    } bit;
    uint32_t word;
} KEYADC_intc_t;

/** 
 * key adc interrupt status register 
 * */
typedef union {
    struct {
        uint32_t ADC0_DATA_PEND : 1;        // ADC0_DATA_PENDING.
                                            // ADC 0 Data IRQ Pending Bit
                                            // 0: No IRQ
                                            // 1: IRQ Pending
                                            // Notes: Writing 1 to the bit will clear it and its corresponding interrupt if the
                                            // interrupt is enable.

        uint32_t ADC0_KEYDOWN_PEND : 1;     // ADC0_KEYDOWN_PENDING.
                                            // ADC 0 Key Down IRQ Pending Bit
                                            // When General key pull down, the status bit is set and the interrupt line is set
                                            // if the corresponding interrupt is enabled.
                                            // 0: No IRQ
                                            // 1: IRQ Pending
                                            // Notes: Writing 1 to the bit will clear it and its corresponding interrupt if the
                                            // interrupt is enable

        uint32_t ADC0_HOLDKEY_PEND : 1;     // ADC0_HOLDKEY_PENDING.
                                            // ADC 0 Hold Key pending Bit
                                            // When Hold key pull down, the status bit is set and the interrupt line is set if
                                            // the corresponding interrupt is enabled.
                                            // 0: No IRQ
                                            // 1: IRQ Pending
                                            // Notes: Writing 1 to the bit will clear it and its corresponding interrupt if the
                                            // interrupt is enable

        uint32_t ADC0_ALRDY_HOLD_PEND : 1;  // ADC0_ALRDY_HOLD_PENDING.
                                            // ADC 0 Already Hold Pending Bit
                                            // When hold key pull down and pull the general key down, if the
                                            // corresponding interrupt is enabled.
                                            // 0: No IRQ
                                            // 1: IRQ Pending
                                            // Notes: Writing 1 to the bit will clear it and its corresponding interrupt if the
                                            // interrupt is enable 

        uint32_t ADC0_KEYUP_PEND : 1;       // ADC0_KEYUP_PENDING.
                                            // ADC 0 Key up pending Bit
                                            // When general key pull up, it the corresponding interrupt is enabled.
                                            // 0: No IRQ
                                            // 1: IRQ Pending
                                            // Notes: Writing 1 to the bit will clear it and its corresponding interrupt if the
                                            // interrupt is enable
        uint32_t RESV : 27;

    } bit;
    uint32_t word;
} KEYADC_ints_t;

/***
 * key adc data register
 */
typedef union {
    struct {
        uint32_t DATA : 6;                  // key adc data
        uint32_t RESV : 26;                 // reserved
    } bit;
    uint32_t word;
} KEYADC_data_t;


typedef struct {
    KEYADC_ctrl_t ctrl;
    KEYADC_intc_t int_ctrl;
    KEYADC_ints_t int_stat;
    KEYADC_data_t data;
} KeyAdc_t;


/** prototype function */
int key_adc_init(void);
/** end of prototype function */


#endif  /** end of KEYADC_H */
