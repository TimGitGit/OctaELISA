#include "portConn.h"
#include "mymessagebox.h"

portConn::portConn(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	inUI();
	inCon();
}

portConn::~portConn()
{
	if (m_serialPort->isOpen())
	{
		m_serialPort->close();
	}
	delete m_serialPort;
	m_serialPort = NULL;
}
void portConn::inUI()
{
	//设置QCombo
	ui.comPort->setView(new QListView());
	ui.pushBack->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pushUse->setCursor(QCursor(Qt::PointingHandCursor));

	foreach(const QSerialPortInfo & info, QSerialPortInfo::availablePorts())
	{
		QSerialPort serial;
		serial.setPort(info);
		if (serial.open(QIODevice::ReadWrite))
		{
			ui.comPort->addItem(serial.portName());
			serial.close();
		}
	}
	m_serialPort = new QSerialPort();

}

void portConn::inCon()
{
	//返回按钮
	connect(ui.pushBack, &QPushButton::clicked, [=]() {
		emit backMain();
		});
	//连接串口
	connect(ui.pushUse, &QPushButton::clicked, [=]() {
		if (m_serialPort->isOpen())//如果串口已经打开了 先给他关闭了
		{
			m_serialPort->clear();
			m_serialPort->close();
		}


		m_serialPort->setPortName(ui.comPort->currentText());//当前选择的串口名字
		int res;
		if (!m_serialPort->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
		{
			qDebug() << "fail!";
			MyMessageBox msgBox(this, MsgBoxType_Warn, QStringLiteral("连接失败"), QStringLiteral("确认"), QStringLiteral("取消"));
			res = msgBox.exec();
			return;
		}
		m_serialPort->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);//设置波特率和读写方向
		m_serialPort->setStopBits(QSerialPort::OneStop); //一位停止位
		m_serialPort->setDataBits(QSerialPort::Data8);      //数据位为8位
		m_serialPort->setFlowControl(QSerialPort::NoFlowControl);//无流控制
		m_serialPort->setParity(QSerialPort::NoParity); //无校验位
		connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(receiveInfo()));
		qDebug() << "success";
		ui.lineMainName->setText(ui.comPort->currentText());
		//MyMessageBox msgBox(this, MsgBoxType_Info, QStringLiteral("连接成功"), QStringLiteral("确认"), QStringLiteral("取消"));
		//res = msgBox.exec();
		getAllRes();
		});

}

