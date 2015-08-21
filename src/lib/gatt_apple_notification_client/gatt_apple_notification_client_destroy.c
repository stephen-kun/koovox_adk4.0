/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <gatt_manager.h>

#include "gatt_apple_notification_client.h"

#include "gatt_apple_notification_client_msg_handler.h"


/****************************************************************************/
gatt_ancs_status_t GattAncsDestroy(GANCS *ancs)
{
    gatt_ancs_status_t result = gatt_ancs_status_invalid_parameter;
    /* Check parameters */
    if (ancs != NULL)
    {
        /* Register with the GATT Manager and verify the result */
        if (GattManagerUnregisterClient(&ancs->lib_task) == gatt_manager_status_success)
        {
            result = gatt_ancs_status_success;
        }
        else
        {
            result = gatt_ancs_status_failed;
        }
        
        /* Clear pending messages */
        MessageFlushTask((Task)&ancs->lib_task);
    }

    return result;
}

