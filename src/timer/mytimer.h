/*mytimer.h*/
//=====================================================
#ifndef MY_TIME_H
#define MY_TIME_H
//=====================================================
#include <stdlib.h>

#include "../Util/typedef.h"

typedef enum
{
TIMER_SINGLE_SHOT = 0, /*Periodic Timer*/
TIMER_PERIODIC         /*Single Shot Timer*/
} t_timer;

//Structure Templates
struct st_Timer
{
	_UINT Interval;
	_UINT Count;
	//_UBYTE Reserved;
	_UBYTE Reason;
	_UBYTE Enable;
	_UBYTE Timeout;
};

typedef void (*time_handler)(size_t timer_id, void * user_data);

int create_timer(pthread_t thread_id);
size_t start_timer(unsigned int interval, time_handler handler, t_timer type, void * user_data);
void stop_timer(size_t timer_id);

int timer_main(void);
//=====================================================
#endif //MY_TIME_H
//=====================================================
