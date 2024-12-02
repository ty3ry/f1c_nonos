#include <stdio.h>
#include "sys.h"
#include "timeout.h"
#include "spi.h"

TIMER tmrSend;

int main (void)
{
  uint8_t data[10];
  int i = 0;

  printf("F1C100S GPIO Example\n");
  for(i = 0; i < 10; i++) {
    data[i] = 0x55;
  }
  spi_init_periph();

  TimeoutSet(&tmrSend, 100);
 
  while(1)
  {
    if (IsTimeout(&tmrSend))
    {
      TimeoutSet(&tmrSend, 100);
      spi_transmit(&data, 10);
    }
  }

  return 0;

}
