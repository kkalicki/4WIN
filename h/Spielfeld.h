/*
 * Spielfeld.h
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#ifndef SPIELFELD_H_
#define SPIELFELD_H_
#include <string>
#include "../h/Konstanten.h"
#include <iostream>

using namespace std;

class Spielfeld {
public:
	/**
	 * Standardkonstruktor
	 */
	Spielfeld();

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
	const int* getFeld() const {
		return *feld;
	}
	/**
	 * gibt den wert an der gefragten Stelle
	 * @param x Wert der x-Achse
	 * @param y Wert der y-Achse
	 * @return
	 */
	int getFeldPos(int x, int y) const {
		return feld[y][x];
	}

	/**
	 * setzt einen Stein in das Feld
	 * @param x wert der x-Achse
	 * @param y Wert der y-Achse
	 * @param wert Wert der gesetzt wird
	 */
	void setFeldPos(int x, int y, int wert) {
		feld[y][x] = wert;
		aktuell[x]++;
	}

	/**
	 * Gibt Anzahl der schon gelegten Steine in einer Spalte zurueck
	 * @param x gibt an welche Spalte gemeint ist
	 * @return gibt die Anzahl der Steine in der Spalte zurueck
	 */
	int getSpalteSteine(int x) const{
		return aktuell[x];
	}



private:
	/**
	 * das Spielfeld als mehrdimensionales Array
	 */
	int feld[Y][X];
	int aktuell[X];
};

#endif /* SPIELFELD_H_ */
