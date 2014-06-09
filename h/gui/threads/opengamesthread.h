#ifndef OPENGAMESTHREAD_H
#define OPENGAMESTHREAD_H

#include <../h/net/msg/helloreply.h>
#include   <QObject>
class OpenGameThread : public QObject
{
   Q_OBJECT

public:
    OpenGameThread(HelloReply incomingGame);
public slots:
    void process();
signals:
    void updateGui(HelloReply* incomingGame);

private:
    HelloReply incomingGame;
};
#endif // OPENGAMESTHREAD_H
