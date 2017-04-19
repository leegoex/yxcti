#include "kfpc_logex.h"
#include "KFPC_LicenseSerAPIHandler.h"
#include "kfpc_licenseser_api.h"
#include "kfpc_api.h"
#include "KFPC_StringUtils.h"

KFPC_LicenseSerAPIHandler::KFPC_LicenseSerAPIHandler(void)
{
	for(unsigned int i=0;i<AES_BLOCK_SIZE;i++)
	{
		m_Key[i] = ~KFPC_AES_KEY[i];
	}

	memset(m_MsgProcFunMap, 0, sizeof(m_MsgProcFunMap));

	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_LIC_TSERVERLIC)]	=	&KFPC_LicenseSerAPIHandler::RecvLIC_TServerLIC;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_LIC_CCSLIC)]	=	&KFPC_LicenseSerAPIHandler::RecvLIC_CCSLIC;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_LIC_FAXLIC)]	=	&KFPC_LicenseSerAPIHandler::RecvLIC_FAXLIC;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_LIC_BASELIC)]	=	&KFPC_LicenseSerAPIHandler::RecvLIC_BASELIC;
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_LIC_IPRECLIC)]	=	&KFPC_LicenseSerAPIHandler::RecvLIC_IPRLIC;
}


KFPC_LicenseSerAPIHandler::~KFPC_LicenseSerAPIHandler(void)
{
}

void KFPC_LicenseSerAPIHandler::RecvMsg(KFPC_MSG_HEADER* pMsg)
{
	unsigned int MsgGroupID = KFPC_MSG_ID_GET_GROUP(pMsg->un32MsgId);

	if(MsgGroupID ==  KFPC_ID_CLASS_COM_LIC &&
		KFPC_MSG_ID_LIC_END > pMsg->un32MsgId )
	{
		MessageProc pFun = m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(pMsg->un32MsgId)];

		if(pFun != NULL)
		{
			(this->*(pFun))(pMsg);
		}
	}
}

int KFPC_LicenseSerAPIHandler::SendMsg( KFPC_MSG_HEADER* pMsg )
{
	return KFPC_SendMsg(pMsg);
}

unsigned int KFPC_LicenseSerAPIHandler::SendREQ_LIC_TSERVERLIC(unsigned int UserContext1,unsigned int UserContext2,unsigned int DestAppID,unsigned int AppType,const char* pSwtich)
{
	KFPC_LIC_REQ_TSERVERLIC* pMsg = NULL;

	KFPC_AllocMsg(sizeof(KFPC_LIC_REQ_TSERVERLIC),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_LIC_TSERVERLIC,
		KFPC_MSG_TYPE_REQUEST,
		DestAppID,
		KFPC_GetLibParam()->AppInfo.AppID,
		UserContext1,UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg\n");
		return -1;
	}
	
	pMsg->AppType = AppType ; 
	strncpy(pMsg->SwichID,pSwtich,MAX_SWITCH_ID);

	INFO_LOG(0,"DestAppID:%u(0x%x),SwitchID:%s,UserContext1:%u,UserContext2:%u",DestAppID,DestAppID,pSwtich,UserContext1,UserContext2);

	unsigned int Ret = SendMsg((KFPC_MSG_HEADER *)pMsg);
	if(Ret != 0)
	{
		ERROR_LOG(0,"Failed to send LICENSE Req message.\n");
	}

	return Ret;
}

unsigned int KFPC_LicenseSerAPIHandler::SendRSP_LIC_TSERVERLIC( unsigned int UserContext1,unsigned int UserContext2,unsigned int DestAppID ,KFPC_TSERVERLIC_INFO &TServerLic,unsigned int Result)
{
	KFPC_LIC_RSP_TSERVERLIC* pMsg = NULL;

	KFPC_AllocMsg(sizeof(KFPC_LIC_RSP_TSERVERLIC),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_LIC_TSERVERLIC,
		KFPC_MSG_TYPE_RESPONSE,
		DestAppID,
		KFPC_GetLibParam()->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg\n");
		return -1;
	}
	DEBUG_LOG(0,"SwitchID:%s",TServerLic.SwichID);
	memmove(&pMsg->TServerLic,&TServerLic,sizeof(KFPC_TSERVERLIC_INFO));
	pMsg->Result = Result;
	Encrypt(&pMsg->TServerLic, sizeof(KFPC_TSERVERLIC_INFO));

	unsigned int Ret = SendMsg((KFPC_MSG_HEADER *)pMsg);
	if(Ret != 0)
	{
		ERROR_LOG(0,"Failed to send LICENSE response message.\n");
	}

	return Ret;
}

