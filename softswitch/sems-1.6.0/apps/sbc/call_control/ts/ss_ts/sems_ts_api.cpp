#include "sems_ts_api.h"
#include "kfpc_logex.h"
#include "KFPC_TServerMain.h"
#include "KFPC_TServerConfigFile.h"

SEMS_TS_API void OnStart(const char* callid, const char* remote_tag, const char* local_tag, void* pCallLeg)
{
	DEBUG_LOG(0, "pCallLeg:0x%x,callid:%s,remote_tag:%s,local_tag:%s",
			pCallLeg,
		callid,
		remote_tag,
		local_tag);
}

SEMS_TS_API void OnInvite(
	const char* callid, void* pCallLeg,
	KFPC_From_t*	pFrom,
	KFPC_To_t*		pTo,
	KFPC_Receive_Info_t*	pReceive_Info,
	KFPC_SdpInfo_t* pSdpInfo)
{
	DEBUG_LOG(0, 
		"callid:%s,pCallLeg:0x%x,"
		"Receive_Info.FromIp:%s,"
		"Receive_Info.FromPort:%d,"
		"Receive_Info.InterfaceIp:%s:%d,"
		"From.UserInfo:%s,"
		"From.DisplayName:%s,"
		"From.HostPort.Host:%s:%d,"
		"From.HostPort.Tag:%s,"
		"To.DisplayName:%s,"
		"To.UserInfo:%s,"
		"To.HostPort.Host:%s:%d,"
		"To.Tag:%s"
		,
		callid,pCallLeg,
		pReceive_Info->FromIp.c_str(),
		pReceive_Info->FromPort,
		pReceive_Info->InterfaceIp.c_str(),
		pReceive_Info->InterfacePort,

		pFrom->DisplayName.c_str(),
		pFrom->UserInfo.c_str(),
		pFrom->HostPort.Host.c_str(),
		pFrom->HostPort.Port,
		pFrom->Tag.c_str(),

		pTo->DisplayName.c_str(),
		pTo->UserInfo.c_str(),
		pTo->HostPort.Host.c_str(),
		pTo->HostPort.Port,
		pTo->Tag.c_str()
		);

	unsigned int	StatusCode = 403;
	char			ReasonText[KFPC_SIP_SER_MAX_REASONTEXT] = "";

	do
	{

		KFPC_TrunkGroup* pMyTrunkGroup = SSTServerCfgInstance->GetTrunkGroupMgr()->GetTrunkGroupByIP(pReceive_Info->FromIp.c_str());
		if (NULL == pMyTrunkGroup)
		{
			WARNING_LOG(0, "Failed to find TrunkGroup by IP %s", pReceive_Info->FromIp.c_str());
			strncpy(ReasonText, "Forbidden", KFPC_SIP_SER_MAX_REASONTEXT);
			break;
		}
		else
		{
			DEBUG_LOG(0,"find TrunkGroup:%s by IP %s", 
				pMyTrunkGroup->GetName(),
				pReceive_Info->FromIp.c_str());
		}


		KFPC_SdpMedia_t*	pSdpMedia = NULL;
		const AudioCodeCfg_t* pAudioCodeCfg = pMyTrunkGroup->SelectMediaInfoFromSdp(pSdpInfo, &pSdpMedia);

		if (NULL == pAudioCodeCfg)
		{
			WARNING_LOG(0, "Code not match.");
			StatusCode = 415;
			strncpy(ReasonText, "Unsupported Media Type", KFPC_SIP_SER_MAX_REASONTEXT);
			break;
		}
		else
		{
			DEBUG_LOG(0, "Matched CodeID:%u,PayloadType:%u,CodeName:%s",
				pAudioCodeCfg->CodeID,
				pAudioCodeCfg->PayloadType,
				pAudioCodeCfg->CodeName.c_str());
		}

		//if (!KFPC_MySipChMgrInstance->CheckLicValidTime())
		//{
		//	ERROR_LOG(0, "license over time.");

		//	KFPC_CallAlarmMgr_Instance->LicAlarm("license over time");

		//	StatusCode = 603;
		//	strncpy(ReasonText, "Decline", KFPC_SIP_SER_MAX_REASONTEXT);
		//	break;
		//}

		unsigned int ChannelIdx;
		if (pMyTrunkGroup->GetIdleChannel(UINTTYPE, &ChannelIdx) != 0)
		{
			WARNING_LOG(0, "TrunkGroup:%s allocal ChID fail and drop call.",
				pMyTrunkGroup->GetName());

			StatusCode = 500;
			strncpy(ReasonText, "no idle channel", KFPC_SIP_SER_MAX_REASONTEXT);
			break;
		}
		else
		{
			KFPC_Channel* pCh = KFPC_ChMgrInstance->GetChannel(ChannelIdx);


			if (NULL != pCh)
			{
				INFO_LOG(0, "Call Offered FromHost:%s,ToHost:%s, Caller:%s,Called:%s,from MediaIP:%s,MySipID:%u,ChID:%u,TrunkGroupName:%s",
					pFrom->HostPort.Host.c_str(),
					pTo->HostPort.Host.c_str(),
					pTo->UserInfo.c_str(),
					pSdpInfo->Address.c_str(),
					ChannelIdx, pCh->GetID(), pMyTrunkGroup->GetName());

				KFPC_DEVICE Device;
				memset(&Device, 0, sizeof(KFPC_DEVICE));

				strncpy(Device.CalledNO, pTo->UserInfo.c_str(), KFPC_MAX_NUMBER_SIZE);
				strncpy(Device.CallerNO, pFrom->UserInfo.c_str(), KFPC_MAX_NUMBER_SIZE);
				strncpy(Device.TrunkGroup, pMyTrunkGroup->GetName(), KFPC_TRUNKGROUP_NAME_LEN);



				pCh->SetPeerMediaIP(pSdpInfo->Address);
				pCh->SetPeerMediaPort(pSdpMedia->Port);
				pCh->SetAudioCode(*pAudioCodeCfg);
				pCh->SetReceive_Info(*pReceive_Info);
				pCh->SetFrom(*pFrom);
				pCh->SetTo(*pTo);
				pCh->SetSIP_CallID(callid);

				pCh->EVT_IncomingCall(Device);

			}
			else
			{
				WARNING_LOG(0, "Failed to get sip channel ChID:%u.", ChannelIdx);

				StatusCode = 500;
				strncpy(ReasonText, "Failed to get sip channel", KFPC_SIP_SER_MAX_REASONTEXT);
				break;
			}
		}

		return;
	} while (false);


	//Send_REQ_SIP_RESPONSE(pMsg->Header.un32SrcAPPId, &pMsg->DialogID, &pMsg->TransactionID, 0, StatusCode, ReasonText, 0, 0);
}

