#include "kfpc_linuxwinnet.h"
#include "kfpc_linuxwinapi.h"
#include "kfpc_log.h"
#include "kfpc_logex.h"


unsigned int g_SocketHandleCount = 0;


static KFPC_Mutex	g_LinuxWinSocketMutex;


SOCKET_t CreateSocket()
{
	g_LinuxWinSocketMutex.lock();
	g_SocketHandleCount++;
	SOCKET_t	Ret = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);;
	g_LinuxWinSocketMutex.unlock();

	DEBUG_LOG(0,"SocketID:%d,Socket handle count:%d",Ret,g_SocketHandleCount);
	return Ret;
}


int InitTcpServer( unsigned short Port,SOCKET_t* ListenSocket )
{
	struct sockaddr_in  local;    

#ifndef LINUX   

	WSADATA             wsd;

	if(WSAStartup(MAKEWORD(2,2), &wsd) == SOCKET_ERROR )
	{   			
		return SOCKET_ERROR;
	}

#endif

	*ListenSocket = CreateSocket();

	if((*ListenSocket) == SOCKET_ERROR )
	{
		return SOCKET_ERROR;
	}

	int option = 1;  

	if ( setsockopt ( *ListenSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&option,  
		sizeof( option ) ) < 0 )  
	{  
		return SOCKET_ERROR;
	}  

	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_family = AF_INET;
	local.sin_port = htons(Port);

	if(bind(*ListenSocket, (struct sockaddr *)&local,sizeof(local)) == SOCKET_ERROR)
	{   
		CloseSocket(*ListenSocket);
		return SOCKET_ERROR;
	}

	listen(*ListenSocket,100);

	return 0;
}

int InitUDPServer( unsigned short Port,SOCKET_t *Socket,unsigned int IP )
{

	struct      sockaddr_in local;
#ifndef LINUX   

	WSADATA             wsd;

	if(WSAStartup(MAKEWORD(2,2), &wsd) == SOCKET_ERROR )
	{   			
		return SOCKET_ERROR;
	}

#endif
	*Socket = socket(AF_INET, SOCK_DGRAM, 0);

	if ((*Socket) < 0)
	{
		return SOCKET_ERROR;
	}

	g_LinuxWinSocketMutex.lock();
	g_SocketHandleCount++;
	g_LinuxWinSocketMutex.unlock();

	local.sin_family = AF_INET;
	local.sin_port = htons(Port);
	local.sin_addr.s_addr = IP;;


	if(Port > 10000)
	{
		int option = 1;  

		if ( setsockopt((*Socket), SOL_SOCKET, SO_REUSEADDR, (char*)&option,  
			sizeof( option ) ) < 0 )  
		{  
			int Ret = GetLastErr();
			CloseSocket(*Socket);
			return SOCKET_ERROR;
		}  
	}

	if (bind(*Socket, ( struct sockaddr *)&local, sizeof(local)) == SOCKET_ERROR)
	{
		int ret = GetLastErr();
		CloseSocket(*Socket);
		return SOCKET_ERROR;
	}


	return 0;
}

