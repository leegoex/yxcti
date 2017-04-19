#include "KFC_VoiceIDMgr.h"
#include "kfpc_logex.h"
#include "KFPC_ContactCenterPublicDef.h"

KFC_VoiceIDMgr::KFC_VoiceIDMgr(void)
{
}


KFC_VoiceIDMgr::~KFC_VoiceIDMgr(void)
{
}

unsigned int KFC_VoiceIDMgr::ASCII2VocID( char ascii )
{
	switch(ascii)
	{
	case '0':	return 91;
	case '1':	return 1;
	case '2':	return 2;
	case '3':	return 3;
	case '4':	return 4;
	case '5':	return 5;
	case '6':	return 6;
	case '7':	return 7;
	case '8':	return 8;
	case '9':	return 9;
	case 'A':	return 101;
	case 'B':	return 102;
	case 'C':	return 103;
	case 'D':	return 104;
	case 'E':	return 105;
	case 'F':	return 106;
	case 'G':	return 107;
	case 'H':	return 108;
	case 'I':	return 109;
	case 'J':	return 110;
	case 'K':	return 111;
	case 'L':	return 112;
	case 'M':	return 113;
	case 'N':	return 114;
	case 'O':	return 115;
	case 'P':	return 116;
	case 'Q':	return 117;
	case 'R':	return 118;
	case 'S':	return 119;
	case 'T':	return 120;
	case 'U':	return 121;
	case 'V':	return 122;
	case 'W':	return 123;
	case 'X':	return 124;
	case 'Y':	return 125;
	case 'Z':	return 126;
	default: return 0;
	}
}


KFPC_CommonVoice* KFC_VoiceIDMgr::AddVDN( unsigned int ID )
{
	KFPC_CommonVoice	CommonVoice;
	CommonVoice.SetVDN(ID);

	KFPC_VoiceVDNMapInsertResult_t	Ret = m_VoiceVDNMap.insert(KFPC_VoiceVDNMapPair_t(ID,CommonVoice));

	if(!Ret.second)
	{
		WARNING_LOG(0,"VDNID:%u exist,VoiceVDNMap size:%u",ID,m_VoiceVDNMap.size());
	}
	else
	{
		INFO_LOG(0,"VDNID:%u,VoiceVDNMap size:%u",ID,m_VoiceVDNMap.size());
	}

	return &(Ret.first->second);
}

void KFC_VoiceIDMgr::DelVDN( unsigned int ID )
{
	int Ret = m_VoiceVDNMap.erase(ID);

	INFO_LOG(0,"VNDID:%u,Ret:%d",ID,Ret);
}

KFPC_CommonVoice* KFC_VoiceIDMgr::FindVDN( unsigned int ID )
{
	KFPC_VoiceVDNMapIter_t	Iter = m_VoiceVDNMap.find(ID);

	if(Iter != m_VoiceVDNMap.end())
	{
		return &Iter->second;
	}
	else
	{
		return NULL;
	}
}

void KFC_VoiceIDMgr::LoadALLVDN( CDataBaseAccess* pDataBaseAccess )
{
	CRecordList RecordList;
	
	string		QueryVDNSQL = "SELECT "
		" VDN_ID "
		" FROM TBL_VDN_BASE";

	bool Ret = pDataBaseAccess->QueryData(QueryVDNSQL.c_str()
		,&RecordList
		,false);


	if(Ret)
	{
		while(!RecordList.GetEof())
		{
			unsigned int VDNID = RecordList.GetFieldAsLongint("VDN_ID");

			AddVDN(VDNID);

			RecordList.MoveNext();
		}

		KFPC_VoiceVDNMapIter_t	BeginIter = m_VoiceVDNMap.begin();
		//KFPC_VDNMapIter_t	EndIter = m_VDNMap.end();

		for(;BeginIter != m_VoiceVDNMap.end();BeginIter++)
		{
			BeginIter->second.LoadDB(pDataBaseAccess);
		}
	}
	else
	{
		WARNING_LOG(0,"Query SQL[%s] fail.",QueryVDNSQL.c_str());
	}
}