unsigned int KFPC_LicenseSerAPIHandler::SendREQ_LIC_CCSLIC(unsigned int UserContext1,unsigned int UserContext2,unsigned int DestAppID,unsigned int AppType)
{
	KFPC_LIC_REQ_CCSLIC* pMsg = NULL;

	KFPC_AllocMsg(sizeof(KFPC_LIC_REQ_CCSLIC),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_LIC_CCSLIC,
		KFPC_MSG_TYPE_REQUEST,
		DestAppID,
		KFPC_GetLibParam()->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg\n");
		return -1;
	}

	pMsg->AppType = AppType;
	
	INFO_LOG(0,
		"Header.un32SrcAPPId:0x%x,"
		"Header.un32DstAPPId:0x%x,"
		"Header.un32UserContext1:%u,"
		"Header.un32UserContext2:%u"
		,
		pMsg->MsgHead.un32SrcAPPId,
		pMsg->MsgHead.un32DstAPPId,
		pMsg->MsgHead.un32UserContext1,
		pMsg->MsgHead.un32UserContext2
		);	

	unsigned int Ret = SendMsg((KFPC_MSG_HEADER *)pMsg);
	if(Ret != 0)
	{
		ERROR_LOG(0,"Failed to send LICENSE Req message.\n");
	}

	return Ret;
}

unsigned int KFPC_LicenseSerAPIHandler::SendRSP_LIC_CCSLIC( unsigned int UserContext1,unsigned int UserContext2,unsigned int DestAppID,KFPC_CCSLIC_INFO &CCSLic,unsigned int Result)
{
	KFPC_LIC_RSP_CCSLIC* pMsg = NULL;

	KFPC_AllocMsg(sizeof(KFPC_LIC_RSP_CCSLIC),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_LIC_CCSLIC,
		KFPC_MSG_TYPE_RESPONSE,
		DestAppID,
		KFPC_GetLibParam()->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg\n");
		return -1;
	}
	
	memmove(&pMsg->CCSLic,&CCSLic,sizeof(KFPC_CCSLIC_INFO));
	pMsg->Result = Result;

	Encrypt(&pMsg->CCSLic, sizeof(KFPC_CCSLIC_INFO));

	unsigned int Ret = SendMsg((KFPC_MSG_HEADER *)pMsg);
	if(Ret != 0)
	{
		ERROR_LOG(0,"Failed to send LICENSE response message.\n");
	}

	return Ret;
}

unsigned int KFPC_LicenseSerAPIHandler::SendREQ_LIC_FAXLIC(unsigned int UserContext1,unsigned int UserContext2,unsigned int DestAppID,unsigned int AppType)
{
	KFPC_LIC_REQ_FAXLIC* pMsg = NULL;

	KFPC_AllocMsg(sizeof(KFPC_LIC_REQ_FAXLIC),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_LIC_FAXLIC,
		KFPC_MSG_TYPE_REQUEST,
		DestAppID,
		KFPC_GetLibParam()->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg\n");
		return -1;
	}
	pMsg->AppType = AppType;

	unsigned int Ret = SendMsg((KFPC_MSG_HEADER *)pMsg);
	if(Ret != 0)
	{
		ERROR_LOG(0,"Failed to send LICENSE Req message.\n");
	}
	return Ret;
}

