#include "elisaMain.h"
#include "mymessagebox.h"
elisaMain::elisaMain(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	inUI();
	inCon();
}

elisaMain::~elisaMain()
{
	delete validator;
	delete intValidator;
}

void elisaMain::inUI()
{
	ui.pushSave->hide();
	//设置鼠标放上时为手型
	ui.tpMainCheck1->setCursor(QCursor(Qt::PointingHandCursor));
	ui.tpMainCheck2->setCursor(QCursor(Qt::PointingHandCursor));
	ui.tpMainCheck3->setCursor(QCursor(Qt::PointingHandCursor));
	ui.tpMainCheck4->setCursor(QCursor(Qt::PointingHandCursor));
	ui.tpMainCheck5->setCursor(QCursor(Qt::PointingHandCursor));
	ui.tpMainCheck6->setCursor(QCursor(Qt::PointingHandCursor));
	ui.tpMainCheck7->setCursor(QCursor(Qt::PointingHandCursor));
	ui.tpMainCheck8->setCursor(QCursor(Qt::PointingHandCursor));
	
	ui.pushBackMain->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pushBack->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pushStart->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pushSave->setCursor(QCursor(Qt::PointingHandCursor));
	//设置QLineEdit的输入范围
	validator = new QDoubleValidator();
	ui.lineMainCAL1->setValidator(validator);
	ui.lineMainCAL1_2->setValidator(validator);
	intValidator = new QIntValidator(0, 20);
	ui.lineMainVolu->setValidator(intValidator);

	//返回上一步隐藏
	ui.pushBack->hide();

	caliNewChecks.append(1);
	caliNewChecks.append(1);
	caliNewChecks.append(1);
	caliNewChecks.append(1);
	caliNewChecks.append(1);
	caliNewChecks.append(1);
	caliNewChecks.append(1);
	caliNewChecks.append(1);

}

