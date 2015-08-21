/******************************************************************************
Copyright Cambridge Silicon Radio Limited 2014 - 2015.
Part of ADK 4.0
 
FILE NAME
    csr_multi_channel_plugin.h
 
DESCRIPTION
    Plugin that implements multichannel audio by utilising multiple hardware
    audio outputs (onboard DAC, I2S, etc...).
*/
 
 
/*!
@file    csr_multi_channel_plugin.h
@brief   Implements multichannel audio by utilising multiple hardware audio
         outputs (onboard DAC, I2S, etc...).
 
         This file provides documentation for the csr_multi_channel_plugin API.
         
         Plugin should be initialised with a suitable output mapping before
         being used, defined by the structures declared in this header file.
*/


#ifndef __CSR_MULTICHANNEL_AUDIO_PLUGIN_H__
#define __CSR_MULTICHANNEL_AUDIO_PLUGIN_H__

/*============================================================================*
 *  SDK Header Files
 *============================================================================*/



/*============================================================================*
 *  Local Header Files
 *============================================================================*/

#include "audio_plugin_if.h"


/*============================================================================*
 *  Public Defintions
 *============================================================================*/

/* DSP Output ports */
#define DSP_OUTPUT_PORT_NONE            0xFFFF
#define DSP_OUTPUT_PORT_SUB_ESCO        0
#define DSP_OUTPUT_PORT_SUB_L2CAP       1
#define DSP_OUTPUT_PORT_RELAY_L2CAP     2
#define DSP_OUTPUT_PORT_USB             3
#define DSP_OUTPUT_PORT_SUB_WIRED       4
#define DSP_OUTPUT_PORT_PRI_LEFT        5
#define DSP_OUTPUT_PORT_PRI_RIGHT       6
#define DSP_OUTPUT_PORT_SEC_LEFT        7
#define DSP_OUTPUT_PORT_SEC_RIGHT       8
#define DSP_OUTPUT_PORT_AUX_LEFT        9
#define DSP_OUTPUT_PORT_AUX_RIGHT       10

/* Turn multi-channel output into a bitmask */
#define CsrMultiChanGetOutputMask(mch_out) ((uint16)1 << mch_out)

/* Helpers for enabling/disabling bits in disable_mask */
#define CsrMultiChanSetOutputDisabled(mask, mch_out) \
    (mask |= CsrMultiChanGetOutputMask(mch_out))
#define CsrMultiChanSetOutputEnabled(mask, mch_out) \
    (mask &= ~CsrMultiChanGetOutputMask(mch_out))

/*============================================================================*
 *  Public Data Types
 *============================================================================*/

/*!
    @brief Multi Channel Output
 
    Allows identification of and looping through each output channel. The first 
    output should always start at 0, and mch_out_max should always be last as
    it is also used to define arrays and loop bounds.
*/
typedef enum __multi_channel_out
{
    mch_out_primary_left = 0,   /*! Left primary (filtered) output */
    mch_out_primary_right,      /*! Right primary (filtered) output */
    mch_out_secondary_left,     /*! Left secondary (filtered) output */
    mch_out_secondary_right,    /*! Right secondary (filtered) output */
    mch_out_wired_sub,          /*! Wired subwoofer (LP filter) output */
    mch_out_aux_left,           /*! Left auxiliary (full range) output */
    mch_out_aux_right,          /*! Right auxiliary (full range) output */
    mch_out_max                 /*! NOT A VALID OUTPUT: For looping/arrays */
} multi_channel_out_t;

/*!
    @brief Audio Output Hardware Type

    Defines the possible audio output hardware types supported by the plugin.
*/
typedef enum __audio_output_hardware_type
{
    audio_output_type_none = 0, /*! NONE: This output should be disabled */
    audio_output_type_dac,      /*! Internal hardware DAC (codec) */
    audio_output_type_i2s,      /*! Digital output to external DAC */
    audio_output_type_bt,       /*! Bluetooth output for subwoofers */
    audio_output_type_spdif     /*! SPDIF output */
} audio_output_hardware_type_t;

/*!
    @brief Audio Output Hardware Instance

    Instance of the audio output hardware type. Some platforms have multiple 
    DAC or I2S outputs, for example.
*/
typedef enum __audio_output_hardware_instance
{
    audio_output_hardware_instance_0 = 0,   /*! First instance */
    audio_output_hardware_instance_1        /*! Second instance */
} audio_output_hardware_instance_t;

