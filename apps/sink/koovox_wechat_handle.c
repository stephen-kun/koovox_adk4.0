/****************************************************************************
Copyright (C) JoySoft . 2015-2025
Part of KOOVOX 1.0.1

FILE NAME
    koovox_wechat_handle.c

*/


#ifdef ENABLE_KOOVOX

#include "koovox_wechat_handle.h"
#include "koovox_wechat_util.h"
#include "sink_debug.h"
#include "crc32.h"
#include "gatt_manager.h"


Wechatble_state g_wechatble_state = {FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 0, 0, 0};
uint8 challeange[CHALLENAGE_LENGTH] = {0x11,0x22,0x33,0x44}; 


Data_info g_send_data = {NULL, 0, 0};
Data_info g_rcv_data = {NULL, 0, 0};

#define GATT_SERVER theSink.rundata->ble.gatt.server


/*************************************************************************
NAME
    koovox_pack_wechat_head
    
DESCRIPTION
    pack the wechat head packect

RETURN
    void
*/
static void koovox_pack_wechat_head(uint16 cmdid, uint8* data)
{
	data[0] = 0xfe;
	data[1] = 0x01;
	data[2] = (g_send_data.len >> 8) & 0xff;
	data[3] = g_send_data.len & 0xff;
	data[4] = (cmdid >> 8) & 0xff;
	data[5] = cmdid & 0xff;
	data[6] =(g_wechatble_state.seq >> 8) & 0xff;
	data[7] = g_wechatble_state.seq & 0xff;
}

/*************************************************************************
NAME
    koovox_rcv_data_confirm
    
DESCRIPTION
    device confirm the response from the wechat

RETURN
    void
*/
static uint16 koovox_rcv_data_confirm(uint8* data, uint16 size_data)
{
	uint16 result = 0;
	uint16 cmd = 0;
	uint16 fix_head_len = FRAME_SIZE_FIX_HEAD;

	if(size_data < FRAME_SIZE_FIX_HEAD)
		return errorCodeUnpackErrorDecode;

	cmd = ((uint16)data[4] << 8) + (uint16)data[5];

	DEBUG(("========cmdid:%x \n", cmd));
	
	switch(cmd)
	{
	case ECI_none:
	break;
	
	case ECI_resp_auth:
	{
		AuthResponse* authResp;
		authResp = epb_unpack_auth_response(data + fix_head_len, size_data - fix_head_len);
		if(!authResp)
		{
			return errorCodeUnpackAuthResp;
		}
		
		if(authResp->base_response)
		{
			if(authResp->base_response->err_code == 0)
			{
				g_wechatble_state.auth_state = TRUE;

			}
			else
			{
				result = (uint16)authResp->base_response->err_code;
			}
		}
		epb_unpack_auth_response_free(authResp);

	}
	break;
	
	case ECI_resp_sendData:
	{
	
		SendDataResponse *sendDataResp;
		sendDataResp = epb_unpack_send_data_response(data + fix_head_len,size_data - fix_head_len);
		if(!sendDataResp)
		{
			return errorCodeUnpackSendDataResp;
		}
		
		if(sendDataResp->base_response->err_code)
		{
			result = (uint16)sendDataResp->base_response->err_code;
		}
		epb_unpack_send_data_response_free(sendDataResp);
	}
	break;
	
	case ECI_resp_init:
	{
		InitResponse *initResp = epb_unpack_init_response(data + fix_head_len, size_data - fix_head_len);
		if(!initResp)
		{
			return errorCodeUnpackInitResp;
		}
		
		if(initResp->base_response)
		{
			if(initResp->base_response->err_code == 0)
			{
				if(initResp->has_challeange_answer)
				{
					uint32 ret = crc32(0,challeange,CHALLENAGE_LENGTH);
					if(ret == initResp->challeange_answer)
					{
						g_wechatble_state.init_state = TRUE;
					}

					DEBUG(("crc32:%ld ,challeange_answer:%ld\n", ret, initResp->challeange_answer));

				}
				else 
					g_wechatble_state.init_state = TRUE;
				
				g_wechatble_state.wechats_switch_state = TRUE;
			}
			else
			{
				result = (uint16)initResp->base_response->err_code;
			}
		}
		epb_unpack_init_response_free(initResp);
	}
	break;
	
	case ECI_push_recvData:
	{
		RecvDataPush *recvDatPush = epb_unpack_recv_data_push(data + fix_head_len, size_data - fix_head_len);
		uint16 cmdid = recvDatPush->data.data[6] ;

		cmdid += (uint16)recvDatPush->data.data[7] << 8;
		
		if(!recvDatPush)
		{
			return errorCodeUnpackRecvDataPush;
		}

		{
		uint16 i = 0;

		DEBUG(("cmdid = %x\n", cmdid));
		for(; i<recvDatPush->data.len; i++ )
			DEBUG(("%x ", recvDatPush->data.data[i]));

		DEBUG(("\n"));
		}
		
		switch(cmdid)
		{
		/* 填充自己的命令 */

		

		default:
			break;
		}
			
		epb_unpack_recv_data_push_free(recvDatPush);
		g_wechatble_state.push_data_seq++;
	}
	break;
	
	case ECI_push_switchView:
	{		
		SwitchViewPush *swichViewPush = epb_unpack_switch_view_push(data + fix_head_len, size_data - fix_head_len);		
		g_wechatble_state.wechats_switch_state = !g_wechatble_state.wechats_switch_state;

		if(!swichViewPush)
		{
			return errorCodeUnpackSwitchViewPush;
		}
		epb_unpack_switch_view_push_free(swichViewPush);
	}
	break;
	
	case ECI_push_switchBackgroud:
	{
		SwitchBackgroudPush *switchBackgroundPush = epb_unpack_switch_backgroud_push(data + fix_head_len, size_data - fix_head_len);

		if(! switchBackgroundPush)
		{
			return errorCodeUnpackSwitchBackgroundPush;
		}	
		
		epb_unpack_switch_backgroud_push_free(switchBackgroundPush);
	}
	break;
	
	case ECI_err_decode:
		break;
	default:
		break;
	}

	return result;
	
}


