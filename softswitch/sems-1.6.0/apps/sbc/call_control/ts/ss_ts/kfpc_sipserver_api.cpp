#include "kfpc_sipserver_api.h"

#ifdef _MSC_VER
#include "apr_general.h"
#define snprintf _snprintf
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#endif


static KFPC_SdpPayloadAttr_t g_KFPC_AudioPayloadAttrMap[AudioCodec_MaxNum]=
{
	{8,		1,	8000,	"G711A",		"1","",0},
	{0,		1,	8000,	"G711U",		"1","",0 },
	{18,	1,	8000,	"G729",			"1","",0 },
	{96,	1,	8000,	"iLBC",			"1","",0 },
	{97,	2,	48000,	"opus",			"1","useinbandfec=1",0 }
};

static KFPC_SdpPayloadAttr_t g_KFPC_VideoPayloadAttrMap[VideoCode_MaxNum]=
{
	{96,	1,	90000,	"H264",			"1","profile-level-id=42801F",0 },
	{97,	1,	90000,	"H265",			"1","profile-level-id=42801F",0 },
	{98,	1,	90000,	"VP8",			"1","",0 },
	{99,	1,	90000,	"VP9",			"1","",0 }

};


//const unsigned char MaxNumPayLoad = sizeof(g_KFPC_SdpPayloadAttrMap)/sizeof(KFPC_SdpPayloadAttr_t);

static KFPC_SendRecvModeList_t	KFPC_SendRecvModeList[]=
{
	{KFPC_SendRecvMode_Null,	"null"},
	{KFPC_SendRecvMode_Recvonly,"recvonly"},
	{KFPC_SendRecvMode_Sendrecv,"sendrecv"},
	{KFPC_SendRecvMode_Sendonly,"sendonly"},
	{KFPC_SendRecvMode_Inactive,"inactive"}
};

static KFPC_TransportProtoList_t	KFPC_TransportProtoList[] =
{

	{KFPC_TP_Null,				"Null" },
	{ KFPC_TP_RTPAVP,			"RTPAVP" },
	{ KFPC_TP_RTPAVPF,			"RTPAVPF" },
	{ KFPC_TP_UDP,				"UDP" },
	{ KFPC_TP_RTPSAVP,			"RTPSAVP" },
	{ KFPC_TP_UDPTL,			"UDPTL" },
	{ KFPC_TP_RTPSAVPF,			"RTPSAVPF" },
	{ KFPC_TP_UDPTLSRTPSAVP,	"UDPTLSRTPSAVP" },
	{ KFPC_TP_UDPTLSRTPSAVPF,	"UDPTLSRTPSAVPF" }

};

static KFPC_MediaTypeList_t	KFPC_MediaTypeList[]=
{
	{KFPC_MediaType_Null,""},
	{KFPC_MediaType_audio,"audio"},
	{KFPC_MediaType_video,"video"},	
	{KFPC_MediaType_application,"application"},
	{ KFPC_MediaType_text,"text" },	
	{KFPC_MediaType_message,"message"},
	{KFPC_MediaType_image,"image"}
};


const char* IntIP2Str( unsigned int addr, char* buf, unsigned short bufLen )
{
	char *cp, *retStr;
	unsigned int byte;
	int n;
	addr = htonl(addr);
	cp = &buf[bufLen];
	*--cp = '\0';

	n = 4;
	do {
		byte = addr & 0xff;
		*--cp = byte % 10 + '0';
		byte /= 10;
		if (byte > 0) {
			*--cp = byte % 10 + '0';
			byte /= 10;
			if (byte > 0)
				*--cp = byte + '0';
		}
		*--cp = '.';
		addr >>= 8;
	} while (--n > 0);

	/* Convert the string to lowercase */
	retStr = (char*)(cp+1);

	return(retStr);
}

KFPC_MediaType_t MediaStr2MediaType( const char* str,int strlen )
{
	int i = 0;


	for(i=0;i<sizeof(KFPC_MediaTypeList);i++)
	{
		if(strncasecmp(KFPC_MediaTypeList[i].MediaName,str,strlen) == 0)
		{
			return KFPC_MediaTypeList[i].MediaType;
		}
	}
	return KFPC_MediaType_Null;
}

const char* MediaType2Str( KFPC_MediaType_t MediaType )
{
	switch(MediaType)
	{
	case KFPC_MediaType_audio:
	case KFPC_MediaType_video:
	case KFPC_MediaType_text:
	case KFPC_MediaType_application:
	case KFPC_MediaType_image:
	case KFPC_MediaType_message:
		{
			return KFPC_MediaTypeList[MediaType].MediaName;
		}
		break;
	default: return "unknow media type";
	}
}

