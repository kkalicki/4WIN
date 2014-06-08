#ifndef HELLOSERVER_H
#define HELLOSERVER_H

#include "../h/net/server4Win.h"
#include "../h/net/msg/helloreply.h"
#include "../h/sys/Konstanten.h"
#include "boost/signals2.hpp"

#include <string>
#include <iostream>
using namespace std;

class HelloServer : public Server4Win{
public:
    HelloServer(int port=DEFAULT_PORT_HELLO);
    ~HelloServer();

    static void * startTcpServerThread(void * ptr);
    void sendHelloBroadcast();

    boost::signals2::signal<void(HelloReply)> HelloReplySignal;

protected:
    virtual void connect();
    struct sockaddr_in address;
    int udpsock;
};

#endif // HELLOSERVER_H
