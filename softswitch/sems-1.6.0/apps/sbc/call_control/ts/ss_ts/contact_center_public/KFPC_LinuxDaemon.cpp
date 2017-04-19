#include "KFPC_LinuxDaemon.h"
#ifdef LINUX_SERVICE
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

KFPC_LinuxDaemon::KFPC_LinuxDaemon(void)
{	
	int pid		= 0; 
	int i		= 0	; 

	if(pid=fork()) 
		exit(0);			//是父进程，结束父进程 
	else if(pid< 0) 
		exit(1);			//fork失败，退出 
	//是第一子进程，后台继续执行 

	setsid();				//第一子进程成为新的会话组长和进程组长 
	//并与控制终端分离 
	if(pid=fork()) 
		exit(0);			//是第一子进程，结束第一子进程 
	else if(pid< 0) 
		exit(1);			//fork失败，退出 
	//是第二子进程，继续 
	//第二子进程不再是会话组长 

	chdir("/tmp");			//改变工作目录到/tmp 
	umask(0);				//重设文件创建掩模 

	return; 
}


KFPC_LinuxDaemon::~KFPC_LinuxDaemon(void)
{
}
#endif
