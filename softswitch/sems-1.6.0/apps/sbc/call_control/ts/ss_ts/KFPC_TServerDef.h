#ifndef KFPC_TServerDef_h__
#define KFPC_TServerDef_h__
#include "KFPC_ContactCenterPublicDef.h"
#include "kfpc_tserver_api.h"

/*--------------------------------------------------------------------------------------------------------------------------------
 |  Defines
 *------------------------------------------------------------------------------------------------------------------------------*/
const char			SS_TSERVER_CFG[]				=	"ss_tserver_config.xml";
const unsigned int  KFPC_MAX_EH_NODE				=	1;																	/**< ���֧��EH�������ڵ� */
const unsigned int  KFPC_SINGLE_NODE_MAX_VOIP_SPAN	= 64;																	/**< ���ڵ����VOIP�м��� */
const unsigned int  KFPC_SINGLE_NODE_MAX_CONF_SPAN	= 32;

const unsigned int KFPC_VOIP_BEGIN_SPAN				= 0;																	/**< VOIP ��ʼ�м��� */
const unsigned int KFPC_VOIP_END_SPAN				= (KFPC_VOIP_BEGIN_SPAN + KFPC_SINGLE_NODE_MAX_VOIP_SPAN - 1);			/**< VOIP �����м̺� */

const unsigned int KFPC_CONFID_BEGIN_SPAN			= (KFPC_VOIP_END_SPAN + 1);												/**< ���鿪ʼ�м̺� */
const unsigned int KFPC_CONFID_END_SPAN				= (KFPC_CONFID_BEGIN_SPAN + KFPC_SINGLE_NODE_MAX_CONF_SPAN - 1);		/**< ��������м̺� */

const unsigned int KFPC_NODE_MAX_SPAN				= (KFPC_CONFID_END_SPAN + 1);											/**< �����ڵ����SPAN */
const unsigned int KFPC_MAX_SIP_CHANNEL				= (KFPC_SINGLE_NODE_MAX_VOIP_SPAN*KFPC_MAX_CHANNEL);
																													
																															/**< ����м��� */
const unsigned int	KFPC_MAX_CHANNEL_NUMBER			=	(KFPC_SINGLE_NODE_MAX_VOIP_SPAN*KFPC_MAX_CHANNEL);								/**< TServer����ͨ���� */
															/**< ���ڵ��������м��� */


const unsigned int KFPC_MAX_AUDIO_NAME				=	16;																	/**< �������������� */
const unsigned int KFPC_IDLE_TYPE_NAME_LEN			=	16;																	/**< �����������ֳ��� */

/*--------------------------------------------------------------------------------------------------------------------------------
 |  Types
 *------------------------------------------------------------------------------------------------------------------------------*/
/**
 *	ͨ������
 */
typedef enum KFPC_CH_TYPE
{
	CH_TYPE_AG,					/**< ģ��ͨ�� */
	CH_TYPE_DTI,				/**< �����м� */
	CH_TYPE_SIP,				/**< SIPͨ�� */
	CH_TYPE_CONF				/**< ����ͨ�� */
}KFPC_CH_TYPE;

const char* ChTypeToStr(KFPC_CH_TYPE val);

/**< �������� */
typedef enum KFPC_ConnectionType
{
	ConType_CH_NULL,
	ConType_CH_IVR,
	ConType_CH_FAX,
	ConType_CH_CH,				/**<  Channel--Channel */
	ConType_CH_CONF				/**<  ConfChannel--Channel */
}KFPC_ConnectionType;
const char* ConTypeToStr(KFPC_ConnectionType val);

typedef enum KFPC_ChannelActionType
{
	KFPC_CHActionType_NULL,
	KFPC_CHActionType_CH_IVR,
	KFPC_CHActionType_CH_FAX,
	KFPC_CHActionType_CH_CH,
	KFPC_CHActionType_CH_CONF,
	KFPC_CHActionType_CH_CHANGE_CONNECT_MODE,
	KFPC_CHActionType_CH_MONITOR_IVR,
	KFPC_CHACTIONTYPE_CH_MIX_IVR
}KFPC_ChannelActionType;

const char* ActionTypeToStr(KFPC_ChannelActionType val);

/**< Voice���ֹ�����ɫ��IVR��AGTONE��CONF */
typedef enum KFPC_VoiceRole
{
	VoiceRole_IVR,				/**< IVR ���ɫ */		
	VoiceRole_AGTONE,			/**< ģ���ź������ */
	VoiceRole_CONF				/**< ����ͨ�� */
}KFPC_VoiceRole;

const char* VoiceRoleToStr(KFPC_VoiceRole val);

typedef enum KFPC_CH_IVRType_t		//ͨ��IVR��Դ����
{	
	CH_IVRType_NULL,	//��Ч
	CH_IVRType_ONE,	//��IVR��Դ
	CH_IVRType_MIX	//������Դ����˫ͨ��������¼����ʱ���õ�,�����ʸ����˵�IVR��Դ
						//CH1--IVR1-IVR2-IVR3--CH2
						//           |
						//			 |
						//		    PRD	
}KFPC_CH_IVRType_t;

const char* IVRTypeToStr(KFPC_CH_IVRType_t val);

typedef struct {
	char			AudioName[KFPC_MAX_AUDIO_NAME];
	unsigned char	AudioCodeID;
} KFPC_AudioCode;


typedef	enum KFPC_QueryIdleChType
{
	KFPC_QueryIdleChType_W		= 0,		// "W"��(�������), 
	KFPC_QueryIdleChType_Z		= 1,		// "Z"��(�������)
	KFPC_QueryIdleChType_Odd	= 2,		// ����������
	KFPC_QueryIdleChType_Even	= 3			// ��ż������
}KFPC_QueryIdleChType;

const char* IdleTypeToStr(unsigned int Type);

typedef struct KFPC_IdleType_Info
{
	KFPC_QueryIdleChType	Type;
	char					IdleTypeName[KFPC_IDLE_TYPE_NAME_LEN];
}KFPC_IdleType_Info;

const char* VoiceStatusToStr(unsigned int val,char* Str);

unsigned int CheckVoiceType(char *pPlayContent);

#endif // KFPC_TServerDef_h__
