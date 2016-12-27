#ifndef XSNOW_H
#define XSNOW_H
#include <QString>

//#ifdef Q_OS_WIN
//#define XFTEXT(s) QString::fromUtf8(s)
#define XFTEXT(s) QString::fromLocal8Bit(s)
//#else
//#define XFTEXT(s) QString(s)
//#endif

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
