/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <gatt_manager.h>

#include "gatt_wechat_server.h"

#include "gatt_wechat_server_access.h"
#include "gatt_wechat_server_private.h"

#include "gatt_wechat_server_debug.h"


/****************************************************************************/
gatt_wechat_server_status_t GattWechatServerReadResponse(const GWECHATS *wechat_server, uint16 cid, uint16 handle, uint16 size_value, uint8* value)
{
    gatt_status_t status = gatt_status_failure;

    if (wechat_server == NULL)
    {
        return gatt_wechat_server_status_invalid_parameter;
    }

	if(size_value >= 6)
	{
		status = gatt_status_success;
	}
	
    sendWechatReadAccessRsp(wechat_server, cid, handle, status, value, size_value);

    return gatt_wechat_server_status_success;
}


/****************************************************************************/
gatt_wechat_server_status_t GattWechatServerReadClientConfigResponse(const GWECHATS *wechat_server, uint16 cid, uint16 handle, uint16 client_config)
{
    gatt_wechat_server_status_t result = gatt_wechat_server_status_invalid_parameter;


    if (wechat_server != NULL)
    {
        sendWechatConfigAccessRsp(wechat_server, cid, handle, client_config);
        result = gatt_wechat_server_status_success;
    }
	
	GATT_WECHAT_DEBUG_INFO(("GattWechatServerReadClientConfigResponse : %x\n", result));
	
    return result;
}



