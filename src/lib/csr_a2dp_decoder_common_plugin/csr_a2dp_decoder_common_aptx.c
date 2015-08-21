/****************************************************************************
Copyright (C) Cambridge Silicon Radio Ltd. 2005

FILE NAME
    csr_a2dp_decoder_common_aptx.c
DESCRIPTION
    aptx specific functions
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
#include "csr_a2dp_decoder_common_aptx.h"

/****************************************************************************
DESCRIPTION
    This function connects APTX standard delay audio 
****************************************************************************/
void MusicConnectAptxSource(A2dpPluginConnectParams *codecData, uint8 content_protection)
{
    DECODER_t * DECODER = CsrA2dpDecoderGetDecoderData();
    
    /* Initialise PCM. Output stereo at 44k1Hz or 48kHz. */
    PRINT(("DECODER: aptX rate=%u Hz\n",(uint16)DECODER->rate));

    /* ensure sample rate is set to a valid value */
    if (DECODER->rate)
    {
        /* disconnect media sink, it may be been disposed of */
        StreamDisconnect(StreamSourceFromSink(DECODER->media_sink), 0);
    
        /* if content protection required connect the media sink to the decoder transform */
        if (content_protection)
        {
#ifdef SHAREME_SLAVE
            StreamConnect(StreamSourceFromSink(DECODER->media_sink) , StreamKalimbaSink(CODEC_TO_DSP_PORT));
#else
            Transform rtp_transform = TransformRtpDecode(StreamSourceFromSink(DECODER->media_sink), StreamKalimbaSink(CODEC_TO_DSP_PORT));
            PRINT(("aptX: RTP Transform \n"));
            csrA2dpDecoderStartTransformCheckScms(rtp_transform, content_protection);
#endif
        }
        /* otherwise connect the media sink to the dsp input port */
        else
        {
            PanicFalse(StreamConnect(StreamSourceFromSink(DECODER->media_sink),StreamKalimbaSink(CODEC_TO_DSP_PORT)));
        }

        /* Send parameters that are to be displayed in Music Manager application */
        PRINT(("aptX: sampling rate=0x%lx channel mode=0x%x \n",DECODER->rate,codecData->channel_mode));
        KalimbaSendMessage(APTX_PARAMS_MSG,DECODER->rate, codecData->channel_mode, 0,0);
    }
    
    /* update the current audio state */
    SetAudioInUse(TRUE);
}
