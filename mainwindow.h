#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTextCodec>
#include <QRegExp>
#include <QDebug>
#include "xsnow.h"
#include "resultswnd.h"
#include "aboutwnd.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void SendNetworkRequest();

private slots:
    void on_pushButton_clicked();
    void ResultsWindowClosed();
    void RequestFinished(QNetworkReply *reply);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *Man;
    ResultsWnd *ResWnd;
    _AboutWnd *AboutWnd;
};

#endif // MAINWINDOW_H
