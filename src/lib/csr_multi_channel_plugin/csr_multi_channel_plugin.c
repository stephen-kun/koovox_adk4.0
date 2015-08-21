/******************************************************************************
Copyright Cambridge Silicon Radio Limited 2014 - 2015.
Part of ADK 4.0
 
FILE NAME
    csr_multi_channel_plugin.c
 
DESCRIPTION
    Plugin that implements multichannel audio by utilising multiple hardware
    audio outputs (onboard DAC, I2S, etc...).
*/
 
 
/*============================================================================*
 *  SDK Header Files
 *============================================================================*/

#include "csr_multi_channel_plugin.h"
#include "csr_multi_channel_private.h"

#ifdef ANC
#include "anc.h"
#endif

#include <codec.h>
#include <panic.h>
#include <pio.h>
#include <print.h>
#include <stream.h>
#include <stdlib.h>
#include <sink.h>
#include <string.h>
#include <transform.h>


/*============================================================================*
 *  Local Header Files
 *============================================================================*/

#include "csr_i2s_audio_plugin.h"

/*============================================================================*
 *  Private Definitions
 *============================================================================*/

/* Hardware Specific Details */
#define PIO_I2S_2_PCM_IN        (4)
#define PIO_I2S_2_PCM_OUT       (5)
#define PIO_I2S_2_PCM_SYNC      (6)
#define PIO_I2S_2_PCM_CLK       (7)

/* Error Return Values */
#define AUDIO_HARDWARE_NONE     (audio_hardware)(0xFFFF)
#define AUDIO_INSTANCE_NONE     (audio_instance)(0xFFFF)
#define AUDIO_CHANNEL_NONE      (audio_channel)(0xFFFF)

/* Macro to check whether an output has been disabled in disable_mask */
#define CsrMultiChanOutputDisabled(mch_out, disable_mask) \
    ((CsrMultiChanGetOutputMask(mch_out) & disable_mask) == CsrMultiChanGetOutputMask(mch_out))
#define CsrMultiChanOutputEnabled(mch_out, disable_mask) \
    (!CsrMultiChanOutputDisabled(mch_out, disable_mask))

/*============================================================================*
 *  Private Data Types
 *============================================================================*/



/*============================================================================*
 *  Private Data
 *============================================================================*/

/* Multichannel audio configuration data */
const multi_channel_config_t* config = NULL;
/* Global state variable */
static multi_channel_state_t state;


/*============================================================================*
 *  Private Function Prototypes
 *============================================================================*/

static bool connect(Source* sources, multi_channel_params_t* params);
static bool i2sHardwareInitialise(void);
static bool i2sOutputEnabled(multi_channel_params_t* params);
static Sink configureSink(multi_channel_out_t mch_out,
                          multi_channel_params_t* params);
static uint16 getDspPort(multi_channel_out_t mch_out);
static audio_hardware getAudioHardwareType(multi_channel_out_t mch_out);
static audio_instance getAudioHardwareInstance(multi_channel_out_t mch_out);
static audio_channel getAudioHardwareChannel(multi_channel_out_t mch_out);
#if defined(DEBUG_PRINT_ENABLED)
static char* debugGetStringAudioType(audio_hardware type);
#endif /* DEBUG_PRINT_ENABLED */


/*============================================================================*
 * Public Function Implementations
 *============================================================================*/

/******************************************************************************/
bool CsrMultiChanInitialisePlugin(const multi_channel_config_t* const conf)
{
    if (conf == NULL)
    {
        /* Passed in pointer was NULL, return error. */
        PRINT(("MULTICHAN: Failed to initialise - NULL config\n"));
        return FALSE;
    }
    
    /* Store pointer for later access. */
    config = conf;
    
    /* Initialise global state variables. */
    memset(&state, 0, sizeof(multi_channel_state_t));
    
    /* Initialise internal I2S hardware. */
    if (!i2sHardwareInitialise())
    {
        /* Failed to perform required initialisation, return error. */
        PRINT(("MULTICHAN: Failed to initialise - I2S hardware\n"));
        return FALSE;
    }
    
    PRINT(("MULTICHAN: Initialised successfully\n"));
    
    return TRUE;
}

