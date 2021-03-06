/****************************************************************************
Copyright Cambridge Silicon Radio Limited 2015
Part of ADK 4.0

FILE NAME
    upgrade_partitions_stub.h
    
DESCRIPTION
    Test stub for partitions module of upgrade library.
*/
#ifndef UPGRADE_PARTITIONS_STUB_H_
#define UPGRADE_PARTITIONS_STUB_H_

#include "upgrade_partitions.h"

void testinit_stubs_partitions(void);

void partitions_stub_addSwap(UpgradePartitionID old,UpgradePartitionID new);


#endif /* UPGRADE_PARTITIONS_STUB_H_ */

