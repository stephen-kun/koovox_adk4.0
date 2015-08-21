/******************************************************************************************  
//  epb.c
//  WeChat Embedded Proto Buffer
//
//  Created by harlliu@tencent.com on 14-02-15.
//  Copyright 2014 Tencent. All rights reserved.
//

//  Version : 1.0.2

****************************************************************************************/

#include <string.h>
#include "epb.h"


#define __LITTLE_ENDIAN__		1 

typedef enum {
    WIRETYPE_VARINT = 0,
    WIRETYPE_FIXED64 = 1,
    WIRETYPE_LENGTH_DELIMITED = 2,
    WIRETYPE_FIXED32 = 5
} WireType;

#define CONTINUOUS_MASK 		0x80
#define WIRETYPE_MASK			0x07

static uint16 epb_get_varint32_bits(const uint8 *data, uint16 len, uint32 *value);

static uint16 epb_get_wire_type(uint16 tag)
{
    uint16 wire_type = tag & WIRETYPE_MASK;
    if ((tag>>8) != 0)
        wire_type = (tag>>8) & WIRETYPE_MASK;

    return wire_type;
}

static uint16 epb_get_value_length(const uint8 *data, uint16 len, uint32 wire_type)
{
    uint16 offset = 0;
    switch(wire_type) {
    case WIRETYPE_VARINT:
        while ((data[offset++]&CONTINUOUS_MASK)!=0 && offset<len);
        break;
    case WIRETYPE_FIXED64:
        offset += 8;
        break;
    case WIRETYPE_LENGTH_DELIMITED:
    {
        int32 l = 0;
        offset += epb_get_varint32_bits(data+offset, len-offset, (uint32 *)&l);
        offset += l;
    }
        break;
    case WIRETYPE_FIXED32:
        offset += 4;
        break;
    default:
        return -1;
    }
    return offset;
}

static uint16 epb_get_tag_value_offset(const uint8 *data, uint16 len, uint16 tag)
{
    uint16 offset = 0;
    uint32 p_tag;
    while (offset < len) {
        p_tag = data[offset++];
        while ((data[offset-1]&CONTINUOUS_MASK)!=0 && offset<len) {
            p_tag = (p_tag<<8)|(data[offset++]&0x7f); 
        }
        if (p_tag == tag)
            return offset;

		{
			uint32 wire_type = epb_get_wire_type(p_tag);
			uint16 ret = epb_get_value_length(data+offset, len-offset, wire_type);
			if (ret < 0) {
				offset++;
				continue;
			}
			
			offset += ret;
		}

    }
    return -1;
}

static uint16 epb_get_varint32_bits(const uint8 *data, uint16 len, uint32 *value)
{
    uint16 offset = 0;
    uint32 p_value = data[offset++] & 0x7F;
    while ((data[offset-1]&CONTINUOUS_MASK) != 0) {
        if (offset >= len)
            return -1;

        if (offset >= 5)
            break;

        p_value |= ((uint32)data[offset]&0x7F) << (offset*7);
        ++offset;
    }
    *value = p_value;
    return offset;
}

static uint32 epb_get_fixed32_bits(const uint8 *data, uint16 len)
{
    if(len < 4)
        return 0;

	{
			uint32 value = 0;
#ifdef __LITTLE_ENDIAN__
			memcpy(&value, data, sizeof(uint32));
#else 
			value = (data[3]<<24)|(data[2]<<16)|(data[1]<<8)|data[0];
#endif
			return value;
	}

}

void epb_unpack_init(Epb *e, const uint8 *buf, uint16 len)
{
    e->unpack_buf = buf;
    e->buf_len = len;
}

bool epb_has_tag(Epb *e, uint16 tag)
{
    uint16 offset = epb_get_tag_value_offset(e->unpack_buf, e->buf_len, tag);
    if (offset < 0)
        return FALSE;
    else
        return TRUE;
}

uint32 epb_get_uint32(Epb *e, uint16 tag)
{
    uint16 offset = epb_get_tag_value_offset(e->unpack_buf, e->buf_len, tag);
    if (offset < 0)
        return 0;

	{
		uint32 value = 0;
		epb_get_varint32_bits(e->unpack_buf+offset, e->buf_len-offset, &value);
		return value;
	}

}

int32 epb_get_int32(Epb *e, uint16 tag)
{
    return epb_get_uint32(e, tag);
}

int32 epb_get_sint32(Epb *e, uint16 tag)
{
    uint32 value = epb_get_uint32(e, tag);
    if (value&1)
        return -(value>>1) - 1;
    else
        return value>>1;
}

bool epb_get_bool(Epb *e, uint16 tag)
{
    return epb_get_uint32(e, tag);
}

uint16 epb_get_enum(Epb *e, uint16 tag)
{
    return epb_get_uint32(e, tag);
}

const uint8 *epb_get_bytes(Epb *e, uint16 tag, uint16 *len)
{
    uint16 offset = epb_get_tag_value_offset(e->unpack_buf, e->buf_len, tag);
    if (offset < 0)
        return NULL;

	{
		uint32 l;
		offset += epb_get_varint32_bits(e->unpack_buf+offset, e->buf_len-offset, &l);
		*len = (uint16)l;
		
		return e->unpack_buf+offset;
	}

}

const char *epb_get_string(Epb *e, uint16 tag, uint16 *len)
{
    return (char *)epb_get_bytes(e, tag, len);
}

const uint8 *epb_get_message(Epb *e, uint16 tag, uint16 *len)
{
    return (uint8 *)epb_get_bytes(e, tag, len);
}

