// *****************************************************************************
// Copyright Cambridge Silicon Radio Limited 2003 - 2015.        http://www.csr.com
// Part of ADK 4.0
//
// $Change: 2317643 $  $DateTime: 2015/07/10 11:14:28 $
// *****************************************************************************

#ifndef MULTICHANNEL_OUTPUT_HEADER_INCLUDED
#define MULTICHANNEL_OUTPUT_HEADER_INCLUDED

#include "cbuffer.h"
#include "..\common\ports.h"


.CONST $MULTI_CHAN_MAX_WIRED_OUT_CHANNELS               7;    // Maximum number of wired channels (only 6 concurrently!)

// There is a maximum of 4 audio channels output channels via I2S and 2 audio channel via DAC
.CONST $MULTI_CHAN_CHAIN0_MAX_WIRED_CHANNELS            6;    // Maximum CHAIN0 (individual) channels to handle in cbops copy struc
.CONST $MULTI_CHAN_CHAIN1_MAX_WIRED_CHANNELS            2;    // Maximum CHAIN1 (individual) channels to handle in cbops copy struc

// Multi-channel port definitions
.CONST $MULTI_CHAN_SUB_WIRED_OUT_PORT                   ($cbuffer.WRITE_PORT_MASK + $SUB_WIRED_OUT_PORT_NUMBER);
.CONST $MULTI_CHAN_PRIMARY_LEFT_OUT_PORT                ($cbuffer.WRITE_PORT_MASK + $PRIMARY_LEFT_OUT_PORT_NUMBER);
.CONST $MULTI_CHAN_PRIMARY_RIGHT_OUT_PORT               ($cbuffer.WRITE_PORT_MASK + $PRIMARY_RIGHT_OUT_PORT_NUMBER);
.CONST $MULTI_CHAN_SECONDARY_LEFT_OUT_PORT              ($cbuffer.WRITE_PORT_MASK + $SECONDARY_LEFT_OUT_PORT_NUMBER);
.CONST $MULTI_CHAN_SECONDARY_RIGHT_OUT_PORT             ($cbuffer.WRITE_PORT_MASK + $SECONDARY_RIGHT_OUT_PORT_NUMBER);
.CONST $MULTI_CHAN_AUX_LEFT_OUT_PORT                    ($cbuffer.WRITE_PORT_MASK + $AUX_LEFT_OUT_PORT_NUMBER);
.CONST $MULTI_CHAN_AUX_RIGHT_OUT_PORT                   ($cbuffer.WRITE_PORT_MASK + $AUX_RIGHT_OUT_PORT_NUMBER);

// Cbops channel indices
.CONST $MULTI_CHAN_CHAIN0_CHAN0                         0;
.CONST $MULTI_CHAN_CHAIN0_CHAN1                         1;
.CONST $MULTI_CHAN_CHAIN0_CHAN2                         2;
.CONST $MULTI_CHAN_CHAIN0_CHAN3                         3;
.CONST $MULTI_CHAN_CHAIN0_CHAN4                         4;
.CONST $MULTI_CHAN_CHAIN0_CHAN5                         5;

.CONST $MULTI_CHAN_CHAIN1_CHAN0                         0;
.CONST $MULTI_CHAN_CHAIN1_CHAN1                         1;

// Bit field flags used to switch cbops operators (bit0: cbops channel 0, bit1: cbops channel 1 etc)
.CONST $MULTI_CHAN_CHAIN0_CHAN0_EN                      (1 << $MULTI_CHAN_CHAIN0_CHAN0);
.CONST $MULTI_CHAN_CHAIN0_CHAN1_EN                      (1 << $MULTI_CHAN_CHAIN0_CHAN1);
.CONST $MULTI_CHAN_CHAIN0_CHAN2_EN                      (1 << $MULTI_CHAN_CHAIN0_CHAN2);
.CONST $MULTI_CHAN_CHAIN0_CHAN3_EN                      (1 << $MULTI_CHAN_CHAIN0_CHAN3);
.CONST $MULTI_CHAN_CHAIN0_CHAN4_EN                      (1 << $MULTI_CHAN_CHAIN0_CHAN4);
.CONST $MULTI_CHAN_CHAIN0_CHAN5_EN                      (1 << $MULTI_CHAN_CHAIN0_CHAN5);

