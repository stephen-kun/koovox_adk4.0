/*******************************************************************************
Copyright Cambridge Silicon Radio Limited 2014 - 2015.
Part of ADK 4.0
*/

#include <csrtypes.h>
#include <stdlib.h>
#include <string.h>
#include <message.h>

#include "gatt_manager_server.h"
#include "gatt_manager.h"
#include "gatt_manager_data.h"

static __inline__ size_t gattAccessIndSize(GATT_ACCESS_IND_T * ind)
{
    return ((ind->size_value) * sizeof(uint8));
}

static __inline__ size_t gattManagerServerAccessIndWithLenSize(GATT_ACCESS_IND_T * ind)
{
    return ((sizeof(GATT_MANAGER_SERVER_ACCESS_IND_T) - sizeof(uint8)) + gattAccessIndSize(ind));
}

static void serverAccessInd(GATT_ACCESS_IND_T * ind, Task task, uint16 handle)
{
    MAKE_GATT_MANAGER_MESSAGE_WITH_LEN(GATT_MANAGER_SERVER_ACCESS_IND, gattAccessIndSize(ind));
    memmove(message, ind, gattManagerServerAccessIndWithLenSize(ind));
            message->handle = handle;
    MessageSend(task, GATT_MANAGER_SERVER_ACCESS_IND, message);
}

static bool serverRegistrationParamsValid(const gatt_manager_server_registration_params_t * server)
{
    if (NULL == server ||
        0 == server->end_handle ||
        0 == server->start_handle ||
        NULL == server->task)
    {
        return FALSE;
    }

    return TRUE;
}

static bool serverConnectionParamsValid(Task task, const typed_bdaddr *taddr,
                                        gatt_connection_type conn_type)
{
    if( (NULL == task) ||
        (gatt_connection_ble_slave_directed == conn_type && NULL != taddr) ||
        (gatt_connection_ble_slave_whitelist == conn_type) ||
        (gatt_connection_ble_slave_undirected == conn_type))
    {
        return TRUE;
    }

    return FALSE;
}

static bool remoteClientValid(Task task, uint16 cid, uint16 handle)
{
    if(NULL != task ||
       0 != cid ||
       0!= handle)
    {
        return TRUE;
    }
    return FALSE;
}

static void remoteClientConnectCfmFail(Task task)
{
    MAKE_GATT_MANAGER_MESSAGE(GATT_MANAGER_REMOTE_CLIENT_CONNECT_CFM);
    message->status = gatt_status_failure;
    MessageSend(task, GATT_MANAGER_REMOTE_CLIENT_CONNECT_CFM, message);
}

static void remoteClientConnectCfm(GATT_CONNECT_CFM_T * cfm)
{
    MAKE_GATT_MANAGER_MESSAGE(GATT_MANAGER_REMOTE_CLIENT_CONNECT_CFM);
    message->status = cfm->status;
    message->taddr  = cfm->taddr;
    message->flags  = cfm->flags;
    message->cid    = cfm->cid;
    message->mtu    = cfm->mtu;
    MessageSend(gattManagerDataGetRemoteClientConnectTask(),
                GATT_MANAGER_REMOTE_CLIENT_CONNECT_CFM, message);
}

static void cancelRemoteClientConnectCfm(Task task, gatt_manager_status_t status)
{
    MAKE_GATT_MANAGER_MESSAGE(GATT_MANAGER_CANCEL_REMOTE_CLIENT_CONNECT_CFM);
    message->status = status;
    MessageSend(task, GATT_MANAGER_CANCEL_REMOTE_CLIENT_CONNECT_CFM, message);
}

static void remoteClientNotificationCfm(GATT_NOTIFICATION_CFM_T * cfm, Task task,
                                        uint16 handle)
{
    MAKE_GATT_MANAGER_MESSAGE(GATT_MANAGER_REMOTE_CLIENT_NOTIFICATION_CFM);
    memmove(message, cfm, sizeof(GATT_MANAGER_REMOTE_CLIENT_NOTIFICATION_CFM_T));
    message->handle = handle;
    MessageSend(task, GATT_MANAGER_REMOTE_CLIENT_NOTIFICATION_CFM, message);
}

static void remoteClientIndicationCfm(GATT_INDICATION_CFM_T * cfm, Task task,
                                      uint16 handle)
{
    MAKE_GATT_MANAGER_MESSAGE(GATT_INDICATION_CFM);
    memmove(message, cfm, sizeof(GATT_INDICATION_CFM_T));
    message->handle = handle;
    MessageSend(task, GATT_MANAGER_REMOTE_CLIENT_INDICATION_CFM, message);
}

