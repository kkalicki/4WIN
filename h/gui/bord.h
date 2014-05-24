#ifndef BORD_H
#define BORD_H

#include <QWidget>
#include "ui_bord.h"
#include <../h/gui/I4WinWidget.h>
#include <../h/sys/Spieler.h>
#include <../h/sys/Konstanten.h>

namespace Ui {
class bordUi;
}

class Bord : public QWidget, public I4WinWidget
{
    Q_OBJECT
public:
    explicit Bord(unsigned short rowCount = Y, unsigned short colCount = X,unsigned short cellSize=CELL_SIZE, QWidget *parent=0);
    ~Bord();
    void setMove(Spieler player, int row, int col);
    virtual void init();
    virtual void preExecute();
    virtual void postExecute();

    unsigned short getRowCount() const{
        return rowCount;
    }

    void setRowCount(unsigned short value){
        rowCount = value;
    }
    unsigned short getColCount() const{
        return colCount;
    }

    void setColCount(unsigned short value){
        colCount = value;
    }

private:
    int isLocked;
    unsigned short rowCount;
    unsigned short colCount;
    unsigned short cellSize;
    QPixmap *defaultImage ;
    QPixmap *redImage ;
    QPixmap *yellowImage ;
    Ui::bordUi* ui;
    static const int START_POSITION_X = 230;
    static const int START_POSITION_Y = 180;
    void clear();

signals:
    void executeMove(unsigned short column);

public slots:

private slots:
    void on_tblbord_doubleClicked(const QModelIndex &index);
    void on_tblbord_clicked(const QModelIndex &index);
};

#endif // BORD_H
