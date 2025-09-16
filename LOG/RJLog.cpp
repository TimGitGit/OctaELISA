#include "RJLog.h"
#include<io.h>
#include <direct.h>
#include <stdarg.h>
#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <unistd.h>
#include <limits.h>
#endif

static const char *sType[UNKNOW] = { "DEBUG", "INFO", "WARN", "ERROR" };

CTC_LogManager *CTC_LogManager::m_LogInstance = NULL;

/******
*创建日志记录日志
*参数一：保留的天数
*返回：
******/
void CTC_LogManager::CreateLog(unsigned int iSaveDay)
{
	if (m_LogInstance == NULL)
	{
		m_LogInstance = new CTC_LogManager(iSaveDay);
	}
}

/******
*获取当前的日志实例
*返回：日志实例
******/
CTC_LogManager *CTC_LogManager::LogInstance()
{
	if (m_LogInstance == NULL)
	{
		m_LogInstance = new CTC_LogManager(30);
	}
	return m_LogInstance;
}

/******
*关闭日志实例
******/
void CTC_LogManager::CloseLog()
{
	if (m_LogInstance != NULL)
	{
		delete m_LogInstance;
	}
	m_LogInstance = NULL;
}

CTC_LogManager::CTC_LogManager(unsigned int iSaveDay)
{
	GetAbsPath(m_sDir, 256);
	strcat(m_sDir, "log\\");
	if (_access(m_sDir, 0) != 0)
	{
		_mkdir(m_sDir);
	}
	m_uSaveDay = iSaveDay;
	if (m_uSaveDay <= 0)
	{
		m_uSaveDay = 1;
	}
	m_tCurDay = 0;
	m_pOutFile = NULL;
	CreateYMDFile(m_sDir);
}


CTC_LogManager::~CTC_LogManager()
{
	if (m_pOutFile != NULL)
	{
		fclose(m_pOutFile);
	}
	m_pOutFile = NULL;
}

/******
*删除过期的文件
*参数一：保留文件的天数
*返回：
******/
void CTC_LogManager::DelTimeoutFile(unsigned int iDay)
{
	QString dir = QCoreApplication::applicationDirPath() + "/log";
	QDir logDir(dir);
	QStringList filters;
	filters << "*.log";
	logDir.setNameFilters(filters);
	QFileInfoList fileList = logDir.entryInfoList();

	foreach(QFileInfo fileInfo, fileList)
	{
		if (!fileInfo.isDir())
		{
			QDateTime createTime = fileInfo.created();
			QDateTime currentTime = QDateTime::currentDateTime();
			if (createTime.daysTo(currentTime) >= iDay)
			{
				if (QFile::remove(fileInfo.absoluteFilePath()))
				{
					qDebug() << "Removed file: " << fileInfo.absoluteFilePath();
				}
				else
				{
					qDebug() << "Failed to remove file: " << fileInfo.absoluteFilePath();
				}
			}
		}
	}
}
//void CTC_LogManager::DelTimeoutFile(unsigned int iDay)
//{
//	long lfile = 0;              //文件句柄 
//	char file[256] = { 0 }, dir[256] = { 0 }, filename[256] = { 0 };      //当前目录
//	struct _finddata_t fileinfo; //文件信息
//	GetAbsPath(dir, 256);
//	_snprintf(file, 256, "%slog\\*.log", dir);
//	if ((lfile = _findfirst(file, &fileinfo)) != -1)
//	{
//		do
//		{
//			if ((fileinfo.attrib &  _A_SUBDIR) != _A_SUBDIR)
//			{
//				if (abs(time(NULL) - fileinfo.time_create) >= (iDay * 24 * 3600))
//				{
//					_snprintf(filename, 256, "%slog\\%s", dir, fileinfo.name);
//					remove(filename);
//				}
//			}
//
//		} while (_findnext(lfile, &fileinfo) == 0);
//	}
//	_findclose(lfile);
//}

/******
*输出到文件
*参数一:类型
*参数二:文件名称
*参数三:行数
*参数四:格式
*参数五:参数
*返回：
*****/
void CTC_LogManager::OutputFile(int iType, const char *sFile, int iLine, const char *sFormat, ...)
{
	va_list vl;
	char sTime[32] = { 0 };
	time_t ct = time(NULL);
	CreateYMDFile(m_sDir);               //判断下可要删除文件
	va_start(vl, sFormat);
	strftime(sTime, 32, "%Y-%m-%d %H:%M:%S", localtime(&ct));
	if (m_pOutFile != NULL &&
		iType != DEBUG0)
	{
		fprintf(m_pOutFile, "[%s][%s]:FILE:%s,LINE:%d:", sType[iType], sTime, sFile, iLine);
		//fprintf(m_pOutFile, "[%s][%s]:", sType[iType], sTime);
		vfprintf(m_pOutFile, sFormat, vl);
		fprintf(m_pOutFile, "\r\n");
		fflush(m_pOutFile);
	}
	fprintf(stdout, "[%s][%s]:FILE:%s,LINE:%d:", sType[iType], sTime, sFile, iLine);
	vfprintf(stdout, sFormat, vl);
	fprintf(stdout, "\n");
	fflush(stdout);
	va_end(vl);
}

/******
*获取绝对路径
*参数一：当前目录
*参数二：当前目录长度
*返回：当前目录字符串,NULL时出错
******/
char* CTC_LogManager::GetAbsPath(char *sCurPath, int iLen)
{
	//int len = GetModuleFileNameA(NULL, sCurPath, iLen);
	//if (len <= 0)
	//{
	//	return NULL;
	//}
	//strrchr(sCurPath, '\\')[1] = 0x00;
	//return sCurPath;
#ifdef _WIN32
	int len = GetModuleFileNameA(NULL, sCurPath, iLen);
	if (len <= 0)
	{
		return NULL;
	}
	strrchr(sCurPath, '\\')[1] = 0x00;
#elif __linux__
	ssize_t len = readlink("/proc/self/exe", sCurPath, iLen);
	if (len <= 0)
	{
		return NULL;
	}
	sCurPath[len] = '\0';
	char* last_slash = strrchr(sCurPath, '/');
	if (last_slash != nullptr)
	{
		*(last_slash + 1) = '\0';
	}
#endif
	return sCurPath;
}

/******
*获取当前年月日的秒
******/
time_t CTC_LogManager::GetYMDSec()
{
	time_t cur = time(NULL);
	struct tm *ctm = localtime(&cur);
	return (cur - ctm->tm_hour * 3600 - ctm->tm_min * 60 - ctm->tm_sec);
}

/******
*创建当前文件
*参数一：当前目录
******/
void CTC_LogManager::CreateYMDFile(char *sDir)
{
	char filename[256] = { 0 };
	time_t curSec = GetYMDSec();
	if (abs(curSec - m_tCurDay) >= (24 * 3600))
	{
		m_tCurDay = curSec;
		DelTimeoutFile(m_uSaveDay);             //删除超时保存的文件
		struct tm *ctm = localtime(&m_tCurDay);
		if (ctm != NULL)
		{
			_snprintf(filename, 256, "%s%04d-%02d-%02d.log", sDir, ctm->tm_year + 1900, ctm->tm_mon + 1, ctm->tm_mday);
			if (m_pOutFile != NULL)
			{
				fclose(m_pOutFile);
			}
			m_pOutFile = fopen(filename, "ab+");
			if (m_pOutFile == NULL)
			{
				m_pOutFile = stdout;
			}
		}
	}
}