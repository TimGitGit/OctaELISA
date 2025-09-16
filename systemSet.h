#pragma once

#include <QWidget>
#include "ui_systemSet.h"

class systemSet : public QWidget
{
	Q_OBJECT

public:
	systemSet(QWidget *parent = nullptr);
	~systemSet();
	void inUI();
	void inCon();
signals:
	void backMain();
private:
	Ui::systemSetClass ui;
};
