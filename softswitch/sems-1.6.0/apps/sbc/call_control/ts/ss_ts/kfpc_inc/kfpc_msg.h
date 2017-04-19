#ifndef kfpc_msg_h__
#define kfpc_msg_h__
/********************************************************************
 * @data:		2012/09/26
 * @details:	26:9:2012   11:15
 * @file: 		D:\MyProgram\ͨ�ſ�\kfpc_com\kfpc_msg.h 
 * @author:		KFPC
 * @brief:		������Ϣ�ṹ����
*********************************************************************/

/*--------------------------------------------------------------------------------------------------------------------------------
 |  Defines
 *------------------------------------------------------------------------------------------------------------------------------*/
#define MSG_FLAG						0xFEEFEDDE					/**< ��Ϣ��ʶ */
#define	UINTTYPE						(unsigned int) 0XFFFFFFFF	/**< ��Ч32λֵ */
#define ULONGTYPE						(unsigned int)0XFFFFFFFF	/**< ��Ч32λֵ */
#define	USHORTTYPE						(unsigned short)0XFFFF		/**< ��Ч16λֵ */
#define UCHARTYPE						(unsigned char)0XFF			/**< ��Ч8λֵ */
#define KFPC_API_NAME_MAX_LEN			128							/**< ���Ӧ�ó��������� */
#define KFPC_API_LISTEN_PORT_MAX_COUNT	1							/**< ͬʱ�������˿��� */
#define KFPC_MAX_SOCKET_COUNT			65535						/**< �Ǵ�ɹ����Socket�� */
#define KFPC_MAX_SOCKET_ROACTOR			32							/**< ��������� */
#define KFPC_MAX_PASSWD_LEN				64							/**< ������볤�� */
#define	KFPC_MAX_IP_LEN					32							/**<IP ��󳤶� */
#define KFPC_MIN_KEEP_LIVE_COUNT		3	
#define KFPC_DEFAULT_FILTER_COUNT		4							/**< Ĭ�Ϲ��������� */
#define KFPC_DEFAULT_SOCKET_COUNT		32							/**< �����������Socket���� */
#define KFPC_DEFAULT_KEEPLIVETIME_COUNT	6							/**< Ĭ���������� */
#define KFPC_DEFAULT_KEEPLIVETIME		15							/**< Ĭ������ʱ�� */
#define KFPC_DEFAULT_THREAD_POOL_SIZE	4							/**< Ĭ���̳߳ش�С */
#define KFPC_MAX_KEY_LEN				16							/**< ����key���� */
#define KFPC_DEFAULT_LISTEN_PORT		12813						/**< Ĭ�ϵļ����˿� */
#define KFPC_MAX_APP_ID					50000						/**< ����APP ID */
#define KFPC_DEFAULT_MUTTICAST_IP		"224.12.8.13"				/**< Ĭ�϶ಥIP */
#define KFPC_CLIENT_SOCKET_COUNT		16							/**< �ͻ������TCP �� */
#define KFPC_CLIENT_THREAD_POOL_SIZE	4							/**< �ͻ����߳��� */
#define KFPC_MAX_COM_BUF_SIZE			10240						/**< ����ͨ��BUF��С */
#define KFPC_MAX_GUID_LEN				16
#define KFPC_MAX_INTERFACE_COUNT		64							/**< ���������� */
#define KFPC_ONE_LOOP_TIME				5							/**< ����ѭ�����5�� */
#define KFPC_MAX_SEND_COUNT				32							/**< ���ͬʱ���͸��� */
#define	MAX_CONNECT_INDEX				2							/**< ͬһ�������������� */
#define KFPC_RECONNECT_TIMER			5							/**< ������ʱ */	
#define KFPC_DEFAULT_MUTTICAST_PORT		12813						/**< Ĭ�϶ಥ�˿� */
#define KFPC_MAX_MSG_ID_STR_LEN			128							/**< �����ַ�������ID */
#define KFPC_SEMWAITTIMEOUT				5000						/**< �ź�����ʱ�� ����*/
/*--------------------------------------------------------------------------------------------------------------------------------
 |  Types
 *------------------------------------------------------------------------------------------------------------------------------*/


/**
 * ��Ϣ����
 */
