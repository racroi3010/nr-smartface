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

private:
    Ui::DialogMatching *ui;
};

#endif // DIALOGMATCHING_H
