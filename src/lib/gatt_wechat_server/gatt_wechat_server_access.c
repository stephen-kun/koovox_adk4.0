/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include "gatt_wechat_server_access.h"

#define GATT_WECHAT_DEBUG_LIBx
#include "gatt_wechat_server_debug.h"
#include "gatt_wechat_server_private.h"
#include "gatt_wechat_server_db.h"

/* Required octets for values sent to Client Configuration Descriptor */
#define GATT_CLIENT_CONFIG_OCTET_SIZE sizeof(uint8) * 2
/* Required octets for values sent to Presentation Descriptor */
#define GATT_PRESENTATION_OCTET_SIZE sizeof(uint8) * 7


/***************************************************************************
NAME
    sendWechatAccessRsp

DESCRIPTION
    Send an access response to the GATT Manager library.
*/
static void sendWechatAccessRsp(Task task,
                                    uint16 cid,
                                    uint16 handle,
                                    uint16 result,
                                    uint16 size_value,
                                    const uint8 *value)
{
    if (!GattManagerServerAccessResponse(task, cid, handle, result, size_value, value))
    {
        /* The GATT Manager should always know how to send this response */
        GATT_WECHAT_DEBUG_PANIC(("Couldn't send GATT access response\n"));
		GATT_WECHAT_DEBUG(("Couldn't send GATT access response\n"));
    }
}

/***************************************************************************
NAME
    sendWechatAccessErrorRsp

DESCRIPTION
    Send an error access response to the GATT Manager library.
*/
static void sendWechatAccessErrorRsp(const GWECHATS *wechat_server, const GATT_MANAGER_SERVER_ACCESS_IND_T *access_ind, uint16 error)
{
    sendWechatAccessRsp((Task)&wechat_server->lib_task, access_ind->cid, access_ind->handle, error, 0, NULL);
}

/***************************************************************************
NAME
    wechatServiceAccess

DESCRIPTION
    Deals with access of the HANDLE_WECHAT_SERVICE handle.
*/
static void wechatServiceAccess(GWECHATS *wechat_server, const GATT_MANAGER_SERVER_ACCESS_IND_T *access_ind)
{

	GATT_WECHAT_DEBUG(("wechatServiceAccess\n"));

    if (access_ind->flags & ATT_ACCESS_READ)
    {
        sendWechatAccessRsp((Task)&wechat_server->lib_task, access_ind->cid, access_ind->handle, gatt_status_success, 0, NULL);
    }
    else if (access_ind->flags & ATT_ACCESS_WRITE)
    {
        /* Write of wechat level not allowed. */
        sendWechatAccessErrorRsp(wechat_server, access_ind, gatt_status_write_not_permitted);
    }
    else
    {
        /* Reject access requests that aren't read/write, which shouldn't happen. */
        sendWechatAccessErrorRsp(wechat_server, access_ind, gatt_status_request_not_supported);
    }
}


/***************************************************************************
NAME
    wechatServiceWriteAccess

DESCRIPTION
    Deals with access of the HANDLE_WECHAT_SERVICE handle.
*/
static void wechatServiceWriteAccess(GWECHATS *wechat_server, const GATT_MANAGER_SERVER_ACCESS_IND_T *access_ind)
{

	GATT_WECHAT_DEBUG(("wechatServiceWriteAccess\n"));

	if(access_ind->flags & ATT_ACCESS_WRITE)
	{
        MAKE_WECHAT_MESSAGE_WITH_VALUE(
            GATT_WECHAT_SERVER_WRITE_IND, 
            access_ind->size_value,
            access_ind->value
            );

		message->cid 	= access_ind->cid;
		message->handle = access_ind->handle;
		message->offset = access_ind->offset;

		MessageSend(wechat_server->app_task, GATT_WECHAT_SERVER_WRITE_IND, message);

		/* Library response to the access request */
		sendWechatAccessRsp(&wechat_server->lib_task, access_ind->cid, access_ind->handle, gatt_status_success, 0, NULL);
		
	}
	else
	{
		/* Reject access requests that aren't read/write, which shouldn't happen. */
		sendWechatAccessErrorRsp(wechat_server, access_ind, gatt_status_request_not_supported);
	}

}

/***************************************************************************
NAME
    wechatServiceReadAccess

DESCRIPTION
    Deals with access of the HANDLE_WECHAT_SERVICE handle.
*/
static void wechatServiceReadAccess(GWECHATS *wechat_server, const GATT_MANAGER_SERVER_ACCESS_IND_T *access_ind)
{

	GATT_WECHAT_DEBUG(("wechatServiceReadAccess\n"));

	if(access_ind->flags & ATT_ACCESS_READ)
	{
        MAKE_WECHAT_MESSAGE(GATT_WECHAT_SERVER_READ_IND);
        message->wechat_server 	= wechat_server;     
        message->cid 			= access_ind->cid;                 
		message->handle 		= access_ind->handle;
        MessageSend(wechat_server->app_task, GATT_WECHAT_SERVER_READ_IND, message);
	}
	else
	{
		/* Reject access requests that aren't read/write, which shouldn't happen. */
		sendWechatAccessErrorRsp(wechat_server, access_ind, gatt_status_request_not_supported);
	}

}


