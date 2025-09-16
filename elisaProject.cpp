#include "elisaProject.h"
#include "mymessagebox.h"

elisaProject::elisaProject(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	inUI();
	inCon();
}

elisaProject::~elisaProject()
{
	//delete &ui;
}

void elisaProject::inUI()
{
	//定标表格的设置
	ui.tableProTest->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列宽
	ui.tableProTest->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);//表头字体居中
	// 设置选择整行
	ui.tableProTest->setSelectionBehavior(QAbstractItemView::SelectRows);
	// 设置QTableWidget的editTriggers属性为NoEditTriggers，禁止编辑
	//ui.tableProTest->setEditTriggers(QAbstractItemView::NoEditTriggers);
	// 设置不能多行选择
	ui.tableProTest->setSelectionMode(QAbstractItemView::SingleSelection);
		//设置鼠标放上时为手型
	ui.tpProCheck1->setCursor(QCursor(Qt::PointingHandCursor));
	ui.tpProCheck2->setCursor(QCursor(Qt::PointingHandCursor));
	ui.tpProCheck3->setCursor(QCursor(Qt::PointingHandCursor));
	ui.tpProCheck4->setCursor(QCursor(Qt::PointingHandCursor));
	ui.tpProCheck5->setCursor(QCursor(Qt::PointingHandCursor));
	ui.tpProCheck6->setCursor(QCursor(Qt::PointingHandCursor));
	ui.tpProCheck7->setCursor(QCursor(Qt::PointingHandCursor));
	ui.tpProCheck8->setCursor(QCursor(Qt::PointingHandCursor));

	ui.pushBack->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pushAdd->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pushOK->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pushBack_2->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pushStart->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pushSave->setCursor(QCursor(Qt::PointingHandCursor));

	//ui.toolBLoss->setCursor(QCursor(Qt::PointingHandCursor));
	//ui.toolBAdd->setCursor(QCursor(Qt::PointingHandCursor));
	//设置QCombo
	ui.comPUnit->setView(new QListView());
	ui.comCheck->setView(new QListView());

	ui.spinBoxPValue->setRange(0,20);
	ui.spinBoxPValue->setValue(10);
	ui.spinBoxPValue->setSingleStep(1);

	//孔位
	testNewChecks.append(1);
	testNewChecks.append(1);
	testNewChecks.append(1);
	testNewChecks.append(1);
	testNewChecks.append(1);
	testNewChecks.append(1);
	testNewChecks.append(1);
	testNewChecks.append(1);

}

