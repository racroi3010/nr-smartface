#include "dialoguserlist_new.h"
#include "ui_dialoguserlist_new.h"

DialogUserList_New::DialogUserList_New(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUserList_New)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);

    users = UserUtil::getInstance()->readXMLDom();
    for(int i = 0; i < users.size(); i ++)
    {
        users.at(i).isSelected = false;
    }

    curPage = 1;
    columnNum = 2;
    rowNum = 2;
    numOfPage = (int)(std::ceil((float)users.size()/(columnNum * rowNum)));
    numOfPage = numOfPage == 0 ? 1 : numOfPage;
    ui->labelPage->setText("<span style=\"color:#ffffff;\">" + QString::number(curPage) + "/" + QString::number(numOfPage) +"</span>");

    // initialize view
    items = new userlabel[columnNum * rowNum];
    for(int i = 0; i < columnNum * rowNum; i ++)
    {
        //items[i] = new userlabel(this);
        //labelImage->setStyleSheet("border-image: url(" + users[i].userImagePath + ") 0 0 0 0 stretch stretch;");
        items[i].setFixedSize(IMAGE_LABEL_WIDTH_4, IMAGE_LABEL_HEIGHT_4);
        connect(&items[i], SIGNAL(click()), this, SLOT(userClick()));
        ui->gridLayout->addWidget(&items[i], i/columnNum, i%columnNum);

    }


    loadPage(curPage);
}

DialogUserList_New::~DialogUserList_New()
{
    delete ui;
}
void DialogUserList_New::loadPage(int page)
{
    int start = (page - 1) * rowNum * columnNum;
    int end = page * rowNum * columnNum;
    for(int i = 0; i < rowNum * columnNum; i ++)
    {
        items[i].setUser(NULL);
    }
    for(int i = start; i < users.size() && i < end; i++)
    {
        items[i - start].setUser(&users.at(i));
    }
}

void DialogUserList_New::userClick()
{
//    QMessageBox *bx = new QMessageBox(this);
//    bx->setText("number: " + QString::number(pos));
//    bx->show();
}

void DialogUserList_New::on_btnMenu_clicked()
{
    this->close();
}

void DialogUserList_New::on_btnUp_clicked()
{
    if(curPage > 1)
    {
        curPage --;
        ui->labelPage->setText("<span style=\"color:#ffffff;\">" + QString::number(curPage) + "/" + QString::number(numOfPage) +"</span>");
        loadPage(curPage);
    }
}

void DialogUserList_New::on_btnDown_clicked()
{
    if(curPage < numOfPage)
    {
        curPage ++;
        ui->labelPage->setText("<span style=\"color:#ffffff;\">" + QString::number(curPage) + "/" + QString::number(numOfPage) +"</span>");
        loadPage(curPage);
    }
}

void DialogUserList_New::on_btnDelete_clicked()
{
    foreach (User u, users) {
        if(u.isSelected)
        {
            UserUtil::getInstance()->removeUser(u.userNumber);
        }
    }
    //users.erase();
    users = UserUtil::getInstance()->readXMLDom();
    for(int i = 0; i < users.size(); i ++)
    {
        users.at(i).isSelected = false;
    }

    curPage = 1;
    columnNum = 2;
    rowNum = 2;
    numOfPage = (int)(std::ceil((float)users.size()/(columnNum * rowNum)));
    numOfPage = numOfPage == 0 ? 1 : numOfPage;
    ui->labelPage->setText("<span style=\"color:#ffffff;\">" + QString::number(curPage) + "/" + QString::number(numOfPage) +"</span>");

    loadPage(curPage);

}

void DialogUserList_New::on_btnNew_clicked()
{
    DialogUserRegister_new *dialog = new DialogUserRegister_new();
    dialog->setModal(true);
    dialog->show();
    this->close();

}
