#ifndef KFPC_ContactCenterPublicDef_h__
#define KFPC_ContactCenterPublicDef_h__

#include "list"
#include <time.h>

/*--------------------------------------------------------------------------------------------------------------------------------
 |  Defines
 *------------------------------------------------------------------------------------------------------------------------------*/

#define KFPC_MAX_FILE_NAME							256			/**< ����ļ������� */
#define KFPC_MAX_VERSION_STR_SIZE					64			/**< �汾�ַ������� */
#define KFPC_MAX_NUMBER_SIZE						64			/**< �����볤�� */
#define KFPC_MAX_DTMF_SIZE							64			/**< ���DTMF�볤�� */
#define KFPC_TRUNKGROUP_NAME_LEN					64			/**< �м��������� */
#define KFPC_TRUNKGROUP_DESC_LEN					256			/**< �м������� */
#define KFPC_MAX_CHANNEL							32			/**< �����м�����ͨ���� */
#define KFPC_MAX_PLAY_CONTENT						1024		/**< ��󵥸������ļ����� */
#define KFPC_MAX_CHARSET_TRANS_BUFF_LEN				1024		/**< �ַ���ת���м仺�峤�� */
#define KFPC_MAX_ALARM_CONTENT						1024		/**< ���ĸ澯���� */
#define KFPC_USER_NAME_LEN							64			/**< �û������� */
#define KFPC_PASSWD_LEN								64			/**< ���볤�� */
#define KFPC_SIGNAL_TYPE_NAME_LEN					16			/**< �������������� */
#define KFPC_MAX_SQL_STR							64000		/**< ���SQL��䳤�� */
#define KFPC_MAX_FAX_INFO							64          /**< �������Ϣ����*/
#define KFPC_MAX_SMS_MSG_LEN						255			/**< ��������Ϣ����*/
#define KFPC_FAX_IP_LEN								64			/**< ���IP��ַ����*/
#define KFPC_MAX_PLAY_FILE_COUNT					128			/**< �������ļ����� */
const unsigned int KFPC_START_TIME				= 1344787200;	/**< KFPC ��ʼʱ��2012-8-13 */
#define KFPC_MAX_TIME_STR							20			/**< ���ʱ���ַ��� */
#define KPFC_MAX_WEEKDAY							7			/**< һ��7�� */
#define KFPC_MAX_CALLED_LIST_STR					10240		
#define KFPC_MAX_WORKNO_LIST_STR					10240
#define KFPC_MAX_LOG_STR							10240
#define KFPC_INVALID_AGENTID						(0)		/**< ��ЧAGENTID */
#define KFPC_INVALID_VDNID							(-1)		/**< ��ЧVDNID */
/**
 * �պ�ģʽ 1Ϊ�̶��պŸ�����2Ϊ��ֹ����0xfΪ�������պ�
 */
#define KFPC_DTMF_MODE_FixedDigits					1			/**< �չ̶��������� */
#define KFPC_DTMF_MODE_UseTermgChar					2			/**< ʹ����ֹ�������պ� */
#define KFPC_DTMF_MODE_IndefiniteFixedDigits		0xf			/**< �������պ� */	

#define KFPC_MAX_CallOutQueueCount					512		/**< ���������г��� */

#define KFPC_DEFAULT_ROUTER0						"****"		/**< Ĭ��·�� */
#define KFPC_DEFAULT_ROUTER1						"*****"		/**< Ĭ��·�� */
#define KFPC_DEFAULT_ROUTER2						"******"	/**< Ĭ��·�� */
#define KFPC_DEFAULT_ROUTER_LEN						5

#define WAIT_CALL_RELEASE_TIME						7200		/**< ϵͳ���ͨ��ʱ������ */
#define MAX_PRIVATEINFO_LEN							1024

#define MAX_SIP_BODY								1024
#define CONF_NAME									128
#define MSML_MAX_CONF								128
#define CREATE_CONF_TIMER							60
#define MAX_RECORD_COUNT							10000
#define MAX_CMD_LIVE_TIME							600
#define KFPC_MAX_REGEX_STR								512			/**< ��������ַ����� */
#define KFPC_MAX_ROUTERCOUNT						6
/*--------------------------------------------------------------------------------------------------------------------------------
 |  Types
 *------------------------------------------------------------------------------------------------------------------------------*/

