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

/***
 * @brief   gpio initialization function
 * @param   port port ID
 * @param   gpio_init gpio configuration
 * @retval  init status
 */
int gpio_init(PIO_T *port, GPIO_Init_t *gpio_init)
{
    uint8_t pos = 0;
    uint32_t mask = 0x00;
    uint32_t pin = gpio_init->pin;

    if (gpio_init->pin < 0x100) {
        pin = (pin >> 0);
    }
    else if (gpio_init->pin < 0x100000) {
        pin = (pin >> 8);
    }
    else if (gpio_init->pin < 0x1000000) {
        pin = (pin >> 16);
    }

    while(pos < 8)
    {
        if ((1<<pos) & pin)
        {
            mask = (mask | (0x07<<(4*pos)));
        }
        pos += 1;
    }

    if (gpio_init->pin < 0x100)
    {
        port->CFG0 = (port->CFG0 & ~(mask)) | gpio_init->mode;
    }
    else if (gpio_init->pin < 0x10000)
    {
        port->CFG1 = (port->CFG1 & ~(mask)) | gpio_init->mode;
    }
    else if (gpio_init->pin < 0x1000000)
    {
        port->CFG2 = (port->CFG2 & ~(mask)) | gpio_init->mode;
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
    if (port->DAT & pin) {
        port->DAT &= ~(pin);
    } else {
        port->DAT |= pin;
    }
}
