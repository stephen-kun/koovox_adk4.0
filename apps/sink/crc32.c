/*  crc32.c
//  WeChat Embedded
//
//  Created by harlliu on 14-03-03.
//  Copyright 2014 Tencent. All rights reserved.
*/

#include "crc32.h"
#include "sink_private.h"

#define DO1(buf) crc = crc_table(((uint16)crc ^ (*buf++)) & 0xff) ^ (crc >> 8);
#define DO2(buf)  DO1(buf); DO1(buf);
#define DO4(buf)  DO2(buf); DO2(buf);
#define DO8(buf)  DO4(buf); DO4(buf);


static uint32 crc_table(uint32 index)
{
	uint32 c = index;
	uint32 poly = 0xedb88320L;
	uint16 k;

	for (k = 0; k < 8; k++)
		c = c & 1 ? poly ^ (c >> 1) : c >> 1;

	return c;
}

uint32 crc32(uint32 crc, const uint8 *buf, uint16 len)
{
    if (buf == NULL) return 0L;

    crc = crc ^ 0xffffffffL;
    while (len >= 8)
    {
      DO8(buf);
      len -= 8;
    }
    if (len) do {
      DO1(buf);
    } while (--len);
    return crc ^ 0xffffffffL;
}

