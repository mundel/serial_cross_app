/*
 * global.cpp
 *
 *  Created on: 04-Feb-2023
 *      Author: mundel
 */

#include "global.h"

bool g_FtdiInitComplete;
char g_FtdiRetryCount;
int  g_FtdiRxTimeout;

unsigned char g_TxBuffer[UART_TX_BUFFER_SIZE];
unsigned char g_RxBuffer[UART_RX_BUFFER_SIZE];



