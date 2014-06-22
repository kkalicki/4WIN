/*
 * Spiel.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/sys/Spiel.h"
#include "../h/sys/SpielerKI.h"
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
    istAktiv = false;
}

Spiel::~Spiel() {

    delete spielfeld;

    if(sp1 != 0)
        delete sp1;
    if(sp2 != 0)
        delete sp2;

    delete historie;
}


void Spiel::starteSpiel(string nameSpieler1, string nameSpieler2, bool sp1KI, bool sp2KI )
{
    if (sp1KI) {
        this->sp1 = new SpielerKI(nameSpieler1, spielfeld);
        static_cast<SpielerKI*>(sp1)->WerfeSteinSignal.connect(boost::bind(&Spiel::naechsterZugRemote, this,_1));
    }else{
        this->sp1 = new Spieler(nameSpieler1);
    }
    if (sp2KI) {
        this->sp2 = new SpielerKI(nameSpieler2, spielfeld);
        static_cast<SpielerKI*>(sp2)->WerfeSteinSignal.connect(boost::bind(&Spiel::naechsterZugRemote, this,_1));
    }else{
        this->sp2 = new Spieler(nameSpieler2);
    }

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
    istAktiv = true;
}

void Spiel::aufgeben() //braucht evtl. noch Parameter...
{
    beenden();
}

void Spiel::beenden()
{
    istAktiv = false;
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
    if(rslt > WIN){
        erstelleNeuenHisEintrag(getAktuellerSpieler(),getAktuelleZeile(spalte),spalte,runde);
        runde++;
    }else if(rslt == WIN){
        //letzter Zug soll noch Eingetragen werden...
        erstelleNeuenHisEintrag(getAktuellerSpieler(),getAktuelleZeile(spalte),spalte,runde);
    }
   // wechselSpieler();
    return rslt;
}

void Spiel::naechsterZugRemote(int spalte)
{
    int result = this->naechsterZug(this->aktuellerSpieler, spalte);
    RemoteZugSignal(spalte,result);
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
    if (aktuellerSpieler->getIsKI() == true){
        static_cast<SpielerKI*>(aktuellerSpieler)->denken();
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

int Spiel::getAktuelleZeile(int spalte)
{
    return spielfeld->getSpalteSteine(spalte -1);
}




