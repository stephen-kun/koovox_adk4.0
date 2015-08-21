/****************************************************************************
Copyright (C) Cambridge Silicon Radio Ltd. 2005

FILE NAME
    csr_voice_prompts.h
DESCRIPTION
    plugin implementation which plays audio prompts
NOTES
*/

#include <audio.h>
#include <codec.h>
#include <stdlib.h>
#include <panic.h>
#include <stream.h>
#include <print.h>
#include <stream.h> 
#include <message.h> 
#include <string.h>
#include <source.h>
#include <transform.h>
#include <i2c.h>

#include <file.h>
#include <stdio.h>
#include "audio_plugin_if.h" 
#include <kalimba.h>
#include <kalimba_standard_messages.h>

#include "audio.h"
#include "audio_plugin_if.h"
#include "csr_voice_prompts_plugin.h"
#include "csr_voice_prompts.h"
#include "csr_i2s_audio_plugin.h"
#include "csr_multi_channel_plugin.h"


#ifdef ANC

#include "anc.h"
#include "csr_anc_plugin.h"

#define ANC_MIC_A_DSP_PORT   5
#define ANC_MIC_B_DSP_PORT   6

#endif /* ANC */

#define PROMPT_MAX_SIZE (0xffff)

#define FORCED_TONE_PLAYBACK_RATE   (48000)

typedef struct
{
    uint16                     no_prompts;
    uint16                     no_prompts_per_lang;
} voice_prompts_header;

typedef struct
{
    uint32              size;
    voice_prompts_codec decompression;
    uint16              playback_rate;
    bool                stereo;
} voice_prompt;

typedef struct 
{
    /*! The codec task to use to connect the audio*/
    Task                codec_task;
    /* */
    AudioPluginFeatures features;
    /*! VP source */
    Source              source;
    /*! 2nd source needed for right channel when not using DSP */
    Source              duplicate_source;
    /*! Decompression to use */
    voice_prompts_codec decompression;
    /*! Playback rate */
    uint16              playback_rate;
    /*! DSP re-sample rate */
    uint16              resample_rate_with_coefficient_applied;
    /*! The language */
    uint16              language;
    /*! The volume at which to play the tone */
    int16               prompt_volume;
    /*! stereo or mono */
    bool                stereo;
    /*! flag that indicates if the prompt is mixing with existing audio */
    bool                mixing;
    /*! prompt index Id. */
    uint16              prompt_id;   
    /*! If this is a tone, pointer to the ringtone_note */
    ringtone_note       *tone;   
} PHRASE_DATA_T ;

/* Decoder type to send to DSP app */
typedef enum
{
    PHRASE_NO_DECODER = 0,
    PHRASE_SBC_DECODER = 1,
    PHRASE_MP3_DECODER = 2,
    PHRASE_AAC_DECODER = 3
} PHRASE_DECODER_T;


static voice_prompts_header     header;
static PHRASE_DATA_T            *phrase_data = NULL;

#define SIZE_PROMPT_DATA   (12)

static Source csrVoicePromptsGetPrompt(voice_prompt* prompt, PHRASE_DATA_T * pData);

static void CsrVoicePromptsPluginStopPhraseMixable ( void ) ;
static void CsrVoicePromptsPluginStopPhraseDsp ( void ) ;
static void DisconnectAndCloseSource(Source source);


