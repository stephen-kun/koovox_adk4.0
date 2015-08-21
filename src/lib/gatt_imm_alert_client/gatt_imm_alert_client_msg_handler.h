/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#ifndef GATT_IMM_ALERT_CLIENT_MSG_HANDLER_H_
#define GATT_IMM_ALERT_CLIENT_MSG_HANDLER_H_


#include <csrtypes.h>
#include <message.h>

/***************************************************************************
NAME
    imm_alert_client_ext_msg_handler

DESCRIPTION
    Handler for messages sent to the library and internal messages. Expects notifications and indications
*/
void imm_alert_client_msg_handler(Task task, MessageId id, Message msg);

#endif /* GATT_IMM_ALERT_CLIENT_MSG_HANDLER_H_ */

