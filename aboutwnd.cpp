#include "aboutwnd.h"
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
}

_AboutWnd::~_AboutWnd()
{
    delete ui;
}
