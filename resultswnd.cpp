#include "resultswnd.h"
#include "ui_resultswnd.h"

ResultsWnd::ResultsWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ResultsWnd)
{
    ui->setupUi(this);

#ifdef Q_OS_WIN
    this->ui->statusbar->showMessage(XFTEXT("Tip: 双击查看详情~"),10000);

    connect(this->ui->tableWidget,
            SIGNAL(cellDoubleClicked(int,int)),
            this,
            SLOT(TableItemClicked(int,int)));
#else
    this->ui->statusbar->showMessage(XFTEXT("Tip: 单击查看详情~"),10000);

    connect(this->ui->tableWidget,
            SIGNAL(cellClicked(int,int)),
            this,
            SLOT(TableItemClicked(int,int)));
#endif

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
    if(List.length() < 1)
    {
        QMessageBox::information(this,
                     "233","404 Not Found     \r\n");
    }

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

void ResultsWnd::TableItemClicked(int row, int col)
{
    QString Buffer;
    QTableWidgetItem *item;
    item = this->ui->tableWidget->item(row,col);

    if(item == nullptr)
    {
        return;
    }
    Buffer = item->text();

    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(Buffer);

    QMessageBox::information(this,
                 XFTEXT("雪峰"),Buffer);
    this->ui->statusbar->showMessage(XFTEXT("已复制到剪切板..."),2000);

}

void ResultsWnd::HideSomeDetails(QList<STU> &List)
{
    int length = List.length();
    for(int i = 0;i<length;i++)
    {
        if(List[i].Id == "201630185017")
        {
            List[i].Id = "201623333333";
            List[i].CardId = "6666666666666666666";
            continue;
        }

        int length = List[i].Id.length();
        if(length >= 5)
        {
            List[i].Id.replace(length-4,2,"**");
        }

        length = List[i].CardId.length();
        if(length >= 8)
        {
            List[i].CardId.replace(length-7, 5,"*****");
        }
    }
}
