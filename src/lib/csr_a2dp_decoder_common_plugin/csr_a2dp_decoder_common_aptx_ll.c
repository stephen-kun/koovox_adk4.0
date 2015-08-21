/****************************************************************************
Copyright (C) Cambridge Silicon Radio Ltd. 2005

FILE NAME
    csr_decoder_common_aptx_ll.c
DESCRIPTION
    aptx low latency specific functions
NOTES
*/

#include <audio.h>
#include <codec.h>
#include <stdlib.h>
#include <panic.h>
#include <print.h>
#include <file.h>
#include <stream.h> /*for the ringtone_note*/
#include <kalimba.h>
#include <kalimba_standard_messages.h>
#include <message.h>
#include <ps.h>
#include <Transform.h>
#include <string.h>
#include <pio_common.h>

#include "csr_i2s_audio_plugin.h"
#include "audio_plugin_if.h" /*for the audio_mode*/
#include "audio_plugin_common.h"
#include "csr_a2dp_decoder_common_plugin.h"
#include "csr_a2dp_decoder_common.h"
#include "csr_a2dp_decoder_common_if.h"
#include "csr_a2dp_decoder_common_aptx_ll.h"
#include "csr_a2dp_decoder_common_cvc_back_channel.h"

/****************************************************************************
DESCRIPTION
    This function connects APTX low delay audio 
****************************************************************************/
void MusicConnectAptxLowLatencySource(A2dpPluginConnectParams *codecData, uint8 content_protection)
{
    Transform rtp_transform = 0;
    DECODER_t * DECODER = CsrA2dpDecoderGetDecoderData();
    
    /* when configured for using back channel low latency apps */
    if(isCodecLowLatencyBackChannel())
    {
        /* if the back channel is required and the mic/line input is configured */
        if (codecData->voice_rate)
        {
            /* Bidirectional channel uses faststream mono with the following settings */
            /*
               Configure the SBC format for the microphone data
               16kHz, Mono, Blocks 16, Sub-bands 8, Loudness, Bitpool = 32
               (data rate = 72kbps, packet size = 3*72 + 4 = 220 <= DM5).
            */
           codecData->format     = 0x31;
           codecData->bitpool    = 32;
           PRINT(("DECODER: apt-X Low Latency Bidirectional rate=0x%lx voice_rate=0x%lx\n format=0x%x\n",DECODER->rate,codecData->voice_rate,codecData->format));
        }
    }

    /* ensure the sample rate is valid */
    if (DECODER->rate)
    {
        /* disconnect media sink as it might be disposed */
        StreamDisconnect(StreamSourceFromSink(DECODER->media_sink), 0);
    
        /* if content protection is required feed the media sink through the rtp decoder transform */
        if (content_protection)
        {
            rtp_transform = TransformRtpDecode(StreamSourceFromSink(DECODER->media_sink) , StreamKalimbaSink(LOW_LATENCY_CODEC_TO_DSP_PORT));
            PRINT(("aptX: RTP Transform \n"));
            csrA2dpDecoderStartTransformCheckScms(rtp_transform, content_protection);
        }
        /* connect the media sink to the dsp input port */
        else
        {
            PanicFalse(StreamConnect(StreamSourceFromSink(DECODER->media_sink),StreamKalimbaSink(LOW_LATENCY_CODEC_TO_DSP_PORT)));
        }
    }
    
    /* Send parameters that configure the SRA and buffer settings */
    PRINT(("aptX LL params: initial level=%d target level=%d sra max rate=%d/10000 sra avg time=%d good working buffer level=%d \n",
           codecData->aptx_sprint_params.target_codec_level,codecData->aptx_sprint_params.initial_codec_level,
           codecData->aptx_sprint_params.sra_max_rate,codecData->aptx_sprint_params.sra_avg_time,
           codecData->aptx_sprint_params.good_working_level));
    KalimbaSendMessage(MESSAGE_SET_APTX_LL_PARAMS1, codecData->aptx_sprint_params.target_codec_level,
                       codecData->aptx_sprint_params.initial_codec_level,
                       codecData->aptx_sprint_params.sra_max_rate,   /* Third field is scaled by 10000 */
                       codecData->aptx_sprint_params.sra_avg_time);
    KalimbaSendMessage(MESSAGE_SET_APTX_LL_PARAMS2, codecData->aptx_sprint_params.good_working_level,
                       0, 0, 0);

    /* update the current audio state */
    SetAudioInUse(TRUE);
}
