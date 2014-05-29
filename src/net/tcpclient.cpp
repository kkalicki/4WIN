#include "../h/net/tcpclient.h"
#include "../h/net/msg/loginreply.h"
#include "../h/net/msg/loginrequest.h"

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
}

TcpClient::~TcpClient()
{

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
    host = gethostbyname("127.0.0.1");
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

void TcpClient::sendLoginRequest()
{
    openConnection();
    LoginRequest *testRequest = new LoginRequest("MAX_REQUEST");
    NetworkMessage msg = LOGINREQUEST;
    write(sock, &msg, sizeof(NetworkMessage));
    int rslt = write(sock, testRequest,sizeof(LoginRequest));

    //sleep(5);
    cout << "sleep finished" << endl;
    disconnect();
    //delete testRequest;
}

void TcpClient::sendLoginReply()
{
    openConnection();
    Spieler test2("MAXIMILIAN_REPLAY");
    LoginReply* testReplay = new LoginReply(test2);
    NetworkMessage msg = LOGINREPLY;
    write(sock, &msg, sizeof(NetworkMessage) );
    write(sock, testReplay, sizeof(LoginReply) );
    disconnect();
    //delete testReplay;
}

void TcpClient::sendMove()
{

}
