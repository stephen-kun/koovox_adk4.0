/* crc32.h
//  WeChat Embedded
//
//  Created by harlliu on 14-03-03.
//  Copyright 2014 Tencent. All rights reserved.
*/

#ifndef __CRC32_H__
#define __CRC32_H__

#include <csrtypes.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32 crc32(uint32 crc, const uint8 *buf, uint16 len);

#ifdef __cplusplus
}
#endif


#endif
