#ifndef UDPSERVER_H
#define UDPSERVER_H

#include "../h/net/msg/remotemove.h"
#include "../h/sys/Konstanten.h"
#include "boost/signals2.hpp"
#include <netinet/in.h>
#include <iostream>
#include <string>
#include "../h/net/tcpserver.h"

using namespace std;


class UdpServer{
public:
    UdpServer(int port=DEFAULT_PORT_UDP);
    ~UdpServer();
    void start();
    void stop();
    void connect();
    static void * startServerThread(void * ptr);
    static void * processThread(void * ptr);
    static void process(connection_t * conn, void * ptr);

    boost::signals2::signal<void(string)> LoginRequestSignal;

    int getSock() const;
    void setSock(int value);

    int getIsActive() const;
    void setIsActive(int value);

private:
    pthread_t udpServerThread;
    int sock;
    int port;
    int isActive;

};
#endif // UDPSERVER_H
