// *****************************************************************************
// Copyright Cambridge Silicon Radio Limited 2003 - 2015.        http://www.csr.com
// Part of ADK 4.0
//
// $Change: 1322655 $  $DateTime: 2012/06/07 14:16:10 $
// *****************************************************************************

// *****************************************************************************
// DESCRIPTION
//    Resampler used to reconcile the codec output sampling rate to the
//    DAC sampling rate. This is used for multi-channel operation and
//    is performed before channel splitting (before the Music manager) in
//    order to reduce MIPS.
//
// *****************************************************************************

#include "core_library.h"
#include "cbops_library.h"

#if defined(APTX_ACL_SPRINT_ENABLE)
#include "codec_decoder_aptx_acl_sprint.h"
#elseif defined(FASTSTREAM_ENABLE)
#include "codec_decoder_faststream.h"
#else
#include "codec_decoder.h"
#endif
#ifdef TWS_ENABLE
#include "relay_conn.h"
#endif


#include "operators\iir_resamplev2\iir_resamplev2_header.h"
#include "music_example.h"
#include "frame_sync_stream_macros.h"

// CODEC resampler module
.MODULE $codec_resampler;
   .DATASEGMENT DM;

#if defined(APTX_ACL_SPRINT_ENABLE) || defined(FASTSTREAM_ENABLE)
   // Size of CODEC resampler output buffers when ONLY APTX or FASTSTREAM decoders are used
   .CONST CODEC_RESAMPLER_CBUFFER_SIZE          ($music_example.NUM_SAMPLES_PER_FRAME + 100);
#else
   // Size of CODEC resampler output buffers (needs to be double the frame size when using the subwoofer)
   .CONST CODEC_RESAMPLER_CBUFFER_SIZE          (2 * $music_example.NUM_SAMPLES_PER_FRAME + 100);
#endif

   DeclareCBuffer($codec_resamp_out_left_cbuffer_struc,$codec_resamp_out_left,CODEC_RESAMPLER_CBUFFER_SIZE);
   DeclareCBuffer($codec_resamp_out_right_cbuffer_struc,$codec_resamp_out_right,CODEC_RESAMPLER_CBUFFER_SIZE);
#if defined(SPDIF_ENABLE)
   DeclareCBuffer($codec_resamp_out_lfe_cbuffer_struc,$codec_resamp_out_lfe,CODEC_RESAMPLER_CBUFFER_SIZE);
