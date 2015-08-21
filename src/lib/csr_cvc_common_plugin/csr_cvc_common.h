/****************************************************************************
Copyright (C) Cambridge Silicon Radio Ltd. 2005

FILE NAME
    csr_cvc_common.h

DESCRIPTION
    
    
NOTES
   
*/

#ifndef _CSR_CVC_COMMON_H_
#define _CSR_CVC_COMMON_H_

/*plugin functions*/
void CsrCvcPluginConnect( CvcPluginTaskdata *task, 
                          AUDIO_PLUGIN_CONNECT_MSG_T* connect_msg,
                          Source audio_source);
void CsrCvcPluginDisconnect(CvcPluginTaskdata *task) ;
void CsrCvcPluginSetVolume(uint16 volume ) ;
void CsrCvcPluginResetVolume( void );
void CsrCvcPluginSetMode ( CvcPluginTaskdata *task, AUDIO_MODE_T mode , const void * params ) ;
void CsrCvcPluginSetModeNoDsp ( AUDIO_MODE_T mode ) ;
void CsrCvcPluginSetSoftMute (AUDIO_PLUGIN_SET_SOFT_MUTE_MSG_T* message);
void CsrCvcPluginSetSoftMuteNoDsp (AUDIO_PLUGIN_SET_SOFT_MUTE_MSG_T* message);
void CsrCvcPluginPlayTone (CvcPluginTaskdata *task, ringtone_note * tone , uint16 tone_volume) ;
void CsrCvcPluginStopTone ( CvcPluginTaskdata *task ) ;


#ifdef CVC_ALL
void CsrCvcPluginMicSwitch(void);
#else
#define CsrCvcPluginMicSwitch() (NULL)
#endif

#ifdef CVC_ALL
void CsrCvcPluginOutputSwitch(void);
#else
#define CsrCvcPluginOutputSwitch() (NULL)
#endif

void CsrCvcPluginToneForceCompleteNoDsp( CvcPluginTaskdata *task );
void CsrCvcPluginSetPower( CvcPluginTaskdata *task,  AUDIO_POWER_T power );
void CvcConfigureASR( CvcPluginTaskdata *task);
void CsrCvcPluginSetAsr ( CvcPluginTaskdata *task, AUDIO_MODE_T mode  );

/*internal plugin message functions*/
void CsrCvcPluginInternalMessage( CvcPluginTaskdata *task ,uint16 id , Message message ) ;

void CsrCvcPluginToneComplete ( CvcPluginTaskdata *task ) ;

/* The power level that the plugin will switch to low power mode */
#define LPIBM_THRESHOLD		POWER_BATT_LEVEL0

/* Rate match enable masks */
#define RATE_MATCH_DISABLE_MASK                0x0000
#define RATE_MATCH_HARDWARE_MASK               0x0001
#define RATE_MATCH_SOFTWARE_MASK               0x0002

#endif

