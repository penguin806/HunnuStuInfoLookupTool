#ifndef RESULTSWND_H
#define RESULTSWND_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QClipboard>
#include "xsnow.h"

namespace Ui {
class ResultsWnd;
}

class ResultsWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit ResultsWnd(QWidget *parent = 0);
    ~ResultsWnd();
    void showData(QList<STU> &List);
    void deleteData();

signals:
    void Closed();

private slots:
    void on_pushButton_clicked();
    void TableItemClicked(int row,int col);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::ResultsWnd *ui;
};

#endif // RESULTSWND_H
