#include "dialoguserlisthist.h"
#include "ui_dialoguserlisthist.h"

DialogUserListHist::DialogUserListHist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUserListHist)
{
    ui->setupUi(this);

    this->setFixedSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);

    users = UserUtil::getInstance()->readXMLHistDom();

    curPage = 1;
    columnNum = 2;
    rowNum = 2;
    numOfPage = (int)(std::ceil((float)users.size()/(columnNum * rowNum)));
    numOfPage = numOfPage == 0 ? 1 : numOfPage;
    ui->labelPage->setText("<span style=\"color:#ffffff;\">" + QString::number(curPage) + "/" + QString::number(numOfPage) +"</span>");

    // initialize view
    items = new userlabelhist[columnNum * rowNum];
    for(int i = 0; i < columnNum * rowNum; i ++)
    {
        items[i].setFixedSize(IMAGE_LABEL_WIDTH_4, IMAGE_LABEL_HEIGHT_4);
        ui->gridLayout_3->addWidget(&items[i], i/columnNum, i%columnNum);
    }


    loadPage(curPage);
}

DialogUserListHist::~DialogUserListHist()
{
    delete ui;
}
void DialogUserListHist::loadPage(int page)
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
void DialogUserListHist::on_btnMenu_clicked()
{
    this->close();
}

void DialogUserListHist::on_btnDown_clicked()
{
    if(curPage < numOfPage)
    {
        curPage ++;
        ui->labelPage->setText("<span style=\"color:#ffffff;\">" + QString::number(curPage) + "/" + QString::number(numOfPage) +"</span>");
        loadPage(curPage);
    }
}

void DialogUserListHist::on_btnUp_clicked()
{
    if(curPage > 1)
    {
        curPage --;
        ui->labelPage->setText("<span style=\"color:#ffffff;\">" + QString::number(curPage) + "/" + QString::number(numOfPage) +"</span>");
        loadPage(curPage);
    }
}
