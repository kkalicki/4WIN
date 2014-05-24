/*
 * Spiel.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/sys/Spiel.h"
#include "../h/sys/FourWinExceptions.h"
#include <stdlib.h>
#include <sstream>

/*
 * Kommentare/Aenderungen:
 * - Funktion werfeStein(): keine Ein- und Ausgaben innerhalb der Logikklassen. Alles muss von der Menuestruktur bedient werden,
 *   sonst besteht keine Chance mit der GUI an die Informationen zu kommen.
 * - Funktion starteSpiel(), s.o.
 * - Klasse Spieler bekommt Attribut INT FARBE;
 * - Klasse spieler bekommt Attribut BOOL istAmZug;
 * - Parameter werfeStein(): Spieler sp (ok), int farbe (unnötig, da ueber spieler die Farbe gefunden werden kann), int spalte RETURN int row
 * - Funktion Spielrunde wird erstmal auf Eis gelegt: Ablauf der Routinen: Menue bedient --> Spiel erfüllt, gibt zurück --> Menue bedient wieder --> Spiel erfüllt, gibt zurüeck usw...
 *   (der Schlenker geht immer nach aussen in die Menuestruktur, da nur hier auch von der GUI eingegriffen werden kann)
 * - Alle Pruef- und Checkroutinen --> OK! (Müsste so auch weiterhin Funktionieren)
 * - Funktion erstelleSpielfeld() mit Variablen x,y --> OK!
 * - Spiel bekommt ein neues Attribut SPIELER aktuellerSpieler;
 * - Spiel erhaelt funktion wechselSpieler() --> wechselt nach jedem Ordnungsgemäßen Zug aktuellerSpieler auf den jeweilig anderen; switched das Attribut istAmZug an den Spielern um
 * - Funktion werfeStein() in Klasse Spielfeld; Pruef und CheckRoutinen in eigene Klasse auslagern bzw. in Spielfeld implementieren (Interfaces->Reinreelefunktionen: ILogik4WinSpielfeld)
 * - kein Attribut Spielfeld mehr am Spiel, sondern nur noch ein Objekt des Interfaces ILogik4WinSpielfeld (hierdurch abstrahiert und austauschbar...)
 * - eigentliche KI-Logik als Objekt an Spielfeld --> erster Step --> zweiter Stepp evtl. vererbungshirarchie über ILogik4WinSpielfeld oder direkt an Spielfeld implementieren (erst Überblick der bis dahin implementierten Stuktur schaffen --> Klassendiagramm spätestens jetzt bis zum aktuellen Stand vervollständigen)
 * - Testen mit Menuestruktur... Wenn ein Spiel nur mit Ein- und Ausgaben der Menüstruktur bedienbar ist --> Menuestrukur ersetzen durch GUI!
 *
 *
 *TODO: return von werfeStein() ist spalten und nicht row
 *      werte > spalte --> Programmabsturtz
 *      dynamisches Spielfeld erzeugt sich nicht korrekt
 *      wurf in letzte spalte --> !!!!!!nach dynamischer Objektreferzierung nicht mehr vorgekommen!
 *      Auswertung, ob gewonnen greift nicht
 *      Testen, Testen, Testen....
 *      Klasse history anlegen
 *      Klasse transportItem anlegen (netzwerk)
 *
 */

Spiel::Spiel(unsigned short zeilen, unsigned short spalten)
{
    this->spielfeld = new Spielfeld(zeilen,spalten);
    this->runde = 0;
}

Spiel::~Spiel() {

    delete spielfeld;
    delete sp1;
    delete sp2;
    delete &aktuellerSpieler; //<-- ist unoetig da nicht mit new erzeugt!
}


void Spiel::startMP(string nameSpieler1, string nameSpieler2)
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


int Spiel::naechsterZug(Spieler spieler, int spalte)
{
    int rslt = spielfeld->werfeStein(spieler,spalte);
    if(rslt > -1){ //sonst kann nur -1 kommen, dann isses Spiel eh rum oder ne Exception, dann throwt der automatisch nach aussen....
        runde++;
        wechselSpieler();

        //hier werden alle Events gefeuert die bei einem Spielerwechsel erforderlich sind... bspweise: broadcast füer zuschauen mit den daten, die wir noch nicht haben :-D
        //Funktion postExecute() anlegen
        //..
        //..
    }

    return rslt;
}

void Spiel::wechselSpieler()
{
    if(sp1->getIstAmZug()){
        sp1->setIstAmZug(false);
        sp2->setIstAmZug(true);
        aktuellerSpieler = *sp2;
    }
    else{
        sp2->setIstAmZug(false);
        sp1->setIstAmZug(true);
        aktuellerSpieler = *sp1;
    }
}

ostream& operator<<(ostream& out, Spiel& sp){
    out << sp.toString();
    return out;
}

string Spiel::toString() const{

    ostringstream out;
    out << *sp1 << endl;
    out << *sp2 << endl;
    out << "Runde : " << runde << endl;
    out << *spielfeld << endl;
    return out.str();
}


