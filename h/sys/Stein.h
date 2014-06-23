/*
 * Stein.h
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#ifndef STEIN_H_
#define STEIN_H_
#include <string>
#include "../h/sys/Konstanten.h"
#include <iostream>

using namespace std;

class Stein {
public:
	/**
	 * Standardkonstruktor
	 */
	Stein();

	Stein(const Stein& rhs);
	/**
	 * Konstruktor zum erstellen eines Steins
	 * @param farbe Entweder ROT oder GELB(Konstanten)
	 */
	Stein(short int farbe, short int x, short int y);



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

	Stein& operator= (Stein const& rhs);


	friend bool operator==(Stein const& lhs, short int const& rhs){
        return (&lhs.farbe == &rhs);
	}
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
		//if ((farbe == GELB) || (farbe == ROT))
		this->farbe = farbe;
	}

	void setPos(int x, int y) {
		pos[0] = x;
		pos[1] = y;
	}

	const short int* getPos() const {
		return pos;
	}

    int getWert() const;
    void setWert(int value);

private:

    /**
     * Farbe des Spielsteins, entweder ROT oder GELB (Konstanten)
	 */
	short int farbe;
	short int pos[2];
    int wert;

};


#endif /* STEIN_H_ */
