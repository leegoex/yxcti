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

const int   MAX_REGEX_STR	= 512;	/**< 最大正则字符串长 */

class KFPC_Log;

/**
 *	文件信息类
 */
class CFileInfo
{
public:
	time_t	m_Createtime;	/**< 文件创建日间 */
	time_t GetCreatetime() { return m_Createtime; }
	void SetCreatetime(time_t val) { m_Createtime = val; }

	char	m_Filename[MAX_FILE_NAME_LEN];	/**< 长文件名，包括路径 */

	const char* GetFilename() { return m_Filename; }
	void SetFilename(const char* val) { strncpy(m_Filename, val,MAX_FILE_NAME_LEN-1); }

	CFileInfo():
	m_Createtime(0)
	{
		m_Filename[0] = '\0';
	}
};

/**
 *	定义文件信息类型
 */
typedef list<CFileInfo>				FileInfoList_t;			/**< 文件信息列表类型 */
typedef list<CFileInfo>::iterator	FileInfoListIter_t;		/**< 文件信息列表迭代器类型 */



class KFPC_ScanLogPath :
	public KFPC_ThreadTask
{

protected:
	KFPC_Log*		m_pLog;
	FileInfoList_t	m_FileInfoList;	/**< 用于文件排序 */
	char			m_RegexStr[MAX_REGEX_STR];		/**< 正则匹配字符串 */
	string			m_FileNamePrefix;	/**< 长文件名，包括路径 */
	unsigned int	m_MaxKeepFilesCount;

public:
	KFPC_ScanLogPath(KFPC_Log*	pLog,const char* FileNamePrefix,unsigned int MaxKeepFilesCount);
	~KFPC_ScanLogPath(void);

	/**
	 * Method:    	ScanLogPath
	 * FullName:  	KFPC_ScanLogPath::ScanLogPath
	 * @brief 		扫描日记目录
	 * @return   	void
	 * @pre 		无
	 * @par 		示例
	 * @see 		引用
	 */
	void ScanLogPath();

	virtual void* Svc();

	void AddFileInfo( time_t CreateTime, const char* logfile );
	void DelOldFile();


	const char* TimeToStr( char* pStr,time_t t );

};
#endif // kfpc_scanlogpath_h__

