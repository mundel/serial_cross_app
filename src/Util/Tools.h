/*
 * Tool.h
 *
 *  Created on: 10-Sep-2022
 *      Author: mundel
 */
//===============================================================================
#ifndef UTIL_TOOLS_H_
#define UTIL_TOOLS_H_
//===============================================================================

#include <stdint.h>
#include <time.h>

#include "utility.h"

#define MAX(val1, val2) (val1 > val2 ? val1 : val2)
#define MIN(val1, val2) (val1 < val2 ? val1 : val2)

#define SWAP16(val) ((((uint16_t) (val)) << 8) | \
                     (((uint16_t) (val)) >> 8)   \
                    )
#define SWAP32(val) (((((uint32_t) (val)) & 0x000000ff) << 24) | \
                     ((((uint32_t) (val)) & 0x0000ff00) <<  8) | \
                     ((((uint32_t) (val)) & 0x00ff0000) >>  8) | \
                     ((((uint32_t) (val)) & 0xff000000) >> 24)   \
                    )

TickType_t diffTick(TickType_t startTick, TickType_t endTick);

//===============================================================================
#endif /* UTIL_TOOLS_H_ */
//===============================================================================


