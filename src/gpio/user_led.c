/**
 * just for led test purpose 
 * 
*/
#include "sys.h"
#include "timeout.h"

#define USER_LED_PORT   PE
#define USER_LED_PIN    GPIO_PIN_12

TIMER timer_user_led;

#define LED_BLINK_MODE_SYS_CYCLE        1
#define LED_BLINK_MODE_BLINK_TICK       2
#define LED_BLINK_MODE_BLINK_PERIODE    3

#define BLINK_MODE  (LED_BLINK_MODE_BLINK_TICK)

#if (BLINK_MODE==LED_BLINK_MODE_BLINK_TICK)
#define MULTIPLIER      (1)
#define T_ON            (MULTIPLIER*1)
#define T_OFF           (MULTIPLIER*12)
#define T_ON_OFF        (T_ON+T_OFF)
static uint32_t count_led = 0;

#endif

void user_led_init(void)
{
    TimeoutSet(&timer_user_led, 500);
}

/**
 * @brief   handler for user led process
 */
void user_led_process(void)
{

#if (BLINK_MODE==LED_BLINK_MODE_BLINK_PERIODE)
    if (IsTimeout(&timer_user_led) ) {
        // toggle led on PA0
        gpio_toggle_pin(USER_LED_PORT, USER_LED_PIN);
        TimeoutSet(&timer_user_led, 500);
    }
#elif (BLINK_MODE==LED_BLINK_MODE_BLINK_TICK)
    if (IsTimeout(&timer_user_led) ) {
        TimeoutSet(&timer_user_led, 100);

        if (count_led < T_ON) {
            gpio_set_pin(USER_LED_PORT, USER_LED_PIN, GPIO_PIN_SET);
        } 
        else if (count_led < T_OFF) {
            gpio_set_pin(USER_LED_PORT, USER_LED_PIN, GPIO_PIN_RESET);
        }
        count_led = (count_led + 1) % T_ON_OFF;
    }

#elif (BLINK_MODE==LED_BLINK_MODE_SYS_CYCLE)
    gpio_toggle_pin(USER_LED_PORT, USER_LED_PIN);
#endif

}
