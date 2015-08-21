/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

/*
FILE NAME
    gatt_device_info_server_debug.h

DESCRIPTION
    Header file for the GATT Device Information Server library debug functionality.
*/
#ifndef GATT_DEVICE_INFO_SERVER_DEBUG_H_
#define GATT_DEVICE_INFO_SERVER_DEBUG_H_

/* Macro used to generate debug version of this library */
#ifdef GATT_DEVICE_INFO_DEBUG_LIB

#ifndef DEBUG_PRINT_ENABLED
#define DEBUG_PRINT_ENABLED
#endif

#include <panic.h>
#include <print.h>
#include <stdio.h>

#define GATT_DEVICE_INFO_DEBUG_INFO(x) {PRINT(("%s:%d - ", __FILE__, __LINE__)); PRINT(x);}
#define GATT_DEVICE_INFO_DEBUG_PANIC(x) {GATT_DEVICE_INFO_DEBUG_INFO(x); Panic();}


#else /* GATT_DEVICE_INFO_DEBUG_LIB */


#define GATT_DEVICE_INFO_DEBUG_INFO(x)
#define GATT_DEVICE_INFO_DEBUG_PANIC(x)

#endif /* GATT_DEVICE_INFO_DEBUG_LIB */

#endif /* GATT_DEVICE_INFO_SERVER_DEBUG_H_ */
