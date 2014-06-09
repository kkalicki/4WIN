#include "../h/net/helloserver.h"
#include "../h/net/msg/helloreply.h"
#include "../h/net/netmessage.h"
#include <netdb.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

HelloServer::HelloServer(int port): Server4Win(HELLO,port)
{
    udpsock= socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int broadcastPermission = 1;

    if (setsockopt(udpsock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission, sizeof(broadcastPermission)) < 0)
        printf("setsockopt() failed");

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(BROADCAST.c_str());
    address.sin_port = htons(DEFAULT_PORT_UDP);
}

HelloServer::~HelloServer()
{
    close(udpsock);
    close(sock);
}

void HelloServer::connect()
{
    Server4Win::connect();
    pthread_create(&helloServerThread, 0, startTcpServerThread, this);
    //pthread_detach(helloServerThread);
}

void *HelloServer::startTcpServerThread(void *ptr)
{
    connection_t * connection;
    int sock = ((HelloServer *)ptr)->sock;
    cout << "server gestartet!" << endl;
    try
    {
        while (((HelloServer *)ptr)->getIsActive())
        {
            cout << "warte auf eingehende Verbindungen.." << endl;
            connection = (connection_t *)malloc(sizeof(connection_t));
            connection->sock = accept(sock, (struct sockaddr*)&connection->address, &connection->addr_len); //TODO Hier Select() nachlesen
            if (connection->sock <= 0)
            {
                 free(connection);
            }
            else
            {
                cout << "Verbindungen eingegangen(TCP)..Port: " <<  ((HelloServer *)ptr)->port << endl;
                cout << "starte verarbeitung!" << endl;

                NetworkMessage incomingMessage;
                read(connection->sock, &incomingMessage, sizeof(NetworkMessage));

                if(incomingMessage.getId() == HELLOREPLY)
                {

                    int len;
                    string temp;

                    read(connection->sock, &len, sizeof(int));
                    char bufferhr[len];
                    read(connection->sock, bufferhr, len);
                    temp.assign(bufferhr,len);
                    char* ip = inet_ntoa(connection->address.sin_addr);
                    string ipstr(ip);
                    HelloReply helloReply;
                    temp.insert(0,ipstr);
                    helloReply.fromCsvString(temp);
                    cout << helloReply << " empfangen!" << endl;
                    ((HelloServer *)ptr)->HelloReplySignal(helloReply);

                }
                close(connection->sock);
                free(connection);
            }
        }
    }catch(exception& e)
    {
        cout << "HELLOSERVER in CATCH-CLAUSE...." << e.what()<< endl;
    }


     cout << "HELLOSERVER aus der WHILE-Schleife" << endl;
}

void HelloServer::sendHelloBroadcast()
{
    NetworkMessage networkMessage(UDPHELLO);
    sendto(udpsock,&networkMessage,sizeof(NetworkMessage),0,(struct sockaddr*)&address, sizeof(address));
}
