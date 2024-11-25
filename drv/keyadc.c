/******************************************************************************
 * @brief   driver for key adc  
 *          KEYADC is 6-bit resolution ADC for key application.
 *          the KEYADC can work up to 250Hz conversion rate
 * 
 * @author  c_e (cosmas.es08@gmail.com)
 * 
 * @date    2024/11/23
 * 
 *****************************************************************************/
#include "sys.h"
#include "keyadc.h"

KeyAdc_t key_adc;

/**
 * @brief   keyadc init
 */
int key_adc_init(void)
{
    key_adc.ctrl.bit.keyadc_en = 1;
    key_adc.ctrl.bit.KEY_MODE_SELECT = 2;   // continues mode
    ADC->CTRL = key_adc.ctrl.word;

    key_adc.int_ctrl.bit.KEYUP_IRQ_EN = 1;
    ADC->INTC = key_adc.int_ctrl.word;

    key_adc.int_stat.word = ADC->INTS;

    return 0;
}

