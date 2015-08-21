// *****************************************************************************
// Copyright Cambridge Silicon Radio Limited 2005 - 2015.        http://www.csr.com
// Part of ADK 4.0
//
// $Change: 2317643 $  $DateTime: 2015/07/10 11:14:28 $
// *****************************************************************************

#ifndef MATH_FFT_HEADER_INCLUDED
#define MATH_FFT_HEADER_INCLUDED

   .CONST   $fft.STRUC_SIZE            3;
   .CONST   $fft.NUM_POINTS_FIELD      0;
   .CONST   $fft.REAL_ADDR_FIELD       1;
   .CONST   $fft.IMAG_ADDR_FIELD       2;

// In this variant, fft twiddle factors are stored externally ...   
   #if defined(FFT_LOW_RAM)
      .CONST $FFT_LOW_RAM_USED       1;
   #endif

#endif
