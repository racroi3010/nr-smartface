#include "dialogsetting.h"
#include "ui_dialogsetting.h"

DialogSetting::DialogSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSetting)
{
    ui->setupUi(this);

    this->setFixedSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);

    // initialize data for combobox
    QStringList listTemplateSize;
    listTemplateSize.append("Compact");
    listTemplateSize.append("Small");
    listTemplateSize.append("Medium");
    listTemplateSize.append("Large");
    this->ui->cbox_template_size->addItems(listTemplateSize);

    QStringList listMatchSpeed;
    listMatchSpeed.append("Low");
    listMatchSpeed.append("Medium");
    listMatchSpeed.append("High");
    this->ui->cbox_match_speed->addItems(listMatchSpeed);


    QStringList listLiveMode;
    listLiveMode.append("None");
    listLiveMode.append("Passive");
    listLiveMode.append("Active");
    listLiveMode.append("PassiveAndActive");
    this->ui->cbox_liveness_mode->addItems(listLiveMode);


    PreferenceHandler *preHandler = PreferenceHandler::getInstance();


    ui->sp_eye_distance->setValue(preHandler->getEyeDistance());
    ui->sp_confident->setValue(preHandler->getConfident());
    ui->sp_max_roll->setValue(preHandler->getMaxRoll());
    ui->sp_max_yaw->setValue(preHandler->getMaxYaw());
    ui->sp_quality->setValue(preHandler->getQualityThreshold());
    ui->cb_liveness_check->setChecked(preHandler->getUseLivenessCheck());
    ui->sp_liveness_threshold->setValue(preHandler->getLivenessThreshold());

    switch (preHandler->getLivenessMode()) {
    case nlmNone:
        this->ui->cbox_liveness_mode->setCurrentIndex(0);
        break;
    case nlmPassive:
        this->ui->cbox_liveness_mode->setCurrentIndex(1);
        break;
    case nlmActive:
        this->ui->cbox_liveness_mode->setCurrentIndex(2);
        break;
    case nlmPassiveAndActive:
        this->ui->cbox_liveness_mode->setCurrentIndex(3);
        break;
    }

    switch (preHandler->getMatchSpeed()) {
    case nmsLow:
        this->ui->cbox_match_speed->setCurrentIndex(0);
        break;
    case nmsMedium:
        this->ui->cbox_match_speed->setCurrentIndex(1);
        break;
    case nmsHigh:
        this->ui->cbox_match_speed->setCurrentIndex(2);
        break;
    }

    ui->sp_token_img_width->setValue(preHandler->getTokenImageWidth());
    ui->sp_token_quality->setValue(preHandler->getTokenQualityThreshold());
    ui->sp_sharpness->setValue(preHandler->getSharpnessThreshold());
    ui->sp_bg_uniform->setValue(preHandler->getBgUniformThreshold());
    ui->sp_gray_density->setValue(preHandler->getGrayDensityThreshold());

    switch (preHandler->getTemplateSize()) {
    case ntsCompact:
        this->ui->cbox_template_size->setCurrentIndex(0);
        break;
    case ntsSmall:
        this->ui->cbox_template_size->setCurrentIndex(1);
        break;
    case ntsMedium:
        this->ui->cbox_template_size->setCurrentIndex(2);
        break;
    case ntsLarge:
        this->ui->cbox_template_size->setCurrentIndex(3);
        break;


    }

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
    int livenessModeIndex = ui->cbox_liveness_mode->currentIndex();
    switch (livenessModeIndex) {
    case 0:
        PreferenceHandler::getInstance()->setLivenessMode(nlmNone);
        break;
    case 1:
        PreferenceHandler::getInstance()->setLivenessMode(nlmPassive);
        break;
    case 2:
        PreferenceHandler::getInstance()->setLivenessMode(nlmActive);
        break;
    case 3:
        PreferenceHandler::getInstance()->setLivenessMode(nlmPassiveAndActive);
        break;
    }

    int matchSpeedIdx = ui->cbox_match_speed->currentIndex();
    switch (matchSpeedIdx) {
    case 0:
        PreferenceHandler::getInstance()->setMatchSpeed(nmsLow);
        break;
    case 1:
        PreferenceHandler::getInstance()->setMatchSpeed(nmsMedium);
        break;
    case 2:
        PreferenceHandler::getInstance()->setMatchSpeed(nmsHigh);
        break;
    }

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

    int templateSizeIdx = ui->cbox_template_size->currentIndex();
    switch (templateSizeIdx) {
    case 0:
        PreferenceHandler::getInstance()->setTemplateSize(ntsCompact);
        break;
    case 1:
        PreferenceHandler::getInstance()->setTemplateSize(ntsSmall);
        break;
    case 2:
        PreferenceHandler::getInstance()->setTemplateSize(ntsMedium);
        break;
    case 3:
        PreferenceHandler::getInstance()->setTemplateSize(ntsLarge);
        break;
    }

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
