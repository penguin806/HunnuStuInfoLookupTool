#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(_bRegistered)
    {
        this->setWindowTitle(XFTEXT("湖师大搜索引擎"));
    }
    else
    {
        this->setWindowTitle(XFTEXT("湖师大搜索引擎 [未注册]"));
    }

    this->setWindowIcon(QIcon(":/resource/HUNNU.ico"));
    this->ui->pushButton->setDefault(true);

    this->Man = new QNetworkAccessManager(nullptr);
    this->ResWnd = new ResultsWnd(this);
    this->AboutWnd = new _AboutWnd(this);

    connect(this->Man,
           SIGNAL(finished(QNetworkReply*)),
           this,
           SLOT(RequestFinished(QNetworkReply*)));

    connect(this->ResWnd,SIGNAL(Closed()),
            this,SLOT(ResultsWindowClosed()));

#ifdef Q_OS_WIN
    connect(this->ui->lineEdit,
            SIGNAL(returnPressed()),
            this,SLOT(on_pushButton_clicked()));
#endif


    //this->ui->plainTextEdit->document()->
    //       setMaximumBlockCount(1);

    QStringList ComboText;
    ComboText.append(XFTEXT("名字"));
    // ComboText.append(XFTEXT("学号"));
    ComboText.append(XFTEXT("银行卡号"));
    ComboText.append(XFTEXT("身份证号"));

    this->ui->comboBox->addItems(ComboText);
    this->ui->lineEdit->setText("");
}

MainWindow::~MainWindow()
{
    delete this->ResWnd;
    delete this->Man;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "saddsadsadsaas";
    this->SendNetworkRequest();
}

void MainWindow::RequestFinished(QNetworkReply *reply)
{
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->error();
        switch (reply->error()) {
        case QNetworkReply::UnknownNetworkError:
        case QNetworkReply::TimeoutError:
        case QNetworkReply::HostNotFoundError:
            QMessageBox::information(this,
                         XFTEXT("雪峰"),XFTEXT("WTF, 没网?"));
            break;
        case QNetworkReply::RemoteHostClosedError:
        case QNetworkReply::InternalServerError:
            QMessageBox::information(this,
                         XFTEXT("雪峰"), XFTEXT("服务器开小差了."));
            break;
        default:
        {
            QString _Buffer = "Error: " +
                    reply->errorString() +
                    "\r\nE-mail me if you have any question.";
            QMessageBox::information(this,XFTEXT("雪峰"),
                         _Buffer);
            break;

        }
        }
        return;
    }

    QString Buffer;
    Buffer = QString::fromLocal8Bit(reply->readAll());

    QRegExp regxa("<td class=\"[^<]*[^d]*[^i]*[^v]*[^>]*</td>");
    int position = Buffer.indexOf(regxa);

    QList<STU> StudentInfoList;

    if(position >= 0)
    {
        // qDebug()  << regxa.cap(0);
        Buffer = regxa.cap(0);

        Buffer.remove("<td class=\"center\">");
        Buffer.remove("<td class=\"left\">");
        Buffer.remove("</td>");
        Buffer.remove("<tr>");
        Buffer.remove("</tr>");
        Buffer.remove(' ');
        Buffer.remove('\t');
        Buffer.remove("&nbsp;");
        QStringList list = Buffer.split("\r\n");
        STU Temp;
        int count = 0;
        foreach (QString x, list)
        {
            switch (count % 10){
            case 0:
                Temp.Id = x;
                break;
            case 1:
                Temp.Name = x;
                break;
            case 2:
                Temp.ClassId = x;
                break;
            case 3:
                Temp.ClassName = x;
                break;
            case 5:
                Temp.CardId = x;
                StudentInfoList.append(Temp);
                break;
            default:
                break;
            }

            count++;
        }
    }
    reply->deleteLater();

    if(_bRegistered == false)
    {
        this->ResWnd->HideSomeDetails(StudentInfoList);
    }
    this->ResWnd->showData(StudentInfoList);
    this->ResWnd->show();
    this->hide();
}

