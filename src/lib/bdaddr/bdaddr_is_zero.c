/* Copyright Cambridge Silicon Radio Limited 2005 - 2015. */
/* Part of ADK 4.0 */

#include <bdaddr.h>

bool BdaddrIsZero(const bdaddr *in)
{ 
    return !in->nap && !in->uap && !in->lap; 
}
