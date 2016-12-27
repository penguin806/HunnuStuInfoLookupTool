#include "xsnow.h"
#include "mainwindow.h"


QString _RegCode, _RegKey;
bool _bRegistered;

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("gb2312");
    QTextCodec::setCodecForLocale(codec);

    qsrand(QTime::currentTime().msec());
    QApplication a(argc, argv);

    MainWindow::GetRegisterInfo();
    if(MainWindow::IsRegistered())
    {
        _bRegistered = true;
    }
    else
    {
        _bRegistered = false;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
