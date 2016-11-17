#ifndef DIALOGUSERLISTHIST_H
#define DIALOGUSERLISTHIST_H

#include <QDialog>
#include <QLabel>
#include <QMessageBox>
#include <QFileInfo>

#include "UserUtil.h"
#include "userlabelhist.h"
#include "Constants.h"

namespace Ui {
class DialogUserListHist;
}

class DialogUserListHist : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUserListHist(QWidget *parent = 0);
    ~DialogUserListHist();

private slots:
    void on_btnMenu_clicked();

    void on_btnDown_clicked();

    void on_btnUp_clicked();

private:
    Ui::DialogUserListHist *ui;
    std::vector<User> users;
    userlabelhist * items;

    void loadPage(int page);

    int numOfPage;
    int curPage;
    int columnNum;
    int rowNum;

};

#endif // DIALOGUSERLISTHIST_H
