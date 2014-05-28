
#include "../h/sys/NetzwerkSpiel.h"


NetzwerkSpiel::NetzwerkSpiel(unsigned short zeilen, unsigned short spalten) : Spiel(zeilen,spalten)
{
    this->tcpserver = new TcpServer();
}

NetzwerkSpiel::~NetzwerkSpiel()
{
   // tcpserver.close();
    delete tcpserver;
}

void NetzwerkSpiel::starteNetzwerkSpiel(string spielerName)
{
    this->sp1 = new Spieler(spielerName);

    //warte bis spieler sich anmeldet...

    //dann...rueckgabe eigene Spielerinfo
    rueckgabeSpielerInfo(sp1);
}

void NetzwerkSpiel::anmeldenNetzwerk(string nameSpieler2)
{
    this->sp2 = new Spieler(nameSpieler2);

    //warten auf rueckgabe vom Server

    //wenn rueckgabe da ist, dann werte aus wer an der reihe ist
    if(sp1->getFarbe() == aktuellerSpieler->getFarbe())
    {
        //der andere faengt an... ich warte bis nachricht mit seinem zug rein kommt und setzte
    }
}

void NetzwerkSpiel::rueckgabeSpielerInfo(Spieler *spieler)
{
    //sende spieler heraus....
}

void NetzwerkSpiel::abmeldenNetzwerk()
{
    //Blaa Blaa Blubb....
}

/*
void NetzwerkSpiel::on_loginReply(Spieler *player)
{

}

void NetzwerkSpiel::on_loginRequest(string loginPlayerName)
{

}

void NetzwerkSpiel::on_nextMove(int column)
{

}*/
