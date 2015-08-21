/****************************************************************************
Copyright (C) Cambridge Silicon Radio Ltd. 2005

FILE NAME
    csr_cvc_common.c
    
DESCRIPTION
NOTES
*/

#ifndef SCO_DSP_BOUNDARIES
#define SCO_DSP_BOUNDARIES
#endif

#include <audio.h>
#include <codec.h>
#include <stdlib.h>
#include <panic.h>
#include <stream.h>
#include <print.h>
#include <kalimba.h>
#include <file.h>
#include <stream.h>     /*for the ringtone_note*/
#include <connection.h> /*for the link_type */
#include <string.h>
#include <kalimba_standard_messages.h>
#include <source.h>
#include <transform.h>
#include <app/vm/vm_if.h>
#include <pblock.h>
#include <ps.h> 

#include "audio_plugin_if.h"        /*for the audio_mode*/
#include "audio_plugin_common.h"
#include "csr_cvc_common_if.h"      /*for things common to all CVC systems*/
#include "csr_cvc_common_plugin.h"
#include "csr_cvc_common.h"
#include "csr_i2s_audio_plugin.h"
#include "csr_multi_channel_plugin.h"

#ifdef ANC
#include "anc.h"
#endif /* ANC */

typedef enum
{
    microphone_input_id_voice_a,
    microphone_input_id_voice_b,
#ifdef ANC
    microphone_input_id_anc_a,
    microphone_input_id_anc_b,
#endif
    microphone_input_id_max
} microphone_input_id_t;

/*helper functions*/
static void connectAudio (CvcPluginTaskdata *task);
static void setMicGain(audio_instance instance, audio_channel channel, bool digital, T_mic_gain gain);

static void connectMic(const audio_channel channel, const audio_mic_params * const params);
static void disconnectMic(const audio_channel channel, const audio_mic_params * const params);
static const audio_channel getAudioChannelFromMicId(const microphone_input_id_t mic_id);
static const audio_mic_params * const getMicParamsFromMicId(const microphone_input_id_t mic_id);
#define connectMicId(mic_id) connectMic(getAudioChannelFromMicId(mic_id), getMicParamsFromMicId(mic_id))
#define disconnectMicId(mic_id) disconnectMic(getAudioChannelFromMicId(mic_id), getMicParamsFromMicId(mic_id))

#define connectMicNoCvc() connectMicId(CVC->mic_for_no_cvc)
#define disconnectMicNoCvc() disconnectMicId(CVC->mic_for_no_cvc)
static void connectOutputNoCvc(void);
static void disconnectOutputNoCvc(void);
static void csrCvcPluginMessageToneComplete(CvcPluginTaskdata* task);

/* Disable all but left and right primary outputs for standard CVC */
#define CVC_DISABLED_OUTPUTS ~(CsrMultiChanGetOutputMask(mch_out_primary_left) | CsrMultiChanGetOutputMask(mch_out_primary_right))
/* Disable all but left primary output for no DSP mode */
#define CVC_NO_DSP_DISABLED_OUTPUTS ~(CsrMultiChanGetOutputMask(mch_out_primary_left))

#define CVC_PLUGIN_IS_ASR(task) ((task->cvc_plugin_variant == CVSD_CVC_1_MIC_HEADSET_ASR) || \
                                 (task->cvc_plugin_variant == CVSD_CVC_2_MIC_HEADSET_ASR) || \
                                 (task->cvc_plugin_variant == CVSD_CVC_1_MIC_HANDSFREE_ASR) || \
                                 (task->cvc_plugin_variant == CVSD_CVC_2_MIC_HANDSFREE_ASR))

#define CVC_PLUGIN_IS_USB()     (CVC->link_type == AUDIO_SINK_USB)


typedef struct audio_Tag
{
    /* vm task to send messages back to */
    TaskData* app_task;
    /*! The codec being used*/
    Task codec_task ; 
    /*! The audio sink being used*/
    Sink audio_sink ;
    /*! The audio source being used*/
    Source audio_source;
    /*! Over the air rate  */
    uint32 incoming_rate;
    /*! Audio rate - used for mic switch */
    uint32 audio_rate;
    /*! Left microphone gain */
    T_mic_gain mic_gain_left;
    /*! Right microphone gain */
    T_mic_gain mic_gain_right;
    const common_mic_params* digital;
    
    /*! The current volume level*/
    unsigned volume:8;
    /*! The current tone volume level*/
    unsigned tone_volume:8;
    
    /*! Indicates current mic/output for no_dsp */
    microphone_input_id_t mic_for_no_cvc:3;
    multi_channel_out_t output_for_no_cvc:3;
    unsigned unused_2:2;

    /*! The current CVC mode */
    AUDIO_MODE_T mode:4 ;
    /*! The link_type being used*/
    AUDIO_SINK_T link_type:4 ;
    /*! CVC extended params */
    cvc_extended_parameters_t ext_params:1;
    /*! Whether or not CVC is running */
    unsigned cvc_running:1 ;
    /*! Set if in low power(CVC off) or no DSP mode*/
    unsigned no_dsp:1 ;
    unsigned production_testing:1;
    /*! is tone mono or stereo*/
    unsigned tone_stereo:1;
    /*! Mute states */
    unsigned mic_muted:1;
    unsigned speaker_muted:1;
    unsigned unused:1;
    
    /*! mono or stereo/use i2s output */
    AudioPluginFeatures features;
}CVC_t ;

/* The CVC task instance pointer*/
static CVC_t * CVC = NULL;

/* dsp message structure*/
typedef struct
{
    uint16 id;
    uint16 a;
    uint16 b;
    uint16 c;
    uint16 d;
} DSP_REGISTER_T;

typedef struct
{
    uint16 id;
    uint16 size;
    char   buf[1];
} DSP_LONG_REGISTER_T;


static void cvcSetupMcParams(multi_channel_params_t* params, bool no_dsp)
{
    memset(params, 0, sizeof(multi_channel_params_t));
    
    if(no_dsp)
    {
        /* In no DSP mode route only the primary left output for I2S/SPDIF */
        params->disable_mask = CVC_NO_DSP_DISABLED_OUTPUTS;
        
        /* Set sample rate. Can't re-sample if DSP is not being used */
        params->sample_rate  = CVC->incoming_rate;
        params->disable_resample = TRUE;
    }
    else
    {
        params->disable_mask = CVC_DISABLED_OUTPUTS;
        params->sample_rate  = CVC->incoming_rate;
    }
}

static const char* csrCvcPluginGetKapFile(CVC_PLUGIN_TYPE_T variant)
{
    switch(variant)
    {
        case CVSD_CVC_1_MIC_HEADSET:
        case CVSD_CVC_1_MIC_HEADSET_BEX:
        case WBS_CVC_1_MIC_HEADSET:
        case CVSD_CVC_1_MIC_HEADSET_ASR:
            return "cvc_headset/cvc_headset.kap";
			
        case CVSD_CVC_2_MIC_HEADSET:
        case CVSD_CVC_2_MIC_HEADSET_BEX:
        case WBS_CVC_2_MIC_HEADSET:
        case CVSD_CVC_2_MIC_HEADSET_ASR:
            return "cvc_headset_2mic/cvc_headset_2mic.kap";

		case CVSD_CVC_1_MIC_HANDSFREE:            
		case CVSD_CVC_1_MIC_HANDSFREE_BEX:
		case WBS_CVC_1_MIC_HANDSFREE:	
        case CVSD_CVC_1_MIC_HANDSFREE_ASR:
			return "cvc_handsfree/cvc_handsfree.kap";		
			
		case CVSD_CVC_2_MIC_HANDSFREE:            
		case CVSD_CVC_2_MIC_HANDSFREE_BEX:
		case WBS_CVC_2_MIC_HANDSFREE:		
        case CVSD_CVC_2_MIC_HANDSFREE_ASR:
			return "cvc_handsfree_2mic/cvc_handsfree_2mic.kap";		

        /* special case to engage re-sampler for I2S outputs */
        case CVSD_NO_DSP:
            return "cvc_headset/cvc_headset.kap";
            
        default:
            Panic() ;
            return NULL;
    }
}

/* Bit set in DSP volume message to indicate digital volume is to be used */
#define DSP_DIG_VOL_FLAG (1 << 4)

/****************************************************************************
NAME    
    send_volume_to_dsp

DESCRIPTION
    Send volume message to DSP

*/
static void send_volume_to_dsp(const uint16 volume)
{
    uint16 digital_dsp = 0;

    if (CsrMultiChanGainGetType(multi_channel_group_main) == multi_channel_gain_digital)
    {
        multi_channel_gain_t gain;

        /* CVC needs to know the fixed system gain, no need to pass master/tone gain
           so set them to zero and call function to get the fixed system gain. */
        CsrMultiChanGainGetDigital(multi_channel_group_main, 0, 0, &gain);

        digital_dsp = DSP_DIG_VOL_FLAG | (gain.common.system & 0xF);
    }
    KalimbaSendMessage(CVC_VOLUME_MSG, 0, digital_dsp, volume, CVC->tone_volume); 

    PRINT(("CVC: Send vol->DSP; vol[0x%x] tone[0x%x] dig[0x%x]\n", volume, CVC->tone_volume, digital_dsp));
}

