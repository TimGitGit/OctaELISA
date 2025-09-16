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
	start_run,//备用
	handshake,//握手指令
	get_single_fl_data,//获取单条荧光数据指令
	get_fl_data,//获取荧光数据指令
	temp_set,//备用
	get_all_stored_data, //获取全部存储数据指令
	get_single_stored_data,//获取一条存储数据指令
	save_single_stored_data,//保存一条存储数据指令
	delete_single_stored_data,//删除一条存储数据指令
	delete_all_stored_data//删除全部存储数据指令
};
class portConn : public QWidget
{
	Q_OBJECT

public:
	portConn(QWidget *parent = nullptr);
	~portConn();
	void inUI();
	void inCon();
	void getAllRes();//获得全部记录
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
	int proOrCali;//用来判断当前收到开始命令是cali还是test
	int proOrCali2;//用来判断要进行保存数据是cali还是test，
	int nowDelete = 0;
};
