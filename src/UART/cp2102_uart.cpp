
// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <iostream>
#include <cstdlib>
//#include <pthread.h>

#include "cp2102_uart.h"
#include "../Util/hm_debug.h"
#include "../Util/utility.h"

static _SINT fg_uartPortDev;
static struct termios fg_uartPortOptions;
static void (*CB_uartReceive) (uint8_t a_DataByte) = 0x00;		//callback function on receiving
static uint8_t fg_uartPortInit;

void createCp2102PortThread(void);
void cp2102_uartCreatePortThread(void);
void cp2102_ReceiveByte (uint8_t a_DataByte);

//======================================================================================================
uint32_t cp2102_uart_PortOpen(const _SBYTE* a_pPortName, _ULONG a_Baudrate)
{
	_ULONG l_Baudrate;

	//TRACE_START();

	if (fg_uartPortInit) return (0);

	switch(a_Baudrate)
	{
		case 50     : l_Baudrate = B50;      break;
		case 75     : l_Baudrate = B75;      break;
		case 110    : l_Baudrate = B110;   	 break;
		case 134    : l_Baudrate = B134;   	 break;
		case 150    : l_Baudrate = B150;     break;
		case 200    : l_Baudrate = B200;     break;
		case 300    : l_Baudrate = B300;     break;
		case 600    : l_Baudrate = B600;     break;
		case 1200   : l_Baudrate = B1200;    break;
		case 1800   : l_Baudrate = B1800;    break;
		case 2400   : l_Baudrate = B2400;    break;
		case 4800   : l_Baudrate = B4800;    break;
		case 9600   : l_Baudrate = B9600;    break;
		case 19200  : l_Baudrate = B19200;   break;
		case 38400  : l_Baudrate = B38400;   break;
		case 57600  : l_Baudrate = B57600;   break;
		case 115200 : l_Baudrate = B115200;  break;
		case 230400 : l_Baudrate = B230400;  break;
		case 460800 : l_Baudrate = B460800;  break;
		case 500000 : l_Baudrate = B500000;  break;
		case 576000 : l_Baudrate = B576000;  break;
		case 921600 : l_Baudrate = B921600;  break;
		case 1000000: l_Baudrate = B1000000; break;

		default:
			TRACE_ERROR("Invalid a_Baudrate");
			//TRACE_END();
            return(1);
            break;
	}

	fg_uartPortDev = open(a_pPortName, O_RDWR | O_NOCTTY | O_NDELAY);

	if(fg_uartPortDev == -1)	//If port open failed
	{
		TRACE_ERROR("Port Access Error(%s)", a_pPortName);
		//TRACE_END();
		//while(1);
		return(1);
	}
	else
	{
		if(!isatty(fg_uartPortDev))
		{
			TRACE_ERROR("Failed to open port. This is not a serial port.");
			//TRACE_END();
			return(1);
		}

		if((ioctl(fg_uartPortDev, TIOCEXCL) == -1))
		{
			TRACE_ERROR("Failed to open port. Exclusive access denied.");
			//TRACE_END();
			return(1);
		}
	}

	memset(&fg_uartPortOptions, 0, sizeof(fg_uartPortOptions)); /* Clear the new struct */
	fg_uartPortOptions.c_iflag = 0;								//IGNPAR;
	fg_uartPortOptions.c_oflag = 0;

	fg_uartPortOptions.c_cflag = CS8 | CLOCAL | CREAD;			//l_Baudrate
	cfsetospeed(&fg_uartPortOptions, l_Baudrate);
	cfsetispeed(&fg_uartPortOptions, l_Baudrate);

	fg_uartPortOptions.c_lflag = 0;
	fg_uartPortOptions.c_cc[VMIN] = 0;	//0;      				/* block untill n bytes are received */
	fg_uartPortOptions.c_cc[VTIME] = 0;     					/* block untill a timer expires (n * 100 mSec.) */

//	fg_uartError = tcsetattr(fg_uartPortDev, TCSANOW, &fg_uartPortOptions);
//
//	if(fg_uartError == -1)
//	{
//		close(fg_uartPortDev);
//		perror("Unable to adjust Port Settings ");
//		return(1);
//	}

	if(tcsetattr(fg_uartPortDev, TCSAFLUSH, &fg_uartPortOptions) != 0)
	{
		TRACE_ERROR("Failed to open port. tcsetattr failed.");
		//TRACE_END();
		return(1);
	}

	fg_uartPortInit = 0x01;		//Port initialized
	TRACE_INFO("Port open (%s)", a_pPortName);
	cp2102_uart_RegCBReceive(&cp2102_ReceiveByte);
	cp2102_uartCreatePortThread();
	//TRACE_END();
	return(0);
}

