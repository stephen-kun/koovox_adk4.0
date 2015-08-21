/* Copyright Cambridge Silicon Radio Limited 2011 - 2015. */
/* Part of ADK 4.0 */

#include <bdaddr.h>

void BdaddrConvertVmToBluestack(BD_ADDR_T *out, const bdaddr *in)
{

    out->lap = (uint32_t)(in->lap);
    out->uap = (uint8_t)(in->uap);
    out->nap = (uint16_t)(in->nap);
}
