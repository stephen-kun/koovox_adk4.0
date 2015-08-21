/* Copyright (C) CSR plc, 2015 */
/* Part of ADK 4.0 */

#include <message.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <panic.h>

#include "gatt_hid_client.h"

#include "gatt_hid_client_msg_handler.h"
#include "gatt_hid_client_private.h"
#include "gatt_hid_client_discovery.h"
#include "gatt_hid_client_debug.h"


/****************************************************************************/
/*                                      Internal Helper Functions                                                              */                      
/****************************************************************************/

/***************************************************************************
NAME
    hid_client_start_handle_discovery

DESCRIPTION
    Utility function used to send internal message for HID server handle discovery.
*/
static void  hid_client_start_handle_discovery(GHIDC_T *const hid_client,
                const GATT_HID_CLIENT_CONFIG_PARAMS_T *const cfg,
                const GATT_HID_CLIENT_INIT_PARAMS_T *const init_params,
                bool start_discovery)
{
    if(start_discovery)
    {
        /* Make internal message for HID Handle Discovery and Post it to Discovery Module  */
        MAKE_HID_CLIENT_MESSAGE(HID_CLIENT_INTERNAL_MSG_DISCOVER);
        /* Copy the connection ID */
        message->cid = init_params->cid;
        /*  Copy the start Handle for srevice */
        message->start_handle = init_params->start_handle;
        /* Copy the end handle for service */
        message->end_handle = init_params->end_handle;
        /* Send the discover request to message handler */
        MessageSend((Task)&hid_client->lib_task,HID_CLIENT_INTERNAL_MSG_DISCOVER, message);
    }
    else
    {
        /* Make internal message for HID Handle Discovery Complete and Post it to Discovery Module  */
        MAKE_HID_CLIENT_MESSAGE(HID_CLIENT_INTERNAL_MSG_DISCOVER_COMPLETE);
        /* Copy the connection ID */
        message->cid = init_params->cid;
        MessageSend((Task)&hid_client->lib_task,HID_CLIENT_INTERNAL_MSG_DISCOVER_COMPLETE, message);
    }

    GATT_HID_CLIENT_DEBUG_INFO(("Func:hid_client_start_handle_discovery(),Exit\n"));
}

/***************************************************************************
NAME
    hid_client_allocate_memory_for_handles

DESCRIPTION
    Utility function used to allocate memory for handles configured by application  .
*/
static void hid_client_allocate_memory_for_handles(GHIDC_T *const hid_client,
               const GATT_HID_CLIENT_CONFIG_PARAMS_T *const cfg)
{
    uint16 ccd_mem_size = 0;

    GATT_HID_CLIENT_DEBUG_INFO(("Func:hid_client_allocate_memory_for_handles(),Entry\n"));
    /* Check handles are configured */    
    if(cfg != NULL )
    {
        /* Boot mode supported? */
        if((cfg->is_boot_mode_supported) && (cfg->max_num_bootmode_ccd > 0))
        {
            ccd_mem_size += (sizeof(uint16) * cfg->max_num_bootmode_ccd);
            hid_client->boot_mode_supported = TRUE;
            hid_client->ccd_handles = (gatt_hid_ccd_handle_mem_t*)PanicUnlessMalloc(ccd_mem_size*sizeof(gatt_hid_ccd_handle_mem_t));
            memset(hid_client->ccd_handles,0,ccd_mem_size*sizeof(gatt_hid_ccd_handle_mem_t));
            memset(&hid_client->boot_handles,0,sizeof(gatt_hid_boot_mode_handles_t));
        }
        else
        {   /* Set Boot handles as NULL as client does not want to use remote device boot mode */
             hid_client->boot_mode_supported = FALSE;
        }
        ccd_mem_size += (sizeof(uint16) *cfg->max_num_reportmode_ccd);
        hid_client->ccd_handles = (gatt_hid_ccd_handle_mem_t*)realloc( hid_client->ccd_handles,ccd_mem_size*sizeof(gatt_hid_ccd_handle_mem_t));
        memset(hid_client->ccd_handles,0,ccd_mem_size*sizeof(gatt_hid_ccd_handle_mem_t));


        hid_client->report_id_map = (gatt_hid_client_report_id_map_t *)PanicUnlessMalloc(sizeof(gatt_hid_client_report_id_map_t) * cfg->max_num_report);
        memset(hid_client->report_id_map,0,(sizeof(gatt_hid_client_report_id_map_t) * cfg->max_num_report));
       
    }
    /* Use Default parameters */
    else
    {
        GATT_HID_CLIENT_DEBUG_INFO(("Func:hid_client_allocate_memory_for_handles(), Use Default Handle Settings \n"));
        /* Allocate memory for all handles as per pre defined values */
        hid_client->boot_mode_supported = TRUE;
        ccd_mem_size = MAX_NUM_BOOT_CCD+MAX_NUM_REPORT_CCD;
        hid_client->ccd_handles = (gatt_hid_ccd_handle_mem_t*)calloc(ccd_mem_size,sizeof(gatt_hid_ccd_handle_mem_t));
        hid_client->report_id_map = (gatt_hid_client_report_id_map_t *)calloc(MAX_NUM_HID_REPORTS,sizeof(gatt_hid_client_report_id_map_t));
    }
    GATT_HID_CLIENT_DEBUG_INFO(("Func:hid_client_allocate_memory_for_handles(),Exit\n"));
}