/*!
    @brief Audio Output Channel

    Channels for each audio output hardware instance. Each instance usually has
    more than one channel, left and right for example.
*/
typedef enum __audio_output_channel
{
    audio_output_channel_a = 0,  /*! Left or Mono */
    audio_output_channel_b       /*! Right */
} audio_output_channel_t;

/*!
    @brief Audio Endpoint
    
    Defines a hardware audio output. Used in pskey mapping to determine which
    audio sink to connect each output stream to.
*/
typedef struct __audio_endpoint
{
    unsigned unused:8;
    audio_output_hardware_type_t type:4;
    audio_output_hardware_instance_t instance:2;
    audio_output_channel_t channel:2;
} audio_endpoint_t;

/*!
    @brief Multi Channel Hardware Mapping
    
    Hardware mapping for an audio output 'channel'.
*/
typedef struct __multi_channel_hardware_mapping
{
    audio_endpoint_t endpoint;
    int16 volume_trim;
} multi_channel_hardware_mapping_t;

/*!
    @brief Multi Channel Output Group
    
    Describes the logical groupings of outputs in multi_channel_out_t used
    to handle volume control and mute. Each grouping of outputs has an 
    independent system, master and tone gain; the individual outputs have
    their own gain trims as given in multi_channel_hardware_mapping_t. 
    Muting a group mutes all outputs within that group.
    
    multi_channel_group_main contains:
    - mch_out_primary_left
    - mch_out_primary_right
    - mch_out_secondary_left
    - mch_out_secondary_right
    - mch_out_wired_sub
    
    multi_channel_group_aux contains:
    - mch_out_aux_left
    - mch_out_aux_right
*/
typedef audio_plugin_mch_group_t multi_channel_group_t;

/*!
    @brief Multi Channel Output Group Gain Type
    
    Describes gain type for an output group, this may be hardware
    controlled, digital or hybrid mode (a combination of hardware
    for coarse gain adjustments and digital for fine gain adjustments)
*/
typedef enum
{
    multi_channel_gain_hardware,
    multi_channel_gain_digital,
    multi_channel_gain_hybrid,
    multi_channel_gain_invalid
} multi_channel_group_gain_type_t;

/*!
    @brief Multi Channel Output Group Gain
    
    Describes system, master and tone gain for an output group
*/
typedef AUDIO_PLUGIN_SET_VOLUME_COMMON_MSG_T multi_channel_gain_t;

/*!
    @brief Multi Channel Configuration
    
    Configuration type for loading pskey config into. Simply a wrapper for an
    array of hardware mappings, one for each output.
*/
typedef struct __multi_channel_config
{
    multi_channel_hardware_mapping_t mapping[mch_out_max];
    multi_channel_group_gain_type_t gain_type[multi_channel_group_all];
    int16 fixed_hw_gain;
} multi_channel_config_t;

/*!
    @brief Multi Channel Transform
    
    Determines how sources are connected to audio outputs
*/
typedef enum
{
    mch_transform_connect,            /*! Use StreamConnect */
    mch_transform_adpcm,              /*! Use TransformAdpcmDecode */
    mch_transform_connect_and_dispose,/*! Use StreamConnectAndDispose */
    mch_transform_max                 /*! Invalid */
} multi_channel_transform_t;

/*!
    @brief Multi Channel Parameters
    
    Passed to the plugin to carry any additional information required for
    setting up connections at runtime. This information might be different on
    each call to the plugin, unlike the mapping config which stays constant.
    
    Optional parameters should be expected to be FALSE or 0 by default, so that
    memset may be used for initialisation (to 0).
*/
typedef struct __multi_channel_params
{
    uint32 sample_rate;                     /*! Sample rate to run hardware outputs at */
    unsigned disable_mask:mch_out_max;      /*! Allows individual outputs to be disabled */
    multi_channel_transform_t transform:2;  /*! Source is ADPCM (doesn't apply to DSP) */
    unsigned disable_resample:1;            /*! Don't adjust sample rate even when 
                                                configured to re-sample*/
} multi_channel_params_t;

/*============================================================================*
 *  Public Function Prototypes
 *============================================================================*/

/******************************************************************************
NAME:
    CsrMultiChanInitialisePlugin

DESCRIPTION:
    This function gets a pointer to the application malloc'd slot containing
    the multichannel audio configuration data. It is kept in RAM because it is
    not possible to read from the persistent store "on the fly" as this would
    interrupt audio.

PARAMETERS:
    conf    Pointer to malloc'd slot.
    
RETURNS:
    Whether initialisation was successful. TRUE = success, FALSE = error.
*/
bool CsrMultiChanInitialisePlugin(const multi_channel_config_t* const conf);

