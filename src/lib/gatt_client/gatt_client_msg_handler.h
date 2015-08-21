/* Copyright (C) CSR plc, 2015 */
/* Part of ADK 4.0 */

#ifndef GATT_CLIENT_MSG_HANDLER_H_
#define GATT_CLIENT_MSG_HANDLER_H_

#include <csrtypes.h>
#include <message.h>


/***************************************************************************
NAME
    gattClientMsgHandler

DESCRIPTION
    Handler for external messages sent to the library in the client role.
*/
void gattClientMsgHandler(Task task, MessageId id, Message payload);


#endif
