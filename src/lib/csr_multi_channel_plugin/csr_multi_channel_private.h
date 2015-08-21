/******************************************************************************
Copyright Cambridge Silicon Radio Limited 2014 - 2015.
Part of ADK 4.0
 
FILE NAME
    csr_multi_channel_private.h
 
DESCRIPTION
    Private data/functions for multi-channel lib
*/

#ifndef __CSR_MULTICHANNEL_AUDIO_PRIVATE_H__
#define __CSR_MULTICHANNEL_AUDIO_PRIVATE_H__

/*============================================================================*
 *  Private Definitions
 *============================================================================*/

#define MCH_OUT_NONE    mch_out_max

/* Convenience Function Macros */
#define forEachOutput(mch_out) for(mch_out=0; mch_out<mch_out_max; mch_out++)

/*============================================================================*
 *  Private Data Types
 *============================================================================*/

/*!
    @brief Multi Channel State Variables
    
    Used internally by the plugin to maintain a record of its current state.
*/
typedef struct __multi_channel_state
{
    unsigned connected:1;           /*! Whether connection has take place */
    unsigned i2s_devices_active:1;  /*! Whether any I2S devices are active */
    multi_channel_params_t params;  /*! Latest params passed on connection */
} multi_channel_state_t;

/*============================================================================*
 *  Private Function Prototypes
 *============================================================================*/
 
extern const multi_channel_config_t* config;

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
Sink csrMultiChanGetSink(multi_channel_out_t mch_out);

/******************************************************************************
NAME:
    csrMultiChanGainMuteHardware

DESCRIPTION:
    Mutes the external hardware (e.g. I2S amps, DAC) associated with an output,
    regardless of the gain type and trims set for it in the configuration. Also
    mutes it at the stream level. Used when connecting ports to ensure there
    are no pops, clicks, e.t.c.

PARAMETERS:
    mch_out     Output to hard mute.
    
RETURNS:
    Nothing.
*/
void csrMultiChanGainMuteHardware(multi_channel_out_t mch_out);

#endif /*__CSR_MULTICHANNEL_AUDIO_PRIVATE_H__*/