static void gattConnectCfmPanicOnWrongCid(GATT_CONNECT_CFM_T * cfm)
{
    if(cfm->cid != gattManagerDataGetRemoteClientConnectCid())
    {
         GATT_MANAGER_PANIC(("GM: Unknown CID in Connect CFM!"));
    }
}

static void gattConnectCfmSuccess(GATT_CONNECT_CFM_T * cfm)
{
    if (gattManagerDataIsCancelPending())
    {
        cancelRemoteClientConnectCfm(gattManagerDataGetRemoteClientConnectTask(),
                                     gatt_manager_status_failed);
    }

    gattManagerDataAdvertisingState_Idle();
    remoteClientConnectCfm(cfm);
}

static void gattConnectCfmFailure(GATT_CONNECT_CFM_T * cfm)
{
    if (gattManagerDataIsCancelPending())
    {
        gattManagerDataPendingCancelled();
        cancelRemoteClientConnectCfm(gattManagerDataGetRemoteClientConnectTask(),
                                     gatt_manager_status_success);
    }
    else
    {
        remoteClientConnectCfm(cfm);
    }
    gattManagerDataAdvertisingState_Idle();
}

static void gattConnectCfmUnknown(GATT_CONNECT_CFM_T * cfm)
{
    if (gattManagerDataIsCancelPending())
    {
        cancelRemoteClientConnectCfm(gattManagerDataGetRemoteClientConnectTask(),
                                     gatt_manager_status_failed);
    }
    else
    {
        remoteClientConnectCfm(cfm);
    }
}

static void clearRemoteClientConnectData(void)
{
    gattManagerDataSetRemoteClientConnectTask(NULL);
    gattManagerDataSetRemoteClientConnectCid(0);
}

/******************************************************************************
 *                      GATT MANAGER SERVER PUBLIC API                        *
 ******************************************************************************/

gatt_manager_status_t GattManagerRegisterServer(const gatt_manager_server_registration_params_t * server)
{
    if (!gattManagerDataIsInit())
    {
        return gatt_manager_status_not_initialised;
    }

    if (gattManagerDataGetInitialisationState() != gatt_manager_initialisation_state_registration)
    {
        return gatt_manager_status_wrong_state;
    }

    if (!serverRegistrationParamsValid(server))
    {
        return gatt_manager_status_invalid_parameters;
    }

    if (gattManagerDataGetDB() == NULL)
    {
        return gatt_manager_status_failed;
    }

    if (!gattManagerDataAddServer(server))
    {
        return gatt_manager_status_invalid_parameters;
    }

    return gatt_manager_status_success;
}

void GattManagerWaitForRemoteClient(Task task,
                                    const typed_bdaddr *taddr,
                                    gatt_connection_type conn_type)
{
    if (!gattManagerDataIsInit())
    {
        GATT_MANAGER_PANIC(("GM: Not initialised!"))
    }

    if (gattManagerDataGetInitialisationState() != gatt_manager_initialisation_state_initialised)
    {
        GATT_MANAGER_PANIC(("GM: In wrong Initialisation state!"))
    }

    if(!serverConnectionParamsValid(task, taddr, conn_type))
    {
        GATT_MANAGER_PANIC(("GM: Invalid parameters!"))
    }

    if(gattManagerDataServerCount() == 0)
    {
        GATT_MANAGER_PANIC(("GM: No Servers registered!"))
    }

    if(gattManagerDataGetAdvertisingState() == gatt_manager_advertising_state_idle)
    {
        gattManagerDataSetRemoteClientConnectTask(task);

        if(gattManagerDataGetRemoteServerConnectHandler())
        {
            MAKE_GATT_MANAGER_MESSAGE(GATT_MANAGER_INTERNAL_MSG_WAIT_FOR_REMOTE_CLIENT);
            message->task = task;
            if(NULL != taddr)
            {
                message->taddr_not_null = TRUE;
                message->taddr = *taddr;
            }
            message->conn_type = conn_type;
            MessageSendConditionallyOnTask(gattManagerDataGetTask(),
                                           GATT_MANAGER_INTERNAL_MSG_WAIT_FOR_REMOTE_CLIENT,
                                           message, gattManagerDataGetPointerToRemoteServerConnectHandler());
            gattManagerDataAdvertisingState_Queued();
        }
        else
        {
            GattConnectRequest(gattManagerDataGetTask(), taddr, conn_type, FALSE);
            gattManagerDataAdvertisingState_Requested();
        }
    }
    else
    {
        remoteClientConnectCfmFail(task);
    }
}