/******************************************************************************/
bool CsrMultiChanConnectDsp(multi_channel_params_t* params)
{
    multi_channel_out_t mch_out;  /* Loop variable */
    Source* sources;
    
    if (config == NULL)
    {
        /* Plugin is not yet initialised, return error. */
        PRINT(("MULTICHAN: Connect DSP failed - Not initialised\n"));
        return FALSE;
    }
    
    if (state.connected)
    {
        /* Already connected, return error. */
        PRINT(("MULTICHAN: Connect DSP failed - Already Connected\n"));
        return FALSE;
    }
    
    if (params->sample_rate == 0)
    {
        /* Invalid sample rate, return error. */
        PRINT(("MULTICHAN: Connect DSP failed - Invalid sample rate\n"));
        return FALSE;
    }
    
    /* Allocate sources (default unused sources to NULL). */
    sources = PanicUnlessMalloc(sizeof(Source) * mch_out_max);
    memset(sources, 0, (sizeof(Source) * mch_out_max));
    
    /* Get the source for each DSP port in turn. */
    forEachOutput(mch_out)
    {
        uint16 dsp_port;
        
        if (getAudioHardwareType(mch_out) == AUDIO_HARDWARE_NONE)
        {
            /* No hardware mapping for this output, move onto the next. */
            continue;
        }
        
        dsp_port = getDspPort(mch_out);
        
        if (dsp_port == DSP_OUTPUT_PORT_NONE)
        {
            /* This output is not supported or doesn't exist. */
            continue;
        }
        
        PRINT(("MULTICHAN: Connecting %s_%u channel %u to DSP port %u\n",
               debugGetStringAudioType(getAudioHardwareType(mch_out)),
               getAudioHardwareInstance(mch_out),
               getAudioHardwareChannel(mch_out),
               dsp_port));
        
        sources[mch_out] = StreamKalimbaSource(dsp_port);
    }
    
    /* Connect the DSP sources to their appropriate hardware outputs. */
    if (!connect(sources, params))
    {
        /* Configuring and connecting sinks failed somewhere, return error. */
        PRINT(("MULTICHAN: Connect DSP failed - Connecting sinks error\n"));
        free(sources);
        return FALSE;
    }
    
    /* Update state variables */
    state.params = *params;
    state.connected = TRUE;
    
    PRINT(("MULTICHAN: Connect DSP successful\n"));
    free(sources);
    return TRUE;
}

/******************************************************************************/
bool CsrMultiChanConnectStereoSource(Source source_left,
                                     Source source_right,
                                     multi_channel_params_t* params)
{
    Source* sources;
    bool success;

    if(config == NULL || state.connected || !(source_left || source_right) || params->sample_rate == 0)
    {
        PRINT(("MULTICHAN: Connect source failed - "));
        PRINT(("%s", config == NULL ? "Not Initialised " : ""));
        PRINT(("%s", state.connected ? "Already Connected " : ""));
        PRINT(("%s", !(source_left || source_right) ? "Both Sources NULL " : ""));
        PRINT(("Sample rate %ld\n", params->sample_rate));
        return FALSE;
    }

    sources = PanicUnlessMalloc(sizeof(Source) * mch_out_max);
    memset(sources, 0, (sizeof(Source) * mch_out_max));

    sources[mch_out_primary_left] = source_left;
    sources[mch_out_primary_right] = source_right;

    PRINT(("MULTICHAN: Connecting %s_%u channel %u direct to Source 0x%04x\n",
               debugGetStringAudioType(getAudioHardwareType(mch_out_primary_left)),
               getAudioHardwareInstance(mch_out_primary_left),
               getAudioHardwareChannel(mch_out_primary_left),
               (uint16)sources[mch_out_primary_left]));
    PRINT(("MULTICHAN: Connecting %s_%u channel %u direct to Source 0x%04x\n",
               debugGetStringAudioType(getAudioHardwareType(mch_out_primary_right)),
               getAudioHardwareInstance(mch_out_primary_right),
               getAudioHardwareChannel(mch_out_primary_right),
               (uint16)sources[mch_out_primary_right]));

    /* Connect the sources to the primary hardware outputs. */
    success = connect(sources, params);
    free(sources);

    if (!success)
    {
        /* Configuring and connecting sinks failed somewhere, return error. */
        PRINT(("MULTICHAN: Connect sources failed - Connecting sinks error\n"));
        return FALSE;
    }

    /* Update state variables */
    state.params = *params;
    state.connected = TRUE;

    PRINT(("MULTICHAN: Connect %s source successful\n",
           (source_left && source_right && (source_left != source_right)) ? "stereo" : "mono"));
    return TRUE;
}

