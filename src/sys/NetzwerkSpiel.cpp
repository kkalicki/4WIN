
#include "../h/sys/NetzwerkSpiel.h"
#include "../h/net/tcpclient.h"
#include "../h/net/tcpserver.h"
#include "../h/net/udpserver.h"
#include "boost/bind.hpp"
#include "iostream"

NetzwerkSpiel::NetzwerkSpiel(unsigned short zeilen, unsigned short spalten) : Spiel(zeilen,spalten)
{
    this->tcpClient = new TcpClient();
    this->tcpServer = 0;
    this->udpServer = 0;
}

NetzwerkSpiel::~NetzwerkSpiel()
{
    std::cout << "schließe Netzwerkspiel!!!" << endl;
    stopTcpServer();
    stopUdpServer();
    delete tcpClient;
    tcpClient=0;
    std::cout << "Netzwerkspiel geschlossen!!!" << endl;
}

void NetzwerkSpiel::startTcpServer()
{
    this->tcpServer = new TcpServer();
    dynamic_cast<TcpServer*>(tcpServer)->LoginRequestSignal.connect(boost::bind(&NetzwerkSpiel::on_loginRequest, this,_1,_2));
    dynamic_cast<TcpServer*>(tcpServer)->LoginReplySignal.connect(boost::bind(&NetzwerkSpiel::on_loginReply, this,_1));
    dynamic_cast<TcpServer*>(tcpServer)->RemoteMoveSignal.connect(boost::bind(&NetzwerkSpiel::on_remoteMove, this,_1));
    dynamic_cast<TcpServer*>(tcpServer)->GiveUpSignal.connect(boost::bind(&NetzwerkSpiel::on_giveUp, this));
    //dynamic_cast<TcpServer*>(tcpServer)->HelloReplySignal.connect(boost::bind(&NetzwerkSpiel::on_helloReply, this,_1));
    tcpServer->start();

}

void NetzwerkSpiel::stopTcpServer()
{
    if(tcpServer != 0){
        dynamic_cast<TcpServer*>(tcpServer)->LoginRequestSignal.disconnect(&NetzwerkSpiel::on_loginRequest);
        dynamic_cast<TcpServer*>(tcpServer)->LoginReplySignal.disconnect(&NetzwerkSpiel::on_loginReply);
        dynamic_cast<TcpServer*>(tcpServer)->RemoteMoveSignal.disconnect(&NetzwerkSpiel::on_remoteMove);
        dynamic_cast<TcpServer*>(tcpServer)->GiveUpSignal.disconnect(&NetzwerkSpiel::on_giveUp);

        if(tcpServer->getIsActive())
            tcpServer->stop();

         delete tcpServer;
        tcpServer = 0;
    }
}

void NetzwerkSpiel::startUdpServer()
{
    this->udpServer = new UdpServer();
    dynamic_cast<UdpServer*>(udpServer)->UdpHelloSignal.connect(boost::bind(&NetzwerkSpiel::on_udpHello, this,_1));
    dynamic_cast<UdpServer*>(udpServer)->VisitorPackageSignal.connect(boost::bind(&NetzwerkSpiel::on_visitorPackage, this,_1));
    udpServer->start();
}

void NetzwerkSpiel::stopUdpServer()
{
    if(udpServer != 0){
        dynamic_cast<UdpServer*>(udpServer)->UdpHelloSignal.disconnect(&NetzwerkSpiel::on_udpHello);
        dynamic_cast<UdpServer*>(udpServer)->VisitorPackageSignal.disconnect(&NetzwerkSpiel::on_visitorPackage);

        if(udpServer->getIsActive())
           udpServer->stop();

        delete udpServer;
        udpServer = 0;
    }
}

void NetzwerkSpiel::starteNetzwerkSpiel(string spielerName)
{
   cout << "starte Netzwerkspiel..."<< endl;
   this->nameSpieler1 = spielerName;
   this->visitorMode = false;
   startTcpServer();
   startUdpServer();
}

void NetzwerkSpiel::anmeldenNetzwerk(string nameSpieler2,int gameId, bool visitorMode)
{
    this->id = gameId;
    this->visitorMode = visitorMode;
    if(!visitorMode){
        startTcpServer();
        this->sp2 = new Spieler(nameSpieler2);
        this->remoteSpieler = sp2;
        cout << "melde an..."<< endl;
        tcpClient->sendLoginRequest(nameSpieler2);
    }
    else{
         startUdpServer();
    }
}

void NetzwerkSpiel::startClient(string ip)
{
    tcpClient->setIpAddress(ip);
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
    this->visitorSp1 = *sp1;
    this->visitorSp2 = *sp2;

    //hier signal start...
    StartGameSignal();
}

int NetzwerkSpiel::naechsterZug(Spieler *spieler, unsigned short spalte)
{
    int rslt = Spiel::naechsterZug(spieler,spalte);
    tcpClient->sendMove(spalte);

    VisitorPackage vp(&visitorSp1,&visitorSp2,historie,id);
    tcpClient->sendVisitorPackageBroadcast(&vp);
    return rslt;
}

void NetzwerkSpiel::aufgeben()
{
    tcpClient->sendGiveUp();
}

void NetzwerkSpiel::beenden()
{
    Spiel::beenden();
    stopTcpServer();
    stopUdpServer();
}

void NetzwerkSpiel::on_loginRequest(string loginPlayerName, string ip)
{
    cout << "Incoming to on_loginRequest() VALUE: " << loginPlayerName << endl;
    starteSpiel(nameSpieler1,loginPlayerName,false,false);
    this->remoteSpieler = sp1;
    tcpClient->setIpAddress(ip);
    this->tcpClient->sendLoginReply(sp1);

    this->visitorSp1 = *sp1;
    this->visitorSp2 = *sp2;
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

void NetzwerkSpiel::on_visitorPackage(VisitorPackage vp)
{
    cout << "Incoming to on_visitorPackage VALUE: " << vp << endl;

    if(sp1 == 0){
         sp1 = new Spieler(vp.getSp1());
         sp2 = new Spieler(vp.getSp2());
         if(sp1->getIstAmZug()){
            aktuellerSpieler = sp1;
         }else{
             aktuellerSpieler = sp2;
         }
         StartGameSignal();
    }

    if(visitorMode){
        //pruefe ID obs die richtige ist...
        if(vp.getGameId() == id){
            int lastround  = 0;
            if(this->getHistorie()->getHisList()->size() > 0){
                lastround = this->getHistorie()->getLetztenEintrag()->getRunde();
            }
            VisitorPackageSignal(vp,lastround);
        }
    }
}

void NetzwerkSpiel::on_udpHello(string remoteIp)
{
    cout << "Incoming to on_udpHello() VALUE: " << remoteIp << endl;
    int isAct=0;
    if(istAktiv)
        isAct=1;

    HelloReply helloReply("",this->nameSpieler1,this->spielfeld->getZeilen(),this->spielfeld->getSpalten(),isAct, this->id);
    if(!remoteIp.empty())
        tcpClient->sendHelloReply(remoteIp,&helloReply);
}

void NetzwerkSpiel::sendHello()
{
    tcpClient->sendHelloBroadcast();
}



