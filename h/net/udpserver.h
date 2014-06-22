#ifndef UDPSERVER_H
#define UDPSERVER_H

#include "../h/sys/Konstanten.h"
#include "../h/net/server4Win.h"
#include "../h/net/netmessage.h"
#include "../h/net/msg/visitorpackage.h"
#include "boost/signals2.hpp"

using namespace std;


class UdpServer : public Server4Win{
public:
    UdpServer(int port=DEFAULT_PORT_UDP);
    ~UdpServer();

    static void *startUdpServerThread(void * ptr);
    static void *processThread(struct sockaddr_in sender, void *ptr, NetworkMessage mid);

    boost::signals2::signal<void(string)> UdpHelloSignal;
    boost::signals2::signal<void(VisitorPackage)> VisitorPackageSignal;

protected:
    virtual void connect();

private:
    pthread_t thread;
};
#endif // UDPSERVER_H
