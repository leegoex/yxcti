#pragma once
#include "kfpc_api_handle.h"
#include "kfpc_licenseser_api.h"
#include <openssl/aes.h>

const unsigned char KFPC_AES_KEY[AES_BLOCK_SIZE] = {'K','F','P','C','@','-','-','-','2','0','1','2','0','8','1','3'};

class KFPC_LicenseSerAPIHandler :
	public KFPC_API_Handler
{
private:
	typedef void (KFPC_LicenseSerAPIHandler::*MessageProc)( KFPC_MSG_HEADER*);
	
	MessageProc m_MsgProcFunMap[KFPC_MAX_MSG_ID_LIC];
	
	virtual void RecvMsg(KFPC_MSG_HEADER* pMsg);
	
	void RecvLIC_TServerLIC( KFPC_MSG_HEADER* pMsg);
	void RecvLIC_CCSLIC( KFPC_MSG_HEADER* pMsg);
	void RecvLIC_FAXLIC( KFPC_MSG_HEADER* pMsg);
	void RecvLIC_BASELIC( KFPC_MSG_HEADER* pMsg);
	void RecvLIC_IPRLIC( KFPC_MSG_HEADER* pMsg);
	unsigned char	m_Key[AES_BLOCK_SIZE];
public:
	
	virtual int SendMsg(KFPC_MSG_HEADER* pMsg);


	virtual void OnREQ_LIC_TSERVERLIC(KFPC_LIC_REQ_TSERVERLIC* pMsg){}
	virtual void OnRSP_LIC_TSERVERLIC(KFPC_LIC_RSP_TSERVERLIC* pMsg){}

	virtual void OnREQ_LIC_CCSLIC(KFPC_LIC_REQ_CCSLIC* pMsg){}
	virtual void OnRSP_LIC_CCSLIC(KFPC_LIC_RSP_CCSLIC* pMsg){}

	virtual void OnREQ_LIC_FAXLIC(KFPC_LIC_REQ_FAXLIC* pMsg){}
	virtual void OnRSP_LIC_FAXLIC(KFPC_LIC_RSP_FAXLIC* pMsg){}

	virtual void OnREQ_LIC_BASELIC(KFPC_LIC_REQ_BASELIC* pMsg){}
	virtual void OnRSP_LIC_BASELIC(KFPC_LIC_RSP_BASELIC* pMsg){}
	
	virtual void OnREQ_LIC_IPRECLIC(KFPC_LIC_REQ_IPR* pMsg){}
	virtual void OnRSP_LIC_IPRECLIC(KFPC_LIC_RSP_IPR* pMsg){}

	unsigned int SendREQ_LIC_TSERVERLIC(unsigned int UserContext1,unsigned int UserContext2,unsigned int DestAppID,unsigned int AppType,const char* pSwtich);
	unsigned int SendRSP_LIC_TSERVERLIC(unsigned int UserContext1,unsigned int UserContext2,unsigned int DestAppID,KFPC_TSERVERLIC_INFO &TServerLic,unsigned int Result);

	void Encrypt(  void* Buf, unsigned int BufSize );
	void Decrypt( void* Buf, unsigned int BufSize );

	unsigned int SendREQ_LIC_CCSLIC(unsigned int UserContext1,unsigned int UserContext2,unsigned int DestAppID,unsigned int AppType);
	unsigned int SendRSP_LIC_CCSLIC(unsigned int UserContext1,unsigned int UserContext2,unsigned int DestAppID,KFPC_CCSLIC_INFO &CCSLic,unsigned int Result);

	unsigned int SendREQ_LIC_FAXLIC(unsigned int UserContext1,unsigned int UserContext2,unsigned int DestAppID,unsigned int AppType);
	unsigned int SendRSP_LIC_FAXLIC(unsigned int UserContext1,unsigned int UserContext2,unsigned int DestAppID,KFPC_FAXLIC_INFO &FAXLic,unsigned int Result);
	
	unsigned int SendREQ_LIC_BASELIC(unsigned int UserContext1,unsigned int UserContext2,unsigned int DestAppID,unsigned int AppType);
	unsigned int SendRSP_LIC_BASELIC(unsigned int UserContext1,unsigned int UserContext2,unsigned int DestAppID,KFPC_BASELIC_INFO &BaseLic,unsigned int Result);
	
	unsigned int SendREQ_LIC_IPRECLIC(unsigned int UserContext1,unsigned int UserContext2,unsigned int DestAppID,unsigned int AppType);
	unsigned int SendRSP_LIC_IPRECLIC(unsigned int UserContext1,unsigned int UserContext2,unsigned int DestAppID,KFPC_IPR_INFO &IpRecLic,unsigned int Result);



	KFPC_LicenseSerAPIHandler(void);
	virtual ~KFPC_LicenseSerAPIHandler(void);
};

