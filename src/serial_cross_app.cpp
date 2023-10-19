//============================================================================
// Name        : serial_cross_app.cpp
// Author      : Mundel
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>
#include <syslog.h>

#include "version.h"
#include "appConfig.h"
#include "UART/FTDI_uart.h"
#include "UART/cp2102_uart.h"
#include "Util/hm_debug.h"

using namespace std;

int fg_20msTimeSchedule;


int main(int argc, char **argv)
{
	struct utsname name;

	TRACE_INFO("!!!Welcome to CROSS UART Solution, mundel!!!"); /* prints !!!Hello World!!! */

	TRACE_INFO(" Application Version %s ", SW_REVISION_ASCII);

	//Check firmware check
	if(argv[1] == NULL)
	{
		TRACE_WARNING("No argument pass ");
	}
	else if(strcmp(argv[1],"version_info") == 0)
	{
		TRACE_ERROR(" App fine so copy it ");
		return(99);
	}
	else
	{
		TRACE_INFO("Run app");
	}

	//Check System arch
	if(uname(&name) == -1)
	{
		TRACE_WARNING("Unable to read uname");
	}

	TRACE_INFO("%s\t", name.domainname);
	TRACE_INFO("%s\t", name.machine);
	///TRACE_INFO("%s\t", name.nodename);
	TRACE_INFO("%s\t", name.release);
	TRACE_INFO("%s\t", name.sysname);
	TRACE_INFO("%s ", name.version);

	if(((strcmp(name.machine, "i686") == 0) || (strcmp(name.machine, "x86_64") == 0)))			//i686 //armv7l
	{
		TRACE_INFO("Linux PC detect");
	}
	else
	{
		TRACE_INFO("Embedded Linux Device detect");
	}


	uint32_t res=0;

	res = cp2102_uart_PortOpen(CP2102_RS232_PORT_NAME, CP2102_RS232_BAUDRATE);
	if(0 != res)
	{
		TRACE_ERROR("Port Access Error(%s)", CP2102_RS232_PORT_NAME);
	}
	else
	{
		TRACE_INFO("Port successfully opened (%s)", CP2102_RS232_PORT_NAME);
	}

	res = FTDI_uart_PortOpen(FTDI_RS232_PORT_NAME, FTDI_RS232_BAUDRATE);	//port open
	if(0 != res)
	{
		TRACE_ERROR("Port Access Error(%s)", FTDI_RS232_PORT_NAME);
	}
	else
	{
		TRACE_INFO("Port successfully opened (%s)", FTDI_RS232_PORT_NAME);
	}


	while(1)
	{
		//schProcess();
		//data exchanging in uart threads
		sleep(10);
	}

	return EXIT_SUCCESS;
}

//=============================================================================
//=============================================================================
//This function will be called by CallBack Function (Port Module), when a
//Byte received by external port
void FTDIReceiveByte (_UBYTE a_DataByte)
{
	cp2102_uart_PortSendByte(a_DataByte);
	return;
}

//=============================================================================
//This function will be called by CallBack Function (Port Module), when a
//Byte received by RF 6LoWPAN port
void cp2102_ReceiveByte (uint8_t a_DataByte)
{
	FTDI_uart_PortSendByte(a_DataByte);
	return;
}

