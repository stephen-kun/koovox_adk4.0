/****************************************************************************
Copyright (C) Cambridge Silicon Radio Ltd. 2004 - 2015.
Part of ADK 4.0

FILE NAME
    codec_init_handler.h
    
DESCRIPTION
*/

#ifndef CODEC_INIT_HANDLER_H_
#define CODEC_INIT_HANDLER_H_


/****************************************************************************
NAME	
	sendInitCfmToApp

DESCRIPTION
	Send an initialisation confirmation message back to the client application.
*/
void sendInitCfmToApp(Task codecTask, 
					  Task clientTask, 
					  codec_status_code status, 
					  uint16 inputGainRange, 
					  uint16 outputGainRange);
	

#endif /* CODEC_INIT_HANDLER_H */
