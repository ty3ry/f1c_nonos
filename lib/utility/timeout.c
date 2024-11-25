/***
 * @file    timeout.h
 * 
 * @brief   utility to set/get timeout based on tick
 * @author  c_e (cosmas.es08@gmail.com)
 * 
 * @date    2024/11/24
 */
#include "sys.h"
#include "timeout.h"

#define	GET_TICK()	ctr_ms

static uint32_t timeout_get_tick(void)
{
    return (GET_TICK());
}

/**
 * @brief timeout function
 * @param   timer   timer instance identifier
 * @param   timeout timeout in ms
 * 
 * @return  none
*/
void TimeoutSet(TIMER *timer, uint32_t timeout)
{   
    timer->TimeOutVal = timeout;
    timer->TickValCache = GET_TICK();    //timeout_get_tick();
}


/**
 * @brief   Is timer timeout
 * @param   timer timer instance
 * @return  1: timeout
 *          0: no timeout (running)
*/
bool IsTimeout(TIMER *timer)
{
    if (GET_TICK() >= (timer->TimeOutVal + timer->TickValCache) )
    {
        timer->IsTimeOut = 1;
        return 1;
    }
    
    timer->IsTimeOut = 0;
    return 0;
}