/******************************************************************************
DESCRIPTION

    Sends input ('CODEC'), required output ('DAC'), and tone sample rate
    configuration messages to the DSP, taking into account any re-sampling.
*/
static void sendDspSampleRateMessages(void)
{
#ifdef ANC
    /* If using ANC then we need to give an indication of the sample rate required
       when the ANC mics are connected. */
    uint32 anc_sample_rate = AncGetDacSampleRate();
    uint16 anc_sample_rate_flag = DSP_ANC_SAMPLE_RATE_NONE;

    if (anc_sample_rate == ANC_SAMPLE_RATE_96K)
    {
        PRINT(("VP: Using ANC at 96k\n"));
        anc_sample_rate_flag = DSP_ANC_SAMPLE_RATE_96K;
    }
    else if (anc_sample_rate == ANC_SAMPLE_RATE_192K)
    {
        PRINT(("VP: Using ANC at 192k\n"));
        anc_sample_rate_flag = DSP_ANC_SAMPLE_RATE_192K;
    }

    /* Set the ANC Sample rate */
    if(!KalimbaSendMessage(MESSAGE_SET_ANC_MODE, anc_sample_rate_flag, 0, 0, 0))
    {
        PRINT(("VP: Message MESSAGE_SET_ANC_MODE failed!\n"));
        Panic();
    }
#endif /* ANC */
        
    if (phrase_data->decompression == voice_prompts_codec_pcm)
    {
        /* PCM specific messages */
        /* Set that we are sending a PCM prompt in tone port */
        KalimbaSendMessage(MESSAGE_SET_DAC_SAMPLE_RATE, phrase_data->resample_rate_with_coefficient_applied, 0, 0, (LOCAL_FILE_PLAYBACK|PCM_PLAYBACK));
        
        /* Configure prompt playback */
        KalimbaSendMessage(MESSAGE_SET_TONE_RATE_MESSAGE_ID, phrase_data->playback_rate, (phrase_data->stereo?PROMPT_STEREO:0)|PROMPT_ISPROMPT, 0, 0);
        
        KalimbaSendMessage(MESSAGE_SET_CODEC_SAMPLE_RATE, phrase_data->resample_rate_with_coefficient_applied, 0, 0, 0);
    }
    else if(phrase_data->decompression == voice_prompts_codec_tone)
    {
        /* Tone specific messages */
        /* Set that we are sending a tone in tone port */
        KalimbaSendMessage(MESSAGE_SET_DAC_SAMPLE_RATE, phrase_data->resample_rate_with_coefficient_applied, 0, 0, (PCM_PLAYBACK));
        
        /* Configure prompt playback */
        KalimbaSendMessage(MESSAGE_SET_TONE_RATE_MESSAGE_ID, phrase_data->playback_rate, 0, 0, 0);
        
        KalimbaSendMessage(MESSAGE_SET_CODEC_SAMPLE_RATE, phrase_data->resample_rate_with_coefficient_applied, 0, 0, 0);
    }
    else if (phrase_data->decompression == voice_prompts_codec_ima_adpcm)
    {
        PRINT(("VP: Play ADPCM with DSP\n"));
        /* Set that we are sending a ADPCM prompt in tone port */
        KalimbaSendMessage(MESSAGE_SET_DAC_SAMPLE_RATE, phrase_data->resample_rate_with_coefficient_applied, 0, 0, (LOCAL_FILE_PLAYBACK|PCM_PLAYBACK));
        
        KalimbaSendMessage(MESSAGE_SET_TONE_RATE_MESSAGE_ID, phrase_data->playback_rate, PROMPT_ISPROMPT, 0, 0);
        
        KalimbaSendMessage(MESSAGE_SET_CODEC_SAMPLE_RATE, phrase_data->resample_rate_with_coefficient_applied, 0, 0, 0);
    }
    else
    {
        /* Set the codec sampling rate (DSP needs to know this for resampling) */
        KalimbaSendMessage(MESSAGE_SET_DAC_SAMPLE_RATE, phrase_data->resample_rate_with_coefficient_applied, 0, 0, (LOCAL_FILE_PLAYBACK));
        
        KalimbaSendMessage(MESSAGE_SET_CODEC_SAMPLE_RATE, phrase_data->playback_rate/DSP_RESAMPLING_RATE_COEFFICIENT, 0, 0, 0);
    }
}

/****************************************************************************
DESCRIPTION

    Sends configuration messages relating to multi-channel output to the DSP.
    This includes configuring the hardware type of each output, and the I2S
    master/slave mode.
*/
static void sendDspMultiChannelMessages(void)
{
    AUDIO_PLUGIN_SET_MULTI_CHANNEL_OUTPUT_TYPES_MSG_T message;
    
    PanicFalse(CsrMultiChanGetDspOutputTypesMsg(&message));
    
    /* Set the hardware type of each output */
    if (!KalimbaSendLongMessage(MESSAGE_SET_MULTI_CHANNEL_OUTPUT_TYPES,
                                sizeof(AUDIO_PLUGIN_SET_MULTI_CHANNEL_OUTPUT_TYPES_MSG_T),
                                (const uint16*)&message))
    {
        PRINT(("DECODER: Message MESSAGE_SET_MULTI_CHANNEL_OUTPUT_TYPES failed!\n"));
        Panic();
    }
    
    if (CsrMultiChanI2sActive())
    {
        /* Set the I2S master/slave mode */
        if (!KalimbaSendMessage(MESSAGE_SET_I2S_CONFIG_MSG, !CsrI2SMasterIsEnabled(), 0, 0, 0))
        {
            PRINT(("DECODER: Message MESSAGE_SET_I2S_CONFIG_MSG failed!\n"));
            Panic();
        }
    }
}

