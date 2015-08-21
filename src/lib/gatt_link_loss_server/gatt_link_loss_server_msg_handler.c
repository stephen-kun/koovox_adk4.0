/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include <message.h>
#include <stdio.h>
#include <stdlib.h>

#include <gatt.h>

#include "gatt_link_loss_server_debug.h"
#include "gatt_link_loss_server_msg_handler.h"
#include "gatt_link_loss_server_access.h"
#include "gatt_link_loss_server.h"


/****************************************************************************/
void linkLossServerMsgHandler(Task task, MessageId id, Message msg)
{

    GLLSS_T *const link_loss_server = (GLLSS_T*)task;
    switch (id)
    {
        case GATT_MANAGER_SERVER_ACCESS_IND:
        {
             /* ATT Access IND is received */
            GATT_LINK_LOSS_DEBUG_INFO((" Received 'GATT_MANAGER_SERVER_ACCESS_IND' \n"));
            handle_link_loss_access(link_loss_server, (GATT_MANAGER_SERVER_ACCESS_IND_T *)msg);
        }
        break;
        default:
        {
            /* GATT unrecognised messages */
            GATT_LINK_LOSS_DEBUG_PANIC(("Func: link_loss_ext_msg_handler()  Unknown message \n"));
        }
        break;
    }
}