/**
 *	״̬											����									��ע
 */
typedef enum KFPC_Ch_Status
{
	KFPC_CH_Status_Unready					= 0x00,				/**<	δ����	�����ʼ�� */
	KFPC_CH_Status_CallOffer				= 0x01,				/**< 	�����ʼ��״̬ */	
	KFPC_CH_Status_CallOut					= 0x02,				/**< 	������ʼ��״̬ */	
	KFPC_CH_Status_Accept					= 0x04,				/**< 	��������״̬ */	
	KFPC_CH_Status_Alerting					= 0x08,				/**<  	��������״̬ */	
	KFPC_CH_Status_Connect					= 0x10,				/**< 	Ӧ������״̬ */	
	KFPC_CH_Status_Release					= 0x20,				/**< 	�ͷ�״̬ */	
	KFPC_CH_Status_Failed					= 0x40,				/**< 	����״̬						ģ�����߼�ⲻ���κ��� */
	KFPC_CH_Status_OutofService				= 0x80,				/**< 	����ʧЧ						�����м�Ϊ������·ͨ�����ͨ */
	KFPC_CH_Status_LocalBlock				= 0x100,			/**< 	���ر���״̬ */	
	KFPC_CH_Status_Idle						= 0x200,			/**< 	�ձ�״̬ */	
	KFPC_CH_Status_RemoteBlock				= 0x400,			/**< 	Զ�˱��� */	
	KFPC_CH_Status_HardwareFailureBlock		= 0x800,			/**< 	Ӳ�����ϱ��� */	
	KFPC_CH_Status_OffHook					= 0x1000,			/**< 	ժ����Ҫ�����ģ����	 */
	KFPC_CH_Status_OnHook					= 0x2000,			/**< 	�һ���Ҫ�����ģ����	 */
	KFPC_CH_Status_WaitMoreInfo				= 0x4000,			/**< 	�ȴ������Ϣ	 */
}KFPC_Ch_Status;


typedef enum KFPC_Ch_Status_Inx
{
	KFPC_CH_Status_Inx_Unready					,				/**<	δ����	�����ʼ�� */
	KFPC_CH_Status_Inx_CallOffer				,				/**< 	�����ʼ��״̬ */	
	KFPC_CH_Status_Inx_CallOut					,				/**< 	������ʼ��״̬ */	
	KFPC_CH_Status_Inx_Accept					,				/**< 	��������״̬ */	
	KFPC_CH_Status_Inx_Alerting					,				/**<  	��������״̬ */	
	KFPC_CH_Status_Inx_Connect					,				/**< 	Ӧ������״̬ */	
	KFPC_CH_Status_Inx_Release					,				/**< 	�ͷ�״̬ */	
	KFPC_CH_Status_Inx_Failed					,				/**< 	����״̬						ģ�����߼�ⲻ���κ��� */
	KFPC_CH_Status_Inx_OutofService				,				/**< 	����ʧЧ						�����м�Ϊ������·ͨ�����ͨ */
	KFPC_CH_Status_Inx_LocalBlock				,			/**< 	���ر���״̬ */	
	KFPC_CH_Status_Inx_Idle						,			/**< 	�ձ�״̬ */	
	KFPC_CH_Status_Inx_RemoteBlock				,			/**< 	Զ�˱��� */	
	KFPC_CH_Status_Inx_HardwareFailureBlock		,			/**< 	Ӳ�����ϱ��� */	
	KFPC_CH_Status_Inx_OffHook					,			/**< 	ժ����Ҫ�����ģ����	 */
	KFPC_CH_Status_Inx_OnHook					,			/**< 	�һ���Ҫ�����ģ����	 */
	KFPC_CH_Status_Inx_WaitMoreInfo				,			/**< 	�ȴ������Ϣ	 */
}KFPC_Ch_Status_Inx;

#define KFPC_IDLE_STATUS	(KFPC_CH_Status_Idle |	KFPC_CH_Status_OnHook)	/**< ͨ������״̬ */
#define KFPC_CALL_LIVE		(KFPC_CH_Status_CallOffer | KFPC_CH_Status_CallOut | KFPC_CH_Status_Accept | KFPC_CH_Status_Alerting | KFPC_CH_Status_Connect | KFPC_CH_Status_OffHook | KFPC_CH_Status_WaitMoreInfo)	/**< �����ǻ��״̬ */
#define KFPC_CALL_RING		(KFPC_CH_Status_Accept | KFPC_CH_Status_CallOffer)		/**< �ȴ�ժ�� */

