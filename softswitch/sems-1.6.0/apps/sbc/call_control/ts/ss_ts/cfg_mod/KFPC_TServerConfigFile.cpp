#include "KFPC_TServerConfigFile.h"
#include "xpath_static.h"
#include "kfpc_api.h"
#include "KFPC_EH_ID2Str.h"
#include "KFPC_StringUtils.h"

#include "kfpc_linuxwinnet.h"

#ifdef LINUX
#include <arpa/inet.h>
#endif


SS_TServerConfigFile::SS_TServerConfigFile(void):
m_CheckCallIDInterval(1800),
m_CheckCallIDLiveTime(14400),
m_EchoCancel(true)
//m_CallMaxTime(7200)
{
	m_GetChannelSignalFlag = false;

}


SS_TServerConfigFile::~SS_TServerConfigFile(void)
{
}

unsigned int SS_TServerConfigFile::GeteHangComIp( char* Ip )
{
	if(m_ConfigFileLoadFlag)
	{
		if(NULL != Ip)
		{
			TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_EHANGCOM);
			if(pNode == NULL)
			{
				WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_EHANGCOM,GetFileName());
				return -1;
			}

			TiXmlElement *pElement = pNode->ToElement();
			if(pElement == NULL)
			{
				WARNING_LOG(0,"Not found effective element in node[%s].",NODE_EHANGCOM);
				return -1;
			}

			const char *pEHangComIP = pElement->Attribute(ATTR_IP);
			if(pEHangComIP == NULL)
			{
				WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_IP,NODE_EHANGCOM);
				return -1;
			}

			strncpy(Ip,pEHangComIP,KFPC_MAX_IP_LEN);
			return 0;
		}
		else
		{
			WARNING_LOG(0,"Ip is invalid parameter.");
			return -1;
		}
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}

unsigned int SS_TServerConfigFile::GeteHangComPort( unsigned int &Port )
{
	if(m_ConfigFileLoadFlag)
	{
		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_EHANGCOM);
		if(pNode == NULL)
		{
			WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_EHANGCOM,GetFileName());
			return -1;
		}

		TiXmlElement *pElement = pNode->ToElement();
		if(pElement == NULL)
		{
			WARNING_LOG(0,"Not found effective element in node [%s].",NODE_EHANGCOM);
			return -1;
		}

		const char *pEHangComPort = pElement->Attribute(ATTR_PORT);
		if(pEHangComPort == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_PORT,NODE_EHANGCOM);
			return -1;
		}

		Port = atoi(pEHangComPort);
		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}

unsigned int SS_TServerConfigFile::GeteHangComKeepAlive( unsigned int &KeepAlive )
{
	if(m_ConfigFileLoadFlag)
	{
		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_EHANGCOM);
		if(pNode == NULL)
		{
			WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_EHANGCOM,GetFileName());
			return -1;
		}

		TiXmlElement *pElement = pNode->ToElement();
		if(pElement == NULL)
		{
			WARNING_LOG(0,"Not found effective element in node[%s].",NODE_EHANGCOM);
			return -1;
		}

		const char *pEHangKeepAlive = pElement->Attribute(ATTR_EHANGCOMKEEPALIVE);
		if(pEHangKeepAlive == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_EHANGCOMKEEPALIVE,NODE_EHANGCOM);
			return -1;
		}

		KeepAlive = atoi(pEHangKeepAlive);
		return 0;
	}
	else
	{
		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
		return -1;
	}
}


void SS_TServerConfigFile::ConfigFileLoadSuccess()
{
	GetTserverCfg(OP_TRUNKGROUP);

	GetTserverCfg(OP_ANALOGTONE);

	GetTserverCfg(OP_ANALOGCHANNELNUM);

	GetTserverCfg(OP_DIGITTRUNKNUM);

	GetTserverCfg(OP_SIPREGISTER);

	GetTserverCfg(OP_CHANNELSIGNAL);

	GetTserverCfg(OP_FXSINFO);

	GetTserverCfg(OP_FXOINFO);

	GetTserverCfg(OP_DBACCESSINFO);

	GetTserverCfg(OP_NODECONFIG);

	GetTserverCfg(OP_AGC);

	GetTserverCfg(OP_CONFCFG);

	GetTserverCfg(OP_MSML);

	GetTserverCfg(OP_CheckinvalidCallID);

	GetMonitorCfg();

	GetRecordCfg();

	GetEchoCancelCfg();
	
}

KFPC_TrunkGroupMgr *SS_TServerConfigFile::GetTrunkGroupMgr()
{
	return &m_TrunkGroupMgr;
}


KFPC_DBAccessInfo *SS_TServerConfigFile::GetDBAccessInfoSet()
{
	return &m_DBAccessInfo;
}


unsigned int SS_TServerConfigFile::GetTserverCfg(ConfigObjectType_t NodeType)
{
	TiXmlElement *pRootElement = m_ConfigDocument.RootElement();
	if(pRootElement == NULL)
	{
		WARNING_LOG(0, "Not found root node in config file[%s].",GetFileName());
		return -1;
	}

	TiXmlNode *pChildNode = NULL;
	while(pChildNode = pRootElement->IterateChildren(pChildNode))
	{
		if(pChildNode == NULL)
		{
			continue;
		}

		TiXmlElement *pChildElement = pChildNode->ToElement();
		if(pChildElement != NULL && pChildElement->Value() != NULL)
		{

			switch(NodeType)
			{
			case OP_TRUNKGROUP:
				  {
					  if(strcmp(pChildElement->Value(),NODE_TRUNKGROUPMGR) == 0)
					  {
						  return GetTrunkGroup(pChildElement);
					  }

					  break;
				  }

			//case OP_SIPREGISTER:
			//	  {
			//		  if(strcmp(pChildElement->Value(),NODE_SIPREGISTERLIST) == 0)
			//		  {
			//			  return GetSipRegister(pChildElement);
			//		  }

			//		  break;
			//	  }
			case OP_DBACCESSINFO:
				{
					if(strcmp(pChildElement->Value(),NODE_DATABASE) == 0)
					{
						return GetDBAccessInfo(pChildElement);
					}
				}
				break;
			//case OP_NODECONFIG:
			//	{
			//		if(strcmp(pChildElement->Value(),NODE_SWNODECONFIG) == 0)
			//		{
			//			return GetNodeCfg(pChildElement);
			//		}
			//	}
			//	break;
			//case OP_AGC:
			//	{
			//		if(strcmp(pChildElement->Value(),NODE_AGC) == 0)
			//		{
			//			return GetAgc(pChildElement);
			//		}
			//	}
			//	break;
			//case OP_CONFCFG:
			//	{
			//		if(strcmp(pChildElement->Value(),NODE_Conference) == 0)
			//		{
			//			return GetConfCfg(pChildElement);
			//		}
			//	}
			//	break;
			case OP_MSML:
				{
					if(strcmp(pChildElement->Value(),NODE_MSML) == 0)
					{
						return GetMSMLCfg(pChildElement);
					}

				}
				break;
			case OP_CheckinvalidCallID:
				{
					if(strcmp(pChildElement->Value(),NODE_CheckinvalidCallID) == 0)
					{
						return GetCheckinvalidCallIDCfg(pChildElement);
					}
				}
			
			default:
				{
					
					break;
				}
			}

		}
	}

	

	return -1;
}

