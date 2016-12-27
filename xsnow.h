#ifndef XSNOW_H
#define XSNOW_H
#include <QApplication>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTextCodec>
#include <QRegExp>
#include <QSettings>
#include <QCloseEvent>
#include <QMessageBox>
#include <QClipboard>
#include <QString>
#include <QTime>
#include <QDebug>

//#ifdef Q_OS_WIN
#define XFTEXT(s) QString::fromLocal8Bit(s)
//#else
//#define XFTEXT(s) QString(s)
//#endif

extern QString _RegCode;
extern QString _RegKey;
extern bool _bRegistered;

class STU
{
public:
    QString Id;
    QString Name;
    QString ClassId;
    QString ClassName;
    QString CardId;
};


#endif // XSNOW_H