/******************************************************************************/
bool CsrMultiChanConnectSourceToMultiChannelOutput(Source source,
                                                    multi_channel_out_t output,
                                                    multi_channel_params_t* params)
{
    Source* sources;
    bool success;

    if(config == NULL || state.connected || (!source) || params->sample_rate == 0)
    {
        PRINT(("MULTICHAN: Connect source failed - "));
        PRINT(("%s", config == NULL ? "Not Initialised " : ""));
        PRINT(("%s", state.connected ? "Already Connected " : ""));
        PRINT(("%s", (!source) ? "Source NULL " : ""));
        PRINT(("Sample rate %ld\n", params->sample_rate));
        return FALSE;
    }

    sources = PanicUnlessMalloc(sizeof(Source) * mch_out_max);
    memset(sources, 0, (sizeof(Source) * mch_out_max));

    sources[output] = source;

    PRINT(("MULTICHAN: Connecting %s_%u channel %u direct to Source 0x%04x\n",
                   debugGetStringAudioType(getAudioHardwareType(output)),
                   getAudioHardwareInstance(output),
                   getAudioHardwareChannel(output),
                   (uint16)sources[output]));

    success = connect(sources, params);
    free(sources);

    if (!success)
    {
        /* Configuring and connecting sinks failed somewhere, return error. */
        PRINT(("MULTICHAN: Connect sources failed - Connecting sinks error\n"));
        return FALSE;
    }

    /* Update state variables */
    state.params = *params;
    state.connected = TRUE;

    PRINT(("MULTICHAN: Connect source to multi-channel output successful\n"));
    return TRUE;
}

/******************************************************************************/
bool CsrMultiChanDisconnect(void)
{
    multi_channel_out_t mch_out;  /* Loop variable */
    bool at_least_one_mapping = FALSE;
    
    if (config == NULL)
    {
        /* Plugin is not yet initialised, return error. */
        PRINT(("MULTICHAN: Disconnect failed - Not initialised\n"));
        return FALSE;
    }
    
    if (!state.connected)
    {
        /* Not connected yet, return error. */
        PRINT(("MULTICHAN: Disconnect failed - Not connected\n"));
        return FALSE;
    }
    
    /* Disconnect each output in turn. */
    forEachOutput(mch_out)
    {
        Sink audio_sink = csrMultiChanGetSink(mch_out);
        
        if (audio_sink == NULL)
        {
            /* No mapping for this output. Move on to the next. */
            continue;
        }
        
        at_least_one_mapping = TRUE;
        
        if (CsrMultiChanOutputDisabled(mch_out, state.params.disable_mask))
        {
            /* Mapping exists for this output, but it wasn't connected. */
            continue;
        }
        
        /* Mute before disconnecting streams so no 'pops' or 'clicks'. */
        csrMultiChanGainMuteHardware(mch_out);
        
        StreamDisconnect(0, audio_sink);
        PanicFalse(SinkClose(audio_sink));
    }
    
    if (!at_least_one_mapping)
    {
        /* No mappings in config, return error. */
        PRINT(("MULTICHAN: Disconnect failed - No enabled mappings\n"));
        return FALSE;
    }
    
    /* Update state variables */
    state.connected = FALSE;
    
    if (state.i2s_devices_active)
    {
        /* Shut down I2S devices */
        PRINT(("MULTICHAN: Shutting down I2S devices...\n"));
        CsrShutdownI2SDevice();
        state.i2s_devices_active = FALSE;
    }
    
    PRINT(("MULTICHAN: Disconnect successful\n"));
    return TRUE;
}

/******************************************************************************/
Sink CsrMultiChanGetAudioSink(void)
{
    multi_channel_out_t mch_out;
    
    /* Return the first valid audio sink */
    forEachOutput(mch_out)
    {
        Sink audio_sink;
        bool disabled = CsrMultiChanOutputDisabled(mch_out, state.params.disable_mask);
        
        if (disabled)
        {
            /* No source for this output, or disabled, move onto the next. */
            continue;
        }
        
        audio_sink = csrMultiChanGetSink(mch_out);
        
        if(audio_sink)
            return audio_sink;
    }
    
    return NULL;
}

