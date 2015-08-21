/******************************************************************************************  
//  epb.h
//  MicroMessenger
//
//  Created by harlliu@tencent.com on 14-02-15.
//  Copyright 2014 Tencent. All rights reserved.
//

//  Version : 1.0.2
*******************************************************************************************/

#ifndef __EPB_H__
#define __EPB_H__

#include <csrtypes.h>


typedef struct
{
    uint8 *data;
    uint16 len;
} Bytes;

typedef struct
{
    const uint8 *data;
    uint16 len;
} CBytes;

typedef struct
{
    char *str;
    uint16 len;
} String;

typedef struct
{
    const char *str;
    uint16 len;
} CString;

typedef struct 
{
    const uint8 *unpack_buf;
    uint8 *pack_buf;
    uint16 buf_len;
    uint16 buf_offset;
} Epb;

/*
 * embeded protobuf unpack functions
 */

void epb_unpack_init(Epb *e, const uint8 *buf, uint16 len);
bool epb_has_tag(Epb *e, uint16 tag);

int32 epb_get_int32(Epb *e, uint16 tag);
uint32 epb_get_uint32(Epb *e, uint16 tag);
int32 epb_get_sint32(Epb *e, uint16 tag);
bool epb_get_bool(Epb *e, uint16 tag);
uint16 epb_get_enum(Epb *e, uint16 tag);

const char *epb_get_string(Epb *e, uint16 tag, uint16 *len);
const uint8 *epb_get_bytes(Epb *e, uint16 tag, uint16 *len);
const uint8 *epb_get_message(Epb *e, uint16 tag, uint16 *len);

uint32 epb_get_fixed32(Epb *e, uint16 tag);
int32 epb_get_sfixed32(Epb *e, uint16 tag);

/*
 * embeded protobuf pack functions
 */

void epb_pack_init(Epb *e, uint8 *buf, uint16 len);
uint16 epb_get_packed_size(Epb *e);

uint16 epb_set_int32(Epb *e, uint16 tag, int32 value);
uint16 epb_set_uint32(Epb *e, uint16 tag, uint32 value);
uint16 epb_set_sint32(Epb *e, uint16 tag, int32 value);
uint16 epb_set_bool(Epb *e, uint16 tag, bool value);
uint16 epb_set_enum(Epb *e, uint16 tag, uint16 value);

uint16 epb_set_string(Epb *e, uint16 tag, const char *data, uint16 len);
uint16 epb_set_bytes(Epb *e, uint16 tag, const uint8 *data, uint16 len);
uint16 epb_set_message(Epb *e, uint16 tag, const uint8 *data, uint16 len);

uint16 epb_set_fixed32(Epb *e, uint16 tag, uint32 value);
uint16 epb_set_sfixed32(Epb *e, uint16 tag, int32 value);
uint16 epb_set_float(Epb *e, uint16 tag, float value);

uint16 epb_varint32_pack_size(uint16 tag, uint32 value, bool is_signed);
uint16 epb_fixed32_pack_size(uint16 tag);
uint16 epb_length_delimited_pack_size(uint16 tag, uint16 len);

#endif
