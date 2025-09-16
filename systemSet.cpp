#include "systemSet.h"

systemSet::systemSet(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	inUI();
	inCon();
}

systemSet::~systemSet()
{}

void systemSet::inUI()
{
	ui.pushBack->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pushUse->setCursor(QCursor(Qt::PointingHandCursor));

}

void systemSet::inCon()
{
	//���ذ�ť
	connect(ui.pushBack, &QPushButton::clicked, [=]() {
		emit backMain();
		});
}
