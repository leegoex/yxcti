

#include "kfpc_logex.h"
#include "KFPC_ComApiHanderImp.h"
#include "KFPC_AppMainThread.h"
//#include "KFPC_DBTaskImp.h"
#include "KFPC_DBThreadPool.h"

//#include "KFPC_EHSwitch.h"
//#include "KFPC_FaxSerMgr.h"
//#include "KFPC_TTSSerMgr.h"
//#include "KFPC_VoiceSerMgr.h"
#include "KFPC_CmdMgr.h"
#include "KFPC_TServerErr.h"
#include "KFPC_TSLicSerMgr.h"
//#include "KFPC_TSLicenseSerAPIHandlerImp.h"
//#include "KFPC_NodeMgr.h"
#include "KFPC_TServerConfigFile.h"
#include "KFPC_MonitorRefreshData.h"
//#include "KFPC_SipSerMgr.h"

KFPC_ComApiHanderImp::KFPC_ComApiHanderImp(void)
{
}


KFPC_ComApiHanderImp::~KFPC_ComApiHanderImp(void)
{
}



void KFPC_ComApiHanderImp::OnEVT_API_REMOTE_CONNECTED( KFPC_EVT_API_REMOTE_CONNECTED* pMsg )
{
	
	if(KFPC_APP_TYPE_CTI == pMsg->AppInfo.AppType)
	{
		CTIServerConnected(pMsg);
	}
	
	if(KFPC_APP_TYPE_ROUTER == pMsg->AppInfo.AppType)
	{
		RouteServerConnected(pMsg);
	}

}

void KFPC_ComApiHanderImp::OnEVT_API_APP_DISCONNECT( KFPC_EVT_API_APP_DISCONNECT* pMsg )
{
	if (KFPC_APP_TYPE_FAX == pMsg->AppType)
	{
		//KFPC_FaxSerMgrInstance->RemoveFaxSer(pMsg->Header.un32SrcAPPId);
		//ExeFaxRelatedCmd(pMsg);
	}
	else if(KFPC_APP_TYPE_VOICE == pMsg->AppType)
	{
		//KFPC_VoiceSerMgrInstance->RemoveVoiceSer(pMsg->Header.un32SrcAPPId);
	}
	else if(KFPC_APP_TYPE_TTS == pMsg->AppType)
	{
		//KFPC_TTSSerMgrInstance->RemoveTTSSer(pMsg->Header.un32SrcAPPId);
	}
	else if(pMsg->AppType == KFPC_APP_TYPE_LICENSE)
	{
		KFPC_TSLicSerMgrInstance->RemoveLicSer(pMsg->Header.un32SrcAPPId);
	}
	else if(pMsg->AppType == KFPC_APP_TYPE_ROUTER)
	{
		KFPC_ChMgrInstance->OnAPP_DISCONNECT(pMsg->Header.un32SrcAPPId);
	}
	else if(pMsg->AppType == KFPC_APP_TYPE_SIPSERVER)
	{
		//KFPC_SipSerMgrInstance->RemoveSipSer(pMsg->Header.un32SrcAPPId);
	}
}

void KFPC_ComApiHanderImp::OnEVT_LOCAL_REDUNDANCE_STATUS_CHANGE( KFPC_EVT_LOCAL_REDUNDANCE_STATUS_CHANGE* pMsg )
{
	if(pMsg->MasterFlag)
	{
		/**
		  *	初始化通道状态
		  */
		 //KFPC_DBTaskImp* pDBTask = NULL;
		 //unsigned long long CallID = 0;	/**< 没有实际意义 */
		 //smart_new(KFPC_DBTaskImp(0,CallID,KFPC_DB_DelAllChannelStatus,0,0,0,CH_TYPE_AG),pDBTask);
		 //KFPC_DBThreadPoolInstance->PutTask(pDBTask);

		KFPC_AppMainThreadInstance->RegisterLoopHandler(KFPC_MonitorRefreshData_Instance,"KFPC_MonitorRefreshData_Instance");

		//if(KFPC_EHSwitchInstance->Open() == 0)
		//{
		//	 /**
		//	  *	注册EH 消息处理器
		//	  */
		//	KFPC_AppMainThreadInstance->RegisterLoopHandler(KFPC_EHSwitchInstance,"KFPC_EHSwitchInstance");
		//	KFPC_AppMainThreadInstance->SetTimeOut(0);
		//}
	}
	else
	{
		
		 /**
		  *	删除EH 消息处理器
		  */
		//KFPC_AppMainThreadInstance->RemoverLoopHandler(KFPC_EHSwitchInstance);
		//KFPC_EHSwitchInstance->Close();
		KFPC_AppMainThreadInstance->SetTimeOut(500);
	}
	
}

void KFPC_ComApiHanderImp::CTIServerConnected( KFPC_EVT_API_REMOTE_CONNECTED* pMsg )
{
	SSTServerCfgInstance->GetTrunkGroupMgr()->Send_EVT_UpdateTrunkGroup(pMsg->AppInfo.AppID);
}

