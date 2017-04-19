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
		exit(0);			//�Ǹ����̣����������� 
	else if(pid< 0) 
		exit(1);			//forkʧ�ܣ��˳� 
	//�ǵ�һ�ӽ��̣���̨����ִ�� 

	setsid();				//��һ�ӽ��̳�Ϊ�µĻỰ�鳤�ͽ����鳤 
	//��������ն˷��� 
	if(pid=fork()) 
		exit(0);			//�ǵ�һ�ӽ��̣�������һ�ӽ��� 
	else if(pid< 0) 
		exit(1);			//forkʧ�ܣ��˳� 
	//�ǵڶ��ӽ��̣����� 
	//�ڶ��ӽ��̲����ǻỰ�鳤 

	chdir("/tmp");			//�ı乤��Ŀ¼��/tmp 
	umask(0);				//�����ļ�������ģ 

	return; 
}


KFPC_LinuxDaemon::~KFPC_LinuxDaemon(void)
{
}
#endif
