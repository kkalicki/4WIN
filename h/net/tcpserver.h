#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <iostream>
#include <string>
#include "../h/sys/Konstanten.h"
#include "../h/sys/Spieler.h"
#include "boost/signals2.hpp"

using namespace std;

typedef struct
{
    int sock;
    struct sockaddr address;
    unsigned int addr_len;
} connection_t;

class TcpServer{
public:
    TcpServer(int port=DEFAULT_PORT_TCP);
    ~TcpServer();
    void start();
    void stop();
    static void * startServerThread(void * ptr);
    static void * processThread(void * ptr);
    static void process(connection_t * conn, void * ptr);

    boost::signals2::signal<void(string)> LoginRequestSignal;
    boost::signals2::signal<void(Spieler)> LoginReplySignal;
    boost::signals2::signal<void(unsigned short)> IncomingMoveSignal;

private:
    pthread_t tcpServerThread;
    string ipAdresse;
    int port;
    int isActive;
};

#endif // SERVER_H