/***************************************************************************
NAME
    wechatServerIndicateAccess

DESCRIPTION
    Deals with access of the HANDLE_WECHAT_LEVEL handle.
*/
static void wechatServerIndicateAccess(GWECHATS *wechat_server, const GATT_MANAGER_SERVER_ACCESS_IND_T *access_ind)
{

	GATT_WECHAT_DEBUG(("wechatServerIndicateAccess\n"));

    if (access_ind->flags & ATT_ACCESS_READ)
    {
        /* Send read level message to app_task so it can return the current level */
        MAKE_WECHAT_MESSAGE(GATT_WECHAT_SERVER_INDICATE_IND);
        message->wechat_server 	= wechat_server;     /* Pass the instance which can be returned in the response */
        message->cid 			= access_ind->cid;                 /* Pass the CID which can be returned in the response */
		message->handle 		= access_ind->handle;
        MessageSend(wechat_server->app_task, GATT_WECHAT_SERVER_INDICATE_IND, message);
    }
    else if (access_ind->flags & ATT_ACCESS_WRITE)
    {
        /* Write of wechat level not allowed. */
        sendWechatAccessErrorRsp(wechat_server, access_ind, gatt_status_write_not_permitted);
    }
    else
    {
        /* Reject access requests that aren't read/write, which shouldn't happen. */
        sendWechatAccessErrorRsp(wechat_server, access_ind, gatt_status_request_not_supported);
    }
}

/***************************************************************************
NAME
    wechatClientConfigAccess

DESCRIPTION
    Deals with access of the HANDLE_WECHAT_LEVEL_CLIENT_CONFIG handle.
*/
static void wechatClientConfigAccess(GWECHATS *wechat_server, const GATT_MANAGER_SERVER_ACCESS_IND_T *access_ind)
{

	GATT_WECHAT_DEBUG(("wechatClientConfigAccess\n"));

	if(access_ind->flags & ATT_ACCESS_READ)
	{
        MAKE_WECHAT_MESSAGE(GATT_WECHAT_SERVER_INDICATE_READ_CLIENT_CONFIG_IND);
        message->wechat_server = wechat_server;     
        message->cid 			= access_ind->cid;    
		message->cid 			= access_ind->handle;
        MessageSend(wechat_server->app_task, GATT_WECHAT_SERVER_INDICATE_READ_CLIENT_CONFIG_IND, message);
	}
    else if (access_ind->flags & ATT_ACCESS_WRITE)
    {
        if (access_ind->size_value == GATT_CLIENT_CONFIG_OCTET_SIZE)
        {
            /* On a Write, send new client config value to the app */
            MAKE_WECHAT_MESSAGE(GATT_WECHAT_SERVER_INDICATE_WRITE_CLIENT_CONFIG_IND);
            message->wechat_server 	= wechat_server;
            message->cid 			= access_ind->cid;
			message->handle 		= access_ind->handle;
            message->config_value 	= (access_ind->value[0] & 0xFF) | ((access_ind->value[1] << 8) & 0xFF00);
            MessageSend(wechat_server->app_task, GATT_WECHAT_SERVER_INDICATE_WRITE_CLIENT_CONFIG_IND, message);
            /* Library response to the access request */
            sendWechatAccessRsp(&wechat_server->lib_task, access_ind->cid, access_ind->handle, gatt_status_success, 0, NULL);
        }
        else
        {
            sendWechatAccessErrorRsp(wechat_server, access_ind, gatt_status_invalid_length);
        }
    }
    else
    {
        /* Reject access requests that aren't read/write, which shouldn't happen. */
        sendWechatAccessErrorRsp(wechat_server, access_ind, gatt_status_request_not_supported);
    }
}



/***************************************************************************/
void handleWechatAccess(GWECHATS *wechat_server, const GATT_MANAGER_SERVER_ACCESS_IND_T *access_ind)
{
    switch (access_ind->handle)
    {
        case HANDLE_WECHAT:
        {
            wechatServiceAccess(wechat_server, access_ind);
        }
        break;

		case HANDLE_WRITE_CHARACTERISTIC:
		{
			wechatServiceWriteAccess(wechat_server, access_ind);
		}
		break;

		case HANDLE_INDICATE_CHARACTERISTIC:
		{
            wechatServerIndicateAccess(wechat_server, access_ind);
		}
		break;

		case HANDLE_WECHAR_CLIENT_CONFIG:
		{
            if (wechat_server->notifications_enabled)
            {
                wechatClientConfigAccess(wechat_server, access_ind);
            }
            else
            {
                /* Handle shouldn't be accessed if notifications disabled */
                sendWechatAccessErrorRsp(wechat_server, access_ind, gatt_status_invalid_handle);
            }
		}
		break;

		case HANDLE_READ_CHARACTERISTIC:
		{
			wechatServiceReadAccess(wechat_server, access_ind);
		}
		break;
               
        default:
        {

			GATT_WECHAT_DEBUG(("handleWechatAccess:%d\n", access_ind->handle));

            /* Respond to invalid handles */
            sendWechatAccessErrorRsp(wechat_server, access_ind, gatt_status_invalid_handle);
        }
        break;
    }
}


/***************************************************************************/
void sendWechatReadAccessRsp(const GWECHATS *wechat_server, uint16 cid, uint16 handle, uint16 result, uint8* value, uint16 size_value)
{
    sendWechatAccessRsp((Task)&wechat_server->lib_task, cid, handle, result, size_value, value);
}


/***************************************************************************/
void sendWechatConfigAccessRsp(const GWECHATS *wechat_server, uint16 cid, uint16 handle, uint16 client_config)
{
    uint8 config_resp[GATT_CLIENT_CONFIG_OCTET_SIZE];
    
    config_resp[0] = client_config & 0xFF;
    config_resp[1] = (client_config >> 8) & 0xFF;

    sendWechatAccessRsp((Task)&wechat_server->lib_task, cid, handle, gatt_status_success, GATT_CLIENT_CONFIG_OCTET_SIZE, config_resp);
}


