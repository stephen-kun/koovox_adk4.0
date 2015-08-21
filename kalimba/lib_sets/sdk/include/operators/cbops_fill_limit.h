// *****************************************************************************
// Copyright Cambridge Silicon Radio Limited 2005 - 2015.        http://www.csr.com
// Part of ADK 4.0
//
// $Change: 2317643 $  $DateTime: 2015/07/10 11:14:28 $
// *****************************************************************************

#ifndef CBOPS_FILL_LIMIT_HEADER_INCLUDED
#define CBOPS_FILL_LIMIT_HEADER_INCLUDED

   // This restricts copy operations so that the output cbuffer/port will not
   // contain more than the number of words of data in the FILL_LIMIT_FIELD.
   .CONST   $cbops.fill_limit.FILL_LIMIT_FIELD                      0;
   .CONST   $cbops.fill_limit.OUT_BUFFER_FIELD                      1;
   .CONST   $cbops.fill_limit.STRUC_SIZE                            2;
   .CONST   $cbops.fill_limit.NO_LIMIT                              -1;

#endif // CBOPS_FILL_LIMIT_HEADER_INCLUDED
