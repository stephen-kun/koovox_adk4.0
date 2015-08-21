/****************************************************************************
Copyright (C) Cambridge Silicon Radio Ltd. 2005

FILE NAME
    csr_decoder_common_faststream.c
DESCRIPTION
    plugin implentation which routes the sco audio though the dsp
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
#include <pblock.h>

#include "csr_i2s_audio_plugin.h"
#include "audio_plugin_if.h" /*for the audio_mode*/
#include "audio_plugin_common.h"
#include "csr_a2dp_decoder_common_plugin.h"
#include "csr_a2dp_decoder_common.h"
#include "csr_a2dp_decoder_common_if.h"
#include "csr_a2dp_decoder_common_faststream.h"
#include "csr_a2dp_decoder_common_cvc_back_channel.h"

/****************************************************************************
DESCRIPTION
    This function connects FASTSTREAM
    
    FastStream does not use RTP. L2CAP frames enter/leave via port 2
****************************************************************************/
void MusicConnectFaststreamSource(A2dpPluginConnectParams *codecData )
{
    uint32 voice_rate = 16000;
    DECODER_t * DECODER = CsrA2dpDecoderGetDecoderData();

    /*  Initialise PCM. Output stereo at 44k1Hz or 48kHz, input from left ADC at 16kHz.  */
    
    /* If no voice rate is set just make the ADC rate equal to 16kHz */
    if (codecData->voice_rate)
        voice_rate = codecData->voice_rate;

    PRINT(("DECODER: FastStream rate=0x%lx voice_rate=0x%lx\n format=0x%x bitpool=0x%x",DECODER->rate,codecData->voice_rate,codecData->format,codecData->bitpool));

    if (DECODER->rate)
    {
        /* ensure media sink is available, may have been disposed */
        StreamDisconnect(StreamSourceFromSink(DECODER->media_sink), 0);
        
        /* connect dsp input port */
        PanicFalse(StreamConnect(StreamSourceFromSink(DECODER->media_sink),StreamKalimbaSink(LOW_LATENCY_CODEC_TO_DSP_PORT)));
    }
    
    /* update the current audio state */
    SetAudioInUse(TRUE);
}

