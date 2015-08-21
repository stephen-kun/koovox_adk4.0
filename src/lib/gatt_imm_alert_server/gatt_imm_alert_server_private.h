/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#ifndef GATT_IMM_ALERT_PRIVATE_H
#define GATT_IMM_ALERT_PRIVATE_H

#include <csrtypes.h>
#include <message.h>
#include <panic.h>
#include <stdlib.h>

/* Macros for creating messages */
#define MAKE_IMM_ALERT_MESSAGE(TYPE) MESSAGE_MAKE(message,TYPE##_T)

#endif /* GATT_IMM_ALERT_PRIVATE_H */

