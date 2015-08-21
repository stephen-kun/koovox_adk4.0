/*******************************************************************************
 Copyright Cambridge Silicon Radio Limited 2015
 Part of ADK 4.0
*******************************************************************************/

#include "service.h"

bool ServiceFindAttribute(Region *r, uint16 id, ServiceDataType *type, Region *out)
{
    uint16 found;
    while(ServiceNextAttribute(r, &found, type, out))
        if(found == id)
            return 1;
    return 0;
}

