// *****************************************************************************
// Copyright Cambridge Silicon Radio Limited 2007 - 2015.        http://www.csr.com
// Part of ADK 4.0
//
// $Change: 2317643 $  $DateTime: 2015/07/10 11:14:28 $
// *****************************************************************************


#ifndef two_mic_example_LIB_H
#define two_mic_example_LIB_H


.CONST $two_mic_example.REINITIALIZE           1;
.CONST $two_mic_example.VMMSG.SETMODE          4;
.CONST $two_mic_example.VMMSG.READY            5;
.CONST $two_mic_example.MESSAGE_REM_BT_ADDRESS 0x2001;

// System Modes
.CONST $two_mic_example.SYSMODE.PASSTHRU       0;

// Data block size
#ifdef uses_16kHz
.CONST $two_mic_example.NUM_SAMPLES_PER_FRAME  120;
.CONST $two_mic_example.JITTER                 16;
#else
.CONST $two_mic_example.NUM_SAMPLES_PER_FRAME  60;
.CONST $two_mic_example.JITTER                 8;
#endif


#endif
