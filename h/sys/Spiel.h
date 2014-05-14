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
#include "../h/sys/Spieler.h"
#include <iostream>


class Spiel {
public:
	/**
	 * Standardkonstruktor
	 */
	Spiel();

	/**
	 * Konstruktor mit Auswahl der KI (Schwierigkeitsstufen)
	 * @param Int Wert fuer die Auswahl der KI
	 */
	Spiel(int ki);

	/**
	 * startet ein Spiel mit der ausgewaehlten KI
	 * @param ki wert zur Auswahl der KI
	 */
	void startKI(int ki);

	/**
	 * startet ein Spiel gegen einen anderen Spieler, und erstellt die Spieler
	 * @param name1 Name des ersten Spielers
	 * @param name2 Name des zweiten Spielers
	 */
	void startMP(string name1,string name2);

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
	Spielfeld erstelleSpielfeld(int x, int y);

	/**
	 * Funktion die ein stein fuer einen bestimmten Spieler ins Spielfeld wirft
	 * @param sp variable fuer den Spieler
	 * @return pruefzahl ob stein gelegt wurde
	 */
	int werfeStein(Spieler sp, int farbe);

	int pruefeStein(int farbe, int spalte);

	int checkHorizontal(int farbe, int spalte);
	int checkVertikal(int farbe, int spalte);
	int checkDiagonal(int farbe, int spalte);



	int spielrunde(Spieler sp1, Spieler sp2);

	/**
	 * Ueberladung des << Operators fuer toString-Methode
	 * @param out Variable des Outstreams
	 * @param sp Variable der Klasse Spiel
	 * @return manipulierter outstream
	 */
	friend ostream& operator<<(ostream& out, Spiel& sp){
		out << sp.toString();
		return out;
	}

	virtual ~Spiel();
private:
	Spielfeld spf;
	Spieler sp1;
	Spieler sp2;
//	Spieler ki;
	unsigned short int runde;
};

#endif /* SPIEL_H_ */