#define MAX_STATUS_COUNT		32	

unsigned int GetExp(unsigned int Val);

typedef enum KFPC_SignalType
{
	KFPC_SignalType_R2_CHINA,					/**< R2 */
	KFPC_SignalType_R2_BASEIC,			/**< R2 */
	KFPC_SignalType_ISDN_N,				/**< ISDN */
	KFPC_SignalType_ISDN_U,				/**< ISDN */
	KFPC_SignalType_SS7_TUP,				/**< SS7 */
	KFPC_SignalType_SS7_ISUP,				/**< SS7 */
	KFPC_SignalType_ClearChannel,		/**< ͸��ͨ�� */
	KFPC_SignalType_FXS,				/**< ���� */
	KFPC_SignalType_SIP,				/**< SIP */
	KFPC_SignalType_FXO,				/**< ���� */
	KFPC_SignalType_END
}KFPC_SignalType;

KFPC_SignalType IntToSignalType(unsigned int val);

typedef struct SignalType_Info
{
	KFPC_SignalType	SignalType;
	char			SignalTypeName[KFPC_SIGNAL_TYPE_NAME_LEN];
}SignalType_Info;

const SignalType_Info	SignalType_List[]={
	{KFPC_SignalType_R2_CHINA,	"R2_CHINA"},					/**< R2 */
	{KFPC_SignalType_R2_BASEIC,	"R2_BASEIC"},					/**< R2 */
	{KFPC_SignalType_ISDN_N,	"ISDN_N"},						/**< ISDN */
	{KFPC_SignalType_ISDN_U,	"ISDN_U"},						/**< ISDN */
	{KFPC_SignalType_SS7_TUP,	"SS7_TUP"},						/**< SS7 */
	{KFPC_SignalType_SS7_ISUP,	"SS7_ISUP"},					/**< SS7 */
	{KFPC_SignalType_ClearChannel,	"ClearChannel"},			/**< ͸��ͨ�� */
	{KFPC_SignalType_FXS,		"FXS"},							/**< ���� */
	{KFPC_SignalType_SIP,		"SIP"},							/**< SIP */
	{KFPC_SignalType_FXO,		"FXO"}							/**< ���� */
};




/**
 * @enum KFPC_TS_ID_ConferenceJoinMode
 * @brief ����ģʽ
 */
typedef enum KFPC_JoinConfMode
{
	KFPC_CJM_ListenAndSpeak	= 0,		/**< ������˵	*/
	KFPC_CJM_ListenOnly	=	1			/**< ֻ��		*/
}KFPC_JoinConfMode;

typedef enum KFPC_DEVICE_TYPE
{
	DEVICE_TYPE_TRUNKGROUP = 0,			/**< �м��� */
	DEVICE_TYPE_CHANNEL	= 1,			/**< �м� */
	DEVICE_TYPE_ADDRESS = 2				/**< ���� */
}KFPC_DEVICE_TYPE;



/**
 *	�豸��Ϣ�ṹ
 */
typedef struct	KFPC_DEVICE
{	
	unsigned int		Type;	
	unsigned short		Span;
	unsigned char		TimeSlot;
	char				TrunkGroup[KFPC_TRUNKGROUP_NAME_LEN];
	char				CallerNO[KFPC_MAX_NUMBER_SIZE];			/**< ���к���									*/
	char				CalledNO[KFPC_MAX_NUMBER_SIZE];			/**< ���к���									*/	
	char				RedirectingNum[KFPC_MAX_NUMBER_SIZE];		/**< �ض������									*/
	char				OriginalCalled[KFPC_MAX_NUMBER_SIZE];		/**< �ض������									*/

}KFPC_DEVICE;

/**
 *	�պŲ���
 */
