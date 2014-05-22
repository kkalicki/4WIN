/*
 * Menue.h
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#ifndef MENUE_H_
#define MENUE_H_
#include <string>
#include "../h/sys/Konstanten.h"
#include "../h/sys/Spiel.h"
#include <iostream>

using namespace std;

class Menue {
public:

	/**
	 * Standardkonstruktor
	 */
	Menue();

	/**
	 * Gibt ein Menue als string zurueck
	 * @return string mit dem menue
	 */
	string menue()const;

	/**
	 * Funktion die das Menue startet und die auswahl auswertet;
	 */
	void start();

	/**
	 * startet die Funktionen die im Menue ausgewaehlt wurden
	 * @param auswahl Welcher Funktion genutzt werden sol
	 */
	void menueauswahl(int auswahl);

	/**
	 * startet ein Spiel mit einer KI
	 */
	void sofortspielen(string name1);

	/**
	 * startet ein Spiel im Mehrspieler Modus
	 */
	void mehrspieler(string name1,string name2);

	virtual ~Menue();
private:
	/**
	 * Instanz des Spiels
	 */
    Spiel spiel;
};

#endif /* MENUE_H_ */
