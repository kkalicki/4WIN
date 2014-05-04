/*
 * Stein.h
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#ifndef STEIN_H_
#define STEIN_H_
#include <string>
#include "../h/Konstanten.h"
#include <iostream>

using namespace std;

class Stein {
public:
	/**
	 * Standardkonstruktor
	 */
	Stein();
	/**
	 * Konstruktor zum erstellen eines Steins
	 * @param farbe Entweder ROT oder GELB(Konstanten)
	 */
	Stein(short int farbe);



	virtual ~Stein();

	/**
	 * Gibt die Farbe eines Steines aus
	 * @return string Farbe des Steines
	 */
	string toString() const;

	/**
	 * Ueberladung des << Operators fuer toString-Methode
	 * @param out Variable des Outstreams
	 * @param st Variable der Klasse Stein
	 * @return manipulierter outstream
	 */
	friend ostream& operator<<(ostream& out, Stein& st);

	/**
	 * Ueberladung des >> Operators
	 * @param in Variable des Instreams
	 * @param st Variable der Klasse Stein
	 * @return manipulierter instream
	 */
	friend istream& operator>>(istream& in, Stein& st);


	/**
	 * Uebergibt den Wert des Steines
	 * @return short int farbe (ROT oder GELB)
	 */
	short int getFarbe() const {
		return farbe;
	}

	/**
	 * Setzt die Farbe eines Steines entweder auf ROT oder GELB
	 * @param farbe Farbe des Steines
	 */
	void setFarbe(short int farbe) {
		if ((farbe == GELB) || (farbe == ROT))
			this->farbe = farbe;
	}

private:

	/**
	 * Farbe des Spielsteins, entweder ROT oder GELB (Konstanten)
	 */
	short int farbe;
};


#endif /* STEIN_H_ */
