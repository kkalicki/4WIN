#include "../h/net/tcpserver.h"

#include "../h/sys/FourWinExceptions.h"
#include "../h/net/netmessage.h"
#include "../h/net/msg/loginrequest.h"
#include "../h/net/msg/loginreply.h"
#include "../h/net/msg/remotemove.h"
#include <pthread.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <sstream>


TcpServer::TcpServer(int port)
{
    this->port = port;
    this->sock = -1;
}

int TcpServer::getSock() const
{
    return sock;
}

void TcpServer::setSock(int value)
{
    sock = value;
}
int TcpServer::getIsActive() const
{
    return isActive;
}

void TcpServer::setIsActive(int value)
{
    isActive = value;
}


TcpServer::~TcpServer()
{
    // kein new...
}

void TcpServer::start()
{
    connect();
}

void TcpServer::stop()
{
    isActive = false;
    cout << "stoppe Server!" << endl;
    if(sock > -1)
    {
        close(sock);
        cout << "Socket geschlossen!" << endl;
    }

    pthread_cancel(tcpServerThread);
    cout << "Serverthread geschlossen!" << endl;
}

void TcpServer::connect()
{
    struct sockaddr_in address;
    //pthread_t thread;

    cout << "erstelle Socket!" << endl;
    sock = (socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));
    if (sock <= 0)
    {
      throw TcpServerException("Socket konnte nicht erstellt werden!");
    }

    /* bind socket to port */
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    cout << "Binde Socket!" << endl;
    if (bind(sock, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) < 0)
    {
        ostringstream o;
        o << "Socket konnte nicht an Port gebunden werden ! (" << port << ")" << endl;
        throw TcpServerException(o.str());
    }

    if (listen(sock, 5) < 0)
    {
        ostringstream o;
        o << "Server kann horchen an Port! (" << port << ")" << endl;
        throw TcpServerException(o.str());
    }

    isActive = true;
    cout << "starte Server!" << endl;
    pthread_create(&tcpServerThread, 0, startServerThread, this);
    pthread_detach(tcpServerThread);
}


void *TcpServer::startServerThread(void * ptr)
{
    connection_t * connection;
    int sock = ((TcpServer *)ptr)->sock;
    cout << "server gestartet!" << endl;
    while (true)
    {
        cout << "warte auf eingehende Verbindungen.." << endl;
        connection = (connection_t *)malloc(sizeof(connection_t));
        connection->sock = accept(sock, &connection->address, &connection->addr_len); //TODO Hier Select() nachlesen
        if (connection->sock <= 0)
        {
             free(connection);
        }
        else
        {
            cout << "Verbindungen eingegangen..PORT: " << connection->sock << endl;
            process(connection,ptr);
            close(connection->sock);
            free(connection);
        }
    }
}

void TcpServer::process(connection_t * conn, void *ptr)
{
    int len= 0;
    string templr;
    cout << "starte verarbeitung!" << endl;
    NetworkMessage incomingMessage(LOGINREQUEST);
    read(conn->sock, &incomingMessage, sizeof(NetworkMessage));
    switch(incomingMessage.getId())
    {
        case LOGINREQUEST:
        {
            read(conn->sock, &len, sizeof(int));
            char bufferlr[len];
            read(conn->sock, bufferlr, len);

            templr.assign(bufferlr,len);
            stringstream rsltlr;
            rsltlr << templr;
            LoginRequest loginRequest;
            rsltlr >> loginRequest;
            cout << loginRequest << " empfangen!" << endl;
            ((TcpServer *)ptr)->LoginRequestSignal(loginRequest.getPlayerName());
        }
        break;
        case LOGINREPLY:
        {
            read(conn->sock, &len, sizeof(int));
            char bufferlr[len];
            read(conn->sock, bufferlr, len);

            templr.assign(bufferlr,len);
            LoginReply loginRequest;
            loginRequest.fromCsvString(templr);
            cout << loginRequest << " empfangen!" << endl;
            ((TcpServer *)ptr)->LoginReplySignal(loginRequest.getSpieler());
        }
        break;
        case REMOTEMOVE:
        {
            RemoteMove remoteMove;
            read(conn->sock, &remoteMove, sizeof(RemoteMove));
            ((TcpServer *)ptr)->RemoteMoveSignal(remoteMove.getColumn());
        }
        break;
        default: // Do Nothing...
        break;
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


        /*pthread_create(&thread, 0, process, (void *)connection);
        pthread_detach(thread);*/

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



            /*char* buf = (char *)malloc(sizeof(LoginRequest));
            read(conn->sock, buf, sizeof(LoginRequest));
            LoginRequest loginRequest;
            loginRequest.fromCharArray(buf);
            string name = loginRequest.getPlayerName();*/
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



