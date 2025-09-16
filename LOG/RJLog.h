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
	*������־��¼��־
	*����һ������������
	*���أ�
	******/
	static void CreateLog(unsigned int iSaveDay);

	/******
	*��ȡ��ǰ����־ʵ��
	*���أ���־ʵ��
	******/
	static CTC_LogManager *LogInstance();

	/******
	*�ر���־ʵ��
	******/
	static void CloseLog();

	/******
	*������ļ�
	*����һ:����
	*������:�ļ�����
	*������:����
	*������:��ʽ
	*������:����
	*���أ�
	*****/
	void OutputFile(int iType, const char *sFile, int iLine, const char *sFormat, ...);
private:
	CTC_LogManager(unsigned int iSaveDay);
	virtual ~CTC_LogManager();

	/******
	*��ȡ����·��
	*����һ����ǰĿ¼
	*����������ǰĿ¼����
	*���أ���ǰĿ¼�ַ���,NULLʱ����
	******/
	char* GetAbsPath(char *sCurPath, int iLen);

	/******
	*��ȡ��ǰ�����յ���
	******/
	time_t GetYMDSec();

	/******
	*������ǰ�ļ�
	*����һ����ǰĿ¼
	******/
	void CreateYMDFile(char *sDir);

	/******
	*ɾ�����ڵ��ļ�
	*����һ�������ļ�������
	*���أ�
	******/
	void DelTimeoutFile(unsigned int iDay = 30);
private:
	char         m_sDir[256];       //��ǰĿ¼
	unsigned int m_uSaveDay;        //��������
	FILE        *m_pOutFile;        //������ļ�
	time_t       m_tCurDay;         //��ǰ�������뼶
	static CTC_LogManager *m_LogInstance;
};

#define CREATELOG(d)                 CTC_LogManager::CreateLog(d)
#define OUTDEBUG(type, format, ...)  CTC_LogManager::LogInstance()->OutputFile(type, __FILE__, __LINE__, format, __VA_ARGS__)
#define CLOSELOG()                   CTC_LogManager::CloseLog()
#endif


