/****************************************************************************
Copyright Cambridge Silicon Radio Limited 2004 - 2015.
Part of ADK 4.0

FILE NAME
    ConnectionSmSendKeypressNotificationRequest.c        

DESCRIPTION
    This file contains the management entity responsible for device security

NOTES

*/


/****************************************************************************
    Header files
*/
#include "connection.h"
#include "connection_private.h"

#include <message.h>
#include <string.h>
#include <vm.h>


/*****************************************************************************/
void ConnectionSmSendKeypressNotificationRequest(
        const tp_bdaddr* tpaddr, 
        cl_sm_keypress_type type
        )
{
    MAKE_CL_MESSAGE(CL_INTERNAL_SM_SEND_KEYPRESS_NOTIFICATION_REQ);
    message->tpaddr = *tpaddr;
    message->type = type;
    MessageSend(
            connectionGetCmTask(), 
            CL_INTERNAL_SM_SEND_KEYPRESS_NOTIFICATION_REQ, 
            message
            );
}
