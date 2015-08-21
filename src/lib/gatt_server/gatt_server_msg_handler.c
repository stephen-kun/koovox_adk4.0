/*******************************************************************************
Copyright Cambridge Silicon Radio Limited 2014 - 2015.
Part of ADK 4.0

FILE NAME
    gatt_server_msg_handler.c

DESCRIPTION
    Contains the "GATT Server" Message handler, handles external messages
    sent to the "GATT Server" task.
    
NOTES

*/


/* Firmware headers */
#include <csrtypes.h>
#include <message.h>

/* External lib headers */
#include "gatt_manager.h"

/* "GATT Server" headers */
#include "gatt_server_msg_handler.h"
#include "gatt_server_access.h"
#include "gatt_server_indication.h"


/******************************************************************************/
void gattServerMsgHandler(Task task, MessageId id, Message payload)
{
    switch (id)
    {
        case GATT_MANAGER_SERVER_ACCESS_IND:
        {
            gattServerHandleGattManagerAccessInd(task, (GATT_MANAGER_SERVER_ACCESS_IND_T*)payload);
        }
        break;
        case GATT_MANAGER_REMOTE_CLIENT_INDICATION_CFM:
        {
            gattServerHandleGattManagerIndicationCfm(task, (GATT_MANAGER_REMOTE_CLIENT_INDICATION_CFM_T*)payload);
        }
        break;
        default:
        {
            /* Unrecognised GATT Manager message */
        }
        break;
    }
}
