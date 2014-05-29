#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "../h/sys/Konstanten.h"

class TcpClient
{
public:
  TcpClient(int port=DEFAULT_PORT_TCP);
  ~TcpClient();
  void openConnection();
  void disconnect();
  void sendLoginRequest();
  void sendLoginReply();
  void sendMove();
private:
  int sock;
  int port;
};

#endif // TCPCLIENT_H
