
//=================================================================
#ifndef _GQ_PLC_UART_O2_H_
#define _GQ_PLC_UART_O2_H_
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

_UINT FTDI_uart_PortOpen(const _SBYTE* a_pPortName, _ULONG a_Baudrate);
_UINT FTDI_uart_PollRead (void);
_UINT FTDI_uart_PortSendByte(_UBYTE a_DataByte);
_UINT FTDI_uart_PortSendString(_UBYTE *a_pBuffer, _UINT a_Size);
void  FTDI_uart_PortClose (void);
_UINT FTDI_uart_PortGetCTSEnableStatus(void);
void  FTDI_uart_RegCBReceive ( void (* a_pFunctionName) (_UBYTE a_Data) );
void  FTDI_uartCreatePortThread(void);
//=================================================================
#endif	//_GQ_PLC_UART_O2_H_
//=================================================================


