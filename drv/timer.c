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