typedef enum KFPC_MSG_TYPE
{
	KFPC_MSG_TYPE_FIRST			= 0,
	KFPC_MSG_TYPE_REQUEST		= 1,		/* Bits field so values can be ORed in filters */
	KFPC_MSG_TYPE_RESPONSE		= 2,
	KFPC_MSG_TYPE_EVENT			= 4,
	KFPC_MSG_TYPE_LAST			= 5

} KFPC_MSG_TYPE, *PKFPC_MSG_TYPE;

static const char* MsgTypeToStr(KFPC_MSG_TYPE MsgType)
{
	switch(MsgType)
	{
	case KFPC_MSG_TYPE_REQUEST	:	return "REQUEST";
	case KFPC_MSG_TYPE_RESPONSE	:	return "RESPONSE";
	case KFPC_MSG_TYPE_EVENT	:	return "EVENT";	
	default: return "unknow";
	}
}

//KFPC_MSG_TYPE	IntToMsgType(unsigned int MsgType);
static KFPC_MSG_TYPE IntToMsgType( unsigned int MsgType )
{
	switch(MsgType)
	{
	case 1:return KFPC_MSG_TYPE_REQUEST;
	case 2:return KFPC_MSG_TYPE_RESPONSE;
	case 3:return KFPC_MSG_TYPE_EVENT;
	default: return KFPC_MSG_TYPE_REQUEST;
	}
}

/**
 * ������Ϣͷ 
 */ 
typedef struct KFPC_MSG_HEADER
{
	/*@{*/
	unsigned int		un32MsgFlag;							/**< ��Ϣ��ʶ��ͨ�������ʶʶ�������ǵ���Ϣ����ˮ�����ϵĹ��� */
	unsigned int		un32MsgId;							/**< Must be kept first */
	unsigned int		un32MsgType;						/**< Message type */
	unsigned int		un32Length;							/**< The total length of the message,��������Ϣͷ */
	unsigned int		un32SerialNumber;					/**< This buffer's unique serial number */
	unsigned int		un32UserContext1;					/**< User Ctx #1 (filterable) �û�������1*/
	unsigned int		un32UserContext2;					/**< User Ctx #2 (filterable) �û�������2*/
	unsigned int		un32SrcAPPId;						/**< Unique application identifier ӦAPP ID*/
	unsigned int		un32DstAPPId;						/**< Unique application identifier ӦAPP ID*/
	/*@}*/
} KFPC_MSG_HEADER, *PKFPC_MSG_HEADER;

typedef struct	KFPC_MSG
{
	KFPC_MSG_HEADER	Header;
	unsigned char	Buf[1];
}KFPC_MSG;

/*--------------------------------------------------------------------------------------------------------------------------------
 |  Global variables
 *------------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------------------
 |  Macros
 *------------------------------------------------------------------------------------------------------------------------------*/
#define		KFPC_FORMAT_HEADER(__pHeader, __MsgId, __MsgType, __Length, __UserContext1, __UserContext2)		\
{                                                                                                           \
    (__pHeader)->un32MsgFlag = MSG_FLAG;                                                                      \
	(__pHeader)->un32MsgId = (__MsgId);																		\
	(__pHeader)->un32MsgType = (KFPC_MSG_TYPE)(__MsgType);													\
	(__pHeader)->un32Length = (__Length);																	\
	(__pHeader)->un32SerialNumber = 0;																		\
	(__pHeader)->un32SrcAPPId = 0;																			\
	(__pHeader)->un32DstAPPId = 0;																			\
	(__pHeader)->un32UserContext1 = (__UserContext1);														\
	(__pHeader)->un32UserContext2 = (__UserContext2);														\
}                                                                                                           \

#define KFPC_HEAD_SIZE							sizeof(KFPC_MSG_HEADER)  /**<size of message head */
#define KFPC_MAX_MSG_BODY						KFPC_MAX_COM_BUF_SIZE - KFPC_HEAD_SIZE						/**< �����Ϣ���С */
/*--------------------------------------------------------------------------------------------------------------------------------
 |  Function Prototypes
 *------------------------------------------------------------------------------------------------------------------------------*/
#endif // kfpc_msg_h__

