/****************************************************************************
Copyright (C) Cambridge Silicon Radio Ltd. 2005

FILE NAME
    csr_decoder_common_fm.c
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
#include "csr_a2dp_decoder_common_fm.h"

/****************************************************************************
DESCRIPTION
    This function connects FM
    

****************************************************************************/
void MusicConnectFmSource(A2dpPluginConnectParams *codecData )
{
    DECODER_t * DECODER = CsrA2dpDecoderGetDecoderData();
    Source input_a, input_b;
       
    if (DECODER->rate)
    {
        /* connect the FM receiver I2S to the DSP */
        input_a = StreamAudioSource(AUDIO_HARDWARE_I2S, AUDIO_INSTANCE_0, AUDIO_CHANNEL_A);
        PanicFalse(SourceConfigure(input_a, STREAM_I2S_MASTER_MODE, TRUE));
        PanicFalse(SourceConfigure(input_a, STREAM_I2S_SYNC_RATE, DECODER->rate));
        /* connect I2S left channel to dsp */
        PanicFalse(StreamConnect(input_a ,StreamKalimbaSink(WIRED_LINE_A_TO_DSP_PORT)));
    
        input_b = StreamAudioSource(AUDIO_HARDWARE_I2S, AUDIO_INSTANCE_0, AUDIO_CHANNEL_B);
        PanicFalse(SourceConfigure(input_b, STREAM_I2S_MASTER_MODE, TRUE));                    
        PanicFalse(SourceConfigure(input_b, STREAM_I2S_SYNC_RATE, DECODER->rate));
        /* connect I2S right channel to dsp */
        PanicFalse(StreamConnect(input_b ,StreamKalimbaSink(WIRED_LINE_B_TO_DSP_PORT)));
    }
    
    /* update the current audio state */
    SetAudioInUse(TRUE);
}

/****************************************************************************
DESCRIPTION
    This function disconnects the FM I2S ports
    

****************************************************************************/
void MusicDisconnectFmSource(A2dpPluginConnectParams *codecData )
{
    Source input_a, input_b;
       
    /* disconnect the FM receiver I2S to the DSP */
    input_a = StreamAudioSource(AUDIO_HARDWARE_I2S, AUDIO_INSTANCE_0, AUDIO_CHANNEL_A);
    input_b = StreamAudioSource(AUDIO_HARDWARE_I2S, AUDIO_INSTANCE_0, AUDIO_CHANNEL_B);
    
    /* disconnect I2S left and right channels from dsp */
    StreamDisconnect(input_a ,StreamKalimbaSink(WIRED_LINE_A_TO_DSP_PORT));
    StreamDisconnect(input_b ,StreamKalimbaSink(WIRED_LINE_B_TO_DSP_PORT));
}


