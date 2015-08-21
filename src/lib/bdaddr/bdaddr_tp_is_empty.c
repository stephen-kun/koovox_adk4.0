/* Copyright Cambridge Silicon Radio Limited 2005 - 2015. */
/* Part of ADK 4.0 */

#include <bdaddr.h>

bool BdaddrTpIsEmpty(const tp_bdaddr *in)
{
    return  in->transport == TRANSPORT_NONE &&
            BdaddrTypedIsEmpty(&in->taddr);
}
