// *****************************************************************************
// Copyright Cambridge Silicon Radio Limited 2007 - 2015.        http://www.csr.com
// Part of ADK 4.0
//
// $Change: 2317643 $  $DateTime: 2015/07/10 11:14:28 $
// *****************************************************************************

#ifndef FRAME_SYNC_SCO_COPY_OP_HEADER_INCLUDED
#define FRAME_SYNC_SCO_COPY_OP_HEADER_INCLUDED

   // Below must match shift copy for compatibity
   .CONST   $frame_sync.sco_copy_op.INPUT_START_INDEX_FIELD             0;
   .CONST   $frame_sync.sco_copy_op.OUTPUT_START_INDEX_FIELD            1;
   .CONST   $frame_sync.sco_copy_op.SHIFT_AMOUNT_FIELD                  2;
   // Extensions for sco copy
   .CONST   $frame_sync.sco_copy_op.COPY_LIMIT_FIELD                    3;

   .CONST   $frame_sync.sco_copy_op.STRUC_SIZE                          4;


#endif // FRAME_SYNC_SCO_COPY_OP_HEADER_INCLUDED