.CONST $MULTI_CHAN_CHAIN1_CHAN0_EN                      (1 << $MULTI_CHAN_CHAIN1_CHAN0);
.CONST $MULTI_CHAN_CHAIN1_CHAN1_EN                      (1 << $MULTI_CHAN_CHAIN1_CHAN1);

// Table indices for wired output channels
.CONST $MULTI_CHAN_PRIMARY_LEFT_OUT_CHAN                0;
.CONST $MULTI_CHAN_PRIMARY_RIGHT_OUT_CHAN               1;
.CONST $MULTI_CHAN_AUX_LEFT_OUT_CHAN                    2;
.CONST $MULTI_CHAN_AUX_RIGHT_OUT_CHAN                   3;
.CONST $MULTI_CHAN_SECONDARY_LEFT_OUT_CHAN              4;
.CONST $MULTI_CHAN_SECONDARY_RIGHT_OUT_CHAN             5;
.CONST $MULTI_CHAN_SUB_WIRED_OUT_CHAN                   6;

// Mask to select the channel table bitfields
.CONST $MULTI_CHAN_PRIMARY_CHANNELS_LEFT_MASK           (1 << $MULTI_CHAN_PRIMARY_LEFT_OUT_CHAN);
.CONST $MULTI_CHAN_PRIMARY_CHANNELS_RIGHT_MASK          (1 << $MULTI_CHAN_PRIMARY_RIGHT_OUT_CHAN);
.CONST $MULTI_CHAN_AUX_CHANNELS_LEFT_MASK               (1 << $MULTI_CHAN_AUX_LEFT_OUT_CHAN);
.CONST $MULTI_CHAN_AUX_CHANNELS_RIGHT_MASK              (1 << $MULTI_CHAN_AUX_RIGHT_OUT_CHAN);
.CONST $MULTI_CHAN_SECONDARY_CHANNELS_LEFT_MASK         (1 << $MULTI_CHAN_SECONDARY_LEFT_OUT_CHAN);
.CONST $MULTI_CHAN_SECONDARY_CHANNELS_RIGHT_MASK        (1 << $MULTI_CHAN_SECONDARY_RIGHT_OUT_CHAN);
.CONST $MULTI_CHAN_SUB_WIRED_CHANNELS_MASK              (1 << $MULTI_CHAN_SUB_WIRED_OUT_CHAN);

.CONST $MULTI_CHAN_PRIMARY_CHANNELS_MASK                ($MULTI_CHAN_PRIMARY_CHANNELS_LEFT_MASK | $MULTI_CHAN_PRIMARY_CHANNELS_RIGHT_MASK);
.CONST $MULTI_CHAN_SECONDARY_CHANNELS_MASK              ($MULTI_CHAN_SECONDARY_CHANNELS_LEFT_MASK | $MULTI_CHAN_SECONDARY_CHANNELS_RIGHT_MASK);
.CONST $MULTI_CHAN_AUX_CHANNELS_MASK                    ($MULTI_CHAN_AUX_CHANNELS_LEFT_MASK | $MULTI_CHAN_AUX_CHANNELS_RIGHT_MASK);

.CONST $MULTI_CHAN_MAIN_CHANNELS_MASK                   ($MULTI_CHAN_PRIMARY_CHANNELS_MASK | $MULTI_CHAN_SECONDARY_CHANNELS_MASK | $MULTI_CHAN_SUB_WIRED_CHANNELS_MASK);

// Channel allocation structure elements
.CONST $INTERFACE_MAP_ENABLED_CHANNELS_FIELD            0;
.CONST $INTERFACE_MAP_DAC_CHANNELS_FIELD                1;
.CONST $INTERFACE_MAP_CHAIN1_CHANNELS_FIELD             2;
.CONST $INTERFACE_MAP_SPDIF_CHANNELS_FIELD              3;
.CONST $INTERFACE_MAP_SIZE                              4;

#endif
