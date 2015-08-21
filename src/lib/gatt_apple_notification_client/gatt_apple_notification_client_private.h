/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#ifndef GATT_APPLE_NOTIFICATION_CLIENT_PRIVATE_H_
#define GATT_APPLE_NOTIFICATION_CLIENT_PRIVATE_H_

#include <csrtypes.h>
#include <message.h>
#include <panic.h>
#include <stdlib.h>

/* Debug print and panic or just panic depending on build */
#include "gatt_apple_notification_client_debug.h"

#define GATT_APPLE_NOTIFICATION_PANIC(x) {GATT_APPLE_NOTIFICAITON_DEBUG_INFO(x); Panic();}

/* GATT Apple Notification Characteristic Identification */
#define GATT_APPLE_NOTIFICATION_NS                                     (0x01)
#define GATT_APPLE_NOTIFICATION_DS                                     (0x02)
#define GATT_APPLE_NOTIFICATION_CP                                     (0x03)

#define GATT_APPLE_NOTIFICATION_CHARACTERISTIC_MASK   (0x03)
#define GATT_APPLE_NOTIFICATION_CHAR_IDENTIFIER       (0x02)
#define GATT_APPLE_NOTIFICATION_MAX_CHAR              (0x03)
/*!
* Apple Notification Notification Source UUID as per Version 1.1
*/
 #define APPLE_NOTIFICATION_NS_UUID   (0x9FBF120D630142D98C5825E699A21DBD)

 /*!
* Apple Notification Control Point UUID as per Version 1.1
*/
 #define APPLE_NOTIFICATION_CP_UUID   (0x69D1D8F345E149A898219BBDFDAAD9D9)

 /*!
* Apple Notification Data Source UUID as per Version 1.1
*/
 #define APPLE_NOTIFICATION_DS_UUID   (0x22EAC6E924D64BB5BE44B36ACE7C7BFB)

 /*!
* Invalid Handle Value
*/
 #define APPLE_NOTIFICATION_INVALID_HANDLE (0xFFFF)

 /*!
 * Macro to check valid handle
 */
#define CHECK_VALID_HANDLE(handle) (handle != APPLE_NOTIFICATION_INVALID_HANDLE)

 /*!
 * Macro to check the UUID of ANCS 
 */
 #define CHECK_ANCS_NS_UUID(char_cfm) (char_cfm->uuid[3] == 0x99A21DBD) && \
                    (char_cfm->uuid[2] == 0x8C5825E6) && \
                    (char_cfm->uuid[1] == 0x630142D9) && \
                    (char_cfm->uuid[0] == 0x9FBF120D)

 #define CHECK_ANCS_DS_UUID(char_cfm) (char_cfm->uuid[3] == 0xCE7C7BFB) && \
                    (char_cfm->uuid[2] == 0xBE44B36A) && \
                    (char_cfm->uuid[1] == 0x24D64BB5) && \
                    (char_cfm->uuid[0] == 0x22EAC6E9)

 #define CHECK_ANCS_CP_UUID(char_cfm) (char_cfm->uuid[3] == 0xFDAAD9D9) && \
                    (char_cfm->uuid[2] == 0x98219BBD) && \
                    (char_cfm->uuid[1] == 0x45E149A8) && \
                    (char_cfm->uuid[0] == 0x69D1D8F3)

 /*!
 * Macro to check if category is set
 */
#define CHECK_CATEGORY(notification_mask, bit_position) \
                    (notification_mask & (1<< bit_position))

/* Macros for creating messages */
#define MAKE_APPLE_NOTIFICATION_MESSAGE(TYPE) MESSAGE_MAKE(message,TYPE##_T)
#define MAKE_APPLE_NOTIFICATION_MESSAGE_WITH_LEN(TYPE, LEN) TYPE##_T *message = (TYPE##_T *) PanicUnlessMalloc(sizeof(TYPE##_T) + LEN - sizeof(uint8))

#define STANDARD_SIZE_OF_ANCS_CP_WR sizeof(uint8) + sizeof(uint32)

/*
A Get Notification Attributes command contains the following information:
 CommandID:         Should be set to 0 (CommandIDGetNotificationAttributes).
 NotificationUID:   The 32-bit numerical value representing the UID of the iOS notification for which the client wants information.
 AttributeIDs:      A list of attributes that the NC wants to retrieve. Some attributes may need to be followed by a 16-bit length parameter that specifies the maximum number of bytes of the attribute the NC wants to retrieve.
*/
#define CALCULATE_SIZEOF_GET_NOTIFICATION_ATTRIBUTES(size_attribute_ids) STANDARD_SIZE_OF_ANCS_CP_WR + (sizeof(uint8) * size_attribute_ids)

/*
A Get App Attributes command contains the following information:
 CommandID:         Should be set to 1 (CommandIDGetAppAttributes).
 AppIdentifier:     The string identifier of the app the client wants information about. This string must be NULL-terminated.
 AttributeIDs:      A list of attributes the NC wants to retrieve.
*/
#define CALCULATE_SIZEOF_GET_APP_ATTRIBUTES(size_app_identifier, size_attribute_ids) sizeof(uint8) + (sizeof(uint8) * size_app_identifier) + (sizeof(uint8) * size_attribute_ids)

/*
A Perform Notification Action command contains the following information:
 CommandID          Should be set to 2 (CommandIDPerformNotificationAction).
 NotificationUID    A 32-bit numerical value representing the UID of the iOS notification on which the client wants to perform an action.
 ActionID:          The desired action the NC wants to be performed on the iOS notification.
*/
#define CALCULATE_SIZEOF_PERFORM_NOTIFICATION_ACTION STANDARD_SIZE_OF_ANCS_CP_WR + sizeof(uint8)

/* Enum for apple notification library internal message. */
typedef enum __ancs_internal_msg_t
{
    ANCS_INTERNAL_MSG_SET_NS_NOTIFICATION,
    ANCS_INTERNAL_MSG_SET_DS_NOTIFICATION,
    ANCS_INTERNAL_MSG_WRITE_CP_CHARACTERISTIC
} ancs_internal_msg_t;

/* Enum for apple notification pending command type. Only insert new entries at the end. */
typedef enum __ancs_pending_cmd_t
{
    ancs_pending_none = 0,
    ancs_pending_discover_all_characteristics,
    ancs_pending_discover_all_characteristic_descriptors,
    ancs_pending_write_ns_cconfig,
    ancs_pending_write_ds_cconfig,
    ancs_pending_set_ns_notify_enable,
    ancs_pending_set_ns_notify_disable,
    ancs_pending_set_ds_notify_enable,
    ancs_pending_set_ds_notify_disable,
    ancs_pending_write_cp_attr,
    ancs_pending_write_cp_app_attr,
    ancs_pending_max
} ancs_pending_cmd_t;

typedef struct
{
    bool notifications_enable;
    uint16 notifications_mask;
} ANCS_INTERNAL_MSG_SET_NS_NOTIFICATION_T;

typedef struct
{
    bool notifications_enable;
} ANCS_INTERNAL_MSG_SET_DS_NOTIFICATION_T;

/*
    Internal message used to write data to the ANCS Control Point characteristic
*/
typedef struct
{
    ancs_pending_cmd_t pending_cmd;
    uint16      size_command_data;
    uint8       command_data[1];
} ANCS_INTERNAL_MSG_WRITE_CP_CHARACTERISTIC_T;




#endif /* GATT_APPLE_NOTIFICATION_CLIENT_PRIVATE_H_ */
