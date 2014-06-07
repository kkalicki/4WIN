
#include "../h/sys/NetzwerkSpiel.h"
#include "../h/net/tcpclient.h"
#include "../h/net/tcpserver.h"
#include "../h/net/udpserver.h"
#include "boost/bind.hpp"
#include "iostream"

NetzwerkSpiel::NetzwerkSpiel(unsigned short zeilen, unsigned short spalten) : Spiel(zeilen,spalten)
{
    this->tcpServer = new TcpServer();
    dynamic_cast<TcpServer*>(tcpServer)->LoginRequestSignal.connect(boost::bind(&NetzwerkSpiel::on_loginRequest, this,_1));
    dynamic_cast<TcpServer*>(tcpServer)->LoginReplySignal.connect(boost::bind(&NetzwerkSpiel::on_loginReply, this,_1));
    dynamic_cast<TcpServer*>(tcpServer)->RemoteMoveSignal.connect(boost::bind(&NetzwerkSpiel::on_remoteMove, this,_1));
    dynamic_cast<TcpServer*>(tcpServer)->GiveUpSignal.connect(boost::bind(&NetzwerkSpiel::on_giveUp, this));
    dynamic_cast<TcpServer*>(tcpServer)->HelloReplySignal.connect(boost::bind(&NetzwerkSpiel::on_helloReply, this,_1));
    tcpServer->start();

    this->udpServer = new UdpServer();
    dynamic_cast<UdpServer*>(udpServer)->UdpHelloSignal.connect(boost::bind(&NetzwerkSpiel::on_udpHello, this,_1));
    udpServer->start();

    this->tcpClient = new TcpClient("192.168.28.108");
}

NetzwerkSpiel::~NetzwerkSpiel()
{
    std::cout << "schließe Netzwerkspiel!!!" << endl;
    if(tcpServer->getIsActive())
        tcpServer->stop();

    if(udpServer->getIsActive())
        udpServer->stop();

    delete tcpServer;
    delete udpServer;
    delete tcpClient;
    std::cout << "Netzwerkspiel geschlossen!!!" << endl;
}

void NetzwerkSpiel::starteNetzwerkSpiel(string spielerName)
{
   cout << "starte Netzwerkspiel..."<< endl;
   this->nameSpieler1 = spielerName;
}

void NetzwerkSpiel::anmeldenNetzwerk(string nameSpieler2)
{
    this->sp2 = new Spieler(nameSpieler2);
    this->remoteSpieler = sp2;
    cout << "melde an..."<< endl;
    tcpClient->sendLoginRequest(nameSpieler2);
}

void NetzwerkSpiel::rueckgabeSpielerInfo(Spieler spieler)
{
    cout << "Anmeldung erfolgreich!"<< endl;
    //zuweisungsoperator ueberschreiben
    this->sp1 = new Spieler(spieler.getName());
    sp1->setIstAmZug(spieler.getIstAmZug());
    sp1->setFarbe(spieler.getFarbe());

    if(sp1->getFarbe() == ROT)
    {
        sp2->setFarbe(GELB);
    }
    else{
        sp2->setFarbe(ROT);
    }

    //finde heraus wer anfaengt!
    if(sp1->getIstAmZug())
    {
        sp2->setIstAmZug(false);
        aktuellerSpieler = sp1;
    }
    else
    {
        sp2->setIstAmZug(true);
        aktuellerSpieler = sp2;
    }

    std::cout << "System ready!!!" << endl;
    std::cout << *sp1 << endl;
    std::cout << *sp2 << endl;


    //hier signal start...
    StartGameSignal();
}

int NetzwerkSpiel::naechsterZug(Spieler *spieler, unsigned short spalte)
{
    int rslt = Spiel::naechsterZug(spieler,spalte);
    tcpClient->sendMove(spalte);
    return rslt;
}

void NetzwerkSpiel::aufgeben()
{
    tcpClient->sendGiveUp();
}

void NetzwerkSpiel::on_loginRequest(string loginPlayerName)
{
    cout << "Incoming to on_loginRequest() VALUE: " << loginPlayerName << endl;
    starteSpiel(nameSpieler1,loginPlayerName,false,false);
    this->remoteSpieler = sp1;
    this->tcpClient->sendLoginReply(sp1);

    //hier starte spiel...
    StartGameSignal();
}

void NetzwerkSpiel::on_loginReply(Spieler spieler)
{
    cout << "Incoming to on_loginReply() VALUE: " << spieler << endl;
    rueckgabeSpielerInfo(spieler);
}

void NetzwerkSpiel::on_remoteMove(unsigned short column)
{
    cout << "Incoming to on_remoteMove() VALUE: " << column << endl;
    int rslt = Spiel::naechsterZug(aktuellerSpieler,column);
    RemoteMoveSignal(column,rslt);
}

void NetzwerkSpiel::on_giveUp()
{
    cout << "Incoming to on_giveUp()" << endl;

    GiveUpRemotePlayerSignal(remoteSpieler,false);
}

void NetzwerkSpiel::on_helloReply(HelloReply reply)
{
    cout << "Incoming to on_helloReply() VALUE: " << reply << endl;
    HelloReplySignal(reply);
}

void NetzwerkSpiel::on_udpHello(string remoteIp)
{
    cout << "Incoming to on_udpHello() VALUE: " << remoteIp << endl;
    HelloReply helloReply("",sp1->getName(),this->spielfeld->getZeilen(),this->spielfeld->getSpalten());
    tcpClient->sendHelloReply(remoteIp,&helloReply);
}

void NetzwerkSpiel::sendHello()
{
    tcpClient->sendHelloBroadcast();
}


