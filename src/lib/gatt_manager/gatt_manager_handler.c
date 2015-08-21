/*******************************************************************************
Copyright Cambridge Silicon Radio Limited 2014 - 2015.
Part of ADK 4.0
*/

#include <csrtypes.h>
#include <stdlib.h>
#include <string.h>

#include "gatt_manager_handler.h"
#include "gatt_manager_data.h"
#include "gatt_manager_server.h"
#include "gatt_manager_client.h"

static void handleGattInitCfm(GATT_INIT_CFM_T * cfm)
{
    if (gattManagerDataGetInitialisationState() != gatt_manager_initialisation_state_registering )
    {
        GATT_MANAGER_PANIC(("GM: Received GATT_INIT_CFM in wrong state[%x]\n",
                           gattManagerDataGetInitialisationState()));
    }

    if (gatt_status_success != cfm->status)
    {
        gattManagerDataInitialisationState_Registration();
        registerWithGattCfm(gatt_manager_status_failed);
    }
    else
    {
        gattManagerDataInitialisationState_Initialised();
        registerWithGattCfm(gatt_manager_status_success);
    }
}

static void handleGattConnectCfm(GATT_CONNECT_CFM_T * cfm)
{
    if (gatt_status_initialising == cfm->status)
    {
        if(gattManagerDataGetAdvertisingState() == gatt_manager_advertising_state_requested)
        {
            gattManagerServerAdvertising(cfm->cid);
        }
        else
        {
            GATT_MANAGER_DEBUG_INFO(("GM: Remote Server connection Initialising!"));
        }
    }
    else if (cfm->cid == gattManagerDataGetRemoteClientConnectCid())
    {
        gattManagerServerRemoteClientConnected(cfm);
    }
    else
    {
        gattManagerClientRemoteServerConnected(cfm);
    }
}

static void gattManageDisconnectInd(GATT_DISCONNECT_IND_T * ind)
{
    MAKE_GATT_MANAGER_MESSAGE(GATT_MANAGER_DISCONNECT_IND);
    message->status = ind->status;
    message->cid    = ind->cid;
    MessageSend(gattManagerDataGetApplicationTask(), GATT_MANAGER_DISCONNECT_IND,
                message);
}

static void gattManagerExchangeMtuInd(GATT_EXCHANGE_MTU_IND_T * ind)
{
    MAKE_GATT_MANAGER_MESSAGE(GATT_EXCHANGE_MTU_IND);
    memmove(message, ind, sizeof(GATT_EXCHANGE_MTU_IND_T));
    MessageSend(gattManagerDataGetApplicationTask(), GATT_EXCHANGE_MTU_IND,
                message);
}

static void gattManagerExchangeMtuCfm(GATT_EXCHANGE_MTU_CFM_T * cfm)
{
    MAKE_GATT_MANAGER_MESSAGE(GATT_EXCHANGE_MTU_CFM);
    memmove(message, cfm, sizeof(GATT_EXCHANGE_MTU_CFM_T));
    MessageSend(gattManagerDataGetApplicationTask(), GATT_EXCHANGE_MTU_CFM,
                message);
}

