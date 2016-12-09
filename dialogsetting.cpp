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

//    ui->spb_eyemax->setValue(preHandler->getEyeMax());
//    ui->spb_eyemin->setValue(preHandler->getEyeMin());
//    ui->spb_maxRelValue->setValue(preHandler->getMaxRelValue());
//    ui->spb_relValue->setValue(preHandler->getRelValue());

//    ui->spb_eyedistance->setValue(preHandler->getEyeDistance());
//    ui->spb_confidence->setValue(preHandler->getConfident());
//    ui->cb_matchingdetail->setChecked(preHandler->getMmatchingDetail());

//    ui->spb_matching->setValue(preHandler->getMatching());


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
#ifdef USE_NEOFACE
    float relValue = ui->spb_relValue->value();
    float maxRelValue = ui->spb_maxRelValue->value();
    int eyeMin = ui->spb_eyemin->value();
    int eyeMax = ui->spb_eyemax->value();

    PreferenceHandler::getInstance()->setEyeMax(eyeMax);
    PreferenceHandler::getInstance()->setEyeMin(eyeMin);
    PreferenceHandler::getInstance()->setMaxRelValue(maxRelValue);
    PreferenceHandler::getInstance()->setRelValue(relValue);
#endif

#ifdef USE_NEURO
//    int eyeDistance = ui->spb_eyedistance->value();
//    PreferenceHandler::getInstance()->setEyeDistance(eyeDistance);

//    int conf = ui->spb_confidence->value();
//    PreferenceHandler::getInstance()->setConfident(conf);

//    bool matchingDetail = ui->cb_matchingdetail->isChecked();
//    PreferenceHandler::getInstance()->setMmatchingDetail(matchingDetail);

//    int matching = ui->spb_matching->value();
//    PreferenceHandler::getInstance()->setMatching(matching);
#endif


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
