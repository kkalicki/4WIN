#ifndef GAMEINFO_H
#define GAMEINFO_H

#include "../h/gui/I4WinWidget.h"
#include "../h/sys/Spieler.h"
#include "../h/gui/timer4Win.h"
#include <QWidget>
#include <QPixmap>
#include <string>
#include <QThread>
#include <QMovie>

#include "ui_gameinfo.h"

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
    void initPlayer(const Spieler& player1,const Spieler& player2);
    void changePlayer(const Spieler* currentPlayer, unsigned short round, string lastMove);
    void initPlayerDisplays(const Spieler& player1,const Spieler& player2);
    void initfirstPlayer(const Spieler& firstPlayer);
    ~GameInfo();

private slots:
    void on_btnlooseleft_clicked();
    void on_btnlooseright_clicked();
    void on_timeChange();

signals:
    void loose(Spieler* winner);

private:
     QPixmap imgRed;
     QPixmap imgYellow;
     Spieler player1;
     Spieler player2;
     Spieler currentPlayer;
     QThread *timer;
     Timer4Win *timerWorker;
     QMovie* gifRedMovie;
     QMovie* gifYellowMovie;
     unsigned long timePlayer1;
     unsigned long timePlayer2;
     Ui::gameinfoUi *ui;
     static const int START_POSITION_X = 0;
     static const int START_POSITION_Y = 0;
     void setLastMove(string move);
     void setRound(unsigned short round);
     void initPlayerDisplays();
     void setTimePlayer1();
     void setTimePlayer2();
     void clearTimePlayer1();
     void clearTimePlayer2();
     string convertMillToTime(unsigned long ms);
};

#endif // GAMEINFO_H
