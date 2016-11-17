#ifndef USERLABEL_H
#define USERLABEL_H

#include <QGroupBox>
#include <QLabel>
#include <QGridLayout>
#include <QMouseEvent>
#include <QVBoxLayout>

#include "user.h"
#include "Constants.h"

class userlabel : public QGroupBox
{
    Q_OBJECT
public:
    explicit userlabel(QWidget * parent=0);
    ~userlabel();

    void setUser(User* user);
protected:
    void mousePressEvent(QMouseEvent *event);
private:

    QVBoxLayout *layout;
    QLabel *checkLabel;

    QLabel *idLabel;

    User *mUser;

signals:
    void click();

public slots:

};

#endif // USERLABEL_H
