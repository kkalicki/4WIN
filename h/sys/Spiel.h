/*
 * Spiel.h
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#ifndef SPIEL_H_
#define SPIEL_H_
#include <string>
#include "../h/sys/Konstanten.h"
#include "../h/sys/Spielfeld.h"
#include "../h/sys/Historie.h"
#include <iostream>


class Spiel {
public:
    Spiel(unsigned short zeilen=Y, unsigned short spalten=X);
    virtual ~Spiel();

	/**
	 * startet ein Spiel mit der ausgewaehlten KI
	 * @param ki wert zur Auswahl der KI
	 */
    //void startKI(int ki);

	/**
	 * startet ein Spiel gegen einen anderen Spieler, und erstellt die Spieler
	 * @param name1 Name des ersten Spielers
	 * @param name2 Name des zweiten Spielers
	 */
    void startMP(string nameSpieler1, string nameSpieler2);
    int naechsterZug(Spieler spieler, int spalte);
    void aufgeben();
    void erstelleNeuenHisEintrag(Spieler spieler, unsigned short zeile, unsigned short spalte, unsigned short runde);

	/**
	 * Methode zur Ausgabe des Spiels
	 * @return gibt die das Spiel mit Spielfeld aus
	 */
	string toString() const;

	/**
	 * Erstellt ein Spielfeld
	 * @param x wert der x-Achse
	 * @param y Wert der y-Achse
	 * @return gibt ein komplettes Spielfeld zurueck
	 */
    //Spielfeld erstelleSpielfeld(int x, int y);

	/**
	 * Funktion die ein stein fuer einen bestimmten Spieler ins Spielfeld wirft
	 * @param sp variable fuer den Spieler
	 * @return pruefzahl ob stein gelegt wurde
	 */
    //int werfeStein(Spieler sp, int farbe);

    //int pruefeStein(int farbe, int spalte);

    //int checkHorizontal(int farbe, int spalte);
    //int checkVertikal(int farbe, int spalte);
    //int checkDiagonal(int farbe, int spalte);



    //int spielrunde(Spieler sp1, Spieler sp2);
    //void erstelleSpielfeld(unsigned short zeilen=Y, unsigned short spalten=X);


	/**
	 * Ueberladung des << Operators fuer toString-Methode
	 * @param out Variable des Outstreams
	 * @param sp Variable der Klasse Spiel
	 * @return manipulierter outstream
	 */
    friend ostream& operator<<(ostream& out, Spiel& sp);

    Spieler getAktuellerSpieler() const{
        return aktuellerSpieler;
    }

    Spieler getSp1() const{
        return sp1;
    }

    void setSp1(const Spieler &value){
        sp1 = value;
    }

    Spieler getSp2() const{
        return sp2;
    }

    void setSp2(const Spieler &value){
        sp2 = value;
    }

    unsigned short getRunde() const{
        return runde;
    }

    void setRunde(unsigned short value){
        runde = value;
    }

private:
    Spielfeld *spielfeld;
    Historie *historie;
    Spieler sp1;
    Spieler sp2;
    Spieler aktuellerSpieler;
    unsigned short runde;
    void wechselSpieler();
};

#endif /* SPIEL_H_ */