const char* TransportProto2Str( KFPC_TransportProto_t TransportProtoType )
{
	switch(TransportProtoType)
	{
	case KFPC_TP_Null:
	case KFPC_TP_RTPAVP:
	case KFPC_TP_RTPAVPF:
	case KFPC_TP_UDP:
	case KFPC_TP_RTPSAVP:
	case KFPC_TP_UDPTL:
	case KFPC_TP_RTPSAVPF:
	case KFPC_TP_UDPTLSRTPSAVP:
	case KFPC_TP_UDPTLSRTPSAVPF:
		{
			return KFPC_TransportProtoList[TransportProtoType].TransportProtoName;
		}
		break;
	default:return "unknow transport";
	}
}

SendRecvMode_t SendRecvModeStr2SendRecvMode( const char* str ,int strlen )
{
	int i = 0;


	for(i=0;i<sizeof(KFPC_SendRecvModeList);i++)
	{
		if(strncasecmp(KFPC_SendRecvModeList[i].SendRecvModeName,str,strlen) == 0)
		{
			return KFPC_SendRecvModeList[i].SendRecvMode;
		}
	}
	return KFPC_SendRecvMode_Sendrecv;
}

const char* SendRecvMode2Str( SendRecvMode_t SendRecvMode )
{
	switch(SendRecvMode)
	{
	case KFPC_SendRecvMode_Null:
	case KFPC_SendRecvMode_Recvonly:
	case KFPC_SendRecvMode_Sendrecv:
	case KFPC_SendRecvMode_Sendonly:
	case KFPC_SendRecvMode_Inactive:
		{
			return KFPC_SendRecvModeList[SendRecvMode].SendRecvModeName;
		}
		break;
	default:return "unknow send recv mode";
	}
}

KFPC_SdpPayloadAttr_t* CodeIDToVoicePayloadAttrMap( unsigned int CodeID )
{
	if(CodeID < AudioCodec_MaxNum)
	{
		return &g_KFPC_AudioPayloadAttrMap[CodeID];
	}
	else
	{
		return NULL;
	}
}
//
//int SdpInfo2Str( KFPC_SdpInfo_t* Sdp_Info,char* StrBuf,int StrBufLen )
//{
//	int PrintfBufInx = 0;
//	int StreamsNumInx = 0;
//	int PayloadAttrInx=0;
//
//	//char HostStr[KFPC_SIP_SER_MAX_HOST_LEN];
//	PrintfBufInx = snprintf(StrBuf, StrBufLen,
//		"StreamsNum:%u,"
//		"Host:%s "
//		,
//		Sdp_Info->MediaNum,
//		Sdp_Info->Host.c_str());
//		//IntIP2Str(Sdp_Info->Host,HostStr,KFPC_SIP_SER_MAX_HOST_LEN));
//
//	
//
//	for(;StreamsNumInx<Sdp_Info->MediaNum;StreamsNumInx++)
//	{
//		PrintfBufInx+=snprintf(StrBuf+PrintfBufInx,StrBufLen-PrintfBufInx,
//			"{SdpStreamInx:%d,"
//			"Port:%u,"
//			"MediaType:%s,"
//			"TransportProto:%s,"
//			"SendRecvMode:%s,"
//			"PayloadsNum:%d,"
//			"Payloads:"
//			,
//			StreamsNumInx,
//			Sdp_Info->SdpMedia [StreamsNumInx].Port,
//			MediaType2Str(Sdp_Info->SdpMedia [StreamsNumInx].MediaType),
//			TransportProto2Str(Sdp_Info->SdpMedia [StreamsNumInx].TransportProto),
//			SendRecvMode2Str(Sdp_Info->SdpMedia [StreamsNumInx].SendRecvMode),
//			Sdp_Info->SdpMedia [StreamsNumInx].PayloadsNum);
//
//
//		for(;PayloadAttrInx<Sdp_Info->SdpMedia [StreamsNumInx].PayloadsNum;PayloadAttrInx++)
//		{
//			PrintfBufInx+=snprintf(StrBuf+PrintfBufInx,StrBufLen-PrintfBufInx,
//				"%d,",
//				Sdp_Info->SdpMedia [StreamsNumInx].Payloads[PayloadAttrInx]);
//		}
//
//		PrintfBufInx+=snprintf(StrBuf+PrintfBufInx,StrBufLen-PrintfBufInx,"},");
//
//		PrintfBufInx+=snprintf(StrBuf+PrintfBufInx,StrBufLen-PrintfBufInx,
//			"SdpPayloadAttrNum:%d,",
//			Sdp_Info->SdpMedia [StreamsNumInx].SdpPayloadAttrNum);
//
//		for( PayloadAttrInx=0;PayloadAttrInx<Sdp_Info->SdpMedia [StreamsNumInx].SdpPayloadAttrNum;PayloadAttrInx++)
//		{
//			PrintfBufInx+=snprintf(StrBuf+PrintfBufInx,StrBufLen-PrintfBufInx,
//				"{PayloadAttrInx:%d,"
//				"RtpPayload:%d,"
//				"RtpClock:%d,"
//				"RtpEnc:%s,"
//				"RtpParams:%s,"
//				"FmtpString:%s}"
//				,
//				PayloadAttrInx,
//				Sdp_Info->SdpMedia [StreamsNumInx].PayloadAttr[PayloadAttrInx].RtpPayload,
//				Sdp_Info->SdpMedia [StreamsNumInx].PayloadAttr[PayloadAttrInx].RtpClock,
//				Sdp_Info->SdpMedia [StreamsNumInx].PayloadAttr[PayloadAttrInx].RtpEnc.c_str(),
//				Sdp_Info->SdpMedia [StreamsNumInx].PayloadAttr[PayloadAttrInx].RtpParams.c_str(),
//				Sdp_Info->SdpMedia [StreamsNumInx].PayloadAttr[PayloadAttrInx].FmtpString.c_str());
//		}
//
//	}
//
//	return 0;
//}

