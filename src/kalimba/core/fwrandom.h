// *****************************************************************************
// Copyright Cambridge Silicon Radio Limited 2005 - 2015.        http://www.csr.com
// Part of ADK 4.0
//
// $Change: 2317643 $  $DateTime: 2015/07/10 11:14:28 $
// *****************************************************************************


#ifndef FWRANDOM_HEADER_INCLUDED
#define FWRANDOM_HEADER_INCLUDED

   #ifdef DEBUG_ON
      #define FWRANDOM_DEBUG_ON
   #endif

   // structure fields
   .CONST   $fwrandom.NEXT_ENTRY_FIELD           0;
   .CONST   $fwrandom.NUM_REQ_FIELD              1;
   .CONST   $fwrandom.NUM_RESP_FIELD             2;
   .CONST   $fwrandom.RESP_BUF_FIELD             3;
   .CONST   $fwrandom.HANDLER_ADDR_FIELD         4;
   .CONST   $fwrandom.STRUC_SIZE                 5;

   // set the maximum possible number of handlers - this is only used to detect
   // corruption in the linked list, and so can be quite large
   .CONST   $fwrandom.MAX_HANDLERS               50;

   .CONST   $fwrandom.LAST_ENTRY                 -1;
   .CONST   $fwrandom.REATTEMPT_TIME_PERIOD      10000;
   .CONST   $fwrandom.MAX_RAND_BITS              512;

   .CONST   $fwrandom.FAILED_READ_LENGTH         -1;

#endif

