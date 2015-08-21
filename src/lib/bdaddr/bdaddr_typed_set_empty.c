/* Copyright Cambridge Silicon Radio Limited 2005 - 2015. */
/* Part of ADK 4.0 */

#include <bdaddr.h>

void BdaddrTypedSetEmpty(typed_bdaddr *in)
{
    in->type = TYPED_BDADDR_INVALID;
    BdaddrSetZero(&in->addr);
}