int SS_TServerConfigFile::GetTrunkGroup(TiXmlElement *pElement)
{
	TiXmlNode *pChildNode = NULL;
	m_TrunkGroupMgr.PreLoadCfg();

	while(pChildNode = pElement->IterateChildren(pChildNode))
	{
		if(pChildNode == NULL)
		{
			continue;
		}

		TiXmlElement *pChildElement = pChildNode->ToElement();
		if(pChildElement != NULL && pChildElement->Value() != NULL)
		{
			if(strcmp(pChildElement->Value(),NODE_TRUNKGROUP) == 0)
			{
				const char *pName			= pChildElement->Attribute(ATTR_TRUNKGROUPNAME);
				const char *pDescription	= pChildElement->Attribute(ATTR_DESCRIPTION);
				const char *pAutoAnswer		= pChildElement->Attribute(ATTR_AUTOANSWER);
				const char *pAddPrefix		= pChildElement->Attribute(ATTR_AddPrefix);
				const char *pStripPrefix	= pChildElement->Attribute(ATTR_StripPrefix);
				//const char *pSipServer		= pChildElement->Attribute(ATTR_SIPSERVER);
				const char *pLocalRtp		= pChildElement->Attribute(ATTR_LOCALRTP);

				const char *pCallerNOA		= pChildElement->Attribute(ATTR_CallerNOA);	
				const char *pCalledNOA		= pChildElement->Attribute(ATTR_CalledNOA);
				const char *pSupport183		= pChildElement->Attribute(ATTR_Support183);
				

				if(pName != NULL)
				{	
					KFPC_TrunkGroup *pNewTrunkGroup = NULL;

					pNewTrunkGroup = m_TrunkGroupMgr.GetTrunkGroupByName(pName);

					if(NULL != pNewTrunkGroup)
					{
						pNewTrunkGroup->Clear();
						pNewTrunkGroup->SetOld(false);
					}
					else
					{
						pNewTrunkGroup = m_TrunkGroupMgr.AddTrunkGroup(pName);
						if(pNewTrunkGroup == NULL)
						{
							WARNING_LOG(0, "Failed to add trunk group[name:%s].",pName);
							continue;
						}
					}

					if(pDescription != NULL)
					{
						char Description[KFPC_TRUNKGROUP_DESC_LEN] = {0};
						UNICODE2GB2312((char *)pDescription,strlen(pDescription),Description,strlen(pDescription));
						pNewTrunkGroup->SetDescription(Description);
					}
					else
					{
						WARNING_LOG(0,"Not found attribute[%s] in Node[%s].",ATTR_TRUNKGROUPNAME,NODE_TRUNKGROUP);
					}

					if(pAutoAnswer != NULL)
					{
						pNewTrunkGroup->SetAutoAnswer((atoi(pAutoAnswer) == 1)?true:false);
					}
					else
					{
						WARNING_LOG(0,"Not found attribute[%s] in Node[%s].",ATTR_AUTOANSWER,NODE_TRUNKGROUP);
					}

					//if(pSipServer != NULL)
					//{
					//	pNewTrunkGroup->SetSIPServer(atoi(pSipServer));
					//}
					//else
					//{
					//	WARNING_LOG(0,"Not found attribute[%s] in Node[%s].",ATTR_AUTOANSWER,NODE_TRUNKGROUP);
					//}
					
					if(pLocalRtp != NULL)
					{
						pNewTrunkGroup->SetLocalRtp(pLocalRtp);
					}
					else
					{
						WARNING_LOG(0,"Not found attribute[%s] in Node[%s].",ATTR_LOCALRTP,NODE_TRUNKGROUP);
					}

					if(pAddPrefix != NULL)
					{
						char AddPrefix[KFPC_MAX_NUMBER_SIZE] = {0};
						UNICODE2GB2312((char *)pAddPrefix,strlen(pAddPrefix),AddPrefix,KFPC_MAX_NUMBER_SIZE);
						pNewTrunkGroup->SetAddPrefix(AddPrefix);
					}
					else
					{
						WARNING_LOG(0,"Not found attribute[%s] in Node[%s].",ATTR_AddPrefix,NODE_TRUNKGROUP);
					}

					if(pStripPrefix != NULL)
					{
						char StripPrefix[KFPC_MAX_NUMBER_SIZE] = {0};
						UNICODE2GB2312((char *)pStripPrefix,strlen(pStripPrefix),StripPrefix,KFPC_MAX_NUMBER_SIZE);
						pNewTrunkGroup->SetStripPrefix(StripPrefix);
					}
					else
					{
						WARNING_LOG(0,"Not found attribute[%s] in Node[%s].",ATTR_StripPrefix,NODE_TRUNKGROUP);
					}

					if(pCallerNOA != NULL)
					{
						pNewTrunkGroup->SetCallerNOA(atoi(pCallerNOA));
					}
					else
					{
						WARNING_LOG(0,"Not found attribute[%s] in Node[%s].",ATTR_CallerNOA,NODE_TRUNKGROUP);

					}

					if(pCalledNOA != NULL)
					{
						pNewTrunkGroup->SetCalledNOA(atoi(pCalledNOA));
					}
					else
					{
						WARNING_LOG(0,"Not found attribute[%s] in Node[%s].",ATTR_CalledNOA,NODE_TRUNKGROUP);
					}


					if(pSupport183 != NULL &&
						(strcmp(pSupport183,NODE_ENABLE) == 0))
					{
						pNewTrunkGroup->SetSupport183(true);
					}

					TiXmlNode *pSubNode = NULL;
					while(pSubNode = pChildElement->IterateChildren(pSubNode))
					{
						if(pSubNode == NULL)
						{
							continue;
						}

						TiXmlElement *pSubElement = pSubNode->ToElement();
						if(pSubElement != NULL && pSubElement->Value() != NULL)
						{
							if(strcmp(pSubElement->Value(),NODE_CHANNELBLOCK) == 0)
							{
								GetChannelBlock(pSubElement,pNewTrunkGroup);
							}
							else if(strcmp(pSubElement->Value(),NODE_SIPCALLOUT) == 0)
							{
								GetSipCallOut(pSubElement,pNewTrunkGroup);
							}
							else if(strcmp(pSubElement->Value(),NODE_SIPCALLOFFER) == 0)
							{
								GetSipCallOffer(pSubElement,pNewTrunkGroup);
							}
							else if(strcmp(pSubElement->Value(),NODE_AUDIOCODE) == 0)
							{
								GetAudioCode(pSubElement,pNewTrunkGroup);
							}
							else if(strcmp(pSubElement->Value(),NODE_CallOutMode) == 0)
							{
								GetCallOutMode(pSubElement,pNewTrunkGroup);
							}
						}
					}

					pNewTrunkGroup->log();
				}
				else
				{
					ERROR_LOG(0,"Not found attribute[%s]in node[%s].\n",ATTR_TRUNKGROUPNAME,NODE_TRUNKGROUP);
				}
			}
		}
	}

	m_TrunkGroupMgr.EndLoadCfg();

	return 0;
}

