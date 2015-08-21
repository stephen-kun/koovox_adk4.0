/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#ifndef GATT_LINK_LOSS_SERVER_HANDLER_H_
#define GATT_LINK_LOSS_SERVER_HANDLER_H_

#include <csrtypes.h>
#include <message.h>


/***************************************************************************
NAME
    linkLossServerMsgHandler

DESCRIPTION
    Handler for external messages sent to the library.
*/
void linkLossServerMsgHandler(Task task, MessageId id, Message msg);


#endif /*GATT_LINK_LOSS_SERVER_HANDLER_H_*/