unsigned int KFPC_LicenseSerAPIHandler::SendRSP_LIC_FAXLIC( unsigned int UserContext1,unsigned int UserContext2,unsigned int DestAppID,KFPC_FAXLIC_INFO &FAXLic,unsigned int Result)
{
	KFPC_LIC_RSP_FAXLIC* pMsg = NULL;

	KFPC_AllocMsg(sizeof(KFPC_LIC_RSP_FAXLIC),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_LIC_FAXLIC,
		KFPC_MSG_TYPE_RESPONSE,
		DestAppID,
		KFPC_GetLibParam()->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg\n");
		return -1;
	}

	memmove(&pMsg->FaxLic,&FAXLic,sizeof(KFPC_FAXLIC_INFO));
	pMsg->Result = Result;

	Encrypt(&pMsg->FaxLic, sizeof(KFPC_FAXLIC_INFO));

	unsigned int Ret = SendMsg((KFPC_MSG_HEADER *)pMsg);
	if(Ret != 0)
	{
		ERROR_LOG(0,"Failed to send LICENSE response message.\n");
	}

	return Ret;
}

unsigned int KFPC_LicenseSerAPIHandler::SendREQ_LIC_BASELIC(unsigned int UserContext1,unsigned int UserContext2,unsigned int DestAppID,unsigned int AppType)
{
	KFPC_LIC_REQ_FAXLIC* pMsg = NULL;

	KFPC_AllocMsg(sizeof(KFPC_LIC_REQ_BASELIC),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_LIC_BASELIC,
		KFPC_MSG_TYPE_REQUEST,
		DestAppID,
		KFPC_GetLibParam()->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg\n");
		return -1;
	}

	pMsg->AppType = AppType;
	INFO_LOG(0,"DestAppID:%u(0x%x),AppType:%u,UserContext1:%u,UserContext2:%u",DestAppID,DestAppID,AppType,UserContext1,UserContext2);

	unsigned int Ret = SendMsg((KFPC_MSG_HEADER *)pMsg);
	if(Ret != 0)
	{
		ERROR_LOG(0,"Failed to send LICENSE Req message.\n");
	}
	return Ret;
}

unsigned int KFPC_LicenseSerAPIHandler::SendRSP_LIC_BASELIC( unsigned int UserContext1,unsigned int UserContext2,unsigned int DestAppID,KFPC_BASELIC_INFO &BaseLic,unsigned int Result)
{
	KFPC_LIC_RSP_BASELIC* pMsg = NULL;

	KFPC_AllocMsg(sizeof(KFPC_LIC_RSP_BASELIC),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_LIC_BASELIC,
		KFPC_MSG_TYPE_RESPONSE,
		DestAppID,
		KFPC_GetLibParam()->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg\n");
		return -1;
	}

	memmove(&pMsg->BaseLic,&BaseLic,sizeof(KFPC_BASELIC_INFO));
	pMsg->Result = Result;

	Encrypt(&pMsg->BaseLic, sizeof(KFPC_BASELIC_INFO));

	unsigned int Ret = SendMsg((KFPC_MSG_HEADER *)pMsg);
	if(Ret != 0)
	{
		ERROR_LOG(0,"Failed to send LICENSE response message.\n");
	}

	return Ret;
}

void KFPC_LicenseSerAPIHandler::RecvLIC_TServerLIC( KFPC_MSG_HEADER* pMsg )
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_LIC_REQ_TSERVERLIC*	pREQMsg = (KFPC_LIC_REQ_TSERVERLIC*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"SwichID:%s",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pREQMsg->SwichID
			);	
	
		OnREQ_LIC_TSERVERLIC(pREQMsg);

	}
	else if (KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_LIC_RSP_TSERVERLIC*	pRSPMsg = (KFPC_LIC_RSP_TSERVERLIC*)pMsg;

		Decrypt(&pRSPMsg->TServerLic,sizeof(KFPC_TSERVERLIC_INFO));

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"SwichID:%s"
			,
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->TServerLic.SwichID);	

		OnRSP_LIC_TSERVERLIC(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}

