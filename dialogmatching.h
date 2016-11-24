#ifndef DIALOGMATCHING_H
#define DIALOGMATCHING_H

#include <QDialog>
#include <QDir>

namespace Ui {
class DialogMatching;
}

class DialogMatching : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMatching(QWidget *parent = 0, QString Id = NULL);
    ~DialogMatching();
    void setId(QString Id);
private:
    Ui::DialogMatching *ui;
    QString userId;
};

#endif // DIALOGMATCHING_H
