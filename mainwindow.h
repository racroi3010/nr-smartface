#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QException>
#include <QMessageBox>
#include <QDir>
#include <QTimer>
#include <QDateTime>


#include "dialoguserregister_new.h"
#include "dialoguseranalysis_new.h"
#include "dialoguserlist_new.h"
#include "dialogsetting.h"
#include "checklicensethread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_btnExit_clicked();

    void on_btnRegister_clicked();

    void on_btnAnalysis_clicked();

    void on_btnUserList_clicked();

    void on_btnSetting_clicked();

    void showTime();

    void startLicenseChecking();
    void checkLicense(bool result);

private:
    Ui::MainWindow *ui;
    VideoProcessing *vProcessing;
    BaseDialog *dialog;

    QMessageBox *msgBox;
};

#endif // MAINWINDOW_H
