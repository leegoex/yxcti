#include "kfpc_getmac.h"
#include "kfpc_linuxwinnet.h"
#include "kfpc_linuxwinapi.h"
#include <stdio.h>

#ifdef LINUX
#include <sys/types.h> 
//#include <sys/stropts.h> 
#include <stdio.h> 
#include <sys/types.h> 
#include <sys/param.h> 
#include <unistd.h>
//#include <stropts.h>

#include <sys/ioctl.h> 
#include <sys/socket.h> 
#include <net/if.h> 
#include <netinet/in.h> 
#include <net/if_arp.h>

#include <arpa/inet.h>

#endif

#ifdef SOLARIS 
#include <sys/sockio.h> 
#endif 

#ifdef WIN32
#include <Iphlpapi.h>
#endif

#ifdef WIN32
#pragma warning (disable: 4996) 
#endif

int GetLocalMac(char MacList[][MAXMACLEN],char IPlist[][MAXIPLEN],char ethName[][MAXethNameLen],unsigned int* MacCount,bool FilterIP0)
{
#ifdef WIN32
	unsigned long ValidInterfaceCount=0;
	
	PIP_ADAPTER_INFO pInfo=NULL,pInfoTemp=NULL;
	unsigned long ulSize=0;


	GetAdaptersInfo(pInfo,&ulSize);//第一次调用，获取缓冲区大小

	pInfoTemp=pInfo=(PIP_ADAPTER_INFO)new(char[ulSize]);

	GetAdaptersInfo(pInfo,&ulSize);

	while(pInfo != NULL)
	{

		PIP_ADDR_STRING pAddTemp=&(pInfo->IpAddressList);
		
		do 
		{
			if(strcmp(pAddTemp->IpAddress.String,"0.0.0.0") != 0 || !FilterIP0)
			{
				strcpy(ethName[ValidInterfaceCount],pInfo-> AdapterName);
				strcpy(IPlist[ValidInterfaceCount],pAddTemp->IpAddress.String);

				sprintf(MacList[ValidInterfaceCount],"%02x:%02x:%02x:%02x:%02x:%02x", 
					(unsigned char)pInfo->Address[0], 
					(unsigned char)pInfo->Address[1], 
					(unsigned char)pInfo->Address[2], 
					(unsigned char)pInfo->Address[3], 
					(unsigned char)pInfo->Address[4], 
					(unsigned char)pInfo->Address[5]); 




				ValidInterfaceCount++;
			}
		} while ((pAddTemp = pAddTemp->Next) != NULL);


		
		pInfo=pInfo->Next;
	}

	*MacCount = ValidInterfaceCount;

	delete pInfoTemp;

return 0;

#endif

#ifdef LINUX

	register int	fd = 0, 
					intrface = 0;
					//retn = 0; 
	
	struct ifreq buf[MAXINTERFACES]; 

	//struct arpreq arp; 
	struct ifconf ifc; 
	unsigned int ValidInterfaceCount = 0;

	if ((fd = socket (AF_INET, SOCK_DGRAM, 0)) >= 0) 
	{ 
		ifc.ifc_len = sizeof(buf); 
		ifc.ifc_req = buf; 

		if (!ioctl (fd, SIOCGIFCONF , (char *) &ifc)) 
		{ 
			intrface = ifc.ifc_len / sizeof (struct ifreq); 
			struct    sockaddr_in* IPAddr = NULL;   

			for(int i=0;i<intrface;i++)
			{
				IPAddr = (struct sockaddr_in*)(&buf[i].ifr_addr);

				if(strcmp(inet_ntoa(IPAddr->sin_addr),"0.0.0.0") != 0 || !FilterIP0)
				{
					strcpy(ethName[ValidInterfaceCount],buf[i].ifr_name);					
					strcpy(IPlist[ValidInterfaceCount],inet_ntoa(IPAddr->sin_addr));


					if (!(ioctl (fd, SIOCGIFHWADDR, (char *) &buf[i])))
					{

						sprintf(MacList[ValidInterfaceCount],"%02x:%02x:%02x:%02x:%02x:%02x",
							(unsigned char)buf[i].ifr_hwaddr.sa_data[0],
							(unsigned char)buf[i].ifr_hwaddr.sa_data[1],
							(unsigned char)buf[i].ifr_hwaddr.sa_data[2],
							(unsigned char)buf[i].ifr_hwaddr.sa_data[3],
							(unsigned char)buf[i].ifr_hwaddr.sa_data[4],
							(unsigned char)buf[i].ifr_hwaddr.sa_data[5]);

					}
					
		
					ValidInterfaceCount++;
				}


			}

			*MacCount = ValidInterfaceCount;
		}

		close(fd);

		return 0;
	}
	else
	{
		return -1;
	}

#endif

}
