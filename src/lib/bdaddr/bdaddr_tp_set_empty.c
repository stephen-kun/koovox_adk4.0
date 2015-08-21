/* Copyright Cambridge Silicon Radio Limited 2005 - 2015. */
/* Part of ADK 4.0 */

#include <bdaddr.h>

void BdaddrTpSetEmpty(tp_bdaddr *in)
{
    in->transport = TRANSPORT_NONE;
    BdaddrTypedSetEmpty(&in->taddr);
}