static bool isResamplingRequired(void)
{
    if(CsrMultiChanConfigRequiresI2s()==FALSE)
    {
        return FALSE;
    }
    return TRUE;
}

static void loadKapFile(const CvcPluginTaskdata * const task)
{
    FILE_INDEX index=0;
    const char* kap_file = NULL ;

    /*ensure that the messages received are from the correct kap file*/
    (void) MessageCancelAll( (TaskData*) task, MESSAGE_FROM_KALIMBA);
    MessageKalimbaTask( (TaskData*) task );

    /* Select which Kap file to be loaded based on the plugin selected */
    kap_file = csrCvcPluginGetKapFile(task->cvc_plugin_variant);
    index = FileFind(FILE_ROOT,(const char *) kap_file ,strlen(kap_file));
    PRINT(("CVC: App File [0x%X] %s\n", index, kap_file));
    PanicFalse(index != FILE_NONE);

    /* Load the cvc algorithm into Kalimba*/
    if(!KalimbaLoad(index))
    {
        PRINT(("CVC: Kalimba load fail\n"));
        Panic();
    }

    /* Now the kap file has been loaded, wait for the CVC_READY_MSG message from the
       dsp to be sent to the message_handler function. */
    SetCurrentDspStatus(DSP_LOADING);
}

static void pluginConnectForProductionTest(CvcPluginTaskdata * task)
{
    CVC->incoming_rate = 8000;

    if(CVC->no_dsp)
    {
        PRINT(("CVC: connect No DSP\n"));

        /* Disable MetaData */
        SourceConfigure(CVC->audio_source,VM_SOURCE_SCO_METADATA_ENABLE,0);

        connectAudio(task) ;

        SetAudioBusy( NULL );
        SetCurrentDspStatus(DSP_NOT_LOADED);
        return;
    }

    CVC->ext_params = CSR_CVC_PSTHRU_ENABLE;

    /* Enable MetaData - not supported for USB*/
    if((CVC->link_type != AUDIO_SINK_USB)&&(CVC->audio_source))
    {
        SourceConfigure(CVC->audio_source,VM_SOURCE_SCO_METADATA_ENABLE,1);
    }

    loadKapFile(task);
}

static void connectAudioForProductionTest(const CvcPluginTaskdata * const task)
{
    if(CVC->audio_sink)
    {
        /* Use plugin default encoder or overwrite if link type is USB */
        LINK_ENCODING_TYPE_T encoder = CVC_PLUGIN_IS_USB() ? LINK_ENCODING_USB : task->encoder;

        /* update the current audio state */
        SetAudioInUse(TRUE);

        connectMicNoCvc();
        connectOutputNoCvc();

        if(CVC->no_dsp)
        {
            /* DSP not required so no need to continue */
            return;
        }

        /* Flag DSP is up and running */
        CVC->cvc_running = TRUE ;

        KalimbaSendMessage(CVC_AUDIO_CONFIG_MSG, encoder, task->sco_config , task->adc_dac_16kHz ? 128 : 64, 0);

        /* check whether SCO is present */
        if(CVC->audio_sink)
        {
            /* connect sco in/out to dsp ports */
            StreamConnect(CVC->audio_source,StreamKalimbaSink(CVC_SCO_IN_PORT)); /* SCO->DSP */
            StreamConnect( StreamKalimbaSource(CVC_SCO_OUT_PORT), CVC->audio_sink ); /* DSP->SCO */
        }

        /* Set passthrough mode */
        KalimbaSendMessage(CVC_SETMODE_MSG, SYSMODE_PSTHRGH, 0, CALLST_CONNECTED, ((CVC->digital->mic_a.digital << 1) | CVC->digital->mic_b.digital));
    }
}

/****************************************************************************
NAME    
    CsrCvcPluginConnect

DESCRIPTION
    This function connects cvc to the stream subsystem

RETURNS
    void
*/
void CsrCvcPluginConnect( CvcPluginTaskdata *task,
                          AUDIO_PLUGIN_CONNECT_MSG_T* connect_msg,
                          Source audio_source)
{
    hfp_common_plugin_params_t* params = (hfp_common_plugin_params_t*)connect_msg->params;
    
    /*signal that the audio is busy until the kalimba / parameters are fully loaded so that no tone messages etc will arrive*/
    SetAudioBusy((TaskData*) task);
  
    PanicNotNull(CVC);
    CVC = PanicUnlessNew ( CVC_t ); 
    
    
    /* The DAC gain must be limited to 0 dB so that no distortion occurs and so the echo canceller works. */
    if (connect_msg->volume > 0xf)
        connect_msg->volume = 0xf;
    
    CVC->app_task        = (TaskData *) connect_msg->app_task;
    CVC->cvc_running     = FALSE;
    CVC->digital         = params ? params->digital : NULL;
    CVC->codec_task      = connect_msg->codec_task;
    CVC->link_type       = connect_msg->sink_type;
    CVC->volume          = connect_msg->volume;
    CVC->audio_sink      = connect_msg->audio_sink;
    CVC->audio_source    = audio_source;
    CVC->mode            = connect_msg->mode;
    CVC->ext_params      = CSR_CVC_HFK_ENABLE;
    CVC->tone_volume     = connect_msg->volume;
    CVC->audio_rate      = connect_msg->rate;
    CVC->features        = connect_msg->features;
    CVC->mic_for_no_cvc = microphone_input_id_voice_a;
    CVC->output_for_no_cvc = mch_out_primary_left;
    CVC->mic_muted       = FALSE;
    CVC->speaker_muted   = FALSE;
    /* Check if this is the no dsp plugin or should be started in low power mode */
    CVC->production_testing = (task->cvc_plugin_variant == CVSD_NO_DSP);
    CVC->no_dsp = FALSE;
    
    if(CVC->production_testing)
    {
        CVC->no_dsp = (isResamplingRequired() == FALSE);
        pluginConnectForProductionTest(task);
        return;
    }

    /* Set clear mic pin */
    AudioPluginSetMicPio(CVC->digital->mic_a, TRUE);
    if(task->two_mic) 
        AudioPluginSetMicPio(CVC->digital->mic_b, TRUE);
    
    /* Don't drop to no DSP if meta data cannot be disabled */
    if(connect_msg->power <= LPIBM_THRESHOLD)
    {
        bool can_disable_meta = (task->encoder != LINK_ENCODING_SBC) && SourceConfigure(CVC->audio_source, VM_SOURCE_SCO_METADATA_ENABLE, 0);
        if(can_disable_meta && CVC->link_type != AUDIO_SINK_USB)
            CVC->no_dsp = TRUE;
        else
            CVC->ext_params = CSR_CVC_PSTHRU_ENABLE;
    }
    
    PRINT(("CVC: connect [%x] [%x] [%x]\n", CVC->cvc_running , (int)CVC->audio_sink, (int)CVC->audio_source));
    
    /* Calculate the DAC rate based on the over-the-air rate value passed in from VM */
    if(CVC->no_dsp)
    {     /* force DAC rate to 8k if in low power mode and not WBS */
        CVC->incoming_rate = 8000;
    }
    else
    {
        /* Set ADC & DAC to 16 or 8 kHz  */
        CVC->incoming_rate = (task->adc_dac_16kHz)?16000:8000;
    }
    
    /* Fow WBS set SBC Frame size, else sample-based */
    if(((CVC_PLUGIN_TYPE_T)task->encoder) == LINK_ENCODING_SBC)
    {
        SinkConfigure(CVC->audio_sink,VM_SINK_SCO_SET_FRAME_LENGTH,60); 
    }

    /* If in no DSP mode then just connect the ports, if this is cVc then continue and load the DSP */
    if(CVC->no_dsp)
    {
        PRINT(("CVC: connect No DSP\n"));

        /* Disable MetaData */
        SourceConfigure(CVC->audio_source,VM_SOURCE_SCO_METADATA_ENABLE,0);

        connectAudio (task) ;

        CsrCvcPluginSetVolume(CVC->volume);
        SetAudioBusy( NULL );
        SetCurrentDspStatus(DSP_NOT_LOADED);
        return;
    }

    /* Enable MetaData - not supported for USB*/
    if((CVC->link_type != AUDIO_SINK_USB)&&(CVC->audio_source))
    {
        SourceConfigure(CVC->audio_source,VM_SOURCE_SCO_METADATA_ENABLE,1);
    }

    loadKapFile(task);

}


