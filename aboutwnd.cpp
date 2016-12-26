#include "aboutwnd.h"
#include "ui_aboutwnd.h"

AboutWnd::AboutWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AboutWnd)
{
    ui->setupUi(this);
}

AboutWnd::~AboutWnd()
{
    delete ui;
}