/******************************************************************************
NAME:
    CsrMultiChanConnectDsp

DESCRIPTION:
    Connects up all the hardware audio outputs to their corresponding DSP ports
    based on the mapping specified in the configuration data.

PARAMETERS:
    params      Captures all additional parameters in a single structure.
    
RETURNS:
    Whether connection was successful. TRUE = success, FALSE = error.
*/
bool CsrMultiChanConnectDsp(multi_channel_params_t* params);

/******************************************************************************
NAME:
    CsrMultiChanConnectStereoSource

DESCRIPTION:
    Connects the two primary hardware audio outputs directly to the two sources
    specified as parameters, in stereo mode (bypassing the DSP). One source may
    be NULL, in which case only one output will be connected (in mono mode).

PARAMETERS:
    source_left     Left source of the stereo input.
    source_right    Right source of the stereo input.
    params          Captures all additional parameters in a single structure.
    
RETURNS:
    Whether connection was successful. TRUE = success, FALSE = error.
*/
bool CsrMultiChanConnectStereoSource(Source source_left,
                                     Source source_right,
                                     multi_channel_params_t* params);

/******************************************************************************
NAME:
    CsrMultiChanConnectSourceToMultiChannelOutput

DESCRIPTION:
    Connects the specified source directly to the specified multichannel audio
    output, in stereo mode (bypassing the DSP).

PARAMETERS:
    source          source to be connected.
    output          multi-channel output to be connected.
    params          Captures all additional parameters in a single structure.

RETURNS:
    Whether connection was successful. TRUE = success, FALSE = error.
*/

bool CsrMultiChanConnectSourceToMultiChannelOutput(Source source,
                                                    multi_channel_out_t output,
                                                    multi_channel_params_t* params);


/******************************************************************************
NAME:
    CsrMultiChanDisconnect

DESCRIPTION:
    Disconnects all connected hardware audio outputs from their input sources
    (regardless of whether they are DSP sources or otherwise).
    
RETURNS:
    Whether disconnection was successful. TRUE = success, FALSE = error.
*/
bool CsrMultiChanDisconnect(void);

/******************************************************************************
NAME:
    CsrMultiChanGetActiveSink

DESCRIPTION:
    Get the first connected audio sink; intended for use with MessageSinkTask

RETURNS:
    The first audio sink that has been connected or NULL if no valid sink is
    connected.
*/
Sink CsrMultiChanGetAudioSink(void);

/******************************************************************************
NAME:
    CsrMultiChanConfigRequiresI2s

DESCRIPTION:
    Returns whether the output mapping contains usage of any I2S hardware, and
    therefore whether the I2S plugin needs to be loaded and initialised,
    regardless of the state of any external I2S devices.
    
RETURNS:
    Whether I2S is required. TRUE = yes, FALSE = no.
*/
bool CsrMultiChanConfigRequiresI2s(void);

/******************************************************************************
NAME:
    CsrMultiChanI2sActive

DESCRIPTION:
    Returns whether any external I2S devices are currently connected and active.
    
    I2S devices are only activated if and when they are required. This function
    can therefore be used as a reliable indication that a device is connected
    and actually going to be used.
    
RETURNS:
    Whether an I2S device is active. TRUE = yes, FALSE = no.
*/
bool CsrMultiChanI2sActive(void);

/******************************************************************************
NAME:
    CsrMultiChannelGetSampleRate

DESCRIPTION:
    Returns the sample rate that will be used when connecting audio outputs
    
    This will be adjusted if I2S ports are to be connected and an I2S 
    re-sampling rate has been configured. If no I2S re-sampling is to be
    used then the value returned will be the sample_rate from params.
    
PARAMETERS:
    params     The parameters that will be used when connecting audio
    
RETURNS:
    Sample rate in Hz that will be used when connecting audio
*/
uint32 CsrMultiChannelGetSampleRate(multi_channel_params_t* params);

/******************************************************************************
NAME:
    CsrMultiChanGetOutputType

DESCRIPTION:
    Gets the audio output hardware type of the sink mapped to an output.

PARAMETERS:
    mch_out     Output to get the output type for.
    
RETURNS:
    The output type.
*/
AUDIO_OUTPUT_TYPE_T CsrMultiChanGetOutputType(multi_channel_out_t mch_out);

