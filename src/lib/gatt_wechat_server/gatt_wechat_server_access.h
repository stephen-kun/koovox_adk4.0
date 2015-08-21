/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#ifndef GATT_WECHAT_SERVER_ACCESS_H_
#define GATT_WECHAT_SERVER_ACCESS_H_


#include <gatt_manager.h>

#include "gatt_wechat_server.h"


/***************************************************************************
NAME
    handleWechatAccess

DESCRIPTION
    Handles the GATT_MANAGER_SERVER_ACCESS_IND message that was sent to the wechat library.
*/
void handleWechatAccess(GWECHATS *wechat_server, const GATT_MANAGER_SERVER_ACCESS_IND_T *access_ind);


/***************************************************************************
NAME
    sendWechatReadAccessRsp

DESCRIPTION
    Sends a wechat level response back to the GATT Manager.
*/
void sendWechatReadAccessRsp(const GWECHATS *wechat_server, uint16 cid, uint16 handle, uint16 result, uint8* value, uint16 size_value);


/***************************************************************************
NAME
    sendBatteryConfigAccessRsp

DESCRIPTION
    Sends an client configuration access response back to the GATT Manager library.
*/
void sendWechatConfigAccessRsp(const GWECHATS *wechat_server, uint16 cid, uint16 handle, uint16 client_config);



#endif