void elisaMain::inCon()
{
	//开始实验的8个勾
	connect(ui.tpMainCheck1, &QToolButton::clicked, [=]() {
		if (caliNewChecks[0] == 1) {
			caliNewChecks[0] = 0;
			ui.tpMainCheck1->setIcon(QIcon(":/images/image/cha.png"));
		}
		else if (caliNewChecks[0] == 0) {
			caliNewChecks[0] = 1;
			ui.tpMainCheck1->setIcon(QIcon(":/images/image/gou.png"));
		}
		});
	connect(ui.tpMainCheck2, &QToolButton::clicked, [=]() {
		if (caliNewChecks[1] == 1) {
			caliNewChecks[1] = 0;
			ui.tpMainCheck2->setIcon(QIcon(":/images/image/cha.png"));
		}
		else if (caliNewChecks[1] ==0) {
			caliNewChecks[1] = 1;
			ui.tpMainCheck2->setIcon(QIcon(":/images/image/gou.png"));
		}
		});
	connect(ui.tpMainCheck3, &QToolButton::clicked, [=]() {
		if (caliNewChecks[2] == 1) {
			caliNewChecks[2] = 0;
			ui.tpMainCheck3->setIcon(QIcon(":/images/image/cha.png"));
		}
		else if (caliNewChecks[2] == 0) {
			caliNewChecks[2] = 1;
			ui.tpMainCheck3->setIcon(QIcon(":/images/image/gou.png"));
		}
		});
	connect(ui.tpMainCheck4, &QToolButton::clicked, [=]() {
		if (caliNewChecks[3] == 1) {
			caliNewChecks[3] = 0;
			ui.tpMainCheck4->setIcon(QIcon(":/images/image/cha.png"));
		}
		else if (caliNewChecks[3] == 0) {
			caliNewChecks[3] = 1;
			ui.tpMainCheck4->setIcon(QIcon(":/images/image/gou.png"));
		}
		});
	connect(ui.tpMainCheck5, &QToolButton::clicked, [=]() {
		if (caliNewChecks[4] == 1) {
			caliNewChecks[4] = 0;
			ui.tpMainCheck5->setIcon(QIcon(":/images/image/cha.png"));
		}
		else if (caliNewChecks[4] == 0) {
			caliNewChecks[4] = 1;
			ui.tpMainCheck5->setIcon(QIcon(":/images/image/gou.png"));
		}
		});
	connect(ui.tpMainCheck6, &QToolButton::clicked, [=]() {
		if (caliNewChecks[5] == 1) {
			caliNewChecks[5] = 0;
			ui.tpMainCheck6->setIcon(QIcon(":/images/image/cha.png"));
		}
		else if (caliNewChecks[5] == 0) {
			caliNewChecks[5] = 1;
			ui.tpMainCheck6->setIcon(QIcon(":/images/image/gou.png"));
		}
		});
	connect(ui.tpMainCheck7, &QToolButton::clicked, [=]() {
		if (caliNewChecks[6] == 1) {
			caliNewChecks[6] = 0;
			ui.tpMainCheck7->setIcon(QIcon(":/images/image/cha.png"));
		}
		else if (caliNewChecks[6] == 0) {
			caliNewChecks[6] = 1;
			ui.tpMainCheck7->setIcon(QIcon(":/images/image/gou.png"));
		}
		});
	connect(ui.tpMainCheck8, &QToolButton::clicked, [=]() {
		if (caliNewChecks[7] == 1) {
			caliNewChecks[7] = 0;
			ui.tpMainCheck8->setIcon(QIcon(":/images/image/cha.png"));
		}
		else if (caliNewChecks[7] == 0) {
			caliNewChecks[7] = 1;
			ui.tpMainCheck8->setIcon(QIcon(":/images/image/gou.png"));
		}
		});
	//返回按钮
	connect(ui.pushBack, &QPushButton::clicked, [=]() {
		if (firstOrNot == 1) {
			firstOrNot = 0;
			ui.pushStart->setText(QStringLiteral("开始实验"));
			ui.tpMainCheck1->setEnabled(true);
			ui.tpMainCheck2->setEnabled(true);
			ui.tpMainCheck3->setEnabled(true);
			ui.tpMainCheck4->setEnabled(true);
			ui.tpMainCheck5->setEnabled(true);
			ui.tpMainCheck6->setEnabled(true);
			ui.tpMainCheck7->setEnabled(true);
			ui.tpMainCheck8->setEnabled(true);
			ui.pushBack->hide();
		}
		//else if (firstOrNot == 0) {
		//	emit backMain();
		//}
		else if (firstOrNot == 2) {
			ui.pushSave->hide();
			ui.pushStart->show();
			firstOrNot = 1;
			ui.pushStart->setText(QStringLiteral("继续实验"));
		}
		});
	//返回主界面
	connect(ui.pushBackMain, &QPushButton::clicked, [=]() {
		ui.lineMainName->setText("");
		ui.lineMainTime->setText("");
		ui.lineMainCAL1->setText("");
		ui.lineMainCAL1_2->setText("");
		ui.lineMainVolu->setText("");

		ui.labelTube1->setText("");
		ui.labelTube2->setText("");
		ui.labelTube3->setText("");
		ui.labelTube4->setText("");
		ui.labelTube5->setText("");
		ui.labelTube6->setText("");
		ui.labelTube7->setText("");
		ui.labelTube8->setText("");

		ui.labelSam1->setText("");
		ui.labelSam2->setText("");
		ui.labelSam3->setText("");
		ui.labelSam4->setText("");
		ui.labelSam5->setText("");
		ui.labelSam6->setText("");
		ui.labelSam7->setText("");
		ui.labelSam8->setText("");

		ui.tpMainCheck1->setIcon(QIcon(":/images/image/gou.png"));
		ui.tpMainCheck2->setIcon(QIcon(":/images/image/gou.png"));
		ui.tpMainCheck3->setIcon(QIcon(":/images/image/gou.png"));
		ui.tpMainCheck4->setIcon(QIcon(":/images/image/gou.png"));
		ui.tpMainCheck5->setIcon(QIcon(":/images/image/gou.png"));
		ui.tpMainCheck6->setIcon(QIcon(":/images/image/gou.png"));
		ui.tpMainCheck7->setIcon(QIcon(":/images/image/gou.png"));
		ui.tpMainCheck8->setIcon(QIcon(":/images/image/gou.png"));

		caliNewChecks[0] = 1;
		caliNewChecks[1] = 1;
		caliNewChecks[2] = 1;
		caliNewChecks[3] = 1;
		caliNewChecks[4] = 1;
		caliNewChecks[5] = 1;
		caliNewChecks[6] = 1;
		caliNewChecks[7] = 1;

		firstOrNot = 0;
		ui.tpMainCheck1->setEnabled(true);
		ui.tpMainCheck2->setEnabled(true);
		ui.tpMainCheck3->setEnabled(true);
		ui.tpMainCheck4->setEnabled(true);
		ui.tpMainCheck5->setEnabled(true);
		ui.tpMainCheck6->setEnabled(true);
		ui.tpMainCheck7->setEnabled(true);
		ui.tpMainCheck8->setEnabled(true);
		ui.pushBack->hide();
		ui.pushStart->setText(QStringLiteral("开始实验"));
		ui.pushSave->hide();
		ui.pushStart->show();

		emit backMain();
		});
	//开始实验
	connect(ui.pushStart, &QPushButton::clicked, [=]() {
		if (firstOrNot == 0) {
			ui.tpMainCheck1->setEnabled(false);
			ui.tpMainCheck2->setEnabled(false);
			ui.tpMainCheck3->setEnabled(false);
			ui.tpMainCheck4->setEnabled(false);
			ui.tpMainCheck5->setEnabled(false);
			ui.tpMainCheck6->setEnabled(false);
			ui.tpMainCheck7->setEnabled(false);
			ui.tpMainCheck8->setEnabled(false);
			firstOrNot = 1;
			ui.pushBack->show();
			QDateTime nowTime = QDateTime::currentDateTime();
			QString nowStr = nowTime.toString("yyyy.MM.dd hh:mm:ss");
			ui.lineMainTime->setText(nowStr);
			ui.pushStart->setText(QStringLiteral("继续实验"));
		}
		else if (firstOrNot == 1) {
			firstOrNot = 2;
			ui.pushSave->show();
			ui.pushStart->hide();
		}
		emit startMain(1);

		});
	//保存实验
	connect(ui.pushSave, &QPushButton::clicked, [=]() {
		//判断CAL1和CAL2是否为空
		if (ui.lineMainName->text() != "" && ui.lineMainCAL1->text() != "" &&  ui.lineMainCAL1_2->text() != "" && ui.lineMainVolu->text() != "" &&
			ui.labelTube1->text() != "" && ui.labelTube2->text() != "" && ui.labelTube3->text() != "" && ui.labelTube4->text() != "" &&
			ui.labelTube5->text() != "" && ui.labelTube6->text() != "" && ui.labelTube7->text() != "" && ui.labelTube7->text() != "" &&
			ui.labelSam1->text() != "" && ui.labelSam2->text() != "" && ui.labelSam3->text() != "" && ui.labelSam4->text() != "" &&
			ui.labelSam5->text() != "" && ui.labelSam6->text() != "" && ui.labelSam7->text() != "" && ui.labelSam8->text() != "") {
				float cal1 = ui.lineMainCAL1->text().toFloat();
				float cal2 = ui.lineMainCAL1_2->text().toFloat();


				QVector<double> yData; // 存储浓度
				QVector<double> xData; // 存储AD值
				xData.clear();
				yData.clear();
				caliNewA.clear();
				caliNewB.clear();
				yData.append(cal1);
				yData.append(cal2);
				xData.append(ui.labelTube1->text().toInt());
				xData.append(ui.labelSam1->text().toInt());
				linearFit(xData,yData);
				xData.clear();
				xData.append(ui.labelTube2->text().toInt());
				xData.append(ui.labelSam2->text().toInt());
				linearFit(xData, yData);
				xData.clear();
				xData.append(ui.labelTube3->text().toInt());
				xData.append(ui.labelSam3->text().toInt());
				linearFit(xData, yData);
				xData.clear();
				xData.append(ui.labelTube4->text().toInt());
				xData.append(ui.labelSam4->text().toInt());
				linearFit(xData, yData);
				xData.clear();
				xData.append(ui.labelTube5->text().toInt());
				xData.append(ui.labelSam5->text().toInt());
				linearFit(xData, yData);
				xData.clear();
				xData.append(ui.labelTube6->text().toInt());
				xData.append(ui.labelSam6->text().toInt());
				linearFit(xData, yData);
				xData.clear();
				xData.append(ui.labelTube7->text().toInt());
				xData.append(ui.labelSam7->text().toInt());
				linearFit(xData, yData);
				xData.clear();
				xData.append(ui.labelTube8->text().toInt());
				xData.append(ui.labelSam8->text().toInt());
				linearFit(xData, yData);
				QDateTime nowTime = QDateTime::fromString(ui.lineMainTime->text(), "yyyy.MM.dd hh:mm:ss"); // 将QString转换为QDateTime对象
				int timestamp = nowTime.toSecsSinceEpoch(); // 将QDateTime对象转换为时间戳


				for (int i = 0; i < caliNewA.size();i++) {
					qDebug() << "k" << caliNewA[i] << "b" << caliNewB[i];
				}
				caliResu cResult = { ui.lineMainName->text() ,timestamp,cal1,cal2,ui.lineMainVolu->text().toInt(),caliNewChecks,caliNewA ,caliNewB};
				emit sendSaveSingleCali(cResult);
				//xData.append();

		}
		else {
			int res;
			MyMessageBox msgBox(this, MsgBoxType_Error, QStringLiteral("定标信息未齐全！"), QStringLiteral("确认"), QStringLiteral("取消"));
			res = msgBox.exec();
		}


		});
}
void elisaMain::receiveNewMain(QByteArray newArray) {
	qDebug() << newArray << newArray.size();
	QList<int> intList;
	for (int i = 0; i < newArray.size(); i += 4) {
		QByteArray chunk = newArray.mid(i, 4);
		int intValue = 0;

		for (int j = 0; j < 4; j++) {
			intValue |= (static_cast<uchar>(chunk.at(j)) << (j * 8));
		}
		intList.append(intValue);
		qDebug() << chunk <<intValue;
	}
	if (firstOrNot == 1) {
		if (caliNewChecks[0] == 1)
			ui.labelTube1->setText(QString::number(intList[0]));
		else if (caliNewChecks[0] == 0)
			ui.labelTube1->setText("\\");
		if (caliNewChecks[1] == 1)
			ui.labelTube2->setText(QString::number(intList[1]));
		else if (caliNewChecks[1] == 0)
			ui.labelTube2->setText("\\");
		if (caliNewChecks[2] == 1)
			ui.labelTube3->setText(QString::number(intList[2]));
		else if (caliNewChecks[2] == 0)
			ui.labelTube3->setText("\\");
		if (caliNewChecks[3] == 1)
			ui.labelTube4->setText(QString::number(intList[3]));
		else if (caliNewChecks[3] == 0)
			ui.labelTube4->setText("\\");
		if (caliNewChecks[4] == 1)
			ui.labelTube5->setText(QString::number(intList[4]));
		else if (caliNewChecks[4] == 0)
			ui.labelTube5->setText("\\");
		if (caliNewChecks[5] == 1)
			ui.labelTube6->setText(QString::number(intList[5]));
		else if (caliNewChecks[5] == 0)
			ui.labelTube6->setText("\\");
		if (caliNewChecks[6] == 1)
			ui.labelTube7->setText(QString::number(intList[6]));
		else if (caliNewChecks[6] == 0)
			ui.labelTube7->setText("\\");
		if (caliNewChecks[7] == 1)
			ui.labelTube8->setText(QString::number(intList[7]));
		else if (caliNewChecks[7] == 0)
			ui.labelTube8->setText("\\");
	}
	else if (firstOrNot == 2) {
		if (caliNewChecks[0] == 1)
			ui.labelSam1->setText(QString::number(intList[0]));
		else if (caliNewChecks[0] == 0)
			ui.labelSam1->setText("\\");
		if (caliNewChecks[1] == 1)
			ui.labelSam2->setText(QString::number(intList[1]));
		else if (caliNewChecks[1] == 0)
			ui.labelSam2->setText("\\");
		if (caliNewChecks[2] == 1)
			ui.labelSam3->setText(QString::number(intList[2]));
		else if (caliNewChecks[2] == 0)
			ui.labelSam3->setText("\\");
		if (caliNewChecks[3] == 1)
			ui.labelSam4->setText(QString::number(intList[3]));
		else if (caliNewChecks[3] == 0)
			ui.labelSam4->setText("\\");
		if (caliNewChecks[4] == 1)
			ui.labelSam5->setText(QString::number(intList[4]));
		else if (caliNewChecks[4] == 0)
			ui.labelSam5->setText("\\");
		if (caliNewChecks[5] == 1)
			ui.labelSam6->setText(QString::number(intList[5]));
		else if (caliNewChecks[5] == 0)
			ui.labelSam6->setText("\\");
		if (caliNewChecks[6] == 1)
			ui.labelSam7->setText(QString::number(intList[6]));
		else if (caliNewChecks[6] == 0)
			ui.labelSam7->setText("\\");
		if (caliNewChecks[7] == 1)
			ui.labelSam8->setText(QString::number(intList[7]));
		else if (caliNewChecks[7] == 0)
			ui.labelSam8->setText("\\");
	}
	
}
void elisaMain::linearFit(const QVector<double>& xData, const QVector<double>& yData) {
	int n = xData.size();
	Eigen::MatrixXd A(n, 2);
	Eigen::VectorXd b(n);

	for (int i = 0; i < n; ++i) {
		A(i, 0) = xData[i];
		A(i, 1) = 1;
		b(i) = yData[i];
		qDebug() << "A" << xData[i] << "B" << yData[i];
	}
	
	Eigen::Vector2d result = A.colPivHouseholderQr().solve(b);
	QString resultStr = QString("y =  %1 * x + %2")
		.arg(QString::number(result[0]))
		.arg(QString::number(result[1]));
	qDebug() << "线性拟合结果： y = " << result[0] << " * x + " << result[1];
	caliNewA.append(result[0]);
	caliNewB.append(result[1]);

	//lineA = result[0];
	//lineB = result[1];
	//ui->lineFitForm->setText(resultStr);
}
