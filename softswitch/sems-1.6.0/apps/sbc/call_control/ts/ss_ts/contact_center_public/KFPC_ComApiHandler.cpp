#include "KFPC_ComApiHandler.h"
#include "kfpc_logex.h"
#include "kfpc_linuxwinapi.h"

KFPC_ComApiHandler::KFPC_ComApiHandler(void)
{	
	for(unsigned int i = 0;i<KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_API_END);i++)
	{
		m_MsgProcFunMap[i] = NULL;
	}

	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_API_REMOTE_APP_ONLINE)					] = &KFPC_ComApiHandler::DoAPI_REMOTE_APP_ONLINE;	
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_API_REMOTE_APP_OFFLINE)					] = &KFPC_ComApiHandler::DoAPI_REMOTE_APP_OFFLINE;					
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_API_LOCAL_CONNECTED)						] = &KFPC_ComApiHandler::DoAPI_LOCAL_CONNECTED;						
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_API_REMOTE_CONNECTED)						] = &KFPC_ComApiHandler::DoAPI_REMOTE_CONNECTED;					
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_API_APP_DISCONNECT)						] = &KFPC_ComApiHandler::DoAPI_APP_DISCONNECT;						
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_API_LOCAL_REDUNDANCE_STATUS_CHANGE)		] = &KFPC_ComApiHandler::DoAPI_LOCAL_REDUNDANCE_STATUS_CHANGE;		
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_API_REMOTE_APP_REDUNDANCE_STATUS_CHANGE)	] = &KFPC_ComApiHandler::DoAPI_REMOTE_APP_REDUNDANCE_STATUS_CHANGE;	
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_API_TEST_MSG)								] = &KFPC_ComApiHandler::DoAPI_TEST_MSG;							
	m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(KFPC_MSG_ID_API_APPID_CONFLICT)						] = &KFPC_ComApiHandler::DoAPI_APPID_CONFLICT;	
	
	memset(m_AuthPassWord,0,KFPC_MAX_PASSWD_LEN);
}													


KFPC_ComApiHandler::~KFPC_ComApiHandler(void)
{
}

void KFPC_ComApiHandler::RecvMsg( KFPC_MSG_HEADER* pMsg )
{
	unsigned int MsgGroupID = KFPC_MSG_ID_GET_GROUP(pMsg->un32MsgId);

	if(MsgGroupID ==  KFPC_ID_CLASS_COM_API &&
		KFPC_MSG_ID_API_END > pMsg->un32MsgId )
	{
		MessageProcFun pFun = m_MsgProcFunMap[KFPC_MSG_ID_GET_SUBID(pMsg->un32MsgId)];

		if(pFun != NULL)
		{
			(this->*(pFun))(pMsg);
		}
	}
}

int KFPC_ComApiHandler::SendMsg( KFPC_MSG_HEADER* pMsg )
{
	return 0;
}

void KFPC_ComApiHandler::DoAPI_REMOTE_APP_ONLINE( KFPC_MSG_HEADER* pMsg )
{
	KFPC_EVT_API_REMOTE_APP_ONLINE* pRemoteAppOnline	= (KFPC_EVT_API_REMOTE_APP_ONLINE*)pMsg;
	const char*						MsgID				= KFPC_MSG_ID_API_TO_STRING(pMsg->un32MsgId);
	KFPC_AppInfo&					AppInfo				= pRemoteAppOnline->AppInfo;

	BEGIN_MSG_LOG(0,"");
	APPEND_MSG_LOG("%s",	MsgID);
	APPEND_MSG_LOG("%s",	AppInfo.AppName);
	APPEND_MSG_LOG("0x%x",	AppInfo.AppID);
	APPEND_MSG_LOG("%u",	AppInfo.AppGroupID);
	APPEND_MSG_LOG("%u",	AppInfo.AppType);
	APPEND_MSG_LOG("%u",	AppInfo.MasterFlag);
	APPEND_MSG_LOG("%s",	AppInfo.PeerIp);
	APPEND_MSG_LOG("%u",	AppInfo.ListenPort);
	END_MSG_LOG();

	OnEVT_API_REMOTE_APP_ONLINE(pRemoteAppOnline);
}

