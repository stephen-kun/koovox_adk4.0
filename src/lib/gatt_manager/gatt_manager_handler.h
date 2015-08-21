/*******************************************************************************
Copyright Cambridge Silicon Radio Limited 2014 - 2015.
Part of ADK 4.0
*/

#ifndef GATTMANAGER_HANDLER_H_
#define GATTMANAGER_HANDLER_H_

#include <library.h>
#include <csrtypes.h>
#include <gatt.h>

#include "gatt_manager.h"
#include "gatt_manager_internal.h"

/* Send GATT_MANAGER_REGISTER_WITH_GATT_CFM message. */
void registerWithGattCfm(gatt_manager_status_t status);

/* GATT Manager message handler. */
void gattManagerMessageHandler(Task task, MessageId id, Message payload);

#endif /*GATTMANAGER_HANDLER_H_*/
