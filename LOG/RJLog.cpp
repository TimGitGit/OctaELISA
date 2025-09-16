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
*������־��¼��־
*����һ������������
*���أ�
******/
void CTC_LogManager::CreateLog(unsigned int iSaveDay)
{
	if (m_LogInstance == NULL)
	{
		m_LogInstance = new CTC_LogManager(iSaveDay);
	}
}

/******
*��ȡ��ǰ����־ʵ��
*���أ���־ʵ��
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
*�ر���־ʵ��
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
*ɾ�����ڵ��ļ�
*����һ�������ļ�������
*���أ�
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
//	long lfile = 0;              //�ļ���� 
//	char file[256] = { 0 }, dir[256] = { 0 }, filename[256] = { 0 };      //��ǰĿ¼
//	struct _finddata_t fileinfo; //�ļ���Ϣ
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
*������ļ�
*����һ:����
*������:�ļ�����
*������:����
*������:��ʽ
*������:����
*���أ�
*****/
void CTC_LogManager::OutputFile(int iType, const char *sFile, int iLine, const char *sFormat, ...)
{
	va_list vl;
	char sTime[32] = { 0 };
	time_t ct = time(NULL);
	CreateYMDFile(m_sDir);               //�ж��¿�Ҫɾ���ļ�
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
*��ȡ����·��
*����һ����ǰĿ¼
*����������ǰĿ¼����
*���أ���ǰĿ¼�ַ���,NULLʱ����
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
*��ȡ��ǰ�����յ���
******/
time_t CTC_LogManager::GetYMDSec()
{
	time_t cur = time(NULL);
	struct tm *ctm = localtime(&cur);
	return (cur - ctm->tm_hour * 3600 - ctm->tm_min * 60 - ctm->tm_sec);
}

/******
*������ǰ�ļ�
*����һ����ǰĿ¼
******/
void CTC_LogManager::CreateYMDFile(char *sDir)
{
	char filename[256] = { 0 };
	time_t curSec = GetYMDSec();
	if (abs(curSec - m_tCurDay) >= (24 * 3600))
	{
		m_tCurDay = curSec;
		DelTimeoutFile(m_uSaveDay);             //ɾ����ʱ������ļ�
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