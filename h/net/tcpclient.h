#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "../h/sys/Konstanten.h"
#include "../h/net/msg/loginrequest.h"
#include "../h/net/msg/loginreply.h"
#include "../h/net/msg/remotemove.h"
#include "../h/net/msg/helloreply.h"
#include <string>

class TcpClient
{
public:
  TcpClient(string ipAddress=LOCALHOST, int port=DEFAULT_PORT_TCP);
  ~TcpClient();
  void openConnection(string ipAddress, int port);
  void disconnect();
  void sendLoginRequest(string playerName);
  void sendLoginReply(Spieler* player);
  void sendMove(unsigned short column);
  void sendGiveUp();

  void openConnectionBroadcast();
  void sendHelloBroadcast();
   void sendHelloReply(string ip,HelloReply* reply);

   string getIpAddress() const;
   void setIpAddress(const string &value);

private:
   int sock;
   int udpsock;
   int port;
   string ipAddress;
};

#endif // TCPCLIENT_H