/****************************************************************************
DESCRIPTION
    helper function to determine whether voice prompt to be played is adpcm or pcm which
    can then be mixed by the other dsp applications.
*/
bool CsrVoicePromptsIsMixable(uint16 id, uint16 language, Task codec_task)
{
    Source lSource = NULL ;
    voice_prompt prompt;
    PHRASE_DATA_T * p_data;

#ifdef ANC
    if (GetAudioPlugin() == &csr_anc_audio_plugin)
    {
        /* Currently used plugin is the ANC plugin, cannot mix as the plugin does not
           use the DSP. */
        return FALSE;
    }
#endif

    /* Allocate the memory */
    p_data = (PHRASE_DATA_T *) PanicUnlessMalloc(sizeof(PHRASE_DATA_T));
    
    /* Set up params */
    p_data->language      = language;
    p_data->codec_task    = codec_task;
    p_data->prompt_id     = id;
    p_data->tone          = NULL;
    
    /* initialise compression type */    
    prompt.decompression = voice_prompts_codec_none;  
    
    /* call function to get type of compression used  for this prompt */
    lSource = csrVoicePromptsGetPrompt(&prompt, p_data);
    
    /* Finished with header source now compression type has been found, close it */
    if(!SourceClose(lSource))
        Panic();
    
    free(p_data);
    p_data = NULL;

    switch (prompt.decompression)
    {
        case voice_prompts_codec_ima_adpcm:
        case voice_prompts_codec_pcm:
        case voice_prompts_codec_tone:
            return TRUE;
        default:
            return FALSE;
    }
}

static Source csrVoicePromptsGetPrompt(voice_prompt* prompt, PHRASE_DATA_T * pData)
{
    const uint8* rx_array;
    Source lSource = NULL;
    uint16 index;

    char file_name[17];

    if(!pData)
        return NULL;
        
    /* determine if this is a tone */
    if(pData->tone)
    {
        PRINT(("VP: Prompt is a tone 0x%x\n", (uint16)pData->tone));    
    
        /* update current tone playing status */
        SetTonePlaying(TRUE);
        
        prompt->size = 0;
        prompt->decompression = voice_prompts_codec_tone;
        prompt->playback_rate = 8000;
        prompt->stereo = pData->features.stereo;

        /*return the tone source*/
        return StreamRingtoneSource ( (const ringtone_note *) (pData->tone) ) ;        
    }
    
    /* Must be a prompt, work out the index of the prompt */
    index = pData->prompt_id;
    
    /* Adjust for language */
    index += (pData->language * header.no_prompts_per_lang);
    
    /* Sanity checking */
    if(index >= header.no_prompts || !prompt )
        return NULL;
    
    PRINT(("VP: Play prompt %d of %d\n", index+1, header.no_prompts));
    
    /* Get the header file name */
    sprintf(file_name, "headers/%d.idx", index);
    lSource = StreamFileSource(FileFind(FILE_ROOT, file_name, strlen(file_name)));

    /* Check source created successfully */
    if(SourceSize(lSource) < SIZE_PROMPT_DATA)
    {
        /* Finished with header source, close it */
        SourceClose(lSource);
        return NULL;
    }
    
    /* Map in header */
    rx_array = SourceMap(lSource);
    
    /* Pack data into result */
    /*    rx_array[0] not used*/
    /*    rx_array[1] index, not used */
    prompt->stereo        = rx_array[4];
    prompt->size          = ((uint32)rx_array[5] << 24) | ((uint32)rx_array[6] << 16) | ((uint16)rx_array[7] << 8) | (rx_array[8]);
    prompt->decompression = rx_array[9];
    prompt->playback_rate = ((uint16)rx_array[10] << 8) | (rx_array[11]);   
    
    /* The size of the prompt must be limited to 16 bits for I2C and SPI as the firmware traps only support a 16 bit size */
    if (prompt->size > PROMPT_MAX_SIZE)
    {
        prompt->size = PROMPT_MAX_SIZE;
        PRINT(("Prompt size adjusted to 16 bit maximum\n"));
    }
    
    /* Get the prompt file name */
    sprintf(file_name, "prompts/%d.prm", index);
    
    PRINT(("File Prompt: %s dec %X rate 0x%x stereo %u size 0x%lx \n", file_name, prompt->decompression,prompt->playback_rate,prompt->stereo,prompt->size));
    
    /* Finished with header source, close it */
    if(!SourceClose(lSource))
        Panic();
    
    return StreamFileSource(FileFind(FILE_ROOT, file_name, strlen(file_name)));
}


static const char* csrVoicePromptsGetKapFile(void)
{
    switch (phrase_data->decompression)
    {
    /* if no DSP loaded, use SBC decoder to playback variable rate PCM and tones */
    case voice_prompts_codec_tone:
    case voice_prompts_codec_sbc:
    case voice_prompts_codec_pcm: 
    case voice_prompts_codec_ima_adpcm: /* use when resampling */
        return "sbc_decoder/sbc_decoder.kap";
    case voice_prompts_codec_mp3:
        return "mp3_decoder/mp3_decoder.kap";
    case voice_prompts_codec_aac:
        return "aac_decoder/aac_decoder.kap";
    default:
        Panic();
        return NULL;
    }
}

