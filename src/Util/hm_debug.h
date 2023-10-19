
//#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#ifndef _GW_DEBUG_H_
#define _GW_DEBUG_H_

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


  /******************************************************
 *                    Constants
 ******************************************************/

/* Default loglevel */
#ifndef LOGLEVEL
//#define LOGLEVEL LOGLEVEL_VERBOSE		//LOGLEVEL_INFO	//LOGLEVEL_DEBUG
#define LOGLEVEL LOGLEVEL_DEBUG
#endif

/* Log prints for function names */
#ifndef LOGFUNC
#define LOGFUNC 0
#endif

/* Restricting Header length to MAX_DEBUG_HEADER_LENGTH for timestamp, thread, file and function names */
/* Restricting Debug string length to MAX_DEBUG_STRING_LENGTH bytes,
    bigger strings will be stripped off after printing first MAX_DEBUG_STRING_LENGTH */
#define MAX_DEBUG_HEADER_LENGTH (200)
#define MAX_DEBUG_STRING_LENGTH (800)

#define LOGLEVEL_DISABLED (0)
#define LOGLEVEL_ERROR    (1)
#define LOGLEVEL_ASSERT   (1)
#define LOGLEVEL_WARNING  (2)
#define LOGLEVEL_INFO     (3)
#define LOGLEVEL_FUNCTION (4)
#define LOGLEVEL_DEBUG    (4)
#define LOGLEVEL_VERBOSE  (5)
#define LOGLEVEL_MEMDEBUG (6)

/******************************************************
 *                      Macros
 ******************************************************/
#ifdef CUSTOM_LOG
#define LOG_PRINT_V(x,...) do { __LogPrint('V', " ", 0 , x, ##__VA_ARGS__); } while (0==1)
#endif

#if ( (LOGLEVEL >= LOGLEVEL_ERROR) || (LOGLEVEL_DEFINED >0 ))

#if (LOGFUNC == 1)
#define LOG_PRINT(x,...) do { __LogPrint('E', __func__, FILE_GW, __LINE__, x, ##__VA_ARGS__); } while (0==1)
#else
#define LOG_PRINT(x,...) do { __LogPrint('E', FILE_GW, __LINE__, x, ##__VA_ARGS__); } while (0==1)
#define LOG_PRINT_E(x,...) do { __LogPrint('E', FILE_GW, __LINE__, x, ##__VA_ARGS__); } while (0==1)
#define LOG_PRINT_V(x,...) do { __LogPrint('V', FILE_GW,__LINE__, x, ##__VA_ARGS__); } while (0==1)
#define LOG_PRINT_W(x,...) do { __LogPrint('W', FILE_GW, __LINE__, x, ##__VA_ARGS__); } while (0==1)
#define LOG_PRINT_I(x,...) do { __LogPrint('I', FILE_GW, __LINE__, x, ##__VA_ARGS__); } while (0==1)
#define LOG_PRINT_D(x,...) do { __LogPrint('D', FILE_GW, __LINE__, x, ##__VA_ARGS__); } while (0==1)
#define LOG_PRINT_E_NAMED(x,...) do { __LogPrint('E', srcFileName, __LINE__, x, ##__VA_ARGS__); } while (0==1)
#define LOG_PRINT_V_NAMED(x,...) do { __LogPrint('V', srcFileName,__LINE__, x, ##__VA_ARGS__); } while (0==1)
#define LOG_PRINT_W_NAMED(x,...) do { __LogPrint('W', srcFileName, __LINE__, x, ##__VA_ARGS__); } while (0==1)
#define LOG_PRINT_I_NAMED(x,...) do { __LogPrint('I', srcFileName, __LINE__, x, ##__VA_ARGS__); } while (0==1)
#define LOG_PRINT_D_NAMED(x,...) do { __LogPrint('D', srcFileName, __LINE__, x, ##__VA_ARGS__); } while (0==1)
#endif
#ifdef _WIN32
#define FILE_GW (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else // ! _WIN32
#define FILE_GW (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif // _WIN32
#define ERR_LINE __LINE__
#define ERR_FUNC __func__
#define ERR_FILE FILE_GW
#else // LOGLEVEL == 0
#define TrFileName(str)
#define LOG_PRINT(x,...)
#define ERR_LINE 0
#define ERR_FUNC ""
#define ERR_FILE ""
#endif // LOGLEVEL


/** Log an error-message (with formatting) to the debug console.
 *  All results that will end up in the system crashing or locking are errors. */
#if (LOGLEVEL >= LOGLEVEL_ERROR)
#define TRACE_ERROR(x,...)   LOG_PRINT_E(x, ##__VA_ARGS__)
#else
#define TRACE_ERROR(x,...)
#endif


  /** Log a warning-message (with formatting) to the debug console.
   *  All results that will end up potential crashes or unknown states are warnings. */
#if (LOGLEVEL >= LOGLEVEL_WARNING)
#define TRACE_WARNING(x,...) LOG_PRINT_W(x, ##__VA_ARGS__)
#else
#define TRACE_WARNING(x,...)
#endif

  /** Log an informational message (with formatting) to the debug console.
   *  All results that will help to follow the flow through the code are infos.*/
#if (LOGLEVEL >= LOGLEVEL_INFO)
#define TRACE_INFO(x,...)    LOG_PRINT_I(x, ##__VA_ARGS__)
#else
#define TRACE_INFO(x,...)
#endif

  /** Log a debug message (with formatting) to the debug console.
   *  All results that will help to debug the found issues are debugs. */
#if (LOGLEVEL >= LOGLEVEL_DEBUG)
#define TRACE_DEBUG(x,...)   LOG_PRINT_D(x, ##__VA_ARGS__)
#else
#define TRACE_DEBUG(x,...)
#endif

  /** Log a verbose message (with formatting) to the debug console.
   *  Extensive prints of information that may be of value to debug are verbose. */
#if (LOGLEVEL >= LOGLEVEL_VERBOSE)
#define TRACE_VERBOSE(x,...) LOG_PRINT_V(x, ##__VA_ARGS__)
#else
#define TRACE_VERBOSE(x,...)
#endif

/** Evaluates a condition, and if not-true, terminate program execution with a message (includes formatting)*/
#if (LOGLEVEL >= LOGLEVEL_ERROR)
#define TRACE_ASSERT(c,x,...) do { if( !(c) ) { LOG_PRINT_E("[A] " x, ##__VA_ARGS__); assert(!x); } } while (0)
#else
#define TRACE_ASSERT(c,x,...)
#endif

/** Log a message to the debug console when entering a function and print the parameters.
 *  Log a message to the debug console when exiting a function and print the return values.
 *  The parameters and return values are only printed when verbose logging is enabled.
 */
#if (LOGLEVEL >= LOGLEVEL_VERBOSE)
#define TRACE_START(x,...)        LOG_PRINT_V(">> " x, ##__VA_ARGS__);
#define TRACE_END(x,...)          LOG_PRINT_V("<< " x, ##__VA_ARGS__);
#else
#define TRACE_START(x,...)
#define TRACE_END(x,...)
#endif


#define SRC_FILENAME(x) static const char* srcFileName = #x;

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/
#if (LOGFUNC == 1)
void __LogPrint(const char loglevel, const char *functionName, const char *fileName, int lineNumber, const char *message, ...);
#else
void __LogPrint(const char logLevel, const char *fileName, int lineNumber, const char *message, ...);
#endif
/******************************************************
 *                    Structures
 ******************************************************/
#endif //_GW_DEBUG_H_
#ifdef __cplusplus
} /*extern "C" */
#endif
