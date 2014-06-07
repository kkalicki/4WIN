#ifndef CONNECTION4WIN_H
#define CONNECTION4WIN_H

#include <pthread.h>
#include <netinet/in.h>

enum ServerType{TCP=1,UDP=2};

typedef struct
{
    int sock;
    struct sockaddr_in address;
    unsigned int addr_len;
} connection_t;

class Server4Win{

public:
    Server4Win(ServerType serverType,int port);
    ~Server4Win();

    void start();
    void stop();

    int getSock() const;
    void setSock(int value);

    int getPort() const;
    void setPort(int value);

    int getIsActive() const;
    void setIsActive(int value);

protected:
     virtual void connect()=0;
     pthread_t serverThread;
     int sock;
     int port;
     int isActive;

private:
    ServerType serverType;
};

#endif // CONNECTION4WIN_H
