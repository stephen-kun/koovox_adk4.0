/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include <message.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gatt.h"

#include "gatt_hid_client_write.h"

#include "gatt_hid_client.h"
#include "gatt_hid_client_utils.h"
#include "gatt_hid_client_private.h"
#include "gatt_hid_client_debug.h"



/*These are defines as per LE HID spec*/
#define HID_LE_SUSPEND       0x00
#define HID_LE_EXIT_SUSPEND  0x01
#define HID_LE_SET_BOOT      0x00
#define HID_LE_SET_REPORT    0x01


/***************************************************************************/
/*                                      Internal Helper Functions                                                            */
/***************************************************************************/

/***************************************************************************
NAME
    hid_client_write_without_resp_one_byte

DESCRIPTION
   Utility function to write without response a single byte
*/
static void hid_client_write_without_resp_one_byte(GHIDC_T *const hid_client,
                uint16 handle,
                uint8 value)
{
    uint8 databuff[1];

    databuff[0] = value;

    GattManagerWriteWithoutResponse((Task)&hid_client->lib_task,
                                                handle,
                                                sizeof(databuff),
                                                databuff);
}


/***************************************************************************
NAME
    hid_client_write_set_protocol_cfm

DESCRIPTION
   Utility function to send set protocol confirmation to resgistered application task
*/
static void hid_client_write_set_protocol_cfm(GHIDC_T *const hid_client,
    const GATT_MANAGER_WRITE_WITHOUT_RESPONSE_CFM_T* cfm)
{
    /* Convert GATT lib status to HID lib status */
    gatt_hid_client_status hid_client_status = hid_client_convert_status(cfm->status);

    MAKE_HID_CLIENT_MESSAGE(GATT_HID_CLIENT_SET_PROTOCOL_CFM);
    memset(message, 0, sizeof(GATT_HID_CLIENT_SET_PROTOCOL_CFM_T));
    /* Fill in confirmation message parameters */
    message->hid_client = hid_client;
    message->status = hid_client_status;
    message->cid = cfm->cid;

    MessageSend(hid_client->app_task, GATT_HID_CLIENT_SET_PROTOCOL_CFM, message);

    CLEAR_PENDING_FLAG(hid_client->pending_request);
}

/***************************************************************************
NAME
    hid_client_write_set_control_point_cfm

DESCRIPTION
   Utility function to send set control point request confirmation to resgistered application task
*/
static void hid_client_write_set_control_point_cfm(GHIDC_T *const hid_client,
                const GATT_MANAGER_WRITE_WITHOUT_RESPONSE_CFM_T* cfm)
{
    /* Convert GATT lib status to HID lib status */
    gatt_hid_client_status hid_client_status = hid_client_convert_status(cfm->status);

    MAKE_HID_CLIENT_MESSAGE(GATT_HID_CLIENT_CONTROL_REQ_CFM);
   /* Fill in confirmation message parameters */
    memset(message, 0, sizeof(GATT_HID_CLIENT_CONTROL_REQ_CFM_T));
    message->hid_client = hid_client;
    message->status = hid_client_status;
    message->cid = cfm->cid;

    MessageSend(hid_client->app_task, GATT_HID_CLIENT_CONTROL_REQ_CFM, message);

    CLEAR_PENDING_FLAG(hid_client->pending_request);
}


/***************************************************************************
NAME
    hid_client_write_set_report_cfm

DESCRIPTION
   Utility function to send set set report confirmation to resgistered application task
*/
static void  hid_client_write_set_report_cfm(GHIDC_T *const hid_client,
    uint16 handle,
    uint16 cid,
    gatt_status_t status)
{
    /* Convert GATT lib status to HID lib status */
    gatt_hid_client_status hid_client_status = hid_client_convert_status(status);
    uint16 report_id = 0;
    MAKE_HID_CLIENT_MESSAGE(GATT_HID_CLIENT_SET_REPORT_CFM);
    memset(message, 0, sizeof(GATT_HID_CLIENT_SET_REPORT_CFM_T));
    /* Fill in confirmation message parameters */
    message->hid_client = hid_client;
    message->status = hid_client_status;
    message->cid = cid;
    /* Get the report ID and fill in confirmation message */
    if(hid_client_get_report_id_from_handle(hid_client,handle,&report_id))
    {
        message->report_id = report_id;
    }  

    MessageSend(hid_client->app_task, GATT_HID_CLIENT_SET_REPORT_CFM, message);

    CLEAR_PENDING_FLAG(hid_client->pending_request);
}
/***************************************************************************
NAME
    hid_client_write_boot_report_cfm

DESCRIPTION
   Utility function to send write boot  report confirmation to resgistered application task
*/
static void hid_client_write_boot_report_cfm(GHIDC_T *const hid_client,
    uint16 cid,
    gatt_status_t status)
{
    /* Convert GATT lib status to HID lib status */
    gatt_hid_client_status hid_client_status = hid_client_convert_status(status);
    MAKE_HID_CLIENT_MESSAGE(GATT_HID_CLIENT_WRITE_BOOT_REPORT_CFM);
    memset(message, 0, sizeof(GATT_HID_CLIENT_WRITE_BOOT_REPORT_CFM_T));
    /* Fill in confirmation message parameters */
    message->hid_client = hid_client;
    message->status = hid_client_status;
    message->cid = cid;

    MessageSend(hid_client->app_task, GATT_HID_CLIENT_WRITE_BOOT_REPORT_CFM, message);

    CLEAR_PENDING_FLAG(hid_client->pending_request);
}
/****************************************************************************/
/*     Interfaces within HID client lib, Interface to hadle write response confirmation from msg handler */
/****************************************************************************/

