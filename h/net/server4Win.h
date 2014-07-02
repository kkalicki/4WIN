#ifndef CONNECTION4WIN_H
#define CONNECTION4WIN_H

#include <pthread.h>
#include <netinet/in.h>

enum ServerType{TCP=1,UDP=2,HELLO=3};

typedef struct
{
    int sock;
    struct sockaddr_in address;
    socklen_t addr_len;
} connection_t;

/**
 * @brief The Server4Win class
 * Klasse, die alggemein funktionalitäten fuer einen 4WinServer zur Verfuegung stellt. Jeder Server im System
 * erbt von dieser Klasse!
 */
class Server4Win{

public:
    /**
     * @brief Server4Win Konstruktor
     * @param serverType Typ des Servers
     * @param port Port an dem gehorcht wird
     */
    Server4Win(ServerType serverType,int port);
    virtual ~Server4Win();

    /**
     * @brief start Funktion, um Server zu starten
     */
    void start();

    /**
     * @brief stop Funktion, um Server zu stoppen
     */
    void stop();

    /**
     * @brief getSock Getter fuer Socket
     * @return Socketfd
     */
    int getSock() const;

    /**
     * @brief setSock Setter fuer Socketfd
     * @param value Wert
     */
    void setSock(int value);

    /**
     * @brief getPort Getter fuer Port
     * @return port
     */
    int getPort() const;

    /**
     * @brief setPort Setter fuer Port
     * @param value Wert
     */
    void setPort(int value);

    /**
     * @brief getIsActive Getter fuer Flag, ob Server aktiv ist
     * @return true/false
     */
    int getIsActive() const;

    /**
     * @brief setIsActive Setterfuer Flag, ob Server aktiv ist
     * @param value
     */
    void setIsActive(int value);

protected:
    /**
      * @brief connect Funktion um Verbindung herzustellen
      */
     virtual void connect()=0;

    /**
      * @brief isOwnAddress Funktion um eigene Ip-Adresse herauszufiltern
      * @param address Ip-Adresse
      * @return Ip-Adresse
      */
     bool isOwnAddress(sockaddr_in address);
     /**
      * @brief tcpServerThread TcpServerThread
      */
     pthread_t tcpServerThread;

     /**
      * @brief udpServerThread UdpServerThread
      */
     pthread_t udpServerThread;

     /**
      * @brief helloServerThread helloServerThread
      */
     pthread_t helloServerThread;

     /**
      * @brief sock Socketfd
      */
     int sock;

     /**
      * @brief port Port
      */
     int port;

     /**
      * @brief isActive Flag, ob Server aktiv ist
      */
     int isActive;

private:
    ServerType serverType;
};

#endif // CONNECTION4WIN_H
