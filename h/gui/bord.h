#ifndef BORD_H
#define BORD_H

#include <QWidget>
#include "ui_bord.h"
#include <../h/gui/I4WinWidget.h>
#include <../h/sys/Spieler.h>
namespace Ui {
class bordUi;
}

class Bord : public QWidget, public I4WinWidget
{
    Q_OBJECT
public:
    explicit Bord(QWidget *parent = 0, int rowCount = 6, int colCount = 7);
    ~Bord();
    void setMove(Spieler player, int row, int col);
    virtual void init();
    virtual void preExecute();
    virtual void postExecute();

private:
    int isLocked;
    int rowCount;
    int colCount;
    QPixmap *defaultImage ;
    QPixmap *redImage ;
    QPixmap *yellowImage ;
    Ui::bordUi* ui;
    static const int IMG_SIZE = 80;
    static const int START_POSITION_X = 260;
    static const int START_POSITION_Y = 180;
    void clear();

signals:

public slots:

private slots:
    void on_tblbord_doubleClicked(const QModelIndex &index);
};

#endif // BORD_H
