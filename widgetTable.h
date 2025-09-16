#pragma once

#include <QWidget>
#include <QDateTime>
#include <QDebug>
#include <QListView>
#include "mymessagebox.h"
#include "ui_widgetTable.h"

class widgetTable : public QWidget
{
	Q_OBJECT

public:
	widgetTable(QWidget *parent = nullptr);
	~widgetTable();
    QList<QVariantList> m_lDatas;
    QList<QVariantList> m_lDatasAll;
    int currentPage;

    void inconn();
    void updataPage();
    void updataPageData();

    void initHeader(const QStringList& headers);

    void addLogData(const QVariantList& data);

    void addLogDatas(const QList<QVariantList>& datas);

    void getDeleteData();

    void getDeleteAllData();

    void getDeleteOneData();

signals:
    void backCheckAll();
    void searchOk();
    void tableBack();
    void showResult(QString, QString, QString);
    //void removeData(QList<int,int>);
    void removeAll();
    void removeOne(int);
public slots:
    void getCheckAll(int);
    void searchType(int);
private slots:
    void on_tableBack_clicked();//返回

    void on_tableUp_clicked();//上一页

    void on_tableNext_clicked();//下一页

    void on_tableJump_clicked();//跳转

    void on_tableRemove_clicked();//删除
private:
	Ui::widgetTableClass ui;
    int currentPageSum;
    int pageSum;
};
