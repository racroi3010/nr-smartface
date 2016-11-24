#include "dialoguseranalysis_new.h"
#include "ui_dialoguseranalysis_new.h"

DialogUserAnalysis_New::DialogUserAnalysis_New(QWidget *parent) :
    BaseDialog(parent),
    ui(new Ui::DialogUserAnalysis_New)
{
    ui->setupUi(this);

    vProcessing = new VideoProcessing(this);
    vProcessing->start();

    ui->labelStatus->setText("");

    d = new DialogMatching(this);
    d->setGeometry(50, 50, 200, 100);
}

DialogUserAnalysis_New::~DialogUserAnalysis_New()
{
    delete vProcessing;
    delete d;
    delete ui;
}
void DialogUserAnalysis_New::updateFrame(QImage& qImage)
{
    if(!qImage.isNull()){
        QPixmap pm = QPixmap::fromImage(qImage.scaled(IMAGE_LABEL_WIDTH_3, IMAGE_LABEL_HEIGHT_3, Qt::KeepAspectRatio));
        QPainter painter(&qImage);
        painter.setPen(QPen(Qt::red, 4));
        painter.drawRect(currentFace);
        painter.end();

        ui->labelImage_2->setPixmap(pm);
        currentFace = QRect(0, 0, 0, 0);
    }
}
void DialogUserAnalysis_New::updateUser(QString user)
{
    if(user != "unknown")
            //&& (currentUserNumber.isNull() || currentUserNumber != user))
    {
        currentUserNumber = user;
        vProcessing->shot(currentImage);
        if(!vProcessing->saveImage(currentImage, currentUserNumber))
        {
            currentUserNumber = "";
        }
        if(!currentUserNumber.isEmpty() && d->isHidden()){
            d->setId(currentUserNumber);
            d->show();
            QTimer::singleShot(3000, d, SLOT(hide()));
            //timer->start(3000);
        }

    }
    //ui->labelStatus->setText("<span style=\"color:#ffffff;\">userId:" + currentUserNumber +"</span>");
}
void DialogUserAnalysis_New::updateFace(QRect rect)
{
    currentFace = rect;
}

void DialogUserAnalysis_New::on_btnMenu_clicked()
{
    vProcessing->close();
    this->close();
}

void DialogUserAnalysis_New::on_btnUserList_clicked()
{
    vProcessing->close();
    DialogUserListHist *userList = new DialogUserListHist();
    userList->setModal(true);
    userList->show();

    this->close();
}
