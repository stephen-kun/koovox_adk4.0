// *****************************************************************************
// Copyright Cambridge Silicon Radio Limited 2005 - 2015.        http://www.csr.com
// Part of ADK 4.0
//
// $Change: 2317643 $  $DateTime: 2015/07/10 11:14:28 $
// *****************************************************************************


#ifdef DEBUG_ON
   #define ENABLE_PROFILER_MACROS
#endif

#include "profiler.h"
#include "segments.asm"
#include "stream_encode.asm"
#include "stream_decode.asm"
#include "stream_decode_sync.asm"
#include "stream_relay.asm"

#ifdef BUILD_WITH_C_SUPPORT
  #include "codec_library_c_stubs.asm"
#endif
