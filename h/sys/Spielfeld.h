/*
 * Spielfeld.h
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#ifndef SPIELFELD_H_
#define SPIELFELD_H_
#include <string>
#include "../h/sys/Konstanten.h"
#include "../h/sys/Stein.h"
#include "../h/sys/Spieler.h"
#include <iostream>

using namespace std;

class Spielfeld {
public:
	/**
	 * Standardkonstruktor
	 */
    Spielfeld(unsigned short zeilen=Y, unsigned short spalten=X);

	/**
	 * Gibt die Groesse des Feldes als String aus
	 * @return string groesse des Feldes
	 */
	string toString() const;

	/**
	 * Ueberladung des << Operators für toString-Methode
	 * @param out Variable des Outstreams
	 * @param spf Variable der Klasse Spielfeld
	 * @return manipulierter outstream
	 */
	friend ostream& operator<<(ostream& out, Spielfeld& spf);

	virtual ~Spielfeld();

	/**
	 * gibt das komplette Feld zurueck
	 * @return feld komplettes Feld
	 */
	Stein getFeld() {
		return **feld;
	}
	/**
	 * gibt den wert an der gefragten Stelle
	 * @param x Wert der x-Achse
	 * @param y Wert der y-Achse
	 * @return
	 */
	Stein getFeldPos(int x, int y) {
		return feld[y][x];
	}

    int werfeStein(Spieler* spieler, int spalte);

    /**
     * Gibt Anzahl der schon gelegten Steine in einer Spalte zurueck
     * @param x gibt an welche Spalte gemeint ist
     * @return gibt die Anzahl der Steine in der Spalte zurueck
     */
    int getSpalteSteine(int x) const{
        return aktuell[x];
    }

private:

    void init();
    /**
     * setzt einen Stein in das Feld
     * @param x wert der x-Achse
     * @param y Wert der y-Achse
     * @param wert Wert der gesetzt wird
     */
    void setFeldPos(int x, int y, int wert) {
        feld[y][x].setFarbe(wert);
        aktuell[x]++;
    }



    int pruefeStein(int farbe, int spalte);

    int checkHorizontal(int farbe, int spalte);
    int checkVertikal(int farbe, int spalte);
    int checkDiagonal(int farbe, int spalte);

	/**
	 * das Spielfeld als mehrdimensionales Array
	 */
    Stein **feld;
    int *aktuell;
    unsigned short zeilen;
    unsigned short spalten;
};

#endif /* SPIELFELD_H_ */