#endif // SPDIF_ENABLE

   // Lookup table used to determine cbops/resampler structure values given codec rate and ADC rate
   // Codec rate, DAC rate, filter spec, mono resampler operator, stereo resampler operator, mono operator struc, stereo operator struc
   // Optimized table to have only the minimum required parameters (3 elements) compared to the original table structure (5 elements)
   .CONST record_size 3;
   .VAR filter_spec_lookup_table[] =
      48000, 48000, 0,
      44100, 44100, 0,
      32000, 32000, 0,
      22050, 22050, 0,
      16000, 16000, 0,
      8000, 8000, 0,

      16000, 48000, $M.iir_resamplev2.Up_3_Down_1.filter,
      32000, 48000, $M.iir_resamplev2.Up_3_Down_2.filter,
      44100, 48000, $M.iir_resamplev2.Up_160_Down_147.filter,
      16000, 44100, $M.iir_resamplev2.Up_441_Down_160.filter,
      32000, 44100, $M.iir_resamplev2.Up_441_Down_320.filter,
      48000, 44100, $M.iir_resamplev2.Up_147_Down_160.filter,
      0;

   // Temp buffer size is calculated for worst-case scenario, which occurs when
   // an ESCO wireless subwoofer is connected.  In this scenario the resampler
   // runs at 7.5 msec intervals, the input rate is 44.1 kHz and the output rate
   // is 48 kHz.
   // The equation is:
   // Temp Buffer Size = (Number of Input Samples in 7.5 msec + 1) /(int_ration_s1 + frac_ratio_s1)
   // Temp Buffer Size = 331.75 / (0 + 0.525)
   // Temp Buffer Size = 631.90
   .CONST TEMP_BUFF_SIZE                     632;

   .VAR/DM iir_temp[TEMP_BUFF_SIZE];

   // Use the process interface to the resampleV2 library
   .VAR left[$iir_resamplev2.OBJECT_SIZE] =
      $audio_out_left_cbuffer_struc,                                    // $iir_resamplev2.INPUT_1_START_INDEX_FIELD              0;
      $codec_resamp_out_left_cbuffer_struc,                             // $iir_resamplev2.OUTPUT_1_START_INDEX_FIELD             1;
      // Filter Definition
      0,                                                                // $iir_resamplev2.FILTER_DEFINITION_PTR_FIELD            2;
      -8,                                                               // $iir_resamplev2.INPUT_SCALE_FIELD                      3;
      8,                                                                // $iir_resamplev2.OUTPUT_SCALE_FIELD                     4;
      // Buffer between Stages
      iir_temp,                                                         // $iir_resamplev2.INTERMEDIATE_CBUF_PTR_FIELD            5;
      length(iir_temp),                                                 // $iir_resamplev2.INTERMEDIATE_CBUF_LEN_FIELD            6;
      // 1st Stage
      0,                                                                // $iir_resamplev2.PARTIAL1_FIELD                         7;
      0,                                                                // $iir_resamplev2.SAMPLE_COUNT1_FIELD                    8;
      0,                                                                // $iir_resamplev2.FIR_HISTORY_BUF1_PTR_FIELD             9;
      0,                                                                // $iir_resamplev2.IIR_HISTORY_BUF1_PTR_FIELD             10;
      // 2nd Stage
      0,                                                                // $iir_resamplev2.PARTIAL2_FIELD                         11;
      0,                                                                // $iir_resamplev2.SAMPLE_COUNT2_FIELD                    12;
      0,                                                                // $iir_resamplev2.FIR_HISTORY_BUF2_PTR_FIELD             13;
      0,                                                                // $iir_resamplev2.IIR_HISTORY_BUF2_PTR_FIELD             14;
      // Reset Flags (Set to NULL)
      0,                                                                // $iir_resamplev2.RESET_FLAG_FIELD                       15;
      0 ...;                                                            // Zero the history buffers                               16...;

   .VAR right[$iir_resamplev2.OBJECT_SIZE] =
      $audio_out_right_cbuffer_struc,                                   // $iir_resamplev2.INPUT_1_START_INDEX_FIELD              0;
      $codec_resamp_out_right_cbuffer_struc,                            // $iir_resamplev2.OUTPUT_1_START_INDEX_FIELD             1;
      // Filter Definition
      0,                                                                // $iir_resamplev2.FILTER_DEFINITION_PTR_FIELD            2;
      -8,                                                               // $iir_resamplev2.INPUT_SCALE_FIELD                      3;
      8,                                                                // $iir_resamplev2.OUTPUT_SCALE_FIELD                     4;
      // Buffer between Stages
      iir_temp,                                                         // $iir_resamplev2.INTERMEDIATE_CBUF_PTR_FIELD            5;
      length(iir_temp),                                                 // $iir_resamplev2.INTERMEDIATE_CBUF_LEN_FIELD            6;
      // 1st Stage
      0,                                                                // $iir_resamplev2.PARTIAL1_FIELD                         7;
      0,                                                                // $iir_resamplev2.SAMPLE_COUNT1_FIELD                    8;
      0,                                                                // $iir_resamplev2.FIR_HISTORY_BUF1_PTR_FIELD             9;
      0,                                                                // $iir_resamplev2.IIR_HISTORY_BUF1_PTR_FIELD             10;
      // 2nd Stage
      0,                                                                // $iir_resamplev2.PARTIAL2_FIELD                         11;
      0,                                                                // $iir_resamplev2.SAMPLE_COUNT2_FIELD                    12;
      0,                                                                // $iir_resamplev2.FIR_HISTORY_BUF2_PTR_FIELD             13;
      0,                                                                // $iir_resamplev2.IIR_HISTORY_BUF2_PTR_FIELD             14;
      // Reset Flags (Set to NULL)
      0,                                                                // $iir_resamplev2.RESET_FLAG_FIELD                       15;
      0 ...;                                                            // Zero the history buffers                               16...;

