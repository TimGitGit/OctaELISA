#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    inUI();
    initCon();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mainW;
    mainW = NULL;
    delete animation;
    animation = NULL;
    delete animation2;
    animation2 = NULL;
}

void MainWindow::inUI()
{
    setWindowFlags(Qt::FramelessWindowHint); //���ر�����
    setWindowIcon(QIcon(":/images/image/logo.png"));

    //��ť���������ʽ
    ui->logoShrink_4->setCursor(Qt::PointingHandCursor);
    ui->logoClose_4->setCursor(Qt::PointingHandCursor);
    ui->logoShrink->setCursor(Qt::PointingHandCursor);
    ui->logoClose->setCursor(Qt::PointingHandCursor);
    ui->logoShrink_2->setCursor(Qt::PointingHandCursor);
    ui->logoClose_2->setCursor(Qt::PointingHandCursor);
    ui->logoShrink_3->setCursor(Qt::PointingHandCursor);
    ui->logoClose_3->setCursor(Qt::PointingHandCursor);
    ui->buKeyCre->setCursor(Qt::PointingHandCursor);
    ui->buKeyCpy->setCursor(Qt::PointingHandCursor);
    ui->logoCheck->setCursor(Qt::PointingHandCursor);

    ui->logoConnect->setCursor(Qt::PointingHandCursor);
    ui->logoAdd->setCursor(Qt::PointingHandCursor);
    ui->logoChange->setCursor(Qt::PointingHandCursor);

    ui->logoAddPush->setCursor(Qt::PointingHandCursor);
    ui->logoBack_3->setCursor(Qt::PointingHandCursor);
    ui->logoBack->setCursor(Qt::PointingHandCursor);

    ui->logoChangePush->setCursor(Qt::PointingHandCursor);
    ui->logoBack_4->setCursor(Qt::PointingHandCursor);
    ui->logoBack_2->setCursor(Qt::PointingHandCursor);

    checkIniFile();

    mainW = new mainWidget();
    mainW->hide();
    ui->logoWidget->installEventFilter(this);
    ui->logoWidget_2->installEventFilter(this);
    ui->logoWidget_3->installEventFilter(this);
    ui->logoWidget_4->installEventFilter(this);

    ui->userPass->installEventFilter(this);
    ui->logoUser->setView(new QListView());
    ui->logoChangeUser->setView(new QListView());

    //��ת����
    animation = new QPropertyAnimation(this, "rotation");
    animation2 = new QPropertyAnimation(this, "ronation");

    animation->setStartValue(0);
    animation->setEndValue(180);
    animation->setDuration(2000);
    animation2->setStartValue(0);
    animation2->setEndValue(180);
    animation2->setDuration(2000);
}
QString aesEncryption(const QString val, const QString key, const QString iv)
{
    QAESEncryption encryption(QAESEncryption::AES_128, QAESEncryption::ECB, QAESEncryption::PKCS7);
    QByteArray enBA = encryption.encode(val.toUtf8(), key.toUtf8(), iv.toUtf8());
    return QString::fromLatin1(enBA.toBase64()); //�Ա����紫�䣬�򱣴��� txt���ļ���
}
void MainWindow::checkIniFile() {
    QString exePath = QCoreApplication::applicationDirPath();
    QString iniFilePath = exePath + "/config.ini";

    QFileInfo checkFile(iniFilePath);
    if (!checkFile.exists() || !checkFile.isFile()) {
        // ���ini�ļ������ڣ�����һ���µ�ini�ļ���д��Ĭ������
        QSettings settings(iniFilePath, QSettings::IniFormat);
        settings.setValue("password", "default_password");
        //qDebug() << "Ini file created with default password.";
    }
    else {
        // ���ini�ļ����ڣ���ȡ�����password
        QSettings settings(iniFilePath, QSettings::IniFormat);
        QString password = settings.value("password").toString();
        QString uuid = getComputerUUID();
        uuid = "3" + uuid + "QCLOUD";
        QString hashedUUID = md5Hash(uuid);
        if (password == hashedUUID) {
            ui->stackedWLogo->setCurrentIndex(1);

        }
    }
}
/**
 * @brief MainWindow::initCon ��ʼ���ź����
 */
 //extern tc_middle tc_m;
