/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#ifndef GATT_BATTERY_SERVICE_DEBUG_H_
#define GATT_BATTERY_SERVICE_DEBUG_H_

/* Macro used to generate debug version of this library */
#ifdef GATT_BATTERY_DEBUG_LIB


#ifndef DEBUG_PRINT_ENABLED
#define DEBUG_PRINT_ENABLED
#endif

#include <panic.h>
#include <print.h>
#include <stdio.h>

#define GATT_BATTERY_DEBUG(x)		PRINT(x)

#if 0
#define GATT_BATTERY_DEBUG_INFO(x) {PRINT(("%s:%d - ", __FILE__, __LINE__)); PRINT(x);}
#define GATT_BATTERY_DEBUG_PANIC(x) {GATT_BATTERY_DEBUG_INFO(x); Panic();}
#else
#define GATT_BATTERY_DEBUG_INFO(x)
#define GATT_BATTERY_DEBUG_PANIC(x)
#endif

#else /* GATT_BATTERY_DEBUG_LIB */

#define GATT_BATTERY_DEBUG(x)
#define GATT_BATTERY_DEBUG_INFO(x)
#define GATT_BATTERY_DEBUG_PANIC(x)

#endif /* GATT_BATTERY_DEBUG_LIB */


#endif /* GATT_BATTERY_SERVICE_DEBUG_H_ */