static PHRASE_DECODER_T csrVoicePromptsDecompressionToDecoder(void)
{
    switch (phrase_data->decompression)
    {
        case voice_prompts_codec_sbc:
        case voice_prompts_codec_pcm:
        case voice_prompts_codec_ima_adpcm:
        case voice_prompts_codec_tone:
            return PHRASE_SBC_DECODER;
        case voice_prompts_codec_mp3: 
            return PHRASE_MP3_DECODER;
        case voice_prompts_codec_aac:
            return PHRASE_AAC_DECODER;
        default:
            return PHRASE_NO_DECODER;
    }
}

static bool CsrVoicePromptsPluginIsDSPRequiredForTonePlayback(void)
{
    /* DSP re-sampler is required for I2S outputs to up-sample unsupported 8kHz tones */
    if(CsrMultiChanConfigRequiresI2s())
    {
        return TRUE;
    }
    /* Multichannel setup */
    if(CsrMultiChanGetOutputType(mch_out_aux_left) != OUTPUT_INTERFACE_TYPE_NONE)
    {
        return TRUE;
    }
    /* forced from sink config */
    if(phrase_data->features.force_resampling_of_tones)
    {
        return TRUE;
    }

    return FALSE;
}
       


/****************************************************************************
DESCRIPTION
    Initialise indexing.
*/

void CsrVoicePromptsPluginInit ( uint16 no_prompts, uint16 no_languages )
{
    PRINT(("VP: Init %d prompts %d languages ", no_prompts, no_languages));
    header.no_prompts = no_prompts;
    header.no_prompts_per_lang = no_prompts / no_languages;
}

/****************************************************************************
DESCRIPTION
    Plays back a voice prompt once DSP has loaded
*/

void CsrVoicePromptPluginPlayDsp(kalimba_state state)
{
    bool using_tone_port;
    
    /* If the dsp has not yet been loaded, load it and wait for a call back to this function */
    if(state == kalimba_idle)
    {        
        /* Find the DSP file to use */
        const char *kap_file = csrVoicePromptsGetKapFile();
        FILE_INDEX file_index = FileFind(FILE_ROOT,(const char *) kap_file ,strlen(kap_file));
        
        /* Load DSP */
        if (!KalimbaLoad(file_index))
            Panic();
        
        return;
    }
    
#ifdef ANC
        /* Attempt to connect ANC microphones */
        AncConnectMics(ANC_MIC_A_DSP_PORT, ANC_MIC_B_DSP_PORT);
#endif /* ANC */    
    
    /* Connect prompt source to kalimba */
    if ((phrase_data->decompression == voice_prompts_codec_pcm) || 
        (phrase_data->decompression == voice_prompts_codec_ima_adpcm) ||
        (phrase_data->decompression == voice_prompts_codec_tone))
    {
        /* Connect ADPCM, PCM prompts and tones to the tone mixing port */
        Sink lSink = NULL;
        Task taskdata = NULL;
        lSink = StreamKalimbaSink(TONE_VP_MIXING_DSP_PORT);
        
        if(phrase_data->decompression == voice_prompts_codec_ima_adpcm)
            PanicFalse(TransformStart(TransformAdpcmDecode(phrase_data->source, lSink)));
        else
            PanicFalse(StreamConnect(phrase_data->source, lSink));
        
        taskdata = MessageSinkTask( lSink , (TaskData*) &csr_voice_prompts_plugin);
        PRINT(("VP: sink task now %x was %x.\n",(uint16)&csr_voice_prompts_plugin,(uint16)taskdata));
        
        using_tone_port = TRUE;
    }
    else
    {
        /* All other prompt codec types */
        PanicFalse(StreamConnect(phrase_data->source, StreamKalimbaSink(DSP_CODEC_INPUT_PORT)));
        using_tone_port = FALSE;
    }
    
    /* Was the dsp loaded by the voice_prompts_plugin? */
    if(state == kalimba_loaded)
    {
        /* Set up multi-channel parameters. */
        multi_channel_params_t mch_params;
        memset(&mch_params, 0, sizeof(multi_channel_params_t));
        
        mch_params.sample_rate = FORCED_TONE_PLAYBACK_RATE;
        
        PRINT(("VP: Using multi-channel mapping (%luHz)\n", mch_params.sample_rate));
        
        /* Pass control to dedicated multi-channel library to connect outputs. */
        PanicFalse(CsrMultiChanConnectDsp(&mch_params));
        
        /* If re-sampling was required, multi-channel library will have overridden supplied rate. */
        phrase_data->resample_rate_with_coefficient_applied = (mch_params.sample_rate/DSP_RESAMPLING_RATE_COEFFICIENT);
        
        /* Set the digital volume before playing the prompt */
        CsrVoicePromptsPluginSetVolume(phrase_data->prompt_volume, using_tone_port);
        
        /* Set the playback rate */
        KalimbaSendMessage(MESSAGE_SET_SAMPLE_RATE, phrase_data->playback_rate, 0, 0, 1);
        
        /* Set the codec in use */
        KalimbaSendMessage(MUSIC_SET_PLUGIN_MSG, csrVoicePromptsDecompressionToDecoder(), 0, 0, 0);
        
        /* Set sample rates */
        sendDspSampleRateMessages();
        
        /* Let the DSP know which outputs are connected to which hardware types */
        sendDspMultiChannelMessages();
        
        /* Ready to go... */
        if (!KalimbaSendMessage(KALIMBA_MSG_GO, 0, 0, 0, 0))
        {
            PRINT(("VP: DSP failed to send go to kalimba\n"));
            Panic();
        }
    }
}


