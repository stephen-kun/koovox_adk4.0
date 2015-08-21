/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include <stdio.h>
#include <stdlib.h>

#include <gatt_manager.h>

#include "gatt_device_info_server_msg_handler.h"

#include "gatt_device_info_server_access.h"
#include "gatt_device_info_server_debug.h"
#include "gatt_device_info_server.h"


/****************************************************************************/
void deviceInfoServerMsgHandler(Task task, MessageId id, Message payload)
{
    gdiss_t *const dev_info_server = (gdiss_t*)task;

    if(dev_info_server != NULL)
    {
        switch (id)
        {
            case GATT_MANAGER_SERVER_ACCESS_IND:
            {
                /* Read/write access to characteristic */
                handleDeviceInfoServerAccess(dev_info_server, (GATT_MANAGER_SERVER_ACCESS_IND_T *)payload);
            }
            break;
            case GATT_MANAGER_REMOTE_CLIENT_NOTIFICATION_CFM:
            {
                /* Library just absorbs confirmation messages */
            }
            break;
            default:
            {
                /* Unrecognised GATT Manager message */
                GATT_DEVICE_INFO_DEBUG_PANIC(("GATT Manager Server Msg not handled\n"));
            }
            break;
        }
    }
}