/****************************************************************************
NAME    
    CsrCvcPluginDisconnect

DESCRIPTION
    Disconnect CVC and power off the Kalimba DSP core
    
RETURNS
    void
*/
void CsrCvcPluginDisconnect( CvcPluginTaskdata *task )
{
    PanicNull(CVC);
    
    if(CVC->no_dsp)
    {
        PRINT(("CVC: NO DSP: disconnect\n"));
        /* Disconnect speakers */
        disconnectOutputNoCvc();
        /* disconnect the microphones */
        disconnectMicNoCvc();
    }
    else
    {
        Source mic_source_a = NULL;
        Source mic_source_b = NULL;
        
        Source kal_source = StreamKalimbaSource(CVC_PLUGIN_IS_USB() ? CVC_USB_OUT_PORT : CVC_SCO_OUT_PORT);
        
        /* check cvc running */
        PanicFalse(CVC->cvc_running);
        
        /* Disconnect speakers */
        PanicFalse(CsrMultiChanDisconnect());

#ifdef ANC
        /* Ensure ANC microphones are disconnected */
        AncDisconnectMics();
#endif /* ANC */

        PRINT(("CVC: Destroy transforms\n")); 

        /* disconnect left mic channel */
        mic_source_a = AudioPluginGetMic(AudioPluginGetInstance(CVC->digital->mic_a),
                                         AUDIO_CHANNEL_A, CVC->digital->mic_a.digital);

        /* disconnect the streams */
        StreamDisconnect(mic_source_a, StreamKalimbaSink(CVC_LEFT_IN_PORT)); 
        
        /* ensure sources are closed */
        SourceClose(mic_source_a);

        /* for the two mic variant disconnect the second microphone */
        if( task->two_mic )
        {
            mic_source_b = AudioPluginGetMic(AudioPluginGetInstance(CVC->digital->mic_b),
                                             AUDIO_CHANNEL_B, CVC->digital->mic_b.digital);
            StreamDisconnect(mic_source_b, StreamKalimbaSink(CVC_RIGHT_IN_PORT));  
            SourceClose(mic_source_b);
        }

        /* disconnect the in and out sco ports */
        StreamDisconnect(CVC->audio_source,StreamKalimbaSink(CVC_SCO_IN_PORT)); /* SCO->DSP */  
        StreamDisconnect(kal_source, CVC->audio_sink ); /* DSP->SCO/USB */
        
        PRINT(("CVC: Disconnected\n"));
    }
    
    CVC->cvc_running = FALSE;    
    CVC->audio_sink = NULL;
    CVC->link_type = 0;
    
    /* Cancel any outstanding cvc messages */
    MessageCancelAll( (TaskData*)task , MESSAGE_FROM_KALIMBA);
    MessageCancelAll( (TaskData*)task , MESSAGE_STREAM_DISCONNECT);
    MessageCancelAll( CVC->app_task , CSR_SR_WORD_RESP_UNKNOWN);
    MessageCancelAll( CVC->app_task , CSR_SR_WORD_RESP_YES);
    MessageCancelAll( CVC->app_task , CSR_SR_WORD_RESP_NO);
    MessageCancelAll( CVC->app_task , CSR_SR_WORD_RESP_FAILED_YES);
    MessageCancelAll( CVC->app_task , CSR_SR_WORD_RESP_FAILED_NO);
    
    /* Turn off Digital Mic PIO */
    AudioPluginSetMicPio(CVC->digital->mic_a, FALSE);
    if(task->two_mic) 
        AudioPluginSetMicPio(CVC->digital->mic_b, FALSE);

    free (CVC);
    CVC = NULL;
    
    KalimbaPowerOff();
    
    /* update current dsp status */
    SetCurrentDspStatus( DSP_NOT_LOADED );
    /* update the current audio state */
    SetAudioInUse(FALSE);
    SetAsrPlaying(FALSE);
}

/****************************************************************************
NAME    
    CsrCvcPluginSetVolume

DESCRIPTION
    Tell CVC to update the volume.

RETURNS
    void
*/
void CsrCvcPluginSetVolume(uint16 volume )
{
    PanicNull(CVC);
    
    /* The DAC gain must be limited to 0 dB so that no distortion occurs and so the echo canceller works. */
    if (volume > 0xf)
        volume = 0xf;

    CVC->volume = volume;
    
    if(CVC->no_dsp)
    {
        int16 master_vol = VolumeConvertDACGainToDB(CVC->volume);
        PRINT(("CVC: NO DSP: Set volume %d (%d dB/60)\n", volume, master_vol));
        /*Set the output Gain immediately*/
        CsrMultiChanGainSetHardwareOnly(multi_channel_group_main, master_vol);
        if(CVC->production_testing)
        {
            CsrMultiChanGainSetHardwareOnly(multi_channel_group_aux, master_vol);
        }
        return;
    }
    
    PRINT(("CVC: DAC GAIN SET[%x]\n", CVC->volume ));
    
    /* Only update the volume if not in a mute mode */
    if ( CVC->cvc_running && !(CVC->speaker_muted) )
    { 
        send_volume_to_dsp(CVC->volume);
    }
}

/****************************************************************************
NAME    
    CsrCvcPluginResetVolume

DESCRIPTION
    reset the volume back to stored values 

RETURNS
    void
*/
void CsrCvcPluginResetVolume( void )
{
    /* Only update the volume if not in a mute mode */
    if ( CVC && CVC->cvc_running && !(CVC->speaker_muted) )
    { 
        send_volume_to_dsp(CVC->volume);
    }    
}

/****************************************************************************
NAME
    CsrCvcPluginSetModeNoDsp

DESCRIPTION
    Set the CSR_COMMON_NO_DSP mode

RETURNS
    void
*/
void CsrCvcPluginSetModeNoDsp ( AUDIO_MODE_T mode )
{
    PRINT(("CsrCvcPluginSetModeNoDsp mode = %d\n",mode));

    switch (mode)
    {
        case AUDIO_MODE_CONNECTED :
        {
            PRINT(("CVC: NODSP: Set Mode CONNECTED\n"));
            connectMicNoCvc();
            connectOutputNoCvc();
        }
        break ;
        case AUDIO_MODE_STANDBY:
        {
            PRINT(("CVC: NODSP: Set Mode STANDBY\n"));
        }
        break ;
        case AUDIO_MODE_MUTE_MIC:
        case AUDIO_MODE_MUTE_SPEAKER:
        case AUDIO_MODE_MUTE_BOTH:
        case AUDIO_MODE_UNMUTE_SPEAKER:
        {
            PRINT(("CVC: NODSP: *** Muting via SET_MODE_MSG is deprecated ***\n"));
            PRINT(("CVC: NODSP: Use SET_SOFT_MUTE_MSG instead\n"));
            Panic();
        }
        default :
        {    
            PRINT(("CVC: NODSP: Set Mode Invalid [0x%x]\n" , mode )) ;
        }
        break ;
    }
}

/****************************************************************************
NAME    
    CsrCvcPluginSetSoftMuteNoDsp

DESCRIPTION
    Set the CSR_COMMON_NO_DSP mute states

RETURNS
    void
*/
void CsrCvcPluginSetSoftMuteNoDsp(AUDIO_PLUGIN_SET_SOFT_MUTE_MSG_T* message)
{
    bool mute_mic = FALSE;
    bool mute_speaker = FALSE;
    
    if (message->mute_states & AUDIO_MUTE_MASK(audio_mute_group_main))
        mute_speaker = TRUE;
    
    if (message->mute_states & AUDIO_MUTE_MASK(audio_mute_group_mic))
        mute_mic = TRUE;
    
    if (CVC->speaker_muted != mute_speaker)
    {
        if (mute_speaker)
            disconnectOutputNoCvc();
        else
            connectOutputNoCvc();
            
        CVC->speaker_muted = mute_speaker;
    }
    
    if (CVC->mic_muted != mute_mic)
    {
        if (mute_mic)
            disconnectMicNoCvc();
        else
            connectMicNoCvc();
            
        CVC->mic_muted = mute_mic;
    }
}