void KFPC_ComApiHandler::DoAPI_REMOTE_APP_OFFLINE( KFPC_MSG_HEADER* pMsg )
{
	KFPC_EVT_API_REMOTE_APP_OFFLINE*	pRemoteAppOffline	= (KFPC_EVT_API_REMOTE_APP_OFFLINE*)pMsg;
	const char*							MsgID				= KFPC_MSG_ID_API_TO_STRING(pMsg->un32MsgId);
	KFPC_MSG_HEADER&					Header				= *pMsg;

	BEGIN_MSG_LOG(0,"");
	APPEND_MSG_LOG("%s",	MsgID);
	APPEND_MSG_LOG("0x%x",	Header.un32SrcAPPId);
	APPEND_MSG_LOG("0x%x",	Header.un32DstAPPId);
	END_MSG_LOG();

	OnEVT_API_REMOTE_APP_OFFLINE(pRemoteAppOffline);
}

void KFPC_ComApiHandler::DoAPI_LOCAL_CONNECTED( KFPC_MSG_HEADER* pMsg )
{
	KFPC_EVT_API_LOCAL_CONNECTED*	pEVT_API_LOCAL_CONNECTED = (KFPC_EVT_API_LOCAL_CONNECTED*)pMsg;
	const char*						MsgID					= KFPC_MSG_ID_API_TO_STRING(pMsg->un32MsgId);
	KFPC_MSG_HEADER&				Header					= *pMsg;

	BEGIN_MSG_LOG(0,"");
	APPEND_MSG_LOG("%s",	MsgID);
	APPEND_MSG_LOG("0x%x",	Header.un32SrcAPPId);
	APPEND_MSG_LOG("0x%x",	Header.un32DstAPPId);
	APPEND_MSG_LOG("GroupID:%u",	Header.un32UserContext1);
	APPEND_MSG_LOG("AppID:%u",	Header.un32UserContext2);

	APPEND_MSG_LOG("%u",	pEVT_API_LOCAL_CONNECTED->LocalAppID);
	APPEND_MSG_LOG("%u",	pEVT_API_LOCAL_CONNECTED->RemoteAppID);
	APPEND_MSG_LOG("%u",	pEVT_API_LOCAL_CONNECTED->ConnectCount);
	APPEND_MSG_LOG("0x%x",	pEVT_API_LOCAL_CONNECTED->Result);
	APPEND_MSG_LOG("%s",	pEVT_API_LOCAL_CONNECTED->AppInfo.PeerIp);
	APPEND_MSG_LOG("%u",	pEVT_API_LOCAL_CONNECTED->AppInfo.ListenPort);
	APPEND_MSG_LOG("%s",	pEVT_API_LOCAL_CONNECTED->AppInfo.AppName);

	END_MSG_LOG();

	OnEVT_API_LOCAL_CONNECTED(pEVT_API_LOCAL_CONNECTED);

}

void KFPC_ComApiHandler::DoAPI_REMOTE_CONNECTED( KFPC_MSG_HEADER* pMsg )
{
	KFPC_EVT_API_REMOTE_CONNECTED*	pEVT_API_REMOTE_CONNECTED = (KFPC_EVT_API_REMOTE_CONNECTED*)pMsg;
	const char*						MsgID					= KFPC_MSG_ID_API_TO_STRING(pMsg->un32MsgId);
	KFPC_MSG_HEADER&				Header					= *pMsg;
	KFPC_AppInfo&					AppInfo					= pEVT_API_REMOTE_CONNECTED->AppInfo;

	char	UniqueIdentify[512];

	Buf2HexStr(AppInfo.UniqueIdentify,sizeof(AppInfo.UniqueIdentify),UniqueIdentify,512);

	//INFO_LOG(0,"UniqueIdentify:%s",BufStr);


	BEGIN_MSG_LOG(0,"");
	APPEND_MSG_LOG("%s",	MsgID);
	APPEND_MSG_LOG("0x%x",	Header.un32SrcAPPId);
	APPEND_MSG_LOG("0x%x",	Header.un32DstAPPId);
	APPEND_MSG_LOG("%u",	Header.un32UserContext1);
	APPEND_MSG_LOG("%u",	Header.un32UserContext2);
	APPEND_MSG_LOG("%s",	AppInfo.AppName);
	APPEND_MSG_LOG("%u",	AppInfo.AppID);
	APPEND_MSG_LOG("%u",	AppInfo.AppGroupID);
	APPEND_MSG_LOG("%u",	AppInfo.AppType);
	APPEND_MSG_LOG("%u",	AppInfo.MasterFlag);
	APPEND_MSG_LOG("%s",	AppInfo.PeerIp);
	APPEND_MSG_LOG("%u",	AppInfo.ListenPort);
	APPEND_MSG_LOG("%u",	pEVT_API_REMOTE_CONNECTED->SocketSN);
	APPEND_MSG_LOG("%s",	UniqueIdentify);
	END_MSG_LOG();

	OnEVT_API_REMOTE_CONNECTED(pEVT_API_REMOTE_CONNECTED);
}

