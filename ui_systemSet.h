/********************************************************************************
** Form generated from reading UI file 'systemSet.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEMSET_H
#define UI_SYSTEMSET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_systemSetClass
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_18;
    QFrame *proMainLine_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_7;
    QLineEdit *lineMainName;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_15;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushBack;
    QPushButton *pushUse;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *systemSetClass)
    {
        if (systemSetClass->objectName().isEmpty())
            systemSetClass->setObjectName(QString::fromUtf8("systemSetClass"));
        systemSetClass->resize(600, 400);
        gridLayout_2 = new QGridLayout(systemSetClass);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(0);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        label_18 = new QLabel(systemSetClass);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        QFont font;
        font.setPointSize(12);
        label_18->setFont(font);

        horizontalLayout_21->addWidget(label_18);

        proMainLine_2 = new QFrame(systemSetClass);
        proMainLine_2->setObjectName(QString::fromUtf8("proMainLine_2"));
        proMainLine_2->setStyleSheet(QString::fromUtf8(""));
        proMainLine_2->setFrameShape(QFrame::HLine);
        proMainLine_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_21->addWidget(proMainLine_2);

        horizontalLayout_21->setStretch(0, 1);
        horizontalLayout_21->setStretch(1, 24);

        verticalLayout_2->addLayout(horizontalLayout_21);

        groupBox = new QGroupBox(systemSetClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setAlignment(Qt::AlignCenter);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(0);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignCenter);

        horizontalLayout_23->addWidget(label_7);

        lineMainName = new QLineEdit(groupBox);
        lineMainName->setObjectName(QString::fromUtf8("lineMainName"));
        lineMainName->setFont(font);

        horizontalLayout_23->addWidget(lineMainName);

        horizontalLayout_23->setStretch(0, 1);

        horizontalLayout->addLayout(horizontalLayout_23);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(0);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_3);

        pushBack = new QPushButton(groupBox);
        pushBack->setObjectName(QString::fromUtf8("pushBack"));
        pushBack->setMinimumSize(QSize(140, 35));
        pushBack->setMaximumSize(QSize(140, 35));
        QFont font1;
        font1.setPointSize(11);
        pushBack->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/image/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushBack->setIcon(icon);
        pushBack->setIconSize(QSize(20, 20));

        horizontalLayout_15->addWidget(pushBack);

        pushUse = new QPushButton(groupBox);
        pushUse->setObjectName(QString::fromUtf8("pushUse"));
        pushUse->setMinimumSize(QSize(140, 35));
        pushUse->setMaximumSize(QSize(140, 35));
        pushUse->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/image/use.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushUse->setIcon(icon1);
        pushUse->setIconSize(QSize(20, 20));

        horizontalLayout_15->addWidget(pushUse);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_15);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(systemSetClass);

        QMetaObject::connectSlotsByName(systemSetClass);
    } // setupUi

    void retranslateUi(QWidget *systemSetClass)
    {
        systemSetClass->setWindowTitle(QCoreApplication::translate("systemSetClass", "systemSet", nullptr));
        label_18->setText(QCoreApplication::translate("systemSetClass", "\347\263\273\347\273\237\350\256\276\347\275\256", nullptr));
        groupBox->setTitle(QCoreApplication::translate("systemSetClass", "\346\213\237\345\220\210\346\233\262\347\272\277", nullptr));
        label_7->setText(QCoreApplication::translate("systemSetClass", "\346\213\237\345\220\210\346\233\262\347\272\277\357\274\232", nullptr));
        lineMainName->setInputMask(QString());
        lineMainName->setPlaceholderText(QCoreApplication::translate("systemSetClass", "\346\232\202\346\234\252\345\274\200\345\217\221", nullptr));
        pushBack->setText(QCoreApplication::translate("systemSetClass", "\350\277\224\345\233\236", nullptr));
        pushUse->setText(QCoreApplication::translate("systemSetClass", "\345\272\224\347\224\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class systemSetClass: public Ui_systemSetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMSET_H
