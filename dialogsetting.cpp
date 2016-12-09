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


    ui->sp_eye_distance->setValue(preHandler->getEyeDistance());
    ui->sp_confident->setValue(preHandler->getConfident());
    ui->sp_max_roll->setValue(preHandler->getMaxRoll());
    ui->sp_max_yaw->setValue(preHandler->getMaxYaw());
    ui->sp_quality->setValue(preHandler->getQualityThreshold());
    ui->cb_liveness_check->setChecked(preHandler->getUseLivenessCheck());
    ui->sp_liveness_threshold->setValue(preHandler->getLivenessThreshold());
    //ui->cbox_liveness_mode->setItemText(preHandler->getLivenessMode());
    //ui->sp_match_speed->setValue(preHandler->getMatchSpeed());
    ui->sp_token_img_width->setValue(preHandler->getTokenImageWidth());
    ui->sp_token_quality->setValue(preHandler->getTokenQualityThreshold());
    ui->sp_sharpness->setValue(preHandler->getSharpnessThreshold());
    ui->sp_bg_uniform->setValue(preHandler->getBgUniformThreshold());
    ui->sp_gray_density->setValue(preHandler->getGrayDensityThreshold());
    //ui->sp_template_size->setValue(preHandler->getTemplateSize());
    ui->cb_detect_all_feature->setChecked(preHandler->getDetectAllFeature());
    ui->cb_matching_detail->setChecked(preHandler->getMmatchingDetail());
    ui->sp_max_result_count->setValue(preHandler->getMatchMaxResult());
    ui->cb_firstresult->setChecked(preHandler->getMatchFirstResult());
    ui->sp_matching->setValue(preHandler->getMatching());
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

    int eyeDistance = ui->sp_eye_distance->value();
    PreferenceHandler::getInstance()->setEyeDistance(eyeDistance);

    int confident = ui->sp_confident->value();
    PreferenceHandler::getInstance()->setConfident(confident);

    float maxRoll = ui->sp_max_roll->value();
    PreferenceHandler::getInstance()->setMaxRoll(maxRoll);

    float maxYaw = ui->sp_max_yaw->value();
    PreferenceHandler::getInstance()->setMaxYaw(maxYaw);

    int qualityThreshold = ui->sp_quality->value();
    PreferenceHandler::getInstance()->setQualityThreshold(qualityThreshold);

    bool useLivenessCheck = ui->cb_liveness_check->isChecked();
    PreferenceHandler::getInstance()->setUseLivenessCheck(useLivenessCheck);
    int livenessThreshold = ui->sp_liveness_threshold->value();
    PreferenceHandler::getInstance()->setLivenessThreshold(livenessThreshold);
//    NLivenessMode livenessMode = ui->;
//    PreferenceHandler::getInstance()->setLivenessMode(livenessMode);
//    NMatchingSpeed matchSpeed;
//    PreferenceHandler::getInstance()->setMatchSpeed(matchSpeed);
    int tokenImageWidth = ui->sp_token_img_width->value();
    PreferenceHandler::getInstance()->setTokenImageWidth(tokenImageWidth);
    int tokenQualityThreshold = ui->sp_token_quality->value();
    PreferenceHandler::getInstance()->setTokenQualityThreshold(tokenQualityThreshold);
    int sharpnessThreshold = ui->sp_sharpness->value();
    PreferenceHandler::getInstance()->setSharpnessThreshold(sharpnessThreshold);
    int bgUniformThreshold = ui->sp_bg_uniform->value();
    PreferenceHandler::getInstance()->setBgUniformThreshold(bgUniformThreshold);
    int grayDensityThreshold = ui->sp_gray_density->value();
    PreferenceHandler::getInstance()->setGrayDensityThreshold(grayDensityThreshold);
//    NTemplateSize templateSize = ui->;
//    PreferenceHandler::getInstance()->setTemplateSize(templateSize);
    bool detectAllFeature = ui->cb_detect_all_feature->isChecked();
    PreferenceHandler::getInstance()->setDetectAllFeature(detectAllFeature);
    bool mmatchingDetail = ui->cb_matching_detail->isChecked();
    PreferenceHandler::getInstance()->setMmatchingDetail(mmatchingDetail);
    int matchMaxResult = ui->sp_max_result_count->value();
    PreferenceHandler::getInstance()->setMatchMaxResult(matchMaxResult);
    bool matchFirstResult = ui->cb_firstresult->isChecked();
    PreferenceHandler::getInstance()->setMatchFirstResult(matchFirstResult);
    int matching = ui->sp_matching->value();
    PreferenceHandler::getInstance()->setMatching(matching);
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
