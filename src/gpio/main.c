#include <stdio.h>
#include "sys.h"
#include "timeout.h"
#include "gpio.h"

#include "user_led.h"

TIMER tmrBlink;
TIMER tmrReadButton;

int main (void)
{
  uint8_t state = 0;
  uint8_t btn_state = 0;
  GPIO_Init_t pio_init = {0};

  printf("F1C100S GPIO Example\n");
  
  pio_init.pin = GPIO_PIN_12 | GPIO_PIN_10;
  pio_init.mode = CFG1_PE12_OUTPUT | CFG1_PE10_INPUT;
  pio_init.drive = MULTI_DRIVE_SELECT(12, DRIVE_LEVEL0) | MULTI_DRIVE_SELECT(10, DRIVE_LEVEL0);
  pio_init.pu_pd = PU_PD_CTRL(12, PU_PD_DISABLED) | PU_PD_CTRL(10, PU_EN);
  gpio_init(PE, &pio_init);

  TimeoutSet(&tmrBlink, 500);
  user_led_init();
 
  while(1)
  {

    /** read key button */
    if (IsTimeout(&tmrReadButton)) {
      TimeoutSet(&tmrReadButton, 100);

      if (gpio_get_pin(PE, GPIO_PIN_10)) {
        if(!btn_state)
        {
          btn_state = 1;
          printf("PE10 HIGH!\n");
        }
      }
      else {
        if (btn_state)
        {
          btn_state = 0;
          printf("PE10 LOW!\n");
        }
      }
    }

    /** set led blink  */
    /*if (IsTimeout(&tmrBlink)) {
      TimeoutSet(&tmrBlink, 250);
      state ^= 0x01;
      gpio_set_pin(PE, GPIO_PIN_12, state);
    }*/
   user_led_process();

  }

  return 0;

}
