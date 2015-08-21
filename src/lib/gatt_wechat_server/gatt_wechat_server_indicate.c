/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include <stdlib.h>

#include <gatt_manager.h>

#include "gatt_wechat_server.h"

#include "gatt_wechat_server_debug.h"
#include "gatt_wechat_server_private.h"
#include "gatt_wechat_server_db.h"


/****************************************************************************/
void GattWechatServerSendIndication(const GWECHATS *wechat_server, uint16 cid,  uint16 handle, uint16 size_value, const uint8* value)
{

	GattManagerRemoteClientIndicate((Task)&wechat_server->lib_task, cid, handle, size_value,value);
}

