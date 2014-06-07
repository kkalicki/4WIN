#ifndef UDPSERVER_H
#define UDPSERVER_H

#include "../h/sys/Konstanten.h"
#include "../h/net/server4Win.h"
#include "../h/net/netmessage.h"

using namespace std;


class UdpServer : public Server4Win{
public:
    UdpServer(int port=DEFAULT_PORT_UDP);
    ~UdpServer();

    static void *startUdpServerThread(void * ptr);
    static void *processThread(struct sockaddr_in sender, void *ptr, NetworkMessage mid, string object);

    bool isOwnAdress(struct sockaddr_in address);

protected:
    virtual void connect();

private:
    pthread_t thread;
};
#endif // UDPSERVER_H
