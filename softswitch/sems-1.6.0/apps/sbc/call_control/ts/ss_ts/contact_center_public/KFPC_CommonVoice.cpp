#include "KFPC_CommonVoice.h"
#include "kfpc_logex.h"
//#include "KFPC_CCSConfigFile.h"
KFPC_CommonVoice::KFPC_CommonVoice(void):
m_VDNID(0)
{
}


KFPC_CommonVoice::~KFPC_CommonVoice(void)
{
}

void KFPC_CommonVoice::LoadDB( CDataBaseAccess* pDataBaseAccess )
{
	m_MultiLangVOCMap.clear();

	CRecordList RecordList;

	string		QuerySQL = "SELECT "
		"VOC_ID,"
		"LANG1_VOICE_FILE,"
		"LANG2_VOICE_FILE,"
		"LANG3_VOICE_FILE,"
		"LANG4_VOICE_FILE"
		" FROM TBL_BASE_COMMONVOICE WHERE VDN_ID =";

	char StrVNDID[128]="";

	sprintf(StrVNDID,"%u",m_VDNID);

	QuerySQL += StrVNDID;

	bool Ret = pDataBaseAccess->QueryData(QuerySQL.c_str()
		,&RecordList,
		false);

	if(Ret)
	{
		while(!RecordList.GetEof())
		{		

			string LANG1_VOICE_FILE;
			string LANG2_VOICE_FILE;
			string LANG3_VOICE_FILE;
			string LANG4_VOICE_FILE;

			RecordList.GetFieldAsString("LANG1_VOICE_FILE",LANG1_VOICE_FILE);
			RecordList.GetFieldAsString("LANG2_VOICE_FILE",LANG2_VOICE_FILE);
			RecordList.GetFieldAsString("LANG3_VOICE_FILE",LANG3_VOICE_FILE);
			RecordList.GetFieldAsString("LANG4_VOICE_FILE",LANG4_VOICE_FILE);

			AddVOC(RecordList.GetFieldAsLongint("VOC_ID"),
				LANG1_VOICE_FILE.c_str(),
				LANG2_VOICE_FILE.c_str(),
				LANG3_VOICE_FILE.c_str(),
				LANG4_VOICE_FILE.c_str());
			RecordList.MoveNext();
		}


	}

}

void KFPC_CommonVoice::AddVOC( unsigned int VOCID,const char* pFileName1,const char* pFileName2,const char* pFileName3,const char* pFileName4 )
{
	KFPC_VOCLanguage	VOCLanguage;
	KFPC_MultiLangVOCMapInsertResult_t	Ret = m_MultiLangVOCMap.insert(KFPC_MultiLangVOCMapPair_t(VOCID,VOCLanguage));

	
	Ret.first->second.m_LANG1_VOICE_FILE = pFileName1;
	Ret.first->second.m_LANG2_VOICE_FILE = pFileName2;
	Ret.first->second.m_LANG3_VOICE_FILE = pFileName3;
	Ret.first->second.m_LANG4_VOICE_FILE = pFileName4;

	INFO_LOG(0,"VDN_ID:%u,VOCID:%u,LANG1:%s,LANG2:%s,LANG3:%s,LANG4:%s MultiLangVOCMap size:%u",
		m_VDNID,
		VOCID,
		Ret.first->second.m_LANG1_VOICE_FILE.c_str(),
		Ret.first->second.m_LANG2_VOICE_FILE.c_str(),
		Ret.first->second.m_LANG3_VOICE_FILE.c_str(),
		Ret.first->second.m_LANG4_VOICE_FILE.c_str(),
		m_MultiLangVOCMap.size());
}

const char* KFPC_CommonVoice::GetVoiceFileByID( unsigned int ID,unsigned int Lang )
{
	KFPC_MultiLangVOCMapIter_t Iter = m_MultiLangVOCMap.find(ID);

	if(Iter != m_MultiLangVOCMap.end())
	{
		return Iter->second.GetVoiceFile(Lang);
	}
	else
	{
		return NULL;
	}
}

const char* KFPC_VOCLanguage::GetVoiceFile( unsigned int Lang )
{
	switch(Lang)
	{
	case 1:	return m_LANG1_VOICE_FILE.c_str();
	case 2:	return m_LANG2_VOICE_FILE.c_str();
	case 3:	return m_LANG3_VOICE_FILE.c_str();
	case 4:	return m_LANG4_VOICE_FILE.c_str();
	default:return m_LANG1_VOICE_FILE.c_str();
	}
}