/*************************************************************************
NAME
    koovox_wechat_error_handle
    
DESCRIPTION
    device handle the error conditional

RETURN
    void
*/
void koovox_wechat_error_handle(uint16 error_code)
{
	DEBUG(("koovox_wechat_error_handle: ERROR_CODE=%x \n", error_code));

	if(error_code)
	{

	}
}



/*************************************************************************
NAME
    koovox_write_from_wechat
    
DESCRIPTION
    device handle write charatiristic from wechat

RETURN
    void
*/
void koovox_write_from_wechat(uint8* data, uint16 size_data)
{
	uint16 chunk_size = 0;
	uint16 error_code = 0;
    
#ifdef DEBUG_PRINT_ENABLED
	{
		uint8 i = 0;
		for(; i<size_data; i++)
			DEBUG(("%x ", data[i]));

		DEBUG(("\n"));
	}
#endif    

	if(size_data < FRAME_SIZE_FIX_HEAD)
		return;

#if 0
	if(size_data <= SIZE_GATT_MTU)
#endif
	{
		if((g_rcv_data.len == 0))
		{
			uint16 lenght = ((uint16)data[2] << 8) + (uint16)data[3] ;

			/* 包头检测 */
			if((data[0] != 0xfe)&&(data[1] != 0x01))
				return;
			
			g_rcv_data.len = lenght;
			g_rcv_data.offset = 0;
			g_rcv_data.data = (uint8*)mallocPanic(g_rcv_data.len);
		}

		chunk_size = g_rcv_data.len - g_rcv_data.offset;
		chunk_size = chunk_size < size_data ? chunk_size : size_data;
		memcpy(g_rcv_data.data + g_rcv_data.offset, data, chunk_size);
		g_rcv_data.offset += chunk_size;
		
		if (g_rcv_data.len <= g_rcv_data.offset) 
		{
			/* 应答消息验证 */
			error_code = koovox_rcv_data_confirm(g_rcv_data.data, g_rcv_data.len);
			
			/* 出错处理 */
			koovox_wechat_error_handle(error_code);

			if(g_rcv_data.data)
			{
				DEBUG(("free g_rcv_data.data\n"));
				freePanic(g_rcv_data.data);
				g_rcv_data.data = NULL;
			}

			g_rcv_data.len = 0;
			g_rcv_data.offset = 0;
			
		}	
	}
}