unsigned int SS_TServerConfigFile::GetChannelBlock(TiXmlElement *pElement,KFPC_TrunkGroup *pTrunkGroup)
{
	const char *pBeginSpan = pElement->Attribute(ATTR_BEGINSPAN);
	const char *pBeginChannel = pElement->Attribute(ATTR_BEGINCHANNEL);
	const char *pEndSpan = pElement->Attribute(ATTR_ENDSPAN);
	const char *pEndChannel = pElement->Attribute(ATTR_ENDCHANNEL);
	const char *pIdle = pElement->Attribute(ATTR_IDLETYPE);
	const char *pFlag = pElement->Attribute(ATTR_FLAG);

	if(pFlag == NULL)
	{
		WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_FLAG,NODE_CHANNELBLOCK);
		return -1;
	}

	if(strcmp(pFlag,NODE_ENABLE) == 0)
	{
		unsigned int BeginSpan;
		unsigned int BeginChannel;
		unsigned int EndSpan;
		unsigned int EndChannel;
		KFPC_QueryIdleChType QueryIdleType;

		if(pBeginSpan != NULL)
		{
			BeginSpan = atoi(pBeginSpan);
		}
		else
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_BEGINSPAN,NODE_CHANNELBLOCK);
		}

		if(pBeginChannel != NULL)
		{
			BeginChannel = atoi(pBeginChannel);
		}
		else
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_BEGINCHANNEL,NODE_CHANNELBLOCK);
		}

		if(pEndSpan != NULL)
		{
			EndSpan = atoi(pEndSpan);
		}
		else
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_ENDSPAN,NODE_CHANNELBLOCK);
		}

		if(pEndChannel != NULL)
		{
			EndChannel = atoi(pEndChannel);
		}
		else
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_ENDCHANNEL,NODE_CHANNELBLOCK);
		}

		if(pIdle != NULL)
		{
			//unsigned int nType = atoi(pIdle);
			QueryIdleType = GetQueryIdleChType(pIdle);
		}
		else
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_IDLETYPE,NODE_CHANNELBLOCK);
		}

		pTrunkGroup->AddRouteBlock(BeginSpan,BeginChannel,EndSpan,EndChannel,QueryIdleType);
	}

	return 0;
}

KFPC_QueryIdleChType SS_TServerConfigFile::GetQueryIdleChType(const char* pIdleType)
{
		if(strcmp(pIdleType,"Z") == 0)
		{
			return KFPC_QueryIdleChType_Z;
		}

		if(strcmp(pIdleType,"ODD") == 0)
		{
			return KFPC_QueryIdleChType_Odd;
		}

		if(strcmp(pIdleType,"EVEN") == 0)
		{
			return KFPC_QueryIdleChType_Even;
		}

		//if(strcmp(pIdleType,"W") == 0)
		{
			return KFPC_QueryIdleChType_W;
		}


}

unsigned int SS_TServerConfigFile::GetSipCallOut(TiXmlElement *pElement,KFPC_TrunkGroup *pTrunkGroup)
{
	const char *pIP = pElement->Attribute(ATTR_IP);
	const char *pPort = pElement->Attribute(ATTR_PORT);
	const char *pUserName = pElement->Attribute(ATTR_SIPCALLUSERNAME);
	const char *pPassWord = pElement->Attribute(ATTR_SIPCALLPASSWORD);
	const char *pFlag = pElement->Attribute(ATTR_FLAG);
	const char *pNodeID = pElement->Attribute(ATTR_NODEID);
	const char *pProxy = pElement->Attribute(ATTR_PROXY);

	if(pFlag == NULL)
	{
		WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_FLAG,NODE_SIPCALLOUT);
		return -1;
	}

	if(strcmp(pFlag,NODE_ENABLE) == 0)
	{
		if(pIP == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_IP,NODE_SIPCALLOUT);
			return -1;
		}

		if(pPort == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_PORT,NODE_SIPCALLOUT);
			return -1;
		}

		if(pUserName == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_SIPCALLUSERNAME,NODE_SIPCALLOUT);
			return -1;
		}

		if(pPassWord == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_SIPCALLPASSWORD,NODE_SIPCALLOUT);
			return -1;
		}

		int NodeID = -1;
		if(pNodeID == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_NODEID,NODE_SIPCALLOUT);
			//return -1;
		}
		else
		{
			NodeID = atoi(pNodeID);
		}

		if(pProxy == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_PROXY,NODE_SIPCALLOUT);
			//return -1;
		}

		
		pTrunkGroup->AddCallOutAddrBlock(pIP,atoi(pPort),pUserName,pPassWord,NodeID,pProxy);
	}

	return 0;
}

unsigned int SS_TServerConfigFile::GetSipCallOffer(TiXmlElement *pElement,KFPC_TrunkGroup *pTrunkGroup)
{
	const char *pIP = pElement->Attribute(ATTR_IP);
	const char *pMask = pElement->Attribute(ATTR_SIPCALLOFFERMASK);
	const char *pFlag = pElement->Attribute(ATTR_FLAG);

	if(pFlag == NULL)
	{
		WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_FLAG,NODE_SIPCALLOFFER);
		return -1;
	}

	if(strcmp(pFlag,NODE_ENABLE) == 0)
	{
		if(pIP != NULL && pMask != NULL)
		{
			pTrunkGroup->AddFromAddrBlock((char *)pIP,(char *)pMask,0,"","");
		}
		else if(pIP == NULL)
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_IP,NODE_SIPCALLOFFER);
		}
		else
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_SIPCALLOFFERMASK,NODE_SIPCALLOFFER);
		}
	}

	return 0;
}