/****************************************************************************
NAME    
    CsrCvcPluginSetMode

DESCRIPTION
    Set the CVC mode

RETURNS
    void
*/
void CsrCvcPluginSetMode ( CvcPluginTaskdata *task, AUDIO_MODE_T mode , const void * params )
{
    /* pre-initialise with the most common parameters and adjust below as necessary */
    uint16 sysmode;
    uint16 call_state = CALLST_CONNECTED;
    uint16 volume;
    
    PRINT(("CsrCvcPluginSetMode mode = %d\n",mode));
    
    /* ensure CVC is valid and this is not a stale message left in the queue at disconnect */
    if(CVC)
    {
    
/* when using aptx dsp app with wbs back channel check for external mic support */    
#ifdef REMOVABLE_MIC 
        if (params)
        {
            /* if mode parameters supplied then use these */
            CVCPluginModeParams * mode_params = (CVCPluginModeParams *)params;
            
            /* external microphone connected */
            if(mode_params->external_mic_settings == EXTERNAL_MIC_FITTED)
            {
                /* choose pskey base address according to NB or WB dsp app */
                switch(task->cvc_plugin_variant)
                {
                    case CVSD_CVC_1_MIC_HEADSET:
                        PRINT(("CVC: CVC_LOADPARAMS_MSG pskey[%x] mode[%x]\n",CVC_1MIC_PS_BASE_EXT_MIC_FITTED,CVC_SR_NB));
                        KalimbaSendMessage(CVC_LOADPARAMS_MSG, CVC_1MIC_PS_BASE_EXT_MIC_FITTED, CVC_SR_NB, 0, 0);
                    break;
                     
                    case WBS_CVC_1_MIC_HEADSET:
                        PRINT(("CVC: CVC_LOADPARAMS_MSG pskey[%x] mode[%x]\n",CVC_1MIC_PS_BASE_WBS_EXT_MIC_FITTED,CVC_SR_WB));
                        KalimbaSendMessage(CVC_LOADPARAMS_MSG, CVC_1MIC_PS_BASE_WBS_EXT_MIC_FITTED, CVC_SR_WB, 0, 0);
                    break;
                }
            } 
            /* external microphone not connected */
            else
            {
                /* choose pskey base address according to NB or WB dsp app */
                switch(task->cvc_plugin_variant)
                {
                    case CVSD_CVC_1_MIC_HEADSET:
                        PRINT(("CVC: CVC_LOADPARAMS_MSG pskey[%x] mode[%x]\n",CVC_1MIC_PS_BASE_EXT_MIC_NOT_FITTED,CVC_SR_NB));
                        KalimbaSendMessage(CVC_LOADPARAMS_MSG, CVC_1MIC_PS_BASE_EXT_MIC_NOT_FITTED, CVC_SR_NB, 0, 0);
                    break;
                 
                    case WBS_CVC_1_MIC_HEADSET:
                        PRINT(("CVC: CVC_LOADPARAMS_MSG pskey[%x] mode[%x]\n",CVC_1MIC_PS_BASE_WBS_EXT_MIC_NOT_FITTED,CVC_SR_WB));
                        KalimbaSendMessage(CVC_LOADPARAMS_MSG, CVC_1MIC_PS_BASE_WBS_EXT_MIC_NOT_FITTED, CVC_SR_WB, 0, 0);
                    break;
                }
            }
        }            
#endif    
            
        /* Store current mode */
        CVC->mode = mode;
    
        /* check if in no dsp mode */
        if(CVC->no_dsp)
        {
            CsrCvcPluginSetModeNoDsp(mode) ;
            return;
        }

        PanicFalse(CVC->cvc_running);
        
        volume  = CVC->volume;
        sysmode = (CVC->ext_params == CSR_CVC_HFK_ENABLE) ? SYSMODE_HFK : SYSMODE_PSTHRGH;
    
        /* if using ASR feature, start it running */
        if((task->cvc_plugin_variant == CVSD_CVC_1_MIC_HEADSET_ASR)||(task->cvc_plugin_variant == CVSD_CVC_2_MIC_HEADSET_ASR)||
           (task->cvc_plugin_variant == CVSD_CVC_1_MIC_HANDSFREE_ASR)||(task->cvc_plugin_variant == CVSD_CVC_2_MIC_HANDSFREE_ASR))
        {
            PRINT(("CVC: SETMODE ASR: vol=%d\n", volume));

            /*send update to kalimba */ 
            KalimbaSendMessage(CVC_SETMODE_MSG, SYSMODE_ASR, 0, CALLST_CONNECTED, ( CVC->digital->mic_a.digital << 1 ) | CVC->digital->mic_b.digital );
            send_volume_to_dsp(volume);
        }
        /* for all modes excluding ASR mode */
        else
        {              
            switch (CVC->mode)
            {
                case AUDIO_MODE_CONNECTED:
                {

                }
                break ;
                case AUDIO_MODE_STANDBY:
                {
                    sysmode = SYSMODE_STANDBY;
                    call_state = 0;
                    volume = DAC_MUTE;
                }
                break;
                case AUDIO_MODE_MUTE_MIC:
                case AUDIO_MODE_MUTE_SPEAKER:
                case AUDIO_MODE_MUTE_BOTH:
                case AUDIO_MODE_UNMUTE_SPEAKER:
                {
                    PRINT(("CVC: *** Muting via SET_MODE_MSG is deprecated ***\n"));
                    PRINT(("CVC: Use SET_SOFT_MUTE_MSG instead\n"));
                    Panic();
                }
                default:
                {
                /*do not send a message*/
                    PRINT(("CVC: Set Mode Invalid [0x%x]\n" , mode ));
                    return;
                }
            }
        
            /*send update to kalimba */
            PRINT(("CVC: SYSMODE 0x%x, CALLSTATE 0x%x, VOL 0x%x\n", sysmode, call_state, volume));
            KalimbaSendMessage(CVC_SETMODE_MSG, sysmode, 0, call_state, ( CVC->digital->mic_a.digital << 1 ) | CVC->digital->mic_b.digital );
            send_volume_to_dsp(volume);
        }                
    }
}

/****************************************************************************
NAME    
    CsrCvcPluginSetSoftMute

DESCRIPTION
    Set the mute states

RETURNS
    void
*/
void CsrCvcPluginSetSoftMute(AUDIO_PLUGIN_SET_SOFT_MUTE_MSG_T* message)
{
    if (!CVC)
        return;
        
    /* Check if in no dsp mode */
    if(CVC->no_dsp)
    {
        CsrCvcPluginSetSoftMuteNoDsp(message);
    }
    else
    {
        bool mute_mic = FALSE;
        bool mute_speaker = FALSE;
        bool send_mode_msg = FALSE;
        
        uint16 sysmode = (CVC->ext_params == CSR_CVC_HFK_ENABLE)? SYSMODE_HFK : SYSMODE_PSTHRGH;
        
        PanicFalse(CVC->cvc_running);
        
        if (message->mute_states & AUDIO_MUTE_MASK(audio_mute_group_main))
            mute_speaker = TRUE;
        
        if (message->mute_states & AUDIO_MUTE_MASK(audio_mute_group_mic))
            mute_mic = TRUE;
        
        /* If both mic and speaker muted, can enter standby mode */
        if (mute_mic && mute_speaker)
            sysmode = SYSMODE_STANDBY;
        
        if (CVC->mic_muted != mute_mic)
        {
            /* Mic mute state changing, need to change call state, so need to send
               mode message. Also if speaker muted, need to enter/exit standby mode. */
            send_mode_msg = TRUE;
            
            CVC->mic_muted = mute_mic;
        }
        
        if (CVC->speaker_muted != mute_speaker)
        {
            /* Speaker mute state changing, need to set volume */
            send_volume_to_dsp(mute_speaker? DAC_MUTE : CVC->volume);
            
            /* If speaker changing AND mic muted, need to enter/exit standby mode */
            if (mute_mic)
                send_mode_msg = TRUE;
                
            CVC->speaker_muted = mute_speaker;
        }
        
        /* Change DSP mode only if necessary (changing call state or entering/exiting standby mode) */
        if (send_mode_msg)
            KalimbaSendMessage(CVC_SETMODE_MSG, sysmode, 0, (mute_mic? CALLST_MUTE : CALLST_CONNECTED), ((CVC->digital->mic_a.digital << 1) | CVC->digital->mic_b.digital));
        
        PRINT(("CVC: SYSMODE 0x%x, CALLSTATE 0x%x, VOL 0x%x\n", sysmode, (mute_mic? CALLST_MUTE : CALLST_CONNECTED), (mute_speaker? DAC_MUTE : CVC->volume)));
    }
}

/****************************************************************************
NAME    
    CsrCvcPluginPlayTone

DESCRIPTION

    queues the tone if can_queue is TRUE and there is already a tone playing

RETURNS
    false if a tone is already playing
    
*/
void CsrCvcPluginPlayTone (CvcPluginTaskdata *task, ringtone_note * tone , uint16 tone_volume)  
{
    Sink lSink ; 
    Source lSource = StreamRingtoneSource( (const ringtone_note *) (tone) );
    
    PanicNull(CVC);

    PRINT(("CVC: Tone Start\n"));
    
    if(CVC->no_dsp)
    {
        multi_channel_params_t params;
        /* Use the tone volume if present */
        uint16 sys_vol = tone_volume ? tone_volume : CVC->volume;
        
        if ( CVC->audio_sink )
            disconnectOutputNoCvc();
        
        /* Connect the tone source direct to left primary output */
        cvcSetupMcParams(&params, TRUE);
        /* Automatically dispose tone source on early disconnect */
        params.transform = mch_transform_connect_and_dispose;
        PanicFalse(CsrMultiChanConnectStereoSource(lSource, NULL, &params));
        
        MessageSinkTask( CsrMultiChanGetAudioSink() , (TaskData*) task );
        
        /* Set gain using multi-channel lib */
        CsrMultiChanGainSetHardwareOnly(multi_channel_group_main, 
                                        VolumeConvertDACGainToDB(sys_vol));
        
        return;
    }
    
    /*check cvc running */
    PanicFalse(CVC->cvc_running);
    
    /* when mixing tones with ASR, mute the microphone as currently no echo removal */
    if(CVC_PLUGIN_IS_ASR(task))
    {   
        /* set gain to 0 */ 
        T_mic_gain input_gain;
        memset(&input_gain,0,sizeof(T_mic_gain));
        
        PRINT(("CVC: Mute Mic for tone play with ASR\n"));

           /* Set input gain(s) */
            setMicGain(AudioPluginGetInstance(CVC->digital->mic_a),
                         AUDIO_CHANNEL_A, CVC->digital->mic_a.digital, input_gain);
            if( task->two_mic )
                setMicGain(AudioPluginGetInstance(CVC->digital->mic_b),
                             AUDIO_CHANNEL_B, CVC->digital->mic_b.digital, input_gain);
        }       

    /* The DAC gain must be limited to 0 dB so that no distortion occurs and so the echo canceller works. */
    if (tone_volume > 0xf)
        tone_volume = 0xf;

    /* Configure prompt playback, indicate that all firmware tones are mono*/    
    KalimbaSendMessage(MESSAGE_SET_TONE_RATE_MESSAGE_ID, 8000 , 0/*Mono Bit 0 =0, TONE BIT 1 = 0*/, 0, 0);             

    /* set DAC gain to a suitable level for tone play */
    if (tone_volume != CVC->tone_volume)
    {
        CVC->tone_volume = tone_volume;
        send_volume_to_dsp(CVC->volume);
    }

    lSink = StreamKalimbaSink(TONE_VP_MIXING_DSP_PORT);
    
    /*request an indication that the tone has completed / been disconnected*/
    MessageSinkTask ( lSink , (TaskData*) task );
 
    /* connect the tone (mix the tone if this is CVC) */    
    PanicFalse( StreamConnectAndDispose( lSource , lSink ) );
}