void KFPC_ComApiHandler::DoAPI_APP_DISCONNECT( KFPC_MSG_HEADER* pMsg )
{
	KFPC_EVT_API_APP_DISCONNECT*	pEVT_API_APP_DISCONNECT = (KFPC_EVT_API_APP_DISCONNECT*)pMsg;
	const char*						MsgID					= KFPC_MSG_ID_API_TO_STRING(pMsg->un32MsgId);
	KFPC_MSG_HEADER&				Header					= *pMsg;
	

	BEGIN_MSG_LOG(0,"");
	APPEND_MSG_LOG("%s",	MsgID);
	APPEND_MSG_LOG("0x%x",	Header.un32SrcAPPId);
	APPEND_MSG_LOG("0x%x",	Header.un32DstAPPId);
	APPEND_MSG_LOG("%u",	Header.un32UserContext1);
	APPEND_MSG_LOG("%u",	Header.un32UserContext2);

	APPEND_MSG_LOG("%u",	pEVT_API_APP_DISCONNECT->LocalConnect);
	APPEND_MSG_LOG("%u",	pEVT_API_APP_DISCONNECT->DiscountCount);
	APPEND_MSG_LOG("%u",	pEVT_API_APP_DISCONNECT->SocketSN);
	END_MSG_LOG();

	OnEVT_API_APP_DISCONNECT(pEVT_API_APP_DISCONNECT);
}

void KFPC_ComApiHandler::DoAPI_LOCAL_REDUNDANCE_STATUS_CHANGE( KFPC_MSG_HEADER* pMsg )
{
	KFPC_EVT_LOCAL_REDUNDANCE_STATUS_CHANGE* pEVT_LOCAL_REDUNDANCE_STATUS_CHANGE = (KFPC_EVT_LOCAL_REDUNDANCE_STATUS_CHANGE*)pMsg;

	const char*						MsgID					= KFPC_MSG_ID_API_TO_STRING(pMsg->un32MsgId);
	KFPC_MSG_HEADER&				Header					= *pMsg;


	BEGIN_MSG_LOG(0,"");
	APPEND_MSG_LOG("%s",	MsgID);
	APPEND_MSG_LOG("0x%x",	Header.un32SrcAPPId);
	APPEND_MSG_LOG("0x%x",	Header.un32DstAPPId);
	APPEND_MSG_LOG("%u",	pEVT_LOCAL_REDUNDANCE_STATUS_CHANGE->MasterFlag);
	END_MSG_LOG();

	OnEVT_LOCAL_REDUNDANCE_STATUS_CHANGE(pEVT_LOCAL_REDUNDANCE_STATUS_CHANGE);

}

