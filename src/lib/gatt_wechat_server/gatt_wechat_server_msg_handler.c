/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include <gatt_manager.h>

#include "gatt_wechat_server_msg_handler.h"

#include "gatt_wechat_server_access.h"
#include "gatt_wechat_server_debug.h"
#include "gatt_wechat_server.h"
#include "gatt_wechat_server_private.h"



/****************************************************************************/
void wechatServerMsgHandler(Task task, MessageId id, Message payload)
{
    GWECHATS *wechat_server = (GWECHATS *)task;
    
    switch (id)
    {
        case GATT_MANAGER_SERVER_ACCESS_IND:
        {
            /* Read/write access to characteristic */
            handleWechatAccess(wechat_server, (GATT_MANAGER_SERVER_ACCESS_IND_T *)payload);
        }
        break;

		case GATT_MANAGER_REMOTE_CLIENT_INDICATION_CFM:
		{
			GATT_MANAGER_REMOTE_CLIENT_INDICATION_CFM_T* rcic = (GATT_MANAGER_REMOTE_CLIENT_INDICATION_CFM_T*)payload;
			MAKE_WECHAT_MESSAGE(GATT_WECHAT_SERVER_INDICATION_CFM);
			message->wechat_server	= wechat_server;
			message->status 		= rcic->status;
			message->cid    		= rcic->cid;
			message->handle 		= rcic->handle;
			
			MessageSend(wechat_server->app_task, GATT_WECHAT_SERVER_INDICATION_CFM, message);

		}
		break;
		
        default:
        {
            /* Unrecognised GATT Manager message */
            GATT_WECHAT_DEBUG_PANIC(("GATT Manager Server Msg not handled\n"));
        }
        break;
    }
}

