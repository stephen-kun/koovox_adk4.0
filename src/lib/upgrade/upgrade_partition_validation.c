/****************************************************************************
Copyright Cambridge Silicon Radio Limited 2014 - 2015.
Part of ADK 4.0

FILE NAME
    upgrade_partition_validation.c

DESCRIPTION

NOTES

*/

#include "upgrade_ctx.h"
#include "upgrade_fw_if.h"
#include "upgrade_partition_validation.h"

void UpgradePartitionValidationInit(void)
{
    UpgradeCtxGet()->partitionValidationNextPartition = 0;
}

UpgradePartitionValidationResult UpgradePartitionValidationValidate(void)
{
    uint16 partitions_num = UpgradeFWIFGetPhysPartitionNum();

    while(UpgradeCtxGet()->partitionValidationNextPartition < partitions_num)
    {
        UpgradeFWIFPartitionValidationStatus status = UpgradeFWIFValidateExecutablePartition(
                UpgradeCtxGet()->partitionValidationNextPartition);

        switch(status)
        {
        case UPGRADE_FW_IF_PARTITION_VALIDATION_TRIGGERED:
            ++UpgradeCtxGet()->partitionValidationNextPartition;
            /* fall through */
        case UPGRADE_FW_IF_PARTITION_VALIDATION_IN_PROGRESS:
            return UPGRADE_PARTITION_VALIDATION_IN_PROGRESS;
            break;

        case UPGRADE_FW_IF_PARTITION_VALIDATION_SKIP:
            ++UpgradeCtxGet()->partitionValidationNextPartition;
            break;
        }
    }

    return UPGRADE_PARTITION_VALIDATION_DONE;
}


