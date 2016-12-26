#include "resultswnd.h"
#include "ui_resultswnd.h"

ResultsWnd::ResultsWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ResultsWnd)
{
    ui->setupUi(this);
}

ResultsWnd::~ResultsWnd()
{
    delete ui;
}
