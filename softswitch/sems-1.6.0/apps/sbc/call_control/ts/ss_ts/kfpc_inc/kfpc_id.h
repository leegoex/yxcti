
/********************************************************************
 * @data:		2012/09/25
 * @details:	25:9:2012   14:31
 * @file: 		D:\MyProgram\通信库\kfpc_com\kfpc_id.h 
 * @author:		KFPC
 * @brief:		
*********************************************************************/


#ifndef kfpc_id_h__
#define kfpc_id_h__
#include <string.h>

/*--------------------------------------------------------------------------------------------------------------------------------
 |  C++ support
 *------------------------------------------------------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*--------------------------------------------------------------------------------------------------------------------------------
 |  Defines
 *------------------------------------------------------------------------------------------------------------------------------*/
/************************************************************************/
/* 消息ID分段                                                           */
/************************************************************************/
typedef enum KFPC_ID_CLASS_ALLOCATION
{
	/* Common classes */
	KFPC_ID_CLASS_ALLOCATION_COMMON_BEGIN			= 0x0000,			/**< 公共消息ID开始 */
	KFPC_ID_CLASS_ALLOCATION_COMMON_END				= 0x00FF			/**< 公共消息ID结束 */

} KFPC_ID_CLASS_ALLOCATION, *PKFPC_ID_CLASS_ALLOCATION;


#define KFPC_ID_CLASS_COM_INTERNAL				(KFPC_ID_CLASS_ALLOCATION_COMMON_BEGIN + 0x00)	/**< 内消息组ID组 */
#define KFPC_ID_CLASS_COM_API					(KFPC_ID_CLASS_ALLOCATION_COMMON_BEGIN + 0x01)	/**< 通信库API消息组ID */
#define KFPC_ID_CLASS_COM_TSERVER				(KFPC_ID_CLASS_ALLOCATION_COMMON_BEGIN + 0x02)	/**< TServerAPI消息组ID */
#define KFPC_ID_CLASS_COM_CTI					(KFPC_ID_CLASS_ALLOCATION_COMMON_BEGIN + 0x03)	/**< CTI API消息组ID */
#define KFPC_ID_CLASS_COM_AGENT					(KFPC_ID_CLASS_ALLOCATION_COMMON_BEGIN + 0x04)	/**< 坐席接口API消息组ID */
#define KFPC_ID_CLASS_COM_TTS					(KFPC_ID_CLASS_ALLOCATION_COMMON_BEGIN + 0x05)	/**< TTS API消息组ID */
#define KFPC_ID_CLASS_COM_VOICE					(KFPC_ID_CLASS_ALLOCATION_COMMON_BEGIN + 0x06)	/**< 语音处理 API消息组ID */
#define KFPC_ID_CLASS_COM_FAX					(KFPC_ID_CLASS_ALLOCATION_COMMON_BEGIN + 0x07)	/**< 传真处理 API消息组ID */
#define KFPC_ID_CLASS_COM_EH					(KFPC_ID_CLASS_ALLOCATION_COMMON_BEGIN + 0x08)	/**< EH API消息组ID */
#define KFPC_ID_CLASS_COM_LIC					(KFPC_ID_CLASS_ALLOCATION_COMMON_BEGIN + 0x09)	/**< 许可服务消息组ID */
#define	KFPC_ID_CLASS_COM_BILL					(KFPC_ID_CLASS_ALLOCATION_COMMON_BEGIN + 0x0A)	/**< 计费消息组ID */
#define KFPC_ID_CLASS_COM_SMS					(KFPC_ID_CLASS_ALLOCATION_COMMON_BEGIN + 0x0B)	/**< 短信消息组ID */
#define KFPC_ID_CLASS_COM_FAXCONVERT			(KFPC_ID_CLASS_ALLOCATION_COMMON_BEGIN + 0x0C)	/**< 传真转换消息组ID */
#define KFPC_ID_CLASS_COM_GLTSERVER				(KFPC_ID_CLASS_ALLOCATION_COMMON_BEGIN + 0x0D)	/**< GL TSERVER消息组ID */
#define KFPC_ID_CLASS_COM_SIPSERVER				(KFPC_ID_CLASS_ALLOCATION_COMMON_BEGIN + 0x0E)	/**< SIP SERVER消息组ID */
#define KFPC_ID_CLASS_COM_SIPRECORD				(KFPC_ID_CLASS_ALLOCATION_COMMON_BEGIN + 0x0F)	/**< IP RECORD消息组ID */
#define KFPC_ID_CLASS_COM_NODE_CCS				(KFPC_ID_CLASS_ALLOCATION_COMMON_BEGIN + 21)	/**< Node CCS 消息组ID */
#define KFPC_ID_CLASS_COM_NOTIFY				(KFPC_ID_CLASS_ALLOCATION_COMMON_BEGIN + 23)	/**< Notify 消息组ID */

