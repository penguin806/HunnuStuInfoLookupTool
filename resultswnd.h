#ifndef RESULTSWND_H
#define RESULTSWND_H

#include <QMainWindow>

namespace Ui {
class ResultsWnd;
}

class ResultsWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit ResultsWnd(QWidget *parent = 0);
    ~ResultsWnd();

private:
    Ui::ResultsWnd *ui;
};

#endif // RESULTSWND_H