/****************************************************************************
NAME
    koovox_handle_wechat_indicate
    
DESCRIPTION
    handle the wechat indicate event

RETURN
	void
*/
void koovox_handle_wechat_indicate(uint16 cid, uint16 handle)
{
	DEBUG(("koovox_handle_wechat_indicate\n"));
	
	g_wechatble_state.indication_state = TRUE;

	if((g_wechatble_state.indication_state) 
		&& (!g_wechatble_state.auth_state) 
		&& (!g_wechatble_state.auth_send) )
	{
	
		koovox_pack_wechat_auth_req();
		koovox_indicate_to_wechat(cid, handle);
		g_wechatble_state.auth_send = TRUE;
	}
}



/*************************************************************************
NAME
    koovox_indicate_to_wechat
    
DESCRIPTION
    device indicate data to wechat

RETURN
    void
*/
void koovox_indicate_to_wechat(uint16 cid, uint16 handle)
{
	if(g_send_data.len > g_send_data.offset)
	{
		uint16 len_send = 0;
		if(g_send_data.len - g_send_data.offset > SIZE_GATT_MTU)
			len_send = SIZE_GATT_MTU;
		else
			len_send = g_send_data.len - g_send_data.offset;

		GATT_SERVER.wechat_server->indications_enabled = TRUE;
		
		/* If indications were enabled, send one */
		GattWechatServerSendIndication(GATT_SERVER.wechat_server, cid, handle, len_send, g_send_data.data + g_send_data.offset);
		
		g_send_data.offset += len_send;

		DEBUG(("server_handle_gatt_indication_cfm:offset %d\n", g_send_data.offset));
	}
	else if(g_send_data.len == g_send_data.offset)
	{
		DEBUG(("****finish send data*****\n"));
		g_send_data.len = 0;
		g_send_data.offset= 0;
		freePanic(g_send_data.data);
		g_send_data.data = NULL;

		GATT_SERVER.wechat_server->indications_enabled = FALSE;
	}
}


/*************************************************************************
NAME
    koovox_pack_wechat_auth_req
    
DESCRIPTION
    pack wechat auth request package

RETURN
    void
*/
void koovox_pack_wechat_auth_req(void)
{
	AuthRequest authReq = {0};
	uint8 bd_addr[6] = {0};
	uint16 fix_head_len = FRAME_SIZE_FIX_HEAD;
	
	memset(&authReq, 0, sizeof(authReq));
	KoovoxGetBluetoothAdrress((uint8 *)bd_addr);
	
	authReq.proto_version = PROTO_VERSION;
	authReq.auth_proto = AUTH_PROTO;
	authReq.auth_method = EAM_macNoEncrypt;
	authReq.has_mac_address = TRUE;
	authReq.mac_address.len = 0x06;
	authReq.mac_address.data = (uint8*)bd_addr;
					
	g_send_data.len = epb_auth_request_pack_size(&authReq) + fix_head_len;
	g_send_data.data = (uint8*)mallocPanic(g_send_data.len);
	
	g_wechatble_state.seq++;
	
	koovox_pack_wechat_head(ECI_req_auth, g_send_data.data);

	
	epb_pack_auth_request(&authReq, g_send_data.data + fix_head_len, g_send_data.len - fix_head_len);

	g_send_data.offset = 0;
					
}


