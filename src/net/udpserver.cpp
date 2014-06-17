#include "../h/net/udpserver.h"
#include "../h/sys/FourWinExceptions.h"

#include <netdb.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/types.h>

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
    pthread_create(&udpServerThread, 0, startUdpServerThread, this);
    //pthread_detach(udpServerThread);
}

void *UdpServer::startUdpServerThread(void *ptr)
{
    int sock = ((UdpServer*)ptr)->getSock();

    struct sockaddr_in sender;
    sender.sin_family = AF_INET;
    socklen_t sendsize = sizeof(sender);
    bzero(&sender, sizeof(sender));

    connection_t * connection;
    cout << "server gestartet!" << endl;
    while (((UdpServer *)ptr)->getIsActive())
    {
        cout << "warte auf Broadcast..." << endl;
        connection = (connection_t *)malloc(sizeof(connection_t));

        NetworkMessage incomingMessage(LOGINREQUEST);
        connection->sock = recvfrom(sock,&incomingMessage,sizeof(NetworkMessage),0,(struct sockaddr*)&sender, &sendsize);
        if (connection->sock <= 0){
             free(connection);
        }
        else{

            if(!((UdpServer*)ptr)->isOwnAddress(sender)){
                cout << "Verbindungen eingegangen(UDP)..SOCK: " << connection->sock << endl;
                processThread((struct sockaddr_in)sender,ptr,incomingMessage);
                close(connection->sock);
                free(connection);
            }

        }
        cout << "Boradcast eigegangen!" << endl;
    }
    pthread_exit((void*) true);
}

void *UdpServer::processThread(struct sockaddr_in sender,void *ptr, NetworkMessage mid)
{
    switch(mid.getId()){
    case UDPHELLO:
    {
        char* ip = inet_ntoa(sender.sin_addr);
        string ipstr(ip);
        ((UdpServer*)ptr)->UdpHelloSignal(ipstr);
    }
    break;
    default: // Do Nothing...
    break;
    }
}
