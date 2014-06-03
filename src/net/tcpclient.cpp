#include "../h/net/tcpclient.h"
#include "../h/net/msg/loginreply.h"
#include "../h/net/msg/loginrequest.h"
#include "../h/net/msg/remotemove.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <sstream>
#include <netinet/in.h>
#include <iostream>

using namespace std;

TcpClient::TcpClient(string ipAddress,int port)
{
    this->ipAddress = ipAddress;
    this->port = port;
    this->sock = -1;
    //this->remoteMove = new RemoteMove();
    //this->loginRequest = *new LoginRequest();
    //this->loginReply = new LoginReply();
}

TcpClient::~TcpClient()
{
   //delete loginRequest;
   delete loginReply;
   delete remoteMove;
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
        //fprintf(stderr, "%s: error: unknown host %s\n", argv[0], argv[1]);
        //return -4;
    }

    memcpy(&address.sin_addr, host->h_addr_list[0], host->h_length);

    if(connect(sock, (struct sockaddr *)&address, sizeof(address)))
    {
        //fprintf(stderr, "%s: error: cannot connect to host %s\n", argv[0], argv[1]);
        //return -5;
    }
}

void TcpClient::disconnect()
{
    close(sock);
}

void TcpClient::sendLoginRequest(string playerName)
{
    openConnection();
    LoginRequest loginRequest(playerName);
    NetworkMessage msgId(LOGINREQUEST);
    cout <<"LOGINREQUEST (ID=" << msgId.getId() <<")" << endl;
    write(sock, msgId.toCharArray(), sizeof(NetworkMessage));
    cout <<"Schicke Nachricht..."<< loginRequest<< endl;
    write(sock, loginRequest.toCharArray(),sizeof(LoginRequest));
    disconnect();
}

void TcpClient::sendLoginReply(Spieler* player)
{
    openConnection();
    loginReply->setSpieler(*player);
    NetworkMessage msg = LOGINREPLY;
    write(sock, &msg, sizeof(NetworkMessage) );
    write(sock, loginReply, sizeof(LoginReply) );
    disconnect();
}

void TcpClient::sendMove(unsigned short column)
{
    openConnection();
    remoteMove->setColumn(column);
    NetworkMessage msg = REMOTEMOVE;
    write(sock, &msg, sizeof(NetworkMessage) );
    write(sock, remoteMove, sizeof(RemoteMove) );
    disconnect();
}