unsigned int SS_TServerConfigFile::GetAudioCode(TiXmlElement *pElement,KFPC_TrunkGroup *pTrunkGroup)
{
	const char *pCodes = pElement->Attribute(ATTR_CODES);
	const char *pFlag = pElement->Attribute(ATTR_FLAG);

	if(pFlag == NULL)
	{
		WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_FLAG,NODE_AUDIOCODE);
		return -1;
	}

	if(strcmp(pFlag,NODE_ENABLE) == 0)
	{
		if(pCodes != NULL)
		{

			int nLen = strlen(pCodes) + 1;

			/// µ«Ô¸¹»ÓÃ

			char pAudioCodeList[2048] = { 0 };
			strncpy(pAudioCodeList, pCodes, 2048); 

			int last = 0;
			int next = 0;

			#define AUDIO_CODE_SEP	(",\t ")

			char * token = strtok(pAudioCodeList, AUDIO_CODE_SEP);

			while (token != NULL)
			{
				// While there are tokens in "string"

				INFO_LOG(0,"Found Audio Code:%s", token);

				Trim(token,' ');
				unsigned short CodeID = StrToAudioCodeID(token);
				if(CodeID >=0 )
				{		
					pTrunkGroup->AddAudioCode(CodeID);
				}
				else
				{
					WARNING_LOG(0,"Code:%s can not match to codeID",token);
				}

				// Get next token: 
				token = strtok( NULL, AUDIO_CODE_SEP); 
			}			
		}
		else
		{
			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_CODES,NODE_AUDIOCODE);
		}
	}

	return 0;
}
//
//unsigned int KFPC_TServerConfigFile::GetAnalogTone(TiXmlElement *pElement)
//{
//	TiXmlNode *pChildNode = NULL;
//	m_AnalogToneMgr.Clear();
//
//	while(pChildNode = pElement->IterateChildren(pChildNode))
//	{
//		if(pChildNode == NULL)
//		{
//			continue;
//		}
//
//		TiXmlElement *pChildElement = pChildNode->ToElement();
//		if(pChildElement != NULL && pChildElement->Value() != NULL)
//		{
//			if(strcmp(pChildElement->Value(),NODE_TONE) == 0)
//			{
//				const char *pID = pChildElement->Attribute(ATTR_TONEID);
//				const char *pDescription = pChildElement->Attribute(ATTR_DESCRIPTION);
//				const char *pFq1 = pChildElement->Attribute(ATTR_TONEFQ1);
//				const char *pFq2 = pChildElement->Attribute(ATTR_TONEFQ2);
//				const char *pOn = pChildElement->Attribute(ATTR_TONEON);
//				const char *pOndv = pChildElement->Attribute(ATTR_TONEONDV);
//				const char *pOff = pChildElement->Attribute(ATTR_TONEOFF);
//				const char *pOffdv = pChildElement->Attribute(ATTR_TONEOFFDV);
//				const char *pFlag = pChildElement->Attribute(ATTR_FLAG);
//
//				if(pFlag == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_FLAG,NODE_TONE);
//					continue;
//				}
//
//				if(pID == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_TONEID,NODE_TONE);
//					continue;
//				}
//
//				if(pDescription == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_DESCRIPTION,NODE_TONE);
//					continue;
//				}
//
//				if(pFq1 == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_TONEFQ1,NODE_TONE);
//					continue;
//				}
//
//				if(pFq2 == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_TONEFQ2,NODE_TONE);
//					continue;
//				}
//
//				if(pOn == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_TONEON,NODE_TONE);
//					continue;
//				}
//
//				if(pOndv == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_TONEONDV,NODE_TONE);
//					continue;
//				}
//
//				if(pOff == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_TONEOFF,NODE_TONE);
//					continue;
//				}
//
//				if(pOffdv == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_TONEOFFDV,NODE_TONE);
//					continue;
//				}
//
//				if(strcmp(pFlag,NODE_ENABLE) == 0)
//				{
//					char Description[KFPC_TRUNKGROUP_DESC_LEN] = {0};
//					UNICODE2GB2312((char *)pDescription,strlen(pDescription),Description,strlen(pDescription));
//
//					m_AnalogToneMgr.AddAnalogTone(atoi(pID),(char *)pDescription,atoi(pFq1),atoi(pFq2),atoi(pOn),atoi(pOndv),
//												  atoi(pOff),atoi(pOffdv));
//				}
//			}
//		}
//	}
//
//	return 0;
//}
//
//unsigned int KFPC_TServerConfigFile::GetAnalogChannelNum(TiXmlElement *pElement)
//{
//	TiXmlNode *pChildNode = NULL;
//	m_AnalogChannelNumTable.Clear();
//
//	while(pChildNode = pElement->IterateChildren(pChildNode))
//	{
//		if(pChildNode == NULL)
//		{
//			continue;
//		}
//
//		TiXmlElement *pChildElement = pChildNode->ToElement();
//		if(pChildElement != NULL && pChildElement->Value() != NULL)
//		{
//			if(strcmp(pChildElement->Value(),NODE_AG) == 0)
//			{
//				const char *pChannel = pChildElement->Attribute(ATTR_ANALOGCHANNEL);
//				const char *pNum = pChildElement->Attribute(ATTR_ANALOGCHANNELNUM);
//				const char *pFlag = pChildElement->Attribute(ATTR_FLAG);
//				const char *pQuickDial = pChildElement->Attribute(ATTR_ANALOGCHANNELQUICKDIAL);
//				const char *pNodeID = pChildElement->Attribute(ATTR_NODEID);
//
//				if(pFlag == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_FLAG,NODE_AG);
//					continue;
//				}
//
//				if(pChannel == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_ANALOGCHANNEL,NODE_AG);
//					continue;
//				}
//
//				if(pNum == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_ANALOGCHANNELNUM,NODE_AG);
//				}
//
//				if(pQuickDial == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_ANALOGCHANNELQUICKDIAL,NODE_AG);
//				}
//
//				unsigned char	NodeID = 0;
//				if(pNodeID == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_NODEID,NODE_AG);
//				}
//				else
//				{
//					NodeID = atoi(pNodeID);
//				}
//
//				if(strcmp(pFlag,NODE_ENABLE) == 0)
//				{
//					m_AnalogChannelNumTable.AddItem(atoi(pChannel),NodeID,pNum,pQuickDial);
//				}
//			}
//		}
//	}
//
//	return 0;
//}
//
//unsigned int KFPC_TServerConfigFile::GetDigitTrunkNum(TiXmlElement *pElement)
//{
//	TiXmlNode *pChildNode = NULL;
//	m_DigitTrunkNumTable.Clear();
//
//	while(pChildNode = pElement->IterateChildren(pChildNode))
//	{
//		if(pChildNode == NULL)
//		{
//			continue;
//		}
//
//		TiXmlElement *pChildElement = pChildNode->ToElement();
//		if(pChildElement != NULL && pChildElement->Value() != NULL)
//		{
//			if(strcmp(pChildElement->Value(),NODE_TRUNK) == 0)
//			{
//				const char *pSpan = pChildElement->Attribute(ATTR_DIGITSPAN);
//				const char *pNum = pChildElement->Attribute(ATTR_DIGITTRUNKNUM);
//				const char *pFlag = pChildElement->Attribute(ATTR_FLAG);
//
//				if(pFlag == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_FLAG,NODE_TRUNK);
//					continue;
//				}
//
//				if(pSpan == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_DIGITSPAN,NODE_TRUNK);
//					continue;
//				}
//
//				if(pNum == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_DIGITTRUNKNUM,NODE_TRUNK);
//					continue;
//				}
//
//				if(strcmp(pFlag,NODE_ENABLE) == 0)
//				{
//					m_DigitTrunkNumTable.AddItem(atoi(pSpan),pNum);
//				}
//			}
//		}
//	}
//
//	return 0;
//}
//
//unsigned int KFPC_TServerConfigFile::GetSipRegister(TiXmlElement *pElement)
//{
//
//	m_SipRegisterMgr.Clear();
//
//	const char *pReregisterInterval = pElement->Attribute(ATTR_REREGISTERINTERVAL);
//	if(pReregisterInterval != NULL)
//	{
//		m_SipRegisterMgr.SetReregisterInterval(atoi(pReregisterInterval));
//	}
//	else
//	{
//		WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_REREGISTERINTERVAL,NODE_SIPREGISTERLIST);
//	}
//
//	const char *pFailRegisterInterval = pElement->Attribute(ATTR_FAILREGISTERINTERVAL);
//	if(pFailRegisterInterval != NULL)
//	{
//		m_SipRegisterMgr.SetFailRegisterInterval(atoi(pFailRegisterInterval));
//	}
//	else
//	{
//		WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_FAILREGISTERINTERVAL,NODE_SIPREGISTERLIST);
//	}
//
//	TiXmlNode *pChildNode = NULL;
//	while(pChildNode = pElement->IterateChildren(pChildNode))
//	{
//		if(pChildNode == NULL)
//		{
//			continue;
//		}
//
//		TiXmlElement *pChildElement = pChildNode->ToElement();
//		if(pChildElement != NULL && pChildElement->Value() != NULL)
//		{
//			if(strcmp(pChildElement->Value(),NODE_SIPACCOUNT) == 0)
//			{
//				const char *pSipAccountID = pChildElement->Attribute(ATTR_ID);
//				const char *pNodeID = pChildElement->Attribute(ATTR_NODEID);
//				const char *pBRD = pChildElement->Attribute(ATTR_BRD);
//				const char *pDomain = pChildElement->Attribute(ATTR_DOMAIN);
//				const char *pPort = pChildElement->Attribute(ATTR_PORT);
//				const char *pUserName = pChildElement->Attribute(ATTR_USERNAME);
//				const char *pPassWord = pChildElement->Attribute(ATTR_PASSWORD);
//				const char *pExpires = pChildElement->Attribute(ATTR_EXPIRES);
//				const char *pFlag = pChildElement->Attribute(ATTR_FLAG);
//
//				if(pFlag == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_FLAG,NODE_SIPACCOUNT);
//					continue;
//				}
//
//				if(pSipAccountID == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_ID,NODE_SIPACCOUNT);
//					continue;
//				}
//
//				if(pNodeID == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_NODEID,NODE_SIPACCOUNT);
//				}
//
//				if(pBRD == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_BRD,NODE_SIPACCOUNT);
//				}
//
//				if(pDomain == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_DOMAIN,NODE_SIPACCOUNT);
//				}
//
//				if(pPort == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_PORT,NODE_SIPACCOUNT);
//				}
//
//				if(pUserName == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_USERNAME,NODE_SIPACCOUNT);
//				}
//
//				if(pPassWord == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_PASSWORD,NODE_SIPACCOUNT);
//				}
//
//				if(pExpires == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_EXPIRES,NODE_SIPACCOUNT);
//				}
//
//				if(strcmp(pFlag,NODE_ENABLE) == 0)
//				{
//					m_SipRegisterMgr.AddSipRegister(atoi(pSipAccountID),atoi(pNodeID),atoi(pBRD),(char *)pDomain,atoi(pPort),
//													(char*)pUserName,(char *)pPassWord,atoi(pExpires));
//				}
//			}
//		}
//	}
//
//	m_SipRegisterMgr.SipRegister();
//	return 0;
//}
//
//KFPC_SignalType KFPC_TServerConfigFile::Translate(char * pType)
//{
//	for (int i = 0; i < SIGNALTYPECOUNT; i++)
//	{
//		if(strcmp(pType,SignalType_List[i].SignalTypeName) == 0)
//		{
//			return SignalType_List[i].SignalType;
//		}
//	}
//
//	return KFPC_SignalType_ClearChannel;
//}
//
//unsigned int KFPC_TServerConfigFile::GetChannelSignal(TiXmlElement *pElement)
//{
//	TiXmlNode *pChildNode = NULL;
//
//	m_ChannelSignalMgr.Clear();
//
//	while(pChildNode = pElement->IterateChildren(pChildNode))
//	{
//		if(pChildNode == NULL)
//		{
//			continue;
//		}
//
//		TiXmlElement *pChildElement = pChildNode->ToElement();
//		if(pChildElement != NULL && pChildElement->Value() != NULL)
//		{
//			if(strcmp(pChildElement->Value(),NODE_SIGNAL) == 0)
//			{
//				const char *pSignalType = pChildElement->Attribute(ATTR_SIGNALTYPE);
//				const char *pBeginSpan = pChildElement->Attribute(ATTR_BEGINSPAN);
//				const char *pBeginChannel = pChildElement->Attribute(ATTR_BEGINCHANNEL);
//				const char *pEndSpan = pChildElement->Attribute(ATTR_ENDSPAN);
//				const char *pEndChannel = pChildElement->Attribute(ATTR_ENDCHANNEL);
//				const char *pFlag = pChildElement->Attribute(ATTR_FLAG);
//				
//				if(pFlag == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_FLAG,NODE_SIGNAL);
//					continue;
//				}
//
//				if(pSignalType == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_SIGNALTYPE,NODE_SIGNAL);
//					continue;
//				}
//
//				if(pBeginSpan == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_BEGINSPAN,NODE_SIGNAL);
//				}
//
//				if(pBeginChannel == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_BEGINCHANNEL,NODE_SIGNAL);
//				}
//
//				if(pEndSpan == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_ENDSPAN,NODE_SIGNAL);
//				}
//
//				if(pEndChannel == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_ENDCHANNEL,NODE_SIGNAL);
//				}
//
//				if(strcmp(pFlag,NODE_ENABLE) == 0)
//				{
//					m_ChannelSignalMgr.AddChannelSignal(Translate((char *)pSignalType),atoi(pBeginSpan),atoi(pBeginChannel),
//						                                atoi(pEndSpan),atoi(pEndChannel));
//				}
//			}
//		}
//	}
//
//	m_GetChannelSignalFlag = true;
//
//	return 0;
//}
//
//unsigned int KFPC_TServerConfigFile::GetSignalType(unsigned int ChID,KFPC_SignalType& SignalType)
//{
//	if(!m_GetChannelSignalFlag)
//	{
//		GetTserverCfg(OP_CHANNELSIGNAL);
//	}
//
//	return m_ChannelSignalMgr.GetChannelSignalType(ChID,SignalType);
//}
//
//int KFPC_TServerConfigFile::GetFxs(TiXmlElement *pElement)
//{
//	TiXmlNode *pChildNode = NULL;
//
//	m_FxsInfo.Clear();
//
//	while(pChildNode = pElement->IterateChildren(pChildNode))
//	{
//		if(pChildNode == NULL)
//		{
//			continue;
//		}
//
//		TiXmlElement *pChildElement = pChildNode->ToElement();
//		if(pChildElement != NULL && pChildElement->Value() != NULL)
//		{
//			if(strcmp(pChildElement->Value(),NODE_COLLECTCALLED) == 0)
//			{
//				const char *pMode = pChildElement->Attribute(ATTR_MODE);
//				const char *pMaxDigits = pChildElement->Attribute(ATTR_MAXDIGITS);
//				const char *pTermChar = pChildElement->Attribute(ATTR_TERMCHAR);
//				const char *pFirstDigitTimer = pChildElement->Attribute(ATTR_FIRSTDIGITTIMER);
//				const char *pInterDigitTimer = pChildElement->Attribute(ATTR_INTERDIGITTIMER);
//				const char *pCompletionTimer = pChildElement->Attribute(ATTR_COMPLETIONTIMER);
//
//				if(pMode != NULL)
//				{
//					m_FxsInfo.SetMode(atoi(pMode));
//				}
//				else
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_MODE,NODE_COLLECTCALLED);
//				}
//
//				if(pMaxDigits != NULL)
//				{
//					m_FxsInfo.SetMaxDigits(atoi(pMaxDigits));
//				}
//				else
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_MAXDIGITS,NODE_COLLECTCALLED);
//				}
//
//				if(pTermChar != NULL)
//				{
//					m_FxsInfo.SetTermChar(pTermChar[0]);
//				}
//				else
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_TERMCHAR,NODE_COLLECTCALLED);
//				}
//
//				if(pFirstDigitTimer != NULL)
//				{
//					m_FxsInfo.SetFirstDigitTimer(atoi(pFirstDigitTimer));
//				}
//				else
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_FIRSTDIGITTIMER,NODE_COLLECTCALLED);
//				}
//
//				if(pInterDigitTimer != NULL)
//				{
//					m_FxsInfo.SetInterDigitTimer(atoi(pInterDigitTimer));
//				}
//				else
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_INTERDIGITTIMER,NODE_COLLECTCALLED);
//				}
//
//				if(pCompletionTimer != NULL)
//				{
//					m_FxsInfo.SetCompletionTimer(atoi(pCompletionTimer));
//				}
//				else
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_COMPLETIONTIMER,NODE_COLLECTCALLED);
//				}
//			}
//			else if(strcmp(pChildElement->Value(),NODE_CALLOUNT) == 0)
//			{
//				const char *pMaxRingTimes = pChildElement->Attribute(ATTR_MAXRINGTIMES);
//
//				if(pMaxRingTimes != NULL)
//				{
//					m_FxsInfo.SetMaxRingTimes(atoi(pMaxRingTimes));
//				}
//				else
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_MAXRINGTIMES,NODE_CALLOUNT);
//				}
//			}
//		}
//	}
//
//	return 0;
//}
//
//int KFPC_TServerConfigFile::GetFxo(TiXmlElement *pElement)
//{
//	TiXmlNode *pChildNode = NULL;
//	while(pChildNode = pElement->IterateChildren(pChildNode))
//	{
//		if(pChildNode == NULL)
//		{
//			continue;
//		}
//
//		TiXmlElement *pChildElement = pChildNode->ToElement();
//		if(pChildElement != NULL && pChildElement->Value() != NULL)
//		{
//			if(strcmp(pChildElement->Value(),NODE_GETCALLER) == 0)
//			{
//				const char *pCallOfferRingTimes = pChildElement->Attribute(ATTR_CALLOFFERRINGTIMES);
//
//				if(pCallOfferRingTimes != NULL)
//				{
//					m_FxoInfo.SetCallOfferRingTimes(atoi(pCallOfferRingTimes));
//				}
//				else
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_CALLOFFERRINGTIMES,NODE_GETCALLER);
//				}
//			}
//		}
//	}
//
//	return 0;
//}
//

