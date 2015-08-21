/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "gatt_wechat_server.h"

#include "gatt_wechat_server_msg_handler.h"
#include "gatt_wechat_server_private.h"
#include "gatt_wechat_server_db.h"


/****************************************************************************/
gatt_wechat_server_status_t GattWechatServerInit(GWECHATS *wechat_server, 
                                                   Task app_task,
                                                   const gatt_wechat_server_init_params_t *init_params,
                                                   uint16 start_handle,
                                                   uint16 end_handle)
{
    gatt_wechat_server_status_t result = gatt_wechat_server_status_invalid_parameter;

    /* Check parameters */
    if ((app_task != NULL) && (wechat_server != NULL))
    {
        gatt_manager_server_registration_params_t registration_params;
        
        /* Set up library handler for external messages */
        wechat_server->lib_task.handler = wechatServerMsgHandler;
        
        /* Store the Task function parameter.
           All library messages need to be sent here */
        wechat_server->app_task = app_task;
        
        /* Check optional initialisation parameters */
        /* When GATT_MANAGER_USE_CONST_DB is enabled then it is the callers responsibility
         * to register the appropriate GATT wechat server configuration when the 
         * const database is registered.
         */
        if (init_params)
        {
            /* Store indications/notifications enable flag */
            wechat_server->notifications_enabled = init_params->enable_notifications;
			wechat_server->indications_enabled = init_params->enable_indications;
        }
        else
        {
            wechat_server->notifications_enabled = 0;
			wechat_server->indications_enabled = 0;
        }
        
        /* Setup data required for Wechat Service to be registered with the GATT Manager */
        registration_params.task = &wechat_server->lib_task;
        registration_params.start_handle = start_handle;
        registration_params.end_handle = end_handle;
        
        /* Register with the GATT Manager and verify the result */
        if (GattManagerRegisterServer(&registration_params) == gatt_manager_status_success)
        {
            result = gatt_wechat_server_status_success;
        }
        else
        {
            result = gatt_wechat_server_status_registration_failed;
        }
    }
    
    return result;
}