void GattManagerCancelWaitForRemoteClient(void)
{
    if (!gattManagerDataIsInit())
    {
        GATT_MANAGER_PANIC(("GM: Not initialised!"));
    }

    if (gattManagerDataGetInitialisationState() != gatt_manager_initialisation_state_initialised)
    {
        GATT_MANAGER_PANIC(("GM: In wrong Initialisation state!"));
    }

    if(gattManagerDataServerCount() == 0)
    {
        GATT_MANAGER_PANIC(("GM: No Servers registered!"))
    }

    if (gattManagerDataIsCancelPending())
    {
        GATT_MANAGER_DEBUG_INFO(("GM: Repeat Disconnect Request Ignored!"))
        return;
    }

    switch(gattManagerDataGetAdvertisingState())
    {
        case gatt_manager_advertising_state_requested:
            /* Can't issue a disconnect until the GATT_CONNECT_CFM returns as
             * the CID is not known at this point. So this request must be
             * queued until the GATT_CONNECT_CFM message indicating the pending
             * advertising request has been received.
             * */
            MessageCancelFirst(gattManagerDataGetTask(),
                               GATT_MANAGER_INTERNAL_MSG_CANCEL_ADVERTISING);
            MessageSendConditionally(gattManagerDataGetTask(),
                                     GATT_MANAGER_INTERNAL_MSG_CANCEL_ADVERTISING,
                                     0, gattManagerDataGetAdvertisingRequestedFlag());
            break;

        case gatt_manager_advertising_state_advertising:
            gattManagerDataCancelPending();
            GattDisconnectRequest(gattManagerDataGetRemoteClientConnectCid());
            break;

        case gatt_manager_advertising_state_queued:
            if(MessageCancelAll(gattManagerDataGetTask(), GATT_MANAGER_INTERNAL_MSG_WAIT_FOR_REMOTE_CLIENT) > 0)
            {
                cancelRemoteClientConnectCfm(gattManagerDataGetRemoteClientConnectTask(),
                                             gatt_status_success);
                clearRemoteClientConnectData();
                gattManagerDataAdvertisingState_Idle();
            }
            else
            {
                GATT_MANAGER_PANIC(("GM: No WaitFor Remote Client Queued!"))
            }
            break;

        case gatt_manager_advertising_state_idle:
            cancelRemoteClientConnectCfm(gattManagerDataGetApplicationTask(),
                                         gatt_manager_status_wrong_state);
            break;

        default:
            GATT_MANAGER_PANIC(("GM: In Impossible state!"));
            break;
    }
}

bool GattManagerServerAccessResponse(Task task,
                                     uint16 cid,
                                     uint16 handle,
                                     uint16 result,
                                     uint16 size_value,
                                     const uint8 *value)
{
    uint16 adjusted_handle;

    if (!gattManagerDataIsInit())
    {
        return FALSE;
    }

    if(!remoteClientValid(task, cid, handle))
    {
        return FALSE;
    }

    adjusted_handle = gattManagerDataGetServerDatabaseHandle(task, handle);
    if (adjusted_handle == 0)
    {
        return FALSE;
    }

    GattAccessResponse(cid, adjusted_handle, result, size_value, value);

    return TRUE;
}

void GattManagerRemoteClientNotify(Task   task,
                                   uint16 cid,
                                   uint16 handle,
                                   uint16 size_value,
                                   const uint8 *value)
{
    uint16 adjusted_handle;

    if (!gattManagerDataIsInit())
    {
        GATT_MANAGER_PANIC(("GM: Not initialised!"));
    }

    if(!remoteClientValid(task, cid, handle))
    {
        GATT_MANAGER_PANIC(("GM: Remote Client Notify Invalid parameters!"));
    }

    adjusted_handle = gattManagerDataGetServerDatabaseHandle(task, handle);
    if (adjusted_handle)
    {
        GattNotificationRequest(gattManagerDataGetTask(), cid, adjusted_handle,
                                size_value, value);
    }
    else
    {
        MAKE_GATT_MANAGER_MESSAGE(GATT_MANAGER_REMOTE_CLIENT_NOTIFICATION_CFM);
        message->status = gatt_status_failure;
        MessageSend(task, GATT_MANAGER_REMOTE_CLIENT_NOTIFICATION_CFM, message);
    }
}

