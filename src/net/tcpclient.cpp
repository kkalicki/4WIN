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

void TcpClient::openConnection(string ipAddress)
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

    openConnection(this->ipAddress);
    write(sock,&msgId,sizeof(LOGINREQUEST));
    write(sock,(char*) &len,sizeof(int));
    write(sock, o.str().c_str(),len);
    cout<<"LOGINREQUEST "<< o.str() << " gesendet!"<< endl;
    disconnect();
}

void TcpClient::sendLoginReply(Spieler* player)
{
    NetworkMessage msgId(LOGINREPLY);
    LoginReply loginRequest(*player);
    stringstream o;
    o << loginRequest;
    int len= strlen(o.str().c_str());

    openConnection(this->ipAddress);
    write(sock,&msgId,sizeof(LOGINREPLY));
    write(sock,(char*) &len,sizeof(int));
    write(sock, o.str().c_str(),len);
    cout<<"LOGINREPLY "<< o.str() << " gesendet!"<< endl;
    disconnect();
}

void TcpClient::sendMove(unsigned short column)
{
    openConnection(this->ipAddress);
    RemoteMove remoteMove(column);
    NetworkMessage msg(REMOTEMOVE);
    write(sock, &msg, sizeof(NetworkMessage) );
    write(sock, &remoteMove, sizeof(RemoteMove) );
    cout<< "REMOTEMOVE "<< column <<" gesendet!"<< endl;
    disconnect();
}

void TcpClient::sendGiveUp()
{
    openConnection(this->ipAddress);
    NetworkMessage msg(GIVEUP);
    write(sock, &msg, sizeof(NetworkMessage) );
    cout<< "GIVEUP gesendet!"<< endl;
    disconnect();
}

void TcpClient::openConnectionBroadcast()
{
    //struct hostent * host;

    udpsock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    int broadcastPermission = 1;
        if (setsockopt(udpsock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission, sizeof(broadcastPermission)) < 0)
            printf("setsockopt() failed");
    disconnect();
}

void TcpClient::sendHelloBroadcast()
{
    openConnectionBroadcast();
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("192.168.28.255");
    address.sin_port = htons(DEFAULT_PORT_UDP);

    NetworkMessage networkMessage(UDPHELLO);
    sendto(udpsock,&networkMessage,sizeof(NetworkMessage),MSG_SEND,(struct sockaddr*)&address, sizeof(address));

    disconnect();
}

void TcpClient::sendHelloReply(string ip, HelloReply *reply)
{
    NetworkMessage msgId(HELLOREPLY);
    stringstream o;
    o << *reply;
    int len= strlen(o.str().c_str());

    openConnection(this->ipAddress);
    write(sock,&msgId,sizeof(LOGINREPLY));
    write(sock,(char*) &len,sizeof(int));
    write(sock, o.str().c_str(),len);
    cout<<"HELLOREPLY "<< o.str() << " gesendet!"<< endl;
    disconnect();
}
