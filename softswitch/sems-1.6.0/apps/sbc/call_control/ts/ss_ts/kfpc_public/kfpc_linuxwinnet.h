#ifndef kfpc_linuxwinnet_h__
#define kfpc_linuxwinnet_h__


#ifdef WIN32
//#pragma comment(lib, "libcmt.lib")
#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>	
#include <ws2tcpip.h>
#include <mstcpip.h>
typedef int             socklen_t ;
typedef SOCKET          SOCKET_t; 

#else

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
typedef int             SOCKET_t;
#define SOCKET int
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
typedef int             SOCKET_t;

#endif


/************************************************************************/
/* �����������                                                         */
/************************************************************************/


/**
 * Method:    	InitTcpServer
 * FullName:  	InitTcpServer
 * @brief 		��ʼ��TCP������
 * @param[in] unsigned short Port	�����˿�
 * @param[out] SOCKET_t * ListenSocket	����SOCKET
 * @return   	int �ɹ�����0
 * @pre 		��
 * @par 		ʾ��
 * @see 		����
 */
int InitTcpServer(unsigned short Port,SOCKET_t* ListenSocket);	/**< ��ʼ��TCP������ */	

/**
 * Method:    	InitUDPServer
 * FullName:  	InitUDPServer
 * @brief 		��ʼ��UDP����
 * @param[in] unsigned short Port
 * @param[out] SOCKET_t * Socket
 * @return   	int ����0�ɹ�
 * @pre 		��
 * @par 		ʾ��
 * @see 		����
 */
int InitUDPServer(unsigned short Port,SOCKET_t *Socket,unsigned int IP = INADDR_ANY);		/**<��ʼ��һ��UDP������ */

/**
 * Method:    	ConnectTcp
 * FullName:  	ConnectTcp
 * @brief 		����TCP������
 * @param[in] const char * IP	������IP��ַ
 * @param[in] unsigned short Port	�������˿�
 * @param[out] SOCKET_t * Socket	�ɹ��󷵻ص�SOCKET���
 * @return   	int
 * @pre 		��
 * @par 		ʾ��
 * @see 		����
 */
int ConnectTcp(const char* IP,unsigned short Port,SOCKET_t *Socket,int NoBlock = 0 /*����Ϊ0,������1*/);

SOCKET_t	CreateSocket();
void CloseSocket(SOCKET_t Socket);	/**< �ر�SOCKET */

int SetSocketRecvTimeOut(SOCKET_t socket,int Time);
int	SetSocketNoBlock(SOCKET_t tsocket);	/**< ����SOCKET Ϊ������ */
int SetSocketKeepLive( SOCKET_t socket,int KEEPINTVL,int KEEPCNT );

/**
 * Method:    	SendDataByMulticast
 * FullName:  	SendDataByMulticast
 * @brief 		���Ͷಥ���ݰ�
 * @param[in,out] SOCKET_t server	����ಥ��SOCKET
 * @param[in,out] const char * IP	�ಥIP
 * @param[in,out] unsigned short short Port �ಥ�˿�
 * @param[in,out] const char * Buffer ���ݻ���
 * @param[in,out] int BufSize �����С
 * @return   	int
 * @pre 		��
 * @par 		ʾ��
 * @see 		����
 */
int SendDataByMulticast( SOCKET_t Socket,const char* IP,unsigned short Port,const char * Buffer,int BufSize );

int SendDataByMulticast(const char* SrcIP,const char* IP,unsigned short Port,const char * Buffer,int BufSize);

SOCKET_t CreateUdpSocketByIp(const char* SrcIP,unsigned short Port);


struct addrinfo *ResolveAddress(char *addr, char *port, int af, int type, int proto);
int GuessIpForVia (int familiy, char *address, int size);

int GetPeerIp(SOCKET_t Socket,char* Ip,unsigned short* Port);

#endif // kfpc_linuxwinnet_h__
