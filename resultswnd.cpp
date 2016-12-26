#include "resultswnd.h"
#include "ui_resultswnd.h"

ResultsWnd::ResultsWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ResultsWnd)
{
    ui->setupUi(this);

    this->ui->tableWidget->setFont(QFont("Microsoft YaHei"));
    this->ui->tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);
    this->ui->tableWidget->horizontalHeader()->
            setSectionResizeMode(QHeaderView::Stretch);
}

ResultsWnd::~ResultsWnd()
{
    delete ui;
}

void ResultsWnd::on_pushButton_clicked()
{
    this->close();
}

void ResultsWnd::showData(QList<STU> &List)
{
    this->ui->tableWidget->setRowCount(
                List.length()+1);

    int row = 0;
    foreach (STU data, List)
    {
        QTableWidgetItem *item0 = new
                QTableWidgetItem(data.Id);
        QTableWidgetItem *item1 = new
                QTableWidgetItem(data.Name);
        QTableWidgetItem *item2 = new
                QTableWidgetItem(data.ClassId);
        QTableWidgetItem *item3 = new
                QTableWidgetItem(data.ClassName);
        QTableWidgetItem *item4 = new
                QTableWidgetItem(data.CardId);
        this->ui->tableWidget->setItem(row,0,item0);
        this->ui->tableWidget->setItem(row,1,item1);
        this->ui->tableWidget->setItem(row,2,item2);
        this->ui->tableWidget->setItem(row,3,item3);
        this->ui->tableWidget->setItem(row,4,item4);

        row++;
    }
}

void ResultsWnd::deleteData()
{
    for(int i=0;i<this->ui->tableWidget->rowCount();i++)
    {
        for(int j=0;j<this->ui->tableWidget->columnCount();j++)
        {
            QTableWidgetItem *item =
                    this->ui->tableWidget->item(i,j);
            if(item)
            {
                delete item;
                item = nullptr;
            }
        }
    }
}

void ResultsWnd::closeEvent(QCloseEvent *event)
{
    emit Closed();
    this->deleteData();
    event->accept();
}