unsigned char calculateChecksum(const unsigned char* data, int size)
{
	unsigned int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += data[i];
	}

	unsigned char checksum = sum & 0xFF; // 取结果的最后8位作为校验位

	return checksum;
}
void portConn::getAllRes()
{
	qDebug() << "getAll";
	unsigned char sendData[5] = { 0 };
	sendData[0] = FH;
	sendData[1] = (unsigned char)CommandType::get_all_stored_data;
	sendData[2] = 0x00;
	sendData[3] = 0x05;
	sendData[4] = calculateChecksum(sendData, 4);

	m_serialPort->write((char*)sendData, sizeof(sendData));
}
void portConn::getStartMain(int type)
{
	proOrCali = type;
	qDebug() << "sendStart";
	unsigned char sendData[6] = { 0 };
	sendData[0] = FH;
	sendData[1] = (unsigned char)CommandType::get_fl_data;
	sendData[2] = 0x00;
	sendData[3] = 0x06;
	sendData[4] = 0xFF;
	sendData[5] = calculateChecksum(sendData, 5);

	m_serialPort->write((char*)sendData, sizeof(sendData));
}
void portConn::getSaveSingleCali(caliResu getcali)
{
	qDebug() << "项目名称" << getcali.caliName << "项目时间" << getcali.caliTime << "CAL1" << getcali.dataCAL1 << "CAL2" << getcali.dataCAL2 << "体积" << getcali.dataVlo;
	for (int i = 0; i < 8;i++) {
		qDebug() << "lineA" << getcali.dataA[i] << "lineB" << getcali.dataB[i] << "check" << getcali.dataChecks[i];
	}
	newCali = getcali;
	proOrCali2 = 0;
	unsigned char sendData[106] = { 0 };
	sendData[0] = FH;
	sendData[1] = (unsigned char)CommandType::save_single_stored_data;
	sendData[2] = 0x00;
	sendData[3] = 0x6A;

	uint16_t offset = 4;
	memcpy(&sendData[offset], &getcali.caliTime, 4);
	offset += 4;
	QByteArray byteArray = getcali.caliName.toUtf8(); // 将QString转换为QByteArray
	char caliNameArray[16];

	// 将转换后的数据复制到caliNameArray
	qstrncpy(caliNameArray, byteArray.constData(), 16); // 注意：这里假设qstrncpy是一个自定义的函数，用来安全地复制数据到char数组

	memcpy(&sendData[offset], &caliNameArray, 16);
	offset += 16;
	memcpy(&sendData[offset], &getcali.dataCAL1, sizeof(float));
	offset += 4;
	memcpy(&sendData[offset], &getcali.dataCAL2, sizeof(float));
	offset += 4;
	sendData[offset] = static_cast<uint8_t>(getcali.dataVlo);//样本体积
	offset += sizeof(uint8_t);
	for (int i = 0; i < 8;i++) {
		sendData[offset] = static_cast<uint8_t>(getcali.dataChecks[i]);
		offset += sizeof(uint8_t);
		memcpy(&sendData[offset], &getcali.dataA[i], 4);
		offset += 4;
		memcpy(&sendData[offset], &getcali.dataB[i], 4);
		offset += 4;
	}
	sendData[offset] = calculateChecksum(sendData, offset);
	m_serialPort->write((char*)sendData, sizeof(sendData));

}
void portConn::getSaveSingleTest(testResu gettest)
{
	qDebug() << gettest.testTime << "proTime";
	qDebug() << gettest.caliTime << "caliTime";
	qDebug() << "name" << gettest.testName;
	for (int i = 0; i < 8; i++) {
		qDebug() << "check" << gettest.dataChecks[i] << "date" << gettest.dataAD[i];
	}
	newTest = gettest;
	proOrCali2 = 1;
	unsigned char sendData[69] = { 0 };
	sendData[0] = FH;
	sendData[1] = (unsigned char)CommandType::save_single_stored_data;
	sendData[2] = 0x00;
	sendData[3] = 0x45;

	uint16_t offset = 4;
	memcpy(&sendData[offset], &gettest.testTime, 4);
	offset += 4;
	QByteArray byteArray = gettest.testName.toUtf8(); // 将QString转换为QByteArray
	char caliNameArray[16];

	// 将转换后的数据复制到caliNameArray
	qstrncpy(caliNameArray, byteArray.constData(), 16);

	memcpy(&sendData[offset], &caliNameArray, 16);
	offset += 16;
	memcpy(&sendData[offset], &gettest.caliTime, 4);
	offset += 4;
	for (int i = 0; i < 8; i++) {
		sendData[offset] = static_cast<uint8_t>(gettest.dataChecks[i]);
		offset += sizeof(uint8_t);
		memcpy(&sendData[offset], &gettest.dataAD[i], 4);
		offset += 4;
	}
	sendData[offset] = calculateChecksum(sendData, offset);
	m_serialPort->write((char*)sendData, sizeof(sendData));

}
void portConn::getRemoveAll()
{
	qDebug() << "sendRemoveAll";
	unsigned char sendData[5] = { 0 };
	sendData[0] = FH;
	sendData[1] = (unsigned char)CommandType::delete_all_stored_data;
	sendData[2] = 0x00;
	sendData[3] = 0x05;
	sendData[4] = calculateChecksum(sendData, 4);

	m_serialPort->write((char*)sendData, sizeof(sendData));
}
void portConn::getRemoveOne(int deleTime)
{
	nowDelete = deleTime;
	qDebug() << "sendRemoveOne";
	unsigned char sendData[9] = { 0 };
	sendData[0] = FH;
	sendData[1] = (unsigned char)CommandType::delete_single_stored_data;
	sendData[2] = 0x00;
	sendData[3] = 0x09;
	memcpy(&sendData[4], &deleTime, 4);
	sendData[8] = calculateChecksum(sendData, 8);

	m_serialPort->write((char*)sendData, sizeof(sendData));
}
void portConn::receiveInfo()
{
	QByteArray info = m_serialPort->readAll();
	qDebug() << "info" << info << info.size();
	if (info.size()>0) {
		if (info.at(0) == FH) {
			flag = 1;
			allSize = static_cast<int>(info.at(3));
			qDebug() << "allSize" << allSize;
		}
		if (flag == 1) {
			allData.append(info);
			sizeData += info.size();
			qDebug() <<"sizeData" << sizeData;
			if (sizeData == allSize) {
				int dataType = static_cast<int>(allData[1] & 0x7F);
				qDebug() << "allData" << allData << allData.size() << "dataType" << dataType;
				checkData = allData;
				allData.clear();
				sizeData = 0;
				allSize = 0;
				flag = 0;
				switch (dataType)
				{
				case 3://获取所有检测荧光数据（定标和项目都一样开始检测）
				{
					QByteArray trimmedData = checkData.mid(4, checkData.size() - 6); // 去掉开头的四个字符和结尾的两个字符
					if (proOrCali == 0)
						emit emitNewPro(trimmedData);
					else if (proOrCali == 1)
						emit emitNewMain(trimmedData);


					break;
				}
				case 5://获得全部记录
				{
					qDebug() << "allDataallDataallData" << checkData.size();

					if (checkData.size() == 107) {
						QByteArray trimmedData = checkData.mid(4, checkData.size() - 6);
						unsigned char sendData[101] = { 0 };
						memcpy(sendData, trimmedData.constData(), trimmedData.size());

						uint16_t offset = 0;
						int time;
						memcpy(&time, &sendData[offset], 4);
						offset += 4;
						char name[16];
						memcpy(&name, &sendData[offset], 16);
						QString str_data = name; // 将char数组转换为QString
						offset += 16;
						float CAL1 = 0.0;
						memcpy(&CAL1, &sendData[offset], 4);
						offset += 4;
						float CAL2 = 0.0;
						memcpy(&CAL2, &sendData[offset], 4);
						offset += 4;
						//qDebug() << "CAL1" << CAL1 << "CAL2" << CAL2;
						int value = 0;
						memcpy(&value, &sendData[offset], 1);
						offset += 1;
						QVector<int> dataChecks;//孔位是否选中
						QVector<float> dataA;//直线式的A
						QVector<float> dataB;//直线式的B
						for (int i = 0; i < 8; i++) {
							int check = 0;
							float lineA = 0.0;
							float lineB = 0.0;
							memcpy(&check, &sendData[offset], 1);
							offset += 1;
							memcpy(&lineA, &sendData[offset], 4);
							offset += 4;
							memcpy(&lineB, &sendData[offset], 4);
							offset += 4;
							//qDebug() << "check" << check << "A" << lineA << "B" << lineB;
							dataChecks.append(check);
							dataA.append(lineA);
							dataB.append(lineB);
						}
						caliResu caOne = { name,time,CAL1,CAL2,value,dataChecks,dataA,dataB };
						emit emitAddTableCali(caOne);
					}
					else if (checkData.size() == 70) {
						qDebug() << checkData.size();
						QByteArray trimmedData = checkData.mid(4, checkData.size() - 6);
						unsigned char sendData[64] = { 0 };
						memcpy(sendData, trimmedData.constData(), trimmedData.size());

						uint16_t offset = 0;
						int time;
						memcpy(&time, &sendData[offset], 4);
						offset += 4;
						char name[16];
						memcpy(&name, &sendData[offset], 16);
						QString str_data = name; // 将char数组转换为QString
						offset += 16;
						int calitime;
						memcpy(&calitime, &sendData[offset], 4);
						offset += 4;
						QVector<int> dataChecks;//孔位是否选中
						QVector<int> dataAD;//检测值
						for (int i = 0; i < 8; i++) {
							int check = 0;
							int dataCheck = 0;
							memcpy(&check, &sendData[offset], 1);
							offset += 1;
							memcpy(&dataCheck, &sendData[offset], 4);
							offset += 4;
							//qDebug() << "check" << check << "A" << lineA << "B" << lineB;
							dataChecks.append(check);
							dataAD.append(dataCheck);
						}
						testResu tsOne = { time,name,calitime,dataChecks,dataAD };
						emit emitAddTableTest(tsOne);
					}
					else if (checkData.size() == 6) {
						int res;
						MyMessageBox msgBox(this, MsgBoxType_Info, QStringLiteral("数据获取成功"), QStringLiteral("确认"), QStringLiteral("取消"));
						res = msgBox.exec();
						emit backMain();
					}

					break;
				}
				case 7://保存一条数据//要确定是定标还是测试的
				{
					int dataSTATUS = static_cast<int>(checkData[4]);
					qDebug() << "dataSTATUS" << dataSTATUS;
					int res;
					if (dataSTATUS == 0) {
						if (proOrCali2 == 0)
							emit emitAddTableCali(newCali);
						else if (proOrCali2 == 1)
							emit emitAddTableTest(newTest);

						MyMessageBox msgBox(this, MsgBoxType_Info, QStringLiteral("保存成功"), QStringLiteral("确认"), QStringLiteral("取消"));
						res = msgBox.exec();
					}
					else {
						MyMessageBox msgBox(this, MsgBoxType_Info, QStringLiteral("保存失败"), QStringLiteral("确认"), QStringLiteral("取消"));
						res = msgBox.exec();
					}
					break;
				}
				case 8:
				{
					int dataSTATUS = static_cast<int>(checkData[4]);
					qDebug() << "dataSTATUS" << dataSTATUS;
					int res;
					if (dataSTATUS == 0) {
						emit emitRemoveOne(nowDelete);
						MyMessageBox msgBox(this, MsgBoxType_Info, QStringLiteral("删除成功"), QStringLiteral("确认"), QStringLiteral("取消"));
						res = msgBox.exec();
					}
					else {
						MyMessageBox msgBox(this, MsgBoxType_Info, QStringLiteral("删除失败"), QStringLiteral("确认"), QStringLiteral("取消"));
						res = msgBox.exec();
					}
					break;
				}
				case 9://删除所有
				{
					int dataSTATUS = static_cast<int>(checkData[4]);
					qDebug() << "dataSTATUS" << dataSTATUS;
					int res;
					if (dataSTATUS == 0) {
						emit emitRemoveAllOk();
						MyMessageBox msgBox(this, MsgBoxType_Info, QStringLiteral("全部删除成功"), QStringLiteral("确认"), QStringLiteral("取消"));
						res = msgBox.exec();
					}
					else {
						MyMessageBox msgBox(this, MsgBoxType_Info, QStringLiteral("全部删除失败"), QStringLiteral("确认"), QStringLiteral("取消"));
						res = msgBox.exec();
					}
					break;
				}
				default:
					break;
				}


				//allData.clear();
				//sizeData = 0;
				//allSize = 0;
				//flag = 0;
			}
			else if (sizeData == allSize + 6) {
				int dataType = static_cast<int>(allData[1] & 0x7F);

				qDebug() << "allData22" << allData << allData.size() << "dataType" << dataType;
				checkData = allData;
				allData.clear();
				sizeData = 0;
				allSize = 0;
				flag = 0;

				if (dataType == 5) {
					if (checkData.size() == 113) {
						QByteArray trimmedData = checkData.mid(4, checkData.size() - 12);
						unsigned char sendData[101] = { 0 };
						memcpy(sendData, trimmedData.constData(), trimmedData.size());

						uint16_t offset = 0;
						int time;
						memcpy(&time, &sendData[offset], 4);
						offset += 4;
						char name[16];
						memcpy(&name, &sendData[offset], 16);
						QString str_data = name; // 将char数组转换为QString
						offset += 16;
						float CAL1 = 0.0;
						memcpy(&CAL1, &sendData[offset], 4);
						offset += 4;
						float CAL2 = 0.0;
						memcpy(&CAL2, &sendData[offset], 4);
						offset += 4;
						//qDebug() << "CAL1" << CAL1 << "CAL2" << CAL2;
						int value = 0;
						memcpy(&value, &sendData[offset], 1);
						offset += 1;
						QVector<int> dataChecks;//孔位是否选中
						QVector<float> dataA;//直线式的A
						QVector<float> dataB;//直线式的B
						for (int i = 0; i < 8; i++) {
							int check = 0;
							float lineA = 0.0;
							float lineB = 0.0;
							memcpy(&check, &sendData[offset], 1);
							offset += 1;
							memcpy(&lineA, &sendData[offset], 4);
							offset += 4;
							memcpy(&lineB, &sendData[offset], 4);
							offset += 4;
							//qDebug() << "check" << check << "A" << lineA << "B" << lineB;
							dataChecks.append(check);
							dataA.append(lineA);
							dataB.append(lineB);
						}
						caliResu caOne = { name,time,CAL1,CAL2,value,dataChecks,dataA,dataB };
						emit emitAddTableCali(caOne);
						int res;
						MyMessageBox msgBox(this, MsgBoxType_Info, QStringLiteral("数据获取成功"), QStringLiteral("确认"), QStringLiteral("取消"));
						res = msgBox.exec();
						emit backMain();

					}
					else if (checkData.size() == 76) {
						qDebug() << checkData.size();
						QByteArray trimmedData = checkData.mid(4, checkData.size() - 12);
						unsigned char sendData[64] = { 0 };
						memcpy(sendData, trimmedData.constData(), trimmedData.size());

						uint16_t offset = 0;
						int time;
						memcpy(&time, &sendData[offset], 4);
						offset += 4;
						char name[16];
						memcpy(&name, &sendData[offset], 16);
						QString str_data = name; // 将char数组转换为QString
						offset += 16;
						int calitime;
						memcpy(&calitime, &sendData[offset], 4);
						offset += 4;
						QVector<int> dataChecks;//孔位是否选中
						QVector<int> dataAD;//检测值
						for (int i = 0; i < 8; i++) {
							int check = 0;
							int dataCheck = 0;
							memcpy(&check, &sendData[offset], 1);
							offset += 1;
							memcpy(&dataCheck, &sendData[offset], 4);
							offset += 4;
							//qDebug() << "check" << check << "A" << lineA << "B" << lineB;
							dataChecks.append(check);
							dataAD.append(dataCheck);
						}
						testResu tsOne = { time,name,calitime,dataChecks,dataAD };
						emit emitAddTableTest(tsOne);
						int res;
						MyMessageBox msgBox(this, MsgBoxType_Info, QStringLiteral("数据获取成功"), QStringLiteral("确认"), QStringLiteral("取消"));
						res = msgBox.exec();
						emit backMain();

					}
				}
				//allData.clear();
				//sizeData = 0;
				//allSize = 0;
				//flag = 0;
			}
			else if (sizeData > allSize + 6) {
			allData.clear();
			sizeData = 0;
			allSize = 0;
			flag = 0;
			}
		}
	}
	

}
