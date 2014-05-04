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
	 * Überladung des << Operators für toString-Methode
	 * @param out Variable des Outstreams
	 * @param spf Variable der Klasse Spielfeld
	 * @return manipulierter outstream
	 */
	friend ostream& operator<<(ostream& out, Spielfeld& spf);

	virtual ~Spielfeld();

	/**
	 * gibt das komplette Feld zurück
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



private:
	/**
	 * das Spielfeld als mehrdimensionales Array
	 */
	int feld[Y][X];
};

#endif /* SPIELFELD_H_ */
