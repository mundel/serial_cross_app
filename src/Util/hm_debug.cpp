
/** @file
 *
 * Debug code
 *
 * This file contains the actual printing and formatting of debug lines.
 * Used by the debug macros found in gw_debug.h
 */

#include "hm_debug.h"

#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

#include "../appConfig.h"

/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *               Function Declarations
 ******************************************************/

/******************************************************
 *               Variable Definitions
 ******************************************************/
static uint16_t debug_count = 0;

/******************************************************
 *               Function Definitions
 ******************************************************/

#if (LOGFUNC == 1)
void __LogPrint(const char logLevel, const char *functionName, const char *fileName, int lineNumber, const char *message, ...)
#else
void __LogPrint(const char logLevel, const char *fileName, int lineNumber, const char *message, ...)
#endif
{
	char headerString[MAX_DEBUG_HEADER_LENGTH];
	char debugInfoString[MAX_DEBUG_STRING_LENGTH];
	//wiced_tm_t tmUTC = {0};
	//wiced_utc_time_ms_t currentTimeUTC = {0};
	va_list ap;
	int millisec;
	struct tm* tmUTC;
	struct timeval tv;

	gettimeofday(&tv, NULL);

	millisec = lrint(tv.tv_usec/1000.0); // Round to nearest millisec

	if (millisec >= 1000) // Allow for rounding up to nearest second
	{
		millisec -=1000;
		tv.tv_sec++;
	}

	tmUTC = localtime(&tv.tv_sec);

  /* Get the current time since boot in milliseconds. */
  //(void) wiced_time_get_utc_time_ms(&currentTimeUTC);
  //(void) wiced_time_convert_utc_ms_to_tm(currentTimeUTC, &tmUTC);
  debug_count++; /* debug_count will automatically wrap to 0 after 65536 */
  /* Create a string for each debug print containing which function, file and line in the file. */
///  if (_tx_thread_current_ptr != NULL)
  {
#if (LOGFUNC == 1)
    snprintf(headerString, (MAX_DEBUG_HEADER_LENGTH - 1), "[%5u][%02d:%02d:%02d.%05u %02d/%02d/%04d] %-18s : %-30s  @%-10s:%4i: [%c] ",
          debug_count, tmUTC->tm_hour, tmUTC->tm_min, tmUTC->tm_sec, millisec, tmUTC->tm_mday, tmUTC->tm_mon, tmUTC->tm_year, _tx_thread_current_ptr->tx_thread_name, functionName, fileName, lineNumber, logLevel);
#else
///    snprintf(headerString, (MAX_DEBUG_HEADER_LENGTH - 1), "[%5u][%02d:%02d:%02d.%05u %02d/%02d/%04d] %-18s : %-10s:%4i: [%c] ",
///          debug_count, tmUTC->tm_hour, tmUTC->tm_min, tmUTC->tm_sec, millisec, tmUTC->tm_mday,tmUTC->tm_mon,tmUTC->tm_year, _tx_thread_current_ptr->tx_thread_name, fileName, lineNumber, logLevel);
#endif
  }
///  else
  {
#if (LOGFUNC == 1)
    snprintf(headerString, (MAX_DEBUG_HEADER_LENGTH - 1), "[%5u][%02d:%02d:%02d.%05u %02d][No THREAD] %24s@%-9s:%4i: [%c] ",
              debug_count, tmUTC->tm_hour, tmUTC->tm_min, tmUTC->tm_sec, millisec, tmUTC->tm_mday, functionName, fileName, lineNumber, logLevel);
#else
    snprintf(headerString, (MAX_DEBUG_HEADER_LENGTH - 1), "[%5u][%02d:%02d:%02d.%05u %02d][No THREAD] %-9s:%4i: [%c] ",
              debug_count, tmUTC->tm_hour, tmUTC->tm_min, tmUTC->tm_sec, millisec, tmUTC->tm_mday, fileName, lineNumber, logLevel);
#endif
  }

  /* Create a  string of the debug message. */
  va_start(ap, message);
  vsnprintf(debugInfoString, (size_t)(MAX_DEBUG_STRING_LENGTH - 1), message, ap);
  va_end(ap);

  //printf("%s",headerString);
 // printf("%s\n",debugInfoString);

  //Send log over uart from here
#if 0
//#ifdef ENABLE_UART_COMPLETE_LOG
  int header_len = strlen(headerString);
  int msg_len = strlen(debugInfoString);
  int count = 0;

  /*
  for(count=0; count < header_len; count++)
  {
	  log_uart_PortSendByte(headerString[count]);
  }
  */

  for(count=0; count < msg_len; count++)
  {
	  log_uart_PortSendByte(debugInfoString[count]);
  }
  log_uart_PortSendByte('\n');
#else
  printf("%s",headerString);
  printf("%s\n",debugInfoString);
#endif

}


