/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <gatt_manager.h>

#include "gatt_battery_server.h"

#include "gatt_battery_server_access.h"
#include "gatt_battery_server_private.h"


/****************************************************************************/
gatt_battery_server_status_t GattBatteryServerReadLevelResponse(const GBASS *battery_server, uint16 cid, uint8 battery_level)
{
    gatt_status_t status = gatt_status_failure;

    if (battery_server == NULL)
    {
        return gatt_battery_server_status_invalid_parameter;
    }

    if (battery_level <= 100)
    {
        status = gatt_status_success;
    }
    
    sendBatteryLevelAccessRsp(battery_server, cid, battery_level, status);

    return gatt_battery_server_status_success;
}

/****************************************************************************/
gatt_battery_server_status_t GattBatteryServerReadClientConfigResponse(const GBASS *battery_server, uint16 cid, uint16 client_config)
{
    gatt_battery_server_status_t result = gatt_battery_server_status_invalid_parameter;

    if (battery_server != NULL)
    {
        sendBatteryConfigAccessRsp(battery_server, cid, client_config);
        result = gatt_battery_server_status_success;
    }
    
    return result;
}

/****************************************************************************/
gatt_battery_server_status_t GattBatteryServerReadPresentationResponse(const GBASS *battery_server, uint16 cid, uint8 name_space, uint16 description)
{
    gatt_battery_server_status_t result = gatt_battery_server_status_invalid_parameter;

    if (battery_server != NULL)
    {
        sendBatteryPresentationAccessRsp(battery_server, cid, name_space, description);
        result = gatt_battery_server_status_success;
    }
    
    return result;
}