/****************************************************************************
NAME    
    CsrCvcPluginStopTone

DESCRIPTION
    Stop a tone from playing

RETURNS
    whether or not the tone was stopped successfully
*/
void CsrCvcPluginStopTone ( CvcPluginTaskdata *task ) 
{
    PRINT(("CVC: Stop Tone\n"));
    PanicNull(CVC);
        
    if(CVC->no_dsp)
    {
        disconnectOutputNoCvc() ;
        CsrCvcPluginSetModeNoDsp(CVC->mode);
    }    
    else
    {
        StreamDisconnect( 0 , StreamKalimbaSink(TONE_VP_MIXING_DSP_PORT) ) ; 

        /* when mixing tones with ASR, restore mic volume settins once tone is complete */
        if((task->cvc_plugin_variant == CVSD_CVC_1_MIC_HEADSET_ASR)||(task->cvc_plugin_variant == CVSD_CVC_2_MIC_HEADSET_ASR)||
           (task->cvc_plugin_variant == CVSD_CVC_1_MIC_HANDSFREE_ASR)||(task->cvc_plugin_variant == CVSD_CVC_2_MIC_HANDSFREE_ASR))
        {        
            /* restore microphone gain */
            CsrCvcPluginResetVolume();
        }       

    }
    /* update current tone playing status */
    SetTonePlaying(FALSE);

}

/****************************************************************************
DESCRIPTION
    Set mic gain
*/
static void setMicGain(audio_instance instance, audio_channel channel, bool digital, T_mic_gain gain)
{
    Source mic_source = AudioPluginGetMic(instance, channel, digital);
    uint8 mic_gain = (digital ? gain.digital_gain : gain.analogue_gain);
    AudioPluginSetMicGain(mic_source, digital, mic_gain, gain.preamp_enable);
}

static uint32 getVoiceOutputSampleRate(void)
{
    if(CsrMultiChanConfigRequiresI2s())
    {
        uint32 output_rate = CsrI2SVoiceResamplingFrequency();
        if(output_rate != I2S_NO_RESAMPLE)
        {
            return output_rate;
        }
    }
    return CVC->incoming_rate;
}

/****************************************************************************
DESCRIPTION
    Connect the audio stream (Speaker and Microphone)
*/ 
static void connectAudio (CvcPluginTaskdata *task)
{
    if(CVC->production_testing)
    {
        connectAudioForProductionTest(task);
    }
    else if ((CVC->audio_sink != NULL) || CVC_PLUGIN_IS_ASR(task))
    {
        uint16 adc_rate;
        Source mic_source_a = NULL;
        Source mic_source_b = NULL;
        multi_channel_params_t params;
        
        /* Default to hardware rate matching for DAC outputs */
        uint16 rate_matching = RATE_MATCH_HARDWARE_MASK;
        
        /* Use plugin default encoder or overwrite if link type is USB */
        LINK_ENCODING_TYPE_T encoder = CVC_PLUGIN_IS_USB() ? LINK_ENCODING_USB : task->encoder;
    
        /* Set up params, initially to work out ADC rate */
        cvcSetupMcParams(&params, FALSE);

        /* bandwidth extension variants require different adc rate to output sample rate */
        if((task->cvc_plugin_variant==CVSD_CVC_2_MIC_HEADSET_BEX)||(task->cvc_plugin_variant==CVSD_CVC_2_MIC_HANDSFREE_BEX))
            params.sample_rate = 8000;
        
        adc_rate = CsrMultiChannelGetSampleRate(&params);    
        
        /* update the current audio state */
        SetAudioInUse(TRUE);
        
        PRINT(("CVC: Use i2s input? %x\n",CVC->features.audio_input_routing == AUDIO_ROUTE_I2S));
        switch(CVC->features.audio_input_routing)
        {
			case AUDIO_ROUTE_INTERNAL:
				/* Configure mic A */
				mic_source_a = AudioPluginGetMic(AudioPluginGetInstance(CVC->digital->mic_a),
                                                 AUDIO_CHANNEL_A, CVC->digital->mic_a.digital);

                /* match input and output rates when using resampling */
                AudioPluginSetMicRate(mic_source_a, CVC->digital->mic_a.digital, adc_rate);

				/* configure mic B if applicable for 2 mic operation */
				if( task->two_mic )
				{
					PRINT(("CVC: Connect PCM source 2\n"));
					/* Configure mic B */
					mic_source_b = AudioPluginGetMic(AudioPluginGetInstance(CVC->digital->mic_b),
                                                     AUDIO_CHANNEL_B, CVC->digital->mic_b.digital);
                    /* match input and output rates when using resampling */
                    AudioPluginSetMicRate(mic_source_b, CVC->digital->mic_b.digital, adc_rate);
                    
					/* synchronise both mics A and B */
					SourceSynchronise(mic_source_a, mic_source_b);
                    /* Connect mic A to DSP ports */
                    PanicFalse(StreamConnect(mic_source_a, StreamKalimbaSink(CVC_LEFT_IN_PORT)));
                    /* if 2 mic enabled then connect Mic B */
                    if(task->two_mic)
                    {
                        /* Connect mic/speaker B to DSP ports */
                        PanicFalse(StreamConnect(mic_source_b, StreamKalimbaSink(CVC_RIGHT_IN_PORT)));
                    }
				}
                /* 1 mic, connect left mic only */
                else
                {   
                    /* Connect mic A to DSP ports */
                    if(!CVC->no_dsp)
                    {
                        PanicFalse(StreamConnect(mic_source_a, StreamKalimbaSink(CVC_LEFT_IN_PORT)));
                    }
                }
                break;
            case AUDIO_ROUTE_I2S:
				if( task->two_mic )
                    CsrI2SAudioInputConnect(CsrI2SVoiceResamplingFrequency(), TRUE, StreamKalimbaSink(CVC_LEFT_IN_PORT), StreamKalimbaSink(CVC_RIGHT_IN_PORT) );
                else
                    CsrI2SAudioInputConnect(CsrI2SVoiceResamplingFrequency(), FALSE, StreamKalimbaSink(CVC_LEFT_IN_PORT), NULL );
                break;
            case AUDIO_ROUTE_SPDIF:
            case AUDIO_ROUTE_INTERNAL_AND_RELAY:
                {   /* Not currently supported */
                }
                break;
        }

#ifdef ANC
        /* ANC requires digital volume control and therefore the DSP to be running */
        PanicFalse(!CVC->no_dsp);

        /* Attempt to connect ANC microphones */
        AncConnectMics(ANC_MIC_A_IN_PORT, ANC_MIC_B_IN_PORT);
#else /* ANC */

        /* Handle no DSP as special case */
        if(CVC->audio_sink && CVC->no_dsp)
        {
            /* Call set mode to connect DSP */
            CsrCvcPluginSetModeNoDsp(CVC->mode);

            /* Set hardware gain */
            CsrMultiChanGainSetHardwareOnly(multi_channel_group_main,
                                            VolumeConvertDACGainToDB(CVC->volume));
            return;
        }
#endif /* ANC */

        /* Now set the DAC rate */
        params.sample_rate = getVoiceOutputSampleRate();

        /* Connect DSP - note sample rate may be updated if re-sampling
           is required for outputs used */
        PanicFalse(CsrMultiChanConnectDsp(&params));
        
        /* Flag DSP is up and running */
        CVC->cvc_running = TRUE ;

        PRINT(("CVC: AUDIO_CONFIG_MSG 0x%x config 0x%x %s\n", encoder, task->sco_config, task->adc_dac_16kHz ? "16kHz" : "8kHz"));
        KalimbaSendMessage(CVC_AUDIO_CONFIG_MSG, encoder, task->sco_config , task->adc_dac_16kHz ? 128 : 64, 0);
        
        /* check whether SCO is present */
        if(CVC->audio_sink)
        {
            /* connect sco in/out to dsp ports */
            StreamConnect(CVC->audio_source,StreamKalimbaSink(CVC_SCO_IN_PORT)); /* SCO->DSP */  
            
            if(CVC_PLUGIN_IS_USB())
                StreamConnect( StreamKalimbaSource(CVC_USB_OUT_PORT), CVC->audio_sink ); /* DSP->USB */
            else
                StreamConnect( StreamKalimbaSource(CVC_SCO_OUT_PORT), CVC->audio_sink ); /* DSP->SCO */
        }

#ifdef ANC
        if (AncGetDacSampleRate() != 0)
        {
            PRINT(("CVC: ANC in use\n"));
            params.sample_rate = AncGetDacSampleRate();
            
            /* Always use use software rate matching when ANC in use */
            rate_matching = RATE_MATCH_SOFTWARE_MASK;
        }
#endif /* ANC */

        /* Always use use software rate matching when I2S in use */
        if(CsrMultiChanI2sActive())
            rate_matching = RATE_MATCH_SOFTWARE_MASK;

        /* The DSP must know the sampling rate for the ADC and DAC  (rate value sent = actual rate/10) */
        PRINT(("CVC: SET_SAMPLE_RATE rate[%ld] rate_match[%x] interface[%x]\n",params.sample_rate / 10, rate_matching, 
                                                                               CsrMultiChanI2sActive() ? CVC_INTERFACE_I2S : CVC_INTERFACE_ANALOG));
        
        if(!KalimbaSendMessage(MESSAGE_SET_ADCDAC_SAMPLE_RATE_MESSAGE_ID, 
                               params.sample_rate / 10, rate_matching, 
                               CsrMultiChanI2sActive() ? CVC_INTERFACE_I2S : CVC_INTERFACE_ANALOG, 
                               adc_rate))
        {
            PRINT(("CVC: Message MESSAGE_SET_ADCDAC_SAMPLE_RATE_MESSAGE_ID failed!\n"));
            Panic();
        }
        
        /* Set the mode */
        CsrCvcPluginSetMode ( task, CVC->mode , NULL );
        
        /* if using ASR feature, start it running */
        if(CVC_PLUGIN_IS_ASR(task))
        {
            KalimbaSendMessage(ASR_START,0,0,0,0);
            PRINT(("ASR running msg %x busy [%x]\n",ASR_START,(uint16)IsAudioBusy()));
            /* update the current audio state */
            SetAsrPlaying(TRUE);
        }
    }
    else
    {   
        CVC->cvc_running = TRUE ;
        /*Power Down*/
        CsrCvcPluginDisconnect(task);
    }
}

