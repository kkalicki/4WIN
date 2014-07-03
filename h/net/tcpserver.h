#ifndef SERVER_H
#define SERVER_H

#include "../h/net/server4Win.h"
#include "../h/sys/Konstanten.h"
#include "../h/sys/Spieler.h"
#include "../h/net/msg/remotemove.h"
#include "../h/net/msg/helloreply.h"
#include "boost/signals2.hpp"
#include <netinet/in.h>
#include <iostream>
#include <string>
using namespace std;

/**
 * @brief The TcpServer class
 * Klasse, die ein TCPServer darstellt. Diese Klasse wartet auf eingehende Tcp-Nachrichten, wertet diese aus und
 * signalisiert dem System das und welche Nachricht eingegangen ist
 */
class TcpServer: public Server4Win{
public:
    /**
     * @brief TcpServer Konstruktor
     * @param port  Port auf dem dieser Server aktiv ist
     */
    TcpServer(int port=DEFAULT_PORT_TCP);
    ~TcpServer();

    /**
     * @brief startTcpServerThread Funktion um Server in einem Thread zu starten
     * @param ptr Pointer auf eigene Klasse
     * @return Funktionspointer
     */
    static void * startTcpServerThread(void * ptr);

    /**
     * @brief process Funktion, um Anfrage zu bearbeiten
     * @param conn Connection struktur mit informationen des Anfragenden
     * @param ptr Klassenpointer
     */
    static void process(connection_t * conn, void * ptr);

    /**
     * @brief LoginRequestSignal Signal bei eingehendem LoginRequest
     */
    boost::signals2::signal<void(string,string)> LoginRequestSignal;

    /**
     * @brief LoginReplySignal Signal bei eingehendem LoginReply
     */
    boost::signals2::signal<void(Spieler)> LoginReplySignal;

    /**
     * @brief RemoteMoveSignal Signal bei eingehendem RemoteMove
     */
    boost::signals2::signal<void(unsigned short)> RemoteMoveSignal;
    /**
     * @brief GiveUpSignalSignal Signal bei eingehendem GiveUP
     */
    boost::signals2::signal<void()> GiveUpSignal;

    /**
     * @brief HelloReplySignal Signal bei eingehendem HelloReply
     */
    boost::signals2::signal<void(HelloReply)> HelloReplySignal;

protected:

    /**
     * @brief connect Funktion, um Server zu initialisieren
     */
    virtual void connect();

};

#endif // SERVER_H