/****************************************************************************
DESCRIPTION
    plays One digital number using the audio plugin    
*/

static void CsrVoicePromptsPluginPlayDigit(void) 
{
    Source lSource;
    voice_prompt prompt;
    multi_channel_transform_t mch_transform = mch_transform_connect;
    
    /* Get the prompt data */
    lSource = csrVoicePromptsGetPrompt(&prompt, phrase_data);
    if(!lSource) Panic();
    
    SetAudioBusy((TaskData*) &(csr_voice_prompts_plugin));

    /* Stash the source */
    phrase_data->source = lSource;
    phrase_data->duplicate_source = NULL; /* set only if needed below */
    phrase_data->decompression = prompt.decompression;
    phrase_data->stereo = prompt.stereo;
    phrase_data->playback_rate =  (prompt.playback_rate ? prompt.playback_rate : 8000);
    phrase_data->mixing = FALSE;    /* overridden later if this prompt is mixed */
    
    SetVpPlaying(TRUE);

    /* Connect the stream to the appropriate outputs */
    switch(prompt.decompression)
    {
        /* Only for ADPCM prompts (do not attenuate tones): */
        case voice_prompts_codec_ima_adpcm:
            mch_transform = mch_transform_adpcm;
        case voice_prompts_codec_none:
            phrase_data->prompt_volume = ((phrase_data->prompt_volume * 2)/3);
        /* For both ADPCM prompts and tones: */
        case voice_prompts_codec_tone:
        {
            Sink lSink = NULL;
            Task taskdata = NULL;
            
            /* If DSP is already running, the voice prompt can be mixed with the DSP audio
               via the kalimba mixing port (3), either the CVC plugin or the music plugin
               will have already determined the output source and connected the appropriate
               ports to the hardware, and the volume will already have been set. */
            if(GetCurrentDspStatus())
            {
                phrase_data->mixing = TRUE;
                
                /* Configure DSP tone or prompt playback */
                if(prompt.decompression == voice_prompts_codec_tone)
                {
                    PRINT(("VP: play tone\n"));
                    KalimbaSendMessage(MESSAGE_SET_TONE_RATE_MESSAGE_ID, phrase_data->playback_rate , 0/*Mono Bit 0 =0, TONE BIT 1 = 0*/, 0, 0); 
                }                    
                else
                {
                    PRINT(("VP: play adpcm\n"));
                    KalimbaSendMessage(MESSAGE_SET_TONE_RATE_MESSAGE_ID, phrase_data->playback_rate , /*PROMPT_MONO*/PROMPT_ISPROMPT, 0, 0);                                  
                }
                
                /* Configure sink */
                lSink = StreamKalimbaSink(TONE_VP_MIXING_DSP_PORT);
                SinkConfigure(lSink, STREAM_CODEC_OUTPUT_RATE, phrase_data->playback_rate);
                
                PRINT(("VP: play dsp mix lSink = %x lSource = %x\n",(uint16)lSink,(uint16)lSource));
                
                /* Get messages when source has finished */
                taskdata = MessageSinkTask( lSink , (TaskData*) &csr_voice_prompts_plugin);

                /* Stream voice prompt data to the DSP tone mixing port */
                if(prompt.decompression == voice_prompts_codec_ima_adpcm)
                    PanicFalse(TransformStart(TransformAdpcmDecode(lSource, lSink)));
                else
                    PanicFalse(StreamConnect(lSource, lSink));
                
                /* No need to set volume as host plugin has already done so */
            }
            /* DSP not currently loaded, cannot mix */
            /* Load the DSP to playback this prompt if we are in multi-channel mode, as filtering / aux output may be required. */
            else if(CsrVoicePromptsPluginIsDSPRequiredForTonePlayback())
            {
                Task kal_task = MessageKalimbaTask((TaskData*)&csr_voice_prompts_plugin);
                PRINT(("VP: Use DSP for prompt (multi-channel)\n"));
                CsrVoicePromptPluginPlayDsp((kal_task != &csr_voice_prompts_plugin)? kalimba_idle : kalimba_ready);
                return;
            }
            /* Play the prompt directly without the DSP */
            else
            {
                Source rSource = NULL;

                multi_channel_params_t mch_params;
                memset(&mch_params, 0, sizeof(multi_channel_params_t));
                    
                /* Not using DSP so can't re-sample */
                mch_params.disable_resample = TRUE;
                mch_params.sample_rate = phrase_data->playback_rate;
                mch_params.transform = mch_transform;
                    
                PRINT(("VP: Play prompt direct (%u Hz) vol[%d]\n", phrase_data->playback_rate, phrase_data->prompt_volume));
                    
                /* Obtain another source to the prompt if stereo, as each one can only be connected to one output sink */
                if(CsrMultiChanGetOutputType(mch_out_primary_right) != OUTPUT_INTERFACE_TYPE_NONE)
                {
                    rSource = csrVoicePromptsGetPrompt(&prompt, phrase_data);
                    if (rSource == NULL)
                    {
                        PRINT(("VP: Failed obtain second prompt source\n"));
                        Panic();
                    }
                    phrase_data->duplicate_source = rSource;
                }
                    
                /* Connect prompt source(s) to appropriate output sink(s) */
                PanicFalse(CsrMultiChanConnectStereoSource(lSource, rSource, &mch_params));
                lSink = CsrMultiChanGetAudioSink();
                    
                /* Request an indication that the prompt has completed */
                taskdata = MessageSinkTask(lSink, (TaskData*)&csr_voice_prompts_plugin);
                    
                /* Set gain (no DSP so set main hardware gains only) */
                CsrMultiChanGainSetHardwareOnly(multi_channel_group_main, VolumeConvertDACGainToDB(phrase_data->prompt_volume));
            }
        }
        break;
        
        case voice_prompts_codec_pcm:        
        {    
            Sink lSink = NULL;
            Task taskdata = NULL;
            
            /* If DSP is already running, the voice prompt can be mixed with the DSP audio, in which case there
               is no need to set the volume as this will already have been performed by the plugin used to load
               the DSP for audio processing */            
            if(GetCurrentDspStatus())
            {
                /* store that this PCM prompt is mixing */
                phrase_data->mixing = TRUE;
                
                /* stream voice prompt data to the DSP tone mixing port */                
                lSink = StreamKalimbaSink(TONE_VP_MIXING_DSP_PORT);
                PRINT(("VP: play dsp mix lSink = %x lSource = %x\n",(uint16)lSink,(uint16)lSource));
                SinkConfigure(lSink, STREAM_CODEC_OUTPUT_RATE, phrase_data->playback_rate);                               
                
                /* Get messages when source has finished */
                taskdata = MessageSinkTask( lSink , (TaskData*) &csr_voice_prompts_plugin);

                PRINT(("VP: sink task now %x was %x\n",(uint16)&csr_voice_prompts_plugin,(uint16)taskdata));
                
                /* Configure PCM prompt playback */    
                KalimbaSendMessage(MESSAGE_SET_TONE_RATE_MESSAGE_ID, phrase_data->playback_rate , (phrase_data->stereo?PROMPT_STEREO:0)|PROMPT_ISPROMPT, 0, 0);        
                
                /* Connect source to PCM */
                PanicFalse(StreamConnect(lSource, lSink));
            }
            /* Load the DSP to play PCM audio prompt  */
            else
            {
                Task kal_task = MessageKalimbaTask( (TaskData*) &csr_voice_prompts_plugin );
                phrase_data->prompt_volume = ((phrase_data->prompt_volume * 2)/3);
                PRINT(("VP: Use DSP for PCM prompt\n"));
                CsrVoicePromptPluginPlayDsp((kal_task != &csr_voice_prompts_plugin) ? kalimba_idle : kalimba_ready);            
            }
        }
        break;

        case voice_prompts_codec_sbc:
        case voice_prompts_codec_mp3:
        case voice_prompts_codec_aac:     
        {
            /* For SBC, AAC or MP3 voice prompts, it is necessary to load the DSP with the appropriate application
               to perform the decoding */
            Task kal_task = MessageKalimbaTask( (TaskData*) &csr_voice_prompts_plugin );
            phrase_data->prompt_volume = ((phrase_data->prompt_volume * 2)/3);
            PRINT(("VP: Play DSP prompt\n"));
            CsrVoicePromptPluginPlayDsp((kal_task != &csr_voice_prompts_plugin) ? kalimba_idle : kalimba_ready);
        }
        break;

        default:
            PRINT(("VP: Codec Invalid\n"));
            Panic();
        break;
    }

}

