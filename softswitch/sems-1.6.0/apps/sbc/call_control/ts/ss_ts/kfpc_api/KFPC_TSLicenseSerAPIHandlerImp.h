#pragma once
#include "kfpc_LicenseSerapihandler.h"
//#include "KFPC_LicenseSerDef.h"
#include "kfpc_licenseser_api.h"
//#include "KFPC_LicenseSerConfigFile.h"

class KFPC_TSLicenseSerAPIHandlerImp :
	public KFPC_LicenseSerAPIHandler
{
private:
	

public:
	KFPC_TSLicenseSerAPIHandlerImp(void);
	~KFPC_TSLicenseSerAPIHandlerImp(void);

	static KFPC_TSLicenseSerAPIHandlerImp* GetInstance()
	{
		static KFPC_TSLicenseSerAPIHandlerImp LicenseSerAPIHandlerImpInstance;
		return &LicenseSerAPIHandlerImpInstance;
	}

	void OnRSP_LIC_TSERVERLIC(KFPC_LIC_RSP_TSERVERLIC* pMsg);
	void OnRSP_LIC_CCSLIC(KFPC_LIC_RSP_CCSLIC* pMsg);
};

#define  KFPCTSLicenseSerAPIHandlerImpInstance	KFPC_TSLicenseSerAPIHandlerImp::GetInstance()