/****************************************************************************
DESCRIPTION
    Handles a CVC_CODEC message received from CVC
*/
static void codecMessage (CvcPluginTaskdata *task, T_mic_gain input_gain_l, T_mic_gain input_gain_r, uint16 output_gain )
{   
    PRINT(("CVC: Output gain = 0x%x\n" , output_gain ));
    PRINT(("CVC: Input gain L:R = 0x%x : 0x%x \n", *(uint16*)&input_gain_l,*(uint16*)&input_gain_r));

    /* check pointer validity as there is a very small window where a message arrives
       as the result of playing a tone after CVC has been powered down */
    if(CVC)
    {
        /* Set output volume level */
        CsrMultiChanGainSetHardwareOnly(multi_channel_group_main, VolumeConvertDACGainToDB(output_gain));
        if(CVC->production_testing)
        {
            CsrMultiChanGainSetHardwareOnly(multi_channel_group_aux, VolumeConvertDACGainToDB(output_gain));
        }
    
        /* Set input gain(s) */
        setMicGain(AudioPluginGetInstance(CVC->digital->mic_a),
                      AUDIO_CHANNEL_A, CVC->digital->mic_a.digital, input_gain_l);
        if( task->two_mic ) 
            setMicGain(AudioPluginGetInstance(CVC->digital->mic_b),
                          AUDIO_CHANNEL_B, CVC->digital->mic_b.digital, input_gain_r);
    }
}


/****************************************************************************
DESCRIPTION
    handles the internal cvc messages /  messages from the dsp
*/
void CsrCvcPluginInternalMessage( CvcPluginTaskdata *task ,uint16 id , Message message ) 
{
    switch(id)
    {
        case MESSAGE_FROM_KALIMBA:
        {
            const DSP_REGISTER_T *m = (const DSP_REGISTER_T *) message;
            PRINT(("CVC: msg id[%x] a[%x] b[%x] c[%x] d[%x]\n", m->id, m->a, m->b, m->c, m->d));
        
            switch ( m->id ) 
            {
                case CVC_READY_MSG:
                {
                    /* determine PSKEY base address for tuning parameters, CVC 1 mic and SSR use a
                       different base address to allow coexistance with CVC 2 mic */
                    switch(task->cvc_plugin_variant)
                    {
#ifndef REMOVABLE_MIC
                        case CVSD_CVC_1_MIC_HEADSET:
                        case WBS_CVC_1_MIC_HEADSET:
                            if(CVC->incoming_rate == 8000)
                            {
                                PRINT(("CVC: CVC_LOADPARAMS_MSG pskey[%x] mode[%x]\n",CVC_1MIC_PS_BASE,CVC_SR_NB));
                                KalimbaSendMessage(CVC_LOADPARAMS_MSG, CVC_1MIC_PS_BASE, CVC_SR_NB, 0, 0);
                            }
                            else if (CVC->incoming_rate == 16000)
                            {
                                PRINT(("CVC: CVC_LOADPARAMS_MSG pskey[%x] mode[%x]\n",CVC_1MIC_PS_BASE_WBS,CVC_SR_WB));
                                KalimbaSendMessage(CVC_LOADPARAMS_MSG, CVC_1MIC_PS_BASE_WBS, CVC_SR_WB, 0, 0);
                            }
                            else
                            {
                                PRINT(("CVC: Unknown dac_rate.\n"));
                                Panic();
                            }
                        break;
#else
                        case CVSD_CVC_1_MIC_HEADSET:
                            PRINT(("CVC: CVC_LOADPARAMS_MSG pskey[%x] mode[%x]\n",CVC_1MIC_PS_BASE_EXT_MIC_NOT_FITTED,CVC_SR_NB));
                            KalimbaSendMessage(CVC_LOADPARAMS_MSG, CVC_1MIC_PS_BASE_EXT_MIC_NOT_FITTED, CVC_SR_NB, 0, 0);
                        break;
                 
                        case WBS_CVC_1_MIC_HEADSET:
                            PRINT(("CVC: CVC_LOADPARAMS_MSG pskey[%x] mode[%x]\n",CVC_1MIC_PS_BASE_WBS_EXT_MIC_NOT_FITTED,CVC_SR_WB));
                            KalimbaSendMessage(CVC_LOADPARAMS_MSG, CVC_1MIC_PS_BASE_WBS_EXT_MIC_NOT_FITTED, CVC_SR_WB, 0, 0);                    
                        break;
#endif
                        case CVSD_CVC_1_MIC_HEADSET_BEX:
                            PRINT(("CVC: CVC_LOADPARAMS_MSG pskey[%x] mode[%x]\n",CVC_1MIC_PS_BASE,CVC_SR_BEX));
                            KalimbaSendMessage(CVC_LOADPARAMS_MSG, CVC_1MIC_PS_BASE, CVC_SR_BEX, 0, 0);
                        break;
                        
                        case CVSD_CVC_2_MIC_HEADSET_BEX:
                            PRINT(("CVC: CVC_LOADPARAMS_MSG pskey[%x] mode[%x]\n",CVC_2MIC_PS_BASE,CVC_SR_BEX));
                            KalimbaSendMessage(CVC_LOADPARAMS_MSG, CVC_2MIC_PS_BASE, CVC_SR_BEX, 0, 0);
                        break;

                        case CVSD_CVC_1_MIC_HANDSFREE_BEX:
                            PRINT(("CVC: CVC_LOADPARAMS_MSG pskey[%x] mode[%x]\n",CVC_2MIC_PS_BASE,CVC_SR_BEX));
                            KalimbaSendMessage(CVC_LOADPARAMS_MSG, CVC_2MIC_PS_BASE, CVC_SR_BEX, 0, 0);
                        break;

                        case CVSD_CVC_2_MIC_HANDSFREE_BEX:
                            PRINT(("CVC: CVC_LOADPARAMS_MSG pskey[%x] mode[%x]\n",CVC_2MIC_PS_BASE,CVC_SR_BEX));
                            KalimbaSendMessage(CVC_LOADPARAMS_MSG, CVC_2MIC_PS_BASE, CVC_SR_BEX, 0, 0);
                        break;
        
                        /* ASR is a separate operating mode of CVC */
                        case CVSD_CVC_1_MIC_HEADSET_ASR:
                            PRINT(("CVC: CVC_LOADPARAMS_MSG pskey[%x] mode[%x]\n",CVC_1MIC_PS_BASE_EXT_MIC_NOT_FITTED,CVC_SR_NB));
                            KalimbaSendMessage(CVC_LOADPARAMS_MSG, CVC_1MIC_PS_BASE_EXT_MIC_NOT_FITTED, CVC_SR_NB, 0, 0);
                            /* configure CVC for use as ASR using CVC 1-mic NB*/
                            CvcConfigureASR(task);                        
                        break;
                        
                        case CVSD_CVC_2_MIC_HEADSET_ASR:
                                PRINT(("CVC: CVC_LOADPARAMS_MSG pskey[%x] mode[%x]\n",CVC_2MIC_PS_BASE,CVC_SR_NB));
                                KalimbaSendMessage(CVC_LOADPARAMS_MSG, CVC_2MIC_PS_BASE, CVC_SR_NB, 0, 0);
                            /* configure CVC for use as ASR using CVC 2-mic NB*/
                            CvcConfigureASR(task);                        
                        break;

                        /* handsfree and cvc 2-mic versions */
                        default:
                           if(CVC->incoming_rate == 8000)
                           {
                                PRINT(("CVC: CVC_LOADPARAMS_MSG pskey[%x] mode[%x]\n",CVC_2MIC_PS_BASE,CVC_SR_NB));
                                KalimbaSendMessage(CVC_LOADPARAMS_MSG, CVC_2MIC_PS_BASE, CVC_SR_NB, 0, 0);
                           }
                           else if (CVC->incoming_rate == 16000)
                           {
                               PRINT(("CVC: CVC_LOADPARAMS_MSG pskey[%x] mode[%x]\n",CVC_2MIC_PS_BASE_WBS,CVC_SR_WB));
                               KalimbaSendMessage(CVC_LOADPARAMS_MSG, CVC_2MIC_PS_BASE_WBS, CVC_SR_WB, 0, 0);
                           }
                           else
                           {
                               PRINT(("CVC: Unknown dac_rate.\n"));
                               Panic();
                           }
                        break;
                    }
                                       
                    SetCurrentDspStatus(DSP_LOADED_IDLE);

                    PRINT(("CVC: CVC_READY, SysId[%x] BuildVersion[%x] \n",m->a, m->b));
                    
                    connectAudio (task);
                }
                break;
            
                case CVC_CODEC_MSG:
                {
                    uint16 lOutput_gain;
                    T_mic_gain lInput_gain_l;
                    T_mic_gain lInput_gain_r;
                  
                    lOutput_gain = m->a;
                    lInput_gain_l = *(T_mic_gain*)&m->b;
                    lInput_gain_r = *(T_mic_gain*)&m->c;

                    codecMessage (task, lInput_gain_l,lInput_gain_r, lOutput_gain );

                    SetCurrentDspStatus(DSP_RUNNING);

                 }
                break;

                case MESSAGE_TONE_COMPLETE:
                    csrCvcPluginMessageToneComplete(task);
                    break;
            
                case CVC_LOADPERSIST_MSG:
                {
                    /* a=sysid, b=len */
                    const pblock_entry* entry = PblockGet(m->a);
                    KalimbaSendLongMessage(CVC_LOADPERSIST_RESP, entry->size, entry->data);
                }
                break;

                case CVC_SECPASSED_MSG:
                PRINT(("CVC:  Sec passed.\n"));
                     /*cvc is now loaded, signal that tones etc can be scheduled*/
                    SetAudioBusy(NULL) ;
                break;
 
                case CVC_SECFAILED_MSG:
                PRINT(("CVC: Security has failed.\n"));
                    /*cvc is now loaded, signal that tones etc can be scheduled*/
                    SetAudioBusy(NULL) ;
                break;
               
                case (CSR_SR_WORD_RESP_YES - CSR_SPEECH_RECOGNITION_MESSAGE_BASE):
                {
                    PRINT(("ASR: YES\n")) ;

                    /*Send Message to VM app if VM app has been specified*/
                    if(CVC->app_task)
                        MessageSend ( CVC->app_task , CSR_SR_WORD_RESP_YES, 0 ) ;                
                }
                break;

                case (CSR_SR_WORD_RESP_NO - CSR_SPEECH_RECOGNITION_MESSAGE_BASE):
                {
                    PRINT(("ASR: NO\n")) ;              

                    /*Send Message to VM app if VM app has been specified*/
                    if(CVC->app_task)
                        MessageSend ( CVC->app_task , CSR_SR_WORD_RESP_NO, 0 ) ;                
                }
                break;

                case (CSR_SR_WORD_RESP_FAILED_YES - CSR_SPEECH_RECOGNITION_MESSAGE_BASE):
                {
                    PRINT(("ASR: FAILED YES\n")) ;

                    /*Send Message to VM app if VM app has been specified*/
                    if(CVC->app_task)
                        MessageSend ( CVC->app_task , CSR_SR_WORD_RESP_FAILED_YES, 0 ) ;                
                }
                break;

                case (CSR_SR_WORD_RESP_FAILED_NO - CSR_SPEECH_RECOGNITION_MESSAGE_BASE):
                {
                    PRINT(("ASR: FAILED NO\n")) ;              

                    /*Send Message to VM app if VM app has been specified*/
                    if(CVC->app_task)
                        MessageSend ( CVC->app_task , CSR_SR_WORD_RESP_FAILED_NO, 0 ) ;                
                }
                break;

                case (CSR_SR_WORD_RESP_UNKNOWN - CSR_SPEECH_RECOGNITION_MESSAGE_BASE):
                {
                    PRINT(("ASR: UNKNOWN\n")) ;
                    /*Send Message to VM app if VM app has been specified*/
                    if(CVC->app_task)
                        MessageSend ( CVC->app_task , CSR_SR_WORD_RESP_UNKNOWN, 0 ) ;                                    
                }
                break; 
    
                case KALIMBA_MSG_CBOPS_SILENCE_CLIP_DETECT_CLIP_DETECTED_ID:
                {
                   PRINT(("\n\n\n\n\nInput level clipped.\n"));
                }
                break;                      
            
    
                case KALIMBA_MSG_CBOPS_SILENCE_CLIP_DETECT_SILENCE_DETECTED_ID:
                {
                   PRINT(("\n\n\n\n\nInput level silence.\n"));
                }
                break;   

                default:
                break;
            }
        }
        break;

        case MESSAGE_FROM_KALIMBA_LONG:
        {
            const DSP_LONG_REGISTER_T *m = (const DSP_LONG_REGISTER_T*) message;
/*            PRINT(("CVC: LONG_MESSAGE_FROM_KALIMBA id[0x%x] l[0x%x] \n", m->id, m->size));*/
            switch (m->id)
            {
                case CVC_STOREPERSIST_MSG:
                    /* Set the DSP app's pblock */
/*                   PRINT(("CVC: StorePersist key[0x%x], data[0x%x] \n", m->buf[0], m->buf[1]));*/
                   PblockSet(m->buf[0], m->size-1, (uint16*)m->buf+1);
                break;
                
                default:
                break;
            }
        }
        break;
        
        default:
        break ;
    }
}

