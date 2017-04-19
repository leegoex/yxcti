// KFPC_TServer.cpp : 定义控制台应用程序的入口点。
//
#include "KFPC_TServerMain.h"
#include "kfpc_linuxwinapi.h"
static	bool	g_Run = true;

#ifdef WIN32

int WINAPI HandlerRoutine(unsigned long dwCtrlType)
{
	switch(dwCtrlType) 
	{
	case CTRL_C_EVENT: 
	case CTRL_BREAK_EVENT: 
	case CTRL_CLOSE_EVENT: 
	case CTRL_LOGOFF_EVENT: 
	case CTRL_SHUTDOWN_EVENT:
		{
			TServerClose();
			g_Run = false;
			return false; 
		}
	default: 
		return true; 
	}
	return true; 
}
#else
void signalprocess(int s)
{	 
	TServerClose();
	g_Run = false;
}
#endif

void AutoClose()
{
#ifdef LINUX
	signal(SIGHUP,SIG_IGN);
	signal(SIGINT,signalprocess);
	signal(SIGQUIT,signalprocess);
	signal(SIGKILL,signalprocess);
	signal(SIGPIPE,SIG_IGN);
	signal(SIGALRM,SIG_IGN);
	signal(SIGVTALRM,SIG_IGN);	
	signal(SIGBUS,SIG_IGN);
	signal(SIGTERM,SIG_IGN);
	signal(SIGCLD,SIG_IGN);
	signal(SIGILL,SIG_IGN);
	signal(SIGABRT,SIG_IGN);
	signal(SIGFPE,SIG_IGN);  
#else
	SetConsoleCtrlHandler(HandlerRoutine,true);
#endif
}

int main(int argc, char* argv[])
{


	AutoClose();
	TServerMain(NULL);
	while(g_Run)	Sleep(20);
	


	return 0;
}

