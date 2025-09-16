#pragma once

#include <QMainWindow>
#include <QDebug>
#include <QListView>
#include <QCursor>
#include <QDoubleSpinBox>
#include <QDateTime>
#include "base.h"
#include "set_tem.h"
#include "ui_elisaProject.h"

class elisaProject : public QMainWindow
{
	Q_OBJECT

public:
	elisaProject(QWidget *parent = nullptr);
	~elisaProject();
	void inUI();
	void inCon();
	void reTestTable();
	void removeAll();
	void removeOne(int,int);
public slots:
	void addTableCali(caliResu);
	void addTableTest(testResu);
	//void saveTableTest(testResu);
	void receiveNewPro(QByteArray);
signals:
	void startPro(int);
	void backMain();
	void sendSaveSingleTest(testResu);
private:
	Ui::elisaProjectClass ui;
	QVector<int> testNewChecks;//存储孔位
	QVector<int> intList;//开始检测后获得的8个值
	QList<caliResu> proCali;
	QList<testResu> proTest;
	QString nowTestName;
	QString nowTestDate;
	int selectedRow;
	QVector<float> proDataA;//直线式的A
	QVector<float> proDataB;//直线式的B
};
