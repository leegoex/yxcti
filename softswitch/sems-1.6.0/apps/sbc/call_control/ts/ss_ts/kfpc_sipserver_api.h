#ifndef KFPC_SIPSERVER_API_H
#define KFPC_SIPSERVER_API_H

#include <string>
#include "kfpc_sipserver_api.h"

using namespace std;

#define		SIP_MIN(a,b)	((a<b) ? a:b )
#define		SIP_MAX(a,b)	((a>b) ? a:b )

#define	KFPC_SIP_SER_MAX_HOST_LEN			64 
#define	KFPC_SIP_SER_MAX_USER_LEN			64
#define	KFPC_SIP_SER_MAX_TAG_LEN			64
#define	KFPC_SIP_SER_MAX_PAYLOAD_COUNT		16
#define	KFPC_SIP_SER_MAX_ENCODE_LEN			16
#define	KFPC_SIP_SER_MAX_ENCPARAM_LEN		32
#define	KFPC_SIP_SER_MAX_FMTP_STR_LEN		32
#define	KFPC_SIP_SER_MAX_PAYLOAD_ATTR_COUNT	16
#define	KFPC_SIP_SER_MAX_STREAM_COUNT		8
#define	KFPC_SIP_SER_MAX_SIP_CALLID			64
#define KFPC_SIP_SER_MAX_TSERVER_COUNT		8
#define KFPC_SIP_SER_MAX_REASONTEXT			64
#define KFPC_SIP_SER_MAX_MEDIANAME			16
#define KFPC_SIP_SER_MAX_TRANSPORTPROTONAME	16
#define KFPC_SIP_SER_MAX_SENDRECVMODENAME	16
#define	KFPC_MAX_SDP_ATTR_STR				512


enum {
	/* SIP response code values */
	IPEC_SIPReasonStatus200OK = 200,
	IPEC_SIPReasonStatus400BadRequest = 400,
	IPEC_SIPReasonStatus401Unauthorized = 401,
	IPEC_SIPReasonStatus402PaymentRequired = 402,
	IPEC_SIPReasonStatus403Forbidden = 403,
	IPEC_SIPReasonStatus404NotFound = 404,
	IPEC_SIPReasonStatus405MethodNotAllowed = 405,
	IPEC_SIPReasonStatus406NotAcceptable = 406,
	IPEC_SIPReasonStatus407ProxyAuthenticationRequired = 407,
	IPEC_SIPReasonStatus408RequestTimeout = 408,
	IPEC_SIPReasonStatus410Gone = 410,
	IPEC_SIPReasonStatus413RequestEntityTooLarge = 413,
	IPEC_SIPReasonStatus414RequestUriTooLong = 414,
	IPEC_SIPReasonStatus415UnsupportedMediaType = 415,
	IPEC_SIPReasonStatus416UnsupportedURIScheme = 416,
	IPEC_SIPReasonStatus420BadExtension = 420,
	IPEC_SIPReasonStatus421ExtensionRequired = 421,
	IPEC_SIPReasonStatus423IntervalTooBrief = 423,
	IPEC_SIPReasonStatus480TemporarilyUnavailable = 480,
	IPEC_SIPReasonStatus481CallTransactionDoesNotExist = 481,
	IPEC_SIPReasonStatus482LoopDetected = 482,
	IPEC_SIPReasonStatus483TooManyHops = 483,
	IPEC_SIPReasonStatus484AddressIncomplete = 484,
	IPEC_SIPReasonStatus485Ambiguous = 485,
	IPEC_SIPReasonStatus486BusyHere = 486,
	IPEC_SIPReasonStatus487RequestTerminated = 487,
	IPEC_SIPReasonStatus488NotAcceptableHere = 488,
	IPEC_SIPReasonStatus491RequestPending = 491,
	IPEC_SIPReasonStatus493Undecipherable = 493,
	IPEC_SIPReasonStatus500ServerInternalError = 500,
	IPEC_SIPReasonStatus501NotImplemented = 501,
	IPEC_SIPReasonStatus502BadGateway = 502,
	IPEC_SIPReasonStatus503ServiceUnavailable = 503,
	IPEC_SIPReasonStatus504ServerTimeout = 504,
	IPEC_SIPReasonStatus505VersionNotSupported = 505,
	IPEC_SIPReasonStatus513MessageTooLarge = 513,
	IPEC_SIPReasonStatus600BusyEverywhere = 600,
	IPEC_SIPReasonStatus603Decline = 603,
	IPEC_SIPReasonStatus604DoesNotExistAnywhere = 604,
	IPEC_SIPReasonStatus606NotAcceptable = 606,
	IPEC_SIPReasonStatusBYE = 800,
	IPEC_SIPReasonStatusCANCEL = 801,
};