void KFPC_LicenseSerAPIHandler::RecvLIC_CCSLIC( KFPC_MSG_HEADER* pMsg )
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_LIC_REQ_CCSLIC*	pREQMsg = (KFPC_LIC_REQ_CCSLIC*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);	

		OnREQ_LIC_CCSLIC(pREQMsg);

	}
	else if (KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_LIC_RSP_CCSLIC*	pRSPMsg = (KFPC_LIC_RSP_CCSLIC*)pMsg;
		Decrypt(&pRSPMsg->CCSLic,sizeof(KFPC_CCSLIC_INFO));

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);	

		OnRSP_LIC_CCSLIC(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}

void KFPC_LicenseSerAPIHandler::RecvLIC_FAXLIC( KFPC_MSG_HEADER* pMsg )
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_LIC_REQ_FAXLIC*	pREQMsg = (KFPC_LIC_REQ_FAXLIC*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);	

		OnREQ_LIC_FAXLIC(pREQMsg);

	}
	else if (KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_LIC_RSP_FAXLIC*	pRSPMsg = (KFPC_LIC_RSP_FAXLIC*)pMsg;
		Decrypt(&pRSPMsg->FaxLic,sizeof(KFPC_FAXLIC_INFO));

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);	

		OnRSP_LIC_FAXLIC(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}

void KFPC_LicenseSerAPIHandler::RecvLIC_BASELIC( KFPC_MSG_HEADER* pMsg )
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_LIC_REQ_BASELIC*	pREQMsg = (KFPC_LIC_REQ_BASELIC*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u",
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);	

		OnREQ_LIC_BASELIC(pREQMsg);

	}
	else if (KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_LIC_RSP_BASELIC*	pRSPMsg = (KFPC_LIC_RSP_BASELIC*)pMsg;
		Decrypt(&pRSPMsg->BaseLic,sizeof(KFPC_BASELIC_INFO));

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x,"
			"Header.un32DstAPPId:0x%x,"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"BaseLic.ValidTime:%u"
			,
			Header.un32SrcAPPId,
			Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			pRSPMsg->BaseLic.ValidTime);	

		OnRSP_LIC_BASELIC(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}



