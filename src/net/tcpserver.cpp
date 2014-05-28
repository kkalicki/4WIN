#include "../h/net/tcpserver.h"

#include <pthread.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include "../h/net/netmessage.h"
#include "../h/net/msg/loginrequest.h"
#include "../h/net/msg/loginreply.h"
#include <sstream>


TcpServer::TcpServer(int port)
{
    this->ipAdresse = ipAdresse;
    this->port = port;
}

TcpServer::~TcpServer()
{

}

void TcpServer::start()
{
    isActive = true;
    cout << "starte Server!" << endl;
    pthread_create(&tcpServerThread, 0, startServerThread, 0);
    pthread_detach(tcpServerThread);
}

void TcpServer::stop()
{
    isActive = false;
    pthread_cancel(tcpServerThread);
}


void *TcpServer::startServerThread(void * ptr)
{
    int sock = -1;
    struct sockaddr_in address;
    int port = 8000;
    connection_t * connection;
    //pthread_t thread;

    cout << "erstelle Socket!" << endl;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock <= 0)
    {
        //fprintf(stderr, "%s: error: cannot create socket\n", argv[0]);
        //return -3;
    }

    /* bind socket to port */
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    cout << "Binde Socket!" << endl;
    if (bind(sock, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) < 0)
    {
        //fprintf(stderr, "%s: error: cannot bind socket to port %d\n", argv[0], port);
        //return -4;
    }

    if (listen(sock, 5) < 0)
    {
        //fprintf(stderr, "%s: error: cannot listen on port\n", argv[0]);
        //return -5;
    }

    cout << "server gestartet!" << endl;
    while (true)
    {
        cout << "warte auf eingehende Verbindungen.." << endl;
        /* accept incoming connections */
        connection = (connection_t *)malloc(sizeof(connection_t));
        connection->sock = accept(sock, &connection->address, &connection->addr_len); //TODO Hier Select() nachlesen
//        if (connection->sock <= 0)
//        {
//            free(connection);
//        }
//        else
//        {
            /* start a new thread but do not wait for it */
            cout << "Verbindungen eingegangen.." << endl;
            /*pthread_create(&thread, 0, process, (void *)connection);
            pthread_detach(thread);*/
            process(connection);
            close(connection->sock);
            free(connection);
       // }
    }
}

void *TcpServer::processThread(void * ptr)
{
    int len;
    NetworkMessage incomingMessage;

    cout << "starte verarbeitung!" << endl;
    connection_t * conn;

    if (!ptr) pthread_exit(0);
        conn = (connection_t *)ptr;

    // empfange Nachricht, nimm nur den ersten Teil der Klasse
    /*len =sizeof(int);
    char buffer[1];
    read(conn->sock, buffer, 1);
    string temp;
    temp.assign(buffer);
    stringstream rslt;
    rslt << temp;
    rslt >> incomingMessage;*/

    read(conn->sock, &incomingMessage, sizeof(NetworkMessage));

    //Werte Nachrichtentyp aus..
    switch(incomingMessage.getId())
    {
        case LOGINREQUEST:
        {
            LoginRequest loginRequest;
            read(conn->sock, &loginRequest, sizeof(LoginRequest));
            /*len= sizeof(LoginRequest);
            char bufferlr[len];
            read(conn->sock, bufferlr, len);
            string templr;
            templr.assign(bufferlr);
            stringstream rsltlr;
            rsltlr << templr;
            rsltlr >> loginRequest;*/
            //emit on_loginRequest();
            cout << loginRequest << endl;
        }
        break;

        case LOGINREPLY:
        {
            LoginReply loginReply;
            read(conn->sock, &loginReply, sizeof(LoginReply));
            /*char bufferlrep[sizeof(LoginReply)];
            read(conn->sock, bufferlrep, sizeof(LoginReply));
            string temp;
            temp.assign(bufferlrep);
            temp.clear();
            stringstream rsltlrep;
            rsltlrep << temp;
            cout << rsltlrep.str() << endl;
            rsltlrep >> loginReply;
            temp.clear();
            //emit on_loginRequest();*/
            cout << loginReply << endl;
         }
         break;
    }
    cout << " beendet!" << endl;

    /* close socket and clean up */
    close(conn->sock);
    free(conn);
    pthread_exit(0);
}

void TcpServer::process(connection_t * conn)
{
    cout << "starte verarbeitung!" << endl;

    NetworkMessage incomingMessage;
    read(conn->sock, &incomingMessage, sizeof(NetworkMessage));
    switch(incomingMessage.getId())
    {
        case LOGINREQUEST:
        {
            LoginRequest* loginRequest = new LoginRequest();
            read(conn->sock, loginRequest, sizeof(LoginRequest));
            cout << *loginRequest << endl;
            //delete loginRequest;
        }
        break;
        case LOGINREPLY:
        {
            LoginReply* loginReply = new LoginReply();
            read(conn->sock, loginReply, sizeof(LoginReply));
            cout << *loginReply << endl;
            //delete loginReply;
        }
        break;
        default:
        break;
    }
}





