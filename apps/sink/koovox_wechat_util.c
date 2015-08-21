/****************************************************************************
Copyright (C) JoySoft . 2015-2025
Part of KOOVOX 1.0.1

FILE NAME
    koovox_wechat_util.c

*/


#include "koovox_wechat_util.h"

#define BigLittleSwap16(A)  ((((uint16)(A) & 0xff00) >> 8) | \
                            (((uint16)(A) & 0x00ff) << 8))

 
#define BigLittleSwap32(A)  ((((uint32)(A) & 0xff000000) >> 24) | \
                            (((uint32)(A) & 0x00ff0000) >> 8) | \
                            (((uint32)(A) & 0x0000ff00) << 8) | \
                            (((uint32)(A) & 0x000000ff) << 24))

static uint16 checkCPUendian(void)
{
       union{
              uint32 i;
              uint8 s[4];
       }c;
 
       c.i = 0x12345678;
       return (0x12 == c.s[0]);
}

uint32 t_htonl(uint32 h)
{
       return checkCPUendian() ? h : BigLittleSwap32(h);
}
 
uint32 t_ntohl(uint32 n)
{

       return checkCPUendian() ? n : BigLittleSwap32(n);
}

uint16 htons(uint16 h)
{
       return checkCPUendian() ? h : BigLittleSwap16(h);
}
 
uint16 ntohs(uint16 n)
{
       return checkCPUendian() ? n : BigLittleSwap16(n);
}