typedef struct KFPC_DTMFParam
{
	unsigned int		MODE;									/**< �պ�ģʽ 1Ϊ�̶��պŸ�����2Ϊ��ֹ����0xfΪ�������պ� */
	unsigned int		MaxDigits;								/**< �պų��� */
	unsigned int		TermgChar;								/**< ��ֹ��	*/
	unsigned int		FirstDigitInform;						/**< �յ���һ�����Ƿ�֪ͨ */
	unsigned int		VoiceStopFlag;							/**< �յ����Ƿ��������,0Ϊֹͣ������1Ϊ��������	*/
	unsigned int		FirstDigitTimer;						/**< ����Ϊ��λ(���������밴�µ�һ�����������ʱ����)	*/
	unsigned int		InterDigitermer;						/**< ����Ϊ��λ(���ΰ��������ʱ����)	(���յ���һ��������������ö�ʱ��)					*/
	unsigned int		CompletionTimer;						/**< ����Ϊ��λ(�յ���һ�����������һ��������ʱ�䳤��)	(���յ���һ��������������ö�ʱ��)	*/
}KFPC_DTMFParam;

typedef union KFPC_CallID
{
	unsigned long long	CallID;
	struct 
	{
		
		unsigned short	ChID;									/**< ͨ��ID */
		unsigned short	AppID;									/**< Ӧ��ID */		
		unsigned int	Time;									/**< ��ʼʱ�� */
	}CallIDInfo;
}KFPC_CallID;

typedef union KFPC_LoginSN
{
	unsigned long long	LoginSN;
	struct 
	{		
		unsigned int	SN;
		unsigned int	AppID;									/**< Ӧ��ID */		
		
	}LoginSNInfo;
}KFPC_LoginSN;

typedef union KFPC_SessionID
{
	unsigned long long	SessionID;
	struct 
	{
		
		unsigned short	ChID1;									/**< ͨ��ID */
		unsigned short	ChID2;									/**< ͨ��ID */		
		unsigned int	Time;									/**< ��ʼʱ�� */
	}SessionIDInfo;
}KFPC_SessionID;


typedef enum KFPC_VoicePlayType_t
{
	IVR_PLAY_TYPE_FILE = 0,			/**< �����ļ� */
	IVR_PLAY_TYPE_TEXT = 1,			/**< �����ı� */
}KFPC_VoicePlayType;

typedef struct KFPC_VoiceItem_t
{
	KFPC_VoicePlayType PlayType;
	char BeforeTranContent[KFPC_MAX_PLAY_CONTENT];
}KFPC_VoiceItem;

typedef std::list<KFPC_VoiceItem> VoiceItemList_t;
typedef VoiceItemList_t::iterator VoiceItemListIter_t;	
/*--------------------------------------------------------------------------------------------------------------------------------
 |  Function Prototypes
 *------------------------------------------------------------------------------------------------------------------------------*/
const char* ChStatusToStr(int ID);
const char* SignalTypeToStr(int SignalType);
unsigned short CallIDToChannel(unsigned long long& CallID);
#define ChannelToSpan(x)					((unsigned short)(x/KFPC_MAX_CHANNEL))			/**< �߼�ͨ���ŵ��м̺� */
#define ChannelToTimeSlot(x)					((unsigned char)(x%KFPC_MAX_CHANNEL))				/**< �߼�ͨ���ŵ�ͨ���� */
#define SpanTimeSlotToChannel(Span,TimeSlot)	(Span*KFPC_MAX_CHANNEL+TimeSlot)

const char* MsgIDToStr(unsigned int MsgID,char* MsgIDStr);
unsigned int ParsePlayContent(VoiceItemList_t &VoiceItemList,char *pPlayContent);

//#define KFPC_RESULT_MSG_GET_TYPE(__nResultMsg__)	(unsigned int)(((unsigned int)(__nResultMsg__) & 0xFF000000) >> 28)
#define KFPC_RESULT_MSG_GET_TYPE(__nResultMsg__)	((((unsigned int)(__nResultMsg__) & 0xFF000000) >> 28) & 0x0000FFFF)

#define KFPC_CHANNEL_UNIQUEID(APPID,CHANNELID)	((APPID<<16) + CHANNELID)
#define KFPC_VOIP_UNIQUEID(APPID,NODE,CHANNELID)	((APPID<<16) + NODE*MAX_XIOPCH+CHANNELID)
#define KFPC_IVR_UNIQUEID(APPID,NODE,CHANNELID)	((APPID<<16) + NODE*MAX_IVR_CH+CHANNELID)


const char* GetErrorStr(unsigned int ErrorCode,unsigned int Lang = 0);

const char* GetCauseStr(unsigned int Cause,unsigned int Lang = 0);
const char* GetSIPCauseDes(unsigned int Cause,bool IsChinese);
const char* GetQ850CauseDes(unsigned int Cause,bool IsChinese);

