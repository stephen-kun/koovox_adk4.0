// *****************************************************************************
// Copyright Cambridge Silicon Radio Limited 2005 - 2015.        http://www.csr.com
// Part of ADK 4.0
//
// $Change: 2317643 $  $DateTime: 2015/07/10 11:14:28 $
// *****************************************************************************


#ifndef MATH_ADDRESS_BITREVERSE_INCLUDED
#define MATH_ADDRESS_BITREVERSE_INCLUDED

#include "math_library.h"

//******************************************************************************
// MODULE:
//    $math.address_bitreverse
//
// DESCRIPTION:
//    Software version of the BITREVERSE() preprocessor command.
//    Lower 15 bits of input address are bitreversed, bit15 is left the same.
// @verbatim
//    input:   XXXXXXXXY110010001000010
//                     ||             |
//                     || BITREVERSE  |
//                     V|             |
//    output:  00000000Y010000100010011
// @endverbatim
//
// INPUTS:
//    - r0 = address
//
// OUTPUTS:
//    - r1 = bitreversed address
//
// TRASHED REGISTERS:
//    none
//
//******************************************************************************
.MODULE $M.math.address_bitreverse;
   .CODESEGMENT MATH_ADDRESS_BITREVERSE_PM;
   .DATASEGMENT DM;

   $math.address_bitreverse:
   
      M[$BITREVERSE_VAL] = r0;
      r1 = M[$BITREVERSE_ADDR];
   
   rts;

.ENDMODULE;

#endif // MATH_ADDRESS_BITREVERSE_INCLUDED
