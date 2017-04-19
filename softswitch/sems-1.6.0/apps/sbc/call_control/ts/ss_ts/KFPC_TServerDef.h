#ifndef KFPC_TServerDef_h__
#define KFPC_TServerDef_h__
#include "KFPC_ContactCenterPublicDef.h"
#include "kfpc_tserver_api.h"

/*--------------------------------------------------------------------------------------------------------------------------------
 |  Defines
 *------------------------------------------------------------------------------------------------------------------------------*/
const char			SS_TSERVER_CFG[]				=	"ss_tserver_config.xml";
const unsigned int  KFPC_MAX_EH_NODE				=	1;																	/**< 最大支持EH交换机节点 */
const unsigned int  KFPC_SINGLE_NODE_MAX_VOIP_SPAN	= 64;																	/**< 单节点最大VOIP中继数 */
const unsigned int  KFPC_SINGLE_NODE_MAX_CONF_SPAN	= 32;

const unsigned int KFPC_VOIP_BEGIN_SPAN				= 0;																	/**< VOIP 开始中继数 */
const unsigned int KFPC_VOIP_END_SPAN				= (KFPC_VOIP_BEGIN_SPAN + KFPC_SINGLE_NODE_MAX_VOIP_SPAN - 1);			/**< VOIP 结束中继号 */

const unsigned int KFPC_CONFID_BEGIN_SPAN			= (KFPC_VOIP_END_SPAN + 1);												/**< 会议开始中继号 */
const unsigned int KFPC_CONFID_END_SPAN				= (KFPC_CONFID_BEGIN_SPAN + KFPC_SINGLE_NODE_MAX_CONF_SPAN - 1);		/**< 会议结束中继号 */

const unsigned int KFPC_NODE_MAX_SPAN				= (KFPC_CONFID_END_SPAN + 1);											/**< 单个节点最大SPAN */
const unsigned int KFPC_MAX_SIP_CHANNEL				= (KFPC_SINGLE_NODE_MAX_VOIP_SPAN*KFPC_MAX_CHANNEL);
																													
																															/**< 最大中继数 */
const unsigned int	KFPC_MAX_CHANNEL_NUMBER			=	(KFPC_SINGLE_NODE_MAX_VOIP_SPAN*KFPC_MAX_CHANNEL);								/**< TServer最大的通道号 */
															/**< 单节点最大会议中继数 */


const unsigned int KFPC_MAX_AUDIO_NAME				=	16;																	/**< 语音编码名长度 */
const unsigned int KFPC_IDLE_TYPE_NAME_LEN			=	16;																	/**< 空闲类型名字长度 */

/*--------------------------------------------------------------------------------------------------------------------------------
 |  Types
 *------------------------------------------------------------------------------------------------------------------------------*/
/**
 *	通道类型
 */
typedef enum KFPC_CH_TYPE
{
	CH_TYPE_AG,					/**< 模拟通道 */
	CH_TYPE_DTI,				/**< 数字中继 */
	CH_TYPE_SIP,				/**< SIP通道 */
	CH_TYPE_CONF				/**< 会议通道 */
}KFPC_CH_TYPE;

const char* ChTypeToStr(KFPC_CH_TYPE val);

/**< 连接类型 */
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

/**< Voice三种工作角色：IVR，AGTONE，CONF */
typedef enum KFPC_VoiceRole
{
	VoiceRole_IVR,				/**< IVR 解角色 */		
	VoiceRole_AGTONE,			/**< 模拟信号音检测 */
	VoiceRole_CONF				/**< 会议通道 */
}KFPC_VoiceRole;

const char* VoiceRoleToStr(KFPC_VoiceRole val);

typedef enum KFPC_CH_IVRType_t		//通道IVR资源类型
{	
	CH_IVRType_NULL,	//无效
	CH_IVRType_ONE,	//单IVR资源
	CH_IVRType_MIX	//复合资源，当双通道放音，录音的时候用到,复合资复盖了单IVR资源
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
	KFPC_QueryIdleChType_W		= 0,		// "W"型(纵向查找), 
	KFPC_QueryIdleChType_Z		= 1,		// "Z"型(横向查找)
	KFPC_QueryIdleChType_Odd	= 2,		// 按奇数分配
	KFPC_QueryIdleChType_Even	= 3			// 按偶数分配
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