/******************************************************************************
NAME:
    CsrMultiChanSendDspOutputTypesMsg

DESCRIPTION:
    Fills a AUDIO_PLUGIN_SET_MULTI_CHANNEL_OUTPUT_TYPES_MSG with the hardware
    type of each output for sending to the DSP.

PARAMETERS:
    AUDIO_PLUGIN_SET_MULTI_CHANNEL_OUTPUT_TYPES_MSG_T* m    Pointer to message.
    
RETURNS:
    TRUE on success, FALSE on failure.
*/
bool CsrMultiChanGetDspOutputTypesMsg(AUDIO_PLUGIN_SET_MULTI_CHANNEL_OUTPUT_TYPES_MSG_T* msg);

/******************************************************************************
NAME:
    CsrMultiChanGainGetDigital

DESCRIPTION:
    Get the gain information required to set digital gains. 
    
    This function will set the master gain to 0dB if hardware gain is used. 
    
    Trim values are set depending on the output type for a channel. DAC trims
    are applied in digital gain so will be set in gain_info. I2S trims are 
    applied in hardware when hardware control is used, so trims for I2S 
    channels will only be set in gain_info if digital gain is used.

PARAMETERS:
    group The output group to apply the volume change to
    master_gain The master gain to apply. This is the desired output gain 
                for the group (in dB/60)
    tone_gain The tone gain to apply. This is the desired output gain for 
              the group when playing tones (in dB/60)
    gain_info The gain_info structure will be populated with all gains that 
              need to be sent to the DSP application to allow it to configure 
              digital gain.
*/
void CsrMultiChanGainGetDigital(const multi_channel_group_t group, 
                                const int16 master_gain, const int16 tone_gain,
                                multi_channel_gain_t* gain_info);

/******************************************************************************
NAME:
    CsrMultiChanGainGetDigitalOnly

DESCRIPTION:
    Behaves much the same as CsrMultiChanGainGetDigital, however this function
    ignores the control type and always fills out the master gain and all 
    trims. This is mainly required for TWS which sends all gain information to
    the DSP.

PARAMETERS:
    group The output group to apply the volume change to
    master_gain The master gain to apply. This is the desired output gain 
                for the group (in dB/60)
    tone_gain The tone gain to apply. This is the desired output gain for 
              the group when playing tones (in dB/60)
    gain_info The gain_info structure will be populated with all gains that 
              need to be sent to the DSP application to allow it to configure 
              digital gain.
*/
void CsrMultiChanGainGetDigitalOnly(const multi_channel_group_t group, 
                                    const int16 master_gain, const int16 tone_gain,
                                    multi_channel_gain_t* gain_info);

/******************************************************************************
NAME:
    CsrMultiChanGainSetHardware

DESCRIPTION:
    Apply hardware gains as appropriate for the gain type used. 
    
    When the group is configured to use digital gain this function will set the
    hardware gain to the fixed level specified in configuration. 
    
    When the group is configured to use hardware gain then the hardware gain 
    will be set to the requested value master_gain. 
    
    When the group is configured to use hybrid gain the hardware gain will be 
    set to the required level, the digital gain must be separately set to the 
    gain obtained by calling CsrMultiChanGainGetDigital.

PARAMETERS:
    group The output group to apply the volume change to
    master_gain The master gain to apply. This is the desired output gain 
                for the group (in dB/60)
    gain_info This can be used to override the channel trims configured
              at initialisation. If NULL then configured trims will be used.
    
*/
void CsrMultiChanGainSetHardware(const multi_channel_group_t group,
                                 const int16 master_gain,
                                 const multi_channel_gain_t* gain_info);

/******************************************************************************
NAME:
    CsrMultiChanGainSetHardwareOnly

DESCRIPTION:
    Apply hardware gains as requested by caller.
    
    This function will always set the hardware gain to the value requested in
    master_gain, regardless of the gain type configured for the group.

PARAMETERS:
    group The output group to apply the volume change to
    master_gain The master gain to apply. This is the desired output gain 
                for the group (in dB/60)
    
*/
void CsrMultiChanGainSetHardwareOnly(const multi_channel_group_t group,
                                     const int16 master_gain);

/******************************************************************************
NAME:
    CsrMultiChanGainGetType

DESCRIPTION:
    Get the gain type for a group (as specified in the multi-channel 
    configuration).

PARAMETERS:
    group The output group for which to get the gain type.
    
RETURNS:
    The gain type configured for the group
*/
multi_channel_group_gain_type_t CsrMultiChanGainGetType(const multi_channel_group_t group);

#endif /* __CSR_MULTICHANNEL_AUDIO_PLUGIN_H__ */
