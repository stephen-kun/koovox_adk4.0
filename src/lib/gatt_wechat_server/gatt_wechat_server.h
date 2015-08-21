/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

/*!
@file    gatt_wechat_server.h
@brief   Header file for the GATT wechat server library.

        This file provides documentation for the GATT wechat server library
        API (library name: gatt_wechat_server).
*/

#ifndef GATT_WECHAT_SERVER_H_
#define GATT_WECHAT_SERVER_H_

#include <csrtypes.h>
#include <message.h>

#include <library.h>

#include "gatt_manager.h"

/*! @brief The wechat server internal structure for the server role.

    This structure is visible to the application as it is responsible for managing resource to pass to the wechat library.
    The elements of this structure are only modified by the wechat library.
    The application SHOULD NOT modify the values at any time as it could lead to undefined behaviour.
    
 */
typedef struct __GWECHATS
{
    TaskData lib_task;
    Task app_task;
	unsigned indications_enabled:1;
    unsigned notifications_enabled:1;
} GWECHATS;


/*!
    @brief Status code returned from the GATT wechat server library

    This status code indicates the outcome of the request.
*/
typedef enum
{
    gatt_wechat_server_status_success,
    gatt_wechat_server_status_registration_failed,
    gatt_wechat_server_status_invalid_parameter,
    gatt_wechat_server_status_not_allowed,
    gatt_wechat_server_status_failed
} gatt_wechat_server_status_t;

/*! @brief Contents of the GATT_WECHAT_SERVER_READ_IND message that is sent by the library,
    due to a read of the local wechat level characteristic.
 */
typedef struct PACK_STRUCT __GATT_WECHAT_SERVER_READ_IND
{
    const GWECHATS *wechat_server;
    uint16 cid;
	uint16 handle;
} GATT_WECHAT_SERVER_READ_IND_T;

/*! @brief Contents of the GATT_WECHAT_SERVER_INDICATE_IND message that is sent by the library,
    due to a read of the local wechat level client configuration characteristic.
 */
typedef struct PACK_STRUCT __GATT_WECHAT_SERVER_INDICATE_IND
{
    const GWECHATS *wechat_server;
    uint16 cid;
	uint16 handle;
} GATT_WECHAT_SERVER_INDICATE_IND_T;


/*! @brief Contents of the GATT_WECHAT_SERVER_INDICATE_WRITE_CLIENT_CONFIG_IND message that is sent by the library,
    due to a write of the local wechat level client configuration characteristic.
 */
typedef struct PACK_STRUCT GATT_WECHAT_SERVER_INDICATE_READ_CLIENT_CONFIG_IND_T
{
    const GWECHATS *wechat_server;
    uint16 cid;
	uint16 handle;
} GATT_WECHAT_SERVER_INDICATE_READ_CLIENT_CONFIG_IND_T;


/*! @brief Contents of the GATT_WECHAT_SERVER_INDICATE_WRITE_CLIENT_CONFIG_IND message that is sent by the library,
    due to a write of the local wechat level client configuration characteristic.
 */
typedef struct PACK_STRUCT __GATT_WECHAT_SERVER_INDICATE_WRITE_CLIENT_CONFIG_IND
{
    const GWECHATS *wechat_server;
    uint16 cid;
	uint16 handle;
    uint16 config_value;
} GATT_WECHAT_SERVER_INDICATE_WRITE_CLIENT_CONFIG_IND_T;

/*! @brief Contents of the GATT_WECHAT_SERVER_INDICATION_CFM message that is sent by the library,
    due to a write of the local wechat level client configuration characteristic.
 */
typedef struct PACK_STRUCT __GATT_WECHAT_SERVER_INDICATION_CFM
{
    const GWECHATS *wechat_server;
	gatt_status_t   status;
    uint16 			cid;
	uint16 			handle;
} GATT_WECHAT_SERVER_INDICATION_CFM_T;


/*! @brief Contents of the GATT_WECHAT_SERVER_WRITE_IND message that is sent by the library,
    due to a read of the local presentation characteristic.
 */
typedef struct PACK_STRUCT __GATT_WECHAT_SERVER_WRITE_IND
{
    const GWECHATS *wechat_server;
    uint16 cid;
	uint16 handle;
	uint16 offset;
	uint16 size_value;
	uint8  value[1];
} GATT_WECHAT_SERVER_WRITE_IND_T;


/*! @brief Enumeration of messages an application task can receive from the wechat server library.
 */
typedef enum
{
    /* Server messages */
    GATT_WECHAT_SERVER_READ_IND = GATT_WECHAT_SERVER_MESSAGE_BASE, 	/* 00 */
    GATT_WECHAT_SERVER_INDICATE_IND,                            	/* 01 */
    GATT_WECHAT_SERVER_INDICATE_READ_CLIENT_CONFIG_IND,				/* 02 */
    GATT_WECHAT_SERVER_INDICATE_WRITE_CLIENT_CONFIG_IND,            /* 03 */
    GATT_WECHAT_SERVER_WRITE_IND,                       			/* 04 */
    GATT_WECHAT_SERVER_INDICATION_CFM,								/* 05 */
    
    /* Library message limit */
    GATT_WECHAT_SERVER_MESSAGE_TOP
} gatt_wechat_server_message_id_t;

/*!
    @brief Optional parameters used by the Initialisation API
    
    Parameters that can define how the wechat server library is initialised.
 */
typedef struct
{
   bool enable_indications;		/*! Flag that can be used to enable or disable indications */
   bool enable_notifications;     /*! Flag that can be used to enable or disable notifications */
} gatt_wechat_server_init_params_t;


/*!
    @brief Initialises the Wechat Service Library in the Server role.

    @param app_task The Task that will receive the messages sent from this wechat server library.
    @param wechat_server A valid area of memory that the service library can use.
    
    @return The status result of calling the API.

*/
gatt_wechat_server_status_t GattWechatServerInit(GWECHATS *wechat_server, 
                                                   Task app_task, 
                                                   const gatt_wechat_server_init_params_t *init_params,
                                                   uint16 start_handle,
                                                   uint16 end_hanlde);


/*!
    @brief This API is used to return a wechat level to the library when a GATT_WECHAT_SERVER_READ_IND message is received.

    @param wechat_server The instance pointer that was in the payload of the GATT_WECHAT_SERVER_READ_IND message.
    @param cid The connection identifier from the GATT_WECHAT_SERVER_READ_IND message.
    @param wechat_level The wechat level to return to the library. Valid values from 0-100, a value greater than 100% indicates error.
    @param status Success or failure to pass to the client.

    @return The status result of calling the API.

*/
gatt_wechat_server_status_t GattWechatServerReadResponse(const GWECHATS *wechat_server, uint16 cid, uint16 handle, uint16 size_value, uint8* value);

gatt_wechat_server_status_t GattWechatServerReadClientConfigResponse(const GWECHATS *wechat_server, uint16 cid, uint16 handle, uint16 client_config);

/*!
    @brief This API is used to notify a remote client of the wechat level. 
    This will only be allowed if notifications have been enabled by the remote device.

    @param wechat_server The instance pointer that was passed into the GattWechatServerInit API.
    @param number_cids The number of connection ID values passed in the cids parameter.
    @param cids The connection ID list. The wechat level notification will be sent on each connection that is supplied in the list.
    @param wechat_level The wechat level to send in the notification.
    
    @return none.

*/
void GattWechatServerSendIndication(const GWECHATS *wechat_server, uint16 cid,  uint16 handle, uint16 size_value, const uint8* value);


#endif
