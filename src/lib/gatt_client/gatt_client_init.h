/* Copyright (C) CSR plc, 2015 */
/* Part of ADK 4.0 */

#ifndef GATT_CLIENT_INIT_H_
#define GATT_CLIENT_INIT_H_


#include "gatt_client.h"


/***************************************************************************
NAME
    gattClientSendInitSuccessCfm
    
DESCRIPTION
    Send a success GATT_CLIENT_INIT_CFM message to the registered client task.
*/
void gattClientSendInitSuccessCfm(GGATTC *gatt_client, uint16 service_changed_handle);


/***************************************************************************
NAME
    gattClientSendInitDiscoveryErrorCfm
    
DESCRIPTION
    Send a discovery error GATT_CLIENT_INIT_CFM message to the registered client task.
*/
void gattClientSendInitDiscoveryErrorCfm(GGATTC *gatt_client, uint16 service_changed_handle);


#endif
