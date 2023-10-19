/*
 * utility.c
 *
 *  Created on: 11-Aug-2022
 *      Author: mundel
 */
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

#include "utility.h"

bool first_tick_ready;
//=============================================================================
void PrintSysDateTime(char * a_pInfoData)
{
	char buffer[26];
	int millisec;
	struct tm* tm_info;
	struct timeval tv;

	gettimeofday(&tv, NULL);

	millisec = lrint(tv.tv_usec/1000.0); // Round to nearest millisec

	if (millisec >= 1000) // Allow for rounding up to nearest second
	{
		millisec -=1000;
		tv.tv_sec++;
	}

	tm_info = localtime(&tv.tv_sec);

	strftime(buffer, 26, "%Y:%m:%d %H:%M:%S", tm_info);
	fprintf(stderr, "\n[%s %s.%03d] ",a_pInfoData, buffer, millisec);
}

double xTaskGet_First_TickCount( void )
{
	double first_millisec;
	struct timeval tv;

	first_tick_ready = 1;
	gettimeofday(&tv, NULL);
	first_millisec = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;

	return(first_millisec);
}

TickType_t xTaskGetTickCount( void )
{
	uint32_t millisec;
	static double first_millisec = 0;
	struct timeval tv;

	if(!first_tick_ready)
	{
		first_millisec = xTaskGet_First_TickCount();
	}

	gettimeofday(&tv, NULL);

	//millisec = lrint(tv.tv_usec/1000.0); // Round to nearest millisec
	//millisec = lrint(tv.tv_usec); // Round to nearest millisec
	double time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
	millisec = time_in_mill - first_millisec;

	return(millisec);
}

TickType_t diffTick(TickType_t startTick, TickType_t endTick)
{
    TickType_t diff_Tick;

    if (startTick <= endTick)
    {
    	diff_Tick = endTick - startTick;
    }
    else  // Overflow
    {
    	//printf("\n Overflow observed ");
    }
    return diff_Tick;
}

time_t UTL_GetSysUTCTime(void)
{
	//_ULONG l_Seconds = 0;
	time_t l_Seconds;

	l_Seconds = time(NULL); //it return Seconds since January 1, 1970
	//but we required Seconds since January 1, 2000 so we subtract 946684800
	//l_Seconds -= 946684800;
	//l_Seconds -= 19800;	//International GMT
	//fprintf(stderr, "\nUTCTime = %lu \n", l_Seconds);
	return(l_Seconds);
}



