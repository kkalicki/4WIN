/*
 * Spiel.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/sys/Spiel.h"
#include "../h/sys/FourWinExceptions.h"
#include "../h/sys/HisEintrag.h"
#include <stdlib.h>
#include <sstream>



Spiel::Spiel(unsigned short zeilen, unsigned short spalten)
{
    this->historie = new Historie();
    this->spielfeld = new Spielfeld(zeilen,spalten);
    this->runde = 1;
    this->aktuellerSpieler = 0;
    this->sp1 = 0;
    this->sp2 = 0;
}

Spiel::~Spiel() {

    delete spielfeld;

    if(sp1 != 0)
        delete sp1;
    if(sp2 != 0)
        delete sp2;

    delete historie;
}


void Spiel::starteSpiel(string nameSpieler1, string nameSpieler2)
{
    this->sp1 = new Spieler(nameSpieler1);
    this->sp2 = new Spieler(nameSpieler2);

    time_t t;
    time(&t);
    srand((unsigned int)t);

    //auslosen wer ROT und wer Gelb ist
    if((rand() % 2) == 0){
        sp1->setFarbe(ROT);
        sp2->setFarbe(GELB);
    }
    else{
        sp1->setFarbe(GELB);
        sp2->setFarbe(ROT);
    }

    //Auslosen wer anfaengt
    if((rand() % 2) == 0){
        sp1->setIstAmZug(false);
    }
    else{
         sp1->setIstAmZug(true);
    }
    wechselSpieler();
}

void Spiel::aufgeben() //braucht evtl. noch Parameter...
{
    //implementieren...
}

void Spiel::erstelleNeuenHisEintrag(Spieler* spieler, unsigned short zeile, unsigned short spalte, unsigned short runde)
{
    HisEintrag* neuerEintrag = new HisEintrag(spieler,zeile,spalte,runde);
    historie->hinzufuegenEintrag(neuerEintrag);
}

int Spiel::naechsterZug(Spieler* spieler, unsigned short spalte)
{
    int rslt = spielfeld->werfeStein(spieler,spalte);
    if(rslt > -1){
        erstelleNeuenHisEintrag(getAktuellerSpieler(),rslt,spalte,runde);
        wechselSpieler();
        runde++;
    }else if(rslt == -1){
        //letzter Zug soll noch Eingetragen werden...
        erstelleNeuenHisEintrag(getAktuellerSpieler(),rslt,spalte,runde);
    }
    return rslt;
}

void Spiel::wechselSpieler()
{
    this->vorherigerSpieler = aktuellerSpieler;
    if(sp1->getIstAmZug()){
        sp1->setIstAmZug(false);
        sp2->setIstAmZug(true);
        aktuellerSpieler = sp2;
    }
    else{
        sp2->setIstAmZug(false);
        sp1->setIstAmZug(true);
        aktuellerSpieler = sp1;
    }
}

ostream& operator<<(ostream& out, Spiel& sp){
    out << sp.toString();
    return out;
}

string Spiel::toString() const{

    ostringstream out;
    out << sp1->toString() << endl; //nur spieler shiften...nix toString()
    out << sp2->toString() << endl;
    out << "Runde : " << runde << endl;
    out << *spielfeld << endl;
    out << historie->toString() << endl;
    return out.str();
}




