#include "kfpc_logex.h"
#include "KFPC_TSLicenseSerAPIHandlerImp.h"
#include "KFPC_TSLicSerMgr.h"
#include "KFPC_NodeMgr.h"
#include "KFPC_StringUtils.h"
#include "KFPC_CallAlarmMgr.h"

KFPC_TSLicenseSerAPIHandlerImp::KFPC_TSLicenseSerAPIHandlerImp(void)
{
	
}


KFPC_TSLicenseSerAPIHandlerImp::~KFPC_TSLicenseSerAPIHandlerImp(void)
{
}

void KFPC_TSLicenseSerAPIHandlerImp::OnRSP_LIC_TSERVERLIC(KFPC_LIC_RSP_TSERVERLIC* pMsg)
{
	if (pMsg->Result == 0)
	{
		char	TimeBuf[100]="";
		DEBUG_LOG(0,"SwitchID:%s,AgChCount:%d,SpanChCount:%d,VoipChCount:%d,IVRChCount:%d,ValidTime:%s.",
			pMsg->TServerLic.SwichID,
			pMsg->TServerLic.AgChCount,
			pMsg->TServerLic.SpanChCount,
			pMsg->TServerLic.VoipChCount,
			pMsg->TServerLic.IVRChCount,
			TimeToStr(TimeBuf,pMsg->TServerLic.ValidTime)
			);

		KFPC_TSLicSer *pLicSer = NULL;
		pLicSer = KFPC_TSLicSerMgrInstance->GetLicSer(pMsg->MsgHead.un32SrcAPPId);
		if (NULL == pLicSer)
		{
			pLicSer = KFPC_TSLicSerMgrInstance->AddLicSer(pMsg->MsgHead.un32SrcAPPId);
		}

		if (NULL == pLicSer)
		{
			WARNING_LOG(0,"pLicSer is NULL!")
				return;
		}

		KFPC_EHNode*	pEHNode = KFPC_NodeMgrInstance->GetNode(pMsg->TServerLic.SwichID);
		
		if(pEHNode != NULL)
		{
			pEHNode->SetAgChLicCount(pMsg->TServerLic.AgChCount);
			pEHNode->SetSpanChLicCount(pMsg->TServerLic.SpanChCount* 32);
			pEHNode->SetVoipChLicCount(pMsg->TServerLic.VoipChCount);
			pEHNode->SetIVRChLicCount(pMsg->TServerLic.IVRChCount);
			pEHNode->SetValidTime(time(NULL)+3600);
			pEHNode->SetTimer(600);

			KFPC_CallAlarmMgr_Instance->LicAlarmRecovery();
		}

	}
	else
	{
		WARNING_LOG(0,"SwitchID:%s,Result:%d",pMsg->TServerLic.SwichID,pMsg->Result);
		KFPC_EHNode*	pEHNode = KFPC_NodeMgrInstance->GetNode(pMsg->TServerLic.SwichID);

		if(pEHNode != NULL)
		{
			pEHNode->SetTimer(GET_TS_LICFAIL_TIMER,pMsg->MsgHead.un32UserContext1);
			//pEHNode->GetLic(pMsg->MsgHead.un32UserContext1);
						
		}
	}

	//设置定时，下一次请求时间
}

void KFPC_TSLicenseSerAPIHandlerImp::OnRSP_LIC_CCSLIC(KFPC_LIC_RSP_CCSLIC* pMsg)
{
	
}
