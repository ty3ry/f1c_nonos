#include <stdio.h>
#include "sys.h"
#include "uart.h"
#include "timeout.h"
#include "sys_app.h"
#include "communication_iface.h"
#include "gpio.h"

TIMER tmrTick;
EventContext msg;

/***
 * Global IRQ
 */
void __attribute__((interrupt("IRQ"))) irq_handler (void)
{
    uart_comm_irq_handler();
}

int main (void)
{
  uint8_t state = 0;

  puts("\e[36mF1C100S UART Example\e[0m");

  GPIO_Init_t pio_init = {0};
  pio_init.pin = GPIO_PIN_12 ;
  pio_init.mode = CFG1_PE12_OUTPUT;
  pio_init.drive = MULTI_DRIVE_SELECT(12, DRIVE_LEVEL0);
  pio_init.pu_pd = PU_PD_CTRL(12, PU_PD_DISABLED);
  gpio_init(PE, &pio_init);

  /** init uart communication */
  communication_iface_init();

  TimeoutSet(&tmrTick, 1000);

  __asm__ __volatile__ ("msr cpsr_c,#0x53\n");  // SVC mode, IRQ enabled

  while(1)
  {
    msg.eventId = MSG_NONE;
    
    if (IsTimeout(&tmrTick))
    {
      TimeoutSet(&tmrTick, 1000);
      /** reserved */
    }

    communication_handler(&msg);

    /** do some process */
    switch (msg.eventId) {
      case MSG_TOGGLE_SOMETHING:
        gpio_toggle_pin(PE, GPIO_PIN_12);
        break;
      default: break;
    }

  }
}