void KFPC_ComApiHanderImp::OnEVT_API_LOCAL_CONNECTED( KFPC_EVT_API_LOCAL_CONNECTED* pMsg )
{
	if(pMsg->Result == 0)
	{
		KFPC_AppInfo AppInfo;
		memset(&AppInfo,0,sizeof(KFPC_AppInfo));

		if (0==KFPC_GetAppInfo(pMsg->RemoteAppID,&AppInfo))
		{
			if(KFPC_APP_TYPE_FAX == AppInfo.AppType)
			{
				ConnectFaxServerSuccesful(pMsg);
			}
			else if(KFPC_APP_TYPE_VOICE == AppInfo.AppType)
			{
				ConnectVoiceServerSuccesful(pMsg);
			}
			else if(KFPC_APP_TYPE_TTS == AppInfo.AppType)
			{
				ConnectTTSServerSuccesful(pMsg);
			}
			else if(KFPC_APP_TYPE_LICENSE == AppInfo.AppType)
			{
				ConnectLicServerSuccesful(pMsg);
			}
			else if(KFPC_APP_TYPE_SIPSERVER == AppInfo.AppType)
			{
				SipServerConnected(pMsg);
			}
		}
	}

}

void KFPC_ComApiHanderImp::ConnectLicServerSuccesful( KFPC_EVT_API_LOCAL_CONNECTED* pMsg )
{
	KFPC_TSLicSerMgrInstance->AddLicSer(pMsg->RemoteAppID);
	//KFPC_NodeMgrInstance->RequestAllLic();

	//KFPCTSLicenseSerAPIHandlerImpInstance->SendREQ_LIC_TSERVERLIC(0,0,pMsg->RemoteAppID,KFPC_GetLibParam()->AppInfo.AppType);
}

void KFPC_ComApiHanderImp::ConnectFaxServerSuccesful( KFPC_EVT_API_LOCAL_CONNECTED* pMsg )
{
	//KFPC_FaxSerMgrInstance->AddFaxSer(pMsg->RemoteAppID);
}

void KFPC_ComApiHanderImp::ConnectVoiceServerSuccesful( KFPC_EVT_API_LOCAL_CONNECTED* pMsg )
{
	//KFPC_VoiceSerMgrInstance->AddVoiceSer(pMsg->RemoteAppID);
}

void KFPC_ComApiHanderImp::ConnectTTSServerSuccesful( KFPC_EVT_API_LOCAL_CONNECTED* pMsg )
{
	//KFPC_TTSSerMgrInstance->AddTTSSer(pMsg->RemoteAppID);
}

void KFPC_ComApiHanderImp::OnEVT_API_REMOTE_APP_OFFLINE(KFPC_EVT_API_REMOTE_APP_OFFLINE* pMsg)
{
	if(KFPC_GetLibParam()->AppInfo.AppGroupID != pMsg->AppInfo.AppGroupID)
	{
		return;
	}
	switch(pMsg->AppInfo.AppType)
	{
	case KFPC_APP_TYPE_TSERVER:
		{
		}
		break;
	case KFPC_APP_TYPE_CTI:
		{
		}
		break;
	case KFPC_APP_TYPE_CCS:
		{
		}
		break;
	case KFPC_APP_TYPE_AGENT:
		{

		}
		break;
	case KFPC_APP_TYPE_TTS:
		{
		}
		break;
	case KFPC_APP_TYPE_VOICE:
		{
		}
		break;
	case KFPC_APP_TYPE_FAX:
		{
			
		}
		break;
	}
	return;
}
//
//void KFPC_ComApiHanderImp::ExeFaxRelatedCmd( KFPC_EVT_API_APP_DISCONNECT* pMsg )
//{
//	unsigned int FaxID = pMsg->Header.un32SrcAPPId;
//	KFPC_BaseCommand* pCmd = NULL;
//	unsigned int MsgID = 0;
//
//	KFPC_CmdMgrInstance->SetBeginCmdIter();
//	while(KFPC_CmdMgrInstance->GetExeCmdIter() != KFPC_CmdMgrInstance->m_CommandMap.end())
//	{
//		pCmd = KFPC_CmdMgrInstance->GetExeCmd();
//		MsgID = pCmd->GetMsgID();
//		if(pCmd->GetCmdTypeIsCmdSet())
//		{
//			KFPC_BaseCommand* pExeCmd = KFPC_CmdMgrInstance->GetCmd(pCmd->GetExeCmdID());
//			MsgID = pExeCmd->GetMsgID();
//			pCmd->SetStopFlag(true,KFPC_ERR_FAXDisconnected);
//		}
//
//		if(MsgID == KFPC_MSG_ID_TS_SendFax || MsgID == KFPC_MSG_ID_TS_RecvFax)
//		{
//			KFPC_Channel* pCh = NULL;
//			unsigned int CheckCallRet = KFPC_ChMgrInstance->CheckCallID(pCmd->GetCallID(),&pCh);
//
//			if(0 == CheckCallRet  && FaxID == pCh->GetFaxAppID() )
//			{
//				pCh->ProcessFaxAppOffLine();
//				pCh->CancelCmd();
//
//				//注意:当command被free后,迭代器要重新回到开始
//				KFPC_CmdMgrInstance->SetBeginCmdIter();
//			}
//			else
//			{
//				KFPC_CmdMgrInstance->SetNextCmdIter();
//			}
//		}
//		else
//		{
//			KFPC_CmdMgrInstance->SetNextCmdIter();
//		}
//		
//	}
//}

void KFPC_ComApiHanderImp::RouteServerConnected( KFPC_EVT_API_REMOTE_CONNECTED* pMsg )
{
	SSTServerCfgInstance->GetTrunkGroupMgr()->Send_EVT_UpdateTrunkGroup(pMsg->AppInfo.AppID);
}

void KFPC_ComApiHanderImp::SipServerConnected(  KFPC_EVT_API_LOCAL_CONNECTED* pMsg )
{
	//KFPC_SipSerMgrInstance->AddSipSer(pMsg->AppInfo.AppID);
}