//TYPEDEFINE.H

//==========================================================
#ifndef _TYPEDEFINE_H
#define _TYPEDEFINE_H
//==========================================================
#include <stdio.h>
#include <stdint.h>

//#include <iostream>
//#include <list>
//#include <vector>

//using namespace std;
//typedef list<string> 		_MAPLIST;

typedef char				_SBYTE;
typedef unsigned char 		_UBYTE;
typedef unsigned int 		_UINT;
typedef unsigned long 		_ULONG;
typedef unsigned long 		_UDWORD;
typedef unsigned long long 	_ULONGLONG;
typedef long long			_SLONGLONG;
typedef signed long 		_SLONG;
typedef signed int 			_SINT;
typedef float 				_FLOAT;

typedef char				sint8_t;
typedef unsigned char 		uint8_t;
typedef signed long 		sint32_t;
typedef signed int 			sint16_t;

typedef union
{
	uint8_t  Byte[2];
	uint16_t Value;
}un_2Byte;

typedef union
{
	uint8_t  Byte[4];
	uint32_t Value;
}un_4Byte;

//==========================================================
#endif 	//_TYPEDEFINE_H
//==========================================================