void MainWindow::SendNetworkRequest()
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://cwcx.hunnu.edu.cn/cwcx/sf40/Axhfind.asp"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");

    QByteArray formdata;
    QTextCodec *gb2312 = QTextCodec::codecForName("gb2312");
    QByteArray buf_gb2312 = gb2312->fromUnicode(
    //    this->ui->plainTextEdit->toPlainText());
    this->ui->lineEdit->text());
    QByteArray buf_encoded =
        buf_gb2312.toPercentEncoding();

    if(this->ui->comboBox->currentText() == XFTEXT("名字"))
    {
        formdata.append("TXTXH=&TXTXM=");
        formdata.append(buf_encoded);
        formdata.append("&TXTZH=&TXTSFZH=&CmdFind=%A1%A1%B2%E9%A1%A1%D1%AF%A1%A1");
    }
    else if(this->ui->comboBox->currentText() == XFTEXT("银行卡号"))
    {
        formdata.append("TXTXH=&TXTXM=&TXTZH=");
        formdata.append(buf_encoded);
        formdata.append("&TXTSFZH=&CmdFind=%A1%A1%B2%E9%A1%A1%D1%AF%A1%A1");
    }
    else if(this->ui->comboBox->currentText() == XFTEXT("身份证号"))
    {
        formdata.append("TXTXH=&TXTXM=&TXTZH=&TXTSFZH=");
        formdata.append(buf_encoded);
        formdata.append("&CmdFind=%A1%A1%B2%E9%A1%A1%D1%AF%A1%A1");
    }
    else
    {
        return;
    }

    this->Man->post(request,formdata);
}

void MainWindow::ResultsWindowClosed()
{
    this->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    this->AboutWnd->show();
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1 == XFTEXT("名字"))
    {
        int x = qrand() * 10000 % 5;
        if(x == 0)
            this->ui->lineEdit->setText(XFTEXT("鹿目圆"));
        else
            this->ui->lineEdit->setText(XFTEXT("雪峰"));
    }
    else
    {
        this->ui->lineEdit->setText("233333");
    }
}

void MainWindow::GenerateRegCode()
{
    QByteArray Array("XSNOW");

    for(int i=0;i<6;i++)
    {
        char c = 'A' + qAbs(qrand()) * 100 % 25;
        Array.append(c);
        qDebug() << c;
    }

    _RegCode = QString::fromLocal8Bit(Array);

#ifdef Q_OS_WIN
    QSettings reg("HKEY_CURRENT_USER\\SOFTWARE\\XSNOW\\HUNNUSTUINFO",
                  QSettings::NativeFormat);
#else
    QSettings reg("Xsnow.info",QSettings::NativeFormat);
#endif

    reg.setValue("RegCode", _RegCode);
}

void MainWindow::GetRegisterInfo()
{
#ifdef Q_OS_WIN
    QSettings reg("HKEY_CURRENT_USER\\SOFTWARE\\XSNOW\\HUNNUSTUINFO",
                  QSettings::NativeFormat);
#else
    QSettings reg("Xsnow.info",QSettings::NativeFormat);
#endif
    QString Buffer;
    Buffer = reg.value("RegCode").toString();
    if(Buffer.length()!=11)
    {
        MainWindow::GenerateRegCode();
    }
    else
    {
        _RegCode = Buffer;
    }

    Buffer = reg.value("RegKey").toString();
    if(Buffer.isEmpty() == false)
    {
        _RegKey = Buffer;
    }
}

bool MainWindow::IsRegistered()
{
    const QByteArray Table("XUEFENGLOVEXINXIN");
    int lTable = Table.length();

    if(_RegKey == "XUEFENGLOVEXINXINFOREVER")
    {
        MainWindow::WriteRegKey("XUEFENGLOVEXINXINFOREVER");
        return true;
    }

    QString code = _RegCode;
    QString key(_RegKey);
    QByteArray regcode = code.toLocal8Bit();
    QByteArray regkey = key.toLocal8Bit();

    int lregcode = regcode.length();
    int lregkey = regkey.length();

    if(lregcode < 11 || lregkey < 11 ||
            lregcode != lregkey)
    {
        MainWindow::WriteRegKey("");
        return false;
    }

    int i = 0;
    for(;i<5;i++)
    {
        if(regcode[i] != regkey[i])
        {
            MainWindow::WriteRegKey("");
            return false;
        }
    }


    for(;i<lregcode;i++)
    {
        QChar t = 'A' + (regcode[i] +
                         Table[i % lTable])%26;
        if(t != QChar(regkey[i]))
        {
            MainWindow::WriteRegKey("");
            return false;
        }
    }
    return true;
}

void MainWindow::WriteRegKey(QString _key)
{
#ifdef Q_OS_WIN
    QSettings reg("HKEY_CURRENT_USER\\SOFTWARE\\XSNOW\\HUNNUSTUINFO",
                  QSettings::NativeFormat);
#else
    QSettings reg("Xsnow.info",QSettings::NativeFormat);
#endif

    reg.setValue("RegKey",_key);
}