/****************************************************************************
DESCRIPTION
    plays a number phrase using the audio plugin    
*/

void CsrVoicePromptsPluginPlayPhrase (uint16 id , uint16 language, Task codec_task , uint16 prompt_volume , AudioPluginFeatures features)
{
    if(phrase_data != NULL)
        Panic();
    
    PRINT(("VP: Play Phrase:\n"));
    
    /* Allocate the memory */
    phrase_data = (PHRASE_DATA_T *) PanicUnlessMalloc(sizeof(PHRASE_DATA_T));
    memset(phrase_data,0,sizeof(PHRASE_DATA_T));
    
    /* Set up params */
    phrase_data->language      = language;
    phrase_data->codec_task    = codec_task;
    phrase_data->prompt_volume = prompt_volume;
    phrase_data->features      = features;
    phrase_data->prompt_id     = id;
    phrase_data->mixing        = FALSE; /* currently unknown so set to false */
    phrase_data->tone          = NULL;  /* not a tone */

    CsrVoicePromptsPluginPlayDigit(); 
}

/****************************************************************************
DESCRIPTION
    plays a tone using the audio plugin    
*/
void CsrVoicePromptsPluginPlayTone ( TaskData *task, ringtone_note * tone, Task codec_task, uint16 tone_volume, AudioPluginFeatures features)
{
    if(tone == NULL)
        Panic();
    
    PRINT(("VP: Play tone:\n"));
    
    /* Allocate the memory */
    phrase_data = (PHRASE_DATA_T *) PanicUnlessMalloc(sizeof(PHRASE_DATA_T));
    memset(phrase_data,0,sizeof(PHRASE_DATA_T));
    
    /* Set up params */
    phrase_data->language      = 0;
    phrase_data->codec_task    = codec_task;
    phrase_data->prompt_volume = tone_volume;
    phrase_data->features      = features;
    phrase_data->prompt_id     = 0; /* not a prompt */
    phrase_data->mixing        = FALSE; /* currently unknown so set to false */
    phrase_data->tone          = tone;
    
    MessageCancelAll((TaskData*) &csr_voice_prompts_plugin, MESSAGE_STREAM_DISCONNECT );
    MessageCancelAll((TaskData*) &csr_voice_prompts_plugin, MESSAGE_FROM_KALIMBA);
    
    CsrVoicePromptsPluginPlayDigit(); 
}