/****************************************************************************/
void handle_hid_client_write_without_response_cfm(GHIDC_T *const hid_client,
                const GATT_MANAGER_WRITE_WITHOUT_RESPONSE_CFM_T* write_cfm)
{
    /* Find out the pending request and invoke the reponse handlers */
   switch(hid_client->pending_request)
   {
        case hid_client_write_pending_set_report_protocol:
        case hid_client_write_pending_set_boot_protocol:
        {
            hid_client_write_set_protocol_cfm(hid_client,write_cfm);
        }
        break;
        
        case hid_client_write_pending_set_control:
        {
            hid_client_write_set_control_point_cfm(hid_client,write_cfm);
        }
        break;
        /* For feature and Input reports */
        case hid_client_write_pending_set_report:
        {
            hid_client_write_set_report_cfm(hid_client,write_cfm->handle,write_cfm->cid,write_cfm->status);
        }
        break; 
        /* For boot input reports*/
        case hid_client_write_pending_boot_report:     
        {
            hid_client_write_boot_report_cfm(hid_client,write_cfm->cid,write_cfm->status);
        }
        break;
        
        default:
        /* Nothing pending, Ignore */
         break;
   }
}

/****************************************************************************/
void handle_hid_client_write_char_value_cfm(GHIDC_T *const  hid_client,
                const GATT_MANAGER_WRITE_CHARACTERISTIC_VALUE_CFM_T*write_val_cfm)
{
    /* Find out the pending request and invoke the reponse handlers */
   switch(hid_client->pending_request)
   {
        /* For OutPut report */
        case hid_client_write_pending_set_report:
        {
            hid_client_write_set_report_cfm(hid_client,write_val_cfm->handle,write_val_cfm->cid,write_val_cfm->status);
        }
        break;
        /* For KB boot out put report */
        case hid_client_write_pending_boot_report:
        {
            hid_client_write_boot_report_cfm(hid_client,write_val_cfm->cid,write_val_cfm->status);
        }
        break;
        
        default:
        /* Nothing pending, Ignore */
        break;
   }
}
/****************************************************************************/
/*     Interfaces within HID client lib, Interface to Hid client message Handler for writerequest            */
/****************************************************************************/

/****************************************************************************/
void  hid_client_write_set_boot_protocol(GHIDC_T *const hid_client)
{
    if(VALIDATE_HID_CLIENT(hid_client))
    {
      hid_client_write_without_resp_one_byte(hid_client,hid_client->protocol_handle,HID_LE_SET_BOOT);
      SET_PENDING_FLAG(hid_client_write_pending_set_boot_protocol,hid_client->pending_request);
    }
}

/****************************************************************************/
void  hid_client_write_set_report_protocol(GHIDC_T *const hid_client)
{
    if(VALIDATE_HID_CLIENT(hid_client))
    {
      hid_client_write_without_resp_one_byte(hid_client,hid_client->protocol_handle,HID_LE_SET_REPORT);
      SET_PENDING_FLAG(hid_client_write_pending_set_report_protocol,hid_client->pending_request);
    }
}