//
//unsigned int KFPC_TServerConfigFile::GeteHangComSipPort( unsigned int& Port )
//{
//
//	if(m_ConfigFileLoadFlag)
//	{
//		TiXmlNode *pNode = TinyXPath::XNp_xpath_node(m_ConfigDocument.RootElement(), NODE_EHANGCOM);
//		if(pNode == NULL)
//		{
//			WARNING_LOG(0,"Not found node[%s] in config file[%s].",NODE_EHANGCOM,GetFileName());
//			return -1;
//		}
//
//		TiXmlElement *pElement = pNode->ToElement();
//		if(pElement == NULL)
//		{
//			WARNING_LOG(0,"Not found effective element in node[%s].",NODE_EHANGCOM);
//			return -1;
//		}
//
//		const char *pEHangSipPort = pElement->Attribute(ATTR_EHANGCOMSIPPORT);
//		if(pEHangSipPort == NULL)
//		{
//			WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_EHANGCOMSIPPORT,NODE_EHANGCOM);
//			return -1;
//		}
//
//		Port = atoi(pEHangSipPort);
//		return 0;
//	}
//	else
//	{
//		WARNING_LOG(0,"Didn't load config file[%s].",GetFileName());
//		return -1;
//	}
//
//}
//
//int KFPC_TServerConfigFile::GetNodeCfg(TiXmlElement *pElement)
//{
//	TiXmlNode *pChildNode = NULL;
//	//m_TrunkGroupMgr.PreLoadCfg();
//
//	while(pChildNode = pElement->IterateChildren(pChildNode))
//	{
//		if(pChildNode == NULL)
//		{
//			continue;
//		}
//
//		TiXmlElement *pChildElement = pChildNode->ToElement();
//		if(pChildElement != NULL && pChildElement->Value() != NULL)
//		{
//			if(strcmp(pChildElement->Value(),NODE_SWNODE) == 0)
//			{
//				const char *pID = pChildElement->Attribute(ATTR_ID);
//				const char *pMaxVoice = pChildElement->Attribute(ATTR_SWNODEMAXVOICE);
//				const char *pMaxVoip = pChildElement->Attribute(ATTR_SWNODEMAXVOIP);
//				const char *pMaxSIP = pChildElement->Attribute(ATTR_SWNODEMAXSIP);
//				const char *pMaxConf = pChildElement->Attribute(ATTR_SWNODEMAXCONFERENCE);
//				
//				if(pID != NULL)
//				{	
//					KFPC_NodeCfg *pNewSwNode = NULL;
//
//					pNewSwNode = m_NodeCfgMgr.AddNodeCfg(atoi(pID));
//					if(pNewSwNode == NULL)
//					{
//						WARNING_LOG(0, "Failed to add node cfg[ID:%s].",pID);
//						continue;
//					}
//					
//					pNewSwNode->Clear();
//
//					if(pMaxVoice != NULL)
//					{
//						pNewSwNode->SetMaxVoice(atoi(pMaxVoice));
//					}
//					else
//					{
//						WARNING_LOG(0,"Not found attribute[%s] in Node[%s].",ATTR_SWNODEMAXVOIP,ATTR_ID);
//					}
//
//					if(pMaxVoip != NULL)
//					{
//						pNewSwNode->SetMaxVoip(atoi(pMaxVoip));
//					}
//					else
//					{
//						WARNING_LOG(0,"Not found attribute[%s] in Node[%s].",ATTR_SWNODEMAXVOICE,ATTR_ID);
//					}
//
//					if(pMaxSIP != NULL)
//					{
//						pNewSwNode->SetMaxSip(atoi(pMaxSIP));
//					}
//					else
//					{
//						WARNING_LOG(0,"Not found attribute[%s] in Node[%s].",ATTR_SWNODEMAXSIP,ATTR_ID);
//					}
//
//					if(pMaxConf != NULL)
//					{
//						pNewSwNode->SetMaxConference(atoi(pMaxConf));
//					}
//					else
//					{
//						WARNING_LOG(0,"Not found attribute[%s] in Node[%s].",ATTR_SWNODEMAXCONFERENCE,ATTR_ID);
//					}
//
//					TiXmlNode *pSubNode = NULL;
//					while(pSubNode = pChildElement->IterateChildren(pSubNode))
//					{
//						if(pSubNode == NULL)
//						{
//							continue;
//						}
//
//						TiXmlElement *pSubElement = pSubNode->ToElement();
//						if(pSubElement != NULL && pSubElement->Value() != NULL)
//						{
//							if(strcmp(pSubElement->Value(),NODE_AG) == 0)
//							{
//								GetNodeCfgAG(pSubElement,pNewSwNode);
//							}
//							else if(strcmp(pSubElement->Value(),NODE_DTI) == 0)
//							{
//								GetNodeCfgDTI(pSubElement,pNewSwNode);
//							}
//							else if(strcmp(pSubElement->Value(),NODE_ModuleRes) == 0)
//							{
//								const char *pBRD = pSubElement->Attribute(ATTR_BRD);
//								const char *pMax = pSubElement->Attribute(ATTR_MAX);
//
//
//								pNewSwNode->SetModuleRes(atoi(pBRD),atoi(pMax));
//
//							}
//						}
//					}
//				}
//				else
//				{
//					ERROR_LOG(0,"Not found attribute[%s]in node[%s].\n",ATTR_ID,NODE_SWNODE);
//				}
//			}
//		}
//	}
//
//	return 0;
//}
//
//int KFPC_TServerConfigFile::GetNodeCfgAG(TiXmlElement *pElement,KFPC_NodeCfg *pNodeCfg)
//{
//	const char *pBeginChannel = pElement->Attribute(ATTR_BEGINCHANNEL);
//	const char *pEndChannel = pElement->Attribute(ATTR_ENDCHANNEL);
//
//	unsigned int BeginCh = 0;
//	unsigned int EndCh = 0;
//
//	if(pBeginChannel != NULL)
//	{
//		BeginCh = atoi(pBeginChannel);
//	}
//	else
//	{
//		WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_BEGINCHANNEL,NODE_AG);
//		return -1;
//	}
//
//	if(pEndChannel != NULL)
//	{
//		EndCh = atoi(pEndChannel);
//	}
//	else
//	{
//		WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_ENDCHANNEL,NODE_AG);
//		return -1;
//	}
//
//	for (unsigned int i = BeginCh; i <= EndCh; i++)
//	{
//		pNodeCfg->AddAgCh(i);
//	}
//
//	return 0;
//}
//
//int KFPC_TServerConfigFile::GetNodeCfgDTI(TiXmlElement *pElement,KFPC_NodeCfg *pNodeCfg)
//{
//	const char *pBeginSpan = pElement->Attribute(ATTR_BEGINSPAN);
//	const char *pEndSpan = pElement->Attribute(ATTR_ENDSPAN);
//
//	unsigned int BeginSpan = 0;
//	unsigned int EndSpan = 0;
//
//	if(pBeginSpan != NULL)
//	{
//		BeginSpan = atoi(pBeginSpan);
//	}
//	else
//	{
//		WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_BEGINSPAN,NODE_DTI);
//		return -1;
//	}
//
//	if(pEndSpan != NULL)
//	{
//		EndSpan = atoi(pEndSpan);
//	}
//	else
//	{
//		WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_ENDSPAN,NODE_DTI);
//		return -1;
//	}
//
//	for (unsigned int i = BeginSpan; i <= EndSpan; i++)
//	{
//		pNodeCfg->AddDTISpan(i);
//	}
//
//	return 0;
//}