/******************************************************************************/
bool CsrMultiChanConfigRequiresI2s(void)
{
    multi_channel_out_t mch_out;  /* Loop variable */
    
    if (config == NULL)
    {
        /* Plugin is not initialised, so no I2S required. */
        return FALSE;
    }
    
    /* Loop through and check each output mapping. */
    forEachOutput(mch_out)
    {
        if (config->mapping[mch_out].endpoint.type == audio_output_type_i2s)
        {
            /* I2S output found, no need to continue. */
            return TRUE;
        }
    }
    
    /* No I2S outputs detected. */
    return FALSE;
}

/******************************************************************************/
bool CsrMultiChanI2sActive(void)
{
    if (config == NULL)
    {
        /* Plugin is not initialised, so I2S can't be. */
        return FALSE;
    }
    
    return state.i2s_devices_active;
}

/******************************************************************************/
uint32 CsrMultiChannelGetSampleRate(multi_channel_params_t* params)
{
    /* If an I2S output is to be used then return the re-sampling frequency */
    if(i2sOutputEnabled(params) && !params->disable_resample)
    {
        return CsrI2SGetOutputResamplingFrequencyForI2s(params->sample_rate);
    }
    /* Return the sample_rate from params */
    return params->sample_rate;
}

/******************************************************************************/
AUDIO_OUTPUT_TYPE_T CsrMultiChanGetOutputType(multi_channel_out_t mch_out)
{
    if ((config == NULL) || (mch_out == mch_out_max))
    {
        return OUTPUT_INTERFACE_TYPE_NONE;
    }
    
    switch (config->mapping[mch_out].endpoint.type)
    {
        case audio_output_type_dac:
            return OUTPUT_INTERFACE_TYPE_DAC;
        
        case audio_output_type_i2s:
            return OUTPUT_INTERFACE_TYPE_I2S;
            
        case audio_output_type_spdif:
            return OUTPUT_INTERFACE_TYPE_SPDIF;
        
        case audio_output_type_bt:
            /* Handled by specific decoder plugin, fall through. */
        case audio_output_type_none:
        default:
            /* No mapping or unsupported output type. */
            return OUTPUT_INTERFACE_TYPE_NONE;
    }
}

/******************************************************************************/
bool CsrMultiChanGetDspOutputTypesMsg(AUDIO_PLUGIN_SET_MULTI_CHANNEL_OUTPUT_TYPES_MSG_T* msg)
{
    multi_channel_out_t mch_out;    /* Loop variable */
    
    if (config == NULL || msg == NULL)
    {
        return FALSE;
    }
    
    /* Loop through each output mapping. */
    forEachOutput(mch_out)
    {
        msg->out_type[mch_out] = CsrMultiChanGetOutputType(mch_out);
    }
    
    return TRUE;
}


/*============================================================================*
 *  Private Function Implementations
 *============================================================================*/

