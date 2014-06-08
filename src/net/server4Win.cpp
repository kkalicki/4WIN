#include "../h/net/server4Win.h"
#include <../h/sys/FourWinExceptions.h>
#include <sys/socket.h>
#include <iostream>
#include <sstream>

#include <netdb.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>


using namespace std;

Server4Win::Server4Win(ServerType serverType, int port)
{
    this->port = port;
    this->sock = -1;
    this->serverType = serverType;
}

Server4Win::~Server4Win()
{
    if(isActive)
        stop();
}

void Server4Win::start()
{
    connect();
}

void Server4Win::stop()
{
    isActive = false;
    cout << "stoppe Server!" << endl;
    if(sock > -1)
    {
        close(sock);
        cout << "Socket geschlossen!" << endl;
    }

    pthread_cancel(serverThread);
    cout << "Serverthread geschlossen!" << endl;
}

void Server4Win::connect()
{
    int permission = 1;
    switch(serverType){
    case TCP:
                cout << "erstelle Socket!(TCP)" << endl;
                sock = (socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));
                if (sock <= 0){
                  throw Server4WinException("Socket konnte nicht erstellt werden (TCP)!");
                }
        break;
    case UDP:
                cout << "erstelle Socket!(UDP)" << endl;
                sock = (socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP));
                if (sock <= 0){
                  throw Server4WinException("Socket konnte nicht erstellt werden(UDP)!");
                }

                if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &permission, sizeof(permission)) < 0)
                    throw Server4WinException("Socketoptionen konnten nicht gesetzt werden(UDP)!");
        break;
    default:    //Do Nothing...
        break;
    }


    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    cout << "Binde Socket!" << endl;
    if (bind(sock, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        ostringstream o;
        o << "Socket konnte nicht an Port gebunden werden ! (" << port << ")" << endl;
        throw Server4WinException(o.str());
    }

    if(serverType==TCP){
        cout << "Socket listen!(TCP)" << endl;
        if (listen(sock, 5) < 0){
            ostringstream o;
            o << "Server kann nicht an Port horchen (TCP)! (" << port << ")" << endl;
            throw Server4WinException(o.str());
        }
    }

    isActive = true;
    cout << "starte Server!" << endl;

    //in subklassen muss noch thread erstellt und gestartet werden...
}

bool Server4Win::isOwnAddress(sockaddr_in address)
{
    char hostname[1024];
    hostname[1023] = '\0';
    gethostname(hostname, 1023);

    struct sockaddr_in SocketAddress;
    struct hostent* pHost = gethostbyname(hostname);
    if(pHost)
    {
        for(int iCnt = 0; ((pHost->h_addr_list[iCnt]) && (iCnt < 10)); ++iCnt)
        {
          memcpy(&SocketAddress.sin_addr, pHost->h_addr_list[iCnt], pHost->h_length);
          if(SocketAddress.sin_addr.s_addr == address.sin_addr.s_addr)
              return true;
        }
    }
    return false;
}

int Server4Win::getSock() const
{
    return sock;
}

void Server4Win::setSock(int value)
{
    sock = value;
}
int Server4Win::getPort() const
{
    return port;
}

void Server4Win::setPort(int value)
{
    port = value;
}
int Server4Win::getIsActive() const
{
    return isActive;
}

void Server4Win::setIsActive(int value)
{
    isActive = value;
}







