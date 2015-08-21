/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include <gatt.h>
#include <gatt_manager.h>

#include "gatt_battery_client_msg_handler.h"

#include "gatt_battery_client.h"
#include "gatt_battery_client_debug.h"
#include "gatt_battery_client_discover.h"
#include "gatt_battery_client_notification.h"
#include "gatt_battery_client_private.h"
#include "gatt_battery_client_read.h"
#include "gatt_battery_client_write.h"


/****************************************************************************/
static void handleGattManagerMsg(Task task, MessageId id, Message payload)
{
    GBASC *battery_client = (GBASC *)task;
    
    switch (id)
    {
        case GATT_MANAGER_REMOTE_SERVER_NOTIFICATION_IND:
        {
            handleBatteryNotification(battery_client, (GATT_MANAGER_REMOTE_SERVER_NOTIFICATION_IND_T *)payload);
        }
        break;

        case GATT_MANAGER_DISCOVER_ALL_CHARACTERISTICS_CFM:
        {
            handleDiscoverAllCharacteristicsResp(battery_client, (GATT_MANAGER_DISCOVER_ALL_CHARACTERISTICS_CFM_T *)payload);
        }
        break;

        case GATT_MANAGER_DISCOVER_ALL_CHARACTERISTIC_DESCRIPTORS_CFM:
        {
            handleDiscoverAllCharacteristicDescriptorsResp(battery_client, (GATT_MANAGER_DISCOVER_ALL_CHARACTERISTIC_DESCRIPTORS_CFM_T *)payload);
        }
        break;

        case GATT_MANAGER_READ_CHARACTERISTIC_VALUE_CFM:
        {
            handleBatteryReadValueResp(battery_client, (GATT_MANAGER_READ_CHARACTERISTIC_VALUE_CFM_T *)payload);
        }
        break;

        case GATT_MANAGER_WRITE_CHARACTERISTIC_VALUE_CFM:
        {
            handleBatteryWriteValueResp(battery_client, (GATT_MANAGER_WRITE_CHARACTERISTIC_VALUE_CFM_T *)payload);
        }
        break;

        default:
        {
            /* Unrecognised GATT Manager message */
            GATT_BATTERY_DEBUG_PANIC(("BASC: Client GattMgr Msg not handled [0x%x]\n", id));
        }
        break;
    }
}

/****************************************************************************/
static void handleGattMsg(Task task, MessageId id, Message payload)
{
    /* Unrecognised GATT message */
    GATT_BATTERY_DEBUG_PANIC(("BASC: Client Gatt Msg not handled [0x%x]\n", id));
}

/****************************************************************************/
static void handleInternalBatteryMsg(Task task, MessageId id, Message payload)
{
    GBASC *battery_client = (GBASC *)task;
    
    switch (id)
    {
        case BATTERY_INTERNAL_MSG_READ_LEVEL:
        {
            batteryReadLevelRequest(battery_client, battery_client->handle_level_start, TRUE);
        }
        break;
        
        case BATTERY_INTERNAL_MSG_SET_NOTIFICATION:
        {
            batterySetNotificationRequest(battery_client, ((BATTERY_INTERNAL_MSG_SET_NOTIFICATION_T *)payload)->notifications_enable, TRUE);
        }
        break;
        
        case BATTERY_INTERNAL_MSG_READ_DESCRIPTOR:
        {
            batteryReadDescriptor(battery_client, ((BATTERY_INTERNAL_MSG_READ_DESCRIPTOR_T *)payload)->descriptor_uuid, TRUE);
        }
        break;
        
        default:
        {
            /* Unrecognised GATT Manager message */
            GATT_BATTERY_DEBUG_PANIC(("BASC: Client Internal Msg not handled [0x%x]\n", id));
        }
        break;
    }
}

/****************************************************************************/
void batteryClientMsgHandler(Task task, MessageId id, Message payload)
{
    if ((id >= GATT_MANAGER_MESSAGE_BASE) && (id < GATT_MANAGER_MESSAGE_TOP))
    {
        handleGattManagerMsg(task, id, payload);
    }
    else if ((id >= GATT_MESSAGE_BASE) && (id < GATT_MESSAGE_TOP))
    {
        handleGattMsg(task, id, payload);
    }
    else
    {
        handleInternalBatteryMsg(task, id, payload);
    }
}

