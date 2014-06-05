#include "../h/gui/threads/giveupthread.h"


GiveUpThread::GiveUpThread(Spieler *remotePlayer, bool giveUp)
{
    this->remotePlayer = remotePlayer;
    this->giveUp = giveUp;
}

void GiveUpThread::process()
{
    emit updateGui(remotePlayer,giveUp);
}
