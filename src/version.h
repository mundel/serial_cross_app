//============================================================================
// Name        : version.h
// Author      : NR Mundel
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//=================================================================================================
#ifndef VERSION_H_
#define VERSION_H_
//=================================================================================================
//application version
#define APP_VER_MAJOR				1   /* Major version 1 bypte value 1-255*/
#define APP_VER_MINOR				0   /* Minor version 1 byte value 1-255 */
#define APP_VER_REVISION			2   /* revision 2 byte value 1-65535   */

#define STR_EXPAND(s) #s
#define STR(tok) STR_EXPAND(tok)

#define MAJOR_OFFSET            (24)
#define MINOR_OFFSET            (16)
#define HOTFIX_OFFSET           (0)

#define GET_MINOR(x)            ((x >> MINOR_OFFSET) & 0xFF)
#define GET_MAJOR(x)            ((x >> MAJOR_OFFSET) & 0xFF)
#define GET_HOTFIX(x)           (x & 0xFFFF)

#define SW_REVISION ((APP_VER_MAJOR << MAJOR_OFFSET) | (APP_VER_MINOR << MINOR_OFFSET) | (APP_VER_REVISION << HOTFIX_OFFSET))

#define SW_REVISION_ASCII "UART_cross_communication_app=" \
    STR(APP_VER_MAJOR) "." \
    STR(APP_VER_MINOR) "." \
    STR(APP_VER_REVISION)

/*
int main()
{
    printf("version in hex=%X \n", SW_REVISION);
    printf("version in ASCII=%s \n", SW_REVISION_ASCII);
    return 0;
}
*/

//=================================================================================================
#endif /* VERSION_H_ */
//=================================================================================================
