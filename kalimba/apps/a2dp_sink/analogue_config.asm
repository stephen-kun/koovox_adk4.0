// *****************************************************************************
// Copyright Cambridge Silicon Radio Limited 2009 - 2015.        http://www.csr.com
// Part of ADK 4.0
//
// $Change: 2113562 $  $DateTime: 2015/03/09 16:01:16 $
// *****************************************************************************

// *****************************************************************************
// DESCRIPTION
//   Handle stereo or mono input for ADC/I2S input. The post processing 
//   resampling, rate adjustment, music manager runs on two channels of data.
//   The speaker crossover at the output of music manager produces one or two 
//   channels based on the number of output channels connected
//
// *****************************************************************************
#ifdef ANALOGUE_ENABLE

#include "cbops_library.h"
#include "music_example.h"

.MODULE $M.analogue;
   .DATASEGMENT DM;
   .CODESEGMENT PM;
   
   .VAR $analogue_stats[$music_example.CODEC_STATS_SIZE] =
      &$music_example.SamplingRate,                            //
      &$M.system_config.data.ZeroValue,                        //
      &$M.system_config.data.ZeroValue,                        // CODEC_STAT1
      &$M.system_config.data.ZeroValue,                        // CODEC_STAT2
      &$M.system_config.data.ZeroValue,                        // CODEC_STAT3
      &$M.system_config.data.ZeroValue,                        // CODEC_STAT4
      &$M.system_config.data.ZeroValue,                        // CODEC_STAT5
      &$M.system_config.data.ZeroValue,                        // CODEC_STAT6
      &$M.system_config.data.ZeroValue,                        // CODEC_STAT7
      &$M.system_config.data.ZeroValue,                        // CODEC_STAT8
      &$M.system_config.data.ZeroValue,                        // CODEC_STAT9
      &$M.system_config.data.ZeroValue,                        // CODEC_STATA
      &$M.system_config.data.ZeroValue;                        // CODEC_STATB

       
   // ** allocate memory for Analogue input (ADC inputs) copy routine **
   .VAR/DM1 $analogue_audio_in_copy_struc[] =
      $analogue_in_left_copy_op,        // Start of operator chain
      2,                                // 2 inputs
      $CON_IN_LEFT_PORT,                // ADC left input port
      $CON_IN_RIGHT_PORT,               // ADC right input port
      2,                                // 2 outputs
      &$audio_out_left_cbuffer_struc,   // Left sink buffer
      &$audio_out_right_cbuffer_struc;  // Right sink buffer

   .BLOCK $analogue_in_left_copy_op;
      .VAR $analogue_in_left_copy_op.next = $analogue_in_right_copy_op;
      .VAR $analogue_in_left_copy_op.func = &$cbops.shift;
      .VAR $analogue_in_left_copy_op.param[$cbops.shift.STRUC_SIZE] =
         0,                               // Input index
         2,                               // Output index
         8;                               // Scale up 16bit input word to MSB align with 24bit word
   .ENDBLOCK;

   .BLOCK $analogue_in_right_copy_op;
      .VAR $analogue_in_right_copy_op.next = $cbops.NO_MORE_OPERATORS;
      .VAR $analogue_in_right_copy_op.func = &$cbops.shift;
      .VAR $analogue_in_right_copy_op.param[$cbops.shift.STRUC_SIZE] =
         1,                               // Input index
         3,                               // Output index
         8;                               // Scale up 16bit input word to MSB align with 24bit word
   .ENDBLOCK;
   
   .VAR/DM1 $analogue_audio_in_mono_copy_struc[] =     
      &$audio_channel_one_to_two_internal_copy_op,     // First operator block
      1,                                               // Number of inputs
      $CON_IN_LEFT_PORT,                               // Input
      2,                                               // Number of outputs
      &$audio_out_left_cbuffer_struc,                  // Output A
      &$audio_out_right_cbuffer_struc;                 // Output B

   .BLOCK $audio_channel_one_to_two_internal_copy_op;
      .VAR $audio_channel_one_to_two_internal_copy_op.next = $analogue_mono_in_left_copy_op;
      .VAR $audio_channel_one_to_two_internal_copy_op.func = &$cbops.one_to_two_chan_copy;
      .VAR $audio_channel_one_to_two_internal_copy_op.param[$cbops.one_to_two_chan_copy.STRUC_SIZE] =
         0,                               // Input index
         1,                               // Output index A
         2;                               // Output index B
   .ENDBLOCK;
   
   .BLOCK $analogue_mono_in_left_copy_op;
      .VAR $analogue_mono_in_left_copy_op.next = $analogue_mono_in_right_copy_op;
      .VAR $analogue_mono_in_left_copy_op.func = &$cbops.shift;
      .VAR $analogue_mono_in_left_copy_op.param[$cbops.shift.STRUC_SIZE] =
         1,                               // Input index
         1,                               // Output index
         8;                               // Scale up 16bit input word to MSB align with 24bit word
   .ENDBLOCK;

   .BLOCK $analogue_mono_in_right_copy_op;
      .VAR $analogue_mono_in_right_copy_op.next = $cbops.NO_MORE_OPERATORS;
      .VAR $analogue_mono_in_right_copy_op.func = &$cbops.shift;
      .VAR $analogue_mono_in_right_copy_op.param[$cbops.shift.STRUC_SIZE] =
         2,                               // Input index
         2,                               // Output index
         8;                               // Scale up 16bit input word to MSB align with 24bit word
   .ENDBLOCK;

.ENDMODULE;

#endif