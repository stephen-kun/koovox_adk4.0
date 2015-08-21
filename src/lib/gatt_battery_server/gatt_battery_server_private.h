/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#ifndef GATT_BATTERY_SERVER_PRIVATE_H_
#define GATT_BATTERY_SERVER_PRIVATE_H_

#include <csrtypes.h>
#include <message.h>
#include <panic.h>
#include <stdlib.h>


/* Macros for creating messages */
#define MAKE_BATTERY_MESSAGE(TYPE) MESSAGE_MAKE(message,TYPE##_T)

#endif