void elisaProject::inCon()
{
	//定标结果大全的点击事件
	connect(ui.tableProTest, &QTableWidget::itemClicked, [this](QTableWidgetItem* item) {
		int testTime = 0;
		if (item->column() == 0) {
			qDebug() << ui.tableProTest->item(item->row(),1)->text();
			QDateTime nowTime = QDateTime::fromString(ui.tableProTest->item(item->row(), 1)->text(), "yyyy.MM.dd hh:mm:ss"); // 将QString转换为QDateTime对象
			testTime = nowTime.toSecsSinceEpoch(); // 将QDateTime对象转换为时间戳
		}
		else {
			qDebug() << item->text();
			QDateTime nowTime = QDateTime::fromString(item->text(), "yyyy.MM.dd hh:mm:ss"); // 将QString转换为QDateTime对象
			testTime = nowTime.toSecsSinceEpoch(); // 将QDateTime对象转换为时间戳
		}
		if (testTime != 0) {
			int caliTime = 0;
			for (const testResu& test : proTest) {
				if (test.testTime == testTime) {
					caliTime = test.caliTime;
					break;
				}
			}
			if (caliTime != 0) {
				for (int i = 0; i < proCali.size();i++) {
					if (caliTime == proCali[i].caliTime) {
						ui.comCheck->setCurrentIndex(i+1);
						break;
					}
				}
			}
			else {
				ui.comCheck->setCurrentIndex(0);

			}

		}
		//if (item->column() == 0) {
		//	//if (ui.tableProTest->item(item->row(), 0)->checkState() == Qt::Checked) {
		//	//	int nowRow = item->row();
		//	//	for (int row = 0; row < ui.tableProTest->rowCount(); ++row) {
		//	//		if (row != nowRow) {
		//	//			ui.tableProTest->item(row, 0)->setCheckState(Qt::Unchecked);
		//	//		}
		//	//	}
		//	//}

		//}

		});
	//定标选择的切换
	connect(ui.comCheck, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
		if (index == 0) {
			ui.labelPCaliName->setText("//");
			ui.labelPCaliTime->setText("//");
			ui.labelPCaliCAL1->setText("//");
			ui.labelPCaliCAL2->setText("//");

		}
		else {
			proDataA.clear();
			proDataB.clear();
			QDateTime nowTime = QDateTime::fromString(ui.comCheck->currentText(), "yyyy.MM.dd hh:mm:ss"); // 将QString转换为QDateTime对象
			int timestamp = nowTime.toSecsSinceEpoch(); // 将QDateTime对象转换为时间戳
			for (const caliResu& cali : proCali) {
				if (cali.caliTime == timestamp) {
					ui.labelPCaliName->setText(cali.caliName);
					ui.labelPCaliTime->setText(ui.comCheck->currentText());
					ui.labelPCaliCAL1->setText(QString::number(cali.dataCAL1));
					ui.labelPCaliCAL2->setText(QString::number(cali.dataCAL2));
					ui.spinBoxPValue->setValue(cali.dataVlo);
					proDataA = cali.dataA;
					proDataB = cali.dataB;
					break;
				}
			}
		}

		});
	//返回按钮
	connect(ui.pushBack, &QPushButton::clicked, [=]() {
			emit backMain();
		});
	//新增按钮
	connect(ui.pushAdd, &QPushButton::clicked, [=]() {
		// 获取当前行数
		int row = ui.tableProTest->rowCount();

		// 插入新行
		ui.tableProTest->insertRow(row);

		// 设置该行每个单元格为空
		for (int i = 0; i < ui.tableProTest->columnCount(); i++) {
			QTableWidgetItem* item = new QTableWidgetItem("");
			item->setTextAlignment(Qt::AlignCenter); // 设置文字居中
			ui.tableProTest->setItem(row, i, item);
		}
		});
	//应用按钮
	connect(ui.pushOK, &QPushButton::clicked, [=]() {
		QList<QTableWidgetItem*> selectedItems = ui.tableProTest->selectedItems();

		if (selectedItems.isEmpty()) {
			int res;
			MyMessageBox msgBox(this, MsgBoxType_Warn, QStringLiteral("项目未选择"), QStringLiteral("确认"), QStringLiteral("取消"));
			res = msgBox.exec();
		}
		else {
		    selectedRow = selectedItems.first()->row();

			// 获取选中行的第一列的文本
			QString firstColumnText = ui.tableProTest->item(selectedRow, 0)->text();
			if (firstColumnText == "") {
				int res;
				MyMessageBox msgBox(this, MsgBoxType_Warn, QStringLiteral("项目名称为空"), QStringLiteral("确认"), QStringLiteral("取消"));
				res = msgBox.exec();
			}
			else {
				nowTestName = firstColumnText;
				ui.stackedWidget->setCurrentIndex(1);
				if (ui.comCheck->currentIndex() == 0) {
					ui.stackedWidget_2->setCurrentIndex(1);
					ui.labelSam1->setText("\\");
					ui.labelSam2->setText("\\");
					ui.labelSam3->setText("\\");
					ui.labelSam4->setText("\\");
					ui.labelSam5->setText("\\");
					ui.labelSam6->setText("\\");
					ui.labelSam7->setText("\\");
					ui.labelSam8->setText("\\");

				}
				else {
					ui.stackedWidget_2->setCurrentIndex(0);
					QDateTime nowTime = QDateTime::fromString(ui.comCheck->currentText(), "yyyy.MM.dd hh:mm:ss"); // 将QString转换为QDateTime对象
					int nowcaliTime = nowTime.toSecsSinceEpoch(); // 将QDateTime对象转换为时间戳
					for (const caliResu& item : proCali) {
						if (item.caliTime == nowcaliTime) {
							QVector<int> nowdataChecks = item.dataChecks;
							for (int i = 0; i < nowdataChecks.size(); i++) {
								testNewChecks[i] = nowdataChecks[i];
								QToolButton* button = ui.centralWidget->findChild<QToolButton*>("tpProCheck" + QString::number(i + 1));
								if (button) {
									if (nowdataChecks[i]) {
										button->setIcon(QIcon(":/images/image/gou.png"));
									}
									else {
										button->setIcon(QIcon(":/images/image/cha.png"));
									}
								}
							}
							break; // 找到后退出循环
						}
					}
				}
			}
			
		}

		});
	//开始实验
	connect(ui.pushStart, &QPushButton::clicked, [=]() {

		if (ui.comCheck->currentIndex() == 0) {
			QDateTime nowTime = QDateTime::currentDateTime();
			QString nowStr = nowTime.toString("yyyy.MM.dd hh:mm:ss");
			nowTestDate = nowStr;
			ui.tableProTest->item(selectedRow, 1)->setText(nowTestDate);
			emit startPro(0);
		}
		else {
			QDateTime nowTime = QDateTime::currentDateTime();
			QString nowStr = nowTime.toString("yyyy.MM.dd hh:mm:ss");
			nowTestDate = nowStr;
			ui.tableProTest->item(selectedRow, 1)->setText(nowTestDate);
			emit startPro(0);
			ui.stackedWidget_2->setCurrentIndex(1);
			ui.tpProCheck1->setEnabled(false);
			ui.tpProCheck2->setEnabled(false);
			ui.tpProCheck3->setEnabled(false);
			ui.tpProCheck4->setEnabled(false);
			ui.tpProCheck5->setEnabled(false);
			ui.tpProCheck6->setEnabled(false);
			ui.tpProCheck7->setEnabled(false);
			ui.tpProCheck8->setEnabled(false);
		}

		});
	//保存数据
	connect(ui.pushSave, &QPushButton::clicked, [=]() {
		//判断CAL1和CAL2是否为空
		if (ui.labelTube1->text() != "" && ui.labelTube2->text() != "" && ui.labelTube3->text() != "" && ui.labelTube4->text() != "" &&
			ui.labelTube5->text() != "" && ui.labelTube6->text() != "" && ui.labelTube7->text() != "" && ui.labelTube8->text() != "" ) {
			
			QDateTime nowTime = QDateTime::fromString(nowTestDate, "yyyy.MM.dd hh:mm:ss"); // 将QString转换为QDateTime对象
			int timestamp = nowTime.toSecsSinceEpoch(); // 将QDateTime对象转换为时间戳
			QVector<int> saveList;//保存时的8个孔的值
			int caliTime = 0;
			if (ui.comCheck->currentIndex() != 0) {
				QDateTime nowTime = QDateTime::fromString(ui.comCheck->currentText(), "yyyy.MM.dd hh:mm:ss"); // 将QString转换为QDateTime对象
				caliTime = nowTime.toSecsSinceEpoch(); // 将QDateTime对象转换为时间戳
			}


			testResu tResult = {timestamp,nowTestName,caliTime,testNewChecks,intList };

			emit sendSaveSingleTest(tResult);

		}
		else {
			int res;
			MyMessageBox msgBox(this, MsgBoxType_Error, QStringLiteral("检测信息未齐全！"), QStringLiteral("确认"), QStringLiteral("取消"));
			res = msgBox.exec();
		}
		});
	//开始实验的8个勾
	
	connect(ui.tpProCheck1, &QToolButton::clicked, [=]() {
		if (testNewChecks[0] == 1) {
			testNewChecks[0] = 0;
			ui.tpProCheck1->setIcon(QIcon(":/images/image/cha.png"));
		}
		else if (testNewChecks[0] == 0) {
			testNewChecks[0] = 1;
			ui.tpProCheck1->setIcon(QIcon(":/images/image/gou.png"));
		}
		});
	connect(ui.tpProCheck2, &QToolButton::clicked, [=]() {
		if (testNewChecks[1] == 1) {
			testNewChecks[1] = 0;
			ui.tpProCheck2->setIcon(QIcon(":/images/image/cha.png"));
		}
		else if (testNewChecks[1] == 0) {
			testNewChecks[1] = 1;
			ui.tpProCheck2->setIcon(QIcon(":/images/image/gou.png"));
		}
		});
	connect(ui.tpProCheck3, &QToolButton::clicked, [=]() {
		if (testNewChecks[2] == 1) {
			testNewChecks[2] = 0;
			ui.tpProCheck3->setIcon(QIcon(":/images/image/cha.png"));
		}
		else if (testNewChecks[2] == 0) {
			testNewChecks[2] = 1;
			ui.tpProCheck3->setIcon(QIcon(":/images/image/gou.png"));
		}
		});
	connect(ui.tpProCheck4, &QToolButton::clicked, [=]() {
		if (testNewChecks[3] == 1) {
			testNewChecks[3] = 0;
			ui.tpProCheck4->setIcon(QIcon(":/images/image/cha.png"));
		}
		else if (testNewChecks[3] == 0) {
			testNewChecks[3] = 1;
			ui.tpProCheck4->setIcon(QIcon(":/images/image/gou.png"));
		}
		});
	connect(ui.tpProCheck5, &QToolButton::clicked, [=]() {
		if (testNewChecks[4] == 1) {
			testNewChecks[4] = 0;
			ui.tpProCheck5->setIcon(QIcon(":/images/image/cha.png"));
		}
		else if (testNewChecks[4] == 0) {
			testNewChecks[4] = 1;
			ui.tpProCheck5->setIcon(QIcon(":/images/image/gou.png"));
		}
		});
	connect(ui.tpProCheck6, &QToolButton::clicked, [=]() {
		if (testNewChecks[5] == 1) {
			testNewChecks[5] = 0;
			ui.tpProCheck6->setIcon(QIcon(":/images/image/cha.png"));
		}
		else if (testNewChecks[5] == 0) {
			testNewChecks[5] = 1;
			ui.tpProCheck6->setIcon(QIcon(":/images/image/gou.png"));
		}
		});
	connect(ui.tpProCheck7, &QToolButton::clicked, [=]() {
		if (testNewChecks[6] == 1) {
			testNewChecks[6] = 0;
			ui.tpProCheck7->setIcon(QIcon(":/images/image/cha.png"));
		}
		else if (testNewChecks[6] == 0) {
			testNewChecks[6] = 1;
			ui.tpProCheck7->setIcon(QIcon(":/images/image/gou.png"));
		}
		});
	connect(ui.tpProCheck8, &QToolButton::clicked, [=]() {
		if (testNewChecks[7] == 1) {
			testNewChecks[7] = 0;
			ui.tpProCheck8->setIcon(QIcon(":/images/image/cha.png"));
		}
		else if (testNewChecks[7] == 0) {
			testNewChecks[7] = 1;
			ui.tpProCheck8->setIcon(QIcon(":/images/image/gou.png"));
		}
		});
	//开始实验的doublespin
	connect(ui.spinBoxPValue, QOverload<int>::of(&QSpinBox::valueChanged),
		[=](double newValue) {
			// 在这里编写Lambda表达式的内容，可以访问newValue
			qDebug() << "New value: " << newValue;
			ui.widCircle->set_temperature(newValue);
		});
	//滑轮的数据
	connect(ui.widCircle, &set_tem::sendProValue, [=](float newValue) {
		ui.spinBoxPValue->setValue(newValue);
		});
	//开始实验的返回
	connect(ui.pushBack_2, &QPushButton::clicked, [=]() {
		if (ui.stackedWidget_2->currentIndex() == 1) {
			if (ui.comCheck->currentIndex() == 0) {
				ui.stackedWidget->setCurrentIndex(0);
			}
			else {
				ui.stackedWidget_2->setCurrentIndex(0);
				ui.tpProCheck1->setEnabled(true);
				ui.tpProCheck2->setEnabled(true);
				ui.tpProCheck3->setEnabled(true);
				ui.tpProCheck4->setEnabled(true);
				ui.tpProCheck5->setEnabled(true);
				ui.tpProCheck6->setEnabled(true);
				ui.tpProCheck7->setEnabled(true);
				ui.tpProCheck8->setEnabled(true);
			}
			
		}
		else {
			ui.stackedWidget->setCurrentIndex(0);

		}
		});
}
void elisaProject::reTestTable()
{
	QStringList headerLabels;
	for (int col = 0; col < ui.tableProTest->columnCount(); ++col) {
		headerLabels << ui.tableProTest->horizontalHeaderItem(col)->text();
	}
	// 获取当前行数
	ui.tableProTest->clear();
	ui.tableProTest->setRowCount(0);
	ui.tableProTest->setHorizontalHeaderLabels(headerLabels);

	// 插入新行
	//qDebug() << proTest.size() << "proTest.size()";
	for (int i = 0; i < proTest.size();i++) {
		int row = ui.tableProTest->rowCount();
		//qDebug() << "row" << row;
		ui.tableProTest->insertRow(row);
		QTableWidgetItem* item = new QTableWidgetItem(proTest[i].testName);
		item->setTextAlignment(Qt::AlignCenter); // 设置文字居中
		item->setFlags(item->flags() & ~Qt::ItemIsEditable); // 设置为不可编辑
		ui.tableProTest->setItem(row, 0, item);
		QDateTime dateTime = QDateTime::fromSecsSinceEpoch(proTest[i].testTime);
		// 将QDateTime对象转换为时间QString
		QString timeString = dateTime.toString("yyyy.MM.dd hh:mm:ss");
		QTableWidgetItem* item2 = new QTableWidgetItem(timeString);
		item2->setFlags(item->flags() & ~Qt::ItemIsEditable); // 设置为不可编辑
		item2->setTextAlignment(Qt::AlignCenter); // 设置文字居中
		ui.tableProTest->setItem(row, 1, item2);
	}

	//// 设置该行每个单元格为空
	//for (int i = 0; i < ui.tableProTest->columnCount(); i++) {
	//	QTableWidgetItem* item = new QTableWidgetItem("");
	//	item->setTextAlignment(Qt::AlignCenter); // 设置文字居中
	//	if (i == 0)
	//		item->setText(getTest.testName);
	//	else {
	//		QDateTime dateTime = QDateTime::fromSecsSinceEpoch(getTest.testTime);
	//		// 将QDateTime对象转换为时间QString
	//		QString timeString = dateTime.toString("yyyy.MM.dd hh:mm:ss");
	//		item->setText(timeString);
	//	}
	//	ui.tableProTest->setItem(row, i, item);
	//}
}
void elisaProject::removeAll()
{
	proCali.clear();
	proTest.clear();
	QStringList headerLabels;
	for (int col = 0; col < ui.tableProTest->columnCount(); ++col) {
		headerLabels << ui.tableProTest->horizontalHeaderItem(col)->text();
	}

	// 清除表格内容
	ui.tableProTest->clearContents();
	ui.tableProTest->setRowCount(0);

	// 重新设置表头内容
	ui.tableProTest->setHorizontalHeaderLabels(headerLabels);
	ui.comCheck->clear();
}
void elisaProject::removeOne(int delType, int delTime)
{
	if (delType == 0) {
		for (int i = 0; i < proCali.size(); ++i) {
			if (proCali[i].caliTime == delTime) {
				proCali.removeAt(i);
				ui.comCheck->removeItem(i+1);
				break;
			}
		}
	}
	else if (delType == 1) {
		for (int i = 0; i < proTest.size(); ++i) {
			if (proTest[i].testTime == delTime) {
				proTest.removeAt(i);
				break;
			}
		}
		reTestTable();
	}
}
void elisaProject::addTableCali(caliResu getCali) {
	proCali.append(getCali);

	QDateTime dateTime = QDateTime::fromSecsSinceEpoch(getCali.caliTime);
	// 将QDateTime对象转换为时间QString
	QString timeString = dateTime.toString("yyyy.MM.dd hh:mm:ss");
	ui.comCheck->addItem(timeString);

	//int row = ui.tableProCali->rowCount();
	//ui.tableProCali->insertRow(row);
	//ui.tableProCali->setItem(row, 0, new QTableWidgetItem(getCali.caliName));
	//ui.tableProCali->setItem(row, 1, new QTableWidgetItem(timeString));
	//ui.tableProCali->setItem(row, 2, new QTableWidgetItem(QString::number(getCali.dataCAL1)));
	//ui.tableProCali->setItem(row, 3, new QTableWidgetItem(QString::number(getCali.dataCAL2)));

}
void elisaProject::addTableTest(testResu getTest)
{
	proTest.append(getTest);
	//qDebug() << getTest.testTime << getTest.testName;
	reTestTable();
		// 设置该行每个单元格为空
	//int row = ui.tableProTest->rowCount();

	//for (int i = 0; i < ui.tableProTest->columnCount(); i++) {
	//	QTableWidgetItem* item = new QTableWidgetItem("");
	//	item->setTextAlignment(Qt::AlignCenter); // 设置文字居中
	//	item->setFlags(item->flags() & ~Qt::ItemIsEditable); // 设置为不可编辑
	//	if (i == 0)
	//		item->setText(getTest.testName);
	//	else {
	//		QDateTime dateTime = QDateTime::fromSecsSinceEpoch(getTest.testTime);
	//		// 将QDateTime对象转换为时间QString
	//		QString timeString = dateTime.toString("yyyy.MM.dd hh:mm:ss");
	//		item->setText(timeString);
	//	}
	//	ui.tableProTest->setItem(row, i, item);
	//}
}
//void elisaProject::saveTableTest(testResu getTest)
//{
//	proTest.append(getTest);
//	for (const testResu& test : proTest) {
//		if (test.testTime == getTest.testTime && getTest.testName == test.testName) {
//
//			break;
//		}
//	}
//}
void elisaProject::receiveNewPro(QByteArray newArray) {
	qDebug() << newArray << newArray.size();
	intList.clear();
	for (int i = 0; i < newArray.size(); i += 4) {
		QByteArray chunk = newArray.mid(i, 4);
		int intValue = 0;

		for (int j = 0; j < 4; j++) {
			intValue |= (static_cast<uchar>(chunk.at(j)) << (j * 8));
		}
		intList.append(intValue);
		qDebug() << chunk << intValue;
	}
	if ((testNewChecks[0]) == 1)
		ui.labelTube1->setText(QString::number(intList[0]));
	else if((testNewChecks[0]) == 0)
		ui.labelTube1->setText("\\");
	if ((testNewChecks[1]) == 1)
		ui.labelTube2->setText(QString::number(intList[1]));
	else if ((testNewChecks[1]) == 0)
		ui.labelTube2->setText("\\");
	if ((testNewChecks[2]) == 1)
		ui.labelTube3->setText(QString::number(intList[2]));
	else if ((testNewChecks[2]) == 0)
		ui.labelTube3->setText("\\");
	if ((testNewChecks[3]) == 1)
		ui.labelTube4->setText(QString::number(intList[3]));
	else if ((testNewChecks[3]) == 0)
		ui.labelTube4->setText("\\");
	if ((testNewChecks[4]) == 1)
		ui.labelTube5->setText(QString::number(intList[4]));
	else if ((testNewChecks[4]) == 0)
		ui.labelTube5->setText("\\");
	if ((testNewChecks[5]) == 1)
		ui.labelTube6->setText(QString::number(intList[5]));
	else if ((testNewChecks[5]) == 0)
		ui.labelTube6->setText("\\");
	if ((testNewChecks[6]) == 1)
		ui.labelTube7->setText(QString::number(intList[6]));
	else if ((testNewChecks[6]) == 0)
		ui.labelTube7->setText("\\");
	if ((testNewChecks[7]) == 1)
		ui.labelTube8->setText(QString::number(intList[7]));
	else if ((testNewChecks[7]) == 0)
		ui.labelTube8->setText("\\");
	if (ui.comCheck->currentIndex() == 0) {
		ui.labelSam1->setText("\\");
		ui.labelSam2->setText("\\");
		ui.labelSam3->setText("\\");
		ui.labelSam4->setText("\\");
		ui.labelSam5->setText("\\");
		ui.labelSam6->setText("\\");
		ui.labelSam7->setText("\\");
		ui.labelSam8->setText("\\");

	}
	else {
		if ((testNewChecks[0]) == 1)
			ui.labelSam1->setText(QString::number(intList[0]* proDataA[0]+ proDataB[0]));
		else if ((testNewChecks[0]) == 0)
			ui.labelSam1->setText("\\");
		if ((testNewChecks[1]) == 1)
			ui.labelSam2->setText(QString::number(intList[1] * proDataA[1] + proDataB[1]));
		else if ((testNewChecks[1]) == 0)
			ui.labelSam2->setText("\\");
		if ((testNewChecks[2]) == 1)
			ui.labelSam3->setText(QString::number(intList[2] * proDataA[2] + proDataB[2]));
		else if ((testNewChecks[2]) == 0)
			ui.labelSam3->setText("\\");
		if ((testNewChecks[3]) == 1)
			ui.labelSam4->setText(QString::number(intList[3] * proDataA[3] + proDataB[3]));
		else if ((testNewChecks[3]) == 0)
			ui.labelSam4->setText("\\");
		if ((testNewChecks[4]) == 1)
			ui.labelSam5->setText(QString::number(intList[4] * proDataA[4] + proDataB[4]));
		else if ((testNewChecks[4]) == 0)
			ui.labelSam5->setText("\\");
		if ((testNewChecks[5]) == 1)
			ui.labelSam6->setText(QString::number(intList[5] * proDataA[5] + proDataB[5]));
		else if ((testNewChecks[5]) == 0)
			ui.labelSam6->setText("\\");
		if ((testNewChecks[6]) == 1)
			ui.labelSam7->setText(QString::number(intList[6] * proDataA[6] + proDataB[6]));
		else if ((testNewChecks[6]) == 0)
			ui.labelSam7->setText("\\");
		if ((testNewChecks[7]) == 1)
			ui.labelSam8->setText(QString::number(intList[7] * proDataA[7] + proDataB[7]));
		else if ((testNewChecks[7]) == 0)
			ui.labelSam8->setText("\\");
	}
}
