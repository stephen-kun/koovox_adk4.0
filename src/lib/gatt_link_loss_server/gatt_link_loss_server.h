 /* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

/*!
@file    gatt_link_loss_server.h
@brief   Header file for the GATT link loss server library.

        This file provides documentation for the GATT Link loss server library
        API (library name: gatt_link_loss_server).
*/

#ifndef GATT_LINK_LOSS_SERVER_H
#define GATT_LINK_LOSS_SERVER_H


#include <csrtypes.h>
#include <message.h>

#include <library.h>

#include "gatt_manager.h"

/*!
    @brief Enumeration for Alert level Value of Alert Level characteristic for Link Loss alert service 
*/

/* For Alert Level characteristic value, refer http://developer.bluetooth.org/
 * gatt/characteristics/Pages/CharacteristicViewer.aspx?u=org.bluetooth.
 * characteristic.alert_level.xml
 */
 
typedef enum {

    gatt_link_loss_alert_level_no          = 0,     /* No Alert request */
    gatt_link_loss_alert_level_mild        = 1,     /* Mild Alert request */
    gatt_link_loss_alert_level_high        = 2,     /* High Alert request */
    gatt_link_loss_alert_level_reserved

}gatt_link_loss_alert_level;

/*! @brief The Link Loss server internal structure for the server role.

    This structure is visible to the application as it is responsible for managing resource to pass to the Link Loss library.
    The elements of this structure are only modified by the Link Loss library.
    The application SHOULD NOT modify the values at any time as it could lead to undefined behaviour.
    
 */
typedef struct
{
    TaskData lib_task;
    Task app_task;
    gatt_link_loss_alert_level alert_level;            /*! Current LLS Alert level */
}GLLSS_T;

/*!@brief Alert level write indication type
*/
typedef struct PACK_STRUCT __GATT_LLS_ALERT_LEVEL_CHANGE_IND
{
    const GLLSS_T *link_loss_server;   /*! Reference structure for the instance */
    uint16 cid;                        /*! Connection ID */
} GATT_LLS_ALERT_LEVEL_CHANGE_IND_T;

/*! @brief Enumeration of messages a client task may receive from the Link Loss service library.
 */
typedef enum
{
    GATT_LLS_ALERT_LEVEL_CHANGE_IND = GATT_LINK_LOSS_SERVER_MESSAGE_BASE,
    GATT_LLS_ALERT_SERVER_MESSAGE_TOP
} GattLinkLossServiceMessageId;

/*!
    @brief Status code returned from the GATT Link loss service server library
    This status code indicates the outcome of the request.
*/

typedef enum
{
    gatt_link_loss_server_status_success,                  /* Requested operation was successful */
    gatt_link_loss_server_status_registration_failed,      /* Registration operation to GATT manager was failed  */
    gatt_link_loss_server_status_invalid_parameter
}gatt_link_loss_server_status;


/*!
    @brief initialises the Link Loss Service Library.

    @param appTask The Task that will receive the messages sent from this link loss service library.
    @param A valid area of memory that the service library can use.Must be of at least the size of GLLSS_T
    @param start_handle This indicates the start handle of the LLS service
    @param end_handle This indicates the end handle of the LLS service
    
    @return The status result of calling the API as defined in gatt_link_loss_server_status.

*/
gatt_link_loss_server_status GattLinkLossServerInit(
                                Task appTask , 
                                GLLSS_T *const link_loss_server,
                                uint16 start_handle,
                                uint16 end_handle);


/*!
    @brief This API is used to return the current Alert level to the application.

    @param link_loss_server The pointer to LLS service library instance.

    @return The current alert level.

*/
gatt_link_loss_alert_level GattLinkLossServerGetAlertLevel(const GLLSS_T *const link_loss_server);

#endif /* GATT_LINK_LOSS_SERVER_H */

