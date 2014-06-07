#ifndef UDPSERVER_H
#define UDPSERVER_H

#include "../h/sys/Konstanten.h"
#include "../h/net/server4Win.h"

using namespace std;


class UdpServer : public Server4Win{
public:
    UdpServer(int port=DEFAULT_PORT_UDP);
    ~UdpServer();

    static void * startUdpServerThread(void * ptr);

protected:
    virtual void connect();
};
#endif // UDPSERVER_H
