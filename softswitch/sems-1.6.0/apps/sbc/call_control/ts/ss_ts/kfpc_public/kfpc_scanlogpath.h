#ifndef kfpc_scanlogpath_h__
#define kfpc_scanlogpath_h__

#ifdef WIN32
#pragma warning (disable: 4996) 
#endif
#include <string>
#include "kfpc_threadtask.h"
#include "kfpc_linuxwinapi.h"

#include <list>
using namespace std;

const int   MAX_REGEX_STR	= 512;	/**< ��������ַ����� */

class KFPC_Log;

/**
 *	�ļ���Ϣ��
 */
class CFileInfo
{
public:
	time_t	m_Createtime;	/**< �ļ������ռ� */
	time_t GetCreatetime() { return m_Createtime; }
	void SetCreatetime(time_t val) { m_Createtime = val; }

	char	m_Filename[MAX_FILE_NAME_LEN];	/**< ���ļ���������·�� */

	const char* GetFilename() { return m_Filename; }
	void SetFilename(const char* val) { strncpy(m_Filename, val,MAX_FILE_NAME_LEN-1); }

	CFileInfo():
	m_Createtime(0)
	{
		m_Filename[0] = '\0';
	}
};

/**
 *	�����ļ���Ϣ����
 */
typedef list<CFileInfo>				FileInfoList_t;			/**< �ļ���Ϣ�б����� */
typedef list<CFileInfo>::iterator	FileInfoListIter_t;		/**< �ļ���Ϣ�б���������� */



class KFPC_ScanLogPath :
	public KFPC_ThreadTask
{

protected:
	KFPC_Log*		m_pLog;
	FileInfoList_t	m_FileInfoList;	/**< �����ļ����� */
	char			m_RegexStr[MAX_REGEX_STR];		/**< ����ƥ���ַ��� */
	string			m_FileNamePrefix;	/**< ���ļ���������·�� */
	unsigned int	m_MaxKeepFilesCount;

public:
	KFPC_ScanLogPath(KFPC_Log*	pLog,const char* FileNamePrefix,unsigned int MaxKeepFilesCount);
	~KFPC_ScanLogPath(void);

	/**
	 * Method:    	ScanLogPath
	 * FullName:  	KFPC_ScanLogPath::ScanLogPath
	 * @brief 		ɨ���ռ�Ŀ¼
	 * @return   	void
	 * @pre 		��
	 * @par 		ʾ��
	 * @see 		����
	 */
	void ScanLogPath();

	virtual void* Svc();

	void AddFileInfo( time_t CreateTime, const char* logfile );
	void DelOldFile();


	const char* TimeToStr( char* pStr,time_t t );

};
#endif // kfpc_scanlogpath_h__

