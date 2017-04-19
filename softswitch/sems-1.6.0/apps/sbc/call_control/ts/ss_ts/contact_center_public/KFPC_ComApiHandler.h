#ifndef KFPC_ComApiHandler_h__
#define KFPC_ComApiHandler_h__
#include "kfpc_api.h"
#include "kfpc_api_handle.h"
#include "kfpc_msg.h"


class KFPC_ComApiHandler :
	public KFPC_API_Handler
{

private:
	//KFPC_ConfigFile*	m_ConfigFile;
	char	m_AuthPassWord[KFPC_MAX_PASSWD_LEN];

	typedef void (KFPC_ComApiHandler::*MessageProcFun)(KFPC_MSG_HEADER* pMsg);
	MessageProcFun m_MsgProcFunMap[KFPC_MAX_MSG_ID_API];
private:

	void DoAPI_REMOTE_APP_ONLINE(KFPC_MSG_HEADER* pMsg);	
	void DoAPI_REMOTE_APP_OFFLINE(KFPC_MSG_HEADER* pMsg);					
	void DoAPI_LOCAL_CONNECTED(KFPC_MSG_HEADER* pMsg);						
	void DoAPI_REMOTE_CONNECTED(KFPC_MSG_HEADER* pMsg);					
	void DoAPI_APP_DISCONNECT(KFPC_MSG_HEADER* pMsg);						
	void DoAPI_LOCAL_REDUNDANCE_STATUS_CHANGE(KFPC_MSG_HEADER* pMsg);		
	void DoAPI_REMOTE_APP_REDUNDANCE_STATUS_CHANGE(KFPC_MSG_HEADER* pMsg);	
	void DoAPI_TEST_MSG(KFPC_MSG_HEADER* pMsg);							
	void DoAPI_APPID_CONFLICT(KFPC_MSG_HEADER* pMsg);	

protected:


	void AutoConnectTServer( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg);

	void AutoConnectCTI( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg);

	void AutoConnectCCS( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg);

	void IVRAutoConnectCCS( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg );
	
	void AutoConnectTTS( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg);

	void AutoConnectVOICE( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg);

	void AutoConnectFAX( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg);

	void AutoConnectRoute( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg );

	void AutoConnectLicense( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg );

	void AutoConnectBill( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg );

	void AutoConnectSMS( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg );

	void AutoConnectFaxConvert( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg );

	void CtrlAutoConnectCCS( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg );

	void NodeCCSConnectCCS(KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg);

	void AutoConnectSipServer( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg);
	void AutoConnectNotifyServer( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg);
	
public:
	static KFPC_ComApiHandler* GetInstance()
	{
		static KFPC_ComApiHandler _Instance;
		return &_Instance;
	}
	void AutoConnect( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg );
	virtual void RecvMsg(KFPC_MSG_HEADER* pMsg);
	virtual int SendMsg(KFPC_MSG_HEADER* pMsg);
	KFPC_ComApiHandler(void);
	virtual ~KFPC_ComApiHandler(void);

	virtual void OnEVT_API_REMOTE_APP_ONLINE(KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg);;					
	virtual void OnEVT_API_REMOTE_APP_OFFLINE(KFPC_EVT_API_REMOTE_APP_OFFLINE* pMsg) {};					
	virtual void OnEVT_API_LOCAL_CONNECTED(KFPC_EVT_API_LOCAL_CONNECTED* pMsg){};						
	virtual void OnEVT_API_REMOTE_CONNECTED(KFPC_EVT_API_REMOTE_CONNECTED* pMsg){};					
	virtual void OnEVT_API_APP_DISCONNECT(KFPC_EVT_API_APP_DISCONNECT* pMsg){};						
	virtual void OnEVT_LOCAL_REDUNDANCE_STATUS_CHANGE(KFPC_EVT_LOCAL_REDUNDANCE_STATUS_CHANGE* pMsg){};		
	virtual void OnEVT_API_REMOTE_APP_REDUNDANCE_STATUS_CHANGE(KFPC_EVT_API_REMOTE_APP_REDUNDANCE_STATUS_CHANGE* pMsg){};	
	virtual void OnREQ_API_TEST_MSG(KFPC_REQ_API_TEST_MSG* pMsg){};		
	virtual void OnRSP_API_TEST_MSG(KFPC_RSP_API_TEST_MSG* pMsg){};		
	virtual void OnEVT_APPID_CONFLICTED(KFPC_EVT_APPID_CONFLICTED* pMsg){};						

	const char* GetAuthPassWord() { return m_AuthPassWord; }
	void SetAuthPassWord(char* val) { strncpy(m_AuthPassWord,val,KFPC_MAX_PASSWD_LEN); }

	void PBXAutoConnectCCS( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg );
	void FaxFlowAutoConnectCCS( KFPC_EVT_API_REMOTE_APP_ONLINE* pMsg );
	
	void ConnectRemoteLicenseSer(const char* RemoteIP,unsigned int RemotePort);

};

#endif // KFPC_ComApiHandler_h__