int ConnectTcp( const char* IP,unsigned short Port,SOCKET_t *Socket ,int NoBlock /*阻塞为0,非阻塞1*/)
{

	struct sockaddr_in  server;

	(*Socket) = CreateSocket();
	if ((*Socket) < 0)
	{
		return SOCKET_ERROR;
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(Port);
	if((server.sin_addr.s_addr = inet_addr(IP)) < 0)
	{
		CloseSocket(*Socket);
		return SOCKET_ERROR;
	}

	//Winsock的Nagle算法将降低小数据报的发送速度，而系统默认是使用Nagle算法
#ifdef _NODELAY
	{
		int bNodelay = 1; 
		setsockopt( sClient, IPPROTO_TCP, TCP_NODELAY, (char *)&bNodelay, sizeof(bNodelay));//不采用延时算法 
	}
#endif

	if(NoBlock)
	{
		SetSocketNoBlock(*Socket);
	}

	if (connect((*Socket), (struct sockaddr *)&server,sizeof(server)) == SOCKET_ERROR)
	{
		CloseSocket((*Socket));
		return SOCKET_ERROR;
	}

	return 0;
}

void CloseSocket(SOCKET_t Socket)	/**< 关闭SOCKET */
{
	if(Socket != -1)
	{

		g_LinuxWinSocketMutex.lock();
		g_SocketHandleCount--;

		int Ret = 0;
#ifdef LINUX    
		close(Socket);
#else
		Ret = closesocket(Socket);       
#endif
		g_LinuxWinSocketMutex.unlock();
	}

	DEBUG_LOG(0,"SocketID:%d,Socket handle count:%d",Socket,g_SocketHandleCount);
}

int	SetSocketNoBlock(SOCKET_t tsocket)	/**< 设置SOCKET 为非阻塞 */
{
#ifdef LINUX

	int	flag = fcntl(tsocket,F_GETFL,0);
	if(flag < 0 )
	{ 
		return SOCKET_ERROR; 
	}

	if(fcntl(tsocket,F_SETFL,flag|O_NONBLOCK) < 0)
	{
		return SOCKET_ERROR;
	}

#else

	unsigned long NonBlock = 1;

	if (ioctlsocket(tsocket, FIONBIO, &NonBlock) == SOCKET_ERROR)
	{ 
		return SOCKET_ERROR; 
	}

#endif

	return 0;
}



int SendDataByMulticast( SOCKET_t Socket,const char* IP,unsigned short Port,const char * Buffer,int BufSize )
{

	struct sockaddr_in	remote;	

	remote.sin_family      =	AF_INET;
	remote.sin_port        =	htons(Port);

	if((remote.sin_addr.s_addr = inet_addr(IP)) < 0)
	{		
		return SOCKET_ERROR;
	}


	int ret = sendto(Socket,Buffer,BufSize,0,(struct sockaddr*)&remote,sizeof(remote));
	if(ret> 0)
	{
		return 0;
	}
	else
	{
		return ret;
	}
}

int SendDataByMulticast(const char* SrcIP,const char* IP,unsigned short Port,const char * Buffer,int BufSize )
{
	int Ret = 0;
	 SOCKET_t    Socket;

	//创建一个Socket
	Socket = socket(AF_INET, SOCK_DGRAM, 0);

	if (Socket < 0)
	{        
		return -1;
	}

	do 
	{

		struct      sockaddr_in local;


		local.sin_family = AF_INET;
		local.sin_port = 0;
		local.sin_addr.s_addr = inet_addr(SrcIP);

		if (bind(Socket, ( struct sockaddr *)&local, sizeof(local)) == SOCKET_ERROR)
		{
			Ret = SOCKET_ERROR;
			break;
		}


		struct sockaddr_in	remote;	

		remote.sin_family      =	AF_INET;
		remote.sin_port        =	htons(Port);

		if((remote.sin_addr.s_addr = inet_addr(IP)) < 0)
		{		
			return SOCKET_ERROR;
		}

		Ret = sendto(Socket,Buffer,BufSize,0,(struct sockaddr*)&remote,sizeof(remote));
	} while (0);


#ifdef LINUX    
	close(Socket);
#else
	closesocket(Socket);       
#endif

	if(Ret> 0)
	{
		return 0;
	}
	else
	{
		return Ret;
	}
}


struct addrinfo *ResolveAddress(char *addr, char *port, int af, int type, int proto)
{
	struct addrinfo hints,
		*res = NULL;
	int             rc;

	memset(&hints, 0, sizeof(hints));
	hints.ai_flags  = ((addr) ? 0 : AI_PASSIVE);
	hints.ai_family = af;
	hints.ai_socktype = type;
	hints.ai_protocol = proto;

	rc = getaddrinfo(
		addr,
		port,
		&hints,
		&res
		);
	if (rc != 0)
	{
		printf("Invalid address %s, getaddrinfo failed: %d\n", addr, rc);
		return NULL;
	}
	return res;
}

#ifdef LINUX

#include <ifaddrs.h>
#include <net/if.h>

/* This is a portable way to find the default gateway.
 * The ip of the default interface is returned.
 */
static int
ppl_dns_default_gateway_ipv4 (char *address, int size)
{
#ifdef __APPLE_CC__
  int len;
#else
  unsigned int len;
#endif
  int sock_rt, on = 1;
  struct sockaddr_in iface_out;
  struct sockaddr_in remote;

  memset (&remote, 0, sizeof (struct sockaddr_in));

  remote.sin_family = AF_INET;
  remote.sin_addr.s_addr = inet_addr ("217.12.3.11");
  remote.sin_port = htons (11111);

  memset (&iface_out, 0, sizeof (iface_out));
  sock_rt = socket (AF_INET, SOCK_DGRAM, 0);

  if (setsockopt (sock_rt, SOL_SOCKET, SO_BROADCAST, &on, sizeof (on)) == -1)
    {
      perror ("DEBUG: [get_output_if] setsockopt(SOL_SOCKET, SO_BROADCAST");
      close (sock_rt);
      snprintf(address, size, "127.0.0.1");
      return -1;
    }

  if (connect
      (sock_rt, (struct sockaddr *) &remote, sizeof (struct sockaddr_in)) == -1)
    {
      perror ("DEBUG: [get_output_if] connect");
      close (sock_rt);
      snprintf(address, size, "127.0.0.1");
      return -1;
    }

  len = sizeof (iface_out);
  if (getsockname (sock_rt, (struct sockaddr *) &iface_out, &len) == -1)
    {
      perror ("DEBUG: [get_output_if] getsockname");
      close (sock_rt);
      snprintf(address, size, "127.0.0.1");
      return -1;
    }

  close (sock_rt);
  if (iface_out.sin_addr.s_addr == 0)
    {                           /* what is this case?? */
      snprintf(address, size, "127.0.0.1");
      return -1;
    }
  strncpy (address, inet_ntoa (iface_out.sin_addr), size - 1);
  return 0;
}


/* This is a portable way to find the default gateway.
 * The ip of the default interface is returned.
 */
static int
ppl_dns_default_gateway_ipv6 (char *address, int size)
{
#ifdef __APPLE_CC__
  int len;
#else
  unsigned int len;
#endif
  int sock_rt, on = 1;
  struct sockaddr_in6 iface_out;
  struct sockaddr_in6 remote;

  memset (&remote, 0, sizeof (struct sockaddr_in6));

  remote.sin6_family = AF_INET6;
  inet_pton (AF_INET6, "2001:638:500:101:2e0:81ff:fe24:37c6", &remote.sin6_addr);
  remote.sin6_port = htons (11111);

  memset (&iface_out, 0, sizeof (iface_out));
  sock_rt = socket (AF_INET6, SOCK_DGRAM, 0);

  if (setsockopt (sock_rt, SOL_SOCKET, SO_BROADCAST, &on, sizeof (on)) == -1)
    {
      perror ("DEBUG: [get_output_if] setsockopt(SOL_SOCKET, SO_BROADCAST");
      close (sock_rt);
      return -1;
    }

  if (connect
      (sock_rt, (struct sockaddr *) &remote, sizeof (struct sockaddr_in6)) == -1)
    {
      perror ("DEBUG: [get_output_if] connect");
      close (sock_rt);
      return -1;
    }

  len = sizeof (iface_out);
  if (getsockname (sock_rt, (struct sockaddr *) &iface_out, &len) == -1)
    {
      perror ("DEBUG: [get_output_if] getsockname");
      close (sock_rt);
      return -1;
    }
  close (sock_rt);

  if (iface_out.sin6_addr.s6_addr == 0)
    {                           /* what is this case?? */
      return -1;
    }
  inet_ntop (AF_INET6, (const void *) &iface_out.sin6_addr, address, size - 1);
  return 0;
}

static int
	default_gateway_with_getifaddrs (int type, char *address, int size)
{
	struct ifaddrs *ifp;

	struct ifaddrs *ifpstart;

	int ret = -1;

	if (getifaddrs (&ifpstart) < 0) {
		return -1;
	}

	unsigned int InAddr = inet_addr(address);	

	for (ifp = ifpstart; ifp != NULL; ifp = ifp->ifa_next) {
		if (ifp->ifa_addr && ifp->ifa_addr->sa_family == type && (ifp->ifa_flags & IFF_RUNNING) && !(ifp->ifa_flags & IFF_LOOPBACK)) 
		{

			unsigned int NetMask = ((sockaddr_in*)ifp->ifa_netmask)->sin_addr.s_addr;	
			unsigned int OutNetAddr = ((sockaddr_in*)ifp->ifa_addr)->sin_addr.s_addr;

			OutNetAddr = OutNetAddr & NetMask;
			unsigned int InNetAddr = NetMask & InAddr;

			if(OutNetAddr == InNetAddr)
			{
				getnameinfo (ifp->ifa_addr, (type == AF_INET6) ? sizeof (struct sockaddr_in6) : sizeof (struct sockaddr_in), address, size, NULL, 0, NI_NUMERICHOST);
				return 0;
			}


		}
	}

	strcpy(address,"0.0.0.0");

	freeifaddrs (ifpstart);
	return -1;
}

#endif

int GuessIpForVia( int familiy, char *address, int size )
{
#ifdef LINUX
	int Ret = default_gateway_with_getifaddrs(familiy,address,size);;

	DEBUG_LOG(0,"address:%s",address);

	if(Ret < 0)
	{
		if (familiy == AF_INET6)
		{
			Ret = ppl_dns_default_gateway_ipv6 (address, size);
		} else
		{
			Ret = ppl_dns_default_gateway_ipv4 (address, size);
		}
	}


	return Ret;

#else
	struct addrinfo *addrf = NULL;

	addrf = ResolveAddress(address, "0", familiy, SOCK_DGRAM, IPPROTO_UDP);
	if (addrf == NULL)
	{
		printf("Unable to resolve the bind address!\n");
		return -1;
	}



	SOCKET sock;
	SOCKADDR_STORAGE local_addr;
	DWORD local_addr_len = 0;

	sock = socket(addrf->ai_family, addrf->ai_socktype, addrf->ai_protocol);
	if (sock == INVALID_SOCKET)
	{
		fprintf(stderr, "socket failed: %d\n", WSAGetLastError());
		return -1;
	}

	if(WSAIoctl(sock,SIO_ROUTING_INTERFACE_QUERY, addrf->ai_addr, addrf->ai_addrlen,
		&local_addr, sizeof(local_addr), &local_addr_len, NULL, NULL) != 0)
	{
		closesocket(sock);
		freeaddrinfo(addrf);
		snprintf(address, size, "127.0.0.1");
		return -1;
	}

	closesocket(sock);
	freeaddrinfo(addrf);

	if(getnameinfo((const struct sockaddr*)&local_addr,
		local_addr_len,address, size, NULL, 0, NI_NUMERICHOST))
	{
		snprintf(address, size, "127.0.0.1");
		return -1;
	}

	return 0;
#endif
}

int SetSocketRecvTimeOut( SOCKET_t socket,int millisecond )
{
#ifdef WIN32
	//设置阻塞等时间

	int ret = setsockopt(   socket,   SOL_SOCKET,   SO_RCVTIMEO,   (char*)&millisecond,   sizeof(millisecond));   

	if (ret == SOCKET_ERROR)
	{
		printf("setsockopt() failed with error code %d\n", WSAGetLastError());
		return -1;
	}

#else
	struct timeval tv;
	
	tv.tv_usec = (millisecond%1000)*1000;
	tv.tv_sec = millisecond/1000;  

	setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO,(struct timeval *)&tv,sizeof(struct timeval));
#endif
	return 0;
}


