#include "../h/net/tcpserver.h"

#include "../h/sys/FourWinExceptions.h"
#include "../h/net/netmessage.h"
#include "../h/net/msg/loginrequest.h"
#include "../h/net/msg/loginreply.h"
#include "../h/net/msg/remotemove.h"
#include "../h/net/msg/helloreply.h"
#include <pthread.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <sstream>
#include <arpa/inet.h>


TcpServer::TcpServer(int port): Server4Win(TCP,port)
{
    //Do Nothing...
}

TcpServer::~TcpServer()
{
     close(sock);
}

void TcpServer::connect()
{
    Server4Win::connect();
    pthread_create(&tcpServerThread, 0, startTcpServerThread, this);
    //pthread_detach(tcpServerThread);
}

void *TcpServer::startTcpServerThread(void *ptr)
{
    connection_t * connection;
    int sock = ((TcpServer *)ptr)->sock;
    cout << "server gestartet!" << endl;

    try{
    while (((TcpServer *)ptr)->getIsActive())
    {
        cout << "warte auf eingehende Verbindungen..(TCP-SERVER)" << endl;
        connection = (connection_t *)malloc(sizeof(connection_t));
        socklen_t sendsize = sizeof(connection->address);
        connection->sock = accept(sock, (struct sockaddr*)&connection->address,&sendsize); //TODO Hier Select() nachlesen
        if (connection->sock <= 0)
        {
             free(connection);
        }
        else
        {
            char* ip = inet_ntoa(connection->address.sin_addr);
            string ipstr(ip);
            cout << "Verbindungen eingegangen(TCP)..SOCK: " << connection->sock << endl;
            process(connection,ptr);
            close(connection->sock);
            free(connection);
        }
    }
   }
   catch(exception& e){
        cout << e.what() << endl;
   }

     cout << "TCP-SERVER aus der WHILE-Schleife" << endl;
}

void TcpServer::process(connection_t * conn, void *ptr)
{
    int len= 0;
    string templr;
    cout << "starte verarbeitung!" << endl;
    NetworkMessage incomingMessage;
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
            char* ip = inet_ntoa(conn->address.sin_addr);
            string ipstr(ip);
            ((TcpServer *)ptr)->LoginRequestSignal(loginRequest.getPlayerName(),ipstr);
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
        case GIVEUP:
        {
            ((TcpServer *)ptr)->GiveUpSignal();
        }
        break;
        case HELLOREPLY:
        {
            read(conn->sock, &len, sizeof(int));
            char bufferhr[len];
            read(conn->sock, bufferhr, len);

            templr.assign(bufferhr,len);

            char* ip = inet_ntoa(conn->address.sin_addr);
            string ipstr(ip);
            HelloReply helloReply;
            templr.insert(0,ipstr);
            helloReply.fromCsvString(templr);
            cout << helloReply << " empfangen!" << endl;
            ((TcpServer *)ptr)->HelloReplySignal(helloReply);
        }
        default: // Do Nothing...
        break;
    }
}

//--------------------NUR ALS VORLAGE FUER MULTITHREADING SERVER (LISTENER--WORKER)-----------------------------------
/*
void *TcpServer::processThread(void * ptr)
{
    int len;
    NetworkMessage incomingMessage;

    cout << "starte verarbeitung!" << endl;
    connection_t * conn;

    if (!ptr) pthread_exit(0);
        conn = (connection_t *)ptr;


        pthread_create(&thread, 0, process, (void *)connection);
        pthread_detach(thread);

    // empfange Nachricht, nimm nur den ersten Teil der Klasse
    len =sizeof(int);
    char buffer[1];
    read(conn->sock, buffer, 1);
    string temp;
    temp.assign(buffer);
    stringstream rslt;
    rslt << temp;
    rslt >> incomingMessage;

    read(conn->sock, &incomingMessage, sizeof(NetworkMessage));

    //Werte Nachrichtentyp aus..
    switch(incomingMessage.getId())
    {
        case LOGINREQUEST:
        {
            LoginRequest loginRequest;
            read(conn->sock, &loginRequest, sizeof(LoginRequest));
            len= sizeof(LoginRequest);
            char bufferlr[len];
            read(conn->sock, bufferlr, len);
            string templr;
            templr.assign(bufferlr);
            stringstream rsltlr;
            rsltlr << templr;
            rsltlr >> loginRequest;
            //emit on_loginRequest();
            cout << loginRequest << endl;



           char* buf = (char *)malloc(sizeof(LoginRequest));
            read(conn->sock, buf, sizeof(LoginRequest));
            LoginRequest loginRequest;
            loginRequest.fromCharArray(buf);
            string name = loginRequest.getPlayerName();
        }
        break;

        case LOGINREPLY:
        {
            LoginReply loginReply;
            read(conn->sock, &loginReply, sizeof(LoginReply));
            char bufferlrep[sizeof(LoginReply)];
            read(conn->sock, bufferlrep, sizeof(LoginReply));
            string temp;
            temp.assign(bufferlrep);
            temp.clear();
            stringstream rsltlrep;
            rsltlrep << temp;
            cout << rsltlrep.str() << endl;
            rsltlrep >> loginReply;
            temp.clear();
            //emit on_loginRequest();
            cout << loginReply << endl;
         }
         break;
    }
    cout << " beendet!" << endl;

    close(conn->sock);
    free(conn);
    pthread_exit(0);
}
    */