/*
    Act on a MESSAGE_STREAM_DISCONNECT being received by the plugin.

    If phrase_data has already been freed then there is no further work
    required (because we caused the stream disconnect ourselves during
    cleanup).
    If the prompt was being mixed, we must wait for the MUSIC_TONE_COMPLETE
    message to be sure that the prompt has finished playing and so we ignore
    the stream disconnect.  If it wasn't being mixed, the
    MESSAGE_STREAM_DISCONNECT signals that the prompt has finished.  
*/
void CsrVoicePromptsPluginHandleStreamDisconnect(void)
{
    if (phrase_data && !phrase_data->mixing)
    {
        /* Prompt has finished so tidy up */
        CsrVoicePromptsPluginStopPhrase();
    }
    /* else
     * do nothing either because we have tidied up already or because
     * CsrVoicePromptsPluginCleanup() will be called when
     * AudioBusy is cleared on receipt of a MUSIC_TONE_COMPLETE
     */
}

/****************************************************************************
DESCRIPTION
    Stop prompt where DSP has not been loaded by the plugin, e.g. (adpcm or pcm) 
    Prompt is either mixing in an existing DSP app or not using the DSP.
*/
static void CsrVoicePromptsPluginStopPhraseMixable ( void ) 
{
    Sink lSink = NULL;
    Task taskdata = NULL;
    
    /* Check for DSP mixing */
    if(GetCurrentDspStatus())
    {
        lSink = StreamKalimbaSink(TONE_VP_MIXING_DSP_PORT);
    }
    else    /* Must be ADPCM not mixing */
    {
        PanicFalse(CsrMultiChanDisconnect());
    }
    
    /* Close sink and cancel any messages if valid */
    if(lSink)
    {
        /* Cancel all the messages relating to VP that have been sent */
        taskdata = MessageSinkTask(lSink, NULL);
        SinkClose(lSink);
    }
    
    PRINT(("VP: SinkTask now NULL was %x\n",(uint16)taskdata));
    MessageCancelAll((TaskData*) &csr_voice_prompts_plugin, MESSAGE_STREAM_DISCONNECT);
}

