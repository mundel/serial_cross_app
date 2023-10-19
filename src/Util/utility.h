/*
 * utility.h
 *
 *  Created on: 11-Aug-2022
 *      Author: mundel
 */
//================================================================================
#ifndef UTIL_UTILITY_H_
#define UTIL_UTILITY_H_
//================================================================================
#include "typedef.h"

typedef uint32_t TickType_t;

void PrintSysDateTime(char * a_pInfoData);
TickType_t xTaskGetTickCount( void );

time_t UTL_GetSysUTCTime(void);


//================================================================================
#endif /* UTIL_UTILITY_H_ */
//================================================================================
