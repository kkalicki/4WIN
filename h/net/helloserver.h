#ifndef HELLOSERVER_H
#define HELLOSERVER_H

#include "../h/net/server4Win.h"
#include "../h/net/msg/helloreply.h"
#include "../h/sys/Konstanten.h"
#include "boost/signals2.hpp"

#include <string>
#include <iostream>
using namespace std;

/**
 * @brief The HelloServer class
 * Klasse, mit der es moeglich ist Anfragen zu stellen, ob ein Spiel im Netzwerk offen ist.
 * Diese Klasse erhalt durch die Serverarchitektur per Tcp eine Antwort mit den notwendigen Informationen
 * Diese Klasse ist von der Klasse Server4Win abgeleitet
 */
class HelloServer : public Server4Win{
public:
    /**
     * @brief HelloServer Konstruktor
     * @param port Port auf dem der Server aktiv ist
     */
    HelloServer(int port=DEFAULT_PORT_HELLO);
    ~HelloServer();

    /**
     * @brief startTcpServerThread Funktion, um den Server in einem Thread zu starten
     * @param ptr Klasse als Pointer
     * @return Funktion als Pointer
     */
    static void * startTcpServerThread(void * ptr);
    /**
     * @brief sendHelloBroadcast Funktion um Broadcast-Anfragen zu senden
     */
    void sendHelloBroadcast();

    /**
     * @brief HelloReplySignal Signal,um eingehende Nachrichten dem System zu signalisieren
     */
    boost::signals2::signal<void(HelloReply)> HelloReplySignal;

protected:
    /**
     * @brief connect Funktion um den Server zu verbinden
     */
    virtual void connect();

    /**
     * @brief address Sockaddress_in struktur fuer ausgehende Nachrichten
     */
    struct sockaddr_in address;
    /**
     * @brief udpsock Socketfd des Servers
     */
    int udpsock;
};

#endif // HELLOSERVER_H
