/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include <gatt_manager.h>

#include "gatt_battery_server_msg_handler.h"

#include "gatt_battery_server_access.h"
#include "gatt_battery_server_debug.h"
#include "gatt_battery_server.h"


/****************************************************************************/
void batteryServerMsgHandler(Task task, MessageId id, Message payload)
{
    GBASS *battery_server = (GBASS *)task;
    
    switch (id)
    {
        case GATT_MANAGER_SERVER_ACCESS_IND:
        {
            /* Read/write access to characteristic */
            handleBatteryAccess(battery_server, (GATT_MANAGER_SERVER_ACCESS_IND_T *)payload);
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
            GATT_BATTERY_DEBUG_PANIC(("GATT Manager Server Msg not handled\n"));
            GATT_BATTERY_DEBUG(("GATT Manager Server Msg not handled\n"));
        }
        break;
    }
}

