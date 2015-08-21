/****************************************************************************
Copyright (C) Cambridge Silicon Radio Ltd. 2005

FILE NAME
    csr_a2dp_decoder_common.c
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
#include "csr_multi_channel_plugin.h"
#include "audio_plugin_if.h" /*for the audio_mode*/
#include "audio_plugin_common.h"
#include "csr_a2dp_decoder_common_plugin.h"
#include "csr_a2dp_decoder_common.h"
#include "csr_a2dp_decoder_common_if.h"

#include "csr_a2dp_decoder_common_aptx.h"
#include "csr_a2dp_decoder_common_aptx_ll.h"
#include "csr_a2dp_decoder_common_faststream.h"
#include "csr_a2dp_decoder_common_fm.h"
#include "csr_a2dp_decoder_common_subwoofer.h"
#include "csr_a2dp_decoder_common_sharing.h"
#include "csr_a2dp_decoder_common_cvc_back_channel.h"

#ifdef ANC
#include "anc.h"
#endif /* ANC */

#define IS_TWS_RELAY_MODE() (DECODER && (DECODER->stream_relay_mode == RELAY_MODE_TWS_MASTER || \
                                         DECODER->stream_relay_mode == RELAY_MODE_TWS_SLAVE))

/*the synchronous audio data structure*/
static DECODER_t * DECODER = NULL ;

static bool pskey_read = FALSE;
static uint16 val_pskey_max_mismatch = 0;
static uint16 val_clock_mismatch = 0;

static const uint16 dsp_variant[NUM_DECODER_PLUGINS] =
{
    0,
    DSP_SBC_DECODER,                /* SBC_DECODER              */
    DSP_MP3_DECODER,                /* MP3_DECODER              */
    DSP_AAC_DECODER,                /* AAC_DECODER              */
    DSP_FASTSTREAM_SINK,            /* FASTSTREAM_SINK          */
    DSP_USB_DECODER,                /* USB_DECODER              */
    DSP_APTX_DECODER,               /* APTX_DECODER             */
    DSP_APTX_ACL_SPRINT_DECODER,    /* APTX_ACL_SPRINT_DECODER  */
    DSP_ANALOG_DECODER,             /* WIRED_DECODER            */
    DSP_SPDIF_DECODER,              /* SPDIF_DECODER            */
    DSP_SBC_DECODER,                /* TWS_SBC_DECODER          */
    DSP_MP3_DECODER,                /* TWS_MP3_DECODER          */
    DSP_AAC_DECODER,                /* TWS_AAC_DECODER          */
    DSP_APTX_DECODER,               /* TWS_APTX_DECODER         */
    DSP_SBC_DECODER                 /* FM_DECODER               */
};

/****************************************************************************
DESCRIPTION

    Translated VM variant id into something the DSP app understands
*/
static uint16 getDspVariant (uint16 variant)
{
    if (variant < NUM_DECODER_PLUGINS)
    {
        return dsp_variant[variant];
    }

    return 0xFFFF;
}


/****************************************************************************
DESCRIPTION

    Sends a latency report to the application
*/
static void sendLatencyReport (Task app_task, A2dpPluginTaskdata *audio_plugin, bool estimated, uint16 latency)
{
    MAKE_AUDIO_MESSAGE(AUDIO_PLUGIN_LATENCY_REPORT);
    PRINT(("DECODER: Latency report estimated:%u latency:%ums\n", estimated, latency));
    message->audio_plugin = (Task)audio_plugin;
    message->estimated = estimated;
    message->latency = latency;
    MessageSend(app_task, AUDIO_PLUGIN_LATENCY_REPORT, message);
}

/****************************************************************************
DESCRIPTION

    Helper function to disconnect a Source, flush buffers then close
*/
static void sourceDisconnectFlushClose(Source disconnectSource)
{
    /* The calling order of these functions is critical */
    /* Moving StreamDisconnect beneath StreamConnectDispose */
    /* causes B-182712 */
    StreamDisconnect(disconnectSource, 0);
    
    /* flush buffer */                    
    StreamConnectDispose(disconnectSource);
    
    /* disconnect and close */
    SourceClose(disconnectSource);    
}

/****************************************************************************
DESCRIPTION

    Stores latency reported by DSP and, if required, informs application
*/
void CsrA2dpDecoderPluginSetAudioLatency (A2dpPluginTaskdata *audio_plugin, uint16 latency)
{
    if (DECODER != NULL)
    {
        A2dpPluginLatencyParams *latencyParams = &((A2dpPluginConnectParams *)DECODER->params)->latency;
        latencyParams->last = latency;

        if (latencyParams->period || latencyParams->change)
        {
            sendLatencyReport(DECODER->app_task, audio_plugin, FALSE, latency);
        }
    }
}


/****************************************************************************
DESCRIPTION

    Provides an estimate of audio latency for a specific codec
*/
static uint16 estimateLatency (A2DP_DECODER_PLUGIN_TYPE_T variant)
{
    uint16 latency = 0;

    /* TODO: Temporary values atm, n.b. units are in 1/10th ms. */
    switch (variant)
    {
    case SBC_DECODER:
    case MP3_DECODER:
    case AAC_DECODER:
    case APTX_DECODER:
        latency = 150;
        break;
    case FASTSTREAM_SINK:
    case APTX_ACL_SPRINT_DECODER:
        latency = 45;
        break;
    case TWS_SBC_DECODER:
    case TWS_MP3_DECODER:
    case TWS_AAC_DECODER:
    case TWS_APTX_DECODER:
        latency = 300;
        break;
    default:
        break;
    }

    PRINT(("DECODER: estimateLatency variant=%u latency=%ums\n", variant, latency));
    return latency;
}


/****************************************************************************
DESCRIPTION

    Configures the DSP to start issuing audio latency measurements
*/
static void enableLatencyReporting (A2dpPluginTaskdata *audio_plugin)
{
    if (DECODER != NULL)
    {
        uint16 initial_latency;
        A2dpPluginLatencyParams *latencyParams = &((A2dpPluginConnectParams *)DECODER->params)->latency;

        if (latencyParams->period)
        {
            if (latencyParams->last)
            {
                initial_latency = (uint16)latencyParams->last * LATENCY_LAST_MULTIPLIER;
            }
            else if (latencyParams->target)
            {
                initial_latency = (uint16)latencyParams->target * LATENCY_TARGET_MULTIPLIER;
            }
            else
            {
                initial_latency = estimateLatency(audio_plugin->a2dp_plugin_variant);
            }

            /* Convert latency configuration parameters to single millisecond resolution before sending to DSP */
            PRINT(("DECODER: CONFIGURE_LATENCY_REPORTING Period=%ums, Change=%ums, Initial=%ums\n", (uint16)latencyParams->period * LATENCY_PERIOD_MULTIPLIER, (uint16)latencyParams->change * LATENCY_CHANGE_MULTIPLIER, initial_latency));
            KalimbaSendMessage(CONFIGURE_LATENCY_REPORTING, 1, (uint16)latencyParams->period * LATENCY_PERIOD_MULTIPLIER, (uint16)latencyParams->change * LATENCY_CHANGE_MULTIPLIER, initial_latency);
            /*KalimbaSendMessage(CONFIGURE_LATENCY_REPORTING, 0x8000 | ((uint16)latencyParams->target * LATENCY_TARGET_MULTIPLIER), (uint16)latencyParams->period * LATENCY_PERIOD_MULTIPLIER, (uint16)latencyParams->change * LATENCY_CHANGE_MULTIPLIER, initial_latency);*/
        }
    }
}

/****************************************************************************
DESCRIPTION

    Handles notification from DSP that the Stream Relay mode has been updated.
    
    Result will contain either the mode that has been set or an error code.
    
    Will issue a further request to change mode if unsuccessful or a new mode has been queued.
    
    A successful change will update the TWS Audio Routing mode, if appropriate
*/
static void streamRelayModeUpdated (uint16 result)
{
    PRINT(("streamRelayModeUpdated  result=%u  required mode=%u\n", result, DECODER->stream_relay_mode));
    
    if (DECODER)
    {
        if (result == DECODER->stream_relay_mode)
        {
            DECODER->relay_mode_change_pending = FALSE;
            
            if ((DECODER->stream_relay_mode == RELAY_MODE_TWS_MASTER) && DECODER->routing_mode_change_pending)
            {   /* Only set routing mode if operating as a TWS Master */
                PRINT(("DECODER: Issuing DSP with MESSAGE_SET_TWS_ROUTING=%u,%u\n",DECODER->master_routing_mode, DECODER->slave_routing_mode));
                
                KalimbaSendMessage(MESSAGE_SET_TWS_ROUTING, DECODER->master_routing_mode, DECODER->slave_routing_mode, 0, 0);
                DECODER->routing_mode_change_pending = FALSE;
            }
            
            if ((DECODER->stream_relay_mode == RELAY_MODE_TWS_MASTER) && DECODER->sbc_encoder_params_pending)
            {   /* Only set SBC encoder paramsif operating as a TWS Master */
                PRINT(("DECODER: Issuing DSP with SBC Encoder params  bitpool=%u  format=0x%X\n",DECODER->sbc_encoder_bitpool, DECODER->sbc_encoder_format));
                
                KalimbaSendMessage(KALIMBA_MSG_SBCENC_SET_PARAMS, DECODER->sbc_encoder_format, 0, 0, 0);
                KalimbaSendMessage(KALIMBA_MSG_SBCENC_SET_BITPOOL, DECODER->sbc_encoder_bitpool, 0, 0, 0);
                DECODER->sbc_encoder_params_pending = FALSE;
            }
            
            if ((DECODER->stream_relay_mode == RELAY_MODE_TWS_MASTER) && DECODER->device_trims_pending)
            {   /* Only set device trims if operating as a TWS Master */
                PRINT(("DECODER: Issuing DSP with MESSAGE_SET_TWS_DEVICE_TRIMS  master_trim=%i  slave_trim=%i\n",DECODER->volume.main.device_trim_master, DECODER->volume.main.device_trim_slave));
                
                KalimbaSendMessage(MESSAGE_SET_DEVICE_TRIMS, DECODER->volume.main.device_trim_master, DECODER->volume.main.device_trim_slave, 0, 0);
                DECODER->device_trims_pending = FALSE;
            }
            
        }
        else
        {
            PRINT(("DECODER: Re-issuing DSP with MESSAGE_SET_RELAY_MODE=%u\n",DECODER->stream_relay_mode));
            
            KalimbaSendMessage(MESSAGE_SET_RELAY_MODE, DECODER->stream_relay_mode, 0, 0, 0);
            DECODER->relay_mode_change_pending = TRUE;
        }
    }
}