/******************************************************************************
NAME:
    connect

DESCRIPTION:
    Connects sinks for all output channels to the sources specified in the
    supplied parameters.

PARAMETERS:
    cources     Pointer to an array of mch_out_max sources.
    params      Connection parameters containing configuration data.
    
RETURNS:
    The sink that was successfully configured, NULL otherwise.
*/
static bool connect(Source* sources, multi_channel_params_t* params)
{
    multi_channel_out_t mch_out;  /* Loop variable */
    Sink audio_sink;
    Sink last_valid_sink = NULL;
    bool disabled;
        
    params->sample_rate = CsrMultiChannelGetSampleRate(params);

    /* Carry out I2S-specific set up. */
    if (i2sOutputEnabled(params))
    {
        /* Check if we need to initialise I2S devices. */
        if (!state.i2s_devices_active)
        {
            PRINT(("MULTICHAN: Initialising I2S devices...\n"));
            
            /* Initialise the I2S device hardware. */
            CsrInitialiseI2SDevice(params->sample_rate);
            
            /* Only needs to happen once. */
            state.i2s_devices_active = TRUE;
        }
    }
    
    /* Configure and sync the sink for each output. */
    forEachOutput(mch_out)
    {
        disabled = CsrMultiChanOutputDisabled(mch_out, params->disable_mask);
        
        /* Check if we actually need to open the sink for this output. */
        if (sources[mch_out] == NULL || disabled)
        {
            /* No source for this output, or disabled, move onto the next. */
            continue;
        }
        
        audio_sink = configureSink(mch_out, params);
        
        if (audio_sink == NULL)
        {
            /* No mapping or sink failed to open. Move on to the next. */
            continue;
        }
        
        if (last_valid_sink)
        {
            PanicFalse(SinkSynchronise(last_valid_sink, audio_sink));
        }
        
        last_valid_sink = audio_sink;
    }
    
    /* Check if there are any sinks to connect before proceeding. */
    if (last_valid_sink == NULL)
    {
        /* No mappings in config, all disabled, or all failed, return error. */
        PRINT(("MULTICHAN: Connect failed - No sinks to connect\n"));
        return FALSE;
    }
    
    /* Connect up each valid sink to its source and un-mute. Must happen after
     * synchronisation, hence the need for a second loop and duplicate checks.
     */
    forEachOutput(mch_out)
    {
        disabled = CsrMultiChanOutputDisabled(mch_out, params->disable_mask);
        
        /* Check if we actually need to connect the sink for this output. */
        if (sources[mch_out] == NULL || disabled)
        {
            /* No source for this output, or disabled, move onto the next. */
            continue;
        }
        
        audio_sink = csrMultiChanGetSink(mch_out);
    
        if (audio_sink == NULL)
        {
            /* No mapping or sink failed to open. Move on to the next. */
            continue;
        }
        
        switch(params->transform)
        {
            case mch_transform_adpcm:
                PanicFalse(TransformStart(TransformAdpcmDecode(sources[mch_out], audio_sink)));
            break;
            
            case mch_transform_connect_and_dispose:
                PanicFalse(StreamConnectAndDispose(sources[mch_out], audio_sink));
            break;
            
            case mch_transform_connect:
            default:
                PanicFalse(StreamConnect(sources[mch_out], audio_sink));
            break;
        }
        
        /* Un-mute after connecting streams so no 'pops' or 'clicks'. */
        PanicFalse(SinkConfigure(audio_sink, STREAM_AUDIO_MUTE_ENABLE, FALSE));
    }
    
    /* Update state variables */
    state.params = *params;
    state.connected = TRUE;
    
    return TRUE;
}

/******************************************************************************
NAME:
    i2sHardwareInitialise

DESCRIPTION:
    Performs internal hardware initialisation for I2S, such as configuring the 
    required PIOs. Note that external I2S devices e.g. I2S amplifiers are
    initialised separately, on a per connection basis. This is handled by the
    I2S plugin.
    
RETURNS:
    Whether the I2S hardware was initialised. TRUE = success, FALSE = error.
*/
static bool i2sHardwareInitialise(void)
{
    multi_channel_out_t mch_out;  /* Loop variable */
    
    /* Loop through and check each output for usage of 2nd I2S instance. */
    forEachOutput(mch_out)
    {
        if (config->mapping[mch_out].endpoint.type == audio_output_type_i2s &&
            config->mapping[mch_out].endpoint.instance == audio_output_hardware_instance_1)
        {
            /* 2nd instance found, no need to continue searching. Return success
               based on whether all PIOs can be set to the correct function. */
            return (PioSetFunction(PIO_I2S_2_PCM_IN, PCM_IN) && 
                    PioSetFunction(PIO_I2S_2_PCM_OUT, PCM_OUT) &&
                    PioSetFunction(PIO_I2S_2_PCM_SYNC, PCM_SYNC) &&
                    PioSetFunction(PIO_I2S_2_PCM_CLK, PCM_CLK));
        }
    }
    
    /* No 2nd instance found, so no need to do anything. */
    return TRUE;
}

/******************************************************************************
NAME:
    i2sOutputEnabled

DESCRIPTION:
    Checks whether any output has been configured to use the I2S hardware and
    has not been disabled in the supplied parameters. Used to determine whether
    any I2S devices need to be initialised for a specific connection request.

PARAMETERS:
    params      Pointer to requested parameters that contain the disable mask.
    
RETURNS:
    Whether I2S is going to be used. TRUE = yes, FALSE = no.
*/
bool i2sOutputEnabled(multi_channel_params_t* params)
{
    multi_channel_out_t mch_out;  /* Loop variable */
    
    /* Loop through and check each output mapping. */
    forEachOutput(mch_out)
    {
        if (config->mapping[mch_out].endpoint.type == audio_output_type_i2s &&
            CsrMultiChanOutputEnabled(mch_out, params->disable_mask))
        {
            /* Enabled I2S output found, no need to continue. */
            return TRUE;
        }
    }
    
    /* No enabled I2S outputs detected. */
    return FALSE;
}

