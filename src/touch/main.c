#include <stdio.h>
#include "sys.h"
#include "touch.h"
#include "gpio.h"

volatile int timer_event = 0;

void __attribute__((interrupt("IRQ"))) irq_handler(void)
{
  static int timer_count = 1000;

  touch_panel_irq_handler();

  if(TIM->IS)
  {
    TIM->IS = 1;
    if(--timer_count == 0)
    {
      timer_count = 1000;
      timer_event = 1;
    }
  }
}


void tim_init (void)
{
  TIM->T0_INTV = 3000;  // 24MHz / 8 = 3MHz / 3000 = 1000Hz(1mS)
  TIM->T0_CURV = 0;
  TIM->T0_CTRL = 0x35;
  TIM->IE = 1;
}

int main (void)
{
  GPIO_Init_t pio_init;

  printf("F1C100S Touch Example\n");

  pio_init.pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
  pio_init.mode = CFG0_PA0_TP_X1 | CFG0_PA1_TP_X2 | CFG0_PA2_TP_Y1 | CFG0_PA3_TP_Y2;
  gpio_init(PA, &pio_init);

  tim_init();

  if (touch_panel_init() != 0) {
    printf("Error TP Init!\n");
    return -1;
  }

  /** IRQ init */
  INT->BASE_ADDR = 0;
  INT->MASK[0] = ~((1 << IRQ_TP) | (1 << IRQ_TIM0));
  INT->MASK[1] = 0xFFFFFFFF;
  INT->EN[0] = (1 << IRQ_TP) | (1 << IRQ_TIM0);
  INT->EN[1] = 0;

  __asm__ __volatile__ ("msr cpsr_c,#0x53\n");  // SVC mode, IRQ enabled
  
  while(1)
  {
    if(timer_event)
    {
      timer_event = 0;
      putchar('*');
    }
  }
}