void KFPC_ComApiHandler::DoAPI_REMOTE_APP_REDUNDANCE_STATUS_CHANGE( KFPC_MSG_HEADER* pMsg )
{
	KFPC_EVT_API_REMOTE_APP_REDUNDANCE_STATUS_CHANGE* pRedundanceStatusChange = (KFPC_EVT_API_REMOTE_APP_REDUNDANCE_STATUS_CHANGE*)pMsg;
	const char*						MsgID					= KFPC_MSG_ID_API_TO_STRING(pMsg->un32MsgId);
	KFPC_MSG_HEADER&				Header					= *pMsg;


	BEGIN_MSG_LOG(0,"");
	APPEND_MSG_LOG("%s",	MsgID);
	APPEND_MSG_LOG("0x%x",	Header.un32SrcAPPId);
	APPEND_MSG_LOG("0x%x",	Header.un32DstAPPId);
	APPEND_MSG_LOG("%u",	pRedundanceStatusChange->MasterFlag);
	APPEND_MSG_LOG("%u",	pRedundanceStatusChange->RemoteAppID);
	END_MSG_LOG();

	OnEVT_API_REMOTE_APP_REDUNDANCE_STATUS_CHANGE(pRedundanceStatusChange);

}

void KFPC_ComApiHandler::DoAPI_TEST_MSG( KFPC_MSG_HEADER* pMsg )
{		
	const char*						MsgID						= KFPC_MSG_ID_API_TO_STRING(pMsg->un32MsgId);
	KFPC_MSG_HEADER&				Header						= *pMsg;

	BEGIN_MSG_LOG(0,"");
	APPEND_MSG_LOG("%s",	MsgID);
	APPEND_MSG_LOG("0x%x",	Header.un32SrcAPPId);
	APPEND_MSG_LOG("0x%x",	Header.un32DstAPPId);
	END_MSG_LOG();

	if(KFPC_MSG_TYPE_REQUEST == pMsg->un32MsgType)
	{
		KFPC_REQ_API_TEST_MSG&	REQ_API_TEST_MSG = *((KFPC_REQ_API_TEST_MSG*)pMsg);
		OnREQ_API_TEST_MSG(&REQ_API_TEST_MSG);
	}
	else if(KFPC_MSG_TYPE_RESPONSE == pMsg->un32MsgType)
	{
		KFPC_RSP_API_TEST_MSG&	RSP_API_TEST_MSG = *((KFPC_RSP_API_TEST_MSG*)pMsg);
		OnRSP_API_TEST_MSG(&RSP_API_TEST_MSG);
	}
}

void KFPC_ComApiHandler::DoAPI_APPID_CONFLICT( KFPC_MSG_HEADER* pMsg )
{
	KFPC_EVT_APPID_CONFLICTED*		pKFPC_EVT_APPID_CONFLICTED	= (KFPC_EVT_APPID_CONFLICTED*)pMsg;
	const char*						MsgID						= KFPC_MSG_ID_API_TO_STRING(pMsg->un32MsgId);
	KFPC_MSG_HEADER&				Header						= *pMsg;


	BEGIN_MSG_LOG(0,"");
	APPEND_MSG_LOG("%s",	MsgID);
	APPEND_MSG_LOG("0x%x",	Header.un32SrcAPPId);
	APPEND_MSG_LOG("0x%x",	Header.un32DstAPPId);
	APPEND_MSG_LOG("%u",	pKFPC_EVT_APPID_CONFLICTED->ConflictFlag);
	APPEND_MSG_LOG("%s",	pKFPC_EVT_APPID_CONFLICTED->PeerIP);
	END_MSG_LOG();

	OnEVT_APPID_CONFLICTED(pKFPC_EVT_APPID_CONFLICTED);
}



void KFPC_ComApiHandler::OnEVT_API_REMOTE_APP_ONLINE( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg )
{

	if(KFPC_GetLibParam()->AppInfo.AppGroupID == pMsg->AppInfo.AppGroupID)
	{
		AutoConnect(pMsg);
	}
}


