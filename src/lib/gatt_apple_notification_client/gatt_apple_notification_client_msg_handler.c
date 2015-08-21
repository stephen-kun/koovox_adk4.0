/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include <gatt.h>
#include <gatt_manager.h>

#include "gatt_apple_notification_client_msg_handler.h"

#include "gatt_apple_notification_client.h"
#include "gatt_apple_notification_client_debug.h"
#include "gatt_apple_notification_client_discover.h"
#include "gatt_apple_notification_client_notification.h"
#include "gatt_apple_notification_client_private.h"
#include "gatt_apple_notification_client_write.h"


/****************************************************************************/
static void handleGattManagerMsg(Task task, MessageId id, Message payload)
{
    GANCS *ancs = (GANCS *)task;

    if(ancs != NULL)
    {
        switch (id)
        {
            case GATT_MANAGER_REMOTE_SERVER_NOTIFICATION_IND:
            {
                handleAncsNotification(ancs, (GATT_MANAGER_REMOTE_SERVER_NOTIFICATION_IND_T *)payload);
            }
            break;

            case GATT_MANAGER_DISCOVER_ALL_CHARACTERISTICS_CFM:
            {
                handleAncsDiscoverAllCharacteristicsResp(ancs, (GATT_MANAGER_DISCOVER_ALL_CHARACTERISTICS_CFM_T *)payload);
            }
            break;

            case GATT_MANAGER_DISCOVER_ALL_CHARACTERISTIC_DESCRIPTORS_CFM:
            {
                handleAncsDiscoverAllCharacteristicDescriptorsResp(ancs, (GATT_MANAGER_DISCOVER_ALL_CHARACTERISTIC_DESCRIPTORS_CFM_T *)payload);
            }
            break;

            case GATT_MANAGER_WRITE_CHARACTERISTIC_VALUE_CFM:
            {
                handleAncsWriteValueResp(ancs, (GATT_MANAGER_WRITE_CHARACTERISTIC_VALUE_CFM_T *)payload);
            }
            break;

            default:
            {
                /* Unrecognised GATT Manager message */
                GATT_APPLE_NOTIFICATION_DEBUG_PANIC(("ANCS: Client GattMgr Msg not handled [0x%x]\n", id));
            }
            break;
        }
    }
}
            
/****************************************************************************/
static void handleGattMsg(Task task, MessageId id, Message payload)
{
    /* Unrecognised GATT Manager message */
    GATT_APPLE_NOTIFICATION_DEBUG_PANIC(("ANCS: Client GattMgr Msg not handled [0x%x]\n", id));
}

/****************************************************************************/
static void handleInternalAncsMsg(Task task, MessageId id, Message payload)
{
    GANCS *ancs = (GANCS *)task;

    if(ancs != NULL)
    {
        switch (id)
        {
            case ANCS_INTERNAL_MSG_SET_NS_NOTIFICATION:
            {
                /* Set the notification mask */
                ancs->ns_notification_mask = ((ANCS_INTERNAL_MSG_SET_NS_NOTIFICATION_T *)payload)->notifications_mask;
                ancsSetNotificationRequest(ancs, ((ANCS_INTERNAL_MSG_SET_NS_NOTIFICATION_T *)payload)->notifications_enable, 
                                                         GATT_APPLE_NOTIFICATION_NS);
            }
            break;

            case ANCS_INTERNAL_MSG_SET_DS_NOTIFICATION:
            {
                ancsSetNotificationRequest(ancs, ((ANCS_INTERNAL_MSG_SET_NS_NOTIFICATION_T *)payload)->notifications_enable, 
                                                         GATT_APPLE_NOTIFICATION_DS);
            }
            break;

            case ANCS_INTERNAL_MSG_WRITE_CP_CHARACTERISTIC:
            {
                /* Set the pending command, if it fails the response shall reset the pending_cmd */
                ancs->pending_cmd = ((ANCS_INTERNAL_MSG_WRITE_CP_CHARACTERISTIC_T *)payload)->pending_cmd;
                /* Control Point characteristic is optional, so if its not available return "not supported" */
                if(CHECK_VALID_HANDLE(ancs->control_point))
                {
                    if(!ancsWriteCharValue(ancs, (ANCS_INTERNAL_MSG_WRITE_CP_CHARACTERISTIC_T *)payload, ancs->control_point))
                    {
                        makeAncsWriteCPCfmMsg(ancs, gatt_ancs_status_not_allowed);
                    }
                }
                else
                {
                    makeAncsWriteCPCfmMsg(ancs, gatt_ancs_status_not_supported);
                }
            }
            break;
            
            default:
            {
                /* Unrecognised GATT Manager message */
                GATT_APPLE_NOTIFICATION_DEBUG_PANIC(("ANCS: Client Internal Msg not handled [0x%x]\n", id));
            }
            break;
        }
    }
}

/****************************************************************************/
void appleNotificationClientMsgHandler(Task task, MessageId id, Message payload)
{
    if ((id >= GATT_MANAGER_MESSAGE_BASE) && (id < GATT_MANAGER_MESSAGE_TOP))
    {
        handleGattManagerMsg(task, id, payload);
    }
    else if((id >= GATT_MESSAGE_BASE) && (id < GATT_MESSAGE_TOP))
    {
        handleGattMsg(task, id, payload);
    }
    else
    {
        handleInternalAncsMsg(task, id, payload);
    }
}

