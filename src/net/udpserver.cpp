#include "../h/net/udpserver.h"
#include "../h/sys/FourWinExceptions.h"
//#include <netdb.h>
//#include <stdio.h>
//#include <sstream>


#include <pthread.h>
#include <netinet/in.h>
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
    int sock = ((UdpServer*)ptr)->getSock();

    struct sockaddr_in sender;
    sender.sin_family = AF_INET;
    socklen_t sendsize = sizeof(sender);
    bzero(&sender, sizeof(sender));

    connection_t * connection;
    cout << "server gestartet!" << endl;
    while (true)
    {
        cout << "warte auf Broadcast..." << endl;
        connection = (connection_t *)malloc(sizeof(connection_t));

        NetworkMessage incomingMessage(LOGINREQUEST);
        connection->sock = recvfrom(sock,&incomingMessage,sizeof(NetworkMessage),MSG_WAITSTREAM,(struct sockaddr*)&sender, &sendsize);

        /*int len;
        recvfrom(sock,&len,sizeof(int),0,NULL, 0);

        char buffer[len];
        recvfrom(sock, buffer, len,0,NULL, 0);
        string object(buffer);*/
        string object = "test";
        if (connection->sock <= 0)
        {
             free(connection);
        }
        else
        {
            cout << "Verbindungen eingegangen(UDP)..SOCK: " << connection->sock << endl;
            char* ip = inet_ntoa(sender.sin_addr);
            string ipstr(ip);
            cout << "Adresse : " << ipstr << endl;
            cout << "ID " << incomingMessage.getId() << endl;

            processThread((struct sockaddr*)&sender,ptr,incomingMessage,object);
            close(connection->sock);
            free(connection);
        }
        cout << "Boradcast eigegangen!" << endl;
    }
}

void *UdpServer::processThread(struct sockaddr* sender,void *ptr, NetworkMessage mid, string object)
{
    switch(mid.getId()){
    case UDPHELLO:
                    cout << "HELLO FROM BROADCAST" << endl;
                    int sock = ((UdpServer*)ptr)->sock;
                    NetworkMessage msg(UDPHELLO);
                    sendto(sock, &msg, sizeof(NetworkMessage), 0, (struct sockaddr *) &sender, sizeof(sender));
        break;
    }
}
