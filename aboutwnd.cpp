#include "aboutwnd.h"
#include "mainwindow.h"
#include "xsnow.h"
#include "ui_aboutwnd.h"

_AboutWnd::_AboutWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::_AboutWnd)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() |
                         Qt::WindowStaysOnTopHint |
                         Qt::WindowCloseButtonHint);
    this->ui->label->setOpenExternalLinks(true);
    this->ui->lineEdit->setReadOnly(true);
    this->ui->lineEdit->setText(_RegCode);

    if(_bRegistered)
    {
        this->ui->pushButton->setDisabled(true);
        this->ui->lineEdit->setDisabled(true);
        this->ui->lineEdit_2->setText(XFTEXT("Ñ©·åÒÑÊÚÈ¨"));
        this->ui->lineEdit_2->setDisabled(true);
        this->ui->label_2->setText(
        XFTEXT("<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">[ÒÑ×¢²á]</span></p></body></html>"));
    }
    else
    {
        this->ui->label_2->setText(
        XFTEXT("<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">[Î´×¢²á°æ]</span></p></body></html>"));
    }
}

_AboutWnd::~_AboutWnd()
{
    delete ui;
}

void _AboutWnd::on_pushButton_2_clicked()
{
    this->close();
}

void _AboutWnd::on_lineEdit_selectionChanged()
{
    // do something
}

void _AboutWnd::on_pushButton_clicked()
{
    _RegKey = this->ui->lineEdit_2->text();
    MainWindow::WriteRegKey(_RegKey);

    QMessageBox::information(this,
                 "Ñ©·å^_^","×¢²áÐÅÏ¢Ð´Èë³É¹¦, Relaunch...");
    qApp->quit();
}