void GattManagerRemoteClientIndicate(Task   task,
                                     uint16 cid,
                                     uint16 handle,
                                     uint16 size_value,
                                     const uint8 *value)
{
    uint16 adjusted_handle;

    if (!gattManagerDataIsInit())
    {
        GATT_MANAGER_PANIC(("GM: Not initialised!"));
    }

    if(!remoteClientValid(task, cid, handle))
    {
        GATT_MANAGER_PANIC(("GM: Remote Client Notify Invalid parameters!"));
    }

    adjusted_handle = gattManagerDataGetServerDatabaseHandle(task, handle);
    if (adjusted_handle)
    {
        GattIndicationRequest(gattManagerDataGetTask(), cid, adjusted_handle,
                              size_value, value);
    }
    else
    {
        MAKE_GATT_MANAGER_MESSAGE(GATT_MANAGER_REMOTE_CLIENT_INDICATION_CFM);
        message->status = gatt_status_failure;
        MessageSend(task, GATT_MANAGER_REMOTE_CLIENT_INDICATION_CFM, message);
    }
}

/******************************************************************************
 *                      GATT MANAGER Server Internal API                      *
 ******************************************************************************/

void gattManagerWaitForRemoteClientInternal(GATT_MANAGER_INTERNAL_MSG_WAIT_FOR_REMOTE_CLIENT_T *params)
{
    GATT_MANAGER_PANIC_NULL(params, ("GM: Wait for Remote Client Internal params NULL!"));

    gattManagerDataAdvertisingState_Idle();
    GattManagerWaitForRemoteClient(params->task,
                                   ((TRUE == params->taddr_not_null) ? &params->taddr : NULL),
                                   params->conn_type);
}

void gattManagerServerConnectInd(GATT_CONNECT_IND_T * ind)
{
    MAKE_GATT_MANAGER_MESSAGE(GATT_CONNECT_IND);
    memmove(message, ind, sizeof(GATT_CONNECT_IND_T));
    MessageSend(gattManagerDataGetApplicationTask(), GATT_CONNECT_IND, message);
}

void gattManagerServerIndicationCfm(GATT_INDICATION_CFM_T * cfm)
{
    gatt_manager_resolve_server_handle_t discover;
    discover.handle = cfm->handle;

    if (gattManagerDataResolveServerHandle(&discover))
    {
        remoteClientIndicationCfm(cfm, discover.task, discover.adjusted);
    }
    else
    {
        remoteClientIndicationCfm(cfm, gattManagerDataGetApplicationTask(), cfm->handle);
    }
}

void gattManagerServerNotificationCfm(GATT_NOTIFICATION_CFM_T * cfm)
{
    gatt_manager_resolve_server_handle_t discover;
    discover.handle = cfm->handle;

    if (gattManagerDataResolveServerHandle(&discover))
    {
        remoteClientNotificationCfm(cfm, discover.task, discover.adjusted);
    }
    else
    {
        remoteClientNotificationCfm(cfm, gattManagerDataGetApplicationTask(), cfm->handle);
    }
}

void gattManagerServerAccessInd(GATT_ACCESS_IND_T * ind)
{
    if (ind->handle != 0)
    {
        gatt_manager_resolve_server_handle_t discover;
        discover.handle = ind->handle;

        if(gattManagerDataResolveServerHandle(&discover))
        {
            serverAccessInd(ind, discover.task, discover.adjusted);
        }
        else
        {
            serverAccessInd(ind, gattManagerDataGetApplicationTask(), ind->handle);
        }
    }
    else
    {
        gatt_manager_data_iterator_t iter;
        const gatt_manager_server_lookup_data_t *server;

        if(gattManagerDataServerIteratorStart(&iter))
        {
            while((server = gattManagerDataServerIteratorNext(&iter)) != NULL)
            {
                serverAccessInd(ind, server->task, ind->handle);
            }
        }
    }
}

void gattManagerServerAdvertising(uint16 cid)
{
    gattManagerDataSetRemoteClientConnectCid(cid);
    gattManagerDataAdvertisingState_Advertising();
}

void gattManagerServerRemoteClientConnected(GATT_CONNECT_CFM_T * cfm)
{
    gattConnectCfmPanicOnWrongCid(cfm);

    if(cfm->status == gatt_status_success)
    {
        gattConnectCfmSuccess(cfm);
    }
    else if (cfm->status == gatt_status_failure)
    {
        gattConnectCfmFailure(cfm);
    }
    else
    {
        gattConnectCfmUnknown(cfm);
    }

    clearRemoteClientConnectData();
}
