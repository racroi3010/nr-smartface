#include "dialogsetting.h"
#include "ui_dialogsetting.h"

DialogSetting::DialogSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSetting)
{
    ui->setupUi(this);

    this->setFixedSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);

    PreferenceHandler *preHandler = PreferenceHandler::getInstance();

    ui->spb_eyemax->setValue(preHandler->getEyeMax());
    ui->spb_eyemin->setValue(preHandler->getEyeMin());
    ui->spb_maxRelValue->setValue(preHandler->getMaxRelValue());
    ui->spb_relValue->setValue(preHandler->getRelValue());
}

DialogSetting::~DialogSetting()
{
    delete ui;
}

void DialogSetting::on_btnMenu_clicked()
{
    this->close();
}

void DialogSetting::on_btnSave_clicked()
{
    float relValue = ui->spb_relValue->value();
    float maxRelValue = ui->spb_maxRelValue->value();
    int eyeMin = ui->spb_eyemin->value();
    int eyeMax = ui->spb_eyemax->value();

    PreferenceHandler::getInstance()->setEyeMax(eyeMax);
    PreferenceHandler::getInstance()->setEyeMin(eyeMin);
    PreferenceHandler::getInstance()->setMaxRelValue(maxRelValue);
    PreferenceHandler::getInstance()->setRelValue(relValue);

    QMessageBox *bx = new QMessageBox(this);
    if(PreferenceHandler::getInstance()->saveXMLDom())
    {
        bx->setText("<span style=\"color:#ffffff;\">saved successfully</span>");

    }
    else
    {
        bx->setText("<span style=\"color:#ffffff;\">saved failure</span>");
    }
    bx->show();

}
