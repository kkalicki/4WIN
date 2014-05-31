#include "../h/net/tcpclient.h"
#include "../h/net/msg/loginreply.h"
#include "../h/net/msg/loginrequest.h"
#include "../h/net/msg/remotemove.h"

#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <sstream>
#include <netinet/in.h>
#include <iostream>

using namespace std;

TcpClient::TcpClient(int port)
{
    this->port = port;
    this->sock = -1;
    this->remoteMove = new RemoteMove();
    this->loginRequest = new LoginRequest();
    this->loginReply = new LoginReply();
}

TcpClient::~TcpClient()
{
   delete loginRequest;
   delete loginReply;
   delete remoteMove;
}

void TcpClient::openConnection()
{
    struct sockaddr_in address;
    struct hostent * host;

    /* create socket */
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    /* connect to server */
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    host = gethostbyname("192.168.28.108");
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
    loginRequest->setPlayerName(playerName);
    NetworkMessage msg = LOGINREQUEST;
    write(sock, &msg, sizeof(NetworkMessage));
    write(sock, loginRequest,sizeof(LoginRequest));
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
