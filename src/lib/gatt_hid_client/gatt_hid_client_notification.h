/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#ifndef GATT_HID_CLIENT_NOTIFICATION_H_
#define GATT_HID_CLIENT_NOTIFICATION_H_

#include <csrtypes.h>

#include "gatt_manager.h"
#include "gatt_hid_client.h"
#include "gatt_hid_client_private.h"

/***************************************************************************
NAME
    hid_client_notification_reg_request

DESCRIPTION
    Enable/Disable Notification
*/
void hid_client_notification_reg_request(GHIDC_T *const hid_client ,
        HID_CLIENT_INTERNAL_HANLDE_NOTIFICTION_REQ_T*msg);

/***************************************************************************
NAME
    hid_client_notification_reg_request_ccdhandle

DESCRIPTION
    Enable/Disable Notification for a particular ccd handle
*/
void hid_client_notification_reg_request_ccdhandle(GHIDC_T *const hid_client,
        HID_CLIENT_INTERNAL_SET_NOTIFICATION_CCDHANDLE_REQ_T*msg);
/***************************************************************************
NAME
    handle_hid_client_notification_ind

DESCRIPTION
  Utility function for handling notifitcation from HID service 
*/
void handle_hid_client_notification_ind(GHIDC_T *const hid_client,
    GATT_MANAGER_REMOTE_SERVER_NOTIFICATION_IND_T*ind);


/***************************************************************************
NAME
    handle_hid_client_notification_reg_cfm

DESCRIPTION
    Utility function to handle notification registration cfm
*/
void handle_hid_client_notification_reg_cfm(GHIDC_T *const hid_client,
    GATT_MANAGER_WRITE_CHARACTERISTIC_VALUE_CFM_T* cfm);



#endif /* GATT_HID_CLIENT_NOTIFICATION_H_ */