/****************************************************************************/
void hid_client_write_set_control_point(GHIDC_T *const hid_client,
    HID_CLIENT_INTERNAL_SET_CTRL_POINT_T* ctrl)
{
    if(VALIDATE_HID_CLIENT(hid_client))
    {
        /* Check control point value and set it accordingly */
        if(ctrl->ctrl_type == HID_LE_SUSPEND)
        {
            hid_client_write_without_resp_one_byte(hid_client,hid_client->control_handle,HID_LE_SUSPEND);
        }
        else if(ctrl->ctrl_type == HID_LE_EXIT_SUSPEND)
        {
            hid_client_write_without_resp_one_byte(hid_client,hid_client->control_handle,HID_LE_EXIT_SUSPEND);
        }
        SET_PENDING_FLAG(hid_client_write_pending_set_control,hid_client->pending_request);
    }
}

/****************************************************************************/
void hid_client_write_set_report_request(GHIDC_T *const hid_client,
    HID_CLIENT_INTERNAL_MSG_SET_REPORT_T* msg)
{
    /* Check it is out put report */
    if(msg->type != gatt_hid_output_report)
    {      
        GattManagerWriteWithoutResponse((Task)&hid_client->lib_task,
                                        msg->handle,
                                        msg->size_data,
                                        (uint8 *)msg->data);
    }
    else
    {
        /* For out put report use wirte value */
        GattManagerWriteCharacteristicValue((Task)&hid_client->lib_task,
                                            msg->handle,
                                            msg->size_data,
                                            (uint8 *)msg->data);
    }

    SET_PENDING_FLAG(hid_client_write_pending_set_report,hid_client->pending_request);
}

/****************************************************************************/
void hid_client_write_boot_report_request(GHIDC_T *const hid_client,
    HID_CLIENT_INTERNAL_MSG_WRITE_BOOT_REPORT_T* msg)
{
    /* Check it is out put report */
    if( msg->type != hid_client_kb_ouput_report )
    {
        GattManagerWriteWithoutResponse((Task)&hid_client->lib_task,
                                        msg->handle,
                                        msg->size_data,
                                        (uint8 *)msg->data);
    }
    else
    {
         /* For out put report use wirte value */
        GattManagerWriteCharacteristicValue((Task)&hid_client->lib_task,
                                            msg->handle,
                                            msg->size_data,
                                            (uint8 *)msg->data);
    }
    SET_PENDING_FLAG(hid_client_write_pending_boot_report,hid_client->pending_request);
}

/****************************************************************************/
/*  External Interfaces for HID client lib, Application can use thease interfaces for write to HID service */
/****************************************************************************/

/****************************************************************************/
gatt_hid_client_status GattHidSetProtocol(GHIDC_T *const hid_client,
                                gatt_hid_client_protocol hid_protocol)
{
   gatt_hid_client_status   retval =  gatt_hid_client_status_invalid_param;
   
    /* Validate the Input Parameters */
    if(VALIDATE_INPUT_PARAM(hid_client) && (VALIDATE_HID_PROTOCOL(hid_protocol)))
    {
        if(DISCOVERY_IN_PROGRESS(hid_client))
        {
            return gatt_hid_client_status_not_allowed;
        }
        /*Check Mode  */
        if(hid_protocol == gatt_hid_protocol_boot)
        {
            /* If Boot mode is not supported, the this request can not be processed */
            if(!hid_client->boot_mode_supported)
            return gatt_hid_client_status_not_supported;

            MessageSendConditionally((Task)&hid_client->lib_task, HID_CLIENT_INTERNAL_SET_PROTOCOL_BOOT, NULL,&hid_client->pending_request);   
            retval = gatt_hid_client_status_initiated;
        }
        else if(hid_protocol == gatt_hid_protocol_report)
        {
            MessageSendConditionally((Task)&hid_client->lib_task, HID_CLIENT_INTERNAL_SET_PROTOCOL_REPORT, NULL,&hid_client->pending_request); 
            retval = gatt_hid_client_status_initiated;
        }
    }
    return retval;
}


/****************************************************************************/
gatt_hid_client_status GattHidControlRequest(GHIDC_T *const hid_client,
                               gatt_hid_client_control_type ctrl)
{
    gatt_hid_client_status   retval =  gatt_hid_client_status_invalid_param;   

    /* Validate the Input Parameters */
    if(VALIDATE_INPUT_PARAM(hid_client))
    {
        /* Make internal message */
        MAKE_HID_CLIENT_MESSAGE(HID_CLIENT_INTERNAL_SET_CTRL_POINT);

        if(DISCOVERY_IN_PROGRESS(hid_client))
        {
            free(message);
            return gatt_hid_client_status_not_allowed;
        }
        /* Copy the control type ID */
        message->ctrl_type = ctrl;
        MessageSendConditionally((Task)&hid_client->lib_task, HID_CLIENT_INTERNAL_SET_CTRL_POINT,NULL,&hid_client->pending_request);
        retval = gatt_hid_client_status_initiated;
    }
    return retval;
}

