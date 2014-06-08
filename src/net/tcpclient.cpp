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

void TcpClient::openConnection(string ipAddress,int port)
{
    struct sockaddr_in address;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock <= 0)
        throw ClientException("Client konnte keinen Socket erstellen!");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    if(connect(sock, (struct sockaddr *)&address, sizeof(address)))
        throw ClientException("Client konnte keine Verbindung zum Server herstellen (" +ipAddress+")");

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

    openConnection(this->ipAddress,DEFAULT_PORT_TCP);
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

    openConnection(this->ipAddress,DEFAULT_PORT_TCP);
    write(sock,&msgId,sizeof(LOGINREPLY));
    write(sock,(char*) &len,sizeof(int));
    write(sock, o.str().c_str(),len);
    cout<<"LOGINREPLY "<< o.str() << " gesendet!"<< endl;
    disconnect();
}

void TcpClient::sendMove(unsigned short column)
{
    openConnection(this->ipAddress,DEFAULT_PORT_TCP);
    RemoteMove remoteMove(column);
    NetworkMessage msg(REMOTEMOVE);
    write(sock, &msg, sizeof(NetworkMessage) );
    write(sock, &remoteMove, sizeof(RemoteMove) );
    cout<< "REMOTEMOVE "<< column <<" gesendet!"<< endl;
    disconnect();
}

void TcpClient::sendGiveUp()
{
    openConnection(this->ipAddress,DEFAULT_PORT_TCP);
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
}

void TcpClient::sendHelloBroadcast()
{
    openConnectionBroadcast();
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(BROADCAST);
    address.sin_port = htons(DEFAULT_PORT_UDP);

    NetworkMessage networkMessage(UDPHELLO);
    sendto(udpsock,&networkMessage,sizeof(NetworkMessage),MSG_SEND,(struct sockaddr*)&address, sizeof(address));

    close(udpsock);
}

void TcpClient::sendHelloReply(string ip, HelloReply *reply)
{
    NetworkMessage msgId(HELLOREPLY);
    stringstream o;
    o << *reply;
    int len= strlen(o.str().c_str());

    openConnection(ip,DEFAULT_PORT_HELLO);
    write(sock,&msgId,sizeof(HELLOREPLY));
    write(sock,(char*) &len,sizeof(int));
    write(sock, o.str().c_str(),len);
    cout<<"HELLOREPLY "<< o.str() << " gesendet!"<< endl;
    disconnect();
}
string TcpClient::getIpAddress() const
{
    return ipAddress;
}

void TcpClient::setIpAddress(string value)
{
    ipAddress = value;
}

