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
    //��������Ӧ��С��
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);

    QApplication a(argc, argv);

    static QSharedMemory* singleApp = new QSharedMemory("SingleApp");
    if (!singleApp->create(1))
    {
        QMessageBox::warning(NULL, "Warm!", "this App is already running!"); //������ʾ�� ע�⣺����ʾӦ���� qApp->quit();֮ǰ��������ʾ�򽫻�һ������
        a.quit();
        delete singleApp; // �ͷ�QSharedMemory����
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
    QDateTime currentTime = QDateTime::currentDateTime();   //��¼��ǰʱ��
    while (time.secsTo(currentTime) <= 2)                   //5Ϊ��Ҫ9��ʱ������
    {
        //qDebug() << time.secsTo(currentTime);
        a.processEvents();
        currentTime = QDateTime::currentDateTime();
    };
    splash.hide();

    MainWindow w;
    w.show();
    int result = a.exec();
    delete singleApp; // �������ʱ�ͷ�QSharedMemory����
    return result;
    //return a.exec();
}