SS_TServerConfigFile* SS_TServerConfigFile::GetInstance()
{
	//if(_Instance == NULL)
	//{
	//	smart_new(KFPC_TServerConfigFile(),_Instance)
	//		INFO_LOG(0,"new KFPC_TServerConfigFile")
	//}

	static SS_TServerConfigFile	 Instance;

	return &Instance;
}

unsigned int SS_TServerConfigFile::GetAgc( TiXmlElement *pElement )
{
	
	if(pElement != NULL)
	{
		if(strcmp(pElement->Value(),NODE_AGC) == 0)
		{

			const char *pValid = pElement->Attribute(ATTR_Valid);

			if(pValid != NULL)
			{
				m_Agc.SetValid(atoi(pValid));
			}
			else
			{
				WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_Valid,NODE_AGC);
			}

			const char *pActive = pElement->Attribute(ATTR_Active);

			if(pActive != NULL)
			{
				m_Agc.SetActive(atoi(pActive));
			}
			else
			{
				WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_Active,NODE_AGC);
			}

			const char *pGainSlop = pElement->Attribute(ATTR_GainSlop);

			if(pGainSlop != NULL)
			{
				m_Agc.SetGainSlop(atoi(pGainSlop));
			}
			else
			{
				WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_GainSlop,NODE_AGC);
			}

			const char *pRedirection = pElement->Attribute(ATTR_Redirection);

			if(pRedirection != NULL)
			{
				m_Agc.SetRedirection(atoi(pRedirection));
			}
			else
			{
				WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_Redirection,NODE_AGC);
			}

			const char *pTargetEnergy = pElement->Attribute(ATTR_TargetEnergy);

			if(pTargetEnergy != NULL)
			{
				m_Agc.SetTargetEnergy(atoi(pTargetEnergy));
			}
			else
			{
				WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_TargetEnergy,NODE_AGC);
			}

			m_Agc.Log();
		}
	}


	return 0;
}

