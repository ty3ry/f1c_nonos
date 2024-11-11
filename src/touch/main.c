#include <stdio.h>
#include "sys.h"
#include "touch.h"

#define IRQ_EN  (1)

bool ignore_fifo_data = true;

void __attribute__((interrupt("IRQ"))) irq_handler (void)
{
  u32 x, y;
  u32 reg_val;
  u32 temp_data;

  reg_val = TP->INT_FIFO_STAT;
  printf("reg_val: 0x%08X \n", reg_val);

  /*if (reg_val & TEMP_DATA_PENDING) {
    temp_data = TP->T_DATA;
  }*/

  if (reg_val & FIFO_DATA_PENDING) {
      x = TP->DATA;
      y = TP->DATA;   

      if (!ignore_fifo_data) {
        //printf("x: %d y: %d\n", x, y);
      }
      else {
        ignore_fifo_data = false;
      }
      
  }

  /*if (reg_val & TP_DOWN_PENDING) {
      TP->INT_FIFO_STAT = (1<<0);
      printf("Touch Down IRQ!\n");
  }*/

  if (reg_val & TP_UP_PENDING) {
    ignore_fifo_data = true;
    printf("TP Up Event\n");
  }

  TP->INT_FIFO_STAT = reg_val;
}

int touch_init (void)
{
  printf("Start init touch\n");

  if ( tp_init() != 0 ) 
  {
    /** do error handler */
    printf("\e[31m Error on init touch! \e[0m\n");
    return -1;
  }
  
#if (IRQ_EN)
  /** IRQ init */
  INT->BASE_ADDR = 0;
  INT->MASK[0] = ~(1 << IRQ_TP);
  INT->MASK[1] = 0xFFFFFFFF;
  INT->EN[0] = (1 << IRQ_TP);
  INT->EN[1] = 0;
#endif

}

int main (void)
{
  u32 x, y;

  printf("F1C100S Touch Example\n");

  touch_init();
  __asm__ __volatile__ ("msr cpsr_c,#0x53\n");  // SVC mode, IRQ enabled
  
  printf("\e[32mEnter main loop!\e[0m\n");
  while(1)
  {
    /** reserved */
    delay(50);
    /*x = TP->DATA;
    y = TP->DATA;
    printf("x: %d y: %d\n", x, y);*/

  }
}
