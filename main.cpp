#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QSplashScreen>
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>
#include <QSharedMemory>
int main(int argc, char *argv[])
{
    //字体自适应大小，
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);

    QApplication a(argc, argv);

    static QSharedMemory* singleApp = new QSharedMemory("SingleApp");
    if (!singleApp->create(1))
    {
        QMessageBox::warning(NULL, "Warm!", "this App is already running!"); //弹出提示框 注意：该提示应该在 qApp->quit();之前，否则提示框将会一闪而过
        a.quit();
        delete singleApp; // 释放QSharedMemory对象
        return -1;
    }

    //Bus_App_Region({ true,false,0xffff,30000,AppData_task });

    QFile qss(":/images/image/myQSS.qss");
    qss.open(QFile::ReadOnly);
    a.setStyleSheet(qss.readAll());
    qss.close();



    QPixmap lodingPix(":/images/image/openLogo.png");
    QSplashScreen splash(lodingPix);
    splash.show();
    QDateTime time = QDateTime::currentDateTime();
    QDateTime currentTime = QDateTime::currentDateTime();   //记录当前时间
    while (time.secsTo(currentTime) <= 2)                   //5为需要9延时的秒数
    {
        //qDebug() << time.secsTo(currentTime);
        a.processEvents();
        currentTime = QDateTime::currentDateTime();
    };
    splash.hide();

    MainWindow w;
    w.show();
    int result = a.exec();
    delete singleApp; // 程序结束时释放QSharedMemory对象
    return result;
    //return a.exec();
}
