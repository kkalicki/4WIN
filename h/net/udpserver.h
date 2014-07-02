#ifndef UDPSERVER_H
#define UDPSERVER_H

#include "../h/sys/Konstanten.h"
#include "../h/net/server4Win.h"
#include "../h/net/netmessage.h"
#include "../h/net/msg/visitorpackage.h"
#include "boost/signals2.hpp"

using namespace std;

/**
 * @brief The UdpServer class
 * Klasse, die ein UdpServer darstellt. Diese Klasse wartet auf eingehende UDP-Nachrichten, wertet diese aus und
 * signalisiert dem System das und welche Nachricht eingegangen ist
 */
class UdpServer : public Server4Win{
public:
    /**
     * @brief UdpServer Konstruktor
     * @param port Port auf dem der Server aktiviert werden soll
     */
    UdpServer(int port=DEFAULT_PORT_UDP);
    ~UdpServer();

    /**
     * @brief startUdpServerThread Funktion, um Server in einem Thread zu starten
     * @param ptr Klassenpointer
     * @return Funktionspointer
     */
    static void *startUdpServerThread(void * ptr);

    /**
     * @brief processThread Funktion um eingehende Nachrichten zu verarbeiten
     * @param sender        struktur mit Daten der eingehenden Verbindung
     * @param ptr           Funktionspointer
     * @param mid           Id- der Nachricht die einging
     * @return              Funktionspointer
     */
    static void *processThread(struct sockaddr_in sender, void *ptr, NetworkMessage mid);

    /**
     * @brief UdpHelloSignal Signal bei eingehendem UdpHello
     */
    boost::signals2::signal<void(string)> UdpHelloSignal;
    /**
     * @brief VisitorPackageSignal  Signal bei eingehendem VisitorPackage
     */
    boost::signals2::signal<void(VisitorPackage)> VisitorPackageSignal;

protected:
    /**
     * @brief connect Funktion, um den Server zu initialisieren
     */
    virtual void connect();

private:
    /**
     * @brief thread Thread fuer den Server
     */
    pthread_t thread;
};
#endif // UDPSERVER_H
