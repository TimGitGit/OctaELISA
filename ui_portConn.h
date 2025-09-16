/********************************************************************************
** Form generated from reading UI file 'portConn.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PORTCONN_H
#define UI_PORTCONN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_portConnClass
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_18;
    QFrame *proMainLine_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_7;
    QLabel *label_8;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineMainName;
    QComboBox *comPort;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushBack;
    QPushButton *pushUse;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QWidget *portConnClass)
    {
        if (portConnClass->objectName().isEmpty())
            portConnClass->setObjectName(QString::fromUtf8("portConnClass"));
        portConnClass->resize(596, 391);
        gridLayout = new QGridLayout(portConnClass);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, -1, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(0);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        label_18 = new QLabel(portConnClass);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        QFont font;
        font.setPointSize(12);
        label_18->setFont(font);

        horizontalLayout_21->addWidget(label_18);

        proMainLine_2 = new QFrame(portConnClass);
        proMainLine_2->setObjectName(QString::fromUtf8("proMainLine_2"));
        proMainLine_2->setStyleSheet(QString::fromUtf8(""));
        proMainLine_2->setFrameShape(QFrame::HLine);
        proMainLine_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_21->addWidget(proMainLine_2);

        horizontalLayout_21->setStretch(0, 1);
        horizontalLayout_21->setStretch(1, 24);

        verticalLayout_4->addLayout(horizontalLayout_21);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_7 = new QLabel(portConnClass);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QFont font1;
        font1.setPointSize(11);
        label_7->setFont(font1);
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_7);

        label_8 = new QLabel(portConnClass);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font1);
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_8);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lineMainName = new QLineEdit(portConnClass);
        lineMainName->setObjectName(QString::fromUtf8("lineMainName"));
        lineMainName->setFont(font1);

        verticalLayout_2->addWidget(lineMainName);

        comPort = new QComboBox(portConnClass);
        comPort->setObjectName(QString::fromUtf8("comPort"));
        comPort->setMinimumSize(QSize(140, 30));
        comPort->setMaximumSize(QSize(16777215, 16777215));
        comPort->setFont(font1);

        verticalLayout_2->addWidget(comPort);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushBack = new QPushButton(portConnClass);
        pushBack->setObjectName(QString::fromUtf8("pushBack"));
        pushBack->setMinimumSize(QSize(140, 35));
        pushBack->setMaximumSize(QSize(140, 35));
        pushBack->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/image/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushBack->setIcon(icon);
        pushBack->setIconSize(QSize(20, 20));

        horizontalLayout_2->addWidget(pushBack);

        pushUse = new QPushButton(portConnClass);
        pushUse->setObjectName(QString::fromUtf8("pushUse"));
        pushUse->setMinimumSize(QSize(140, 35));
        pushUse->setMaximumSize(QSize(140, 35));
        pushUse->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/image/use.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushUse->setIcon(icon1);
        pushUse->setIconSize(QSize(20, 20));

        horizontalLayout_2->addWidget(pushUse);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_3->addLayout(verticalLayout_3);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        verticalLayout_4->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout_4, 0, 0, 1, 1);


        retranslateUi(portConnClass);

        QMetaObject::connectSlotsByName(portConnClass);
    } // setupUi

    void retranslateUi(QWidget *portConnClass)
    {
        portConnClass->setWindowTitle(QCoreApplication::translate("portConnClass", "portConn", nullptr));
        label_18->setText(QCoreApplication::translate("portConnClass", "\344\270\262\345\217\243\350\277\236\346\216\245", nullptr));
        label_7->setText(QCoreApplication::translate("portConnClass", "\345\275\223\345\211\215\344\270\262\345\217\243\357\274\232", nullptr));
        label_8->setText(QCoreApplication::translate("portConnClass", "\344\270\262\345\217\243\345\210\227\350\241\250\357\274\232", nullptr));
        pushBack->setText(QCoreApplication::translate("portConnClass", "\350\277\224\345\233\236", nullptr));
        pushUse->setText(QCoreApplication::translate("portConnClass", "\345\272\224\347\224\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class portConnClass: public Ui_portConnClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PORTCONN_H
