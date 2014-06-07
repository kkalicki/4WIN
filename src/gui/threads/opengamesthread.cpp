#include <../h/gui/threads/opengamesthread.h>


OpenGameThread::OpenGameThread(HelloReply incomingGame)
{
    this->incomingGame = incomingGame;
}

void OpenGameThread::process()
{
    emit updateGui(&incomingGame);
}