/******************************************************************************
NAME:
    configureSink

DESCRIPTION:
    Configures the sink mapped to an output with the required parameters.

PARAMETERS:
    mch_out     Output to configure the mapped hardware output of.
    params      Parameters to configure.
    
RETURNS:
    The sink that was successfully configured, NULL otherwise.
*/
static Sink configureSink(multi_channel_out_t mch_out,
                          multi_channel_params_t* params)
{
    Sink audio_sink = csrMultiChanGetSink(mch_out);
    
    if (audio_sink == NULL)
    {
#ifdef DEBUG_PRINT_ENABLED
        if (getAudioHardwareType(mch_out) != AUDIO_HARDWARE_NONE &&
            getAudioHardwareInstance(mch_out) != AUDIO_INSTANCE_NONE &&
            getAudioHardwareChannel(mch_out) != AUDIO_CHANNEL_NONE)
        {
            PRINT(("MULTICHAN: Error - Failed to open Sink %s_%u channel %u)\n",
                   debugGetStringAudioType(getAudioHardwareType(mch_out)),
                   getAudioHardwareInstance(mch_out),
                   getAudioHardwareChannel(mch_out)));
        }
#endif
        /* No mapping or sink failed to open, return error. */
        return NULL;
    }

#ifdef ANC

    /* If using ANC then only DAC output type allowed. Configuration also needs
       to be done using the ANC library */
    PanicFalse(config->mapping[mch_out].endpoint.type == audio_output_type_dac);
    AncConfigureDacs(params->sample_rate);

#else /* ANC */

    /* Configure output rate */
    switch(config->mapping[mch_out].endpoint.type)
    {
        case audio_output_type_i2s:
            CsrI2SAudioOutputConnectConfigureSink(audio_sink, params->sample_rate);
        break;
        
        case audio_output_type_spdif:
            PanicFalse(SinkConfigure(audio_sink, STREAM_SPDIF_OUTPUT_RATE, params->sample_rate));
        break;
        
        case audio_output_type_dac:
            PanicFalse(SinkConfigure(audio_sink, STREAM_CODEC_OUTPUT_RATE, params->sample_rate));
        break;
        
        default:
            /* Should never get here as audio_sink would be NULL */
            Panic();
        break;
    }

#endif /* ANC */

    /* Mute before connecting streams so no 'pops' or 'clicks'. */
    csrMultiChanGainMuteHardware(mch_out);
    
    return audio_sink;
}

/******************************************************************************
NAME:
    csrMultiChanGetSink

DESCRIPTION:
    Gets the sink for a specified output channel, if a mapping exists.

PARAMETERS:
    mch_out     Output to get the sink for.
    
RETURNS:
    The sink, or NULL if there was an error.
*/
Sink csrMultiChanGetSink(multi_channel_out_t mch_out)
{
    return StreamAudioSink(getAudioHardwareType(mch_out),
                           getAudioHardwareInstance(mch_out),
                           getAudioHardwareChannel(mch_out));
}

/******************************************************************************
NAME:
    getDspPort

DESCRIPTION:
    Gets the DSP port number for an output.

PARAMETERS:
    mch_out     The output to get the DSP port number for.
    
RETURNS:
    The port number as a uint16, or DSP_OUTPUT_PORT_NONE if there was an error.
*/
static uint16 getDspPort(multi_channel_out_t mch_out)
{
    switch (mch_out)
    {
        case mch_out_primary_left:
            return DSP_OUTPUT_PORT_PRI_LEFT;
        
        case mch_out_primary_right:
            return DSP_OUTPUT_PORT_PRI_RIGHT;
        
        case mch_out_secondary_left:
            return DSP_OUTPUT_PORT_SEC_LEFT;
        
        case mch_out_secondary_right:
            return DSP_OUTPUT_PORT_SEC_RIGHT;
        
        case mch_out_aux_left:
            return DSP_OUTPUT_PORT_AUX_LEFT;
        
        case mch_out_aux_right:
            return DSP_OUTPUT_PORT_AUX_RIGHT;
        
        case mch_out_wired_sub:
            return DSP_OUTPUT_PORT_SUB_WIRED;
        
        default:
            return DSP_OUTPUT_PORT_NONE;
    }
}

