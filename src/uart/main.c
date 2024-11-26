#include <stdio.h>
#include "sys.h"
#include "uart.h"
#include "timeout.h"

TIMER tmrTick;

void __attribute__((interrupt("IRQ"))) irq_handler (void)
{
  
}

int main (void)
{
  uint8_t recv;

  puts("\e[36mF1C100S UART Example\e[0m");

  struct UART_CFG cfg = {
    .port = SYS_UART_PORT,
    .bitrate = UART_BR(115200), 
    .parity = UART_PAR_NO, 
    .stop = UART_STP_1,
    .lenght = UART_8b 
  };
  
  /** init uart */
  uart_init(UART1, cfg);
  
  TimeoutSet(&tmrTick, 1000);

  __asm__ __volatile__ ("msr cpsr_c,#0x53\n");  // SVC mode, IRQ enabled
  while(1)
  {
    if (IsTimeout(&tmrTick))
    {
      TimeoutSet(&tmrTick, 1000);
      uart_put(UART1, '&');
    }

    recv = (uint8_t) uart_get(UART1);
    if (recv != 0xff ) {
      uart_put(UART1, recv);
    }
  }
}
