#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("HunnuStuInfoLookupTool");
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
    ComboText.append("名字");
    // ComboText.append("学号");
    ComboText.append("银行卡号");
    ComboText.append("身份证号");

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
    this->SendNetworkRequest();
}

void MainWindow::RequestFinished(QNetworkReply *reply)
{
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

    if(this->ui->comboBox->currentText() == "姓名")
    {
        formdata.append("TXTXH=&TXTXM=");
        formdata.append(buf_encoded);
        formdata.append("&TXTZH=&TXTSFZH=&CmdFind=%A1%A1%B2%E9%A1%A1%D1%AF%A1%A1");
    }
    else if(this->ui->comboBox->currentText() == "银行卡号")
    {
        formdata.append("TXTXH=&TXTXM=&TXTZH=");
        formdata.append(buf_encoded);
        formdata.append("&TXTSFZH=&CmdFind=%A1%A1%B2%E9%A1%A1%D1%AF%A1%A1");
    }
    else if(this->ui->comboBox->currentText() == "身份证号")
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
    QTime time = QTime::currentTime();
    qsrand(time.msec());

    if(arg1 == "名字")
    {
        int x = qrand() * 1000 % 4;
        if(x == 0)
            this->ui->lineEdit->setText("鹿目圆香");
        else
            this->ui->lineEdit->setText("雪峰");
    }
    else
    {
        this->ui->lineEdit->setText("233333");
    }
}
