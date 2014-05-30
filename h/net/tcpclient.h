#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "../h/sys/Konstanten.h"
#include "../h/net/msg/loginrequest.h"
#include "../h/net/msg/loginreply.h"
#include "../h/net/msg/remotemove.h"
#include <string>

class TcpClient
{
public:
  TcpClient(int port=DEFAULT_PORT_TCP);
  ~TcpClient();
  void openConnection();
  void disconnect();
  void sendLoginRequest(string playerName);
  void sendLoginReply(Spieler* player);
  void sendMove(unsigned short column);

private:
  int sock;
  int port;
  LoginRequest * loginRequest;
  LoginReply * loginReply;
  RemoteMove* remoteMove;
};

#endif // TCPCLIENT_H