static void toneCompleteNoDsp(CvcPluginTaskdata *task)
{
    disconnectOutputNoCvc();

    if (!(CVC->speaker_muted))
    {
        /* reconnect sco audio if present */
        connectOutputNoCvc();

        /* check to see if the sco is still valid, if it is not then we will have received the
           message before the tone has completed playing due to some other issue, therefore
           allow tone to continue playing for an additional 1.5 seconds to allow the power off
           tone to be played to completion */
        if(SinkIsValid(CVC->audio_sink))
        {
            SetAudioBusy(NULL) ;
            CsrCvcPluginSetVolume(CVC->volume );
            PRINT(("CVC: Tone Complete SCO exists\n"));
        }
        else
        {
            MessageSendLater((TaskData*) task, MESSAGE_FORCE_TONE_COMPLETE, 0, 1500);
            PRINT(("CVC: Tone Complete SCO not exists [0x%x]\n", (uint16)CVC->audio_sink));
        }
    }
    else
    {
        SetAudioBusy(NULL) ;
        CsrCvcPluginSetVolume(CVC->volume );
    }
}

/****************************************************************************
DESCRIPTION
    a tone has completed
*/
void CsrCvcPluginToneComplete( CvcPluginTaskdata *task )
{
    PRINT(("CVC: Tone Complete\n"));
    SetAudioBusy(NULL);
    
    if(CVC->no_dsp)
    {
        toneCompleteNoDsp(task);
    }
    else
    {    /* DSP mode */
        /* Restore the DAC gain to mute if in mute mode */
        if ( CVC->cvc_running && CVC->speaker_muted )
            send_volume_to_dsp(DAC_MUTE);
       
        /* We no longer want to receive stream indications */
        MessageSinkTask (StreamKalimbaSink(TONE_VP_MIXING_DSP_PORT) , NULL);
    }
    /* update current tone playing status */
    SetTonePlaying(FALSE);
}

/****************************************************************************
DESCRIPTION
    Handle a MESSAGE_TONE_COMPLETE from the DSP
*/
static void csrCvcPluginMessageToneComplete(CvcPluginTaskdata* task)
{
    /* Make sure tone port is disconnected. Tone source will be 
       cleared up as it was connected with StreamConnectAndDispose.
       Do this after CsrCvcPluginToneComplete has cleared the sink
       task so we don't get any MESSAGE_STREAM_DISCONNECTs. */
    CsrCvcPluginToneComplete(task);
    StreamDisconnect(NULL, StreamKalimbaSink(TONE_VP_MIXING_DSP_PORT));
}

/****************************************************************************
DESCRIPTION
    Reconnects the audio after a tone has completed in no DSP mode
*/
void CsrCvcPluginToneForceCompleteNoDsp ( CvcPluginTaskdata *task )
{
    PRINT(("CVC: Force Tone Complete No DSP\n"));
    
    if(CVC)
    {
        if(IsAudioBusy())
        {
            SetAudioBusy(NULL);
            
            disconnectOutputNoCvc();
            disconnectMicNoCvc();
        }
        /* ensure volume is set to correct level after playing tone */
        CsrCvcPluginSetVolume(CVC->volume );
        /* update current tone playing status */
        SetTonePlaying(FALSE);
    }

}

static void connectMic(const audio_channel channel, const audio_mic_params * const params)
{
    multi_channel_params_t mch_params;

    cvcSetupMcParams(&mch_params, CVC->no_dsp);

    if(CVC->no_dsp)
    {
        Source mic_source = AudioPluginMicSetup(channel, *params, mch_params.sample_rate);
        PanicFalse(StreamConnect(mic_source, CVC->audio_sink));
    }
    else
    {
        Source mic_source = AudioPluginMicSetup(channel, *params, CsrMultiChannelGetSampleRate(&mch_params));
        PanicFalse(StreamConnect(mic_source, StreamKalimbaSink(CVC_LEFT_IN_PORT)));
    }
}

