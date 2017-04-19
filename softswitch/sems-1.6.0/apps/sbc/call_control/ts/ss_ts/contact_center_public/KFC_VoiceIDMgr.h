#pragma once
#include "KFPC_CommonVoice.h"
#include <unordered_map>
#include "KFPC_ContactCenterPublicDef.h"

using namespace	std;

typedef unordered_map <unsigned int, KFPC_CommonVoice>		KFPC_VoiceVDNMap_t;
typedef KFPC_VoiceVDNMap_t:: iterator						KFPC_VoiceVDNMapIter_t;
typedef pair<unsigned int, KFPC_CommonVoice>				KFPC_VoiceVDNMapPair_t;
typedef pair< KFPC_VoiceVDNMap_t:: iterator, bool >			KFPC_VoiceVDNMapInsertResult_t;


class KFC_VoiceIDMgr
{
private:
	KFPC_VoiceVDNMap_t	m_VoiceVDNMap;
public:
	KFC_VoiceIDMgr(void);
	~KFC_VoiceIDMgr(void);
	unsigned int ASCII2VocID( char ascii );
	const char* VocID2FileName( unsigned int VDNID, unsigned int VocID, unsigned int Lang );

	bool PlayWorkNOLogin( const char * WorkNO, unsigned int Lang, unsigned int VDNID, string& PlayContent );

	bool PlayWorkNOCall( const char * WorkNO, unsigned int Lang, unsigned int VDNID, string& PlayContent );

	bool PlayVDNStatus( KFPC_VDN_STATUS VDNStatus, unsigned int Lang, unsigned int VDNID, string& PlayContent );

	const char* ASCII2VoiceFile( char ascii,unsigned int Lang,unsigned int VDNID);

	bool PlayExtNum( const char * ExtNum, unsigned int Lang, unsigned int VDNID, string& PlayContent );

	bool ExtNumDoesNotOpen(const char * ExtNum, unsigned int Lang, unsigned int VDNID, string& PlayContent);

	static KFC_VoiceIDMgr* GetInstance()
	{
		static KFC_VoiceIDMgr _inStance;
		return &_inStance;
	}

	KFPC_CommonVoice*	AddVDN(unsigned int ID);
	void		DelVDN(unsigned int ID);
	KFPC_CommonVoice*	FindVDN(unsigned int ID);

	void LoadALLVDN(CDataBaseAccess* pDataBaseAccess);
	
};
#define  KFC_VoiceIDMgrInstance KFC_VoiceIDMgr::GetInstance()
