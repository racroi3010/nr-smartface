#ifndef USERLABELHIST_H
#define USERLABELHIST_H
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QDir>

#include "user.h"
#include "Constants.h"
class userlabelhist: public QGroupBox
{
    Q_OBJECT
public:
    explicit userlabelhist(QWidget * parent = 0);
    ~userlabelhist();

    void setUser(User* user);
private:
    QVBoxLayout *layout;
    QLabel *checkLabel;

    User *mUser;
};

#endif // USERLABELHIST_H
