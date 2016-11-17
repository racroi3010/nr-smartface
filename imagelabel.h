#ifndef IMAGELABEL_H
#define IMAGELABEL_H
#include <Constants.h>

#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QImage>
class ImageLabel:public QLabel
{

public:
    explicit ImageLabel(QWidget * parent = 0, int width = IMAGE_LABEL_WIDTH, int height = IMAGE_LABEL_HEIGHT);
    void setImage(QImage &image);
    void setRect(QRect &rect);

protected:
    void paintEvent(QPaintEvent *);

private:
    QImage mImage;
    QRect mRect;
};

#endif // IMAGELABEL_H
