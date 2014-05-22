#ifndef BORD_H
#define BORD_H

#include <QWidget>
#include "ui_bord.h"

namespace Ui {
class bordUi;
}

class Bord : public QWidget
{
    Q_OBJECT
public:
    explicit Bord(QWidget *parent = 0, int rowCount = 6, int colCount = 7);
    ~Bord();

    void init();

private:
    int rowCount;
    int colCount;
    QPixmap *defaultImage ;
    QPixmap *redImage ;
    QPixmap *yellowImage ;
    Ui::bordUi* ui;
    static const int IMG_SIZE = 80;
    static const int START_POSITION_X = 200;
    static const int START_POSITION_Y = 180;
signals:

public slots:

private slots:
    void on_tblbord_doubleClicked(const QModelIndex &index);
};

#endif // BORD_H