/***************************************************************************
NAME
    hid_client_free_memory_for_handles

DESCRIPTION
    Utility function used to free the memory allocated for handles   .
*/
static void hid_client_free_memory_for_handles(GHIDC_T *const hid_client)
{
    /* Free up memory for all other handles which is allocated at time of Init */
    free(hid_client->ccd_handles);
    hid_client->ccd_handles= NULL;
    free(hid_client->report_id_map);
    hid_client->report_id_map= NULL;
}

/***************************************************************************
NAME
    hid_client_free_memory_for_handles

DESCRIPTION
    Utility function used to init hid handles    .
*/
static void hid_client_init_handles(GHIDC_T *const hid_client)
{
    /* Reset all Handles */
    hid_client->protocol_handle= INVALID_HID_HANDLE;
    hid_client->info_handle = INVALID_HID_HANDLE ;
    hid_client->control_handle = INVALID_HID_HANDLE ;
    hid_client->external_report_reference_handle = INVALID_HID_HANDLE ;
    hid_client->report_map_handle = INVALID_HID_HANDLE;
}

/****************************************************************************/
/*                                      External Interface Functions                                                          */                      
/****************************************************************************/

/****************************************************************************/
gatt_hid_client_status GattHidClientInit(Task appTask, 
                                GHIDC_T *const hid_client,
                                const GATT_HID_CLIENT_INIT_PARAMS_T *const init_params,
                                const GATT_HID_CLIENT_CONFIG_PARAMS_T *const config_params,
                                bool discover_handles)
{
    gatt_manager_client_registration_params_t reg_params;
    /* Validate all the input parameters */
    if(INPUT_PARAM_NULL(appTask,hid_client,init_params) || CONFIG_PARAM_INVALID(config_params))
    {      
       return gatt_hid_client_status_invalid_param;
    }
  
    /* Two HID discovery cannot handle together, so check discovery status */
    if(hid_client_discovery_in_progress())
    {
        /* Another Discovery in progress, can not handle second discovery now */
        return gatt_hid_client_status_not_allowed;
    }
    /* Start the Init Process of  HID LIB */
    if(discover_handles)
    {
        /* Reset the HID client data structure */
        memset(hid_client, 0, sizeof(GHIDC_T));
        /* Get memory for handles configured */
        hid_client_allocate_memory_for_handles(hid_client,config_params);
        /* Init the handles */
        hid_client_init_handles(hid_client);
        /* Store the application handle where all the confirmation and indication messages need be posted */
        hid_client->app_task = appTask;
        /* Store the Library task where all the external call backs need to be received */
        hid_client->lib_task.handler = hid_client_msg_handler;
    }

    /* SetUp GATT manager registartion parameters */
    reg_params.cid =  init_params->cid;
    reg_params.client_task = &hid_client->lib_task;
    reg_params.end_handle = init_params->end_handle;
    reg_params.start_handle = init_params->start_handle;
    
    /* Try to register HID Client with GATT manager for notifications and indications */
    if(GattManagerRegisterClient(&reg_params) == gatt_manager_status_success)
    {
        /* Update the discovery intstance parameters */
        if(discover_handles)
        {
            if(!hid_client_init_discovery_instance(config_params, init_params->end_handle))
            {
                return gatt_hid_client_status_insufficient_memory;
            }
        }
        /* Start HID service handle discovery and returns status as initiated */
        hid_client_start_handle_discovery(hid_client,config_params,init_params,discover_handles);
        GATT_HID_CLIENT_DEBUG_INFO(("Func:GattHidClientInit(),Sucess, Start Discovery of handles \n"));
        return gatt_hid_client_status_initiated;
    } 
    else
    {
        return gatt_hid_client_status_registration_failed;
    }
}

/****************************************************************************/
gatt_hid_client_status GattHidClientDeInit(GHIDC_T *const hid_client)
{
    gatt_hid_client_status retval = gatt_hid_client_status_invalid_param;

    GATT_HID_CLIENT_DEBUG_INFO(("Func:GattHidClientDeInit(),Entry\n"));
    /* Validate the Input Parameters */
    if(hid_client != NULL)
    {
        /* Deregister the client from GATT manager */
        if(GattManagerUnregisterClient((Task)&hid_client->lib_task) == gatt_manager_status_success)
        {
            /* Free memory for all handles allocated inside HID client LIB */
            hid_client_free_memory_for_handles(hid_client);
            /* If Discovery in progress for this HID instance while DeInit, Inform this to discovery module */
            if(DISCOVERY_IN_PROGRESS(hid_client))
            {
                GATT_HID_CLIENT_DEBUG_INFO(("Func:GattHidClientDeInit(),Discovery In Progress %d\n",hid_client->discovery_in_progress));
                hid_client_cleanup_discovery_instance();
            }
            
            /* Clear pending messages */
            MessageFlushTask((Task)&hid_client->lib_task);
            return gatt_hid_client_status_success;
        }
        else
        {
            return gatt_hid_client_status_failed;
        }
    }
    GATT_HID_CLIENT_DEBUG_INFO(("Func:GattHidClientDeInit(),Exit\n"));
    return retval;
}

