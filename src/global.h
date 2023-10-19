/*
 * global.h
 *
 *  Created on: 04-Feb-2023
 *      Author: mundel
 */
//=====================================================================
#ifndef GLOBAL_H_
#define GLOBAL_H_
//=====================================================================
#define UART_TX_BUFFER_SIZE		1000
#define UART_RX_BUFFER_SIZE		2000

extern bool g_FtdiInitComplete;
extern char g_FtdiRetryCount;
extern int  g_FtdiRxTimeout;

extern unsigned char g_TxBuffer[UART_TX_BUFFER_SIZE];
extern unsigned char g_RxBuffer[UART_RX_BUFFER_SIZE];

//=====================================================================
#endif /* GLOBAL_H_ */
//=====================================================================
