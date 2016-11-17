#include "imagelabel.h"

ImageLabel::ImageLabel(QWidget * parent, int width, int height):QLabel(parent)
{
    this->setFixedSize(QSize(width, height));
}

void ImageLabel::setImage(QImage &image)
{
    this->mImage = image;
    repaint();
}
void ImageLabel::setRect(QRect &rect)
{
    this->mRect = rect;
}

void ImageLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);
    if (!this->mImage.isNull())
    {
        painter.drawImage(0, 0, mImage);
    }
    if(!this->mRect.width() != 0)
    {
        painter.setPen(QPen(Qt::red, 4));
        painter.drawRect(this->mRect);
    }
    painter.end();


}