#if defined(SPDIF_ENABLE)
   .VAR lfe[$iir_resamplev2.OBJECT_SIZE] =
      $audio_out_lfe_cbuffer_struc,                                     // $iir_resamplev2.INPUT_1_START_INDEX_FIELD              0;
      $codec_resamp_out_lfe_cbuffer_struc,                              // $iir_resamplev2.OUTPUT_1_START_INDEX_FIELD             1;
      // Filter Definition
      0,                                                                // $iir_resamplev2.FILTER_DEFINITION_PTR_FIELD            2;
      -8,                                                               // $iir_resamplev2.INPUT_SCALE_FIELD                      3;
      8,                                                                // $iir_resamplev2.OUTPUT_SCALE_FIELD                     4;
      // Buffer between Stages
      iir_temp,                                                         // $iir_resamplev2.INTERMEDIATE_CBUF_PTR_FIELD            5;
      length(iir_temp),                                                 // $iir_resamplev2.INTERMEDIATE_CBUF_LEN_FIELD            6;
      // 1st Stage
      0,                                                                // $iir_resamplev2.PARTIAL1_FIELD                         7;
      0,                                                                // $iir_resamplev2.SAMPLE_COUNT1_FIELD                    8;
      0,                                                                // $iir_resamplev2.FIR_HISTORY_BUF1_PTR_FIELD             9;
      0,                                                                // $iir_resamplev2.IIR_HISTORY_BUF1_PTR_FIELD             10;
      // 2nd Stage
      0,                                                                // $iir_resamplev2.PARTIAL2_FIELD                         11;
      0,                                                                // $iir_resamplev2.SAMPLE_COUNT2_FIELD                    12;
      0,                                                                // $iir_resamplev2.FIR_HISTORY_BUF2_PTR_FIELD             13;
      0,                                                                // $iir_resamplev2.IIR_HISTORY_BUF2_PTR_FIELD             14;
      // Reset Flags (Set to NULL)
      0,                                                                // $iir_resamplev2.RESET_FLAG_FIELD                       15;
      0 ...;                                                            // Zero the history buffers                               16...;
#endif // SPDIF_ENABLE

   // Flag showing whether the resampling is active
   .VAR resampler_active = 0;


// *****************************************************************************
// MODULE:
//    $M.codec_resampler
//
// DESCRIPTION:
//    Configure the codec resampler to perform the required sampling rate
//    change. This modifies the resampler structures with values appropriate
//    for the sampling rate change.
//
//    Uses $current_codec_sampling_rate and $current_dac_sampling_rate
//    to determine the configuration required.
//
// INPUTS:
//    - none
//
// OUTPUTS:
//    - none
//
// TRASHED REGISTERS:
//    - r0, r1, r2, r3, r4, r5, r6, r10, DoLoop;
//
// *****************************************************************************
   .CODESEGMENT CODEC_RESAMPLER_PM;

   config:

   // Push rLink onto stack
   $push_rLink_macro;

   // Point to first record in table
   r1 = $codec_resampler.filter_spec_lookup_table;

   // Lookup the required resampler changes for the given rates
   lookup_loop:

      // End of table?
      r0 = M[r1];
      if Z jump rates_not_supported;

      // Codec rate matches?
      null = r0 - M[$current_codec_sampling_rate];
      if NZ jump skip;

      // DAC rate matches?
      r0 = M[r1+1];
      null = r0 - M[$current_dac_sampling_rate];
      if Z jump done;

      skip:

      // Next record
      r1 = r1 + $codec_resampler.record_size;
   jump lookup_loop;

   rates_not_supported:

   // Get the requested rates
   r3 = M[$current_codec_sampling_rate];
   r4 = M[$current_dac_sampling_rate];

   // Scale down rates by 10 to fit into 16bit words
   r0 = 10;
   rMAC = r3;
   Div = rMAC/r0;
   r3 = DivResult;
   rMAC = r4;
   Div = rMAC/r0;
   r4 = DivResult;

   // Report the error to the VM
   r2 = UNSUPPORTED_SAMPLING_RATES_MSG;
   call $message.send_short;