uint32 epb_get_fixed32(Epb *e, uint16 tag)
{
    uint16 offset = epb_get_tag_value_offset(e->unpack_buf, e->buf_len, tag);
    if (offset < 0)
        return 0;

    return epb_get_fixed32_bits(e->unpack_buf+offset, e->buf_len-offset);
}

int32 epb_get_sfixed32(Epb *e, uint16 tag)
{
    return epb_get_fixed32(e, tag);
}

static uint16 epb_pack_tag(Epb *e, uint16 tag)
{
    uint16 tag_len = ((tag&0xff00) == 0) ? 1 : 2;
    if ((e->buf_len - e->buf_offset) >= tag_len) {
        uint8 *buf = e->pack_buf + e->buf_offset;
        if (tag_len == 2) 
            *(buf++) = 0xff&(tag>>8);
        *buf = 0xff&tag;
        e->buf_offset += tag_len;
        return tag_len;
    }
    return -1;
}

static uint16 epb_pack_varint32_bits(Epb *e, uint32 value)
{
    uint8 buf[5] = {0};
    uint16 i = 0;
    do {
        buf[i] = value&0x7f;
        if (i-1 >= 0)
            buf[i-1] |= 0x80;
        value = value >> 7;
        ++i;
    } while (value!=0 && i<5);
    if ((e->buf_len - e->buf_offset) >= i) {
        memcpy(e->pack_buf+e->buf_offset, buf, i);
        e->buf_offset += i;
        return i;
    }
    return -1;
}

void epb_pack_init(Epb *e, uint8 *buf, uint16 len)
{
    e->pack_buf = buf;
    e->buf_len = len;
    e->buf_offset = 0;
}

uint16 epb_get_packed_size(Epb *e)
{
    return e->buf_offset;
}

uint16 epb_set_uint32(Epb *e, uint16 tag, uint32 value)
{
    uint16 len = 0;
    uint16 ret = epb_pack_tag(e, tag);
    if (ret < 0) return ret;
    len += ret;

    ret = epb_pack_varint32_bits(e, value);
    if (ret < 0) return ret;
    len += ret;

    return len;
}

uint16 epb_set_int32(Epb *e, uint16 tag, int32 value)
{
    return epb_set_uint32(e, tag, value);
}

uint16 epb_set_sint32(Epb *e, uint16 tag, int32 value)
{
    uint32 v = (value << 1) ^ (value >> 31);
    return epb_set_uint32(e, tag, v);
}

uint16 epb_set_bool(Epb *e, uint16 tag, bool value)
{
    return epb_set_uint32(e, tag, value);
}

uint16 epb_set_enum(Epb *e, uint16 tag, uint16 value)
{
    return epb_set_uint32(e, tag, value);
}

static uint16 epb_set_fixed32_bits(Epb *e, uint32 value)
{
    if ((e->buf_len - e->buf_offset) >= 4) {
#ifdef __LITTLE_ENDIAN__
        memcpy(e->pack_buf+e->buf_offset, &value, 4);
#else
	{
		uint8 *data = (uint8 *)&value;
		for (uint16 i=0; i<4; i++) {
			*(e->pack_buf+e->buf_offset+i) = data[4-i];
		}
	}
#endif
        e->buf_offset += 4;
        return 4;
    }
    return -1;
}

static uint16 epb_pack_length_delimited(Epb *e, const uint8 *data, uint16 len)
{
    if ((e->buf_len - e->buf_offset) >= len) {
        memcpy(e->pack_buf + e->buf_offset, data, len);
        e->buf_offset += len;
        return len;
    }
    return -1;
}

uint16 epb_set_bytes(Epb *e, uint16 tag, const uint8 *data, uint16 length)
{
    uint16 len = 0;
    uint16 ret = epb_pack_tag(e, tag);
    if (ret < 0) return ret;
    len += ret;

    ret = epb_pack_varint32_bits(e, length);
    if (ret < 0) return ret;
    len += ret;

    ret = epb_pack_length_delimited(e, data, length);
    if (ret < 0) return ret;
    len += ret;

    return len;
}

uint16 epb_set_string(Epb *e, uint16 tag, const char *data, uint16 len)
{
    return epb_set_bytes(e, tag, (const uint8 *)data, len);
}

uint16 epb_set_message(Epb *e, uint16 tag, const uint8 *data, uint16 len)
{
    return epb_set_bytes(e, tag, data, len);
}

uint16 epb_set_fixed32(Epb *e, uint16 tag, uint32 value)
{
    uint16 len = 0;
    uint16 ret = epb_pack_tag(e, tag);
    if (ret < 0) return ret;
    len += ret;

    ret = epb_set_fixed32_bits(e, value);
    if (ret < 0) return ret;
    len += ret;

    return len;
}

uint16 epb_set_sfixed32(Epb *e, uint16 tag, int32 value)
{
    return epb_set_fixed32(e, tag, value);
}

uint16 epb_set_float(Epb *e, uint16 tag, float value)
{
    uint32 v = *(uint32 *)&value;
    return epb_set_fixed32(e, tag, v);
}

uint16 epb_varint32_pack_size(uint16 tag, uint32 value, bool is_signed)
{
    uint16 i = 0;

    if (is_signed)
        value = (value << 1) ^ (value >> 31);

    do {
        value = value >> 7;
        ++i;
    } while (value!=0 && i<5);

    return (((tag&0xff00) == 0) ? 1 : 2) + i;
}

uint16 epb_fixed32_pack_size(uint16 tag)
{
    return (((tag&0xff00) == 0) ? 1 : 2) + 4;
}

uint16 epb_length_delimited_pack_size(uint16 tag, uint16 len)
{
    return epb_varint32_pack_size(tag, len, FALSE) + len;
}

