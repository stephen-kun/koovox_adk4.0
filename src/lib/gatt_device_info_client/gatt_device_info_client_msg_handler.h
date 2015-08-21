/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#ifndef GATT_DEVICE_INFO_CLIENT_MSG_HANDLER_H_
#define GATT_DEVICE_INFO_CLIENT_MSG_HANDLER_H_

#include <csrtypes.h>
#include <message.h>


/***************************************************************************
NAME
    deviceInfoClientMsgHandler

DESCRIPTION
    Handler for external messages sent to the library in the client role.
*/
void deviceInfoClientMsgHandler(Task task, MessageId id, Message payload);

#endif