#define ALL_OUTPUTS_DISABLED    0xFFFF

static unsigned getEnableMaskForChannel(const multi_channel_out_t channel)
{
    unsigned mask = ALL_OUTPUTS_DISABLED;
    CsrMultiChanSetOutputEnabled(mask, channel);
    return mask;
}

static void disconnectMic(const audio_channel channel, const audio_mic_params * const params)
{
    Source mic_source = AudioPluginGetMic(AudioPluginGetInstance(*params),
                                        channel, params->digital);
    PRINT(("CVC: NODSP: Disconnect Mic\n")) ;

    if(CVC->no_dsp)
    {
        StreamDisconnect(mic_source, CVC->audio_sink);
    }
    else
    {
        StreamDisconnect(mic_source, StreamKalimbaSink(CVC_LEFT_IN_PORT));
    }
    SourceClose(mic_source);
}

static void connectOutputNoCvc(void)
{
    multi_channel_params_t params;

    /* Don't try to reconnect if sink has closed (e.g. audio transferred to
    the phone while tone playing). */
    if(!SinkIsValid(CVC->audio_sink))
    {
        return;
    }

    PRINT(("CVC: NODSP: Connect Output\n")) ;

    cvcSetupMcParams(&params, CVC->no_dsp);

    if(CVC->no_dsp)
    {
        params.disable_mask = getEnableMaskForChannel(CVC->output_for_no_cvc);

        CsrMultiChanConnectSourceToMultiChannelOutput(CVC->audio_source,
                                                        CVC->output_for_no_cvc,
                                                        &params);
    }
    else
    {
        params.sample_rate = CsrMultiChannelGetSampleRate(&params);
        params.disable_mask = getEnableMaskForChannel(CVC->output_for_no_cvc);

        CsrMultiChanConnectSourceToMultiChannelOutput(StreamKalimbaSource(DSP_OUTPUT_PORT_PRI_LEFT),
                                                                             CVC->output_for_no_cvc,
                                                                             &params);

        if(!KalimbaSendMessage(MESSAGE_SET_ADCDAC_SAMPLE_RATE_MESSAGE_ID,
                                               params.sample_rate / 10, RATE_MATCH_SOFTWARE_MASK,
                                               CsrMultiChanI2sActive() ? CVC_INTERFACE_I2S : CVC_INTERFACE_ANALOG,
                                               params.sample_rate))
        {
            PRINT(("CVC: Message MESSAGE_SET_ADCDAC_SAMPLE_RATE_MESSAGE_ID failed!\n"));
            Panic();
        }
    }
    CsrCvcPluginSetVolume(CVC->volume);
}


static const audio_channel getAudioChannelFromMicId(const microphone_input_id_t mic_id)
{
    if(mic_id == microphone_input_id_voice_b
#ifdef ANC
            || mic_id == microphone_input_id_anc_b
#endif
            )
    {
        return AUDIO_CHANNEL_B;
    }
    return AUDIO_CHANNEL_A;
}

static const audio_mic_params * const getMicParamsFromMicId(const microphone_input_id_t mic_id)
{
    if(mic_id == microphone_input_id_voice_b)
    {
        return &CVC->digital->mic_b;
    }
#ifdef ANC
    else if(mic_id == microphone_input_id_anc_a)
    {
        return AncGetMicAParams();
    }
    else if(mic_id == microphone_input_id_anc_b)
    {
        return AncGetMicBParams();
    }
#endif
    return &CVC->digital->mic_a;
}

#ifdef CVC_ALL

void CsrCvcPluginMicSwitch(void)
{
    PRINT(("CVC: NODSP: MicSwitch [%x]\n" , (int)CVC->audio_sink )) ;
    if ( CVC->audio_sink )
    {
        disconnectMicId(CVC->mic_for_no_cvc);

        CVC->mic_for_no_cvc++;
        if(CVC->mic_for_no_cvc >= microphone_input_id_max)
        {
            CVC->mic_for_no_cvc = microphone_input_id_voice_a;
        }

        connectMicId(CVC->mic_for_no_cvc);
    }
}

static multi_channel_out_t getNextValidMultiChannelOutput(const multi_channel_out_t current_channel)
{
    multi_channel_out_t next_channel = current_channel;

    do
    {
        if(++next_channel == mch_out_max)
        {
            next_channel = mch_out_primary_left;
        }

        if(CsrMultiChanGetOutputType(next_channel))
        {
            break;
        }
    } while(current_channel != next_channel);

    return next_channel;
}

void CsrCvcPluginOutputSwitch(void)
{
    PRINT(("CVC: NODSP: OutputSwitch [%x]\n" , (int)CVC->audio_sink )) ;
    if(CVC->audio_sink)
    {
        disconnectOutputNoCvc();

        CVC->output_for_no_cvc = getNextValidMultiChannelOutput(CVC->output_for_no_cvc);

        connectOutputNoCvc();
    }
}

#endif

static void disconnectOutputNoCvc ( void )
{
    PRINT(("CVC: NODSP: Disconnect Speaker\n")) ;

    /* Possible to have a race between remote close of the link and app disconnecting
       audio. Audio may already be disconnected so ignore return value */
    (void)CsrMultiChanDisconnect();

    /* Clear message task for the audio sink */
    MessageSinkTask( CsrMultiChanGetAudioSink() , NULL );
}

/****************************************************************************
NAME
    CsrCvcPluginSetPower

DESCRIPTION
    Sets the power mode of the plugin

RETURNS
    
*/
void CsrCvcPluginSetPower( CvcPluginTaskdata *task,  AUDIO_POWER_T power)
{
    
    PRINT(("CVC : Set Power [0x%x]\n", power));  
    
    /* If actually using the NO DSP plugin disregard set power requests */
    if(!CVC || task->cvc_plugin_variant == CVSD_NO_DSP)
    {
        PRINT(("CVC : Set Power ignored\n"));
        return;
    }
    
    /*   These are the state transitions possible during an active SCO:
    
    CVC -> (low power) -> DSP Passthrough
    DSP Passthrough -> (normal power) -> CVC
    No DSP -> (normal power) -> CVC
    
    It's not possible to switch CVC or DSP Pass through to No DSP with an active SCO due to Metadata issues */   
    if(!CVC->no_dsp)
    {
        /* Default to normal power */
        CVC->ext_params = CSR_CVC_HFK_ENABLE;
        /* Back to low power unless above threshold */
        if(power <= LPIBM_THRESHOLD)
            CVC->ext_params = CSR_CVC_PSTHRU_ENABLE;
        
        if (IsAudioBusy())
        {
            /* Update mode once busy condition clear */
            MAKE_AUDIO_MESSAGE ( AUDIO_PLUGIN_SET_MODE_MSG) ;
            message->mode   = CVC->mode ;
            message->params = NULL ;
            MessageSendConditionally ( (Task)task, AUDIO_PLUGIN_SET_MODE_MSG , message ,(const uint16 *)AudioBusyPtr() ) ;
        }
        else
        {
            /* Update mode now */
            CsrCvcPluginSetMode((CvcPluginTaskdata*)task, CVC->mode , NULL) ;
        }
    }
}

/****************************************************************************
NAME
    CvcConfigureASR

DESCRIPTION
    configures CVC for use as ASR (speech recognition)

RETURNS
    nothing
*/
void CvcConfigureASR( CvcPluginTaskdata *task)
{
    uint16 ret_len = 0;
    uint16 psdata[4] ;
    
    /* Initialize clip detector */
    PanicFalse(KalimbaSendMessage(KALIMBA_MSG_CBOPS_SILENCE_CLIP_DETECT_INITIALISE_ID,1,0x7fff,1000,1));

    /* Read confidence threshold from from PS if it exists */
    /*needs to be stored somewhere else and not read every time*/
    ret_len = PsRetrieve(60, psdata, 4);

    /* Tell DSP to load Confidence Threshold */
    if(ret_len) 
    {
      PRINT(("Confidence Threshold from PS: len=0x%x, MSB=0x%x, LSB=0x%x, 3rd=0x%x\n\n", ret_len, psdata[0], psdata[1], psdata[2]));
      PanicFalse(KalimbaSendMessage(SET_CONFI_THRESH_MSG, psdata[0], psdata[1], psdata[2], psdata[3]));
    }
}


/****************************************************************************
NAME    
    CsrCvcPluginSetAsr

DESCRIPTION
    Start or restart the ASR engine

RETURNS
    void
*/
void CsrCvcPluginSetAsr ( CvcPluginTaskdata *task, AUDIO_MODE_T mode  )
{
    /* if using ASR feature, start it running */
    if((task->cvc_plugin_variant == CVSD_CVC_1_MIC_HEADSET_ASR)||(task->cvc_plugin_variant == CVSD_CVC_2_MIC_HEADSET_ASR)||
       (task->cvc_plugin_variant == CVSD_CVC_1_MIC_HANDSFREE_ASR)||(task->cvc_plugin_variant == CVSD_CVC_2_MIC_HANDSFREE_ASR))
    {
        KalimbaSendMessage(ASR_START,0,0,0,0);
        PRINT(("ASR START MSG %x busy [%x]\n",ASR_START,(uint16)IsAudioBusy()));
        /* update the current audio state */
        SetAsrPlaying(TRUE);
    }    
}

