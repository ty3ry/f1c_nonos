#include <stdio.h>
#include "sys.h"
#include "touch.h"

volatile int timer_event = 0;

void __attribute__((interrupt("IRQ"))) irq_handler (void)
{
  if (TP->INT_FIFO_STAT & FIFO_DATA_PENDING) {
      TP->INT_FIFO_STAT = (1<<16);
      
  }
}

void touch_init (void)
{
  if ( tp_init() != 0 ) {
    /** do error handler */
  }
  

}

int main (void)
{
  printf("F1C100S Touch Example\n");

  touch_init();
  __asm__ __volatile__ ("msr cpsr_c,#0x53\n");  // SVC mode, IRQ enabled
  
  while(1)
  {
    /** reserved */
  }
}
