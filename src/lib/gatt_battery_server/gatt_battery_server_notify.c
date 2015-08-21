/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include <stdlib.h>

#include <gatt_manager.h>

#include "gatt_battery_server.h"

#include "gatt_battery_server_debug.h"
#include "gatt_battery_server_private.h"
#include "gatt_battery_server_db.h"


/****************************************************************************/
gatt_battery_server_status_t GattBatteryServerSendLevelNotification(const GBASS *battery_server, uint16 number_cids, const uint16 *cids, uint8 battery_level)
{
    gatt_battery_server_status_t result = gatt_battery_server_status_invalid_parameter;
    uint16 index = 0;

    if ((battery_server != NULL) && (battery_level <= 100) && number_cids)
    {
        if (battery_server->notifications_enabled)
        {
            result = gatt_battery_server_status_success;

            for (index = 0; index < number_cids; index++)
            {
                if (cids[index] == 0)
                {
                    /* CID must be non-zero */
                    result = gatt_battery_server_status_invalid_parameter;
                }
                else
                {
                    /* Send notification to GATT Manager */
                    GattManagerRemoteClientNotify((Task)&battery_server->lib_task, cids[index], HANDLE_BATTERY_LEVEL, 1, &battery_level);
                }
            }
            
        }
        else
        {
            result = gatt_battery_server_status_not_allowed;
        }
    }

    return result;
}