/******************************************************************************
NAME:
    getAudioHardwareType

DESCRIPTION:
    Gets the hardware type of an audio sink mapped to an output. Must only be
    called after successful initialisation (i.e. 'config' is valid).

PARAMETERS:
    mch_out     Output to get the hardware type of.
    
RETURNS:
    The hardware type, or AUDIO_HARDWARE_NONE if there was an error.
*/
static audio_hardware getAudioHardwareType(multi_channel_out_t mch_out)
{
    switch (config->mapping[mch_out].endpoint.type)
    {
        case audio_output_type_dac:
            return AUDIO_HARDWARE_CODEC;
        
        case audio_output_type_i2s:
            return AUDIO_HARDWARE_I2S;
        
        case audio_output_type_spdif:
            return AUDIO_HARDWARE_SPDIF;
        
        case audio_output_type_none:
        default:
            /* No mapping or unsupported output type, return error. */
            return AUDIO_HARDWARE_NONE;
    }
}

/******************************************************************************
NAME:
    getAudioHardwareInstance

DESCRIPTION:
    Gets the hardware instance of an audio sink mapped to an output. Must only
    be called after successful initialisation (i.e. 'config' is valid).

PARAMETERS:
    mch_out     Output to get the hardware instance for.
    
RETURNS:
    The hardware instance, or AUDIO_INSTANCE_NONE if there was an error.
*/
static audio_instance getAudioHardwareInstance(multi_channel_out_t mch_out)
{
    switch (config->mapping[mch_out].endpoint.instance)
    {
        case audio_output_hardware_instance_0:
            return AUDIO_INSTANCE_0;
        
        case audio_output_hardware_instance_1:
            return AUDIO_INSTANCE_1;
        
        default:
            /* Control should never reach here, return error. */
            return AUDIO_INSTANCE_NONE;
    }
}

/******************************************************************************
NAME:
    getAudioHardwareChannel

DESCRIPTION:
    Gets the hardware channel of an audio sink mapped to an output. Must only 
    be called after successful initialisation (i.e. 'config' is valid).

PARAMETERS:
    mch_out     Output to get the hardware channel for.
    
RETURNS:
    The hardware channel, or AUDIO_CHANNEL_NONE if there was an error.
*/
static audio_channel getAudioHardwareChannel(multi_channel_out_t mch_out)
{
    /* Channel depends on hardware type */
    switch (config->mapping[mch_out].endpoint.type)
    {
        case audio_output_type_dac:
        {
            switch (config->mapping[mch_out].endpoint.channel)
            {
                case audio_output_channel_a:
                    return AUDIO_CHANNEL_A;
                
                case audio_output_channel_b:
                    return AUDIO_CHANNEL_B;
                
                default:
                break;
            }
        }
        break;
        
        case audio_output_type_i2s:
        {
            switch (config->mapping[mch_out].endpoint.channel)
            {
                case audio_output_channel_a:
                    return AUDIO_CHANNEL_SLOT_0;
                
                case audio_output_channel_b:
                    return AUDIO_CHANNEL_SLOT_1;
                
                default:
                break;
            }
        }
        break;
        
        case audio_output_type_spdif:
        {
            switch (config->mapping[mch_out].endpoint.channel)
            {
                case audio_output_channel_a:
                    return SPDIF_CHANNEL_A;
                    
                case audio_output_channel_b:
                    return SPDIF_CHANNEL_B;
                
                default:
                break;
            }
        }
        break;
        
        case audio_output_type_none:
        default:
        break;
    }
    
    /* No mapping or unsupported output type, return error. */
    return AUDIO_CHANNEL_NONE;
}

#if defined(DEBUG_PRINT_ENABLED)
/******************************************************************************
NAME:
    debugGetStringAudioType

DESCRIPTION:
    Gets the string representing a hardware type for outputting debug messages.
    
PARAMETERS:
    type    Hardware type to get the string of.
    
RETURNS:
    String literal.
*/
static char* debugGetStringAudioType(audio_hardware type)
{
    /* Channel depends on hardware type */
    switch (type)
    {
        case AUDIO_HARDWARE_CODEC:
            return "AUDIO_HARDWARE_CODEC";
        
        case AUDIO_HARDWARE_I2S:
            return "AUDIO_HARDWARE_I2S";
        
        case AUDIO_HARDWARE_SPDIF:
            return "AUDIO_HARDWARE_SPDIF";
        
        default:
            return "<Unknown>";
    }
}
#endif /* DEBUG_PRINT_ENABLED */
