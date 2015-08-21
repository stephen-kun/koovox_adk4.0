/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#include <message.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "gatt_manager.h"
#include "gatt_imm_alert_client.h"

#include "gatt_imm_alert_client_msg_handler.h"
#include "gatt_imm_alert_client_private.h"


/***************************************************************************
NAME
    imm_alert_client_connect_request

DESCRIPTION
    Send Internal Message for start finding out the remote server characteristic handles for immediate alert service .
*/
static void  imm_alert_client_connect_request(GIASC_T *const imm_alert_client,
                                      const GATT_IMM_ALERT_CLIENT_INIT_PARAMS_T *const init_params)
{
    /* Make Inernal Message for fidning out characterisitc handles */
    MAKE_IMM_ALERT_CLIENT_MESSAGE(IMM_ALERT_CLIENT_INETRNAL_MSG_CONNECT);
    /* Fill in the connection ID */
    message->cid = init_params->cid;     
    /* Fill In start Handle */
    message->start_handle = init_params->start_handle;
    /* Fill in end handle  */
    message->end_handle = init_params->end_handle;
    /* Send Connect Request Internal Message */
    MessageSend((Task)&imm_alert_client->lib_task, IMM_ALERT_CLIENT_INETRNAL_MSG_CONNECT, message);
}

/****************************************************************************/
gatt_imm_alert_client_status GattImmAlertClientInit(Task appTask , 
                                        GIASC_T *const imm_alert_client,
                                        const GATT_IMM_ALERT_CLIENT_INIT_PARAMS_T *const client_init_params)
{
    gatt_manager_client_registration_params_t reg_params;
    /* validate the input parameters */
    if((appTask == NULL) || (imm_alert_client == NULL) || CLIENT_INIT_PARAM_INVALID(client_init_params))
    {
        return gatt_imm_alert_client_status_invalid_param;
    }
    /* Reset the alert client data structure */
    memset(imm_alert_client, 0, sizeof(GIASC_T));
    /* Keep track on application task as all the notifications and indication need to be send to here */
    imm_alert_client->app_task = appTask;
    /* Store library task for external message reception */
    imm_alert_client->lib_task.handler = imm_alert_client_msg_handler;
    /*Store the alert handle with Invalid Value */
    imm_alert_client->alert_handle = INVALID_IMM_ALERT_HANDLE;
    /*Store the connection ID within lib instance */
    imm_alert_client->cid = client_init_params->cid;

    /* Setup GATT manager registartion parameters */
    reg_params.cid =  client_init_params->cid;
    reg_params.client_task = &imm_alert_client->lib_task;
    reg_params.end_handle = client_init_params->end_handle;
    reg_params.start_handle = client_init_params->start_handle;

    if(GattManagerRegisterClient(&reg_params) == gatt_manager_status_success)
    {
        /* Start finding out the characteristics handles for Immediate alert service */
        imm_alert_client_connect_request(imm_alert_client,client_init_params);
        return gatt_imm_alert_client_status_initiated;
    } 
    
    return gatt_imm_alert_client_status_failed;

}

/****************************************************************************/
gatt_imm_alert_client_status GattImmAlertClientSetAlertLevel(const GIASC_T *const imm_alert_client,
                                        const gatt_imm_alert_set_level alert_level)
{
    gatt_imm_alert_client_status retval = gatt_imm_alert_client_status_not_allowed;
    
    /* Validate the input parameters */
    if((imm_alert_client == NULL) || (alert_level >= gatt_imm_alert_level_reserved))
    {
        return gatt_imm_alert_client_status_invalid_param;
    }
    /* Check the alert handle as been found out already , else this request can not be allowed */
    if(imm_alert_client->alert_handle != INVALID_IMM_ALERT_HANDLE)
    {
        /* Make Inernal message for set alert level */
        MAKE_IMM_ALERT_CLIENT_MESSAGE(IMM_ALERT_CLIENT_INTERNAL_MSG_SET_ALERT);
        /* Fill In Alert level */
        message->alert_level = alert_level;
        /* Send Internal message for set alert level */
        MessageSend((Task)&imm_alert_client->lib_task, IMM_ALERT_CLIENT_INTERNAL_MSG_SET_ALERT, message);
        /* Return Initiated */
        return  gatt_imm_alert_client_status_initiated;
    }
    return retval;
}

/****************************************************************************/
gatt_imm_alert_client_status GattImmAlertClientDestroy(GIASC_T *imm_alert_client, uint16 cid)
{
    gatt_imm_alert_client_status result = gatt_imm_alert_client_status_invalid_param;

    /* Check parameters */
    if (imm_alert_client != NULL)
    {
        /* Unregister with the GATT Manager and verify the result */
        if (GattManagerUnregisterClient(&imm_alert_client->lib_task) == gatt_manager_status_success)
        {
            result = gatt_imm_alert_client_status_success;
        }
        else
        {
            result = gatt_imm_alert_client_status_failed;
        }
        
        /* Clear pending messages */
        MessageFlushTask((Task)&imm_alert_client->lib_task);
    }
    
    return result;
}




