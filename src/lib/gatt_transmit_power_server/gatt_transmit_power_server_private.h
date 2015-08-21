/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */
/* 
    FILE NAME
    gatt_transmit_power_server_private.h

DESCRIPTION
    Header file for the Transmit Power Server Service data structure.
*/

/*!
@file   gatt_transmit_power_server_private.h
@brief  Header file for the Transmit Power Server data structure.

        This file documents the basic data structure of Transmit Power Server Service.
*/

#ifndef GATT_TRANSMIT_POWER_SERVER_PRIVATE_H
#define GATT_TRANSMIT_POWER_SERVER_PRIVATE_H

#include <csrtypes.h>
#include <message.h>
#include <panic.h>
#include <stdlib.h>

/* Macros for creating messages */
#define MAKE_TRANSMIT_POWER_MESSAGE(TYPE) MESSAGE_MAKE(message,TYPE##_T)

#endif /* GATT_TRANSMIT_POWER_SERVER_PRIVATE_H */
