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

UdpServer::UdpServer(int port)
{
    this->port = port;
    this->sock = -1;
}

void UdpServer::start()
{
    connect();
}

void UdpServer::stop()
{
    isActive = false;
    cout << "stoppe Server!" << endl;
    if(sock > -1)
    {
        close(sock);
        cout << "Socket geschlossen!" << endl;
    }

    pthread_cancel(udpServerThread);
    cout << "Serverthread geschlossen!" << endl;
}

void UdpServer::connect()
{
    struct sockaddr_in address;
    //pthread_t thread;

    cout << "erstelle Socket!" << endl;
    sock = (socket(AF_INET, SOCK_STREAM, IPPROTO_UDP));
    if (sock <= 0)
    {
      throw TcpServerException("Socket konnte nicht erstellt werden!");
    }

    /* bind socket to port */
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    cout << "Binde Socket!" << endl;
    if (bind(sock, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) < 0)
    {
        ostringstream o;
        o << "Socket konnte nicht an Port gebunden werden ! (" << port << ")" << endl;
        throw TcpServerException(o.str());
    }

    if (listen(sock, 5) < 0)
    {
        ostringstream o;
        o << "Server kann horchen an Port! (" << port << ")" << endl;
        throw TcpServerException(o.str());
    }

    isActive = true;
    cout << "starte Server!" << endl;
    pthread_create(&udpServerThread, 0, startServerThread, this);
    pthread_detach(udpServerThread);
}

void *UdpServer::startServerThread(void *ptr)
{
    connection_t * connection;
    int sock = ((UdpServer *)ptr)->sock;
    cout << "server gestartet!" << endl;
    while (true)
    {
        cout << "warte auf eingehende Verbindungen.." << endl;
        connection = (connection_t *)malloc(sizeof(connection_t));
        connection->sock = accept(sock, &connection->address, &connection->addr_len); //TODO Hier Select() nachlesen
        if (connection->sock <= 0)
        {
             free(connection);
        }
        else
        {
            cout << "Verbindungen eingegangen..PORT: " << connection->sock << endl;
            process(connection,ptr);
            close(connection->sock);
            free(connection);
        }
    }
}

void UdpServer::process(connection_t *conn, void *ptr)
{
    int len= 0;
    string templr;
    cout << "starte verarbeitung!" << endl;
    NetworkMessage incomingMessage(LOGINREQUEST);
    read(conn->sock, &incomingMessage, sizeof(NetworkMessage));
    switch(incomingMessage.getId())
    {
        default: // Do Nothing...
        break;
    }
}

int UdpServer::getSock() const
{
    return sock;
}

void UdpServer::setSock(int value)
{
     sock = value;
}

int UdpServer::getIsActive() const
{
    return isActive;
}

void UdpServer::setIsActive(int value)
{
    isActive = value;
}
