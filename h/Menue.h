/*
 * Menue.h
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#ifndef MENUE_H_
#define MENUE_H_
#include <string>
#include "../h/Konstanten.h"
#include "../h/Spiel.h"
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
	void sofortspielen();

	/**
	 * startet ein Spiel im Mehrspieler Modus
	 */
	void mehrspieler();

	virtual ~Menue();
private:
	/**
	 * Instanz des Spiels
	 */
	Spiel spiel;
};

#endif /* MENUE_H_ */
