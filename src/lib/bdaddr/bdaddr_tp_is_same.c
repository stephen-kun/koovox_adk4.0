/* Copyright Cambridge Silicon Radio Limited 2011 - 2015. */
/* Part of ADK 4.0 */

#include <bdaddr.h>

bool BdaddrTpIsSame(const tp_bdaddr *first, const tp_bdaddr *second)
{
    return  first->transport == second->transport && 
            BdaddrTypedIsSame(&first->taddr, &second->taddr);
}