static void gattMessageHandler(Task task, MessageId id, Message payload)
{
    GATT_MANAGER_PANIC_NULL(payload, ("GM: Message payload is NULL!"));

    switch(id)
    {
        /* GATT Messages handled by the GATT Manager CONNECTION module */
        case GATT_INIT_CFM:
            handleGattInitCfm( (GATT_INIT_CFM_T*)payload );
            break;

        case GATT_CONNECT_CFM:
            handleGattConnectCfm( (GATT_CONNECT_CFM_T*)payload );
            break;

        case GATT_DISCONNECT_IND:
            gattManageDisconnectInd((GATT_DISCONNECT_IND_T*)payload);
            break;

        case GATT_EXCHANGE_MTU_CFM:
            gattManagerExchangeMtuCfm((GATT_EXCHANGE_MTU_CFM_T*)payload);
            break;

        case GATT_EXCHANGE_MTU_IND:
            gattManagerExchangeMtuInd((GATT_EXCHANGE_MTU_IND_T*)payload);
            break;

        /* GATT Messages that are forwarded to the client task */
        case GATT_NOTIFICATION_IND:
            gattManagerClientRemoteServerNotification((GATT_NOTIFICATION_IND_T*)payload);
            break;

        case GATT_INDICATION_IND:
            gattManagerClientRemoteServerIndication((GATT_INDICATION_IND_T*)payload);
            break;

        case GATT_DISCOVER_ALL_CHARACTERISTICS_CFM:
            gattManagerClientDiscoverAllCharacteristicsConfirm((GATT_DISCOVER_ALL_CHARACTERISTICS_CFM_T *)payload);
            break;

        case GATT_DISCOVER_ALL_CHARACTERISTIC_DESCRIPTORS_CFM:
            gattManagerClientDiscoverAllCharacteristicsDescriptorsConfirm((GATT_DISCOVER_ALL_CHARACTERISTIC_DESCRIPTORS_CFM_T *)payload);
            break;

        case GATT_READ_CHARACTERISTIC_VALUE_CFM:
            gattManagerClientReadCharacteristicValueConfirm((GATT_READ_CHARACTERISTIC_VALUE_CFM_T *)payload);
            break;

        case GATT_READ_USING_CHARACTERISTIC_UUID_CFM:
            gattManagerClientReadUsingCharacteristicUuidConfirm((GATT_READ_USING_CHARACTERISTIC_UUID_CFM_T *)payload);
            break;

        case GATT_READ_LONG_CHARACTERISTIC_VALUE_CFM:
            gattManagerClientReadLongCharacteristicValueConfirm((GATT_READ_LONG_CHARACTERISTIC_VALUE_CFM_T *)payload);
            break;

        case GATT_WRITE_WITHOUT_RESPONSE_CFM:
            gattManagerClientWriteWithoutResponseConfirm((GATT_WRITE_WITHOUT_RESPONSE_CFM_T *)payload);
            break;

        case GATT_SIGNED_WRITE_WITHOUT_RESPONSE_CFM:
            gattManagerClientSignedWriteWithoutResponseConfirm((GATT_SIGNED_WRITE_WITHOUT_RESPONSE_CFM_T *)payload);
            break;

        case GATT_WRITE_CHARACTERISTIC_VALUE_CFM:
            gattManagerClientWriteCharacteristicValueConfirm((GATT_WRITE_CHARACTERISTIC_VALUE_CFM_T *)payload);
            break;

        case GATT_WRITE_LONG_CHARACTERISTIC_VALUE_CFM:
            gattManagerClientWriteLongCharacteristicValueConfirm((GATT_WRITE_LONG_CHARACTERISTIC_VALUE_CFM_T *)payload);
            break;

        case GATT_RELIABLE_WRITE_PREPARE_CFM:
            gattManagerClientReliableWritePrepareConfirm((GATT_RELIABLE_WRITE_PREPARE_CFM_T *)payload);
            break;

        case GATT_RELIABLE_WRITE_EXECUTE_CFM:
            gattManagerClientReliableWriteExecuteConfirm((GATT_RELIABLE_WRITE_EXECUTE_CFM_T *)payload);
            break;

        /* GATT Messages handled by the GATT Manager Server module */
        case GATT_CONNECT_IND:
            gattManagerServerConnectInd((GATT_CONNECT_IND_T*)payload);
            break;

        case GATT_ACCESS_IND:
            gattManagerServerAccessInd((GATT_ACCESS_IND_T*)payload );
            break;

        case GATT_NOTIFICATION_CFM:
            gattManagerServerNotificationCfm((GATT_NOTIFICATION_CFM_T*)payload);
            break;

        case GATT_INDICATION_CFM:
            gattManagerServerIndicationCfm((GATT_INDICATION_CFM_T*)payload);
            break;

        default:
            GATT_MANAGER_DEBUG_PANIC(("GM: Un-handled GATT message [%x]\n", id));
            break;
    }
}

static void gattManagerInternalMessageHandler(Task task, MessageId id, Message payload)
{
    switch(id)
    {
        case GATT_MANAGER_INTERNAL_MSG_CANCEL_ADVERTISING:
            GattManagerCancelWaitForRemoteClient();
            break;

        case GATT_MANAGER_INTERNAL_MSG_WAIT_FOR_REMOTE_CLIENT:
            gattManagerWaitForRemoteClientInternal((GATT_MANAGER_INTERNAL_MSG_WAIT_FOR_REMOTE_CLIENT_T *)payload);
            break;

        case GATT_MANAGER_INTERNAL_MSG_CONNECT_TO_REMOTE_SERVER:
            GattManagerConnectToRemoteServerInternal((GATT_MANAGER_INTERNAL_MSG_CONNECT_TO_REMOTE_SERVER_T *)payload);
            break;

        default:
            GATT_MANAGER_DEBUG_PANIC(("ERROR: Un-handled Internal GATT Manager message [%x]\n", id));
            break;
    }
}

/******************************************************************************
 *                      GATT MANAGER Internal API                             *
 ******************************************************************************/

void registerWithGattCfm(gatt_manager_status_t status)
{
    MAKE_GATT_MANAGER_MESSAGE(GATT_MANAGER_REGISTER_WITH_GATT_CFM);
    message->status = status;
    MessageSend(gattManagerDataGetApplicationTask(),
                GATT_MANAGER_REGISTER_WITH_GATT_CFM, message);
}

void gattManagerMessageHandler(Task task, MessageId id, Message payload)
{
    if (!gattManagerDataIsInit())
    {
        GATT_MANAGER_PANIC(("GM: Not Initialised but received a message!"));
    }

    if ((id >= GATT_MESSAGE_BASE) && (id <= GATT_MESSAGE_TOP))
    {
        gattMessageHandler(task, id, payload);
    }
    else if ((id >= GATT_MANAGER_INTERNAL_MSG_BASE) &&
             (id < GATT_MANAGER_INTERNAL_MSG_TOP))
    {
        gattManagerInternalMessageHandler(task, id, payload);
    }
    else
    {
        GATT_MANAGER_DEBUG_PANIC(("ERROR: Un-handled message [%x]\n", id));
    }
}