void KFPC_ComApiHandler::AutoConnect( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg)
{
	switch(pMsg->AppInfo.AppType)
	{
	case KFPC_APP_TYPE_TSERVER:
		{
			AutoConnectTServer(pMsg);

		}
		break;
	case KFPC_APP_TYPE_CTI:
		{
			AutoConnectCTI(pMsg);
		}
		break;
	case KFPC_APP_TYPE_CCS:
		{
			AutoConnectCCS(pMsg);
		}
		break;
	case KFPC_APP_TYPE_AGENT:
		{

		}
		break;
	case KFPC_APP_TYPE_TTS:
		{
			AutoConnectTTS(pMsg);
		}
		break;
	case KFPC_APP_TYPE_VOICE:
		{
			AutoConnectVOICE(pMsg);
		}
		break;
	case KFPC_APP_TYPE_FAX:
		{
			AutoConnectFAX(pMsg);
		}
		break;
	case KFPC_APP_TYPE_ROUTER:
		{
			AutoConnectRoute(pMsg);
		}
		break;
	case KFPC_APP_TYPE_LICENSE:
		{
			AutoConnectLicense(pMsg);
		}
		break;
	case KFPC_APP_TYPE_BILL:
		{
			AutoConnectBill(pMsg);
		}
		break;
	case KFPC_APP_TYPE_SMS:
		{
			AutoConnectSMS(pMsg);
		}
		break;
	case KFPC_APP_TYPE_FAXCONVERT:
		{
			AutoConnectFaxConvert(pMsg);
		}		
		break;
	case KFPC_APP_TYPE_SIPSERVER:
		{
			AutoConnectSipServer(pMsg);
		}
		break;
	case KFPC_APP_TYPE_NOTIFY:
		{
			AutoConnectNotifyServer(pMsg);
		}
		break;
	}
}

void KFPC_ComApiHandler::AutoConnectTServer( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg )
{

	unsigned int SocketSN = 0;

	switch(KFPC_GetLibParam()->AppInfo.AppType)
	{
	/*case KFPC_APP_TYPE_CTI:
		{
			KFPC_Connect(pMsg->AppInfo.PeerIp,
				pMsg->AppInfo.ListenPort,
				m_AuthPassWord,
				0,
				0,
				&SocketSN,
				false);
		}
		break;
		*/
	case KFPC_APP_TYPE_ROUTER:
	case KFPC_APP_TYPE_CTRL:
		{
			unsigned int Ret = KFPC_Connect(pMsg->AppInfo.PeerIp,
				pMsg->AppInfo.ListenPort,
				m_AuthPassWord,
				0,
				0,
				&SocketSN,
				false);

			INFO_LOG(0,"PeerIP:%s,Port:%u,PWD:%s,Ret:%u",pMsg->AppInfo.PeerIp,pMsg->AppInfo.ListenPort,m_AuthPassWord,Ret);
		}
		break;
	}
}

void KFPC_ComApiHandler::AutoConnectCTI( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg )
{
	switch(KFPC_GetLibParam()->AppInfo.AppType)
	{

	case KFPC_APP_TYPE_CCS:
		{

		}
		break;

	}
}

void KFPC_ComApiHandler::AutoConnectCCS( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg )
{
	switch(KFPC_GetLibParam()->AppInfo.AppType)
	{

	case KFPC_APP_TYPE_AGENT:
		{

		}
		break;
	case KFPC_APP_TYPE_IVR:
		{
			IVRAutoConnectCCS(pMsg);

		}
		break;
	case KFPC_APP_TYPE_PBX:
		{
			PBXAutoConnectCCS(pMsg);
		}
		break;
	case KFPC_APP_TYPE_FAXFLOW:
		{
			FaxFlowAutoConnectCCS(pMsg);
		}
		break;
	case KFPC_APP_TYPE_CTRL:
		{
			CtrlAutoConnectCCS(pMsg);
		}
		break;
	case KFPC_APP_TYPE_NODE_CCS:
		{
			NodeCCSConnectCCS(pMsg);
		}
		break;
	}
}

void KFPC_ComApiHandler::AutoConnectTTS(KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg )
{

	unsigned int SocketSN = 0;

	INFO_LOG(0,"");
	switch(KFPC_GetLibParam()->AppInfo.AppType)
	{

	case KFPC_APP_TYPE_TSERVER:
		{
			unsigned int Ret = KFPC_Connect(pMsg->AppInfo.PeerIp,
				pMsg->AppInfo.ListenPort,
				m_AuthPassWord,
				0,
				0,
				&SocketSN,
				false);

			INFO_LOG(0,"PeerIP:%s,Port:%u,PWD:%s,Ret:%u",pMsg->AppInfo.PeerIp,pMsg->AppInfo.ListenPort,m_AuthPassWord,Ret);
		}
		break;

	}
}

