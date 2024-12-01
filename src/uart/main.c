/***
 * @brief   uart example to communicate with external mcu or PC with
 *          some user defined protocol.
 *          uart-rx with interrupt also test with timer IRQ 
 */

#include <stdio.h>
#include "sys.h"
#include "uart.h"
#include "timeout.h"
#include "sys_app.h"
#include "communication_iface.h"
#include "gpio.h"
#include "timer.h"

TIMER tmrTick;
EventContext msg;
volatile int timer_event = 0;


static void tim_irq_handler(void)
{
  static int timer_count = 1000;

  TIMER_t *tim = get_tim_handler();

  /** timer 0 */
  if(tim->IS.bit.TMR0_IRQ_PEND)
  {
    tim->IS.bit.TMR0_IRQ_PEND = 1;

    if(--timer_count == 0)
    {
      timer_count = 1000;
      timer_event = 1;
    }
  }

  /** timer 1 */
  if(tim->IS.bit.TMR1_IRQ_PEND)
  {
    static int count = 0;
    tim->IS.bit.TMR1_IRQ_PEND = 1;
    if (count++ > 500)
    {
      count = 0;
      gpio_toggle_pin(PD, GPIO_PIN_21);
    }
  }

  /** timer 2 */
  if(tim->IS.bit.TMR0_IRQ_PEND)
  {
    tim->IS.bit.TMR0_IRQ_PEND = 1;
  }

}

/***
 * Global IRQ
 */
void __attribute__((interrupt("IRQ"))) irq_handler (void)
{
    uart_comm_irq_handler();

    tim_irq_handler();
}



int main (void)
{
  uint8_t state = 0;

  puts("\e[36mF1C100S UART Example\e[0m");

  GPIO_Init_t pio_init = {0};
  pio_init.pin = GPIO_PIN_4 ;
  pio_init.mode = CFG0_PE4_OUTPUT;
  pio_init.drive = MULTI_DRIVE_SELECT(4, DRIVE_LEVEL0);
  pio_init.pu_pd = PU_PD_CTRL(4, PU_PD_DISABLED);
  gpio_init(PE, &pio_init);

  pio_init.pin = GPIO_PIN_21 ;
  pio_init.mode = CFG2_PD21_OUTPUT;
  pio_init.drive = MULTI_DRIVE_SELECT(21, DRIVE_LEVEL0);
  pio_init.pu_pd = PU_PD_CTRL(21, PU_PD_DISABLED);
  gpio_init(PD, &pio_init);

  IRQ_Init(IRQ_TIM0, IRQ_PRIO_0);
  TIM0_Init(TMR_CLK_PSC_8, 3000, 1);

  IRQ_Init(IRQ_TIM1, IRQ_PRIO_1);
  TIM1_Init(TMR_CLK_PSC_8, 3000, 1);

  /** 
   * init uart communication 
   * */
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
        gpio_toggle_pin(PE, GPIO_PIN_4);
        break;
      default: break;
    }

    /** timer check */
    if(timer_event)
    {
      timer_event = 0;
      putchar('*');
    }

  }
}
