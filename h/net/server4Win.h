#ifndef CONNECTION4WIN_H
#define CONNECTION4WIN_H

#include <pthread.h>

class Server4Win{

public:
    void start();
    void stop();
    void connect()=0;
    static void * startServerThread(void * ptr);

private:
    pthread_t tcpServerThread;
    int sock;
    int port;
    int isActive;
};

#endif // CONNECTION4WIN_H