void KFPC_ComApiHandler::AutoConnectVOICE( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg )
{

	unsigned int SocketSN = 0;

	switch(KFPC_GetLibParam()->AppInfo.AppType)
	{

	case KFPC_APP_TYPE_TSERVER:
		{
			unsigned int Ret = 0;
			Ret = KFPC_Connect(pMsg->AppInfo.PeerIp,
				pMsg->AppInfo.ListenPort,
				m_AuthPassWord,
				0,
				0,
				&SocketSN,
				false);
			INFO_LOG(0,"PeerIP:%s,Port:%u,PWD:%s,Ret:%u",pMsg->AppInfo.PeerIp,pMsg->AppInfo.ListenPort,m_AuthPassWord,Ret);
		}
		break;

	}
}

void KFPC_ComApiHandler::AutoConnectFAX(KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg )
{

	unsigned int SocketSN = 0;
	
	switch(KFPC_GetLibParam()->AppInfo.AppType)
	{

	case KFPC_APP_TYPE_TSERVER:
		{
			unsigned int Ret = 0;
			Ret = KFPC_Connect(pMsg->AppInfo.PeerIp,
				pMsg->AppInfo.ListenPort,
				m_AuthPassWord,
				0,
				0,
				&SocketSN,
				false);

			INFO_LOG(0,"PeerIP:%s,Port:%u,PWD:%s,Ret:%u",pMsg->AppInfo.PeerIp,pMsg->AppInfo.ListenPort,m_AuthPassWord,Ret);
		}
		break;

	}
}

void KFPC_ComApiHandler::AutoConnectRoute( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg )
{

	unsigned int SocketSN = 0;

	switch(KFPC_GetLibParam()->AppInfo.AppType)
	{

	case KFPC_APP_TYPE_CCS:
	case KFPC_APP_TYPE_CTRL:
	case KFPC_APP_TYPE_TANDEM:
		{
			unsigned int Ret = KFPC_Connect(pMsg->AppInfo.PeerIp,
				pMsg->AppInfo.ListenPort,
				m_AuthPassWord,
				0,
				0,
				&SocketSN,
				false);

			INFO_LOG(0,"PeerIP:%s,Port:%u,PWD:%s,Ret:%u",pMsg->AppInfo.PeerIp,pMsg->AppInfo.ListenPort,m_AuthPassWord,Ret);
		}
		break;
	case KFPC_APP_TYPE_CTI:
		{
			unsigned int Ret = KFPC_Connect(pMsg->AppInfo.PeerIp,
				pMsg->AppInfo.ListenPort,
				m_AuthPassWord,
				0,
				0,
				&SocketSN,
				false);

			INFO_LOG(0,"PeerIP:%s,Port:%u,PWD:%s,Ret:%u",pMsg->AppInfo.PeerIp,pMsg->AppInfo.ListenPort,m_AuthPassWord,Ret);
		}
		break;
	}
}

void KFPC_ComApiHandler::IVRAutoConnectCCS( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg )
{
	unsigned int SocketSN = 0;
	unsigned int Ret = KFPC_Connect(pMsg->AppInfo.PeerIp,
		pMsg->AppInfo.ListenPort,
		m_AuthPassWord,
		0,
		0,
		&SocketSN,
		false);

	INFO_LOG(0,"PeerIP:%s,Port:%u,PWD:%s,Ret:%u",pMsg->AppInfo.PeerIp,pMsg->AppInfo.ListenPort,m_AuthPassWord,Ret);
}

void KFPC_ComApiHandler::PBXAutoConnectCCS( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg )
{
	unsigned int SocketSN = 0;
	unsigned int Ret = KFPC_Connect(pMsg->AppInfo.PeerIp,
		pMsg->AppInfo.ListenPort,
		m_AuthPassWord,
		0,
		0,
		&SocketSN,
		false);

	INFO_LOG(0,"PeerIP:%s,Port:%u,PWD:%s,Ret:%u",pMsg->AppInfo.PeerIp,pMsg->AppInfo.ListenPort,m_AuthPassWord,Ret);
}

