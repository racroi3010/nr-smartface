#ifndef DIALOGSETTING_H
#define DIALOGSETTING_H

#include <QDialog>

#include "Constants.h"
#include "preferencehandler.h"
#include <QMessageBox>

namespace Ui {
class DialogSetting;
}

class DialogSetting : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSetting(QWidget *parent = 0);
    ~DialogSetting();

private slots:
    void on_btnMenu_clicked();

    void on_btnSave_clicked();

private:
    Ui::DialogSetting *ui;
};

#endif // DIALOGSETTING_H
