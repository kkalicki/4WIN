#include "../h/net/udpserver.h"
#include "../h/sys/FourWinExceptions.h"
//#include <netdb.h>
//#include <stdio.h>
//#include <sstream>

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
    connection_t * connection;
    int sock = ((UdpServer *)ptr)->sock;
    cout << "server gestartet!" << endl;
    while (true)
    {
        cout << "warte auf Broadcast..." << endl;
        connection = (connection_t *)malloc(sizeof(connection_t));

        NetworkMessage incomingMessage(LOGINREQUEST);
        connection->sock = recvfrom(sock,&incomingMessage,sizeof(NetworkMessage),0,&connection->address, &connection->addr_len);

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
            cout << "ID " << incomingMessage.getId() << endl;

            processThread(connection,incomingMessage,object);
            close(connection->sock);
            free(connection);
        }
        cout << "Boradcast eigegangen!" << endl;
    }
}

void *UdpServer::processThread(connection_t *conn, NetworkMessage mid, string object)
{
    switch(mid.getId()){
    case UDPHELLO:
                    cout << "HELLO FROM BROADCAST" << endl;

                    NetworkMessage msg(UDPHELLO);
                    if (sendto(sock, &msg, sizeof(NetworkMessage), 0, &conn->address, &conn->addr_len) != len)
                       printf("sendto() failed");
        break;
    }
}