typedef enum KFPC_NetType_t {
	KFPC_NetType_IN = 1,
	KFPC_NetType_TN = 2,
	KFPC_NetType_ATM = 3,
	KFPC_NetType_PSTN = 4
}KFPC_NetType_t;

typedef enum KFPC_AddrType_t {
	KFPC_AddrType_Null = 0,
	KFPC_AddrType_IP4 = 1,
	KFPC_AddrType_IP6 = 2,
	KFPC_AddrType_NSAP = 3,
	KFPC_AddrType_GWID = 4,
	KFPC_AddrType_E164 = 5
}KFPC_AddrType_t;

typedef enum KFPC_MediaType_t {
	KFPC_MediaType_Null,
	KFPC_MediaType_audio,
	KFPC_MediaType_video,	
	KFPC_MediaType_application,
	KFPC_MediaType_text,	
	KFPC_MediaType_message,
	KFPC_MediaType_image
}KFPC_MediaType_t;

typedef enum KFPC_TransportProto_t {

	KFPC_TP_Null,
	KFPC_TP_RTPAVP,
	KFPC_TP_RTPAVPF,
	KFPC_TP_UDP,
	KFPC_TP_RTPSAVP,
	KFPC_TP_UDPTL,
	KFPC_TP_RTPSAVPF,
	KFPC_TP_UDPTLSRTPSAVP,
	KFPC_TP_UDPTLSRTPSAVPF

}KFPC_TransportProto_t;

typedef enum SendRecvMode_t {
	KFPC_SendRecvMode_Null ,
	KFPC_SendRecvMode_Recvonly,
	KFPC_SendRecvMode_Sendrecv,
	KFPC_SendRecvMode_Sendonly,
	KFPC_SendRecvMode_Inactive,
}SendRecvMode_t;


//typedef enum KFPC_AttFieldType_t {
//	KFPC_AttFieldType_Null = 0x0,
//	KFPC_AttFieldType_Fmtp = (1 << 1),
//	KFPC_AttFieldType_Keywds = (1 << 2),
//	KFPC_AttFieldType_Tool = (1 << 3),
//	KFPC_AttFieldType_Ptime = (1 << 4),
//	KFPC_AttFieldType_Maxptime = (1 << 5),
//	KFPC_AttFieldType_Rtpmap = (1 << 6),
//	KFPC_AttFieldType_Recvonly = (1 << 7),
//	KFPC_AttFieldType_Sendrecv = (1 << 8),
//	KFPC_AttFieldType_Sendonly = (1 << 9),
//	KFPC_AttFieldType_Inactive = (1 << 10),
//	KFPC_AttFieldType_Orient = (1 << 11),
//	KFPC_AttFieldType_Charset = (1 << 12),
//	KFPC_AttFieldType_Framerate = (1 << 13),
//	KFPC_AttFieldType_Quality = (1 << 14),
//	KFPC_AttFieldType_Cat = (1 << 15),
//}KFPC_AttFieldType_t;

typedef enum	KFPC_VoiceCodeID_t {
	AudioCodec_G711A,
	AudioCodec_G711U,
	AudioCodec_G729,
	AudioCodec_iLBC,
	AudioCodec_OPUS,
	AudioCodec_MaxNum,			//This item is not a valid codec
}KFPC_VoiceCodeID_t;

typedef enum	KFPC_VideoCodeID_t {
	VideoCode_H264 ,
	VideoCode_H265,
	VideoCode_VP8,
	VideoCode_VP9,
	VideoCode_MaxNum,			//This item is not a valid codec
}KFPC_VideoCodeID_t;


class  AudioCodeCfg_t
{
public:
	unsigned char	CodeID;
	unsigned char	PayloadType;
	string			CodeName;
	void Clear() 
	{ 
		CodeID = 0; 
		PayloadType = 0;
		CodeName = "";
	}
};


typedef struct KFPC_MediaTypeList_t
{
	KFPC_MediaType_t	MediaType;
	char				MediaName[KFPC_SIP_SER_MAX_MEDIANAME];
}KFPC_MediaTypeList_t;

typedef struct KFPC_TransportProtoList_t
{
	KFPC_TransportProto_t	TransportProtoType;
	char					TransportProtoName[KFPC_SIP_SER_MAX_TRANSPORTPROTONAME];
}KFPC_TransportProtoList_t;

typedef struct KFPC_SendRecvModeList_t
{
	SendRecvMode_t	SendRecvMode;
	char			SendRecvModeName[KFPC_SIP_SER_MAX_SENDRECVMODENAME];
}KFPC_SendRecvModeList_t;




