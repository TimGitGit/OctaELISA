#include "mymessagebox.h"

MyMessageBox::MyMessageBox(QWidget* parent, MsgBoxType type, QString text, QString textOK, QString textCan) : QDialog(parent)
{
    initState();

    if (type == MsgBoxType_Info)
    {
        initInfo(text, textOK);
    }
    else if (type == MsgBoxType_Warn)
    {
        initWarn(text, textOK, textCan);
    }
    else if (type == MsgBoxType_Error)
    {
        initError(text, textOK);
    }
}

void MyMessageBox::initState()
{
    this->resize(240, 160);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    //setAttribute(Qt::WA_TranslucentBackground);
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    //this->setAttribute(Qt::WA_TranslucentBackground, true);
    //setAttribute(Qt::WA_TranslucentBackground);
    //setAttribute(Qt::WA_TranslucentBackground);//ÉèÖÃ±³¾°Í¸Ã÷
    
    this->setStyleSheet("QDialog{border:2px solid rgb(0,0,0);border-radius:0px; }");
    //this->setAttribute(Qt::WA_TranslucentBackground, true);

    labPic = new QLabel(this);
    labNote = new QLabel(this);

        btnSure = new QPushButton( this);
        btnCancle = new QPushButton(this);



    connect(btnSure, &QPushButton::clicked, this, &MyMessageBox::dealbtnSureClicked);
    connect(btnCancle, &QPushButton::clicked, this, &MyMessageBox::dealbtnCancelClicked);
}

void MyMessageBox::initWarn(const QString& text, const QString& textOK, const QString& textCan)
{
    int width = this->width();

    labPic->setStyleSheet("image:url(:/images/image/warning.png)");
    labPic->setGeometry(width * 0.5 - 20, 10, 40, 40);

    labNote->setStyleSheet("color:black");
    labNote->setAlignment(Qt::AlignCenter);
    labNote->setGeometry(0, 70, width, 20);
    labNote->setText(text);

    btnSure->setText(textOK);
    btnSure->setGeometry(width * 0.2 - 15, 110, 80, 30);
    //btnSure->setGeometry(width / 2 - 40, 110, 80, 30);

    btnSure->setStyleSheet("QPushButton{color:rgb(255,255,255); border:1px solid rgb(34,240,227);border-radius: 0px; background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #22f0e3, stop: 0.5 #1bb0a7, stop: 1.0 #22f0e3);}"
        "QPushButton:hover{background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #1bb0a7, stop: 0.5 #0c4e4a, stop: 1.0 #1bb0a7);}"
        "QPushButton:pressed{background-color:blue}");
    //btnCancle->hide();
    btnCancle->setText(textCan);
    btnCancle->setGeometry(width * 0.6, 110, 80, 30);
    btnCancle->setStyleSheet("QPushButton{color:rgb(255,255,255);border:1px solid rgb(34,240,227); border-radius: 0px; background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #22f0e3, stop: 0.5 #1bb0a7, stop: 1.0 #22f0e3);}"
        "QPushButton:hover{background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #1bb0a7, stop: 0.5 #0c4e4a, stop: 1.0 #1bb0a7);}"
        "QPushButton:pressed{background-color:blue}");

}

void MyMessageBox::initError(const QString& text, const QString& textOK)
{
    int width = this->width();

    labPic->setStyleSheet("image:url(:/images/image/error.png)");
    labPic->setGeometry(width * 0.5 - 20, 10, 40, 40);

    labNote->setStyleSheet("color:black");
    labNote->setAlignment(Qt::AlignCenter);
    labNote->setGeometry(0, 70, width, 20);
    labNote->setText(text);

    btnSure->setText(textOK);
    btnSure->setGeometry(width * 0.5 - 40, 110, 80, 30);
    btnSure->setStyleSheet("QPushButton{color:rgb(255,255,255);border:1px solid rgb(34,240,227);  border-radius: 0px; background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #22f0e3, stop: 0.5 #1bb0a7, stop: 1.0 #22f0e3);}"
        "QPushButton:hover{background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #1bb0a7, stop: 0.5 #0c4e4a, stop: 1.0 #1bb0a7);}"
        "QPushButton:pressed{background-color:blue}");

    btnCancle->hide();
}

void MyMessageBox::initInfo(const QString& text, const QString& textOK)
{
    int width = this->width();

    labPic->setStyleSheet("image:url(:/images/image/info.png)");
    labPic->setGeometry(width * 0.5 - 20, 10, 40, 40);

    labNote->setStyleSheet("color:black");
    labNote->setAlignment(Qt::AlignCenter);
    labNote->setGeometry(0, 70, width, 20);
    labNote->setText(text);

    btnSure->setText(textOK);
    btnSure->setGeometry(width * 0.5 - 40, 110, 80, 30);
    btnSure->setStyleSheet("QPushButton{color:rgb(255,255,255);border:1px solid rgb(34,240,227); border-radius: 0px; background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #22f0e3, stop: 0.5 #1bb0a7, stop: 1.0 #22f0e3);}"
        "QPushButton:hover{background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #1bb0a7, stop: 0.5 #0c4e4a, stop: 1.0 #1bb0a7);}"
        "QPushButton:pressed{background-color:blue}");

    btnCancle->hide();
}

void MyMessageBox::dealbtnSureClicked()
{
    this->accept();
}

void MyMessageBox::dealbtnCancelClicked()
{
    this->reject();
}
