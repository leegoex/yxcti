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
/* 网络基础函数                                                         */
/************************************************************************/


/**
 * Method:    	InitTcpServer
 * FullName:  	InitTcpServer
 * @brief 		初始化TCP服务器
 * @param[in] unsigned short Port	监听端口
 * @param[out] SOCKET_t * ListenSocket	监听SOCKET
 * @return   	int 成功返回0
 * @pre 		无
 * @par 		示例
 * @see 		引用
 */
int InitTcpServer(unsigned short Port,SOCKET_t* ListenSocket);	/**< 初始化TCP服务器 */	

/**
 * Method:    	InitUDPServer
 * FullName:  	InitUDPServer
 * @brief 		初始化UDP服务
 * @param[in] unsigned short Port
 * @param[out] SOCKET_t * Socket
 * @return   	int 返回0成功
 * @pre 		无
 * @par 		示例
 * @see 		引用
 */
int InitUDPServer(unsigned short Port,SOCKET_t *Socket,unsigned int IP = INADDR_ANY);		/**<初始化一个UDP服务器 */

/**
 * Method:    	ConnectTcp
 * FullName:  	ConnectTcp
 * @brief 		连接TCP服务器
 * @param[in] const char * IP	服务器IP地址
 * @param[in] unsigned short Port	服务器端口
 * @param[out] SOCKET_t * Socket	成功后返回的SOCKET句柄
 * @return   	int
 * @pre 		无
 * @par 		示例
 * @see 		引用
 */
int ConnectTcp(const char* IP,unsigned short Port,SOCKET_t *Socket,int NoBlock = 0 /*阻塞为0,非阻塞1*/);

SOCKET_t	CreateSocket();
void CloseSocket(SOCKET_t Socket);	/**< 关闭SOCKET */

int SetSocketRecvTimeOut(SOCKET_t socket,int Time);
int	SetSocketNoBlock(SOCKET_t tsocket);	/**< 设置SOCKET 为非阻塞 */
int SetSocketKeepLive( SOCKET_t socket,int KEEPINTVL,int KEEPCNT );

/**
 * Method:    	SendDataByMulticast
 * FullName:  	SendDataByMulticast
 * @brief 		发送多播数据包
 * @param[in,out] SOCKET_t server	加入多播的SOCKET
 * @param[in,out] const char * IP	多播IP
 * @param[in,out] unsigned short short Port 多播端口
 * @param[in,out] const char * Buffer 数据缓冲
 * @param[in,out] int BufSize 缓冲大小
 * @return   	int
 * @pre 		无
 * @par 		示例
 * @see 		引用
 */
int SendDataByMulticast( SOCKET_t Socket,const char* IP,unsigned short Port,const char * Buffer,int BufSize );

int SendDataByMulticast(const char* SrcIP,const char* IP,unsigned short Port,const char * Buffer,int BufSize);

SOCKET_t CreateUdpSocketByIp(const char* SrcIP,unsigned short Port);


struct addrinfo *ResolveAddress(char *addr, char *port, int af, int type, int proto);
int GuessIpForVia (int familiy, char *address, int size);

int GetPeerIp(SOCKET_t Socket,char* Ip,unsigned short* Port);

#endif // kfpc_linuxwinnet_h__