#define KFPC_ID_CLASS_COM_END					(KFPC_ID_CLASS_ALLOCATION_COMMON_END)			/**< 结束 */

#define KFPC_APP_NAME_LEN						16												/**< App type name 长度 */
/*--------------------------------------------------------------------------------------------------------------------------------
 |  Types
 *------------------------------------------------------------------------------------------------------------------------------*/


typedef enum KFPC_APP_TYPE
{
	KFPC_APP_TYPE_UNKNOW = 0,
	KFPC_APP_TYPE_TSERVER = 1,
	KFPC_APP_TYPE_CTI = 2,
	KFPC_APP_TYPE_CCS = 3,
	KFPC_APP_TYPE_AGENT = 4,
	KFPC_APP_TYPE_TTS = 5,
	KFPC_APP_TYPE_VOICE = 6,
	KFPC_APP_TYPE_FAX = 7,
	KFPC_APP_TYPE_ROUTER = 8,
	KFPC_APP_TYPE_IVR = 9,
	KFPC_APP_TYPE_LICENSE = 10,
	KFPC_APP_TYPE_BILL = 11,
	KFPC_APP_TYPE_PBX = 12,
	KFPC_APP_TYPE_SOFTSWITCH = 13,
	KFPC_APP_TYPE_SMS = 14,
	KFPC_APP_TYPE_FAXCONVERT = 15,
	KFPC_APP_TYPE_FAXFLOW = 16,
	KFPC_APP_TYPE_CTRL = 17,
	KFPC_APP_TYPE_NETSERVER = 18,
	KFPC_APP_TYPE_SIPSERVER = 19,
	KFPC_APP_TYPE_TANDEM = 20,
	KFPC_APP_TYPE_NODE_CCS = 21,
	KFPC_APP_TYPE_IPREC = 22,
	KFPC_APP_TYPE_NOTIFY = 23,
	KFPC_APP_TYPE_END = 24
}KFPC_APP_TYPE;

typedef struct KFPC_APP_TYPE_INFO
{
	KFPC_APP_TYPE	Type;
	char			Name[KFPC_APP_NAME_LEN];
}KFPC_APP_TYPE_INFO;


 //KFPC_APP_TYPE AppTypeName2ID(const char* pAppTypeName);

/*--------------------------------------------------------------------------------------------------------------------------------
 |  Global variables
 *------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------------
 |  Macros
 *------------------------------------------------------------------------------------------------------------------------------*/
/*
 * Converts a class Id in the range
 * KFPC_ID_CLASS_ALLOCATION_COMMON_BEGIN - KFPC_ID_CLASS_ALLOCATION_COMMON_END
 * to a readable string
*/

KFPC_APP_TYPE AppTypeName2ID( const char* pAppTypeName );

const char* KFPC_ID_CLASS_COM_TO_STRING( unsigned int in_un32MsgId );

#define KFPC_ID_CLASS_STRING_TO_CLASS_COM_CASE( __MsgGroup )	\
	if( strcmp( in_pszClassId, #__MsgGroup ) == 0 )	\
	{	\
		return __MsgGroup;	\
	}

/*
 |	Macros to generate a message identifier
 */
#define KFPC_MSG_ID_GEN(_nGroup, _nElement)		(((unsigned int)(_nGroup) << 16) + (_nElement))
#define KFPC_MSG_ID_GET_GROUP(_nMsg)			((unsigned int)(_nMsg) >> 16)
#define KFPC_MSG_ID_GET_SUBID(MSGID)			(0xffff & (MSGID))

/*--------------------------------------------------------------------------------------------------------------------------------
 |  Function Prototypes
 *------------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------------------
 |  C++ support
 *------------------------------------------------------------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // kfpc_id_h__

