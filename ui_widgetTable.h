/********************************************************************************
** Form generated from reading UI file 'widgetTable.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETTABLE_H
#define UI_WIDGETTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widgetTableClass
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTableWidget *logTabWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *tableBack;
    QComboBox *comTable;
    QPushButton *tableUp;
    QLabel *label;
    QPushButton *tableNext;
    QSpinBox *spinBox;
    QPushButton *tableJump;
    QPushButton *tableRemove;
    QPushButton *tableRemoveAll;

    void setupUi(QWidget *widgetTableClass)
    {
        if (widgetTableClass->objectName().isEmpty())
            widgetTableClass->setObjectName(QString::fromUtf8("widgetTableClass"));
        widgetTableClass->resize(1086, 535);
        gridLayout = new QGridLayout(widgetTableClass);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        logTabWidget = new QTableWidget(widgetTableClass);
        logTabWidget->setObjectName(QString::fromUtf8("logTabWidget"));

        verticalLayout->addWidget(logTabWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableBack = new QPushButton(widgetTableClass);
        tableBack->setObjectName(QString::fromUtf8("tableBack"));
        tableBack->setMinimumSize(QSize(140, 35));
        tableBack->setMaximumSize(QSize(140, 35));
        QFont font;
        font.setPointSize(11);
        tableBack->setFont(font);

        horizontalLayout->addWidget(tableBack);

        comTable = new QComboBox(widgetTableClass);
        comTable->addItem(QString());
        comTable->addItem(QString());
        comTable->addItem(QString());
        comTable->setObjectName(QString::fromUtf8("comTable"));
        comTable->setMinimumSize(QSize(140, 30));
        comTable->setMaximumSize(QSize(140, 30));
        comTable->setFont(font);

        horizontalLayout->addWidget(comTable);

        tableUp = new QPushButton(widgetTableClass);
        tableUp->setObjectName(QString::fromUtf8("tableUp"));
        tableUp->setMinimumSize(QSize(140, 35));
        tableUp->setMaximumSize(QSize(140, 35));
        tableUp->setFont(font);

        horizontalLayout->addWidget(tableUp);

        label = new QLabel(widgetTableClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        tableNext = new QPushButton(widgetTableClass);
        tableNext->setObjectName(QString::fromUtf8("tableNext"));
        tableNext->setMinimumSize(QSize(140, 35));
        tableNext->setMaximumSize(QSize(140, 35));
        tableNext->setFont(font);

        horizontalLayout->addWidget(tableNext);

        spinBox = new QSpinBox(widgetTableClass);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setFont(font);
        spinBox->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(spinBox);

        tableJump = new QPushButton(widgetTableClass);
        tableJump->setObjectName(QString::fromUtf8("tableJump"));
        tableJump->setMinimumSize(QSize(140, 35));
        tableJump->setMaximumSize(QSize(140, 35));
        tableJump->setFont(font);

        horizontalLayout->addWidget(tableJump);

        tableRemove = new QPushButton(widgetTableClass);
        tableRemove->setObjectName(QString::fromUtf8("tableRemove"));
        tableRemove->setMinimumSize(QSize(140, 35));
        tableRemove->setMaximumSize(QSize(140, 35));
        tableRemove->setFont(font);

        horizontalLayout->addWidget(tableRemove);

        tableRemoveAll = new QPushButton(widgetTableClass);
        tableRemoveAll->setObjectName(QString::fromUtf8("tableRemoveAll"));
        tableRemoveAll->setMinimumSize(QSize(140, 35));
        tableRemoveAll->setMaximumSize(QSize(140, 35));
        tableRemoveAll->setFont(font);

        horizontalLayout->addWidget(tableRemoveAll);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(widgetTableClass);

        QMetaObject::connectSlotsByName(widgetTableClass);
    } // setupUi

    void retranslateUi(QWidget *widgetTableClass)
    {
        widgetTableClass->setWindowTitle(QCoreApplication::translate("widgetTableClass", "widgetTable", nullptr));
        tableBack->setText(QCoreApplication::translate("widgetTableClass", "\350\277\224\345\233\236", nullptr));
        comTable->setItemText(0, QCoreApplication::translate("widgetTableClass", "\345\205\250\351\203\250\351\241\271\347\233\256", nullptr));
        comTable->setItemText(1, QCoreApplication::translate("widgetTableClass", "\346\243\200\346\265\213\351\241\271\347\233\256", nullptr));
        comTable->setItemText(2, QCoreApplication::translate("widgetTableClass", "\345\256\232\346\240\207\351\241\271\347\233\256", nullptr));

        tableUp->setText(QCoreApplication::translate("widgetTableClass", "\344\270\212\344\270\200\351\241\265", nullptr));
        label->setText(QString());
        tableNext->setText(QCoreApplication::translate("widgetTableClass", "\344\270\213\344\270\200\351\241\265", nullptr));
        tableJump->setText(QCoreApplication::translate("widgetTableClass", "\350\267\263\350\275\254", nullptr));
        tableRemove->setText(QCoreApplication::translate("widgetTableClass", "\345\210\240\351\231\244", nullptr));
        tableRemoveAll->setText(QCoreApplication::translate("widgetTableClass", "\345\205\250\351\203\250\345\210\240\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widgetTableClass: public Ui_widgetTableClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETTABLE_H