unsigned int SS_TServerConfigFile::GetConfCfg( TiXmlElement *pElement )
{
	if(pElement != NULL)
	{
		if(strcmp(pElement->Value(),NODE_Conference) == 0)
		{

			const char *pValid = pElement->Attribute(ATTR_Valid);

			if(pValid != NULL)
			{
				m_ConfCfg.SetValid(atoi(pValid));
			}
			else
			{
				WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_Valid,NODE_Conference);
			}

			const char *pDirection = pElement->Attribute(ATTR_Direction);

			if(pDirection != NULL)
			{
				m_ConfCfg.SetDirection(atoi(pDirection));
			}
			else
			{
				WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_Direction,NODE_Conference);
			}

			const char *pVolume = pElement->Attribute(ATTR_Volume);

			if(pVolume != NULL)
			{
				m_ConfCfg.SetVolume(atoi(pVolume));
			}
			else
			{
				WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_Volume,NODE_Conference);
			}

			m_ConfCfg.Log();
		}
	}


	return 0;
}

unsigned int SS_TServerConfigFile::GetCallOutMode( TiXmlElement *pElement,KFPC_TrunkGroup *pTrunkGroup )
{
	const char *pValue = pElement->Attribute(ATTR_Value);


	if(pValue == NULL)
	{
		WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_Value,NODE_CallOutMode);
		return -1;
	}


	unsigned int Val = atoi(pValue);

	if(Val == 0)
	{
		pTrunkGroup->SetSipCallOutMode(CallOutMode_StandBy);
		INFO_LOG(0,"TrunkGroup:%s Sip Call Mode standby",pTrunkGroup->GetName());
	}
	else
	{
		pTrunkGroup->SetSipCallOutMode(CallOutMode_MultiCall);
		INFO_LOG(0,"TrunkGroup:%s Sip Call Mode multi call",pTrunkGroup->GetName());
	}
	
	return 0;
}

int SS_TServerConfigFile::GetMSMLCfg( TiXmlElement *pElement)
{
	if(pElement != NULL)
	{
		if(strcmp(pElement->Value(),NODE_MSML) == 0)
		{

			const char *pConferenceSize = pElement->Attribute(ATTR_ConferenceSize);

			if(pConferenceSize != NULL)
			{
				m_MSMLCfg.SetConfSize(atoi(pConferenceSize));
				INFO_LOG(0,"MSML Conference size:%u",m_MSMLCfg.GetConfSize());

			}
			else
			{
				WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_ConferenceSize,NODE_MSML);
			}
		}
	}


	return 0;
}

int SS_TServerConfigFile::GetCheckinvalidCallIDCfg( TiXmlElement *pElement )
{


	if(pElement != NULL)
	{
		if(strcmp(pElement->Value(),NODE_CheckinvalidCallID) == 0)
		{

			const char *pInterval = pElement->Attribute(ATTR_Interval);

			if(pInterval != NULL)
			{
				m_CheckCallIDInterval = atoi(pInterval);
				INFO_LOG(0,"CheckCallIDInterval:%u",m_CheckCallIDInterval);

			}
			else
			{
				WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_Interval,NODE_CheckinvalidCallID);
			}

			const char *pLiveTime = pElement->Attribute(ATTR_LiveTime);

			if(pLiveTime != NULL)
			{
				m_CheckCallIDLiveTime = atoi(pLiveTime);
				INFO_LOG(0,"CheckCallIDLiveTime:%u",m_CheckCallIDLiveTime);

			}
			else
			{
				WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_LiveTime,NODE_CheckinvalidCallID);
			}

			//const char *pCallMaxTime = pElement->Attribute(ATTR_CallMaxTime);

			//if(pCallMaxTime != NULL)
			//{
			//	m_CallMaxTime = atoi(pCallMaxTime);
			//	INFO_LOG(0,"CallMaxTime:%u",m_CallMaxTime);
			//}
			//else
			//{
			//	WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_CallMaxTime,NODE_CheckinvalidCallID);
			//}

		}
	}


	return 0;
}

