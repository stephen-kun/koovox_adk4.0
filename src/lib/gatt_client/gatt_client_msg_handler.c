/* Copyright (C) CSR plc, 2015 */
/* Part of ADK 4.0 */


#include "gatt_client_msg_handler.h"
#include "gatt_client.h"
#include "gatt_client_debug.h"
#include "gatt_client_discovery.h"
#include "gatt_client_private.h"
#include "gatt_client_write.h"

#include <gatt_manager.h>


/***************************************************************************/
static void sendServerChangedMsg(GGATTC *gatt_client, uint16 cid, uint16 start_handle, uint16 end_handle)
{
    MAKE_GATT_CLIENT_MESSAGE(GATT_CLIENT_SERVICE_CHANGED_IND);
    message->gatt_client = gatt_client;
    message->cid = cid;
    message->start_handle = start_handle;
    message->end_handle = end_handle;
    MessageSend(gatt_client->app_task, GATT_CLIENT_SERVICE_CHANGED_IND, message);
}


/***************************************************************************/
static void handleGattIndication(GGATTC *gatt_client, const GATT_MANAGER_REMOTE_SERVER_INDICATION_IND_T *ind)
{
    uint16 start_handle = 0x0;
    uint16 end_handle = 0xffff;
    
    GATT_CLIENT_DEBUG_INFO(("GATTC: Remote server indication cid=[0x%x] handle=[0x%x]\n", 
                            ind->cid, 
                            ind->handle));
    
    if (ind->handle == gatt_client->service_changed_handle)
    {
        if (ind->size_value >= 4)
        {
            start_handle = (ind->value[0] >> 8) | ind->value[1];
            end_handle = (ind->value[2] >> 8) | ind->value[3];
        }
        GATT_CLIENT_DEBUG_INFO(("    start_handle=[0x%x] end_handle=[0x%x]\n", 
                                start_handle, 
                                end_handle));
        /* Send Service Changed indication to app with range of handles affected */
        sendServerChangedMsg(gatt_client, 
                             ind->cid, 
                             start_handle, 
                             end_handle);
    }
    else
    {
        GATT_CLIENT_PANIC(("GATTC: Unrecognised server changed handle!\n"));
    }
    
    /* Send indication response */
    GattManagerIndicationResponse(ind->cid);
}


/****************************************************************************/
static void handleGattManagerMsg(Task task, MessageId id, Message payload)
{
    GGATTC *gatt_client = (GGATTC *)task;
    
    switch (id)
    {
        case GATT_MANAGER_REMOTE_SERVER_INDICATION_IND:
        {
            handleGattIndication(gatt_client, (GATT_MANAGER_REMOTE_SERVER_INDICATION_IND_T *)payload);
        }
        break;

        case GATT_MANAGER_DISCOVER_ALL_CHARACTERISTICS_CFM:
        {
            handleDiscoverAllGattCharacteristicsResp(gatt_client, (GATT_MANAGER_DISCOVER_ALL_CHARACTERISTICS_CFM_T *)payload);
        }
        break;

        case GATT_MANAGER_DISCOVER_ALL_CHARACTERISTIC_DESCRIPTORS_CFM:
        {
            handleDiscoverAllGattCharacteristicDescriptorsResp(gatt_client, (GATT_MANAGER_DISCOVER_ALL_CHARACTERISTIC_DESCRIPTORS_CFM_T *)payload);
        }
        break;
        
        case GATT_MANAGER_WRITE_CHARACTERISTIC_VALUE_CFM:
        {
            handleWriteValueResp(gatt_client, (GATT_MANAGER_WRITE_CHARACTERISTIC_VALUE_CFM_T *)payload);
        }
        break;

        default:
        {
            /* Unrecognised GATT Manager message */
            GATT_CLIENT_DEBUG_PANIC(("GATTC: Client GattMgr Msg not handled [0x%x]\n", id));
        }
        break;
    }
}

/****************************************************************************/
static void handleGattMsg(Task task, MessageId id, Message payload)
{
    /* Unrecognised GATT message */
    GATT_CLIENT_DEBUG_PANIC(("GATTC: Client Gatt Msg not handled [0x%x]\n", id));
}

/****************************************************************************/
void gattClientMsgHandler(Task task, MessageId id, Message payload)
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
        GATT_CLIENT_DEBUG_PANIC(("GATTC: Client Msg not handled [0x%x]\n", id));
    }
}