int SetSocketKeepLive( SOCKET_t socket,int KEEPINTVL,int KEEPCNT )
{
	int keepAlive = 1;
	int Ret = setsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, (char*)&keepAlive, sizeof(keepAlive));

	if(Ret != 0)
	{
		printf("setsockopt SO_KEEPALIVE fail.\n");
		return -1;
	}

#ifdef WIN32

	struct tcp_keepalive keepin;
	struct tcp_keepalive keepout;

	keepin.keepaliveinterval=KEEPINTVL*1000;	
	keepin.keepalivetime= KEEPINTVL*1000*KEEPCNT;	
	keepin.onoff=1;

	DWORD bytesnum;  

	Ret = WSAIoctl(socket,SIO_KEEPALIVE_VALS,	&keepin,sizeof(keepin),	&keepout,sizeof(keepout),&bytesnum,NULL,NULL);

	if(Ret != 0)
	{
		printf("setsockopt SIO_KEEPALIVE_VALS fail.\n");
		return -1;
	}

#else

	Ret = setsockopt(socket, SOL_TCP, TCP_KEEPIDLE, (void *)&KEEPINTVL, sizeof(KEEPINTVL));
	if(Ret != 0)
	{
		printf("setsockopt TCP_KEEPIDLE fail.\n");
		return -1;
	}

	Ret = setsockopt(socket, SOL_TCP, TCP_KEEPINTVL, (void *)&KEEPINTVL, sizeof(KEEPINTVL));
	if(Ret != 0)
	{
		printf("setsockopt TCP_KEEPINTVL fail.\n");
		return -1;
	}

	Ret = setsockopt(socket, SOL_TCP, TCP_KEEPCNT, (void *)&KEEPCNT, sizeof(KEEPCNT));

	if(Ret != 0)
	{
		printf("setsockopt TCP_KEEPCNT fail.\n");
		return -1;
	}
