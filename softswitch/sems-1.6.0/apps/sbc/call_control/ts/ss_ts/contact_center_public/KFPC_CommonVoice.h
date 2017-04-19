#pragma once
#include<string>
using namespace std;
#include "DataBaseAccess.h"
#include <unordered_map>



class KFPC_VOCLanguage
{

public:
	const char* GetVoiceFile(unsigned int Lang);
	string m_LANG1_VOICE_FILE;
	string m_LANG2_VOICE_FILE;
	string m_LANG3_VOICE_FILE;
	string m_LANG4_VOICE_FILE;
};

typedef unordered_map <unsigned int, KFPC_VOCLanguage>		KFPC_MultiLangVOCMap_t;
typedef KFPC_MultiLangVOCMap_t:: iterator					KFPC_MultiLangVOCMapIter_t;
typedef pair<unsigned int, KFPC_VOCLanguage>				KFPC_MultiLangVOCMapPair_t;
typedef pair< KFPC_MultiLangVOCMap_t:: iterator, bool >		KFPC_MultiLangVOCMapInsertResult_t;


class KFPC_CommonVoice
{
private:
	KFPC_MultiLangVOCMap_t	m_MultiLangVOCMap;
	unsigned int			m_VDNID;

public:
	unsigned int GetVDN() { return m_VDNID; }
	void SetVDN(unsigned int val) { m_VDNID = val; }

	KFPC_CommonVoice(void);
	~KFPC_CommonVoice(void);
	void AddVOC(unsigned int VOCID,const char* pFileName1,const char* pFileName2,const char* pFileName3,const char* pFileName4);
	void LoadDB(CDataBaseAccess* pDataBaseAccess);
	const char* GetVoiceFileByID(unsigned int ID,unsigned int Lang);
};

