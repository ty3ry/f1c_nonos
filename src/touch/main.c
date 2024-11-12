#include <stdio.h>
#include "sys.h"
#include "touch.h"


void __attribute__((interrupt("IRQ"))) irq_handler(void)
{
  tp_irq_handler();
}


int main (void)
{
  u32 x, y;

  printf("F1C100S Touch Example\n");

  if (tp_init() != 0) {
    printf("Error TP Init!\n");
    return -1;
  }

  __asm__ __volatile__ ("msr cpsr_c,#0x53\n");  // SVC mode, IRQ enabled
  
  while(1)
  {
    /** reserved */
    delay(50);

  }
}
