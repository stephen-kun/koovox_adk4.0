/****************************************************************************
Copyright Cambridge Silicon Radio Limited 2015
Part of ADK 4.0

FILE NAME
    upgrade_fw_if_priv.h
    
DESCRIPTION
    Definition of FW I/F state datatype.
*/

#ifndef UPGRADE_FW_IF_PRIV_H_
#define UPGRADE_FW_IF_PRIV_H_

typedef struct
{
#ifdef UPGRADE_USE_OEM_SIGN_VALIDATION
    ValidationContext vctx;
#endif

#ifdef UPGRADE_USE_FW_STUBS
    uint8 *lastPartitionData;
    uint16 lastPartitionDataLen;
    uint16 openPartitionNum;
#else
    uint16 partitionNum;
#endif
} UpgradeFWIFCtx;

#endif /* UPGRADE_FW_IF_PRIV_H_ */
