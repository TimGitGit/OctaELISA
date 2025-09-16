#pragma once

#include <QMainWindow>
#include <QDebug>
#include <Eigen\Dense>
#include <QDateTime>
#include <QDoubleValidator>
#include "base.h"
#include "ui_elisaMain.h"


class elisaMain : public QMainWindow
{
	Q_OBJECT

public:
	elisaMain(QWidget *parent = nullptr);
	~elisaMain();
	void inUI();
	void inCon();
	void linearFit(const QVector<double>& xData, const QVector<double>& yData);//Ö±ÏßÊ½

public slots:
	void receiveNewMain(QByteArray);
signals:
	void backMain();
	void startMain(int);
	void sendSaveSingleCali(caliResu);
private:
	Ui::elisaMainClass ui;
	int firstOrNot = 0;
	QDoubleValidator* validator;
	QIntValidator* intValidator;
	QVector<int> caliNewChecks;//´æ´¢¿×Î»
	QVector<float> caliNewA; // ´æ´¢A
	QVector<float> caliNewB; // ´æ´¢B
};