typedef struct KFPC_SdpPayloadAttr_t {
	//unsigned int		AttFieldType;
	unsigned char		RtpPayload;
	unsigned char		Channel;			// Set number of channels for raw input (default: 2)	
	unsigned int		RtpClock;			// Set sampling rate for raw input (default: 48000)
	string				RtpEnc;				// encoding name
	string				RtpParams;
	string				FmtpString;
	unsigned char		MediaType;
} KFPC_SdpPayloadAttr_t;


typedef struct KFPC_SdpMedia_t
{
	unsigned short			Port;
	KFPC_MediaType_t		MediaType;
	KFPC_TransportProto_t	TransportProto;
	SendRecvMode_t			SendRecvMode;
	//unsigned char			PayloadsNum;
	//unsigned char			Payloads[KFPC_SIP_SER_MAX_PAYLOAD_COUNT];
	unsigned char			SdpPayloadAttrNum;
	KFPC_SdpPayloadAttr_t	PayloadAttr[KFPC_SIP_SER_MAX_PAYLOAD_ATTR_COUNT];
}KFPC_SdpMedia_t;

typedef struct KFPC_SdpInfo_t {
	string				Address;
	unsigned char		MediaNum;
	KFPC_SdpMedia_t		SdpMedia[KFPC_SIP_SER_MAX_STREAM_COUNT];
}KFPC_SdpInfo_t;

class KFPC_Receive_Info_t {
public:
	void Clear()
	{
		FromIp = "";
		FromPort = 0;
		InterfaceIp = "";
		InterfacePort = 0;
	}

	string				FromIp;
	unsigned short		FromPort;
	string				InterfaceIp;
	unsigned short		InterfacePort;
};

class KFPC_HostPort_t {
public:
	void Clear()
	{
		Host = "";
		Port = 0;
	}
	string		   Host;
	unsigned short Port;

};

class KFPC_From_t {
public:
	void Clear()
	{
		UserInfo = "";
		HostPort.Clear();
		DisplayName = "";
		Tag = "";
	}
	string			UserInfo;
	KFPC_HostPort_t	HostPort;
	string			DisplayName;
	string			Tag;

};

class KFPC_To_t {
public:
	void Clear()
	{
		UserInfo = "";
		HostPort.Clear();
		DisplayName = "";
		Tag = "";
	}

	string			UserInfo;
	KFPC_HostPort_t	HostPort;
	string			DisplayName;
	string			Tag;
};

#ifdef __cplusplus
extern "C" 
{
#endif


SendRecvMode_t SendRecvModeStr2SendRecvMode( const char* str ,int strlen);
const char* SendRecvMode2Str(SendRecvMode_t SendRecvMode);
const char* SIPMsgIDToStr( unsigned int MsgID );
const char* IntIP2Str(unsigned int addr, char* buf, unsigned short bufLen);
int SdpInfo2Str(KFPC_SdpInfo_t* Sdp_Info,char* StrBuf,int StrBufLen);
KFPC_SdpPayloadAttr_t* CodeIDToVoicePayloadAttrMap(unsigned int CodeID);
KFPC_TransportProto_t TransportStr2Transport( const char* str ,int strlen);
const char* TransportProto2Str(KFPC_TransportProto_t	TransportProtoType);
KFPC_MediaType_t MediaStr2MediaType( const char* str,int strlen );
const char* MediaType2Str(KFPC_MediaType_t	MediaType);

KFPC_SdpPayloadAttr_t* CodeNameToAudioPayloadAttrMap(const char* CodeName,unsigned char* CodeID);
KFPC_SdpPayloadAttr_t* CodeNameToVideoPayloadAttrMap(const char* CodeName,unsigned char* CodeID);

KFPC_SdpPayloadAttr_t* CodeIDToVideoPayloadAttrMap(unsigned int CodeID);

unsigned int VoiceStr2CodeIDList(	
	const char*			Str,
	unsigned char		CodeIdList[]);

unsigned int VideoStr2CodeIDList(	
	const char*			Str,
	unsigned char		CodeIdList[]);

bool	CheckPayloadType(const char*			Str);
//unsigned int InitVoiceSDP( 
//	const char*			MediaIp, 
//	unsigned short		MediaPort, 
//	unsigned char		CodeIdList[], 
//	unsigned char		CodeIDCount, 
//	KFPC_SdpStream_t*	SdpStream,
//	SendRecvMode_t		SendRecvMode );
//
//unsigned int InitVideoSDP( 
//	const char*			MediaIp, 
//	unsigned short		MediaPort, 
//	unsigned char		CodeIdList[], 
//	unsigned char		CodeIDCount, 
//	KFPC_SdpStream_t*	SdpStream,
//	SendRecvMode_t		SendRecvMode );

#ifdef __cplusplus
}  /* end extern "C" */
#endif

#endif