int SS_TServerConfigFile::GetMonitorCfg(  )
{
	TiXmlElement *pRootElement = m_ConfigDocument.RootElement();
	if(pRootElement == NULL)
	{
		WARNING_LOG(0, "Not found root node in config file[%s].",GetFileName());
		return -1;
	}

	TiXmlNode *pChildNode = NULL;
	while(pChildNode = pRootElement->IterateChildren(pChildNode))
	{
		if(pChildNode == NULL)
		{
			continue;
		}

		TiXmlElement *pChildElement = pChildNode->ToElement();
		if(pChildElement != NULL && pChildElement->Value() != NULL)
		{

			if(strcmp(pChildElement->Value(),NODE_Monitor) == 0)
			{

				const char *pInterval = pChildElement->Attribute(ATTR_StatInterval);

				if(pInterval != NULL)
				{
					m_Monitor_Cfg.m_StatInterval = atoi(pInterval);
					INFO_LOG(0,"StatInterval:%u",m_Monitor_Cfg.m_StatInterval);

				}
				else
				{
					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_StatInterval,NODE_Monitor);
				}

			}
		}
	}


	return 0;
}

int SS_TServerConfigFile::GetRecordCfg()
{
	TiXmlElement *pRootElement = m_ConfigDocument.RootElement();
	if(pRootElement == NULL)
	{
		WARNING_LOG(0, "Not found root node in config file[%s].",GetFileName());
		return -1;
	}

	TiXmlNode *pChildNode = NULL;
	while(pChildNode = pRootElement->IterateChildren(pChildNode))
	{
		if(pChildNode == NULL)
		{
			continue;
		}

		TiXmlElement *pChildElement = pChildNode->ToElement();
		if(pChildElement != NULL && pChildElement->Value() != NULL)
		{

			if(strcmp(pChildElement->Value(),NODE_Record) == 0)
			{

				const char *pMode			= pChildElement->Attribute(ATTR_Mode);
				const char *pTransformMp3	= pChildElement->Attribute(ATTR_TransformMp3);
				const char *pRecordAGC		= pChildElement->Attribute(ATTR_RecordAGC);

				if(pMode != NULL)
				{
					if(strcmp(pMode,"Conf") == 0)
					{
						m_Record_Cfg.SetRecordMode(RM_CONF);
					}
					else if(strcmp(pMode,"Mix") == 0)
					{
						m_Record_Cfg.SetRecordMode(RM_Mix);
					}
					
					INFO_LOG(0,"Mode:%s",(m_Record_Cfg.GetRecordMode() == RM_CONF)?"Conf":"Mix");

				}
				else
				{
					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_Mode,NODE_Record);
				}

				if(pTransformMp3 != NULL)
				{
					if(strcmp(pTransformMp3,NODE_ENABLE) == 0)
					{
						m_Record_Cfg.SetTransformMp3(true);
					}
					else
					{
						m_Record_Cfg.SetTransformMp3(false);
					}

					INFO_LOG(0,"TransformMp3:%s",(m_Record_Cfg.GetTransformMp3())?NODE_ENABLE:"Disable");
				}
				else
				{
					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_TransformMp3,NODE_Record);
				}

				if(pRecordAGC != NULL)
				{
					m_Record_Cfg.SetRecordAGC(atoi(pRecordAGC));
					INFO_LOG(0,"RecordAGC:%d",m_Record_Cfg.GetRecordAGC());
				}
				else
				{
					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_RecordAGC,NODE_Record);
				}
			}
		}
	}


	return 0;
}
//
//int KFPC_TServerConfigFile::GetContactIPMap()
//{
//	TiXmlElement *pRootElement = m_ConfigDocument.RootElement();
//	if(pRootElement == NULL)
//	{
//		WARNING_LOG(0, "Not found root node in config file[%s].",GetFileName());
//		return -1;
//	}
//
//	TiXmlNode *pChildNode = NULL;
//	while(pChildNode = pRootElement->IterateChildren(pChildNode))
//	{
//		if(pChildNode == NULL)
//		{
//			continue;
//		}
//
//		TiXmlElement *pChildElement = pChildNode->ToElement();
//		if(pChildElement != NULL && pChildElement->Value() != NULL)
//		{
//			if(strcmp(pChildElement->Value(),NODE_ContactIPMap) == 0)
//			{
//				KFPC_ContactIPMapMgrInstance->Clear();
//
//				GetIPMap(pChildElement);
//			}
//		}
//	}
//	return 0;
//}
//
//unsigned int KFPC_TServerConfigFile::GetIPMap( TiXmlElement *pElement )
//{
//	TiXmlNode *pChildNode = NULL;
//	while(pChildNode = pElement->IterateChildren(pChildNode))
//	{
//		if(pChildNode == NULL)
//		{
//			continue;
//		}
//
//		TiXmlElement *pChildElement = pChildNode->ToElement();
//		if(pChildElement != NULL && pChildElement->Value() != NULL)
//		{
//			if(strcmp(pChildElement->Value(),NODE_IPMap) == 0)
//			{
//				const char *pLAN_IP = pChildElement->Attribute(ATTR_LAN_IP);
//				const char *pWAN_IP = pChildElement->Attribute(ATTR_WAN_IP);	
//				const char *pFlag = pChildElement->Attribute(ATTR_FLAG);
//
//				if(pFlag == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",ATTR_FLAG,NODE_IPMap);
//					continue;
//				}
//
//				if(pLAN_IP == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",pLAN_IP,NODE_IPMap);
//					continue;
//				}
//
//				if(pWAN_IP == NULL)
//				{
//					WARNING_LOG(0,"Not found attribute[%s] in node[%s].",pWAN_IP,NODE_IPMap);
//					continue;
//				}
//
//				if(strcmp(pFlag,NODE_ENABLE) == 0)
//				{
//					KFPC_ContactIPMapMgrInstance->AddIPMap(inet_addr(pLAN_IP),inet_addr(pWAN_IP));
//				}
//
//			}
//		}
//	}
//	return 0;
//}

int SS_TServerConfigFile::GetEchoCancelCfg()
{
	TiXmlElement *pRootElement = m_ConfigDocument.RootElement();
	if(pRootElement == NULL)
	{
		WARNING_LOG(0, "Not found root node in config file[%s].",GetFileName());
		return -1;
	}

	TiXmlNode *pChildNode = NULL;
	while(pChildNode = pRootElement->IterateChildren(pChildNode))
	{
		if(pChildNode == NULL)
		{
			continue;
		}

		TiXmlElement *pChildElement = pChildNode->ToElement();
		if(pChildElement != NULL && pChildElement->Value() != NULL)
		{

			if(strcmp(pChildElement->Value(),NODE_EchoCancel) == 0)
			{

				const char *pValid	= pChildElement->Attribute(ATTR_Valid);

				if(atoi(pValid) == 1)
				{
					SetEchoCancel(true);
				}
				else
				{
					SetEchoCancel(false);
				}

				INFO_LOG(0,"EchoCancel:%u",m_EchoCancel);
			}
		}
	}

	return 0;
}
