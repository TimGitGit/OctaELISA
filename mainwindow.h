#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QListView>
#include <QSettings>
#include <QCryptographicHash>
#include <QClipboard>

#include "mainwidget.h"
#include "qaesencryption.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

        Q_PROPERTY(int rotation READ rotation WRITE setRotation);
    Q_PROPERTY(int ronation READ ronation WRITE setRonation);

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void inUI();
    void initCon();
    QString getComputerUUID();
    void checkIniFile();
    QString md5Hash(const QString&);
    mainWidget* mainW = NULL;
    int rotation() const
    {
        return m_rotation;
    }
    int ronation() const
    {
        return m_ronation;
    }
signals:
    //void sendUserName(QString);
public slots:
    void showThis();//登出至登录界面
    void setRotation(int rotation)
    {
        m_rotation = rotation;
        update();
    }
    void setRonation(int ronation)
    {
        m_ronation = ronation;
        update();
    }
protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
private:
    Ui::MainWindow* ui;
    QPoint last;

    QPropertyAnimation* animation = NULL;
    QPropertyAnimation* animation2 = NULL;

    int m_rotation;
    int m_ronation;
    QString key = "5891237813749485";
    QString iv = "4932080975671358";
};
#endif // MAINWINDOW_H
