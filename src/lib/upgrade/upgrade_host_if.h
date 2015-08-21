/****************************************************************************
Copyright Cambridge Silicon Radio Limited 2004 - 2015.
Part of ADK 4.0

FILE NAME
    upgrade_host_if.h
    
DESCRIPTION

*/
#ifndef UPGRADE_HOST_IF_H_
#define UPGRADE_HOST_IF_H_

#include <message.h>
#include "upgrade.h"

void UpgradeHostIFClientConnect(Task clientTask);
void UpgradeHostIFClientSendData(uint8 *data, uint16 dataSize);

void UpgradeHostIFTransportConnect(Task transportTask);
void UpgradeHostIFProcessDataRequest(uint8 *data, uint16 dataSize);
void UpgradeHostIFTransportDisconnect(void);

#endif /* UPGRADE_HOST_IF_H_ */
