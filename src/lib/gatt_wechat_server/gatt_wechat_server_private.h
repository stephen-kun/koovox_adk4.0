/* Copyright (C) CSR plc, 2014 - 2015. */
/* Part of ADK 4.0 */

#ifndef GATT_WECHAT_SERVER_PRIVATE_H_
#define GATT_WECHAT_SERVER_PRIVATE_H_

#include <csrtypes.h>
#include <message.h>
#include <panic.h>
#include <stdlib.h>
#include <string.h>


/* Macros for creating messages */
#define MAKE_WECHAT_MESSAGE(TYPE) MESSAGE_MAKE(message,TYPE##_T)


#define MAKE_WECHAT_MESSAGE_WITH_LEN(TYPE, LEN)                           \
    TYPE##_T *message = (TYPE##_T*)PanicUnlessMalloc(sizeof(TYPE##_T) + \
                                                     (LEN ? LEN - 1 : 0))

#define MAKE_WECHAT_MESSAGE_WITH_VALUE(TYPE, SIZE, VALUE) \
    MAKE_WECHAT_MESSAGE_WITH_LEN(TYPE, SIZE);             \
    memmove(message->value, (VALUE), (SIZE));           \
    message->size_value = (SIZE)


#endif