#endif

	return 0;
}


SOCKET_t CreateUdpSocketByIp( const char* SrcIP,unsigned short Port )
{
	SOCKET_t    Socket;

	//创建一个Socket
	Socket = socket(AF_INET, SOCK_DGRAM, 0);

	if (Socket < 0)
	{      
		ERROR_LOG(0,"SrcIP:%s,Port:%u",SrcIP,Port);
		return -1;
	}

	struct      sockaddr_in local;


	local.sin_family = AF_INET;
	local.sin_port = htons(Port);
	local.sin_addr.s_addr = inet_addr(SrcIP);

	if (bind(Socket, ( struct sockaddr *)&local, sizeof(local)) == SOCKET_ERROR)
	{
#ifdef LINUX    
		close(Socket);
#else
		closesocket(Socket);       
#endif
		return -1;
	}
	else
	{
		INFO_LOG(0,"SrcIP:%s,Port:%u",SrcIP,Port);
		return Socket;
	}
}

int GetPeerIp( SOCKET_t Socket,char* Ip ,unsigned short* Port)
{

	struct	sockaddr		SocketAddr;	
	memset(&SocketAddr,0,sizeof(SocketAddr));

	socklen_t RemoteAddrLen = sizeof(SocketAddr);

	struct	sockaddr_in*	pRemoteAddrIn = (struct	sockaddr_in*)&SocketAddr;

	if(getpeername(Socket,&SocketAddr,&RemoteAddrLen) == 0)
	{

		strcpy(Ip,inet_ntoa(pRemoteAddrIn->sin_addr));
		*Port= ntohs(pRemoteAddrIn->sin_port);

		return 0;
	}
	else
	{
		return -1;
	}	
}