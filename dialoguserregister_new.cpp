#include "dialoguserregister_new.h"
#include "ui_dialoguserregister_new.h"

DialogUserRegister_new::DialogUserRegister_new(QWidget *parent) :
    BaseDialog(parent),
    ui(new Ui::DialogUserRegister_new)
{
    ui->setupUi(this);

    vProcessing = new VideoProcessing(this);
    vProcessing->start();

    //ui->labelStatus->setText("<span style=\"color:#ffffff;\">License OK</span>");
    ui->labelStatus->setText("");
}

DialogUserRegister_new::~DialogUserRegister_new()
{
    delete ui;
}
void DialogUserRegister_new::updateFrame(QImage qImage)
{
    if(!qImage.isNull()){
        QPainter painter(&qImage);
        painter.setPen(QPen(Qt::red, 4));
        painter.drawRect(currentFace);
        painter.end();
        QPixmap pm = QPixmap::fromImage(qImage.scaled(IMAGE_LABEL_WIDTH_3, IMAGE_LABEL_HEIGHT_3, Qt::KeepAspectRatio));

        ui->labelImage->setPixmap(pm);
        currentFace = QRect(0, 0, 0, 0);
    }
}
void DialogUserRegister_new::updateUser(QString user)
{
    //ui->labelStatus->setText("<span style=\"color:#ffffff;\">userId:" + user +"</span>");
}
void DialogUserRegister_new::updateFace(QRect rect)
{
    currentFace = rect;
}

void DialogUserRegister_new::on_btnMenu_clicked()
{
    vProcessing->close();
    this->close();
}

void DialogUserRegister_new::on_btnUserList_clicked()
{
    vProcessing->close();
    DialogUserList_New *userList = new DialogUserList_New();
    userList->setModal(true);
    userList->show();

    this->close();
}

void DialogUserRegister_new::on_btnSave_clicked()
{
    QMessageBox *b = new QMessageBox(this);
    QString msg = "";
    QString userNumber = "";
    QString userName = "";

    // gen ramdom user number if null
    int lastId = UserUtil::getInstance()->getLastId();
    if(lastId >= 999)
    {
        b->setText("<span style=\"color:#ffffff;\">Number of user is limit 1000</span>");
    }
    else
    {
        userNumber =  QString("%1").arg(lastId + 1, 3, 'g', -1, '0');
        userName = "user" + userNumber;
        if(capImage.data == NULL)
        {
            b->setText("<span style=\"color:#ffffff;\">Please capture an image first</span>");
        }
        else if(vProcessing->checkExistUser(userNumber))
        {
            b->setText("<span style=\"color:#ffffff;\">User is exists already</span>");
        }
        else if(vProcessing->registerUser(userNumber, userName, capImage, msg))
        {
            b->setText("<span style=\"color:#ffffff;\">Success: " + userName + "</span>");
        }
        else
        {
            b->setText("<span style=\"color:#ffffff;\">Failure: " + msg + "</span>");
        }
    }


    b->show();
    capImage.data = NULL;
    vProcessing->resumeCam();
}

void DialogUserRegister_new::on_btnCapture_clicked()
{
    if(!vProcessing->capture(capImage))
    {
        QMessageBox *b = new QMessageBox(this);
        b->setText("<span style=\"color:#ffffff;\">Cannot detect face\nplease capture again</span>");
        b->show();
        vProcessing->resumeCam();
    }
}
