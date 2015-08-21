/*******************************************************************************
 Copyright Cambridge Silicon Radio Limited 2015
 Part of ADK 4.0
*******************************************************************************/

#ifndef _VMTYPES_H
#define _VMTYPES_H

#ifndef STATIC_ASSERT
#define STATIC_ASSERT(COND, MSG) typedef char static_assertion_##MSG[(COND)?1:-1]
#endif

#ifndef BITFIELD
#define BITFIELD    unsigned
#endif

#ifndef PACK_STRUCT
#define PACK_STRUCT
#endif

#endif
