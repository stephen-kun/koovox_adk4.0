/* Copyright Cambridge Silicon Radio Limited 2011 - 2015. */
/* Part of ADK 4.0 */

#include <bdaddr.h>

void BdaddrConvertBluestackToVm(bdaddr *out, const BD_ADDR_T *in)
{
    out->lap = (uint32)(in->lap);
    out->uap = (uint8)(in->uap);
    out->nap = (uint16)(in->nap);
}
