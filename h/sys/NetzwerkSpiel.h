#ifndef NETZWERKSPIEL_H
#define NETZWERKSPIEL_H

#include "../h/sys/Spiel.h"
#include "../h/sys/Spieler.h"
#include "../h/sys/Konstanten.h"
#include "../h/net/tcpserver.h"
#include "../h/net/tcpclient.h"

using namespace std;

class NetzwerkSpiel : Spiel
{
public:
    NetzwerkSpiel(unsigned short zeilen=Y, unsigned short spalten=X);
    ~NetzwerkSpiel();
    void starteNetzwerkSpiel(string spielerName);
    void anmeldenNetzwerk(string nameSpieler2);
    void abmeldenNetzwerk();
    void rueckgabeSpielerInfo(Spieler spieler);

    void on_loginRequest(string loginPlayerName);
    void on_loginReply(Spieler spieler);
    void on_remoteMove(unsigned short column);

protected:
    TcpServer* tcpServer;
    TcpClient* tcpClient;
};

#endif // NETZWERKSPIEL_H
