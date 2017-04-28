#pragma once
#include "KFPC_BaseCommand.h"
#include "KFPC_ContactCenterPublicDef.h"
#include "KFPC_TrunkGroup.h"


class EH_Cmd_EVT_IncomingCall :
	public KFPC_BaseCommand
{
	enum Cmd_EVT_IncomingCallStatus
	{
		Cmd_Status_Start,							/**< 开始节点 */
		Cmd_Status_CalledNumBroken
	};
private:
	Cmd_EVT_IncomingCallStatus	m_Cmd_Status;

	//KFPC_DEVICE	m_Device;
	//KFPC_SignalType	m_SignalType;
	virtual void SendRSP(unsigned int Ret){}
public:
	EH_Cmd_EVT_IncomingCall(unsigned long long& CallID,unsigned int DstAppID,unsigned int UserContext1,unsigned int UserContext2,bool SubCmd = false);
	virtual ~EH_Cmd_EVT_IncomingCall(void);
	virtual unsigned int Execute(unsigned int MsgID,KFPC_MSG_TYPE MsgType,KFPC_MSG_HEADER* MsgHeader= NULL,void* pMsg = NULL);

	unsigned int CallOfferToApp( KFPC_TrunkGroup* pTrunkGroup, KFPC_Channel* pCh );

	//KFPC_DEVICE& GetDevice() { return m_Device; }
	
};

