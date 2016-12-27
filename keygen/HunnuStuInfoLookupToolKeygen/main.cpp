#include <QCoreApplication>
#include <QTextStream>

QString CalcRegKey(QString _RegCode);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream in(stdin);
    QTextStream out(stdout);
    QString Buffer;

    in >> Buffer;
    out << CalcRegKey(Buffer) << endl;

    in >> Buffer;
    return 0;
    //return a.exec();
}

QString CalcRegKey(QString _RegCode)
{
    const QByteArray Table("XUEFENGLOVEXINXIN");
    int lTable = Table.length();
    int lRegCode = _RegCode.length();

    if(lRegCode < 11)
    {
        return "ERROR\n";
    }

    QByteArray RegCode = _RegCode.toLocal8Bit();
    QString RegKey("XSNOW");

    int i = 5;

    for(;i < lRegCode;i++)
    {
        QChar t = 'A' + (RegCode[i] +
                         Table[i % lTable])%26;
        RegKey.append(t);
    }

    return RegKey;
}
