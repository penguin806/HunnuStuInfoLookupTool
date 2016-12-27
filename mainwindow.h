#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    static void GenerateRegCode();
    static void GetRegisterInfo();
    static bool IsRegistered();
    static void WriteRegKey(QString _key);

private slots:
    void on_pushButton_clicked();
    void ResultsWindowClosed();
    void RequestFinished(QNetworkReply *reply);

    void on_pushButton_2_clicked();
    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *Man;
    ResultsWnd *ResWnd;
    _AboutWnd *AboutWnd;
};

#endif // MAINWINDOW_H
