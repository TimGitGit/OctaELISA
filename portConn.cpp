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
	//����QCombo
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
	//���ذ�ť
	connect(ui.pushBack, &QPushButton::clicked, [=]() {
		emit backMain();
		});
	//���Ӵ���
	connect(ui.pushUse, &QPushButton::clicked, [=]() {
		if (m_serialPort->isOpen())//��������Ѿ����� �ȸ����ر���
		{
			m_serialPort->clear();
			m_serialPort->close();
		}


		m_serialPort->setPortName(ui.comPort->currentText());//��ǰѡ��Ĵ�������
		int res;
		if (!m_serialPort->open(QIODevice::ReadWrite))//��ReadWrite ��ģʽ���Դ򿪴���
		{
			qDebug() << "fail!";
			MyMessageBox msgBox(this, MsgBoxType_Warn, QStringLiteral("����ʧ��"), QStringLiteral("ȷ��"), QStringLiteral("ȡ��"));
			res = msgBox.exec();
			return;
		}
		m_serialPort->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);//���ò����ʺͶ�д����
		m_serialPort->setStopBits(QSerialPort::OneStop); //һλֹͣλ
		m_serialPort->setDataBits(QSerialPort::Data8);      //����λΪ8λ
		m_serialPort->setFlowControl(QSerialPort::NoFlowControl);//��������
		m_serialPort->setParity(QSerialPort::NoParity); //��У��λ
		connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(receiveInfo()));
		qDebug() << "success";
		ui.lineMainName->setText(ui.comPort->currentText());
		//MyMessageBox msgBox(this, MsgBoxType_Info, QStringLiteral("���ӳɹ�"), QStringLiteral("ȷ��"), QStringLiteral("ȡ��"));
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

	unsigned char checksum = sum & 0xFF; // ȡ��������8λ��ΪУ��λ

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
	qDebug() << "��Ŀ����" << getcali.caliName << "��Ŀʱ��" << getcali.caliTime << "CAL1" << getcali.dataCAL1 << "CAL2" << getcali.dataCAL2 << "���" << getcali.dataVlo;
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
	QByteArray byteArray = getcali.caliName.toUtf8(); // ��QStringת��ΪQByteArray
	char caliNameArray[16];

	// ��ת��������ݸ��Ƶ�caliNameArray
	qstrncpy(caliNameArray, byteArray.constData(), 16); // ע�⣺�������qstrncpy��һ���Զ���ĺ�����������ȫ�ظ������ݵ�char����

	memcpy(&sendData[offset], &caliNameArray, 16);
	offset += 16;
	memcpy(&sendData[offset], &getcali.dataCAL1, sizeof(float));
	offset += 4;
	memcpy(&sendData[offset], &getcali.dataCAL2, sizeof(float));
	offset += 4;
	sendData[offset] = static_cast<uint8_t>(getcali.dataVlo);//�������
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
	QByteArray byteArray = gettest.testName.toUtf8(); // ��QStringת��ΪQByteArray
	char caliNameArray[16];

	// ��ת��������ݸ��Ƶ�caliNameArray
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
				case 3://��ȡ���м��ӫ�����ݣ��������Ŀ��һ����ʼ��⣩
				{
					QByteArray trimmedData = checkData.mid(4, checkData.size() - 6); // ȥ����ͷ���ĸ��ַ��ͽ�β�������ַ�
					if (proOrCali == 0)
						emit emitNewPro(trimmedData);
					else if (proOrCali == 1)
						emit emitNewMain(trimmedData);


					break;
				}
				case 5://���ȫ����¼
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
						QString str_data = name; // ��char����ת��ΪQString
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
						QVector<int> dataChecks;//��λ�Ƿ�ѡ��
						QVector<float> dataA;//ֱ��ʽ��A
						QVector<float> dataB;//ֱ��ʽ��B
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
						QString str_data = name; // ��char����ת��ΪQString
						offset += 16;
						int calitime;
						memcpy(&calitime, &sendData[offset], 4);
						offset += 4;
						QVector<int> dataChecks;//��λ�Ƿ�ѡ��
						QVector<int> dataAD;//���ֵ
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
						MyMessageBox msgBox(this, MsgBoxType_Info, QStringLiteral("���ݻ�ȡ�ɹ�"), QStringLiteral("ȷ��"), QStringLiteral("ȡ��"));
						res = msgBox.exec();
						emit backMain();
					}

					break;
				}
				case 7://����һ������//Ҫȷ���Ƕ��껹�ǲ��Ե�
				{
					int dataSTATUS = static_cast<int>(checkData[4]);
					qDebug() << "dataSTATUS" << dataSTATUS;
					int res;
					if (dataSTATUS == 0) {
						if (proOrCali2 == 0)
							emit emitAddTableCali(newCali);
						else if (proOrCali2 == 1)
							emit emitAddTableTest(newTest);

						MyMessageBox msgBox(this, MsgBoxType_Info, QStringLiteral("����ɹ�"), QStringLiteral("ȷ��"), QStringLiteral("ȡ��"));
						res = msgBox.exec();
					}
					else {
						MyMessageBox msgBox(this, MsgBoxType_Info, QStringLiteral("����ʧ��"), QStringLiteral("ȷ��"), QStringLiteral("ȡ��"));
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
						MyMessageBox msgBox(this, MsgBoxType_Info, QStringLiteral("ɾ���ɹ�"), QStringLiteral("ȷ��"), QStringLiteral("ȡ��"));
						res = msgBox.exec();
					}
					else {
						MyMessageBox msgBox(this, MsgBoxType_Info, QStringLiteral("ɾ��ʧ��"), QStringLiteral("ȷ��"), QStringLiteral("ȡ��"));
						res = msgBox.exec();
					}
					break;
				}
				case 9://ɾ������
				{
					int dataSTATUS = static_cast<int>(checkData[4]);
					qDebug() << "dataSTATUS" << dataSTATUS;
					int res;
					if (dataSTATUS == 0) {
						emit emitRemoveAllOk();
						MyMessageBox msgBox(this, MsgBoxType_Info, QStringLiteral("ȫ��ɾ���ɹ�"), QStringLiteral("ȷ��"), QStringLiteral("ȡ��"));
						res = msgBox.exec();
					}
					else {
						MyMessageBox msgBox(this, MsgBoxType_Info, QStringLiteral("ȫ��ɾ��ʧ��"), QStringLiteral("ȷ��"), QStringLiteral("ȡ��"));
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
						QString str_data = name; // ��char����ת��ΪQString
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
						QVector<int> dataChecks;//��λ�Ƿ�ѡ��
						QVector<float> dataA;//ֱ��ʽ��A
						QVector<float> dataB;//ֱ��ʽ��B
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
						MyMessageBox msgBox(this, MsgBoxType_Info, QStringLiteral("���ݻ�ȡ�ɹ�"), QStringLiteral("ȷ��"), QStringLiteral("ȡ��"));
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
						QString str_data = name; // ��char����ת��ΪQString
						offset += 16;
						int calitime;
						memcpy(&calitime, &sendData[offset], 4);
						offset += 4;
						QVector<int> dataChecks;//��λ�Ƿ�ѡ��
						QVector<int> dataAD;//���ֵ
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
						MyMessageBox msgBox(this, MsgBoxType_Info, QStringLiteral("���ݻ�ȡ�ɹ�"), QStringLiteral("ȷ��"), QStringLiteral("ȡ��"));
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