const char* KFC_VoiceIDMgr::VocID2FileName( unsigned int VDNID, unsigned int VocID, unsigned int Lang )
{
	const char* pRet = NULL;

	KFPC_CommonVoice* pVDNCommonVoice = FindVDN(VDNID);

	if(pVDNCommonVoice != NULL)
	{
		pRet = pVDNCommonVoice->GetVoiceFileByID(VocID,Lang);
	}

	if(pRet == NULL)
	{
		KFPC_CommonVoice* pSysCommonVoice = FindVDN(0);

		if(pSysCommonVoice != NULL)
		{
			return pSysCommonVoice->GetVoiceFileByID(VocID,Lang) ;
		}
	}

	return pRet;
}

bool KFC_VoiceIDMgr::PlayWorkNOLogin( const char * WorkNO, unsigned int Lang, unsigned int VDNID, string& PlayContent )
{
	// 工号的数字语音ID
	char PlayWorkNo[KFPC_MAX_PLAY_CONTENT];
	unsigned int j = 0;

	j += snprintf(&PlayWorkNo[j],KFPC_MAX_PLAY_CONTENT-j,"|FileName:%s",VocID2FileName(VDNID,127,Lang));

	for (unsigned int i = 0;i < strlen(WorkNO);i++)
	{
		j += snprintf(&PlayWorkNo[j],KFPC_MAX_PLAY_CONTENT-j,"|FileName:%s",ASCII2VoiceFile(WorkNO[i],Lang,VDNID));
	}
	PlayContent = PlayWorkNo;
	return true;
}

bool KFC_VoiceIDMgr::PlayWorkNOCall( const char * WorkNO, unsigned int Lang, unsigned int VDNID, string& PlayContent )
{
	// 工号的数字语音ID
	char PlayWorkNo[KFPC_MAX_PLAY_CONTENT];
	unsigned int j = 0;

	j += snprintf(&PlayWorkNo[j],KFPC_MAX_PLAY_CONTENT-j,"|FileName:%s",VocID2FileName(VDNID,127,Lang));

	for (unsigned int i = 0;i < strlen(WorkNO);i++)
	{
		j += snprintf(&PlayWorkNo[j],KFPC_MAX_PLAY_CONTENT-j,"|FileName:%s",ASCII2VoiceFile(WorkNO[i],Lang,VDNID));
	}

	j += snprintf(&PlayWorkNo[j],KFPC_MAX_PLAY_CONTENT-j,"|FileName:%s",VocID2FileName(VDNID,128,Lang));

	PlayContent = PlayWorkNo;
	return true;
}

const char* KFC_VoiceIDMgr::ASCII2VoiceFile( char ascii,unsigned int Lang,unsigned int VDNID )
{
	unsigned int VocID = ASCII2VocID(ascii);

	return VocID2FileName(VDNID, VocID, Lang);
}

bool KFC_VoiceIDMgr::PlayVDNStatus( KFPC_VDN_STATUS VDNStatus, unsigned int Lang, unsigned int VDNID, string& PlayContent )
{
	// 工号的数字语音ID
	char PlayWorkNo[KFPC_MAX_PLAY_CONTENT];
	unsigned int j = 0;

	j += snprintf(&PlayWorkNo[j],KFPC_MAX_PLAY_CONTENT-j,"|FileName:%s",VocID2FileName(VDNID,129,Lang));

	PlayContent = PlayWorkNo;
	return true;
}

bool KFC_VoiceIDMgr::PlayExtNum( const char * ExtNum, unsigned int Lang, unsigned int VDNID, string& PlayContent )
{
	// 工号的数字语音ID
	char PlayExtNum[KFPC_MAX_PLAY_CONTENT];
	unsigned int j = 0;

	j += snprintf(&PlayExtNum[j],KFPC_MAX_PLAY_CONTENT-j,"|FileName:%s",VocID2FileName(VDNID,130,Lang));

	for (unsigned int i = 0;i < strlen(ExtNum);i++)
	{
		j += snprintf(&PlayExtNum[j],KFPC_MAX_PLAY_CONTENT-j,"|FileName:%s",ASCII2VoiceFile(ExtNum[i],Lang,VDNID));
	}
	PlayContent = PlayExtNum;
	return true;
}

bool KFC_VoiceIDMgr::ExtNumDoesNotOpen( const char * ExtNum, unsigned int Lang, unsigned int VDNID, string& PlayContent )
{
	char PlayExtNum[KFPC_MAX_PLAY_CONTENT];
	unsigned int j = 0;

	j += snprintf(&PlayExtNum[j],KFPC_MAX_PLAY_CONTENT-j,"|FileName:%s",VocID2FileName(VDNID,131,Lang));

	PlayContent = PlayExtNum;
	return true;	
}