/****************************************************************************
Copyright (C) Cambridge Silicon Radio Ltd. 2005 - 2015.

FILE NAME
    sink_gatt_server_wechat.c

DESCRIPTION
    Routines to handle messages sent from the GATT Wechat Server Task.
*/
#include "sink_gatt_db.h"
#include "sink_gatt_server_wechat.h"

#include "sink_debug.h"
#include "sink_development.h"
#include "sink_gatt_server.h"
#include "sink_powermanager.h"
#include "sink_private.h"

#include "koovox_wechat_handle.h"

#include <gatt_wechat_server.h>

#include <csrtypes.h>
#include <message.h>


#ifdef GATT_WECHAT_SERVER

#ifdef DEBUG_GATT_WECHAT_SERVER
#define GATT_WECHAT_SERVER_INFO(x) DEBUG(x)
#define GATT_WECHAT_SERVER_ERROR(x) DEBUG(x) TOLERATED_ERROR(x)
#else
#define GATT_WECHAT_SERVER_INFO(x)
#define GATT_WECHAT_SERVER_ERROR(x)
#endif


/* Assigned numbers for GATT Bluetooth Namespace Descriptors */ 
#define NAMESPACE_BLUETOOTH_SIG             0x01        /* Bluetooth SIG Namespace */ 

uint16 wechat_handle = 0;


/******************************************************************************
NAME
    sinkBleWechatLevelReadSendAndRepeat

DESCRIPTION
    Checks and dispatches the wechat levels required for each gatt connection.
	If required, it starts a repeat timer.

PARAMETERS
	NONE

RETURNS
    NONE
*/
void sinkBleWechatLevelReadSendAndRepeat(void)
{

}

/*******************************************************************************
NAME
    sinkGattGetWechatServerHandles

DESCRIPTION
    Handles for the given Wechat server.

PARAMETERS
    start      - wechat server start handle to return.
    end        - wechat server end handle to return.
    wechat_id - Wechat server ID

RETURNS
    TRUE if the Wechat server available, FALSE otherwise.
*/
static void sinkGattGetWechatServerHandles(uint16 *start, uint16 *end)
{
	*start 	= HANDLE_WECHAT;
	*end 	= HANDLE_WECHAT_END;
}


/*******************************************************************************
NAME
    sinkGattGetWechatServerUpdateRundata
    
DESCRIPTION
    Updates rundata for the given server.
    
PARAMETERS
    ptr        - ointer to allocated memory to store server tasks rundata.
    wechat_id - Wechat server ID
    
RETURNS
    TRUE if the Wechat server available, FALSE otherwise.
*/
static void sinkGattGetWechatServerUpdateRundata(uint16 **ptr)
{
    GATT_SERVER.wechat_server = (GWECHATS*)*ptr;
    *ptr += sizeof(GWECHATS);
}

/*******************************************************************************
NAME
    sinkGattWechatServerInitTask

DESCRIPTION
    Initialise a Wechat server task.
    NOTE: This function will modify *ptr.

PARAMETERS
    ptr - pointer to allocated memory to store server tasks rundata.
    remote_wechat - TRUE if a remote wechat, FALSE otherwise.

RETURNS
    TRUE if the Wechat server task was initialised, FALSE otherwise.
*/
static bool sinkGattWechatServerInitTask(uint16 **ptr)
{
    gatt_wechat_server_init_params_t params = {FALSE, TRUE};
    gatt_wechat_server_status_t wechat_status;
    uint16 start_handle;
    uint16 end_handle;

    if (!ptr)
    {
        return FALSE;
    }

    sinkGattGetWechatServerHandles(&start_handle, &end_handle);

    wechat_status = GattWechatServerInit((GWECHATS*)*ptr, sinkGetBleTask(), &params,
                                        start_handle, end_handle);
    if( wechat_status != gatt_wechat_server_status_success)
    {
        GATT_WECHAT_SERVER_INFO(("GATT Wechat Server init failed [%x]\n", wechat_status));
        return FALSE;
    }

    sinkGattGetWechatServerUpdateRundata(ptr);

    GATT_WECHAT_SERVER_INFO(("GATT Wechat Server initialised\n"));
    return TRUE;
}


/*******************************************************************************/
uint16 sinkGattWechatServerCalculateSize(void)
{
    /* Local wechat server size */
    uint16 size = sizeof(GWECHATS);

    GATT_WECHAT_SERVER_INFO(("WECH=[%d]\n", size));
    return size;
}


