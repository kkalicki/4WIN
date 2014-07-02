#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "../h/sys/Konstanten.h"
#include "../h/net/msg/loginrequest.h"
#include "../h/net/msg/loginreply.h"
#include "../h/net/msg/remotemove.h"
#include "../h/net/msg/helloreply.h"
#include "../h/net/msg/visitorpackage.h"
#include <string>

/**
 * @brief The TcpClient class
 * Klasse die Netzwerknachrichten verschickt. Es werden nicht nur TCP Nachrichten verschickt, sonder auch UDP-Nachrichten
 */
class TcpClient
{
public:
    /**
   * @brief TcpClient Konstruktor
   * @param ipAddress IP-Adresse
   * @param port      Port
   */
  TcpClient(string ipAddress=LOCALHOST, int port=DEFAULT_PORT_TCP);
  ~TcpClient();
  /**
   * @brief openConnection Funktion um Tcp-Verbindung zu oeffnen
   * @param ipAddress Ip-Adresse des Remotehosts
   * @param port Port des Remotehosts
   */
  void openConnection(string ipAddress, int port);

  /**
   * @brief disconnect TCP-Verbindung schliessen
   */
  void disconnect();

  /**
   * @brief sendLoginRequest Funktion, um LoginRequest-Nachricht zu senden
   * @param playerName Spielername fuer das Objekt LoginRequest
   */
  void sendLoginRequest(string playerName);

  /**
   * @brief sendLoginReply Funktion, um LoginReply-Nachricht zu senden
   * @param player Spielerobjekt fuer LoginReply
   */
  void sendLoginReply(Spieler* player);

  /**
   * @brief sendMove Funktion, um einen RemoteMove zu senden
   * @param column Spalte des Wurfs
   */
  void sendMove(unsigned short column);

  /**
   * @brief sendGiveUp Funktion, um eine GiveUp-Nachricht zu senden (Aufgeben eines Remotespielers)
   */
  void sendGiveUp();

  /**
   * @brief openConnectionBroadcast Funktion, zum initialisieren einer UDP Verbindung
   */
  void openConnectionBroadcast();

  /**
   * @brief sendHelloBroadcast Funktion, um Broadcast zu senden, um herauszufinden ob Spiele offen sind
   */
  void sendHelloBroadcast();

  /**
   * @brief sendVisitorPackageBroadcast Funktion, um VisitorPackage fuer Zuschauermodus zu senden
   * @param pack VisitorPackage mit Informationen fuer den Zuschauermodus
   */
  void sendVisitorPackageBroadcast(VisitorPackage *pack);

  /**
   * @brief sendHelloReply Funktion, um auf offene-Spiele-Anfrage zu antworten
   * @param ip          Ip-Des RemoteSpiels
   * @param reply       HelloReplyPacket mit Informationen zum offenen Spiel
   */
  void sendHelloReply(string ip,HelloReply* reply);

  /**
    * @brief getIpAddress Getter fuer Ip-Addresse
    * @return Ip-Adresse
    */
   string getIpAddress() const;

   /**
    * @brief setIpAddress Setter fuer Ip-Adresse
    * @param value Wert
    */
   void setIpAddress(string value);

private:
   /**
    * @brief sock TCPSocketfd
    */
   int sock;

   /**
    * @brief UDPsocketfd
    */
   int udpsock;

   /**
    * @brief port Port zu dem gesendet werden soll
    */
   int port;

   /**
    * @brief ipAddress zu der gesendet werden soll
    */
   string ipAddress;
};

#endif // TCPCLIENT_H
