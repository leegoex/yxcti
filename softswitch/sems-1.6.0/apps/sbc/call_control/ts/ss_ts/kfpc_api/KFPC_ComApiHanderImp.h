#pragma once
#include "kfpc_comapihandler.h"
class KFPC_ComApiHanderImp :
	public KFPC_ComApiHandler
{
private:
					
	virtual void OnEVT_API_REMOTE_CONNECTED(KFPC_EVT_API_REMOTE_CONNECTED* pMsg);		
	virtual void OnEVT_API_LOCAL_CONNECTED(KFPC_EVT_API_LOCAL_CONNECTED* pMsg);	
	virtual void OnEVT_API_APP_DISCONNECT(KFPC_EVT_API_APP_DISCONNECT* pMsg);						
	virtual void OnEVT_LOCAL_REDUNDANCE_STATUS_CHANGE(KFPC_EVT_LOCAL_REDUNDANCE_STATUS_CHANGE* pMsg);
	virtual void OnEVT_API_REMOTE_APP_OFFLINE(KFPC_EVT_API_REMOTE_APP_OFFLINE* pMsg);

	void ExeFaxRelatedCmd(KFPC_EVT_API_APP_DISCONNECT* pMsg);
	
public:

	static KFPC_ComApiHanderImp* GetInstance()
	{
		static KFPC_ComApiHanderImp _Instance;
		return &_Instance;
	}

	KFPC_ComApiHanderImp(void);
	~KFPC_ComApiHanderImp(void);

	void CTIServerConnected(KFPC_EVT_API_REMOTE_CONNECTED* pMsg);
	void RouteServerConnected(KFPC_EVT_API_REMOTE_CONNECTED* pMsg);
	void SipServerConnected( KFPC_EVT_API_LOCAL_CONNECTED* pMsg);
	void ConnectFaxServerSuccesful( KFPC_EVT_API_LOCAL_CONNECTED* pMsg );
	void ConnectVoiceServerSuccesful( KFPC_EVT_API_LOCAL_CONNECTED* pMsg );
	void ConnectTTSServerSuccesful( KFPC_EVT_API_LOCAL_CONNECTED* pMsg );
	void ConnectLicServerSuccesful( KFPC_EVT_API_LOCAL_CONNECTED* pMsg );
};
#define KFPC_ComApiHanderImpInstance	KFPC_ComApiHanderImp::GetInstance()