/*******************************************************************************/
bool sinkGattWechatServerInitialise(uint16 **ptr)
{
    /* Initialise wechat server for local wechat */
    if (!sinkGattWechatServerInitTask(ptr))
    {
        return FALSE;
    }

    return TRUE;
}


/******************************************************************************/
void sinkGattWechatServerMsgHandler(Task task, MessageId id, Message message)
{
    switch(id)
    {
        case GATT_WECHAT_SERVER_READ_IND:
        {
			GATT_WECHAT_SERVER_READ_IND_T* ind = (GATT_WECHAT_SERVER_READ_IND_T*)message;
			uint8 addr[6] = {0};
			
			GATT_WECHAT_SERVER_INFO(("GATT_WECHAT_SERVER_READ_IND\n"));

			KoovoxGetBluetoothAdrress((uint8 *)addr);
			
			GattWechatServerReadResponse(ind->wechat_server, ind->cid, ind->handle, 6, addr);
        }
        break;

		case GATT_WECHAT_SERVER_INDICATE_IND:
		{
			GATT_WECHAT_SERVER_INFO(("GATT_WECHAT_SERVER_INDICATE_IND\n"));
		}
		break;

		case GATT_WECHAT_SERVER_INDICATE_READ_CLIENT_CONFIG_IND:
		{
			GATT_WECHAT_SERVER_INDICATE_READ_CLIENT_CONFIG_IND_T* ircc = (GATT_WECHAT_SERVER_INDICATE_READ_CLIENT_CONFIG_IND_T*)message;
			uint16 client_config = 0;
			
			GATT_WECHAT_SERVER_INFO(("GATT_WECHAT_SERVER_INDICATE_READ_CLIENT_CONFIG_IND\n"));
			
			GattWechatServerReadClientConfigResponse(ircc->wechat_server, ircc->cid, ircc->handle, client_config);

		}
		break;

		case GATT_WECHAT_SERVER_INDICATE_WRITE_CLIENT_CONFIG_IND:
		{
			GATT_WECHAT_SERVER_INDICATE_WRITE_CLIENT_CONFIG_IND_T* iwcc = (GATT_WECHAT_SERVER_INDICATE_WRITE_CLIENT_CONFIG_IND_T*)message;
			GATT_WECHAT_SERVER_INFO(("GATT_WECHAT_SERVER_INDICATE_WRITE_CLIENT_CONFIG_IND\n"));
			
			koovox_handle_wechat_indicate(iwcc->cid, iwcc->handle);
			wechat_handle = iwcc->handle;
		}
		break;

		case GATT_WECHAT_SERVER_WRITE_IND:
		{
			GATT_WECHAT_SERVER_WRITE_IND_T* ind = (GATT_WECHAT_SERVER_WRITE_IND_T*)message;
			
			GATT_WECHAT_SERVER_INFO(("GATT_WECHAT_SERVER_WRITE_IND: handle=%x size=%d\n", ind->handle, ind->size_value));

			/* 处理消息 */
			koovox_write_from_wechat(ind->value, ind->size_value);
			
			/* 发送init req */
			if((g_wechatble_state.auth_state) 
				&& (!g_wechatble_state.init_state) 
				&& (!g_wechatble_state.init_send))
			{
				koovox_pack_wechat_init_req();
				koovox_indicate_to_wechat(ind->cid, wechat_handle);
				g_wechatble_state.init_send = TRUE;
			}
		}
		break;

		case GATT_WECHAT_SERVER_INDICATION_CFM:
		{
			GATT_WECHAT_SERVER_INDICATION_CFM_T* wsic = (GATT_WECHAT_SERVER_INDICATION_CFM_T*)message;

			GATT_WECHAT_SERVER_INFO(("GATT_WECHAT_SERVER_INDICATION_CFM: status=%d\n", wsic->status));
			
			if(wsic->status == gatt_status_success)
			{
				koovox_indicate_to_wechat(wsic->cid, wechat_handle);
			}
		}
		break;
		
        default:
        {
            /* Un-handled messages are not critical errors */
            GATT_WECHAT_SERVER_ERROR(("GATT Un-handled msg id[%x]\n", id));
        }
    }
}

#endif /* GATT_WECHAT_SERVER */
