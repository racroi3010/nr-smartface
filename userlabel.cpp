#include "userlabel.h"

userlabel::userlabel(QWidget * parent)
    : QGroupBox(parent)
{
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    checkLabel = new QLabel(this);
    checkLabel->setStyleSheet("border-image: url(:/new/images/images/img_check.png);");
    checkLabel->setFixedSize(25, 25);
    checkLabel->setVisible(false);
    layout->addWidget(checkLabel, 0, Qt::AlignRight|Qt::AlignTop);

    idLabel = new QLabel(this);
    idLabel->setText("<span style=\"color:#ffffff;font: 7pt \"Ubuntu\";\">ID</span>");
    idLabel->setFixedWidth(IMAGE_LABEL_WIDTH_4);
    idLabel->setAlignment(Qt::AlignCenter);
    idLabel->setSizePolicy(QSizePolicy::MinimumExpanding,
                              QSizePolicy::MinimumExpanding);
    layout->addWidget(idLabel, 0, Qt::AlignBottom);

    this->setLayout(layout);
}
userlabel::~userlabel()
{

}
void userlabel::setUser(User *user)
{
    this->mUser = user;
    if(this->mUser != NULL)
    {
        this->setStyleSheet("border-image: url(" + this->mUser->userImagePath + ") 0 0 0 0 stretch stretch;");
        checkLabel->setVisible(this->mUser->isSelected);

        idLabel->setText("<span style=\"color:#ffffff;font: 7pt \"Ubuntu\";\">" + this->mUser->userNumber + "</span>");
        idLabel->setStyleSheet("border-image:url(:/new/images/images/bg_text_overlay.png);");
    }
    else
    {
        this->setStyleSheet("border-color: transparent 0 0 0 0 stretch stretch;");
        checkLabel->setVisible(false);

        idLabel->setText("");
        idLabel->setStyleSheet("border-color: transparent 0 0 0 0 stretch stretch;");
    }

}

void userlabel::mousePressEvent(QMouseEvent *event)
{
    if(this->mUser != NULL)
    {
        this->mUser->isSelected = !(this->mUser->isSelected);
        checkLabel->setVisible(this->mUser->isSelected);
    }
    else
    {
        checkLabel->setVisible(false);
    }

    emit click();
}
