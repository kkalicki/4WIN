/*
 * Spiel.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/Spiel.h"
#include <sstream>

Spiel::Spiel() {
	spf = erstelleSpielfeld(0,0);
}

Spiel::Spiel(int ki) {
	spf = erstelleSpielfeld(0,0);
}

void Spiel::werfeStein(int sp) {
	int spalte;

	cout << "Spalte: ";
	cin >> spalte;
	if (spalte > 0 && spalte <= X){
		int aktuell = spf.getSpalteSteine(spalte-1);
		if (aktuell < Y){
			spf.setFeldPos(spalte-1,aktuell,sp);
		}
		else
			cout << "!!!!    Spalte voll    !!!!\n";
	}
	else
		cout << "!!!!    Fehlerhafte Eingabe    !!!!\n";

}

Spiel::~Spiel() {
	//delete spf;
}


void Spiel::startKI(int ki) {
}

void Spiel::startMP() {
	do{
		cout << spf;
		this->werfeStein(0);
	}while(1);

}

string Spiel::toString() const{
	ostringstream out;
	out << spf.toString();

	return out.str();
}

Spielfeld Spiel::erstelleSpielfeld(int x, int y) {
	Spielfeld feld;
	return feld;

}
