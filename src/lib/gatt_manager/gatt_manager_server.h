/****************************************************************************
Copyright Cambridge Silicon Radio Limited 2014 - 2015.
Part of ADK 4.0
*/

#ifndef GATTMANAGER_SERVER_H_
#define GATTMANAGER_SERVER_H_

#include <library.h>
#include <csrtypes.h>
#include <gatt.h>

#include "gatt_manager_internal.h"

/* Called to handle a queued connect request
 * */
void gattManagerWaitForRemoteClientInternal(GATT_MANAGER_INTERNAL_MSG_WAIT_FOR_REMOTE_CLIENT_T *params);

/* Called when GATT has started advertising
 * */
void gattManagerServerAdvertising(uint16 cid);

/* Connect indication received and should be passed on to the application
 * */
void gattManagerServerConnectInd(GATT_CONNECT_IND_T * ind);

/* Handle a remote client connecting to the server
 * */
void gattManagerServerRemoteClientConnected(GATT_CONNECT_CFM_T * cfm);

/* Handle Access indication from remote client
 * */
void gattManagerServerAccessInd(GATT_ACCESS_IND_T * ind);

/* Handle notification confirm
 * */
void gattManagerServerNotificationCfm(GATT_NOTIFICATION_CFM_T * cfm);

/* Handle indication confirm from remote device
 * */
void gattManagerServerIndicationCfm(GATT_INDICATION_CFM_T * cfm);

#endif
