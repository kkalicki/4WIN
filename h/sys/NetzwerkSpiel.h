#ifndef NETZWERKSPIEL_H
#define NETZWERKSPIEL_H

#include "../h/sys/Spiel.h"
#include "../h/sys/Spieler.h"
#include "../h/sys/Konstanten.h"
#include "../h/net/tcpserver.h"
//#include "../h/net/udpserver.h"
#include "../h/net/tcpclient.h"
#include "boost/signals2.hpp"

using namespace std;

class NetzwerkSpiel : public Spiel
{
public:
    NetzwerkSpiel(unsigned short zeilen=Y, unsigned short spalten=X);
    ~NetzwerkSpiel();
    void starteNetzwerkSpiel(string spielerName);
    void anmeldenNetzwerk(string nameSpieler2);
    void abmeldenNetzwerk();
    void rueckgabeSpielerInfo(Spieler spieler);
    virtual int naechsterZug(Spieler* spieler, unsigned short spalte);

    void on_loginRequest(string loginPlayerName);
    void on_loginReply(Spieler spieler);
    void on_remoteMove(unsigned short column);

    boost::signals2::signal<void(unsigned short, int)> RemoteMoveSignal;
    boost::signals2::signal<void()> StartGameSignal;

protected:
    TcpServer* tcpServer;
    //UdpServer* udpServer;
    TcpClient* tcpClient;
    string nameSpieler1;
};

#endif // NETZWERKSPIEL_H
