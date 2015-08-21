/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <gatt_manager.h>

#include "gatt_device_info_client.h"
#include "gatt_device_info_client_private.h"
#include "gatt_device_info_client_msg_handler.h"

#define INIT_PARAM_INVALID(params) (params->cid == INVALID_CID || params->start_handle==INVALID_GATT_START_HANDLE || params->end_handle == INVALID_GATT_END_HANDLE)

/***************************************************************************
NAME
    resetDeviceInfoHandles

DESCRIPTION
    Initialize all the Device info service characteristic handles to Invalid.
*/
static void resetDeviceInfoHandles( GDISC *const device_info_client)
{
    if(device_info_client != NULL)
    {
        /* Reset the Device information service characteristic handles with Invalid Value */
        device_info_client->manufacturer_name_handle = INVALID_DEVICE_INFO_HANDLE;
        device_info_client->model_number_handle= INVALID_DEVICE_INFO_HANDLE;
        device_info_client->serial_number_handle= INVALID_DEVICE_INFO_HANDLE;
        device_info_client->hardware_revision_handle= INVALID_DEVICE_INFO_HANDLE;
        device_info_client->firmware_revision_handle= INVALID_DEVICE_INFO_HANDLE;
        device_info_client->software_revision_handle= INVALID_DEVICE_INFO_HANDLE;
        device_info_client->system_id_handle= INVALID_DEVICE_INFO_HANDLE;
        device_info_client->ieee_data_list_handle = INVALID_DEVICE_INFO_HANDLE;
        device_info_client->pnp_id_handle= INVALID_DEVICE_INFO_HANDLE;
    }
}

/***************************************************************************
NAME
    deviceInfoClientDiscoverCharacteristics

DESCRIPTION
    start finding out the remote server characteristic handles for Device Info service .
*/
static void deviceInfoDiscoverCharacteristics(const GDISC *const device_info_client,
                                const GATT_DEVICE_INFO_CLIENT_INIT_PARAMS_T *const client_init_params)
{
    /* Make Inernal Message for fidning out characterisitc handles */
    MAKE_DEVICE_INFO_CLIENT_MESSAGE(DEVICE_INFO_CLIENT_INTERNAL_MSG_CONNECT);
    /* Fill in the connection ID */
    message->cid = client_init_params->cid;
    /* Fill In start Handle */
    message->start_handle = client_init_params->start_handle;
    /* Fill in end handle  */
    message->end_handle = client_init_params->end_handle;
    /* Send Connect Request Internal Message */
    MessageSend((Task)&device_info_client->lib_task, DEVICE_INFO_CLIENT_INTERNAL_MSG_CONNECT, message);
}

/****************************************************************************/
gatt_device_info_client_status_t GattDeviceInfoClientInit(Task app_task, 
                                                GDISC *const device_info_client,  
                                                const GATT_DEVICE_INFO_CLIENT_INIT_PARAMS_T *const client_init_params)
{
    gatt_device_info_client_status_t result = gatt_device_info_client_status_registration_failed;
    gatt_manager_client_registration_params_t registration_params;

    /* Check parameters */
    if((app_task == NULL) || (device_info_client == NULL) || INIT_PARAM_INVALID(client_init_params))
    {
        return gatt_device_info_client_status_invalid_parameter; 
    }
    /* Set memory contents to all zeros */
    memset(device_info_client, 0, sizeof(GDISC));

    /* Set up library handler for external messages */
    device_info_client->lib_task.handler = deviceInfoClientMsgHandler;
    /* Keep track on application task as all the notifications and indication need to be sent here */
    device_info_client->app_task = app_task;
    /* intialize device inforamation service characteristic handles to invalid value */
    resetDeviceInfoHandles(device_info_client);

    /* Setup data required for Device Information Service to be registered with the GATT Manager */
    registration_params.client_task = &device_info_client->lib_task;
    registration_params.cid = client_init_params->cid;
    registration_params.start_handle = client_init_params->start_handle;
    registration_params.end_handle = client_init_params->end_handle;

    /* Register with the GATT Manager and verify the result */
    if (GattManagerRegisterClient(&registration_params) == gatt_manager_status_success)
    {
        /* Start finding out the characteristics handles for Device Information service */
        deviceInfoDiscoverCharacteristics(device_info_client, client_init_params);
        result = gatt_device_info_client_status_initiated;
    }
    return result;
}
/****************************************************************************/
gatt_device_info_client_status_t GattDeviceInfoClientReadCharRequest( GDISC *device_info_client,
                                                gatt_device_info_type_t device_info_type)
{
    gatt_device_info_client_status_t retval = gatt_device_info_client_status_not_supported;
    uint16 device_info_char_handle = INVALID_DEVICE_INFO_HANDLE;

    /* Validate the input parameters */
    if((device_info_client == NULL) || (device_info_type >= gatt_device_info_client_invalid_char))
    {
        return gatt_device_info_client_status_invalid_parameter;
    }

    device_info_char_handle = getDeviceInfoCharHandle(device_info_client, device_info_type);
    
    if(device_info_char_handle != INVALID_DEVICE_INFO_HANDLE)
    {
        /* Make Internal message for read characteristic value reqquest */
        MAKE_DEVICE_INFO_CLIENT_MESSAGE(DEVICE_INFO_CLIENT_INTERNAL_MSG_READ_CHAR);
        /* Fill In Requested device info type */
        message->device_info_type = device_info_type;
        /* Fill In Requested device info char handle */
        message->device_info_char_handle = device_info_char_handle;
        
        /* Send Internal message for read device info */
        MessageSend((Task)&device_info_client->lib_task, DEVICE_INFO_CLIENT_INTERNAL_MSG_READ_CHAR, message);
        /* Return Initiated */
        return  gatt_device_info_client_status_initiated;
    }
    return retval;
}

/****************************************************************************/
gatt_device_info_client_status_t GattDeviceInfoClientDestroy(GDISC *device_info_client)
{
    gatt_device_info_client_status_t result = gatt_device_info_client_status_invalid_parameter;

    /* Check parameters */
    if (device_info_client != NULL)
    {
        /* Register with the GATT Manager and verify the result */
        if (GattManagerUnregisterClient(&device_info_client->lib_task) == gatt_manager_status_success)
        {
            result = gatt_device_info_client_status_success;
        }
        else
        {
            result = gatt_device_info_client_status_failed;
        }
        
        /* Clear pending messages */
        MessageFlushTask((Task)&device_info_client->lib_task);
    }
    
    return result;
}


