#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QString>
#include <QVBoxLayout>
enum MsgBoxType
{
    MsgBoxType_Warn = 0,
    MsgBoxType_Info = 1,
    MsgBoxType_Error = 2,
};

class MyMessageBox : public QDialog
{

public:
    MyMessageBox(QWidget* parent, MsgBoxType type, QString text,QString textOK, QString textCan);

    void initState();

    void initWarn(const QString& text, const QString& textOK, const QString& textCan);
    void initError(const QString& text, const QString& textOK);
    void initInfo(const QString& text, const QString& textOK);

signals:

public slots:
    void dealbtnSureClicked();
    void dealbtnCancelClicked();

private:
    QLabel* labPic;
    QLabel* labNote;
    QPushButton* btnSure;
    QPushButton* btnCancle;
};