//======================================================================================================
uint32_t cp2102_uart_PollRead (void)
{
	uint32_t l_Count;
	uint8_t l_Byte, l_Return;

	if (fg_uartPortInit != 0x01) return 0;

	l_Return = 0x00;
	l_Count = 0x00;

	do
	{
		l_Return = read(fg_uartPortDev, &l_Byte, 1);	//Read single byte

		if (l_Return)
		{
			l_Count++;
			CB_uartReceive (l_Byte);
		}

	}while(l_Return);

	//if(l_Count)
	//	UTL_Wait(100);

	return (l_Count);	//Total number of byte received
}

//======================================================================================================
uint32_t cp2102_uart_PortSendByte(uint8_t a_DataByte)
{
	_SINT l_Count;

	//TRACE_START();

	l_Count = write(fg_uartPortDev, &a_DataByte, 1);

	//TRACE_END();

	if(l_Count < 0)
		return(1);
	else
		return(0);
}

//======================================================================================================
_UINT cp2102_uart_PortSendString(uint8_t *a_pBuffer, uint32_t a_Size)
{
	uint8_t l_Count;

	//TRACE_START();

	///hwLEDControl(LED_ON, RF_STATUS_LED);
	PrintSysDateTime((char*)"Tx[SFC]");
	fprintf(stderr, "---->"); 	//outward symbol

	for(l_Count = 0x00; l_Count < a_Size; l_Count++)
	{
		fprintf(stderr,"%02X ", *(a_pBuffer + l_Count));
	}

	fprintf(stderr," - Sent \n");
	///hwLEDControl(LED_OFF, RF_STATUS_LED);

	//TRACE_END();
	return(write(fg_uartPortDev, a_pBuffer, a_Size));
}

//======================================================================================================
//Resetting the serial port settings
void cp2102_uart_PortClose (void)
{
	//TRACE_START();

	CB_uartReceive = 0x00;
	fg_uartPortInit = 0x00;

	close (fg_uartPortDev);
	//// tcsetattr (fg_uartPortDev, TCSANOW, fg_uartPortConfigOld);

	//TRACE_END();

	return;
}

//======================================================================================================
uint32_t cp2102_uart_PortGetCTSEnableStatus(void)
{
	uint32_t l_Status;

	l_Status = ioctl(fg_uartPortDev, TIOCMGET, &l_Status);

	if(l_Status & TIOCM_CTS)
		return(1);
	else
		return(0);
}

//================================================================
//Register callback for receiving
void cp2102_uart_RegCBReceive ( void (* a_pFunctionName) (uint8_t a_Data) )
{
	CB_uartReceive = a_pFunctionName;
	return;
}

//================================================================
void * cp2102_runPort(void *threadid)
{
	TRACE_ERROR("Uart threads Running");

	while(fg_uartPortInit)
	{
		cp2102_uart_PollRead();

		if(fg_uartPortInit == 0x00)
		{
			//fprintf(stderr, "*");
			TRACE_ERROR("Uart threads exit %d", fg_uartPortInit);
			//break;
			return 0;
		}
	}

	TRACE_ERROR("Uart threads exit %d", fg_uartPortInit);
	//pthread_exit(threadid);
}

//==============================================================================
void cp2102_uartCreatePortThread(void)
{
	pthread_t thread;
	int l_rc;

	//TRACE_START();
	TRACE_ERROR("Create Uart threads");

	l_rc = pthread_create(&thread, NULL, cp2102_runPort, (void *) 0);

	if(l_rc)
	{
		TRACE_ERROR("Unable to Create Uart threads");
		//TRACE_END();
		exit(-1);
	}

	TRACE_ERROR("Uart threads successfully created");
	//pthread_exit(NULL);
	//pthread_join(thread, NULL);

	//TRACE_END();
}