/*************************************************************************
NAME
    koovox_pack_wechat_init_req
    
DESCRIPTION
    pack wechat init request package

RETURN
    void
*/
void koovox_pack_wechat_init_req(void)
{	
	InitRequest initReq = {0};
	uint16 fix_head_len = FRAME_SIZE_FIX_HEAD;

	/* 需要根据实际情况修改 */
#if 0
	uint8 resp_field[] = {0x7f, 0x0, 0x0, 0x0};
	uint8 challenge[] = {0x2c, 0x93, 0x4b, 0x0};
#endif
	
	memset(&initReq, 0, sizeof(initReq));
	g_wechatble_state.seq++;
	
	initReq.has_resp_field_filter = FALSE;
	initReq.resp_field_filter.len = 0;
	initReq.resp_field_filter.data = NULL;
	initReq.has_challenge = FALSE;
	initReq.challenge.len = 0;
	initReq.challenge.data = NULL;
	
	g_send_data.len = epb_init_request_pack_size(&initReq)+ fix_head_len;
	g_send_data.data = (uint8*)mallocPanic(g_send_data.len);

	koovox_pack_wechat_head(ECI_req_init, g_send_data.data);
	
	epb_pack_init_request(&initReq, g_send_data.data + fix_head_len, g_send_data.len - fix_head_len);
	
	g_send_data.offset = 0;
	
}

/*************************************************************************
NAME
    koovox_device_wechat_send_data
    
DESCRIPTION
    pack wechat send data request package

RETURN
    void
*/
void koovox_pack_wechat_send_data_req(uint8* data, uint16 size_data, bool has_type, EmDeviceDataType type)
{
	SendDataRequest data_request = {0};
	uint16 fix_head_len = FRAME_SIZE_FIX_HEAD;
	
	memset(&data_request, 0, sizeof(data_request));
	g_wechatble_state.seq++;
	g_wechatble_state.send_data_seq++;
	
	data_request.data.data = data;
	data_request.data.len = size_data;
	
	data_request.has_type = has_type;
	data_request.type = type;
	
	g_send_data.len = epb_send_data_request_pack_size(&data_request)+ fix_head_len;
	g_send_data.data = (uint8*)mallocPanic(g_send_data.len);

	koovox_pack_wechat_head(ECI_req_sendData, g_send_data.data);

	epb_pack_send_data_request(&data_request, g_send_data.data + fix_head_len, g_send_data.len - fix_head_len);
	
	g_send_data.offset = 0;
	
}

/*************************************************************************
NAME
    koovox_device_wechat_disconnect
    
DESCRIPTION
    device disconnect to wechat

RETURN
    void
*/
void koovox_device_wechat_disconnect(void)
{
	g_wechatble_state.wechats_switch_state 	= FALSE;
	g_wechatble_state.auth_state			= FALSE;
	g_wechatble_state.init_state			= FALSE;
	g_wechatble_state.auth_send				= FALSE;
	g_wechatble_state.init_send				= FALSE;
	g_wechatble_state.indication_state		= FALSE;
	g_wechatble_state.seq					= 0;
	g_wechatble_state.send_data_seq			= 0;
	g_wechatble_state.push_data_seq			= 0;

}

/****************************************************************************
NAME 
  	KoovoxGetBluetoothAdrress

DESCRIPTION
 	get the bluetooth address
 
RETURNS
  	void
*/ 
void KoovoxGetBluetoothAdrress(uint8* addr)
{
	uint8 i = 0;
	BD_ADDR_T bd_addr;
	BdaddrConvertVmToBluestack(&bd_addr, (const bdaddr *)(&theSink.local_bd_addr));
	
	addr[i++] = (bd_addr.nap >> 8) & 0xff;
	addr[i++] = bd_addr.nap & 0xff;
	addr[i++] = bd_addr.uap;
	addr[i++] = (bd_addr.lap >> 16) & 0xff;
	addr[i++] = (bd_addr.lap >> 8) & 0xff;
	addr[i++] = bd_addr.lap & 0xff;
}



#else  /* ENABLE_KOOVOX */

#include <csrtypes.h>
static const uint16 dummy_gatt = 0;    

#endif

