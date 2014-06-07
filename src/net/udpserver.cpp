#include "../h/net/udpserver.h"
#include "../h/sys/FourWinExceptions.h"
#include "../h/net/netmessage.h"
#include "../h/net/msg/loginrequest.h"
#include "../h/net/msg/loginreply.h"
#include "../h/net/msg/remotemove.h"
#include <pthread.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <sstream>

#include <arpa/inet.h>

UdpServer::UdpServer(int port) : Server4Win(UDP,port)
{
    //do Nothing...
}

UdpServer::~UdpServer()
{
    //kein new...
}


void UdpServer::connect()
{
    Server4Win::connect();
    pthread_create(&serverThread, 0, startUdpServerThread, this);
    pthread_detach(serverThread);
}

void *UdpServer::startUdpServerThread(void *ptr)
{
    int sock = ((UdpServer *)ptr)->sock;
    cout << "server gestartet!" << endl;
    while (true)
    {
        cout << "warte auf eingehende Verbindungen.." << endl;

        const int MAXDATARECV = 1024;
        char buf[MAXDATARECV];
        memset(buf,0,MAXDATARECV+1);
        if((recvfrom(sock,buf,MAXDATARECV,0,NULL,0)) < 0){
            printf("recvfrom() failed");
        }

        cout << "Boradcast eigegangen!" << endl;
    }
}
