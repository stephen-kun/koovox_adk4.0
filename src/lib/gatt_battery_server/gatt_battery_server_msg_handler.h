/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#ifndef GATT_BATTERY_SERVER_MSG_HANDLER_H_
#define GATT_BATTERY_SERVER_MSG_HANDLER_H_

#include <csrtypes.h>
#include <message.h>


/***************************************************************************
NAME
    batteryServerMsgHandler

DESCRIPTION
    Handler for external messages sent to the library in the server role.
*/
void batteryServerMsgHandler(Task task, MessageId id, Message payload);


#endif
