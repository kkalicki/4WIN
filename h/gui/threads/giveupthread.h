#ifndef GIVEUPTHREAD_H
#define GIVEUPTHREAD_H
#include "../h/sys/Spieler.h"
#include   <QObject>

class GiveUpThread : public QObject{
    Q_OBJECT
public:
    GiveUpThread(Spieler* remotePlayer, bool giveUp=false);
public slots:
    void process();
signals:
    void updateGui(Spieler* remotePlayer, bool giveUp);
private:
    Spieler* remotePlayer;
    bool giveUp;
};

#endif // GIVEUPTHREAD_H
