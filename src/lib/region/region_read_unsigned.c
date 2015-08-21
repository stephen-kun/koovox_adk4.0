/*******************************************************************************
 Copyright Cambridge Silicon Radio Limited 2015
 Part of ADK 4.0
*******************************************************************************/

#include "region.h"

uint32 RegionReadUnsigned(const Region *r)
{
    uint32 v = 0;
    const uint8 *p;
    for(p = r->begin; p != r->end; ++p)
        v = (v<<8) | *p;
    return v;
}
