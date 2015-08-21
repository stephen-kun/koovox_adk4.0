/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

/*!
@file    gatt_transmit_power_server.h
@brief   Header file for the GATT Transmit Power Server library.

        This file provides documentation for the GATT Transmit Power Server library
        API.
*/

#ifndef GATT_TRANSMIT_POWER_SERVER_H
#define GATT_TRANSMIT_POWER_SERVER_H


#include <csrtypes.h>
#include <message.h>

#include <library.h>

#include "gatt_manager.h"

/* Data structure for internal use of transmit power server library. 
 * NOTE: Please DONOT alter this structure for whatever reason */
typedef struct _GTPSS
{
    TaskData lib_task;
    Task app_task;
}GTPSS;

/*!
    @brief Status code returned from the GATT transmit power server library
    This status code indicates the outcome of the request.
*/

typedef enum
{
    gatt_tps_status_success,                  /* Requested operation was successful */
    gatt_tps_status_registration_failed,   /* Registration operation to GATT manager was failed  */
    gatt_tps_status_invalid_parameter,   /* Parameters were not as expetced  */
    gatt_tps_status_not_allowed
}gatt_tps_status;


/*!
    @brief Initialises the Transmit Power Server Library.

    @param appTask The Task that will receive the messages sent from this transmit
                power server service library.
    @param tps A valid area of memory that the server library can use.Must be of at least
               the size of GTPSS
    @param start_handle This indicates the start handle of the TPS service
    @param end_handle This indicates the end handle of the TPS service
    
    @return The status result of calling the API.

*/
gatt_tps_status GattTransmitPowerServerInitTask(Task appTask ,
                                GTPSS *const tps,
                                uint16 start_handle,
                                uint16 end_handle);

#endif /* GATT_TRANSMIT_POWER_SERVER_H */      
