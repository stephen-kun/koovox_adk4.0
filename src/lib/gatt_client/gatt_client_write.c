/* Copyright (C) CSR plc, 2015 */
/* Part of ADK 4.0 */

#include "gatt_client_write.h"

#include "gatt_client_debug.h"
#include "gatt_client_init.h"

#include <gatt_manager.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define GATT_CHARACTERISTIC_INDICATION_VALUE 0x0002


/****************************************************************************/
void writeGattClientConfigValue(GGATTC *gatt_client, uint16 handle)
{
    uint8 value[2];
    
    value[0] = GATT_CHARACTERISTIC_INDICATION_VALUE;
    value[1] = 0;
    
    GATT_CLIENT_DEBUG_INFO(("GATTC: Enable service changed indications handle=[0x%x]\n", handle));
    
    GattManagerWriteCharacteristicValue((Task)&gatt_client->lib_task, handle, sizeof(value), value);
}


/****************************************************************************/
void handleWriteValueResp(GGATTC *gatt_client, const GATT_MANAGER_WRITE_CHARACTERISTIC_VALUE_CFM_T *cfm)
{
    GATT_CLIENT_DEBUG_INFO(("GATTC: Enable indications status=[%u] cid=[0x%x]\n", 
                            cfm->status,
                            cfm->cid));
                            
    if (cfm->status == gatt_status_success)
    {
        gattClientSendInitSuccessCfm(gatt_client, gatt_client->service_changed_handle);
    }
    else
    {
        gattClientSendInitDiscoveryErrorCfm(gatt_client, gatt_client->service_changed_handle);
    }
}