void KFPC_ComApiHandler::FaxFlowAutoConnectCCS( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg )
{
	unsigned int SocketSN = 0;
	unsigned int Ret = KFPC_Connect(pMsg->AppInfo.PeerIp,
		pMsg->AppInfo.ListenPort,
		m_AuthPassWord,
		0,
		0,
		&SocketSN,
		false);

	INFO_LOG(0,"PeerIP:%s,Port:%u,PWD:%s,Ret:%u",pMsg->AppInfo.PeerIp,pMsg->AppInfo.ListenPort,m_AuthPassWord,Ret);
}

void KFPC_ComApiHandler::AutoConnectLicense( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg )
{
	//unsigned int SocketSN = 0;

	switch(KFPC_GetLibParam()->AppInfo.AppType)
	{

	case KFPC_APP_TYPE_CCS:
	case KFPC_APP_TYPE_TSERVER:
	case KFPC_APP_TYPE_FAX:
	case KFPC_APP_TYPE_SOFTSWITCH:
	case KFPC_APP_TYPE_IPREC:
		{

		unsigned int SocketSN = 0;
		unsigned int Ret = KFPC_Connect(pMsg->AppInfo.PeerIp,
			pMsg->AppInfo.ListenPort,
			m_AuthPassWord,
			pMsg->AppInfo.AppGroupID,
			pMsg->AppInfo.AppID,
			&SocketSN,
			false);

		INFO_LOG(0,"PeerIP:%s,Port:%u,PWD:%s,Ret:%u,AppGroupID:%u,AppID:%u",
			pMsg->AppInfo.PeerIp,
			pMsg->AppInfo.ListenPort,
			m_AuthPassWord,Ret,
			pMsg->AppInfo.AppGroupID,
			pMsg->AppInfo.AppID);
		}
		break;
	default:
		break;
	}

}

void KFPC_ComApiHandler::AutoConnectBill( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg )
{
	//unsigned int SocketSN = 0;

	switch(KFPC_GetLibParam()->AppInfo.AppType)
	{
	case KFPC_APP_TYPE_CCS:
	case KFPC_APP_TYPE_TANDEM:
		{
			unsigned int SocketSN = 0;
			unsigned int Ret = KFPC_Connect(pMsg->AppInfo.PeerIp,
				pMsg->AppInfo.ListenPort,
				m_AuthPassWord,
				pMsg->AppInfo.AppGroupID,
				pMsg->AppInfo.AppID,
				&SocketSN,
				false);

			INFO_LOG(0,"PeerIP:%s,Port:%u,PWD:%s,Ret:%u,AppGroupID:%u,AppID:%u",
				pMsg->AppInfo.PeerIp,
				pMsg->AppInfo.ListenPort,
				m_AuthPassWord,Ret,
				pMsg->AppInfo.AppGroupID,
				pMsg->AppInfo.AppID);
		}
		break;
	default:
		break;
	}
}

void KFPC_ComApiHandler::AutoConnectSMS( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg )
{
	//unsigned int SocketSN = 0;

	switch(KFPC_GetLibParam()->AppInfo.AppType)
	{
	case KFPC_APP_TYPE_CCS:
		{
			unsigned int SocketSN = 0;
			unsigned int Ret = KFPC_Connect(pMsg->AppInfo.PeerIp,
				pMsg->AppInfo.ListenPort,
				m_AuthPassWord,
				pMsg->AppInfo.AppGroupID,
				pMsg->AppInfo.AppID,
				&SocketSN,
				false);

			INFO_LOG(0,"PeerIP:%s,Port:%u,PWD:%s,Ret:%u,AppGroupID:%u,AppID:%u",
				pMsg->AppInfo.PeerIp,
				pMsg->AppInfo.ListenPort,
				m_AuthPassWord,Ret,
				pMsg->AppInfo.AppGroupID,
				pMsg->AppInfo.AppID);
		}
		break;
	default:
		break;
	}
}

