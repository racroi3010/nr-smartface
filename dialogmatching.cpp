#include "dialogmatching.h"
#include "ui_dialogmatching.h"
DialogMatching::DialogMatching(QWidget *parent, QString Id) :
    QDialog(parent),
    userId(Id),
    ui(new Ui::DialogMatching)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);

    QString imagePath = QDir::currentPath() + "/temp/" + Id + ".bmp";
    QImage image(imagePath);
    if(!imagePath.isNull()){
       ui->imgLabel->setPixmap(QPixmap::fromImage(image).scaled(80, 60, Qt::KeepAspectRatio));
    }
    ui->idLabel->setText("<span style=\"color:#ffffff;\">[" + Id +"]</span>");
}

DialogMatching::~DialogMatching()
{
    delete ui;
}
void DialogMatching::setId(QString Id){
    this->userId = Id;
    QString imagePath = QDir::currentPath() + "/temp/" + this->userId + ".bmp";
    QImage image(imagePath);
    if(!imagePath.isNull()){
       ui->imgLabel->setPixmap(QPixmap::fromImage(image).scaled(80, 60, Qt::KeepAspectRatio));
    }
    ui->idLabel->setText("<span style=\"color:#ffffff;\">[" + this->userId +"]</span>");
}
