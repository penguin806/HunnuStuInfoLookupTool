#ifndef ABOUTWND_H
#define ABOUTWND_H

#include <QMainWindow>

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

private:
    Ui::_AboutWnd *ui;
};

#endif // ABOUTWND_H