void MainWindow::initCon()
{
    //����ͨ��
    //connect(&tc_m, &tc_middle::sendGetData, mainW, &mainWidget::getTCData);
    //��С��ť
    connect(ui->logoShrink, &QPushButton::clicked, [=]() {
        showMinimized();
        });
    connect(ui->logoShrink_2, &QPushButton::clicked, [=]() {
        showMinimized();
        });
    connect(ui->logoShrink_3, &QPushButton::clicked, [=]() {
        showMinimized();
        });
    connect(ui->logoShrink_4, &QPushButton::clicked, [=]() {
        showMinimized();
        });
    //�رհ�ť
    connect(ui->logoClose, &QPushButton::clicked, [=]() {
        //BusDeInit();
        QApplication* app;
        app->exit(0);
        });
    connect(ui->logoClose_2, &QPushButton::clicked, [=]() {
        //BusDeInit();
        QApplication* app;
        app->exit(0);
        });
    connect(ui->logoClose_3, &QPushButton::clicked, [=]() {
        //BusDeInit();
        QApplication* app;
        app->exit(0);
        });
    connect(ui->logoClose_4, &QPushButton::clicked, [=]() {
        //BusDeInit();
        QApplication* app;
        app->exit(0);
        });
    //������Կ
    connect(ui->buKeyCre, &QPushButton::clicked, [=]() {
        QString uuid = getComputerUUID();
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString val = currentDateTime.toString("yyyy-MM-dd hh:mm");
        uuid = "3" + uuid + val;
        QString encrypt = aesEncryption(uuid, key, iv);
        ui->lineCheck_2->setText(encrypt);
        });
    //������Կ
    connect(ui->buKeyCpy, &QPushButton::clicked, [=]() {
        QClipboard* clipboard = QGuiApplication::clipboard();
        clipboard->setText(ui->lineCheck_2->text());
        });
    //У׼��ť
    connect(ui->logoCheck, &QPushButton::clicked, [=]() {
        QString uuid = getComputerUUID();
        uuid = "3" + uuid + "QCLOUD";
        QString hashedUUID = md5Hash(uuid);
        if (ui->lineCheck->text() == hashedUUID) {
            QString exePath = QCoreApplication::applicationDirPath();
            QString iniFilePath = exePath + "/config.ini";

            QFileInfo checkFile(iniFilePath);
            if (checkFile.exists() && checkFile.isFile()) {
                // ���ini�ļ����ڣ��޸������passwordΪ������
                QSettings settings(iniFilePath, QSettings::IniFormat);
                settings.setValue("password", hashedUUID);
            }
            ui->stackedWLogo->setCurrentIndex(1);

        }
        else {
            int res;
            MyMessageBox msgBox(this, MsgBoxType_Error, QStringLiteral("ע�������"), QStringLiteral("ȷ��"), QStringLiteral("ȡ��"));
            res = msgBox.exec();
        }
        });
    //��¼��ť
    connect(ui->logoConnect, &QPushButton::clicked, [=]() {
        //checkPass();
        this->hide();
        mainW->show();
        //emit sendUserName(ui->logoUser->currentText());
        });
    //mainWidget��ʾ��ǰ�û���
    //connect(this, &MainWindow::sendUserName, mainW, &mainWidget::getUserName);
    //����������
    connect(ui->logoAdd, &QPushButton::clicked, [=]() {
        ui->stackedWLogo->setCurrentIndex(2);
        ui->logoBack_3->hide();
        ui->pageLogin->hide();
        ui->pageAdd->hide();
        ui->pageChange->hide();
        animation->setDirection(QPropertyAnimation::Forward);
        animation->start();
        });
    //���޸Ľ���
    connect(ui->logoChange, &QPushButton::clicked, [=]() {
        ui->stackedWLogo->setCurrentIndex(3);
        ui->logoBack_4->hide();
        ui->pageLogin->hide();
        ui->pageAdd->hide();
        ui->pageChange->hide();
        animation2->setDirection(QPropertyAnimation::Forward);
        animation2->start();
        });
    //����������¼����
    connect(ui->logoBack, &QPushButton::clicked, [=]() {
        ui->stackedWLogo->setCurrentIndex(1);
        ui->pageLogin->hide();
        //ui->pageAdd->hide();
        ui->pageChange->hide();
        animation->setDirection(QPropertyAnimation::Backward);
        animation->start();
        });
    connect(ui->logoBack_2, &QPushButton::clicked, [=]() {
        ui->stackedWLogo->setCurrentIndex(1);
        ui->pageLogin->hide();
        ui->pageChange->hide();
        animation2->setDirection(QPropertyAnimation::Backward);
        animation2->start();
        });
    //�ǳ�����ʾ��¼����
    //connect(mainW, &mainWidget::hideMe, [=]() {
    //    this->show();
    //    mainW->hide();
    //    });
    //��������ʱ��ʾ����
    connect(animation, &QPropertyAnimation::finished, this, [=]() {
        ui->pageLogin->show();
        ui->pageAdd->show();
        if (ui->stackedWLogo->currentIndex() == 1) {
            ui->logoBack_3->show();
        }
        else {
            ui->logoBack_3->hide();
        }
        });
    connect(animation2, &QPropertyAnimation::finished, this, [=]() {
        ui->pageLogin->show();
        ui->pageChange->show();
        if (ui->stackedWLogo->currentIndex() == 1) {
            ui->logoBack_4->show();
        }
        else {
            ui->logoBack_4->hide();
        }
        });
}
/**
 * @brief MainWindow::showThis ��ʾ��¼����
 */