#if 1
   // Abort
   call $error;
#endif

   // Default to a valid rate configuration (given by the first table record)
   r1 = $codec_resampler.filter_spec_lookup_table;

   // Override the DAC and codec rates with default values
   r0 = M[r1];
   M[$current_codec_sampling_rate] = r0;
   r0 = M[r1+1];
   M[$current_dac_sampling_rate] = r0;

   done:

   call $block_interrupts;

   r2 = $cbops.switch_op.ON;

   //Force Set the Reset field in the filter parameter to 0
   M[$codec_resampler.left + $iir_resamplev2.RESET_FLAG_FIELD] = 0;
   M[$codec_resampler.right + $iir_resamplev2.RESET_FLAG_FIELD] = 0;
#if defined(SPDIF_ENABLE)
   M[$codec_resampler.lfe + $iir_resamplev2.RESET_FLAG_FIELD] = 0;
#endif // SPDIF_ENABLE

   // Filter specifications in the resampler structure
   r0 = M[r1+2];
   M[$codec_resampler.left + $iir_resamplev2.FILTER_DEFINITION_PTR_FIELD] = r0;
   M[$codec_resampler.right + $iir_resamplev2.FILTER_DEFINITION_PTR_FIELD] = r0;
#if defined(SPDIF_ENABLE)
   M[$codec_resampler.lfe + $iir_resamplev2.FILTER_DEFINITION_PTR_FIELD] = r0;
#endif // SPDIF_ENABLE

   // Store a flag indicating whether resampling is being used
   if Z r2 = 0;

   M[$codec_resampler.resampler_active] = r2;

   // Calculate the adjustment factor needed to modify the SRA calculation
   call $calc_sra_resampling_adjustment;

   //Filter Function is now statically assigned in the structure

   call $unblock_interrupts;

   // Pop rLink from stack
   jump $pop_rLink_and_rts;

// *****************************************************************************
// MODULE:
//    $codec_resample.run_resampler
//
// DESCRIPTION:
//    utility function that runs the resampler for main chain
//
// INPUTS:
//    - none
//
// OUTPUTS:
//    - none
//
// TRASHED REGISTERS:
//    Assume everything
//
// *****************************************************************************

run_resampler:

   // Push rLink onto stack
   $push_rLink_macro;

#ifdef TWS_ENABLE
   r1 = M[$relay.mode];
   null = r1 - 2;
   if NEG jump resample_no_TWS;
   // resample left channel
   r8 = $codec_resampler.left;
   r5 = $TWS_FORCE_FRAME_SIZE;
   call $iir_resamplev2.Limited_Process;

   // resample right channel
   r8 = $codec_resampler.right;
   r5 = $TWS_FORCE_FRAME_SIZE;
   call $iir_resamplev2.Limited_Process;
   jump run_resampler_done;
   resample_no_TWS:
#endif

   // resample left channel
   r8 = $codec_resampler.left;
   call $iir_resamplev2.Process;

   // resample right channel
   r8 = $codec_resampler.right;
   call $iir_resamplev2.Process;

   #if defined(SPDIF_ENABLE)
      // resample lfe channel
      r8 = $codec_resampler.lfe;
      call $iir_resamplev2.Process;
   #endif // SPDIF_ENABLE


   run_resampler_done:
   // Pop rLink from stack
   jump $pop_rLink_and_rts;

.ENDMODULE;
