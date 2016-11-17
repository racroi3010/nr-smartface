#include "userlabelhist.h"

userlabelhist::userlabelhist(QWidget * parent)
    : QGroupBox(parent)
{
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    checkLabel = new QLabel(this);
    checkLabel->setText("<span style=\"color:#ffffff;font: 7pt \"Ubuntu\";\">Time</span>");
    //checkLabel->setStyleSheet("border-image:url(:/new/images/images/bg_text_overlay.png);");
    checkLabel->setFixedWidth(IMAGE_LABEL_WIDTH_4);
    checkLabel->setAlignment(Qt::AlignCenter);
    checkLabel->setSizePolicy(QSizePolicy::MinimumExpanding,
                              QSizePolicy::MinimumExpanding);
    layout->addWidget(checkLabel, 0, Qt::AlignBottom);

    this->setLayout(layout);
}
userlabelhist::~userlabelhist()
{

}
void userlabelhist::setUser(User *user)
{
    this->mUser = user;
    if(this->mUser != NULL)
    {
        this->setStyleSheet("border-image: url(" + this->mUser->userImagePath + ") 0 0 0 0 stretch stretch;");
        QStringList strs = user->dateTime.split("-");

        QString time = "";
        if(strs.size() > 1)
        {
            time = strs[0] + "&nbsp;&nbsp;" + strs[1];
        }
        checkLabel->setText("<span style=\"color:#ffffff;font: 7pt \"Ubuntu\";\">" + time + "</span>");
        checkLabel->setStyleSheet("border-image:url(:/new/images/images/bg_text_overlay.png);");
    }
    else
    {
        this->setStyleSheet("border-color: transparent 0 0 0 0 stretch stretch;");
        checkLabel->setText("");
        checkLabel->setStyleSheet("border-color: transparent 0 0 0 0 stretch stretch;");
    }

}
