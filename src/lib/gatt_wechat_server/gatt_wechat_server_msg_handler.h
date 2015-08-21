/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#ifndef GATT_WECHAT_SERVER_MSG_HANDLER_H_
#define GATT_WECHAT_SERVER_MSG_HANDLER_H_

#include <csrtypes.h>
#include <message.h>


/***************************************************************************
NAME
    wechatServerMsgHandler

DESCRIPTION
    Handler for external messages sent to the library in the server role.
*/
void wechatServerMsgHandler(Task task, MessageId id, Message payload);


#endif