/****************************************************************************
DESCRIPTION
    Stop dsp phrase playing where VP plugin has loaded the DSP
*/
static void CsrVoicePromptsPluginStopPhraseDsp ( void ) 
{
    /* Cancel all the messages relating to VP that have been sent */
    (void)MessageKalimbaTask(NULL);
    MessageCancelAll((TaskData*) &csr_voice_prompts_plugin, MESSAGE_FROM_KALIMBA);
    
    /* Disconnect PCM sources/sinks */
    PanicFalse(CsrMultiChanDisconnect());
    
#ifdef ANC
        /* Ensure ANC microphones are disconnected */
        AncDisconnectMics();
#endif /* ANC */    
    
    KalimbaPowerOff();
}

/****************************************************************************
DESCRIPTION
    Stop a prompt from currently playing by freeing the AudioBusy lock
    to invoke the cleanup callback
   
*/
void CsrVoicePromptsPluginStopPhrase ( void ) 
{
    if (IsAudioBusy() == &csr_voice_prompts_plugin)
    {
        SetAudioBusy(NULL); /* trigger CsrVoicePromptsPluginCleanup() */
    }
}

/****************************************************************************
DESCRIPTION
    Callback called when the voice prompt plugin loses its audio busy lock
    either when CsrVoicePromptsPluginStopPhrase() voluntarily frees it or
    when some other ill-mannered task grabs or frees the lock itself.
*/
void CsrVoicePromptsPluginCleanup (void) 
{
    bool isTone;
    
    if(!phrase_data)
        Panic();
    
    /* store if this is a tone */
    isTone = (phrase_data->decompression == voice_prompts_codec_tone);        
        
    PRINT(("VP: Terminated\n"));

    DisconnectAndCloseSource(phrase_data->source);
    DisconnectAndCloseSource(phrase_data->duplicate_source);    
    
                
    if(phrase_data->mixing)
    {
        /* If DSP already loaded and the prompt was mixed */         
        CsrVoicePromptsPluginStopPhraseMixable();
    }
    else
    {
        /* DSP not previously loaded or the prompt was not mixable type*/          
        CsrVoicePromptsPluginStopPhraseDsp();        
    }

    
    /* Tidy up */
    free(phrase_data);
    phrase_data = NULL;
    SetVpPlaying(FALSE);
    
    if(isTone)
    {
        SetTonePlaying(FALSE);
    }

    MessageCancelAll ((TaskData *) &csr_voice_prompts_plugin,
            AUDIO_PLUGIN_STOP_AUDIO_PROMPT_MSG) ;
    
}

static void DisconnectAndCloseSource(Source source)
{
    if(SourceIsValid(source))
    {
        StreamDisconnect(source, NULL);
        SourceClose(source);
    }
}


/******************************************************************************
DESCRIPTION
    Set the digital and hardware gain as appropriate. The multi-channel library
    takes care of checking which volume control mode has been configured and
    setting either the hardware or digital gain to a fixed level if applicable.
*/
void CsrVoicePromptsPluginSetVolume(int16 prompt_volume, bool using_tone_port)
{
    AUDIO_PLUGIN_SET_MAIN_VOLUME_MSG_T main_vol_msg;
    AUDIO_PLUGIN_SET_AUX_VOLUME_MSG_T aux_vol_msg;
    
    int16 master_volume = MAXIMUM_DIGITAL_VOLUME_0DB;
    
    /* Input is in DAC levels, multi-channel library expects dB/60 values */
    prompt_volume = VolumeConvertDACGainToDB(prompt_volume);
    
    if (!using_tone_port)
    {
        /* Adjust volume level by -6dB */
        prompt_volume += DSP_VOICE_PROMPTS_LEVEL_ADJUSTMENT;
        /* Have to use master volume to control prompt level */
        master_volume = prompt_volume;
    }
    
    /* Fill in and then send DSP volume messages */
    CsrMultiChanGainGetDigital(multi_channel_group_main, master_volume, prompt_volume, (multi_channel_gain_t*)&main_vol_msg);
    CsrMultiChanGainGetDigital(multi_channel_group_aux, master_volume, prompt_volume, (multi_channel_gain_t*)&aux_vol_msg);
     
    KalimbaSendLongMessage(MUSIC_VOLUME_MSG, SIZEOF_AUDIO_PLUGIN_SET_MAIN_VOLUME_MSG, (const uint16*)&main_vol_msg);
    KalimbaSendLongMessage(MUSIC_VOLUME_AUX_MSG, SIZEOF_AUDIO_PLUGIN_SET_AUX_VOLUME_MSG, (const uint16*)&aux_vol_msg);
    
    /* Set hardware gains */
    CsrMultiChanGainSetHardware(multi_channel_group_main, master_volume, NULL);
    CsrMultiChanGainSetHardware(multi_channel_group_aux, master_volume, NULL);
}
