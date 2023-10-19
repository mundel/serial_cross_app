
//=================================================================
#ifndef _CP2102_RS232_UART_H_
#define _CP2102_RS232_UART_H_
//=================================================================

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>

#include "../Util/typedef.h"

uint32_t cp2102_uart_PortOpen(const _SBYTE* a_pPortName, _ULONG a_Baudrate);
uint32_t cp2102_uart_PollRead (void);
uint32_t cp2102_uart_PortSendByte(uint8_t a_DataByte);
uint32_t cp2102_uart_PortSendString(uint8_t *a_pBuffer, uint32_t a_Size);
void  cp2102_uart_PortClose (void);
uint32_t cp2102_uart_PortGetCTSEnableStatus(void);
void  cp2102_uart_RegCBReceive ( void (* a_pFunctionName) (uint8_t a_Data) );

//=================================================================
#endif	//_CP2102_RS232_UART_H_
//=================================================================


