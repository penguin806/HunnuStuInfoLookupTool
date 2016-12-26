#ifndef ABOUTWND_H
#define ABOUTWND_H

#include <QMainWindow>

namespace Ui {
class AboutWnd;
}

class AboutWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit AboutWnd(QWidget *parent = 0);
    ~AboutWnd();

private:
    Ui::AboutWnd *ui;
};

#endif // ABOUTWND_H
