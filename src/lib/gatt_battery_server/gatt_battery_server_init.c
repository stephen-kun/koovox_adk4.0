/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "gatt_battery_server.h"

#include "gatt_battery_server_msg_handler.h"
#include "gatt_battery_server_private.h"
#include "gatt_battery_server_db.h"


/****************************************************************************/
gatt_battery_server_status_t GattBatteryServerInit(GBASS *battery_server, 
                                                   Task app_task,
                                                   const gatt_battery_server_init_params_t *init_params,
                                                   uint16 start_handle,
                                                   uint16 end_handle)
{
    gatt_battery_server_status_t result = gatt_battery_server_status_invalid_parameter;

    /* Check parameters */
    if ((app_task != NULL) && (battery_server != NULL))
    {
        gatt_manager_server_registration_params_t registration_params;
        
        /* Set up library handler for external messages */
        battery_server->lib_task.handler = batteryServerMsgHandler;
        
        /* Store the Task function parameter.
           All library messages need to be sent here */
        battery_server->app_task = app_task;
        
        /* Check optional initialisation parameters */
        /* When GATT_MANAGER_USE_CONST_DB is enabled then it is the callers responsibility
         * to register the appropriate GATT battery server configuration when the 
         * const database is registered.
         */
        if (init_params)
        {
            /* Store notifications enable flag */
            battery_server->notifications_enabled = init_params->enable_notifications;
        }
        else
        {
            battery_server->notifications_enabled = 0;
        }
        
        /* Setup data required for Battery Service to be registered with the GATT Manager */
        registration_params.task = &battery_server->lib_task;
        registration_params.start_handle = start_handle;
        registration_params.end_handle = end_handle;
        
        /* Register with the GATT Manager and verify the result */
        if (GattManagerRegisterServer(&registration_params) == gatt_manager_status_success)
        {
            result = gatt_battery_server_status_success;
        }
        else
        {
            result = gatt_battery_server_status_registration_failed;
        }
    }
    
    return result;
}
