/* Copyright Cambridge Silicon Radio Limited 2011 - 2015. */
/* Part of ADK 4.0 */

#include <bdaddr.h>

void BdaddrConvertTpVmToBluestack(
        TP_BD_ADDR_T         *out,
        const tp_bdaddr      *in
        )
{
    switch(in->transport)
    {
        case TRANSPORT_BREDR_ACL:
            out->tp_type= BREDR_ACL;
            break;
        case TRANSPORT_BLE_ACL:
            out->tp_type = LE_ACL;
            break;
        default:
            out->tp_type = NO_PHYSICAL_TRANSPORT;
            break;
    }
    BdaddrConvertTypedVmToBluestack(&out->addrt, &in->taddr);
}
