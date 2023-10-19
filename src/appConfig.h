/*
 * appConfig.h
// Author      : NR Mundel
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
 */

//================================================================================
#ifndef APPCONFIG_H_
#define APPCONFIG_H_
//================================================================================

//#define  LINUX_PC
#define  EMBEDDED_LINUX_DEVICE

#ifdef EMBEDDED_LINUX_DEVICE
	#define CP2102_RS232_PORT_NAME 		    "/dev/ttyUSB0"
	#define FTDI_RS232_PORT_NAME			"/dev/ttyUSB2"

#else
	#define CP2102_RS232_PORT_NAME 		    "/dev/ttyUSB0"
	#define FTDI_RS232_PORT_NAME			"/dev/ttyUSB2"
#endif


#define FTDI_RS232_BAUDRATE		 			9600	//115200	//38400
#define CP2102_RS232_BAUDRATE		 		FTDI_RS232_BAUDRATE	//9600

//================================================================================
#endif /* APPCONFIG_H_ */
//================================================================================

