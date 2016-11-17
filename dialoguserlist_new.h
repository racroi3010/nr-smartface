#ifndef DIALOGUSERLIST_NEW_H
#define DIALOGUSERLIST_NEW_H

#include <QDialog>
#include <QLabel>
#include <QMessageBox>

#include "UserUtil.h"
#include "userlabel.h"
#include "Constants.h"
#include "dialoguserregister_new.h"

namespace Ui {
class DialogUserList_New;
}

class DialogUserList_New : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUserList_New(QWidget *parent = 0);
    ~DialogUserList_New();

private:
    Ui::DialogUserList_New *ui;

    std::vector<User> users;
    userlabel * items;

    void loadPage(int page);

    int numOfPage;
    int curPage;
    int columnNum;
    int rowNum;
private slots:
    void userClick();
    void on_btnMenu_clicked();
    void on_btnUp_clicked();
    void on_btnDown_clicked();
    void on_btnDelete_clicked();
    void on_btnNew_clicked();
};

#endif // DIALOGUSERLIST_NEW_H
