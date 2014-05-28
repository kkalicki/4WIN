#ifndef TCPCLIENT_H
#define TCPCLIENT_H
class TcpClient
{
public:
  TcpClient(int port=8000);
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
