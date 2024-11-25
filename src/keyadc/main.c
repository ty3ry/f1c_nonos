#include <stdio.h>
#include "sys.h"
#include "timeout.h"

TIMER tmrBlink;

void __attribute__((interrupt("IRQ"))) irq_handler (void)
{
  
}

int main (void)
{
  printf("F1C100S KEYADC Example\n");

  key_adc_init();

  INT->BASE_ADDR = 0;
  INT->MASK[0] = ~(1 << IRQ_KEYADC);
  INT->MASK[1] = 0xFFFFFFFF;
  INT->EN[0] = (1 << IRQ_KEYADC);
  INT->EN[1] = 0;

  __asm__ __volatile__ ("msr cpsr_c,#0x53\n");  // SVC mode, IRQ enabled
  
  while(1)
  {

  }

  return 0;

}