void KFPC_LicenseSerAPIHandler::Encrypt( void* Buf, unsigned int BufSize )
{
	unsigned len = 0;

	if ((BufSize + 1) % AES_BLOCK_SIZE == 0) 
	{
		len = BufSize + 1;
	} 
	else 
	{
		len = ((BufSize + 1) / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
	}

	unsigned char* pEncryptData = new unsigned char[len];

	unsigned char iv[AES_BLOCK_SIZE];        // init vector
	memset(iv,0,sizeof(iv));

	AES_KEY aes;

	if (AES_set_encrypt_key(m_Key, 128, &aes) < 0) {
		WARNING_LOG(0,"Unable to set encryption key in AES\n");
		return;
	}

	// encrypt (iv will change)
	AES_cbc_encrypt((unsigned char*)Buf, pEncryptData, len, &aes, iv, AES_ENCRYPT);
	memmove(Buf,pEncryptData,len);
	delete []pEncryptData;
}

void KFPC_LicenseSerAPIHandler::Decrypt( void* Buf, unsigned int BufSize )
{
	unsigned len = 0;

	if ((BufSize + 1) % AES_BLOCK_SIZE == 0) 
	{
		len = BufSize + 1;
	} 
	else 
	{
		len = ((BufSize + 1) / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
	}

	unsigned char* pDecryptData = new unsigned char[len];

	unsigned char iv[AES_BLOCK_SIZE];        // init vector
	memset(iv,0,sizeof(iv));

	AES_KEY aes;

	if (AES_set_decrypt_key(m_Key, 128, &aes) < 0) {
		WARNING_LOG(0,"Unable to set encryption key in AES\n");
		return;
	}

	// encrypt (iv will change)
	AES_cbc_encrypt((unsigned char*)Buf, pDecryptData, len, &aes, iv, AES_DECRYPT);

	memmove(Buf,pDecryptData,len);
	delete []pDecryptData;
}

unsigned int KFPC_LicenseSerAPIHandler::SendREQ_LIC_IPRECLIC(unsigned int UserContext1,unsigned int UserContext2,unsigned int DestAppID,unsigned int AppType)
{
	KFPC_LIC_REQ_IPR* pMsg = NULL;

	KFPC_AllocMsg(sizeof(KFPC_LIC_REQ_IPR),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_LIC_IPRECLIC,
		KFPC_MSG_TYPE_REQUEST,
		DestAppID,
		KFPC_GetLibParam()->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg\n");
		return -1;
	}
	pMsg->AppType = AppType;

	unsigned int Ret = SendMsg((KFPC_MSG_HEADER *)pMsg);
	if(Ret != 0)
	{
		ERROR_LOG(0,"Failed to send LICENSE Req message.\n");
	}
	else
	{
		INFO_LOG(0,"");
	}
	return Ret;
}

unsigned int KFPC_LicenseSerAPIHandler::SendRSP_LIC_IPRECLIC( unsigned int UserContext1,unsigned int UserContext2,unsigned int DestAppID,KFPC_IPR_INFO &IpRecLic,unsigned int Result)
{
	KFPC_LIC_RSP_IPR* pMsg = NULL;

	KFPC_AllocMsg(sizeof(KFPC_LIC_RSP_IPR),
		(KFPC_MSG_HEADER **)&pMsg,
		KFPC_MSG_ID_LIC_IPRECLIC,
		KFPC_MSG_TYPE_RESPONSE,
		DestAppID,
		KFPC_GetLibParam()->AppInfo.AppID,
		UserContext1,
		UserContext2);

	if (pMsg == NULL)
	{
		ERROR_LOG(0,"Failed to call KFPC_AllocMsg\n");
		return -1;
	}

	memmove(&pMsg->IPR_INFO,&IpRecLic,sizeof(KFPC_IPR_INFO));
	pMsg->Result = Result;

	Encrypt(&pMsg->IPR_INFO, sizeof(KFPC_IPR_INFO));
	//Decrypt(&pMsg->IPR_INFO,sizeof(KFPC_IPR_INFO));

	unsigned int Ret = SendMsg((KFPC_MSG_HEADER *)pMsg);
	if(Ret != 0)
	{
		ERROR_LOG(0,"Failed to send LICENSE response message.\n");
	}

	return Ret;
}

void KFPC_LicenseSerAPIHandler::RecvLIC_IPRLIC( KFPC_MSG_HEADER* pMsg )
{
	KFPC_MSG_HEADER&				Header					= *pMsg;

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_LIC_REQ_IPR*	pREQMsg = (KFPC_LIC_REQ_IPR*)pMsg;

		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x(%u),"
			"Header.un32DstAPPId:0x%x(%u),"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u",
			Header.un32SrcAPPId,Header.un32SrcAPPId,
			Header.un32DstAPPId,Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2);	

		OnREQ_LIC_IPRECLIC(pREQMsg);

	}
	else if (KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_LIC_RSP_IPR*	pRSPMsg = (KFPC_LIC_RSP_IPR*)pMsg;
		Decrypt(&pRSPMsg->IPR_INFO,sizeof(KFPC_IPR_INFO));

		char	TimeBuf[100]="";
		INFO_LOG(0,
			"Header.un32SrcAPPId:0x%x(%u),"
			"Header.un32DstAPPId:0x%x(%u),"
			"Header.un32UserContext1:%u,"
			"Header.un32UserContext2:%u,"
			"ValidTime(%s),SipChCount(%u) Audio(%u) Video(%u) Traffic(%u) AppCount(%u)"
			,
			Header.un32SrcAPPId,Header.un32SrcAPPId,
			Header.un32DstAPPId,Header.un32DstAPPId,
			Header.un32UserContext1,
			Header.un32UserContext2,
			TimeToStr(TimeBuf,pRSPMsg->IPR_INFO.ValidTime),
			pRSPMsg->IPR_INFO.ChCount,
			pRSPMsg->IPR_INFO.Audio,
			pRSPMsg->IPR_INFO.Video,
			pRSPMsg->IPR_INFO.Traffic,
			pRSPMsg->IPR_INFO.AppCount);	

		OnRSP_LIC_IPRECLIC(pRSPMsg);
	}
	else
	{
		WARNING_LOG(0,"MsgType:%u error.",pMsg->un32MsgType);

	}
}
