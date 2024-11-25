#ifndef TIMEOUT_H
#define TIMEOUT_H

#include <stdint.h>
#include <stdbool.h>

typedef struct	_TIMER
{
	uint32_t	TimeOutVal;
	uint32_t	TickValCache;
	bool	IsTimeOut;
} TIMER;

/* prototype function */
void TimeoutSet(TIMER *timer, uint32_t timeout);
bool IsTimeout(TIMER *timer);
/** end of prototype function */


#endif /*TIMEOUT_H*/