KFPC_TransportProto_t TransportStr2Transport( const char* str ,int strlen )
{
	int i = 0;

	for(i=0;i<sizeof(KFPC_TransportProtoList);i++)
	{
		if(strncasecmp(KFPC_TransportProtoList[i].TransportProtoName,str,strlen) == 0)
		{
			return KFPC_TransportProtoList[i].TransportProtoType;
		}
	}
	return KFPC_TP_Null;
}


unsigned int VoiceStr2CodeIDList( const char* Str, unsigned char CodeIdList[])
{
	unsigned char CodeInx = 0;
	const char *delim = ",";
	char *p = NULL;

	char	SdpAttrStr[KFPC_MAX_SDP_ATTR_STR] = "";

	strncpy(SdpAttrStr,Str,KFPC_MAX_SDP_ATTR_STR-1);

	p = strtok(SdpAttrStr, delim);
	while (NULL != p)
	{
		unsigned char CodeID = 0;

		KFPC_SdpPayloadAttr_t* pAttr = CodeNameToAudioPayloadAttrMap(p,&CodeID);

		if(NULL != pAttr)
		{
			CodeIdList[CodeInx++] = CodeID;
		}

		p = strtok(NULL, delim);
	}

	return CodeInx;

}

KFPC_SdpPayloadAttr_t* CodeNameToAudioPayloadAttrMap( const char* CodeName,unsigned char* CodeID )
{
	unsigned char i = 0;

	for(i = 0;i < AudioCodec_MaxNum;i++)
	{
		if(g_KFPC_AudioPayloadAttrMap[i].RtpEnc == CodeName)
		{
			*CodeID = i;
			return &g_KFPC_AudioPayloadAttrMap[i];
		}
	}


	return NULL;

}

unsigned int VideoStr2CodeIDList( const char* Str, unsigned char CodeIdList[] )
{
	unsigned char CodeInx = 0;
	const char *delim = ",";
	char *p = NULL;

	char	SdpAttrStr[KFPC_MAX_SDP_ATTR_STR] = "";

	strncpy(SdpAttrStr,Str,KFPC_MAX_SDP_ATTR_STR-1);

	p = strtok(SdpAttrStr, delim);
	while (NULL != p)
	{
		unsigned char CodeID = 0;
		KFPC_SdpPayloadAttr_t* pAttr = CodeNameToVideoPayloadAttrMap(p,&CodeID);

		if(NULL != pAttr)
		{
			CodeIdList[CodeInx++] = CodeID;
		}

		p = strtok(NULL, delim);
	}

	return CodeInx;
}

bool CheckPayloadType(const char* Str)
{
	unsigned char	CodeID;

	if (NULL != CodeNameToAudioPayloadAttrMap(Str, &CodeID))
	{
		return true;
	}

	if (NULL != CodeNameToVideoPayloadAttrMap(Str, &CodeID))
	{
		return true;
	}

	return false;
}

KFPC_SdpPayloadAttr_t* CodeNameToVideoPayloadAttrMap( const char* CodeName,unsigned char* CodeID )
{
	unsigned int i = 0;

	for(i = 0;i < VideoCode_MaxNum;i++)
	{
		if(g_KFPC_VideoPayloadAttrMap[i].RtpEnc == CodeName)
		{
			*CodeID = i;
			return &g_KFPC_VideoPayloadAttrMap[i];
		}
	}


	return NULL;
}

KFPC_SdpPayloadAttr_t* CodeIDToVideoPayloadAttrMap( unsigned int CodeID )
{
	if(CodeID < VideoCode_MaxNum)
	{
		return &g_KFPC_VideoPayloadAttrMap[CodeID];
	}
	else
	{
		return NULL;
	}
}