void MainWindow::showThis()
{
    this->show();
    mainW->hide();
}
/**
 * @brief MainWindow::getComputerUUID ���UUID
 */
QString MainWindow::getComputerUUID() {
    QSettings settings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Cryptography", QSettings::NativeFormat);
    QString uuid = settings.value("MachineGuid").toString();
    return uuid;
}
/**
 * @brief MainWindow::md5Hash ����MD5
 */
QString MainWindow::md5Hash(const QString& input) {
    QByteArray data = input.toUtf8();
    QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Md5);
    return QString(hash.toHex());
}
/**
 * @brief MainWindow::eventFilter �¼�������
 */
bool MainWindow::eventFilter(QObject* watched, QEvent* event)
{
    //��Ҫ���˵Ķ���
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            //checkPass();
            return true;
        }
    }
    if (watched == ui->logoWidget || watched == ui->logoWidget_2 || watched == ui->logoWidget_3 || watched == ui->logoWidget_4)
    {
        //��Ҫ���˵��¼�
        if (event->type() == QEvent::MouseMove)
        {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            int dx = mouseEvent->globalX() - last.x();
            int dy = mouseEvent->globalY() - last.y();
            last = mouseEvent->globalPos();
            move(x() + dx, y() + dy);

        }
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* mousePressEvent = static_cast<QMouseEvent*>(event);

            last = mousePressEvent->globalPos();

        }
        if (event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent* mousePressEvent = static_cast<QMouseEvent*>(event);

            int dx = mousePressEvent->globalX() - last.x();
            int dy = mousePressEvent->globalY() - last.y();
            move(x() + dx, y() + dy);
        }
    }
    //���������¼�������
    return QWidget::eventFilter(watched, event);
}
/**
 * @brief MainWindow::paintEvent ��¼����ķ�ת����
 * @param event
 */
void MainWindow::paintEvent(QPaintEvent* event)
{
    if (animation->state() == QPropertyAnimation::Running) {
        QPainter painter(this);

        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        QPixmap pix(this->size());

        QTransform trans;
        trans.translate(width() / 2, 0);
        if (m_rotation < 90) {
            ui->pageLogin->render(&pix);
            trans.rotate(m_rotation, Qt::YAxis);
        }
        else {
            ui->pageAdd->render(&pix);
            trans.rotate(m_rotation - 180, Qt::YAxis);
        }

        painter.setTransform(trans);
        painter.drawPixmap(-width() / 2, 0, pix);
    }
    else if (animation2->state() == QPropertyAnimation::Running) {
        QPainter painter(this);

        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        QPixmap pix(this->size());

        QTransform trans;
        trans.translate(width() / 2, 0);
        if (m_ronation < 90) {
            ui->pageLogin->render(&pix);
            trans.rotate(m_ronation, Qt::YAxis);
        }
        else {
            ui->pageChange->render(&pix);
            trans.rotate(m_ronation - 180, Qt::YAxis);
        }

        painter.setTransform(trans);
        painter.drawPixmap(-width() / 2, 0, pix);
    }
    else {
        QWidget::paintEvent(event);
    }


}

