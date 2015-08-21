/* Copyright (C) CSR plc, 2015 */
/* Part of ADK 4.0 */

#ifndef GATT_CLIENT_PRIVATE_H_
#define GATT_CLIENT_PRIVATE_H_

#include <csrtypes.h>
#include <message.h>
#include <panic.h>
#include <stdlib.h>


/* Macros for creating messages */
#define MAKE_GATT_CLIENT_MESSAGE(TYPE) MESSAGE_MAKE(message,TYPE##_T);


#endif
