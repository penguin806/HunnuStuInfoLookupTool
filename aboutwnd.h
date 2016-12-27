#ifndef ABOUTWND_H
#define ABOUTWND_H

#include "xsnow.h"

namespace Ui {
class _AboutWnd;
}

class _AboutWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit _AboutWnd(QWidget *parent = 0);
    ~_AboutWnd();

private slots:
    void on_pushButton_2_clicked();
    void on_lineEdit_selectionChanged();
    void on_pushButton_clicked();

private:
    Ui::_AboutWnd *ui;
};

#endif // ABOUTWND_H
