/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <gatt.h>

#include "gatt_imm_alert_server.h"
#include "gatt_imm_alert_server_db.h"
#include "gatt_imm_alert_server_msg_handler.h"
#include "gatt_imm_alert_server_private.h"


/****************************************************************************/

gatt_imm_alert_server_status GattImmAlertServiceServerInit(Task appTask ,
                                GIASS_T *const imm_alert_server,
                                uint16 start_handle,
                                uint16 end_handle)
{
    gatt_imm_alert_server_status retval = gatt_imm_alert_server_status_invalid_parameter;

    if((appTask != NULL) && (imm_alert_server != NULL))
    {
        /*Registration parameters for immediate alert service library to GATT manager  */
        gatt_manager_server_registration_params_t reg_params;
        /* Reset all the service library memory */
        memset(imm_alert_server, 0, sizeof(GIASS_T));
        /*Set up the library task handler for external messages
         * immediate alert service library receives gatt manager messages here
         */
        imm_alert_server->lib_task.handler = imm_alert_server_ext_msg_handler;
        /*Store application message handler as application messages need to be posted here */
        imm_alert_server->app_task = appTask;
        /* Fill in the registration parameters */
        reg_params.start_handle = start_handle;
        reg_params.end_handle   = end_handle;
        reg_params.task = &imm_alert_server->lib_task;
        /* Try to register this instance of immediate alert service library to Gatt manager */
        if (GattManagerRegisterServer(&reg_params) == gatt_manager_status_success)
        {
            /* Mark Lib init is done */
           return gatt_imm_alert_server_status_success;
        }
        else
        {
            return gatt_imm_alert_server_status_registration_failed;
        }
    }
    return retval;
}



