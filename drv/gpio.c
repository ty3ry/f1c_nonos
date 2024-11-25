/******************************************************************************
 * @brief   driver for f1c100/200 gpio 
 *          The chip has 6 ports for multi-functional input/out pins. They are 
 *          shown below:
 *          - Port A(PA): 4 input/output port
 *          - Port B(PB): 4 input/output port
 *          - Port C(PC): 4 input/output port
 *          - Port D(PD): 22 input/output port
 *          - Port E(PE) : 13 input/output port
 *          - Port F(PF) : 6 input/output port
 *          
 *          For various system configurations, these ports can be easily 
 *          configured by software. 
 *          All these ports can be configured as
 *          GPIO if multiplexed functions are not used. The total 4 group 
 *          external PIO interrupt sources are supported and interrupt mode 
 *          can be configured by software
 * 
 * @author  c_e (cosmas.es08@gmail.com)
 * 
 * @date    2024/11/23
 * 
 *****************************************************************************/
#include "sys.h"

int gpio_init(PIO_T *port, GPIO_Init_t *gpio_init)
{
    uint32_t temp = 0;

    if (gpio_init->pin < 256)
    {
        temp = port->CFG0;
        port->CFG0 = gpio_init->mode;
    }
    else if (gpio_init->pin < 65536)
    {
        port->CFG1 = gpio_init->mode;;
    }
    else if (gpio_init->pin < 16777216)
    {
        port->CFG2 = gpio_init->mode;;
    }

    port->PUL0 = gpio_init->pu_pd;
    port->DRV0 = gpio_init->drive;

    return 0;
}

/***
 * @brief   set gpio pin state
 * 
 * @param   [in] port: port id
 * @param   [in] pin: pin value (position)
 * @param   [in] state: pin state
 *                      0: low
 *                      1: high
 * 
 * @return  none
 */
void gpio_set_pin(PIO_T *port, uint32_t pin, uint8_t state)
{
    if (state) {
        port->DAT |= pin;
    }
    else {
        port->DAT &= ~(pin);
    }
}

/**
 * @brief   read gpio pin
 * @param   port gpio port
 * @param   pin     gpio pin number
 * 
 * @retval  bool current pin state
 */
bool gpio_get_pin(PIO_T *port, uint32_t pin)
{
    return (port->DAT & pin);
}

/**
 * @brief   toggle gpio
 * @param   port gpio port
 * @param   pin     gpio pin number
 */
void gpio_toggle_pin(PIO_T *port, uint32_t pin)
{
    static uint8_t state = 0x00;

    if (state ^= 0x01) {
        port->DAT = 1;
    } else {
        port->DAT = 0;
    }
}
