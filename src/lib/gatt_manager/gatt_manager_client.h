/****************************************************************************
Copyright Cambridge Silicon Radio Limited 2014 - 2015.
Part of ADK 4.0
*/

#ifndef GATTMANAGER_CLIENT_H_
#define GATTMANAGER_CLIENT_H_

#include <library.h>
#include <csrtypes.h>
#include <gatt.h>

#include "gatt_manager_internal.h"

/* Called to handle a queued connect request
 * */
void GattManagerConnectToRemoteServerInternal(GATT_MANAGER_INTERNAL_MSG_CONNECT_TO_REMOTE_SERVER_T *params);

/* Forward GATT_CONNECT_CFM from the remote server to the application task.
 * */
void gattManagerClientRemoteServerConnected(GATT_CONNECT_CFM_T * cfm);

/* Forward GATT_NOTIFICATION_IND from the remote server to the client.
 * If a client is not found, route it to the application task.
 * */
void gattManagerClientRemoteServerNotification(GATT_NOTIFICATION_IND_T * ind);

/* Forward GATT_INDICATION_IND from the remote server to the client.
 * If a client is not found, route it to the application task.
 * */
void gattManagerClientRemoteServerIndication(GATT_INDICATION_IND_T * ind);

/* Forward GATT_DISCOVER_ALL_CHARACTERISTICS_CFM from the remote server to the client.
 * If a client is not found, discard the message.
 * */
void gattManagerClientDiscoverAllCharacteristicsConfirm(GATT_DISCOVER_ALL_CHARACTERISTICS_CFM_T * cfm);

/* Forward GATT_DISCOVER_ALL_CHARACTERISTIC_DESCRIPTORS_CFM from the remote server to the client.
 * If a client is not found, discard the message.
 * */
void gattManagerClientDiscoverAllCharacteristicsDescriptorsConfirm(GATT_DISCOVER_ALL_CHARACTERISTIC_DESCRIPTORS_CFM_T * cfm);

/* Forward GATT_READ_CHARACTERISTIC_VALUE_CFM from the remote server to the client.
 * If a client is not found, discard the message.
 * */
void gattManagerClientReadCharacteristicValueConfirm(GATT_READ_CHARACTERISTIC_VALUE_CFM_T * cfm);

/* Forward GATT_READ_USING_CHARACTERISTIC_UUID_CFM from the remote server to the client.
 * If a client is not found, discard the message.
 * */
void gattManagerClientReadUsingCharacteristicUuidConfirm(GATT_READ_USING_CHARACTERISTIC_UUID_CFM_T * cfm);

/* Forward GATT_READ_LONG_CHARACTERISTIC_VALUE_CFM from the remote server to the client.
 * If a client is not found, discard the message.
 * */
void gattManagerClientReadLongCharacteristicValueConfirm(GATT_READ_LONG_CHARACTERISTIC_VALUE_CFM_T * cfm);

/* Forward GATT_WRITE_WITHOUT_RESPONSE_CFM from the remote server to the client.
 * If a client is not found, discard the message.
 * */
void gattManagerClientWriteWithoutResponseConfirm(GATT_WRITE_WITHOUT_RESPONSE_CFM_T * cfm);

/* Forward GATT_SIGNED_WRITE_WITHOUT_RESPONSE_CFM from the remote server to the client.
 * If a client is not found, discard the message.
 * */
void gattManagerClientSignedWriteWithoutResponseConfirm(GATT_SIGNED_WRITE_WITHOUT_RESPONSE_CFM_T * cfm);

/* Forward GATT_WRITE_CHARACTERISTIC_VALUE_CFM from the remote server to the client.
 * If a client is not found, discard the message.
 * */
void gattManagerClientWriteCharacteristicValueConfirm(GATT_WRITE_CHARACTERISTIC_VALUE_CFM_T * cfm);

/* Forward GATT_WRITE_LONG_CHARACTERISTIC_VALUE_CFM from the remote server to the client.
 * If a client is not found, discard the message.
 * */
void gattManagerClientWriteLongCharacteristicValueConfirm(GATT_WRITE_LONG_CHARACTERISTIC_VALUE_CFM_T * cfm);

/* Forward GATT_RELIABLE_WRITE_PREPARE_CFM from the remote server to the client.
 * If a client is not found, discard the message.
 * */
void gattManagerClientReliableWritePrepareConfirm(GATT_RELIABLE_WRITE_PREPARE_CFM_T * cfm);

/* Forward GATT_RELIABLE_WRITE_EXECUTE_CFM from the remote server to the client.
 * If a client is not found, discard the message.
 * */
void gattManagerClientReliableWriteExecuteConfirm(GATT_RELIABLE_WRITE_EXECUTE_CFM_T * cfm);

#endif
