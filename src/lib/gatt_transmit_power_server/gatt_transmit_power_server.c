/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <gatt.h>

#include "gatt_transmit_power_server.h"
#include "gatt_transmit_power_server_db.h"
#include "gatt_transmit_power_server_msg_handler.h"
#include "gatt_transmit_power_server_private.h"


/****************************************************************************/
gatt_tps_status GattTransmitPowerServerInitTask(Task appTask ,
                                GTPSS *const tps,
                                uint16 start_handle,
                                uint16 end_handle)
{
    if((appTask!= NULL) && (tps != NULL))
    {
        /*Registartion parameters for transmit power service library to GATT manager  */
        gatt_manager_server_registration_params_t reg_params;
        
        /* Reset all the server service library memory */
        memset(tps, 0, sizeof(GTPSS));

        /*Set up the library task handler for external messages
         * power transmit server service library receives gatt manager messages here
         */
        tps->lib_task.handler = transmit_power_server_ext_msg_handler;
        /*Store application message handler as application messages need to be posted here */
        
        tps->app_task = appTask;
        
        /* Fill in the registration parameters */
        reg_params.start_handle = start_handle;
        reg_params.end_handle   = end_handle;
        reg_params.task = &tps->lib_task;

        /* Try to register this instance of transmit power service library to Gatt manager */
        if (GattManagerRegisterServer(&reg_params) == gatt_manager_status_success)
        {
            return gatt_tps_status_success;
        }
        else
        {
            return gatt_tps_status_registration_failed;
        }
    }

    return gatt_tps_status_invalid_parameter;
}


