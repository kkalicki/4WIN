#ifndef SERVER_H
#define SERVER_H

#include "../h/net/server4Win.h"
#include "../h/sys/Konstanten.h"
#include "../h/sys/Spieler.h"
#include "../h/net/msg/remotemove.h"
#include "../h/net/msg/helloreply.h"
#include "boost/signals2.hpp"
#include <netinet/in.h>
#include <iostream>
#include <string>
using namespace std;


class TcpServer: public Server4Win{
public:
    TcpServer(int port=DEFAULT_PORT_TCP);
    ~TcpServer();
    static void * startTcpServerThread(void * ptr);
    static void process(connection_t * conn, void * ptr);

    boost::signals2::signal<void(string,string)> LoginRequestSignal;
    boost::signals2::signal<void(Spieler)> LoginReplySignal;
    boost::signals2::signal<void(unsigned short)> RemoteMoveSignal;
    boost::signals2::signal<void()> GiveUpSignal;
    boost::signals2::signal<void(HelloReply)> HelloReplySignal;

protected:
    virtual void connect();

};

#endif // SERVER_H
