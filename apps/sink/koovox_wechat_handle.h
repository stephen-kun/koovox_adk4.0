/****************************************************************************
Copyright (C) JoySoft . 2015-2025
Part of KOOVOX 1.0.1

FILE NAME
    koovox_wechat_handle.h

*/

#ifdef ENABLE_KOOVOX


#ifndef __KOOVOX_WECHAT_HANDLE_H
#define __KOOVOX_WECHAT_HANDLE_H

#include <message.h>
#include <gatt.h>

#include "sink_private.h"
#include "epb_MmBp.h"


#define GATT_DEFAULT_MTU		(23)
#define PROTO_VERSION 			0x010004
#define AUTH_PROTO 				1
#define SIZE_GATT_MTU			(GATT_DEFAULT_MTU - 3)
#define FRAME_SIZE_FIX_HEAD		8
#define CHALLENAGE_LENGTH		4



#define	errorCodeUnpackAuthResp   			0x9990
#define	errorCodeUnpackInitResp  	 		0x9991
#define	errorCodeUnpackSendDataResp			0x9992
#define	errorCodeUnpackCtlCmdResp			0x9993
#define	errorCodeUnpackRecvDataPush 		0x9994
#define	errorCodeUnpackSwitchViewPush 		0x9995
#define	errorCodeUnpackSwitchBackgroundPush 0x9996
#define	errorCodeUnpackErrorDecode 			0x9997

typedef enum
{
	sendTextReq = 0x01,
	sendTextResp = 0x1001,
	openLightPush = 0x2001,
	closeLightPush = 0x2002
}WeChatCmdID;

typedef struct 
{
	bool 	wechats_switch_state; /* 公众账号切换到前台的状态 */
	bool 	indication_state;
	bool 	auth_state;
	bool 	init_state;
	bool 	auth_send;
	bool 	init_send;
	uint16 	send_data_seq;
	uint16 	push_data_seq;
	uint16 	seq; 
}Wechatble_state;

typedef struct
{
	uint8 *data;
	uint16 len;
	uint16 offset;
}Data_info;

/* 可自定义 */
typedef struct
{
	uint8 	m_magicCode[2];
	uint16 	m_version;
	uint16 	m_totalLength;
	uint16 	m_cmdid;
	uint16 	m_seq;
	uint16 	m_errorCode;
}WeChatBleHead;

typedef struct{
	uint8 	bMagicNumber;
	uint8 	bVer;
	uint16 	nLength;
	uint16 	nCmdId;
	uint16 	nSeq;
}BpFixHead;


void koovox_indicate_to_wechat(uint16 cid, uint16 handle);
void koovox_write_from_wechat(uint8* data, uint16 size_data);
void koovox_pack_wechat_auth_req(void);
void koovox_pack_wechat_init_req(void);
void koovox_pack_wechat_send_data_req(uint8* data, uint16 size_data, bool has_type, EmDeviceDataType type);
void koovox_wechat_error_handle(uint16 error_code);
void koovox_device_wechat_disconnect(void);
void koovox_handle_wechat_indicate(uint16 cid, uint16 handle);

void KoovoxGetBluetoothAdrress(uint8* addr);


extern Wechatble_state g_wechatble_state;
extern Data_info g_send_data;
extern Data_info g_rcv_data;

#endif /* __KOOVOX_WECHAT_HANDLE_H */


#endif