#define 	UINT32ToHShort(x)	(unsigned short)((x&0xffff0000) >> 16)
#define 	UINT32ToLShort(x)	(unsigned short)(x&0x0000ffff)
#define		MIN(a,b)	((a<b) ? a:b )
#define		MAX(a,b)	((a>b) ? a:b )
/**< �������� */
typedef	enum KFPC_CALL_FLAG
{	
	CALL_FLAG_OUT,					/**< ���� */
	CALL_FLAG_IN,					/**< ���� */
	CALL_FLAG_CONF					/**< ���� */
}KFPC_CALL_FLAG;

const char* CallFlag2Str(KFPC_CALL_FLAG	ct);

typedef	enum KFPC_CALL_TYPE
{	
	CALL_TYPE_ONEPART,					/**< One part */
	CALL_TYPE_TWOPART,					/**< two part */
	CALL_TYPE_CONFRENCE,                 /**< Conference */
	CALL_TYPE_END
}KFPC_CALL_TYPE;

static const char* CallTypeToStr(unsigned int val)
{
	switch(val)
	{
		case CALL_TYPE_ONEPART:    return "OnePartCall";
		case CALL_TYPE_TWOPART:    return "TwoPartCall" ;
		case CALL_TYPE_CONFRENCE:  return "ConferenceCall";
		default:                       return "unknown";
	}
}

typedef enum KFPC_EXT_NUM_TYPE
{
	EXT_NUM_ALL_TRANSNUM,
	EXT_NUM_BUSY_TRANSNUM,
	EXT_NUM_NOANSWER_TRANSNUM,	
	EXT_NUM_OUTSIDE_LINE
}KFPC_EXT_NUM_TYPE;

static const char* ExtNumTypeToStr(unsigned int val)
{
	switch(val)
	{
	case EXT_NUM_ALL_TRANSNUM:    return "EXT_NUM_ALL_TRANSNUM";
	case EXT_NUM_BUSY_TRANSNUM:    return "EXT_NUM_BUSY_TRANSNUM" ;
	case EXT_NUM_NOANSWER_TRANSNUM:  return "EXT_NUM_NOANSWER_TRANSNUM";
	case EXT_NUM_OUTSIDE_LINE:		return "EXT_NUM_OUTSIDE_LINE";
	default:                       return "unknown";
	}
}

typedef enum KFPC_LANG_TYPE
{
	LANG_TYPE_CN = 1,
	LANG_TYPE_EN = 2
}KFPC_LANG_TYPE;

/**< �������� */
typedef	enum KFPC_CALLOUT_TYPE
{	
	CALLOUT_TYPE_AGENTCALL,					/**< ��ϯ�ֶ���� */
	CALLOUT_TYPE_AGENTCONFIRMCALL,			/**< ��ϯȷ����� */
	CALLOUT_TYPE_AUTOCALL,					/**< ϵͳ�Զ���� */
	CALLOUT_TYPE_TESTCALL,					/**< ϵͳ�Ժ� */
}KFPC_CALLOUT_TYPE;

/**< ����״̬ */
typedef	enum KFPC_CALLOUT_STATUS
{	
	CALLOUT_STATUS_READY,				/**< δ���� */
	CALLOUT_STATUS_CALLING,				/**< ���ں��� */
	CALLOUT_STATUS_SUCCESS,				/**< ���гɹ� */
	CALLOUT_STATUS_FAILED,				/**< ����ʧ�� */
	CALLOUT_STATUS_PAUSE				/**< ������ͣ */
}KFPC_CALLOUT_STATUS;


/**< ����ת������ */
typedef	enum KFPC_CALLOUT_TRANSFER_TYPE
{	
	CALLOUT_TRANSFER_TYPE_AGENT,		/**< ��ϯ */
	CALLOUT_TRANSFER_TYPE_IVR,			/**< IVR */
	CALLOUT_TRANSFER_TYPE_QUEUE,		/**< �Ŷ� */

}KFPC_CALLOUT_TRANSFER_TYPE;



typedef enum KFPC_SYS_OBJ_TYPE
{
	OBJ_TYPE_VDN,
	OBJ_TYPE_ACD_SPLIT,
	OBJ_TYPE_ACD_AGENT,
	OBJ_TYPE_ACD_EXTNUM
}KFPC_SYS_OBJ_TYPE;

