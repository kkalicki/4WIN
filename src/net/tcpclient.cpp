#include "../h/net/tcpclient.h"
#include "../h/net/msg/loginreply.h"
#include "../h/net/msg/loginrequest.h"
#include "../h/net/msg/remotemove.h"
#include "../h/sys/FourWinExceptions.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <sstream>
#include <netinet/in.h>
#include <iostream>


#include <arpa/inet.h>
using namespace std;

TcpClient::TcpClient(string ipAddress,int port)
{
    this->ipAddress = ipAddress;
    this->port = port;
    this->sock = -1;
}

TcpClient::~TcpClient()
{
     if(sock > -1)
         disconnect();
}

void TcpClient::openConnection()
{
    struct sockaddr_in address;
    struct hostent * host;

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    ostringstream o;
    o << ipAddress;
    host = gethostbyname(o.str().c_str());

    if (!host)
    {
        throw ClientException("Host konnte nicht identifiziert werden! -> Ip-Adresse pruefen!");
    }

    memcpy(&address.sin_addr, host->h_addr_list[0], host->h_length);

    if(connect(sock, (struct sockaddr *)&address, sizeof(address)))
    {
        throw ClientException("Client konnte keine Verbindung zum Server herstellen (" +ipAddress+")");
    }
}

void TcpClient::disconnect()
{
    close(sock);
}

void TcpClient::sendLoginRequest(string playerName)
{
    NetworkMessage msgId(LOGINREQUEST);
    LoginRequest loginRequest(playerName);
    stringstream o;
    o << loginRequest;
    int len= strlen(o.str().c_str());

    openConnection();
    write(sock,&msgId,sizeof(LOGINREQUEST));
    write(sock,(char*) &len,sizeof(int));
    write(sock, o.str().c_str(),len);
    cout<< o.str() << " gesendet!"<< endl;
    disconnect();
}

void TcpClient::sendLoginReply(Spieler* player)
{
    NetworkMessage msgId(LOGINREPLY);
    LoginReply loginRequest(*player);
    stringstream o;
    o << loginRequest;
    int len= strlen(o.str().c_str());

    openConnection();
    write(sock,&msgId,sizeof(LOGINREPLY));
    write(sock,(char*) &len,sizeof(int));
    write(sock, o.str().c_str(),len);
    disconnect();
}

void TcpClient::sendMove(unsigned short column)
{
    openConnection();
    RemoteMove remoteMove(column);
    NetworkMessage msg = REMOTEMOVE;
    write(sock, &msg, sizeof(NetworkMessage) );
    write(sock, &remoteMove, sizeof(RemoteMove) );
    disconnect();
}

void TcpClient::openConnectionBroadcast()
{
    struct sockaddr_in address;
    //struct hostent * host;

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    int broadcastPermission = 1;
        if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission, sizeof(broadcastPermission)) < 0)
            printf("setsockopt() failed");

     memset(&address, 0, sizeof(address));            /* Zero out structure */
     address.sin_family = AF_INET;                       /* Internet address family */
     address.sin_addr.s_addr = inet_addr("192.168.28.105");      /* client IP address */
     address.sin_port = htons(DEFAULT_PORT_UDP);

     char buff[1024];
    int len =strlen(buff);
     /* bind local port for sending */
         if (bind(sock, (struct sockaddr *) &address, sizeof(address)) < 0)
             printf("bind() failed");

         /* Broadcast sendString in datagram */
         if (sendto(sock, buff, len, 0, (struct sockaddr *) &address, sizeof(address)) != len)
             printf("sendto() failed");

    disconnect();
}

void TcpClient::sendHelloBroadcast()
{
    openConnectionBroadcast();
}
