#ifndef __DATABASE_LOG_H__
#define __DATABASE_LOG_H__
#include <time.h>
#include <stdio.h>
#include <QString>
#include <QCoreApplication>
#include <QDir>
#include <QDateTime>
#include <QDebug>
enum
{
	DEBUG0,
	INFO0,
	WARN0,
	ERROR0,
	UNKNOW
};

class CTC_LogManager
{
public:
	/******
	*创建日志记录日志
	*参数一：保留的天数
	*返回：
	******/
	static void CreateLog(unsigned int iSaveDay);

	/******
	*获取当前的日志实例
	*返回：日志实例
	******/
	static CTC_LogManager *LogInstance();

	/******
	*关闭日志实例
	******/
	static void CloseLog();

	/******
	*输出到文件
	*参数一:类型
	*参数二:文件名称
	*参数三:行数
	*参数四:格式
	*参数五:参数
	*返回：
	*****/
	void OutputFile(int iType, const char *sFile, int iLine, const char *sFormat, ...);
private:
	CTC_LogManager(unsigned int iSaveDay);
	virtual ~CTC_LogManager();

	/******
	*获取绝对路径
	*参数一：当前目录
	*参数二：当前目录长度
	*返回：当前目录字符串,NULL时出错
	******/
	char* GetAbsPath(char *sCurPath, int iLen);

	/******
	*获取当前年月日的秒
	******/
	time_t GetYMDSec();

	/******
	*创建当前文件
	*参数一：当前目录
	******/
	void CreateYMDFile(char *sDir);

	/******
	*删除过期的文件
	*参数一：保留文件的天数
	*返回：
	******/
	void DelTimeoutFile(unsigned int iDay = 30);
private:
	char         m_sDir[256];       //当前目录
	unsigned int m_uSaveDay;        //保留天数
	FILE        *m_pOutFile;        //输出到文件
	time_t       m_tCurDay;         //当前年月日秒级
	static CTC_LogManager *m_LogInstance;
};

#define CREATELOG(d)                 CTC_LogManager::CreateLog(d)
#define OUTDEBUG(type, format, ...)  CTC_LogManager::LogInstance()->OutputFile(type, __FILE__, __LINE__, format, __VA_ARGS__)
#define CLOSELOG()                   CTC_LogManager::CloseLog()
#endif