typedef	enum KFPC_VDN_STATUS
{
	AGENT_VDN_STATUS_NORMAL = 0,				//����״̬
	AGENT_VDN_STATUS_INSUFFICIENTBALANCE = 1,	//����
	AGENT_VDN_STATUS_LOCKED = 2,				//Ƿ������
	AGENT_VDN_STATUS_MANUAL_LOCKED = 3,			//�ֶ�����
	AGENT_VDN_STATUS_STOP = 8,					//ͣ��
}KFPC_VDN_STATUS;

typedef struct TS_RedirectingAttr
{
	unsigned char	NOA;//Nature of address indicator
	unsigned char	NumPlanInd;//Numbering plan Ind
	unsigned char	PresentInd;//Present.Ind
	unsigned char	Original_redirection_reasons;	//0Ϊ��֪��ԭ��1Ϊ�û�æ,��Ϊ��Ӧ��3Ϊ������
	unsigned char   Redirecting_reason;				//0Ϊ��֪��ԭ��1Ϊ�û�æ,��Ϊ��Ӧ��3Ϊ������,4���������û����ɵ���
}TS_RedirectingAttr;	

typedef struct TS_CallingNumAttr
{
	unsigned char	NOA;//Nature of address indicator
	unsigned char	INNInd;	//
	unsigned char	NumPlanInd;//Numbering plan Ind
	unsigned char	PresentInd;//Present.Ind
	unsigned char	Screening;//Screening
}TS_CallingNumAttr;

typedef	enum KFPC_CHANNEL_RELMODE
{
	CHANNEL_RELMODE_REL = 0,				//�ͷ�
	CHANNEL_RELMODE_PARK = 1				//����
}KFPC_CHANNEL_RELMODE;

typedef enum MSML_DeleteWhen
{
	MSML_DelMode_NoMedia,
	MSML_DelMode_NoControl,
	MSML_DelMode_Never
}MSML_DeleteWhen;

//�ȴ�����1Ϊ�Ŷӣ�2Ϊ���壬3Ϊ����
typedef enum CallWaitType_t
{
	CWT_NULL,
	CWT_QUEUE,	
	CWT_RING,
	CWT_HOLD,
	CWT_ROUTEING
}CallWaitType_t;


typedef enum ConfType_t
{
	ConfType_NULL,
	ConfType_Monitor,
	ConfType_ForceInsert,
	ConfType_MultiParty
}ConfType_t;

const char* CallWaitTypeToStr(CallWaitType_t cwt);
#define RingBackMusic	"ringback.wav"
#define DefaultAgentAnswerTimeOut	60
#define DefaultAppDisconnectTimeOut 60
time_t GetCallID_TIME(unsigned long long CallID);
#define MAX_RECALL_TIMES	0
#define MAX_RECALL_TIMEOUT	3
#define MAX_LOGIN_TIMEOUT	60

typedef enum EXT_TYPE_t
{
	EXT_TYPE_NULL,
	EXT_TYPE_GENERAL,
	EXT_TYPE_VIRTUAL	//����ֻ�
	
}EXT_TYPE_t;

const char* ExtTypeToStr(EXT_TYPE_t et);
EXT_TYPE_t	IntToExtType(unsigned int val);

enum KFPC_DB_OPERATE_TYPE
{
	KFPC_Operate_Initialize,
	KFPC_Operate_Insert,
	KFPC_Operate_Update,
	KFPC_Operate_Delete
};

const char* OperateTypeToStr(KFPC_DB_OPERATE_TYPE t);

typedef enum KFPC_QUEUE_END_CAUSE_t
{
	KFPC_EQT_CallReleased,
	KFPC_EQT_CallTimeOut,
	KFPC_EQT_CallOverLen,
	KFPC_EQT_CallAlloced,
	KFPC_EQT_CallManual
}KFPC_QUEUE_END_CAUSE_t;

typedef enum KFPC_ExtNumCallOutFail_t
{
	KFPC_ExtNum_Null,
	KFPC_ExtNum_Busy,
	KFPC_ExtNum_CallReleased,
	KFPC_ExtNum_NoAnswer
}KFPC_ExtNumCallOutFail_t;


#endif // KFPC_ContactCenterPublicDef_h__