/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <gatt.h>

#include "gatt_link_loss_server.h"
#include "gatt_link_loss_server_access.h"
#include "gatt_link_loss_server_db.h"
#include "gatt_link_loss_server_msg_handler.h"


/****************************************************************************/
gatt_link_loss_server_status GattLinkLossServerInit(Task appTask,
                                                         GLLSS_T *const link_loss_server,
                                                         uint16 start_handle,
                                                         uint16 end_handle)
{
    gatt_link_loss_server_status retval = gatt_link_loss_server_status_invalid_parameter;

    if((appTask != NULL) && (link_loss_server != NULL))
    {
        /*Registration parameters for Link Loss service library to GATT manager  */
        gatt_manager_server_registration_params_t reg_params;
        /* Reset all the service library memory */
        memset(link_loss_server, 0, sizeof(GLLSS_T));
        /*Set up the library task handler for external messages
         * Link loss service library receives gatt manager messages here
         */
        link_loss_server->lib_task.handler = linkLossServerMsgHandler;
        /*Store application message handler as application messages need to be posted here */
        link_loss_server->app_task = appTask;
        /* Set intial alert level to no alert */
        link_loss_server->alert_level = gatt_link_loss_alert_level_no;
        /* Fill in the registration parameters */
        reg_params.start_handle = start_handle;
        reg_params.end_handle = end_handle;
        reg_params.task = &link_loss_server->lib_task;
        /* Try to register this instance of link loss service library to Gatt manager */
        if (GattManagerRegisterServer(&reg_params) == gatt_manager_status_success)
        {
            return gatt_link_loss_server_status_success;
        }
        else
        {
            return gatt_link_loss_server_status_registration_failed;
        }
    }
    return retval;
}

/****************************************************************************/
gatt_link_loss_alert_level GattLinkLossServerGetAlertLevel(const GLLSS_T *const link_loss_server)
{
    gatt_link_loss_alert_level alert_level = gatt_link_loss_alert_level_reserved;

    if (link_loss_server != NULL)
    {
        alert_level = link_loss_server->alert_level;
    }
    
    return alert_level;
}

