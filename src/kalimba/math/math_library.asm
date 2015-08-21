// *****************************************************************************
// Copyright Cambridge Silicon Radio Limited 2005 - 2015.        http://www.csr.com
// Part of ADK 4.0
//
// $Change: 2317643 $  $DateTime: 2015/07/10 11:14:28 $
// *****************************************************************************

#ifdef DEBUG_ON
   #define DEBUG_MATH
   #define ENABLE_PROFILER_MACROS
#endif

#include "profiler.h"
#include "sin.asm"
#include "cos.asm"
#include "sqrt.asm"
#include "inv_qdrt.asm"
#include "pow2.asm"
#include "log2.asm"
#include "rand.asm"
#include "fft.asm"
#include "vector_complex_multiply.asm"
#include "iir.asm"
#include "atan.asm"
#include "div48.asm"
#include "address_bitreverse.asm"
#include "misc.asm"