/****************************************************************************/
gatt_hid_client_status GattHidSetReport(GHIDC_T *const hid_client,                              
                                GATT_HID_CLIENT_SET_REPORT_T *hid_report_data)
{
    gatt_hid_client_status   retval =  gatt_hid_client_status_invalid_param;
    uint16 report_handle = 0;
    uint16 type = 0;

    /* Validate the Input Parameters */
    if(VALIDATE_INPUT_PARAM(hid_client))
    {  
        if(DISCOVERY_IN_PROGRESS(hid_client))
        {
            return gatt_hid_client_status_not_allowed;
        }
        /*Check report data is available */
        if(hid_report_data)
        {
            GATT_HID_CLIENT_DEBUG_INFO(("Func:GattHidSetReport(): Entry\n"));
            /* Check there exists a report handle for report id, and get the handle */
            if(hid_client_get_report_handle_and_type_from_id(hid_client,hid_report_data->report_id,&report_handle,&type))
            {
                MAKE_HID_CLIENT_MESSAGE_WITH_LEN( HID_CLIENT_INTERNAL_MSG_SET_REPORT,hid_report_data->report_len);
                memset(message, 0, sizeof(HID_CLIENT_INTERNAL_MSG_SET_REPORT_T) + hid_report_data->report_len - sizeof(uint8));
                message->handle = report_handle;
                message->type = type;
                message->size_data = hid_report_data->report_len;
                memmove(message->data, hid_report_data->data, hid_report_data->report_len);
                MessageSendConditionally((Task)&hid_client->lib_task, HID_CLIENT_INTERNAL_MSG_SET_REPORT,message,&hid_client->pending_request);
                retval = gatt_hid_client_status_initiated;
            }
        }
    }
    return retval;
}

/****************************************************************************/
gatt_hid_client_status GattHidWriteBootReport(GHIDC_T *const hid_client, 
                                GATT_HID_CLIENT_WRITE_BOOT_REPORT_T *hid_boot_report)
{
    gatt_hid_client_status  retval =  gatt_hid_client_status_invalid_param;
    uint16 handle = 0; 
    /* Validate the Input Parameters */
    if(VALIDATE_INPUT_PARAM(hid_client))
    {
        if(DISCOVERY_IN_PROGRESS(hid_client))
        {
            return gatt_hid_client_status_not_allowed;
        }
        
        if(hid_boot_report)
        {   /* Verify Boot mode us supported */
            if(!hid_client->boot_mode_supported)
            {
                return gatt_hid_client_status_not_supported;
            }
            retval = gatt_hid_client_status_initiated;
            /* Get the handle as per request */
            switch(hid_boot_report->report_type)
            {
                case hid_client_kb_ouput_report:
                {
                    handle = hid_client->boot_handles.boot_output_report_handle;
                }
                break;

                case hid_client_kb_input_report:
                {
                   handle = hid_client->boot_handles.boot_kb_input_report_handle;
                }
                break;

                case hid_client_mouse_input_report:
                {
                   handle = hid_client->boot_handles.boot_mouse_input_report_handle;
                }
                break;

                default:
                    retval =gatt_hid_client_status_invalid_param;
                break;
            }
            /*If there is a handle available, then proceed further */
            if(retval != gatt_hid_client_status_invalid_param)
            {
                MAKE_HID_CLIENT_MESSAGE_WITH_LEN( HID_CLIENT_INTERNAL_MSG_WRITE_BOOT_REPORT,hid_boot_report->report_len);
                memset(message, 0, sizeof(HID_CLIENT_INTERNAL_MSG_WRITE_BOOT_REPORT_T) + hid_boot_report->report_len - sizeof(uint8));

                message->handle = handle;
                message->type = hid_boot_report->report_type;
                message->size_data = hid_boot_report->report_len;
                memmove(message->data, hid_boot_report->data, hid_boot_report->report_len);
                GATT_HID_CLIENT_DEBUG_INFO(("Func:GattHidWriteBootReport(): handle[%x],data[%x],typr[%x],length[%x]\n",message->handle,message->data[0],message->type,message->size_data));

                MessageSendConditionally((Task)&hid_client->lib_task, HID_CLIENT_INTERNAL_MSG_WRITE_BOOT_REPORT,message,&hid_client->pending_request);
            }
        }
   }
   return retval;
}