/******************************************************************************
DESCRIPTION
    handles messages from the dsp
*/
static void handleInternalMessage(A2dpPluginTaskdata* task, uint16 id, Message message)
{
    A2dpPluginConnectParams *codecData;
    
    /* determine message id */
    switch (id)
    {
       /* message validity check */
       case MESSAGE_FROM_KALIMBA:
       {
            const DSP_REGISTER_T *m = (const DSP_REGISTER_T *) message;
            PRINT(("DECODER: msg id[%x] a[%x] b[%x] c[%x] d[%x]\n", m->id, m->a, m->b, m->c, m->d));

            switch ( m->id )
            {
                /* indication that the dsp is loaded and ready to accept configuration data */
                case MUSIC_READY_MSG:
                    {
                        if (DECODER)
                        {
                            A2DP_DECODER_PLUGIN_TYPE_T variant;
                            codecData = (A2dpPluginConnectParams *) DECODER->params;

                            /* Override the variant if using a USB or wired connection */
                            switch(DECODER->sink_type)
                            {
                                case AUDIO_SINK_USB:
                                    variant = USB_DECODER;
                                break;

                                case AUDIO_SINK_FM:
                                case AUDIO_SINK_ANALOG:
                                    variant = ANALOG_DECODER;
                                break;

                                case AUDIO_SINK_SPDIF:
                                    variant = SPDIF_DECODER;
                                break;

                                default:
                                    /* Use the (default) variant from task structure */
                                    variant = task->a2dp_plugin_variant;
                                break;
                            }

                            /* Tell the DSP what plugin type is being used */
                            if(!KalimbaSendMessage(MUSIC_SET_PLUGIN_MSG, getDspVariant(variant), 0, 0, 0))
                            {
                                PRINT(("DECODER: Message MUSIC_SET_PLUGIN_MSG failed!\n"));
                                Panic();
                            }
                            PRINT(("DECODER: Message MUSIC_SET_PLUGIN_MSG variant = %x\n",variant));

                            /* load configuration parameters from ps, different for low latency variants */
                            /* pskey base address */
                            KalimbaSendMessage(MUSIC_LOADPARAMS_MSG, MUSIC_PS_BASE, 0, 0, 0);

                            /* Set silence detection params for Soundbar*/
                            if(codecData->is_for_soundbar)
                            {
                                PRINT(("DECODER: Message SILENCE_DETECTION_PARAMS_MSG \n"));
                                PRINT(("Threshold %x, Timeout %x\n", codecData->silence_threshold, codecData->silence_trigger_time));
                                KalimbaSendMessage(MUSIC_SILENCE_DETECTION_PARAMS_MSG, codecData->silence_threshold, codecData->silence_trigger_time, 0, 0);
                            }

                            /* update current dsp status */
                            SetCurrentDspStatus( DSP_LOADED_IDLE );
                            
                            /* hold off setting VM app volume until dsp has full buffer of data to allow
                               a smooth transitional fade in */
                            if ((DECODER->stream_relay_mode != RELAY_MODE_TWS_MASTER)&&(DECODER->stream_relay_mode != RELAY_MODE_TWS_SLAVE))
                            {
                                /* delay the setting of the volume to allow smooth volume ramping */
                                codecData->delay_volume_message_sending = TRUE;   
                            }
                            /* for TWS use case disable the delayed volume changes to maintain TWS volume synchronisation */
                            else
                            {
                                /* don't delay volume changes, smooth volume ramping is disabled for TWS */
                                codecData->delay_volume_message_sending = FALSE;   
                            }
                            /* subwoofer not connected yet */                                
                            codecData->sub_connection_port = DSP_SUB_PORT_NOT_CONNECTED;
                        }
                        else
                        {
                            /* update current dsp status */
                            SetCurrentDspStatus( DSP_ERROR );
                        }
                    }
                    break;

                /* confirmation of the configuration data having been processed, ok to connect audio now */
                case MUSIC_PARAMS_LOADED_MSG:
                    {
                        if (DECODER)
                        {
                            /* send status message to app to indicate dsp is ready to accept data,
                               applicable to A2DP media streams only */
                            MAKE_AUDIO_MESSAGE_WITH_LEN(AUDIO_PLUGIN_DSP_READY_FOR_DATA, 0);
                            PRINT(("DECODER: Send CLOCK_MISMATCH_RATE\n"));
                            message->plugin = (TaskData *)task;
                            message->AUDIO_BUSY = (uint16)IsAudioBusy();
                            message->dsp_status = GetCurrentDspStatus();
                            message->media_sink = DECODER->media_sink;
                            MessageSend(DECODER->app_task, AUDIO_PLUGIN_DSP_READY_FOR_DATA, message);
                            /* A2dp is now loaded, signal that tones etc can be scheduled*/
                            SetAudioBusy( NULL ) ;
                            PRINT(("DECODER: DECODER_READY \n"));
                            /* set initial volume levels to mute, ensure this happens regardless of sub connection state */
                            DECODER->volume.main.master = DIGITAL_VOLUME_MUTE;
                            DECODER->volume.aux.master  = DIGITAL_VOLUME_MUTE;
                            CsrA2dpDecoderPluginSetLevels(&DECODER->volume, TRUE);
                            /* connect the dsp ports to the audio streams */
                            MusicConnectAudio (task);
                            /* update current dsp status */
                            SetCurrentDspStatus( DSP_RUNNING );
                            /* If correctly configured, turn on latency reporting */
                            enableLatencyReporting(task);
                            /* disable soft volume ramping for TWS as needs too maintain volume level syncronisation
                               between master and slave units */
                            if ((DECODER->stream_relay_mode != RELAY_MODE_TWS_MASTER)&&(DECODER->stream_relay_mode != RELAY_MODE_TWS_SLAVE))
                            {
                                /* send message to release the lock on processing VM volume changes */
                                MessageSendLater((TaskData *)DECODER->task, AUDIO_PLUGIN_ALLOW_VOLUME_CHANGES_MSG, 0 , ALLOW_FULL_DSP_BUFFER_DELAY_FOR_SOFT_MUTE);
                                /* set a subwoofer port connection failure timeout */                                    
                                MessageSendLater((TaskData *)DECODER->task, AUDIO_PLUGIN_SUBWOOFER_CONNECTION_TIMEOUT_MSG, 0 , SUBWOOFER_CONNECTION_FAILURE_TIMEOUT);                               
                            }
                        }
                        else
                        {
                            /* update current dsp status */
                            SetCurrentDspStatus( DSP_ERROR );
                        }
                    }
                    break;

                /* dsp status information gets sent to the vm app */
                case KALIMBA_MSG_SOURCE_CLOCK_MISMATCH_RATE:
                    {
                        if (DECODER)
                        {
                            MAKE_AUDIO_MESSAGE_WITH_LEN(AUDIO_PLUGIN_DSP_IND, 1);
                            PRINT(("DECODER: Send CLOCK_MISMATCH_RATE\n"));
                            message->id = KALIMBA_MSG_SOURCE_CLOCK_MISMATCH_RATE;
                            message->size_value = 1;
                            message->value[0] = m->a;
                            MessageSend(DECODER->app_task, AUDIO_PLUGIN_DSP_IND, message);
                        }
                    }
                    break;

                case MUSIC_CUR_EQ_BANK:
                    /* DSP tells plugin which EQ is active.  Send this value to the VM app
                       so the current EQ setting can be restored when the device is repowered.
                    */
                    {
                        if (DECODER)
                        {
                            MAKE_AUDIO_MESSAGE_WITH_LEN(AUDIO_PLUGIN_DSP_IND, 1);
                            PRINT(("DECODER: Current EQ setting: [%x][%x]\n", m->a, m->b));
                            message->id = A2DP_MUSIC_MSG_CUR_EQ_BANK;
                            message->size_value = 1;
                            message->value[0] = m->a;
                            MessageSend(DECODER->app_task, AUDIO_PLUGIN_DSP_IND, message);
                        }
                    }
                    break;

                case MUSIC_SETCONFIG_RESP:
                    /* DSP tells plugin which audio enhancements are active.  Send this value
                       to the VM app so the current enhancements setting can be restored when
                       the device is repowered.
                    */
                    {
                        if (DECODER)
                        {
                            MAKE_AUDIO_MESSAGE_WITH_LEN(AUDIO_PLUGIN_DSP_IND, 2);
                            PRINT(("DECODER: Enhancements setting: [%x][%x]\n", m->a, m->b));
                            message->id = A2DP_MUSIC_MSG_ENHANCEMENTS;
                            message->size_value = 2;
                            message->value[0] = m->a;
                            message->value[1] = m->b;
                            MessageSend(DECODER->app_task, AUDIO_PLUGIN_DSP_IND, message);
                        }
                    }
                    break;

                case APTX_SECPASSED_MSG:
                    PRINT(("aptX: Security passed.\n"));
                    KalimbaSendMessage(APTX_SECURITY_MSG, 1, 0, 0, 0);
                    break;

                case APTX_SECFAILED_MSG:
                  PRINT(("aptX: Security failed.\n"));
                  KalimbaSendMessage(APTX_SECURITY_MSG, 0, 0, 0, 0);
                  break;

                case MUSIC_SIGNAL_DETECTOR_STATUS_RESP:
                    /* DSP tells when signal detector status has changed
                    Param1 == 0 => no audio - go into standby
                    Param1 == 1 => receiving audio - come out of standby
                    "no audio" message is sent when signal level has been below the
                    threshold level for the trigger time out period "receiving audio"
                    message is sent as soon as a signal is detected above the threshold level
                    */

                    {
                        uint16 signal = m->a;
                        codecData = (A2dpPluginConnectParams *) DECODER->params;
                        PRINT(("SIGNAL_DETECTOR_STATUS_RESP: PARAM1 %x \n", signal));

                        /* Need to do only for Soundbar*/
                        if(codecData->is_for_soundbar)
                        {
                            if (signal)
                            {
                                /* Signal detected come out of standby */
                                PioCommonSetPin( codecData->speaker_pio, pio_drive, TRUE);
                                /* unmute the output */
                                csrA2dpDecoderPluginOutputMute(multi_channel_group_all, AUDIO_MUTE_DISABLE);
                            }
                            else
                            {
                                /* no audio go into standby */
                                PioCommonSetPin(codecData->speaker_pio, pio_drive, FALSE);
                                /* mute the output */
                                csrA2dpDecoderPluginOutputMute(multi_channel_group_all, AUDIO_MUTE_ENABLE);
                            }
                        }
                    }
                    break;

                case KALIMBA_MSG_LATENCY_REPORT:
                {   /* DSP has sent us an audio latency measurement */
                    if (DECODER)
                    {
                        CsrA2dpDecoderPluginSetAudioLatency(task, m->a);
                    }
                }
                break;

                case KALIMBA_MSG_RELAY_MODE_RESP:
                {   /* DSP has acknowledged the Relay Mode request */
                    PRINT(("KALIMBA_MSG_RELAY_MODE_RESP: %x\n", m->a));
                    streamRelayModeUpdated(m->a);
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

                /* message sent from DSP with SPDIF information including the calculated sample rate
                   of current stream, VM doesn't need to do anything with the sample rate as the DSP
                   talks directly to the firmware */
                case KALIMBA_MSG_DSP_SPDIF_EVENT_MSG:
                {
                    uint16 invalid = m->a;

                    /* check whether status information is valid before processing further */
                    if(!invalid)
                    {
                        PRINT(("SPDIF status message sample rate = %x \n", m->b));
                    }
                    else
                    {
                        PRINT(("SPDIF status message is invalid \n"));
                    }
                }
                break;

                case DSP_GAIA_MSG_GET_USER_PARAM_RESP:
                {
                    MAKE_AUDIO_MESSAGE_WITH_LEN(AUDIO_PLUGIN_DSP_GAIA_EQ_MSG, 2);
                    PRINT(("DECODER: User EQ Param from DSP: [%x][%x]\n", m->a, m->b));
                    message->size_value = 2;
                    message->value[0] = m->a;
                    message->value[1] = m->b;
                    MessageSend(DECODER->app_task, AUDIO_PLUGIN_DSP_GAIA_EQ_MSG, message);
                }
                break;
                
                /* message from DSP when tone or voice prompt has completed playing */
                case MUSIC_TONE_COMPLETE:
                {
                    /* stop tone and clear up status flags */
                    CsrA2dpDecoderPluginToneComplete() ; 
                }
                break;
                
                case MUSIC_CODEC_MSG:
                {
                    /* This message is supported to allow the UFE to temporarily override
                       hardware gain. Force an update to the hardware gain. */
                    CsrMultiChanGainSetHardwareOnly(multi_channel_group_main, VolumeConvertDACGainToDB(m->a));
                    CsrMultiChanGainSetHardwareOnly(multi_channel_group_aux, VolumeConvertDACGainToDB(m->a));
                }
                break;
            }
        }
        break;

        case MESSAGE_FROM_KALIMBA_LONG:
        {
            /* recast message as this is a long message from the DSP */
            const uint16 *rcv_msg = (const uint16*) message;

            switch ( rcv_msg[0] )
            {
                case DSP_GAIA_MSG_GET_USER_GROUP_PARAM_RESP:
                    {
                        uint16 i;

                        MAKE_AUDIO_MESSAGE_WITH_LEN(AUDIO_PLUGIN_DSP_GAIA_GROUP_EQ_MSG, rcv_msg[1]);
                        PRINT(("DECODER: User EQ Group Param from DSP: [%x][%x]...\n", rcv_msg[2],rcv_msg[3]));
                        message->size_value = rcv_msg[1];
                        for(i=0;i<rcv_msg[1];i++)
                            message->value[i] = rcv_msg[i+2];
                        MessageSend(DECODER->app_task, AUDIO_PLUGIN_DSP_GAIA_GROUP_EQ_MSG, message);
                    }
                    break;
                    
                case KALIMBA_MSG_EXTERNAL_VOLUME:
                {
                    PRINT(("KALIMBA_MSG_EXTERNAL_VOLUME\n"));
                    if (IS_TWS_RELAY_MODE())
                    {
                        /* Apply the TWS system gain received from DSP. This is received unsolicited from DSP on TWS slave. On
                           TWS master this is echoed back from DSP to ensure synchronous volume change on both devices. */
                        const AUDIO_PLUGIN_SET_MAIN_VOLUME_MSG_T* msg = (const AUDIO_PLUGIN_SET_MAIN_VOLUME_MSG_T*)(&rcv_msg[1]);
                        CsrMultiChanGainSetHardware(multi_channel_group_main, msg->common.master, msg);
                    }
                }
                break;
            }
        }

        default:
        break ;
    }
}

/******************************************************************************
DESCRIPTION

    Sends configuration messages relating to S/PDIF input to the DSP. This
    includes sample rates, master mode, and other such parameters.
*/
static void sendDspSpdifConfigMessages(A2dpPluginConnectParams* codecData)
{
    /* Send message to DSP to configure the spdif app, the app will then auto detect the sample rate
       and inform the vm app of the current rate via a message which will then be processed by DSP through
       general registers r1,r2,r3,r4 respectively. Bit 7 for r1 was previously in use and is now available. Refer to the module
       $config_spdif_sink_message_handler in spdif_sink.asm for further details on available bits for future reference */
    
    if(!KalimbaSendMessage(MESSAGE_SET_SPDIF_CONFIG_MSG,
                           ((DECODER->features.spdif_supported_data_types) | (codecData->target_latency_config->target_latency << 8)),
                           (ENABLE_SPDIF_MESSAGING|(SPDIF_MINIMUM_INACTIVITY_TIME_BEFORE_SENDING_MESSAGE<<1)),
                           DECODER->dsp_resample_rate,
                           0))
    {
        PRINT(("DECODER: Message MESSAGE_SET_SPDIF_CONFIG_MSG failed!\n"));
        Panic();
    }

    /* If AC3 is supported then send the configuration message */
    if (DECODER->features.spdif_supported_data_types & INPUT_TYPE_AC3)
    {
        if(!KalimbaSendMessage(MESSAGE_SET_AC3_CONFIG_MSG,
                               codecData->spdif_ac3_config->configuration_word_1,
                               codecData->spdif_ac3_config->configuration_word_2,
                               0,
                               0))
        {
             PRINT(("DECODER: Message MESSAGE_SET_AC3_CONFIG_MSG failed!\n"));
             Panic();
        }
    }
}

/******************************************************************************
DESCRIPTION

    Sends input ('CODEC') and output ('DAC') sample rate configuration messages
    to the DSP, taking into account any mismatch.
*/
static void sendDspSampleRateMessages(uint16 mismatch)
{

    A2dpPluginConnectParams * codecData = (A2dpPluginConnectParams *) DECODER->params;
                            
#ifdef ANC
    /* If using ANC then we need to give an indication of the sample rate required
       when the ANC mics are connected. */
    uint32 anc_sample_rate = AncGetDacSampleRate();
    uint16 anc_sample_rate_flag = DSP_ANC_SAMPLE_RATE_NONE;

    if (anc_sample_rate == ANC_SAMPLE_RATE_96K)
    {
        PRINT(("DECODER: Using ANC at 96k\n"));
        anc_sample_rate_flag = DSP_ANC_SAMPLE_RATE_96K;
    }
    else if (anc_sample_rate == ANC_SAMPLE_RATE_192K)
    {
        PRINT(("DECODER: Using ANC at 192k\n"));
        anc_sample_rate_flag = DSP_ANC_SAMPLE_RATE_192K;
    }

    /* Set the ANC Sample rate */
    if(!KalimbaSendMessage(MESSAGE_SET_ANC_MODE, anc_sample_rate_flag, 0, 0, 0))
    {
        PRINT(("DECODER: Message MESSAGE_SET_ANC_MODE failed!\n"));
        Panic();
    }
#endif /* ANC */

    /* determine if there is a subwoofer compiled in the VM application, does not need to
       be connected or streaming at this point */
    if(codecData->sub_functionality_present)
    {
        /* Set the output sampling rate to a fixed rate of48KHz when subwoofer is being used to
           allow resampling of I2S outputs to be used */
        if(!KalimbaSendMessage(MESSAGE_SET_DAC_SAMPLE_RATE, FIXED_SUBWOOFER_DAC_SAMPLE_RATE/DSP_RESAMPLING_RATE_COEFFICIENT, mismatch, val_clock_mismatch, CsrA2dpDecoderPluginIfLowLatencyGetOutputType()))
        {
            PRINT(("DECODER: Message MESSAGE_SET_DAC_SAMPLE_RATE failed!\n"));
            Panic();
        } 
    }
    /* no subwoofer in system */
    else    
    {
        /* Set the output sampling rate (DAC/I2S if no resampling required) */
        if(!KalimbaSendMessage(MESSAGE_SET_DAC_SAMPLE_RATE, DECODER->dsp_resample_rate, mismatch, val_clock_mismatch, CsrA2dpDecoderPluginIfLowLatencyGetOutputType()))
        {
            PRINT(("DECODER: Message MESSAGE_SET_DAC_SAMPLE_RATE failed!\n"));
            Panic();
        }
    }    

    /* Set the codec sampling rate */
    if(!KalimbaSendMessage(MESSAGE_SET_CODEC_SAMPLE_RATE, DECODER->rate/DSP_RESAMPLING_RATE_COEFFICIENT,  16000/DSP_RESAMPLING_RATE_COEFFICIENT, 0, 0))
    {
        PRINT(("DECODER: Message MESSAGE_SET_CODEC_SAMPLE_RATE failed!\n"));
        Panic();
    }
}

/****************************************************************************
DESCRIPTION

    Sends configuration messages relating to multi-channel output to the DSP.
    This includes configuring the hardware type of each output, and the I2S
    master/slave mode.
    
    Note that these messages are not supported by the a2dp_low_latency_1mic or
    a2dp_low_latency_2mic DSP applications, but it is safe to send them anyway
    as the DSP will just ignore messages it doesn't recognise. This avoids the
    need for any complex logic to determine when to send the messages, we just
    send them in all cases.
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

    Obtains a value for audio latency for the specified plugin

    This function can be called before the DSP is loaded.  In which case, the reported
    latency value is an initial estimate based on the audio_plugin provided.

    If the DSP has been loaded and latency reporting has been enabled, then the value reported is
    the last latency value measured by the DSP.

    The latency is reported in units of one tenth of a ms.
*/
bool CsrA2dpDecoderPluginGetLatency (A2dpPluginTaskdata *audio_plugin, bool *estimated, uint16 *latency)
{
    PRINT(("DECODER: CsrA2dpDecoderPluginGetLatency plugin=%X ", (uint16)audio_plugin));

    if (audio_plugin != NULL)
    {
        if (DECODER != NULL)
        {   /* DSP is loaded */
            A2dpPluginLatencyParams *latencyParams = &((A2dpPluginConnectParams *)DECODER->params)->latency;

            if ((latencyParams->period) && (latencyParams->last))
            {   /* Latency reporting enabled and DSP has provided a latency value */
                *estimated = FALSE;
                *latency = latencyParams->last;

                PRINT(("OK  estimated=%u latency=%u\n", *estimated, *latency));
                return TRUE;
            }
        }

        /* DSP not currently loaded or has not updated the latency */
        *estimated = TRUE;
        *latency = 10 * estimateLatency(audio_plugin->a2dp_plugin_variant);

        PRINT(("OK  estimated=%u latency=%u(1/10th ms)\n", *estimated, *latency));
        return TRUE;
    }

    /* Invalid plugin, return something to indicate an unknown latency */
    *estimated = TRUE;
    *latency = 0xFFFF;

    PRINT(("INVALID  estimated=%u latency=%u\n", *estimated, *latency));
    return FALSE;
}


/****************************************************************************
DESCRIPTION

    Issues a request to the DSP to change the TWS Audio Routing mode.
    
    The audio routing change will be queued if the DSP is not in the appropriate 
    state to accept a request.
*/
void csrA2dpDecoderEnableExternalVolume (bool enabled)
{
    PRINT(("DECODER: csrA2dpDecoderEnableExternalVolume  enabled=%u\n", enabled));
    if (DECODER != NULL)
    {
        DECODER->external_volume_enabled = enabled;
        KalimbaSendMessage(MESSAGE_ENABLE_EXT_VOLUME, enabled, 0, 0, 0);
    }
}


/****************************************************************************
DESCRIPTION

    Issues a request to the DSP to change the TWS Audio Routing mode.
    
    The audio routing change will be queued if the DSP is not in the appropriate 
    state to accept a request.
*/
void csrA2dpDecoderSetTwsRoutingMode (uint16 master_routing, uint16 slave_routing)
{
    PRINT(("DECODER: SetTwsRoutingMode  master=%u  slave=%u\n", master_routing, slave_routing));
    if (DECODER != NULL)
    {
        DECODER->master_routing_mode = master_routing;
        DECODER->slave_routing_mode = slave_routing;
        DECODER->routing_mode_change_pending = TRUE;
        
        if ((DECODER->stream_relay_mode == RELAY_MODE_TWS_MASTER) && !DECODER->relay_mode_change_pending)
        {   /* Only set routing mode if DSP is *currently* operating as a TWS Master */
            KalimbaSendMessage(MESSAGE_SET_TWS_ROUTING, master_routing, slave_routing, 0, 0);
            DECODER->routing_mode_change_pending = FALSE;
        }
    }
}


/****************************************************************************
DESCRIPTION

    Issues a request to the DSP to change the SBC Encoder parameters used for the TWS wired modes.
    
    The SBC encoder params change will be queued if the DSP is not in the appropriate 
    state to accept a request.
*/
void csrA2dpDecoderSetSbcEncoderParams (uint8 bitpool, uint8 format)
{
    PRINT(("DECODER: csrA2dpDecoderSetSbcEncoderParams  bitpool=%u  format=0x%X\n", bitpool, format));
    if (DECODER != NULL)
    {
        DECODER->sbc_encoder_bitpool = bitpool;
        DECODER->sbc_encoder_format = format;
        DECODER->sbc_encoder_params_pending = TRUE;
        
        if ((DECODER->stream_relay_mode == RELAY_MODE_TWS_MASTER) && !DECODER->relay_mode_change_pending)
        {   /* Only set routing mode if DSP is *currently* operating as a TWS Master */
            KalimbaSendMessage(KALIMBA_MSG_SBCENC_SET_PARAMS, format, 0, 0, 0);
            KalimbaSendMessage(KALIMBA_MSG_SBCENC_SET_BITPOOL, bitpool, 0, 0, 0);
            DECODER->sbc_encoder_params_pending = FALSE;
        }
    }
}


/****************************************************************************
DESCRIPTION

    Issue DSP request to update TWS device trims if the device is currently the
    master.

    If not the master, saves the trim change for later.
*/
void csrA2dpDecoderSetTWSDeviceTrims (int16 device_trim_master, int16 device_trim_slave)
{
    PRINT(("DECODER: csrA2dpDecoderSetTWSDeviceTrims  master_trim=%i  slave_trim=%i\n", device_trim_master, device_trim_slave));
    if (DECODER != NULL)
    {
        DECODER->volume.main.device_trim_master = device_trim_master;
        DECODER->volume.main.device_trim_slave = device_trim_slave;
        DECODER->device_trims_pending = TRUE;
        
        if ((DECODER->stream_relay_mode == RELAY_MODE_TWS_MASTER) && !DECODER->relay_mode_change_pending)
        {   /* Only set routing mode if DSP is *currently* operating as a TWS Master */
            KalimbaSendMessage(MESSAGE_SET_DEVICE_TRIMS, device_trim_master, device_trim_slave, 0, 0);
            DECODER->device_trims_pending = FALSE;
        }
    }
}


/****************************************************************************
DESCRIPTION

    Issues a request to the DSP to change the Stream Relay mode.  
    Any outstanding request will cause this new one to be queued.
    
*/
void csrA2dpDecoderSetStreamRelayMode (uint16 mode)
{
    PRINT(("DECODER: SetStreamRelayMode mode=%u\n", mode));

    if (DECODER != NULL)
    {
        PRINT(("DECODER:      last mode=%u  pending=%u\n", DECODER->stream_relay_mode, DECODER->relay_mode_change_pending));
        
#ifdef TWS_DEBUG
        if (mode==RELAY_MODE_TWS_MASTER)
        {
            mode = RELAY_MODE_SHAREME;
            PRINT(("DECODER: SetStreamRelayMode changed to mode=%u\n", mode));
        }

        if (mode==RELAY_MODE_TWS_SLAVE)
        {
            mode = RELAY_MODE_NONE;
            PRINT(("DECODER: SetStreamRelayMode changed to mode=%u\n", mode));
        }
#endif

        if (DECODER->stream_relay_mode != mode)
        {   /* Requested mode is different to current/queued mode */
            DECODER->stream_relay_mode = mode;
            
            if (!DECODER->relay_mode_change_pending)
            {   /* Not currently updating relay mode, so go ahead and issue a request */
                PRINT(("DECODER: Issuing DSP with MESSAGE_SET_RELAY_MODE=%u\n",DECODER->stream_relay_mode));
                
                KalimbaSendMessage(MESSAGE_SET_RELAY_MODE, DECODER->stream_relay_mode, 0, 0, 0);
                DECODER->relay_mode_change_pending = TRUE;
            }
        }
    }
}

/****************************************************************************
DESCRIPTION
    This function allows the decoder information to be passed to the subwoofer and sharing
    functions
*/
DECODER_t * CsrA2dpDecoderGetDecoderData(void)
{
    return DECODER;
}

/****************************************************************************
DESCRIPTION
    This function returns the filename and path for the variant chosen
*/
static const char* csrA2dpDecoderGetKapFile(A2DP_DECODER_PLUGIN_TYPE_T variant)
{
    /* if using spdif input then use specific dsp app */
    if(DECODER->sink_type == AUDIO_SINK_SPDIF)
    {
        return "spdif_sink/spdif_sink.kap";
    }
    /* not using wired mode with spdif input */
    else
    {
        /* determine required dsp app based on variant required */
        switch (variant)
        {
        case SBC_DECODER:
        case TWS_SBC_DECODER:
        case FM_DECODER:
            return "sbc_decoder/sbc_decoder.kap";

        case MP3_DECODER:
        case TWS_MP3_DECODER:
            return "mp3_decoder/mp3_decoder.kap";

        case AAC_DECODER:
        case TWS_AAC_DECODER:
            return "aac_decoder/aac_decoder.kap";

        case APTX_DECODER:
        case TWS_APTX_DECODER:
            return "aptx_decoder/aptx_decoder.kap";

        /* aptx and faststream apps are now part of the low latency with optional
           back channel dsp apps, function is selectable at runtime */
        case APTX_ACL_SPRINT_DECODER:
        case FASTSTREAM_SINK:
               /* determine which kap file to load, 1 and 2 mic back channels
                   have their own dedicated apps, digital volume control is not
                   available in these apps, 16 steps of volume only */
                if(DECODER->features.use_one_mic_back_channel)
                    return "a2dp_low_latency_1mic/a2dp_low_latency_1mic.kap";
                else if(DECODER->features.use_two_mic_back_channel)
                    return "a2dp_low_latency_2mic/a2dp_low_latency_2mic.kap";
                /* when not using a back channel revert to standard dsp apps without
                   back channel support to give enhanced digital volume control */
                else
                {
                    if(variant == FASTSTREAM_SINK)
                        return "faststream_decoder/faststream_decoder.kap";
                    else
                        return "aptx_acl_sprint_decoder/aptx_acl_sprint_decoder.kap";
                }

        default:
            Panic();
            return NULL;
        }
    }
}

/****************************************************************************
DESCRIPTION
    This function connects a synchronous audio stream to the pcm subsystem
*/
void CsrA2dpDecoderPluginConnect( A2dpPluginTaskdata *task,
                                  Sink audio_sink ,
                                  AUDIO_SINK_T sink_type,
                                  Task codec_task ,
                                  uint16 volume ,
                                  uint32 rate ,
                                  AudioPluginFeatures features ,
                                  AUDIO_MODE_T mode ,
                                  const void * params,
                                  Task app_task)
{
    const char* kap_file;

    /* create malloc'd copy of audio connect parameters, free'd when audio plugin unloads */
    DECODER = (DECODER_t*)PanicUnlessMalloc (sizeof (DECODER_t) ) ;

    DECODER->task = task;
    DECODER->media_sink = audio_sink ;
    DECODER->forwarding_sink = NULL ;
    DECODER->packet_size = 0;
    DECODER->codec_task = codec_task ;

    /*  We use default values to mute volume on A2DP audio connection
        VM application is expected to send volume control right
        after attempting to establish A2DP media connection with the correct
        system and trim volume information along with master and tone volume
    */
    DECODER->volume.group = multi_channel_group_all; /* Always update all groups */
    DECODER->volume.main.tone = volume; /* set the initial tones volume level */
    DECODER->volume.main.master = DIGITAL_VOLUME_MUTE; /* -120dB , literally mute */
    DECODER->volume.main.device_trim_master = 0;
    DECODER->volume.main.device_trim_slave = 0;
    DECODER->volume.aux.tone = volume; /* set the initial tones volume level */
    DECODER->volume.aux.master = DIGITAL_VOLUME_MUTE; /* -120dB , literally mute */
    
    DECODER->device_trims_pending = FALSE;
    DECODER->mute_state[audio_mute_group_main] = AUDIO_MUTE_DISABLE;
    DECODER->mute_state[audio_mute_group_aux] = AUDIO_MUTE_DISABLE;
    DECODER->mute_state[audio_mute_group_mic] = AUDIO_MUTE_DISABLE;
    
    DECODER->mode       = mode;
    DECODER->mode_params = 0;
    DECODER->features   = features;
    DECODER->params     = (uint16) params;
    DECODER->rate       = rate;
    DECODER->app_task   = app_task;
    DECODER->sink_type  = sink_type;

    DECODER->master_routing_mode = TWS_ROUTING_STEREO;
    DECODER->slave_routing_mode = TWS_ROUTING_STEREO;
    DECODER->routing_mode_change_pending = FALSE;
    DECODER->stream_relay_mode = RELAY_MODE_NONE;
    DECODER->relay_mode_change_pending = FALSE;
    
    DECODER->sbc_encoder_bitpool = 0;
    DECODER->sbc_encoder_format = 0;
    DECODER->sbc_encoder_params_pending = FALSE;
    
    DECODER->external_volume_enabled = FALSE;
   
    /* keep DAC gain in mute state until ports are connected to prevent pops and clicks */
    DECODER->dsp_ports_connected = FALSE;
    
    /* get the filename of the kap file to load */
    kap_file = csrA2dpDecoderGetKapFile(task->a2dp_plugin_variant);

    /* Only need to read the PS Key value once */
    if (!pskey_read)
    {
        if (PsFullRetrieve(PSKEY_MAX_CLOCK_MISMATCH, &val_pskey_max_mismatch, sizeof(uint16)) == 0)
            val_pskey_max_mismatch = 0;
        pskey_read = TRUE;
    }

    /*ensure that the messages received are from the correct kap file*/
    (void) MessageCancelAll( (TaskData*) task, MESSAGE_FROM_KALIMBA);
    MessageKalimbaTask( (TaskData*) task );

    /* audio busy until DSP returns ready message */
    SetAudioBusy((TaskData*)task);

    /* update current dsp status */
    SetCurrentDspStatus( DSP_LOADING );

    /* attempt to obtain file handle and load kap file, panic if not achieveable */
    PanicFalse(KalimbaLoad(PanicFalse(FileFind(FILE_ROOT,(const char *) kap_file ,strlen(kap_file)))));

    /* update current dsp status */
    SetCurrentDspStatus( DSP_LOADED_IDLE );

    if (((A2DP_DECODER_PLUGIN_TYPE_T)task->a2dp_plugin_variant == AAC_DECODER) ||
        ((A2DP_DECODER_PLUGIN_TYPE_T)task->a2dp_plugin_variant == TWS_AAC_DECODER))
    {
        /* Workaround for AAC+ sources that negotiate sampling frequency at half the actual value */
        if (rate < 32000)
            DECODER->rate = rate * 2;
    }

    /* For sinks disconnect the source in case its currently being disposed. */
    StreamDisconnect(StreamSourceFromSink(audio_sink), 0);

    PRINT(("DECODER: CsrA2dpDecoderPluginConnect completed\n"));
}

/****************************************************************************
DESCRIPTION
    Disconnect Sync audio
*/
void CsrA2dpDecoderPluginStartDisconnect(TaskData * task)
{

    PRINT(("DECODER: CsrA2dpDecoderPluginDisconnect start mute\n"));
    /* sample rate no longer valid as plugin is unloading, set to 0 to ensure subwoofer doesn't use it */
    DECODER->rate = 0;
    /* ensure nothing interrupts this sequence of events */
    SetAudioBusy((TaskData*) task);    
    /* start disconnect by muting output */
    DECODER->volume.main.master = DIGITAL_VOLUME_MUTE; /* -120dB , literally mute */
    DECODER->volume.aux.master  = DIGITAL_VOLUME_MUTE; /* -120dB , literally mute */
    DECODER->volume.main.device_trim_master = 0;
    DECODER->volume.main.device_trim_slave = 0;
    DECODER->device_trims_pending = FALSE;

    /* set mute volume levels */
    CsrA2dpDecoderPluginSetLevels(&DECODER->volume, TRUE);                              

    /* sub is connected, use longer delay time to alow sub buffers to flush out to prevent pops */
    if ((DECODER->stream_relay_mode == RELAY_MODE_TWS_MASTER)||(DECODER->stream_relay_mode == RELAY_MODE_TWS_SLAVE))
    {
        /* disconnect immediately when using TWS due to the need to keep the volumes synchronised between
           master and slave devices */
        MessageSend( task, AUDIO_PLUGIN_DISCONNECT_DELAYED_MSG, 0);       
    }
    /* not using TWS relay modes so apply soft volume ramp */
    else
    {
        MessageSendLater( task, AUDIO_PLUGIN_DISCONNECT_DELAYED_MSG, 0, MUTE_DISCONNECT_DELAY_WITH_SUB);
    }
}
/****************************************************************************
DESCRIPTION
    Disconnect Sync audio
*/
void CsrA2dpDecoderPluginDisconnect( A2dpPluginTaskdata *task )
{
    Source l_source, r_source;
    A2dpPluginConnectParams *codecData = NULL;

    if (!DECODER)
    {
        PRINT(("DECODER: CsrA2dpDecoderPluginDisconnect, nothing to disconnect\n"));
        return; /* nothing to disconnect */
    }
    
    codecData = (A2dpPluginConnectParams *) DECODER->params;

    /* disconnect the subwoofer if currently connected */
    CsrA2dpDecoderPluginDisconnectSubwoofer();

    /* if using the microphone or spdif/i2s back channel */
    if(isCodecLowLatencyBackChannel())
    {
        /* check whether microphone back channel needs to be disconnected */
        CsrA2dpDecoderPluginDisconnectMic(codecData);
        /* reset the mic bias pio drive */
        AudioPluginSetMicPio(codecData->mic_params->mic_a, FALSE);
    }
    
    PanicFalse(CsrMultiChanDisconnect());

#ifdef ANC
    /* Ensure ANC microphones are disconnected */
    AncDisconnectMics();
#endif /* ANC */

    /* determine input source from sink type and disconnect its ports */  
    switch(DECODER->sink_type)
    {
        case AUDIO_SINK_USB:
        case AUDIO_SINK_AV:
        {
            /* For sinks disconnect the source in case its currently being disposed. */
            sourceDisconnectFlushClose(StreamSourceFromSink(DECODER->media_sink));        
        }
        break;
 
        /* for analog input, determine the input routing and disconnect appropriate sources */
        case AUDIO_SINK_ANALOG:
        {    
            /* select input routing */
            switch(DECODER->features.audio_input_routing)
            {
                case AUDIO_ROUTE_INTERNAL_AND_RELAY:
                case AUDIO_ROUTE_INTERNAL:
                {
                    /* disconnect input A */
                    l_source = AudioPluginMicSetup(AUDIO_CHANNEL_A, codecData->mic_params->line_a, DECODER->rate);
                    sourceDisconnectFlushClose(l_source);
                    /* if set for stereo use, disconnect the second input, mic/line B */
                    if(DECODER->features.stereo)
                    {
                        /* Configure analogue input B */
                        r_source = AudioPluginMicSetup(AUDIO_CHANNEL_B, codecData->mic_params->line_b, DECODER->rate);
                        sourceDisconnectFlushClose(r_source);
                    }
                }
                break;

                /* using the I2S hardware for audio input */
                case AUDIO_ROUTE_I2S:
                {
                    l_source = StreamAudioSource(AUDIO_HARDWARE_I2S, AUDIO_INSTANCE_0, AUDIO_CHANNEL_SLOT_1 );
                    r_source = StreamAudioSource(AUDIO_HARDWARE_I2S, AUDIO_INSTANCE_0, AUDIO_CHANNEL_SLOT_0 );
                    sourceDisconnectFlushClose(l_source);
                    sourceDisconnectFlushClose(r_source);
                }
                break;
                
                default:
                break;
            }
        }
        break;

        /* disconnect the spdif sources */
        case AUDIO_SINK_SPDIF:
        {
            l_source = StreamAudioSource(AUDIO_HARDWARE_SPDIF, AUDIO_INSTANCE_0, SPDIF_CHANNEL_A );
            r_source = StreamAudioSource(AUDIO_HARDWARE_SPDIF, AUDIO_INSTANCE_0, SPDIF_CHANNEL_B );
            sourceDisconnectFlushClose(l_source);
            sourceDisconnectFlushClose(r_source);
        }
        break;

        /* disconnect FM i2s sources */
        case AUDIO_SINK_FM:
        {
            MusicDisconnectFmSource(codecData);
        }
        break;
        
        default:
        break;
    }

    /* disconnect forwarding sink if connected */
    CsrA2dpDecoderPluginDisconnectForwardingSink();

    /* Dispose of any outstanding audio forwarding messages */
    (void) MessageCancelAll((TaskData*) task, AUDIO_PLUGIN_START_FORWARDING_MSG);
    (void) MessageCancelAll((TaskData*) task, AUDIO_PLUGIN_STOP_FORWARDING_MSG);

     /* dispose of any outstanding volume/muting/fading messages */
    (void) MessageCancelAll((TaskData*) task, AUDIO_PLUGIN_ALLOW_VOLUME_CHANGES_MSG);    
    (void) MessageCancelAll((TaskData*) task, AUDIO_PLUGIN_SUBWOOFER_CONNECTION_TIMEOUT_MSG);  
    (void) MessageCancelAll((TaskData*) task, AUDIO_PLUGIN_DISCONNECT_DELAYED_MSG);  
    (void) MessageCancelAll((TaskData*) task, AUDIO_PLUGIN_DELAY_VOLUME_SET_MSG);  

     /* dispose of any remaining messages in the queue */
    (void) MessageCancelAll( (TaskData*) task, MESSAGE_FROM_KALIMBA);
    MessageKalimbaTask( NULL );

    /* turn off dsp */
    KalimbaPowerOff() ;

    /* update current dsp status */
    SetCurrentDspStatus( DSP_NOT_LOADED );

    /* update the current audio state */
    SetAudioInUse(FALSE);
    SetAudioBusy(NULL);
    
    /* free plugin memory */
    free (DECODER);
    DECODER = NULL ;

    PRINT(("DECODER: CsrA2dpDecoderPluginDisconnect completed\n"));
}

/****************************************************************************
DESCRIPTION
    function to set the volume levels of the dsp after a preset delay
*/
void CsrA2dpDecoderPluginSetHardwareLevels(AUDIO_PLUGIN_DELAY_VOLUME_SET_MSG_T * message)
{
    PRINT(("DSP Hybrid Delayed Gains: Group = %d Master Gain = %d\n", message->group, message->master));
    CsrMultiChanGainSetHardware(message->group, message->master, NULL);
}

/****************************************************************************
DESCRIPTION
    Update the volume info stored in DECODER->volume
*/
static void csrA2dpUpdateStoredVolume(AUDIO_PLUGIN_SET_GROUP_VOLUME_MSG_T* volume_msg)
{
    if(volume_msg->group == multi_channel_group_main || volume_msg->group == multi_channel_group_all)
        DECODER->volume.main = volume_msg->main;
    
    if(volume_msg->group == multi_channel_group_aux || volume_msg->group == multi_channel_group_all)
        DECODER->volume.aux = volume_msg->aux;
}

/****************************************************************************
DESCRIPTION
    Determine whether volume levels can be set immediately or whether there
    a pending action must complete before volume can be updated.
*/
static bool csrA2dpDelaySetLevels(AUDIO_PLUGIN_SET_GROUP_VOLUME_MSG_T* volume_msg)
{
    A2dpPluginConnectParams *codecData = (A2dpPluginConnectParams *) DECODER->params;
    
    /* determine if there is a subwoofer present, if it is present and the media stream is not
       yet present then leave volume in muted state, it will be unmuted when the subwoofer is present */
    if(codecData->sub_is_available && codecData->sub_connection_port == DSP_SUB_PORT_NOT_CONNECTED)
    {
        /* a sub is available but it has yet to establish its media channel, hold the app in muted state
        until the sub channel is available and has been connected */
        PRINT(("DSP Set Levels - Sub available - wait for sub media\n"));
        csrA2dpUpdateStoredVolume(volume_msg);
        return TRUE;
    }
    
    /* if no subwoofer connected and this is an initial volume set message sent from the vm then
    delay the setting of the volume to allow the dsp buffers to fill which allows a smooth
    fade in transistion of the audio, also don't change volume if in the middle of playing a tone otherwise
    a discrepancy will be heard */
    if(IsTonePlaying() || (codecData->sub_is_available == FALSE && codecData->delay_volume_message_sending))
    {
        MAKE_AUDIO_MESSAGE( AUDIO_PLUGIN_SET_GROUP_VOLUME_MSG ) ;
         /* create message containing requested volume settings */
        memmove(message, volume_msg, sizeof(AUDIO_PLUGIN_SET_GROUP_VOLUME_MSG_T));
         /* reschedule the volume setting to allow a full buffer of dsp data */
        MessageSendLater ( (TaskData *)DECODER->task , AUDIO_PLUGIN_SET_GROUP_VOLUME_MSG, message, ALLOW_FULL_DSP_BUFFER_DELAY_FOR_SOFT_MUTE) ;
        PRINT(("DSP Set Levels - delay volume set - reschedule main = %d aux = %d\n", DECODER->volume.main.master,
                                                                                      DECODER->volume.aux.master));
        
        return TRUE;
    }
    return FALSE;
}

/****************************************************************************
DESCRIPTION
    Function to set the hardware volume (used to set hardware volume after
    a delay when using hybrid volume control).
*/
static void csrA2dpSetHardwareGainDelayed(multi_channel_group_t group, int16 master_gain, uint16 delay_ms)
{
    TaskData* task = PanicNull(GetAudioPlugin());
    MAKE_AUDIO_MESSAGE(AUDIO_PLUGIN_DELAY_VOLUME_SET_MSG);
    message->group  = group;
    message->master = master_gain;
    MessageSendLater(task, AUDIO_PLUGIN_DELAY_VOLUME_SET_MSG, message, delay_ms);
}

/****************************************************************************
DESCRIPTION
    Function to send the latest volume and mute settings to the DSP
*/
static void csrA2dpDecoderSendKalimbaVolume(multi_channel_group_t group, multi_channel_gain_t* gain_info)
{
    /* Send the correct volume message for this output group */
    if(group == multi_channel_group_main)
    {
        KalimbaSendLongMessage(MUSIC_VOLUME_MSG, SIZEOF_AUDIO_PLUGIN_SET_MAIN_VOLUME_MSG, (const uint16*)gain_info);
    }
    else
    {
        KalimbaSendLongMessage(MUSIC_VOLUME_AUX_MSG, SIZEOF_AUDIO_PLUGIN_SET_AUX_VOLUME_MSG, (const uint16*)gain_info);
    }
}

/****************************************************************************
DESCRIPTION
    Set the volume levels for a group (either main or aux, not all)
*/
static void csrA2dpDecoderPluginSetGroupLevels(audio_plugin_mch_group_t group, int16 master, int16 tone)
{
    multi_channel_gain_t gain_info;
    
    /* Get the previous gain for this group */
    int16 prev_gain = (group == multi_channel_group_main) ? DECODER->volume.main.master : 
                                                            DECODER->volume.aux.master;
    
    PRINT(("%s vol %d dB/60\n", (group == multi_channel_group_main) ? "Main" : "Aux", master));
    
    /* Get the digital gain settings to apply */
    CsrMultiChanGainGetDigital(group, master, tone, &gain_info);
    
    switch(CsrMultiChanGainGetType(group))
    {
        case multi_channel_gain_hardware:
        {
            if(IS_TWS_RELAY_MODE() && (group == multi_channel_group_main))
            {
                /* To sync TWS volume changes we use this function to get all gain
                   info (ignoring control type) and send it to the DSP. DSP will 
                   echo it back to VM at a time synchronised between the TWS devices
                   via KALIMBA_MSG_EXTERNAL_VOLUME where we will set hardware gain. 
                   This only applies to main output, aux is treated as normal */
                CsrMultiChanGainGetDigitalOnly(group, master, tone, &gain_info);
                
                /* Break without setting hardware volume */
                break;
            }
            
            /* Apply hardware gain immediately for non-TWS usage */
            CsrMultiChanGainSetHardware(group, master, NULL);
        }
        break;
        
        case multi_channel_gain_hybrid:
        {
            uint16 hw_delay_ms = (master >= prev_gain) ? MIXED_MODE_INCREASING_DELAY : 
                                                         MIXED_MODE_DECREASING_DELAY;
            /* Set hardware gain after a delay (delay is tuned to ensure digital and hardware gains happen simultaneously) */
            csrA2dpSetHardwareGainDelayed(group, master, hw_delay_ms);
        }
        break;
        
        case multi_channel_gain_digital:
        default:
            /* Set hardware gain to fixed level */
            CsrMultiChanGainSetHardware(group, master, NULL);
        break;
    }
    
    /* Set digital gain in DSP */
    csrA2dpDecoderSendKalimbaVolume(group, &gain_info);
}

/****************************************************************************
DESCRIPTION
    Function to set the volume levels using the appropriate volume control 
    mechanism
*/
void CsrA2dpDecoderPluginSetLevels(AUDIO_PLUGIN_SET_GROUP_VOLUME_MSG_T * volume_msg, bool force_set_volume)
{
    /* Delay setting volume for some cases (unless overridden by caller) */
    if(!force_set_volume && csrA2dpDelaySetLevels(volume_msg))
    {
        /* Return here so volume is not updated */
        return;
    }
    
    if(isCodecLowLatencyBackChannel())
    {
        /* Applications with CVC back channel do not support digital gain messages */
        CsrA2dpDecoderPluginSetLowLatencyGain(volume_msg->main.master, volume_msg->main.tone);
    }
    else
    {
        /* Set the volume parameters for the main group including TWS per-device trims */
        if(volume_msg->group == multi_channel_group_main || volume_msg->group == multi_channel_group_all)
        {
            csrA2dpDecoderPluginSetGroupLevels(multi_channel_group_main, volume_msg->main.master, volume_msg->main.tone);
            csrA2dpDecoderSetTWSDeviceTrims(volume_msg->main.device_trim_master, volume_msg->main.device_trim_slave);
        }
        /* Set the volume parameters for the aux group */
        if(volume_msg->group == multi_channel_group_aux || volume_msg->group == multi_channel_group_all)
        {
            csrA2dpDecoderPluginSetGroupLevels(multi_channel_group_aux, volume_msg->aux.master, volume_msg->aux.tone);
        }
    }
    
    /* Update stored volume once level has been set to ensure correct 
       detection of increase/decrease when setting hybrid volume level */
    csrA2dpUpdateStoredVolume(volume_msg);
}

/****************************************************************************
DESCRIPTION
    Indicate the volume has changed
*/
void CsrA2dpDecoderPluginSetVolume(AUDIO_PLUGIN_SET_GROUP_VOLUME_MSG_T *volumeDsp)
{
    if (DECODER && volumeDsp)
    {
        /* set the volume levels according to volume control type */
        CsrA2dpDecoderPluginSetLevels(volumeDsp, FALSE);
    }
}

/****************************************************************************
DESCRIPTION
    reset the volume levels to that stored in the plugin
*/
void CsrA2dpDecoderPluginResetVolume(void)
{
    /* Reset gains following voice prompt */
    CsrA2dpDecoderPluginSetVolume(&DECODER->volume);
}

/****************************************************************************
DESCRIPTION
    Set the mute state for the main or aux output group
*/
static void muteOutput(audio_plugin_mch_group_t group, AUDIO_MUTE_STATE_T state)
{
    AUDIO_PLUGIN_MULTI_CHANNEL_MUTE_MSG_T mute_msg;
    
    PRINT(("DECODER: %smute ", (state == AUDIO_MUTE_DISABLE) ? "un-" : ""));
    
    if ((group == multi_channel_group_aux || group == multi_channel_group_all) &&
        (DECODER->mute_state[audio_mute_group_aux] != state))
    {
        PRINT(("aux"));
        mute_msg.aux.left = state;
        mute_msg.aux.right = state;
        
        KalimbaSendLongMessage(MESSAGE_MULTI_CHANNEL_MUTE_AUX, sizeof(AUDIO_PLUGIN_MULTI_CHANNEL_AUX_MUTE_MSG_T), (const uint16*)&mute_msg);
        
        /* Update aux mute state */
        DECODER->mute_state[audio_mute_group_aux] = state;
    }
    
    if ((group == multi_channel_group_main || group == multi_channel_group_all) &&
        (DECODER->mute_state[audio_mute_group_main] != state))
    {
        PRINT(("main"));
        mute_msg.main.primary_left = state;
        mute_msg.main.primary_right = state;
        mute_msg.main.secondary_left = state;
        mute_msg.main.secondary_right = state;
        mute_msg.main.wired_sub = state;
        
        KalimbaSendLongMessage(MESSAGE_MULTI_CHANNEL_MUTE_MAIN, sizeof(AUDIO_PLUGIN_MULTI_CHANNEL_MAIN_MUTE_MSG_T), (const uint16*)&mute_msg);
        
        /* Update main mute state */
        DECODER->mute_state[audio_mute_group_main] = state;
    }
    
    PRINT(("\n"));
}

/******************************************************************************
DESCRIPTION
    Set the soft mute state for outputs using the DSP, inputs (microphones) are
    muted using hardware (for low latency back channel DSP applications).
*/
void CsrA2dpDecoderPluginSetSoftMute(AUDIO_PLUGIN_SET_SOFT_MUTE_MSG_T* message)
{
    /* Determine if this is the low latency back channel application using either aptX LL or faststream */
    if (isCodecLowLatencyBackChannel())
    {
        /* Handle separately */
        csrA2dpDecoderPluginSetLowLatencySoftMute(message);
    }
    /* Standard latency codecs including USB and WIRED (analogue/spdif) inputs */
    else
    {
        AUDIO_MUTE_STATE_T new_main_state = AUDIO_MUTE_DISABLE;
        AUDIO_MUTE_STATE_T new_aux_state = AUDIO_MUTE_DISABLE;
        
        if (message->mute_states & AUDIO_MUTE_MASK(audio_mute_group_main))
            new_main_state = AUDIO_MUTE_ENABLE;
        
        if (message->mute_states & AUDIO_MUTE_MASK(audio_mute_group_aux))
            new_aux_state = AUDIO_MUTE_ENABLE;
        
        muteOutput(multi_channel_group_main, new_main_state);
        muteOutput(multi_channel_group_aux, new_aux_state);
    }
}

/****************************************************************************
DESCRIPTION
    Set the mute state for the main or aux output group (or both)
*/
void csrA2dpDecoderPluginOutputMute(audio_plugin_mch_group_t group, AUDIO_MUTE_STATE_T state)
{
    if (isCodecLowLatencyBackChannel())
        csrA2dpDecoderPluginLowLatencyOutputMute(state);
    else
        muteOutput(group, state);
}

/****************************************************************************
DESCRIPTION
    Sets the audio mode
*/
void CsrA2dpDecoderPluginSetMode ( AUDIO_MODE_T mode , A2dpPluginTaskdata *task , const void * params )
{
    A2dpPluginModeParams *mode_params = NULL;
    A2DP_MUSIC_PROCESSING_T music_processing = A2DP_MUSIC_PROCESSING_PASSTHROUGH;

    if (!DECODER)
        Panic() ;

    /* mode not already set so set it */
    DECODER->mode = mode;

    /* check whether any operating mode parameters were passed in via the audio connect */
    if (params)
    {
        /* if mode parameters supplied then use these */
        mode_params = (A2dpPluginModeParams *)params;
        music_processing = mode_params->music_mode_processing;
        DECODER->mode_params = (uint16)params;
    }
    /* no operating mode params were passed in, use previous ones if available */
    else if (DECODER->mode_params)
    {
        /* if previous mode params exist then revert to back to use these */
        mode_params = (A2dpPluginModeParams *)DECODER->mode_params;
        music_processing = mode_params->music_mode_processing;
    }

    /* determine if this is the low latency back channel application using either aptx ll or faststream */
    if(isCodecLowLatencyBackChannel())
    {
        /* Handle separately */
        csrA2dpDecoderPluginSetLowLatencyMode(mode, task, mode_params, music_processing);
    }
    /* standard latency codecs including USB and WIRED (analogue/spdif) inputs */
    else
    {
        /* determine current operating mode */
        switch (mode)
        {
            case AUDIO_MODE_STANDBY:
            {
                KalimbaSendMessage(MUSIC_SETMODE_MSG, MUSIC_SYSMODE_STANDBY, MUSIC_DO_NOT_CHANGE_EQ_BANK, 0, ((mode_params->external_mic_settings << 1)+(mode_params->mic_mute)));
            }
            break;
            
            case AUDIO_MODE_CONNECTED:
            {
                /* ensure mode_params has been set before use */
                if (mode_params)
                {
                    /* Setup routing mode for both Master and Slave TWS devices */
                    csrA2dpDecoderSetTwsRoutingMode(mode_params->master_routing_mode, mode_params->slave_routing_mode);

                    /* Update DSP mode if necessary */
                    CsrA2dpDecoderPluginSetEqMode(MUSIC_SYSMODE_FULLPROC, music_processing, mode_params);
                    
                    /* update the audio enhancements settings */
                    CsrA2dpDecoderPluginUpdateEnhancements(mode_params);
                }
            }
            break;
            
            case AUDIO_MODE_MUTE_MIC:
            case AUDIO_MODE_MUTE_SPEAKER:
            case AUDIO_MODE_MUTE_BOTH:
            case AUDIO_MODE_UNMUTE_SPEAKER:
            {
                PRINT(("DECODER: *** Muting via SET_MODE_MSG is deprecated ***\n"));
                PRINT(("DECODER: Use SET_SOFT_MUTE_MSG instead\n"));
                Panic();
            }
            break;
            
            default:
            {
                PRINT(("DECODER: Set Audio Mode Invalid [%x]\n", mode));
            }
            break;
        }
    }
}

/****************************************************************************
DESCRIPTION
    plays a tone using the audio plugin
*/
void CsrA2dpDecoderPluginPlayTone ( A2dpPluginTaskdata *task, ringtone_note * tone, Task codec_task, uint16 tone_volume)
{
    Source lSource ;
    Sink lSink ;
  
    if (DECODER)
    {
        PRINT(("DECODER: Tone Start, volume [%d]\n", tone_volume)) ;
    
        /* update current tone playing status */
        SetTonePlaying(TRUE);
        
        /* Configure prompt playback, tone is mono*/    
        KalimbaSendMessage(MESSAGE_SET_TONE_RATE_MESSAGE_ID, 8000 , 0/*Mono Bit 0 =0, TONE BIT 1 = 0*/, 0, 0); 
    
        /* mix the tone via the kalimba tone mixing port */
        lSink = StreamKalimbaSink(TONE_VP_MIXING_DSP_PORT) ;
    
        /*request an indication that the tone has completed / been disconnected*/
        MessageSinkTask ( lSink , (TaskData*) task ) ;
    
        /*connect the tone*/
        lSource = StreamRingtoneSource ( (const ringtone_note *) (tone) ) ;
    
        /*mix the tone to the SBC*/
        StreamConnectAndDispose( lSource , lSink ) ;
        SetAudioBusy((TaskData *)task);
    }
    /* not valid to play tone at this time, clear busy flag */
    else
    {
        SetAudioBusy(NULL);
    }
}

/****************************************************************************
DESCRIPTION
    Stop a tone from currently playing
*/
void CsrA2dpDecoderPluginStopTone ( void )
{
    PRINT(("DECODER: Stop Tone\n")) ;
    if (!DECODER)
        Panic() ;

     StreamDisconnect ( 0 , StreamKalimbaSink(TONE_VP_MIXING_DSP_PORT) ) ;

}

/****************************************************************************
DESCRIPTION
    Reconnects the audio after a tone has completed
*/
void CsrA2dpDecoderPluginToneComplete ( void )
{
    PRINT(("DECODER: Tone Complete\n")) ;

    /* ensure plugin hasn't unloaded before dsp message was received */
    if(DECODER)
    {
        /*we no longer want to receive stream indications*/
        MessageSinkTask ( StreamKalimbaSink(TONE_VP_MIXING_DSP_PORT) , NULL) ;
    }
    if (IsTonePlaying() || IsVpPlaying())
    {
        /*
         * unblock messages waiting for tone to complete and trigger a voice
         * prompt cleanup if required
         */
        SetTonePlaying(FALSE);
        SetAudioBusy(NULL) ;
    }
}


/****************************************************************************
DESCRIPTION
    handles the internal cvc messages /  messages from the dsp
*/
void CsrA2dpDecoderPluginInternalMessage( A2dpPluginTaskdata *task ,uint16 id , Message message )
{
    /* determine codec type as message id's are different */
    if(isCodecLowLatencyBackChannel())
    {
        /* different message handler for low latency codec types as message id's are different */
        CsrA2dpDecoderPluginLowLatencyInternalMessage(task , id , message);
    }
    /* non low latency codec types use different message id's */
    else
    {
        /* dsp message handler */
        handleInternalMessage(task, id, message);
    }
}

/******************************************************************************
DESCRIPTION
    Configure content protection for a transform, and then start it.
*/
void csrA2dpDecoderStartTransformCheckScms(Transform rtp_transform, uint8 content_protection)
{
    /* Start or stop SCMS content protection */
    TransformConfigure(rtp_transform, VM_TRANSFORM_RTP_SCMS_ENABLE, content_protection);
    
    /* Start the transform decode */
    TransformStart(rtp_transform);
    
    PRINT(("DECODER: Transform started\n"));
}


/****************************************************************************
DESCRIPTION
    Connect the encoded audio input and pcm audio output streams
*/
void MusicConnectAudio (A2dpPluginTaskdata *task)
{
    A2dpPluginConnectParams *codecData = (A2dpPluginConnectParams *) DECODER->params;
    A2dpPluginModeParams *mode_params = NULL;
    uint8 content_protection;
    uint16 mismatch = val_pskey_max_mismatch;
    Source l_source = NULL;
    Source r_source = NULL;

    /* initialise the content protection and clock mismatch settings from pstore if available */
    if(codecData != NULL)
    {
        DECODER->packet_size = codecData->packet_size;
        val_clock_mismatch = codecData->clock_mismatch;
        content_protection = codecData->content_protection;
        if (codecData->mode_params != NULL)
            mode_params = codecData->mode_params;
    }
    /* otherwise initialise from scratch, the values will be relearnt and then stored */
    else
    {
        val_clock_mismatch = 0;
        content_protection = 0;
    }

    /* Attempt to connect any input (back channel) ports for sources such as USB/Wired or APTX/FASTSTREAM */
    switch(DECODER->sink_type)
    {
        /* for USB audio source, connect the back channel (input) port to dsp */
        case AUDIO_SINK_USB:
        {
            PRINT(("DECODER: USB Sink\n"));
            
            /* determine input type */
            switch(DECODER->features.audio_input_routing)
            {
                case AUDIO_ROUTE_INTERNAL_AND_RELAY:
                {   /* Encodes and then decodes audio locally, using SBC.  SBC encoded audio can also be relayed to another device */
                    PRINT(("DECODER:     AUDIO_ROUTE_INTERNAL_AND_RELAY  format=0x%X  bitpool=%u\n",codecData->format,codecData->bitpool));
                    csrA2dpDecoderSetSbcEncoderParams( codecData->bitpool, codecData->format );
                }
                /* **** Fall through to AUDIO_ROUTE_INTERNAL **** */
                
                /* using internal ADCs */
                case AUDIO_ROUTE_INTERNAL:
                {
                    PRINT(("DECODER:     AUDIO_ROUTE_INTERNAL\n"));
                    /* connect the USB audio to the dsp */
                    PanicFalse(StreamConnect(StreamSourceFromSink(DECODER->media_sink), StreamKalimbaSink(USB_AUDIO_TO_DSP_PORT)));
                    /* determine if USB has been configured to include a microphone back channel */
                    if(codecData)
                    {
                        /* Don't apply to USB - zero */
                        val_clock_mismatch = 0;
                        /* If we have a USB Mic */
                        if(codecData->usb_params)
                        {
                            PRINT(("DECODER:         Back channel\n"));
                            /* Connect Mic -> KalSnk4, KalSrc2 -> USB(mic)*/
                            l_source = AudioPluginMicSetup(AUDIO_CHANNEL_A, codecData->mic_params->mic_a, DECODER->rate);
                            PanicFalse(StreamConnect(l_source, StreamKalimbaSink(USB_MIC_TO_DSP_PORT)));
                            PanicFalse(StreamConnect(StreamKalimbaSource(USB_DSP_TO_MIC_PORT), codecData->usb_params->usb_sink));
                        }
                    }
                }
                break;
            
                case AUDIO_ROUTE_I2S:
                case AUDIO_ROUTE_SPDIF:
                {   /* Not currently supported */
                }
                break;
            }
            
            csrA2dpDecoderSetStreamRelayMode(RELAY_MODE_NONE);
        }
        break;

        /* for wired input source, connect the back channel (input) port to dsp */
        case AUDIO_SINK_ANALOG:
        {
            PRINT(("DECODER: Analog/I2S Wired Sink\n"));

            /* determine input type */
            switch(DECODER->features.audio_input_routing)
            {
                case AUDIO_ROUTE_INTERNAL_AND_RELAY:
                {   /* Encodes and then decodes audio locally, using SBC.  SBC encoded audio can also be relayed to another device */
                    PRINT(("DECODER:     AUDIO_ROUTE_INTERNAL_AND_RELAY  format=0x%X  bitpool=%u\n",codecData->format,codecData->bitpool));
                    csrA2dpDecoderSetSbcEncoderParams( codecData->bitpool, codecData->format );
                }
                /* **** Fall through to AUDIO_ROUTE_INTERNAL **** */
                    
                /* using internal ADCs */
                case AUDIO_ROUTE_INTERNAL:
                {
                    PRINT(("DECODER:     AUDIO_ROUTE_INTERNAL\n"));
                    /* Configure analogue input A */
                    l_source = AudioPluginMicSetup(AUDIO_CHANNEL_A, codecData->mic_params->line_a, DECODER->rate);

                    /* if set for stereo use, configure the second in input, mic/line B */
                    if(DECODER->features.stereo)
                    {
                        /* Configure analogue input B */
                        r_source = AudioPluginMicSetup(AUDIO_CHANNEL_B, codecData->mic_params->line_b, DECODER->rate);
                        /* synchronise the two channels */
                        PanicFalse(SourceSynchronise(l_source, r_source));
                        /* connect mic/line B to the dsp */
                        PanicFalse(StreamConnect(r_source, StreamKalimbaSink(WIRED_LINE_B_TO_DSP_PORT)));
                        PRINT(("DECODER:         Stereo Input\n"));
                    }
                    /* connect mic/line A to the dsp */
                    PanicFalse(StreamConnect(l_source, StreamKalimbaSink(WIRED_LINE_A_TO_DSP_PORT)));
                }
                break;

                /* using the I2S hardware for audio input */
                case AUDIO_ROUTE_I2S:
                {
                    PRINT(("DECODER:     AUDIO_ROUTE_I2S\n"));
                    /* connect the I2S input */
                    CsrI2SAudioInputConnect(DECODER->rate, DECODER->features.stereo, StreamKalimbaSink(WIRED_LINE_A_TO_DSP_PORT), StreamKalimbaSink(WIRED_LINE_B_TO_DSP_PORT) );
                }
                break;
                
                default:
                break;
            }
            /* don't apply the stored values to a WIRED input */
            val_clock_mismatch = 0;
            /* disable rate matching for wired input */
            mismatch |= MUSIC_RATE_MATCH_DISABLE;
            
            csrA2dpDecoderSetStreamRelayMode(RELAY_MODE_NONE);
        }
        break;
        
        /* for spdif input source, connect the back channel (input) port to dsp */
        case AUDIO_SINK_SPDIF:
        {
            /* obtain source to SPDIF hardware */
            r_source = StreamAudioSource(AUDIO_HARDWARE_SPDIF, AUDIO_INSTANCE_0, SPDIF_CHANNEL_B );
            l_source = StreamAudioSource(AUDIO_HARDWARE_SPDIF, AUDIO_INSTANCE_0, SPDIF_CHANNEL_A );

            PRINT(("DECODER: spdif Wired Sink\n"));

            /* when configured for tws audio sharing */
            switch(DECODER->features.audio_input_routing)
            {
                case AUDIO_ROUTE_INTERNAL_AND_RELAY:
                {   /* Encodes and then decodes audio locally, using SBC.  SBC encoded audio can also be relayed to another device */
                    PRINT(("DECODER:     AUDIO_ROUTE_INTERNAL_AND_RELAY  format=0x%X  bitpool=%u\n",codecData->format,codecData->bitpool));
                    csrA2dpDecoderSetSbcEncoderParams( codecData->bitpool, codecData->format );
                }
                
                default:
                break;
            }
            
            PRINT(("DECODER:     AUDIO_ROUTE_SPDIF\n"));
            /* configure the SPDIF interface operating mode, run in auto rate detection mode */
            PanicFalse(SourceConfigure(l_source, STREAM_SPDIF_AUTO_RATE_DETECT, TRUE));
            PanicFalse(SourceConfigure(l_source, STREAM_SPDIF_CHNL_STS_REPORT_MODE, TRUE));
            PanicFalse(SourceConfigure(r_source, STREAM_SPDIF_AUTO_RATE_DETECT, TRUE));
            PanicFalse(SourceConfigure(r_source, STREAM_SPDIF_CHNL_STS_REPORT_MODE, TRUE));

            /* synchronise the two channels */
            PanicFalse(SourceSynchronise(l_source, r_source));

            /* connect mic/line B to the dsp */
            PanicFalse(StreamConnect(r_source, StreamKalimbaSink(WIRED_LINE_B_TO_DSP_PORT)));

            /* connect mic/line A to the dsp */
            PanicFalse(StreamConnect(l_source, StreamKalimbaSink(WIRED_LINE_A_TO_DSP_PORT)));

            /* don't apply the stored values to a WIRED input */
            val_clock_mismatch = 0;
            /* disable rate matching for wired input */
            mismatch |= MUSIC_RATE_MATCH_DISABLE;
            
            csrA2dpDecoderSetStreamRelayMode(RELAY_MODE_NONE);
        }
        break;
                
        /* for BT connections, SBC,MP3,AAC,FASTREAM and APTX */
        case AUDIO_SINK_AV:
        {
            Transform rtp_transform = 0;
            
            PRINT(("DECODER: AV Sink\n"));

            /* determine the A2DP variant in use and see if a transform needs to be used */
            switch ((A2DP_DECODER_PLUGIN_TYPE_T)task->a2dp_plugin_variant)
            {
                /* for SBC, start the SBC RTP transform on the incoming data and connect to dsp sink port 0 */
                case SBC_DECODER:
#ifdef SHAREME_SLAVE
                    StreamConnect(StreamSourceFromSink(DECODER->media_sink) , StreamKalimbaSink(CODEC_TO_DSP_PORT));
#else
                    rtp_transform = TransformRtpSbcDecode(StreamSourceFromSink(DECODER->media_sink) , StreamKalimbaSink(CODEC_TO_DSP_PORT));
#endif
                    csrA2dpDecoderSetStreamRelayMode(RELAY_MODE_NONE);
                break;
                /* for MP3, start the MP3 RTP transform connection to dsp sink port 0 */
                case MP3_DECODER:
#ifdef SHAREME_SLAVE
                    StreamConnect(StreamSourceFromSink(DECODER->media_sink) , StreamKalimbaSink(CODEC_TO_DSP_PORT));
#else
                    rtp_transform = TransformRtpMp3Decode(StreamSourceFromSink(DECODER->media_sink) , StreamKalimbaSink(CODEC_TO_DSP_PORT));
#endif
                    csrA2dpDecoderSetStreamRelayMode(RELAY_MODE_NONE);
                break;
                /* for AAC start the AAC RTP transform connecting to dsp sink port 0 */
                case AAC_DECODER:
#ifdef SHAREME_SLAVE
                    StreamConnect(StreamSourceFromSink(DECODER->media_sink) , StreamKalimbaSink(CODEC_TO_DSP_PORT));
#else
                    rtp_transform = TransformRtpAacDecode(StreamSourceFromSink(DECODER->media_sink) , StreamKalimbaSink(CODEC_TO_DSP_PORT));
#endif
                    csrA2dpDecoderSetStreamRelayMode(RELAY_MODE_NONE);
                break;
                /* for fastream data source */
                case FASTSTREAM_SINK:
                    /* connect dsp ports for the FASTSTREAM codec */
                    if (codecData)
                    {
                        MusicConnectFaststreamSource(codecData);
                    }
                    csrA2dpDecoderSetStreamRelayMode(RELAY_MODE_NONE);
                break;
                /* for APTX standard delay */
                case APTX_DECODER:
                    /* connect dsp ports for the standard APTX codec */
                    if (codecData)
                    {
                        MusicConnectAptxSource(codecData, content_protection);
                    }
                    csrA2dpDecoderSetStreamRelayMode(RELAY_MODE_NONE);
                break;
                /* for APTX low delay */
                case APTX_ACL_SPRINT_DECODER:
                    /* connect dsp ports for low latency APTX codec */
                    if (codecData)
                    {
                        MusicConnectAptxLowLatencySource(codecData, content_protection);
                    }
                    csrA2dpDecoderSetStreamRelayMode(RELAY_MODE_NONE);
                break;
                case TWS_SBC_DECODER:
                case TWS_MP3_DECODER:
                case TWS_AAC_DECODER:
                case TWS_APTX_DECODER:
                    /* TWS codecs do not use RTP.  Connect directly to DSP */
                    StreamConnect(StreamSourceFromSink(DECODER->media_sink) , StreamKalimbaSink(CODEC_TO_DSP_PORT));
                    csrA2dpDecoderSetStreamRelayMode(RELAY_MODE_TWS_SLAVE);
                break;
                default:
                break;
            }
            
            /* Check content protection requirements */
            if (rtp_transform)
                csrA2dpDecoderStartTransformCheckScms(rtp_transform, content_protection);
        }
        break;

        /* for fm input source, connect the FM i2s input */
        case AUDIO_SINK_FM:
        {
            PRINT(("DECODER: FM Sink\n"));

            /* connect dsp ports for the FM */
            if (codecData)
            {
                MusicConnectFmSource(codecData);
            }
            /* no peer sharing */
            csrA2dpDecoderSetStreamRelayMode(RELAY_MODE_NONE);
            /* don't apply the stored values to an FM WIRED input */
            val_clock_mismatch = 0;
            /* disable rate matching for wired input */
            mismatch |= MUSIC_RATE_MATCH_DISABLE;
        }
        break;

        default:
            PRINT(("DECODER: Unsupported Sink\n"));
            Panic();
        break;
    }

#ifdef ANC
    /* Attempt to connect ANC microphones */
    AncConnectMics(ANC_MIC_A_TO_DSP_PORT, ANC_MIC_B_TO_DSP_PORT);
#endif /* ANC */

    /* Connect up DSP output ports to hardware sinks */
    MusicConnectOutputSinks();
    
    /* For the low latency apps, connect the CVC back channel if 1 or two mic back channel has been defined */
    if (isCodecLowLatencyBackChannel())
    {
        /* connect the one or two mics for back channel operation, if two mic is not defined it is assummed 1 mic */
        CsrA2dpDecoderConnectBackChannel(codecData, DECODER->features.use_two_mic_back_channel);
    }
    
    /* check to see if the subwoofer can be connected */
    CsrA2dpDecoderPluginConnectSubwoofer(codecData);
    
    /* DSP port now connected, ok to set DAC_GAIN, this eliminates the pop/clicks associated with port connection */
    DECODER->dsp_ports_connected = TRUE;

    /* set the dsp into the correct operating mode with regards to mute and enhancements */
    CsrA2dpDecoderPluginSetMode(DECODER->mode, task, mode_params);
    
    /* When using S/PDIF input, send S/PDIF specific configuration messages to the DSP */
    if (DECODER->sink_type == AUDIO_SINK_SPDIF)
        sendDspSpdifConfigMessages(codecData);
    /* Otherwise configure rates as normal */
    else
        sendDspSampleRateMessages(mismatch);
    
    /* Let the DSP know which outputs are connected to which hardware types */
    sendDspMultiChannelMessages();
    
    /* Send final 'go' message to the DSP */
    PRINT(("DECODER: Send Go message to DSP now\n"));
    if(!KalimbaSendMessage(KALIMBA_MSG_GO,0,0,0,0))
    {
        PRINT(("DECODER: Message KALIMBA_MSG_GO failed!\n"));
        Panic();
    }
    
    /* Update the current audio state */
    SetAudioInUse(TRUE);
}

/****************************************************************************
DESCRIPTION
    Utility function to connect up the hardware outputs with DSP ports.
    
    @return void
*/
void MusicConnectOutputSinks(void)
{
    A2dpPluginConnectParams *codecData = (A2dpPluginConnectParams *) DECODER->params;
    /* Set up multi-channel parameters */
    multi_channel_params_t mch_params;
    memset(&mch_params, 0, sizeof(multi_channel_params_t));
    
    /* determine if there is a subwoofer compiled in the VM application, does not need to
       be connected or streaming at this point */
    if(codecData->sub_functionality_present)
    {
        /* Set the output sampling rate to a fixed rate of 48KHz when subwoofer is being used to
           allow resampling of I2S outputs to be used */
        mch_params.sample_rate = FIXED_SUBWOOFER_DAC_SAMPLE_RATE;
        /* disable the output rate resampling */        
        mch_params.disable_resample = TRUE;
    }
    else
    {
        /* Set the output sampling rate to that of the codec rate, no resampling */
        mch_params.sample_rate = DECODER->rate;
    }
    
    /* Use multi-channel plugin to connect outputs. Multi-channel plugin 
       must have been initialised by the application */
    PRINT(("DECODER: Using multi-channel mapping (%luHz)\n",mch_params.sample_rate));
    PanicFalse(CsrMultiChanConnectDsp(&mch_params));
    
    /* Store adjusted sample rate returned from multi-channel plugin */
    DECODER->dsp_resample_rate = (uint16)(mch_params.sample_rate/DSP_RESAMPLING_RATE_COEFFICIENT);
}

/****************************************************************************
DESCRIPTION
    @Param  state
            TRUE: Mic will be muted
            FALSE : Unmute Mic
    @return void
*/
void csrA2dpDecoderPluginMicMute(AUDIO_MUTE_STATE_T state)
{
    A2dpPluginConnectParams* codecData = (A2dpPluginConnectParams*)DECODER->params;
    
    if (codecData == NULL)
        return;
    
    if (DECODER->mute_state[audio_mute_group_mic] != state)
    {
        bool digital = (DECODER->sink_type == AUDIO_SINK_ANALOG ? FALSE : codecData->mic_params->mic_a.digital);
        Source src = AudioPluginGetMic(AudioPluginGetInstance(codecData->mic_params->mic_a), AUDIO_CHANNEL_A, digital);
        
        PRINT(("DECODER: Set Mic Mute to [%x]\n", state));
        
        /* update the muteEnable status , according to mute value */
        if(src)
        {
            SourceConfigure(src, STREAM_AUDIO_MUTE_ENABLE, state);
        }
        if(DECODER->features.use_two_mic_back_channel)
        {
            src = AudioPluginGetMic(AudioPluginGetInstance(codecData->mic_params->mic_b),
                                    AUDIO_CHANNEL_B, codecData->mic_params->mic_b.digital);

            /* Do mute/unmute on channel B */
            if(src)
            {
                SourceConfigure(src, STREAM_AUDIO_MUTE_ENABLE, state);
            }
        }
        
        DECODER->mute_state[audio_mute_group_mic] = state;
    }
}

/****************************************************************************
DESCRIPTION
    Utility function to obtain current plugin sample rate 

    @return current sample rate
*/
uint32 CsrA2DPGetDecoderSampleRate(void)
{
    /* if a2dp plugin loaded and rate is valid */
    if((DECODER)&&(DECODER->rate))
    {
        /* return current sample rate */
        PRINT(("DECODER: Sample Rate = %ld , decoder = %d\n",DECODER->rate,DECODER->sink_type));
        return DECODER->rate;
    }
    /* not yet loaded, sample rate unavailable so return 0 */
    else
    {
        PRINT(("DECODER: Sample Rate Not Available\n"));
        return 0;
    }
}

/****************************************************************************
DESCRIPTION
    Utility function to obtain current plugin sample rate for subwoofer use

    @return current sample rate
*/
uint32 CsrA2DPGetDecoderSubwooferSampleRate(void)
{
    /* Subwoofer rate is now fixed at 48KHz to prevent issues with resampling 
       I2S outputs */
    return 48000;
}



/****************************************************************************
DESCRIPTION
    utility function to set the current EQ operating mode

    @return void
*/
void CsrA2dpDecoderPluginSetEqMode(uint16 operating_mode, A2DP_MUSIC_PROCESSING_T music_processing, A2dpPluginModeParams *mode_params)
{
    /* determine the music processing mode requirements, set dsp music mode appropriately */
    switch (music_processing)
    {
        case A2DP_MUSIC_PROCESSING_PASSTHROUGH:
            {
                KalimbaSendMessage (MUSIC_SETMODE_MSG , MUSIC_SYSMODE_PASSTHRU , MUSIC_DO_NOT_CHANGE_EQ_BANK, 0, ((mode_params->external_mic_settings << 1)+(mode_params->mic_mute)) );
                PRINT(("DECODER: Set Music Mode SYSMODE_PASSTHRU\n"));
            }
            break;

        case A2DP_MUSIC_PROCESSING_FULL:
            {
                KalimbaSendMessage (MUSIC_SETMODE_MSG , operating_mode , MUSIC_DO_NOT_CHANGE_EQ_BANK, 0, ((mode_params->external_mic_settings << 1)+(mode_params->mic_mute)));
                PRINT(("DECODER: Set Music Mode SYSMODE_FULLPROC\n"));
            }
            break;

        case A2DP_MUSIC_PROCESSING_FULL_NEXT_EQ_BANK:
            {
                KalimbaSendMessage (MUSIC_SETMODE_MSG , operating_mode , MUSIC_NEXT_EQ_BANK, 0, ((mode_params->external_mic_settings << 1)+(mode_params->mic_mute)));
                PRINT(("DECODER: Set Music Mode %d and advance to next EQ bank\n", operating_mode));
            }
            break;

        case A2DP_MUSIC_PROCESSING_FULL_SET_EQ_BANK0:
            {
                KalimbaSendMessage (MUSIC_SETMODE_MSG , operating_mode , MUSIC_SET_EQ_BANK, 0, ((mode_params->external_mic_settings << 1)+(mode_params->mic_mute)));
                PRINT(("DECODER: Set Music Mode %d and set EQ bank 0\n",operating_mode));
            }
            break;

        case A2DP_MUSIC_PROCESSING_FULL_SET_EQ_BANK1:
            {
                KalimbaSendMessage (MUSIC_SETMODE_MSG , operating_mode , MUSIC_SET_EQ_BANK, 1, ((mode_params->external_mic_settings << 1)+(mode_params->mic_mute)));
                PRINT(("DECODER: Set Music Mode %d and set EQ bank 1\n",operating_mode));
            }
            break;

        case A2DP_MUSIC_PROCESSING_FULL_SET_EQ_BANK2:
            {
                KalimbaSendMessage (MUSIC_SETMODE_MSG , operating_mode , MUSIC_SET_EQ_BANK, 2, ((mode_params->external_mic_settings << 1)+(mode_params->mic_mute)));
                PRINT(("DECODER: Set Music Mode %d and set EQ bank 2\n",operating_mode));
            }
            break;

        case A2DP_MUSIC_PROCESSING_FULL_SET_EQ_BANK3:
            {
                KalimbaSendMessage (MUSIC_SETMODE_MSG , operating_mode , MUSIC_SET_EQ_BANK, 3, ((mode_params->external_mic_settings << 1)+(mode_params->mic_mute)));
                PRINT(("DECODER: Set Music Mode %d and set EQ bank 3\n",operating_mode));
            }
            break;
        case A2DP_MUSIC_PROCESSING_FULL_SET_EQ_BANK4:
            {
                KalimbaSendMessage (MUSIC_SETMODE_MSG , operating_mode , MUSIC_SET_EQ_BANK, 4, ((mode_params->external_mic_settings << 1)+(mode_params->mic_mute)));
                PRINT(("DECODER: Set Music Mode %d and set EQ bank 4\n",operating_mode));
            }
            break;

        case A2DP_MUSIC_PROCESSING_FULL_SET_EQ_BANK5:
            {
                KalimbaSendMessage (MUSIC_SETMODE_MSG , operating_mode , MUSIC_SET_EQ_BANK, 5, ((mode_params->external_mic_settings << 1)+(mode_params->mic_mute)));
                PRINT(("DECODER: Set Music Mode %d and set EQ bank 5\n",operating_mode));
            }
            break;

        case A2DP_MUSIC_PROCESSING_FULL_SET_EQ_BANK6:
            {
                KalimbaSendMessage (MUSIC_SETMODE_MSG , operating_mode , MUSIC_SET_EQ_BANK, 6, ((mode_params->external_mic_settings << 1)+(mode_params->mic_mute)));
                PRINT(("DECODER: Set Music Mode %d and set EQ bank 6\n",operating_mode));
            }
            break;

        default:
            {
                PRINT(("DECODER: Set Music Mode Invalid [%x]\n" , music_processing ));
            }
            break;
    }
}

/****************************************************************************
DESCRIPTION
    utility function to set the current audio enhancments enables

    @return void
*/
void CsrA2dpDecoderPluginUpdateEnhancements(A2dpPluginModeParams *mode_params)
{
    /* update the enables of any audio enhancements */
    if(mode_params)
    {
        /* if data is valid set the enhancement enables for bass boost and 3d effect, the enables are inverted logic */
        if(mode_params->music_mode_enhancements & MUSIC_CONFIG_DATA_VALID)
        {
            PRINT(("DECODER: Set Audio Enhancements Configuration [%x] inverted [%x]\n" , mode_params->music_mode_enhancements , (~mode_params->music_mode_enhancements & 0x0fff)));
            KalimbaSendMessage(MUSIC_SETCONFIG , 0 , (MUSIC_CONFIG_USER_EQ_BYPASS|MUSIC_CONFIG_CROSSOVER_BYPASS|MUSIC_CONFIG_BASS_BOOST_BYPASS|MUSIC_CONFIG_SPATIAL_BYPASS), 0, ~mode_params->music_mode_enhancements);
        }
    }
}

/****************************************************************************
DESCRIPTION
    utility function to reset the VM volume change request block now that the 
    dsp has a full buffer of data 

    @return void
*/
void CsrA2dpDecoderPluginAllowVolChanges(void)
{
    A2dpPluginConnectParams *codecData = (A2dpPluginConnectParams *) DECODER->params;

    /* ensure plugin loaded and we are not waiting for the subwoofer to connect */
    if((DECODER)&&(codecData->sub_is_available == FALSE))
    {
        PRINT(("DECODER: Allow Volume Changes\n"));
        codecData->delay_volume_message_sending = FALSE;
    }
    else
        PRINT(("DECODER: Allow Volume Changes Ignored Due To Sub\n"));

}

/****************************************************************************
DESCRIPTION
    utility function to check whether the subwoofer port got connected within the 
    5 second timeout period, if it didn't the audio will still be in muted state
    so will need to be unmuted 

    @return void
*/
void CsrA2dpDecoderPluginSubCheckForConnectionFailure(void)
{
    /* ensure plugin loaded */
    if(DECODER)
    {
        A2dpPluginConnectParams *codecData = (A2dpPluginConnectParams *) DECODER->params;
      
        /* check whether subwoofer is available, if not exit */
        if((codecData->sub_is_available == TRUE)&&(codecData->sub_connection_port == DSP_SUB_PORT_NOT_CONNECTED))
        {
            PRINT(("DECODER: SUB Failed to Connect, unmute\n"));
                    
            /* a sub is available but it has failed to establish its media channel, 
               unmute audio and set a failed sub channel to allow volume changes to 
               get processed */       
            codecData->sub_connection_port = DSP_SUB_PORT_FAILED;
            
            /* release tone playing/volume setting lock */            
            codecData->delay_volume_message_sending = FALSE;

            /* set volume levels */
            CsrA2dpDecoderPluginSetLevels(&DECODER->volume, TRUE);
        }                                  
    }
}
