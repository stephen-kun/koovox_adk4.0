/*******************************************************************************
Copyright Cambridge Silicon Radio Limited 2014 - 2015.
Part of ADK 4.0

FILE NAME
    sink_gatt_server_wechat.h

DESCRIPTION
    Routines to handle messages sent from the GATT Wechat Server Task.
    
NOTES

*/


#ifndef _SINK_GATT_SERVER_WECHAT_H_
#define _SINK_GATT_SERVER_WECHAT_H_


#ifndef GATT_ENABLED
#undef GATT_WECHAT_SERVER
#endif


#include <gatt_wechat_server.h>

#include <csrtypes.h>
#include <message.h>


/*******************************************************************************
NAME
    sinkBleWechatLevelReadSendAndRepeat
    
DESCRIPTION
    Handle received BLE_INTERNAL_MESSAGE_WECHAT_READ_TIMER.
    
PARAMETERS
    None
    
RETURNS
    None.
*/
#ifdef GATT_WECHAT_SERVER
void sinkBleWechatLevelReadSendAndRepeat(void);
#else
#define sinkBleWechatLevelReadSendAndRepeat() ((void)(0)) 
#endif

/*******************************************************************************
NAME
    sinkGattWechatServerCalculateSize

DESCRIPTION
    Returns the size of data used by a wechat server entry.

PARAMETERS
    None

RETURNS
    The size of the wechat server data.
*/
#ifdef GATT_WECHAT_SERVER
uint16 sinkGattWechatServerCalculateSize(void);
#else
#define sinkGattWechatServerCalculateSize() (0)
#endif


/*******************************************************************************
NAME
    sinkGattWechatServerInitialise

DESCRIPTION
    Initialise the Wechat server tasks.
    NOTE: This function will modify *ptr.

PARAMETERS
    ptr - pointer to allocated memory to store server tasks rundata.

RETURNS
    TRUE if the Wechat server was initialised correctly, FALSE otherwise.
*/
#ifdef GATT_WECHAT_SERVER
bool sinkGattWechatServerInitialise(uint16 **ptr);
#else
#define sinkGattWechatServerInitialise(ptr) (TRUE)
#endif


/*******************************************************************************
NAME
    sinkGattWechatServerMsgHandler

DESCRIPTION
    Handle messages from the GATT Wechat Server library

PARAMETERS
    task    The task the message is delivered
    id      The ID for the GATT message
    payload The message payload

RETURNS
    void
*/
#ifdef GATT_WECHAT_SERVER
void sinkGattWechatServerMsgHandler(Task task, MessageId id, Message message);
#else
#define sinkGattWechatServerMsgHandler(task, id, message) ((void)(0))
#endif


#endif /* _SINK_GATT_SERVER_WECHAT_H_ */
