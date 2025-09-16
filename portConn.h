#pragma once

#include <QWidget>
#include <QListView>
#include <QSerialPort>
#include <QDebug>
#include <QSerialPortInfo>
#include <QDateTime>
#include "base.h"
#include "ui_portConn.h"
static uint8_t FH = { 0x5e };
enum CommandType
{
	start_run,//����
	handshake,//����ָ��
	get_single_fl_data,//��ȡ����ӫ������ָ��
	get_fl_data,//��ȡӫ������ָ��
	temp_set,//����
	get_all_stored_data, //��ȡȫ���洢����ָ��
	get_single_stored_data,//��ȡһ���洢����ָ��
	save_single_stored_data,//����һ���洢����ָ��
	delete_single_stored_data,//ɾ��һ���洢����ָ��
	delete_all_stored_data//ɾ��ȫ���洢����ָ��
};
class portConn : public QWidget
{
	Q_OBJECT

public:
	portConn(QWidget *parent = nullptr);
	~portConn();
	void inUI();
	void inCon();
	void getAllRes();//���ȫ����¼
public slots:
	void receiveInfo();
	void getStartMain(int);
	void getSaveSingleCali(caliResu);
	void getSaveSingleTest(testResu);
	void getRemoveAll();
	void getRemoveOne(int);
signals:
	void backMain();
	void emitNewMain(QByteArray);
	void emitNewPro(QByteArray);
	void emitAddTableCali(caliResu);
	void emitAddTableTest(testResu);
	void emitRemoveAllOk();
	void emitRemoveOne(int);
private:
	Ui::portConnClass ui;
	QSerialPort* m_serialPort = NULL;
	QByteArray allData;
	QByteArray checkData;
	int sizeData = 0;
	int allSize = 0;
	int flag = 0;
	caliResu newCali;
	testResu newTest;
	int proOrCali;//�����жϵ�ǰ�յ���ʼ������cali����test
	int proOrCali2;//�����ж�Ҫ���б���������cali����test��
	int nowDelete = 0;
};