SEMS_TS_API void OnSessionStart(void* pCallLeg, unsigned long long TSCallID)
{
	DEBUG_LOG(TSCallID, "pCallLeg:0x%x", pCallLeg);
}


SEMS_TS_API void OnRinging(void* pCallLeg, unsigned long long TSCallID)
{

}

SEMS_TS_API void OnEarlySession(void* pCallLeg, unsigned long long TSCallID)
{

}

SEMS_TS_API void OnFailedCall(void* pCallLeg, unsigned long long TSCallID)
{

}

SEMS_TS_API void OnSipRequest(void* pCallLeg, unsigned long long TSCallID)
{

}

SEMS_TS_API void OnSipReply(void* pCallLeg, unsigned long long TSCallID)
{

}

SEMS_TS_API void OnBeforeDestroy(void* pCallLeg, unsigned long long TSCallID)
{

}

SEMS_TS_API void OnHangup(void* pCallLeg, unsigned long long TSCallID)
{

}

SEMS_TS_API void OnHold(void* pCallLeg, unsigned long long TSCallID)
{

}

SEMS_TS_API void OnUnHold(void* pCallLeg, unsigned long long TSCallID)
{

}

SEMS_TS_API void OnB2BOtherRequest(void* pCallLeg, unsigned long long TSCallID)
{

}

SEMS_TS_API void OnB2BOtherReply(void* pCallLeg, unsigned long long TSCallID)
{

}

SEMS_TS_API void OnB2BOtherBye(void* pCallLeg, unsigned long long TSCallID)
{

}

SEMS_TS_API void OnSessionTimeout(void* pCallLeg, unsigned long long TSCallID)
{

}

SEMS_TS_API void OnRtpTimeout(void* pCallLeg, unsigned long long TSCallID)
{

}

SEMS_TS_API void OnRemoteDisappeared(void* pCallLeg, unsigned long long TSCallID)
{

}

SEMS_TS_API void OnStartup()
{
	DEBUG_LOG(0, "");
	TServerMain(NULL);
}

SEMS_TS_API void OnReload()
{
	DEBUG_LOG(0, "");
}

SEMS_TS_API void OnSystem()
{
	DEBUG_LOG(0, "");
}

SEMS_TS_API void OnDestroy()
{
	DEBUG_LOG(0, "");
	TServerClose();
}
