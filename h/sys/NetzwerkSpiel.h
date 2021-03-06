#ifndef NETZWERKSPIEL_H
#define NETZWERKSPIEL_H

#include "../h/sys/Spiel.h"
#include "../h/sys/Spieler.h"
#include "../h/sys/Konstanten.h"
#include "../h/net/server4Win.h"
#include "../h/net/tcpclient.h"
#include "boost/signals2.hpp"

using namespace std;

/**
 * Die NetzwerkSpiel-Klasse dient zur eröffnung eines Netzwerkspiels. zusätzlich bietet das Netzwerkspiel noch einen Besuchermodus.
 * Die Klasse erbt von der Klasse Spiel.
 */
class NetzwerkSpiel : public Spiel
{
public:
    NetzwerkSpiel(unsigned short zeilen=Y, unsigned short spalten=X);
    ~NetzwerkSpiel();
    void starteNetzwerkSpiel(string spielerName);
    void anmeldenNetzwerk(string nameSpieler2, int gameId, bool visitorMode);
    void abmeldenNetzwerk();
    void startClient(string ip);
    void rueckgabeSpielerInfo(Spieler spieler);
    virtual int naechsterZug(Spieler* spieler, unsigned short spalte);
    virtual void aufgeben();
    virtual void beenden();

    void sendHello();

    void startTcpServer();
    void stopTcpServer();

    void startUdpServer();
    void stopUdpServer();

    void on_loginRequest(string loginPlayerName,string ip);
    void on_loginReply(Spieler spieler);
    void on_remoteMove(unsigned short column);
    void on_giveUp();
    void on_helloReply(HelloReply reply);


    void on_visitorPackage(VisitorPackage vp);
    void on_udpHello(string remoteIp);

    boost::signals2::signal<void(unsigned short, int)> RemoteMoveSignal;
    boost::signals2::signal<void()> StartGameSignal;
    boost::signals2::signal<void(Spieler*,bool)> GiveUpRemotePlayerSignal;
    boost::signals2::signal<void(HelloReply)> HelloReplySignal;
    boost::signals2::signal<void(VisitorPackage,int)> VisitorPackageSignal;

protected:
    Server4Win* tcpServer;
    Server4Win* udpServer;
    TcpClient* tcpClient;
    string nameSpieler1;
    Spieler * remoteSpieler;
    bool visitorMode;
    Spieler visitorSp1;
    Spieler visitorSp2;
};

#endif // NETZWERKSPIEL_H
