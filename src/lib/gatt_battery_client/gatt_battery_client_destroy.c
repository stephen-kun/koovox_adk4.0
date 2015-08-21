/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <gatt_manager.h>

#include "gatt_battery_client.h"

#include "gatt_battery_client_msg_handler.h"


/****************************************************************************/
gatt_battery_client_status_t GattBatteryClientDestroy(GBASC *battery_client, uint16 cid)
{
    gatt_battery_client_status_t result = gatt_battery_client_status_invalid_parameter;

    /* Check parameters */
    if (battery_client != NULL)
    {
        /* Register with the GATT Manager and verify the result */
        if (GattManagerUnregisterClient(&battery_client->lib_task) == gatt_manager_status_success)
        {
            result = gatt_battery_client_status_success;
        }
        else
        {
            result = gatt_battery_client_status_failed;
        }
        
        /* Clear pending messages */
        MessageFlushTask((Task)&battery_client->lib_task);
    }
    
    return result;
}