void KFPC_ComApiHandler::AutoConnectFaxConvert( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg )
{
	//unsigned int SocketSN = 0;

	switch(KFPC_GetLibParam()->AppInfo.AppType)
	{
	case KFPC_APP_TYPE_CCS:
		{
			unsigned int SocketSN = 0;
			unsigned int Ret = KFPC_Connect(pMsg->AppInfo.PeerIp,
				pMsg->AppInfo.ListenPort,
				m_AuthPassWord,
				pMsg->AppInfo.AppGroupID,
				pMsg->AppInfo.AppID,
				&SocketSN,
				false);

			INFO_LOG(0,"PeerIP:%s,Port:%u,PWD:%s,Ret:%u,AppGroupID:%u,AppID:%u",
				pMsg->AppInfo.PeerIp,
				pMsg->AppInfo.ListenPort,
				m_AuthPassWord,Ret,
				pMsg->AppInfo.AppGroupID,
				pMsg->AppInfo.AppID);
		}
		break;
	default:
		break;
	}
}

void KFPC_ComApiHandler::ConnectRemoteLicenseSer( const char* RemoteIP,unsigned int RemotePort )
{
	unsigned int SocketSN = 0;
	KFPC_Connect(RemoteIP,
		RemotePort,
		"kfpc",
		0,0,
		&SocketSN,
		true);

	INFO_LOG(0,"RemoteIP:%s,RemotePort:%u",RemoteIP,RemotePort);
}

void KFPC_ComApiHandler::CtrlAutoConnectCCS( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg )
{
	unsigned int SocketSN = 0;
	unsigned int Ret = KFPC_Connect(pMsg->AppInfo.PeerIp,
		pMsg->AppInfo.ListenPort,
		m_AuthPassWord,
		0,
		0,
		&SocketSN,
		false);

	INFO_LOG(0,"PeerIP:%s,Port:%u,PWD:%s,Ret:%u",pMsg->AppInfo.PeerIp,pMsg->AppInfo.ListenPort,m_AuthPassWord,Ret);
}

void KFPC_ComApiHandler::AutoConnectSipServer( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg )
{
	unsigned int SocketSN = 0;

	switch(KFPC_GetLibParam()->AppInfo.AppType)
	{

	case KFPC_APP_TYPE_TSERVER:
		{
			unsigned int Ret = 0;
			Ret = KFPC_Connect(pMsg->AppInfo.PeerIp,
				pMsg->AppInfo.ListenPort,
				m_AuthPassWord,
				0,
				0,
				&SocketSN,
				false);

			INFO_LOG(0,"PeerIP:%s,Port:%u,PWD:%s,Ret:%u",pMsg->AppInfo.PeerIp,pMsg->AppInfo.ListenPort,m_AuthPassWord,Ret);
		}
		break;

	}
}

void KFPC_ComApiHandler::AutoConnectNotifyServer( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg )
{
	unsigned int SocketSN = 0;

	switch(KFPC_GetLibParam()->AppInfo.AppType)
	{

	case KFPC_APP_TYPE_CCS:
		{
			unsigned int Ret = 0;
			Ret = KFPC_Connect(pMsg->AppInfo.PeerIp,
				pMsg->AppInfo.ListenPort,
				m_AuthPassWord,
				0,
				0,
				&SocketSN,
				false);

			INFO_LOG(0,"PeerIP:%s,Port:%u,PWD:%s,Ret:%u",pMsg->AppInfo.PeerIp,pMsg->AppInfo.ListenPort,m_AuthPassWord,Ret);
		}
		break;

	}
}

void KFPC_ComApiHandler::NodeCCSConnectCCS( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg )
{
	unsigned int SocketSN = 0;
	unsigned int Ret = KFPC_Connect(pMsg->AppInfo.PeerIp,
		pMsg->AppInfo.ListenPort,
		m_AuthPassWord,
		0,
		0,
		&SocketSN,
		false);

	INFO_LOG(0,"PeerIP:%s,Port:%u,PWD:%s,Ret:%u",pMsg->AppInfo.PeerIp,pMsg->AppInfo.ListenPort,m_AuthPassWord,Ret);
}

