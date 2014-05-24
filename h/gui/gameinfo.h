#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <QWidget>
#include "ui_gameinfo.h"
#include "../h/gui/I4WinWidget.h"
#include "../h/sys/Spieler.h"
#include <QPixmap>
#include <string>

namespace Ui {
class gameinfoUi;
}

class GameInfo : public QWidget, public I4WinWidget
{
    Q_OBJECT
public:
    explicit GameInfo(QWidget * parent=0);
    virtual void init();
    virtual void preExecute();
    virtual void postExecute();
    void lock();
    void unlock();
    void changePlayer();
    void initPlayerDisplays(const Spieler& player1,const Spieler& player2);
    void initfirstPlayer(const Spieler& firstPlayer);
    void setLastMove(string move);
    void setRound(unsigned short round);
    ~GameInfo();

private slots:

    void on_btnlooseleft_clicked();

    void on_btnlooseright_clicked();

private:
     QPixmap imgRed;
     QPixmap imgYellow;
     Spieler player1;
     Spieler player2;
     Spieler currentPlayer;
     Ui::gameinfoUi *ui;
     static const int START_POSITION_X = 0;
     static const int START_POSITION_Y = 0;
};

#endif // GAMEINFO_H
