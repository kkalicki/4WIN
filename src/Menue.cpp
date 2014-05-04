/*
 * Menue.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/Menue.h"
#include <sstream>

Menue::Menue() {

}

string Menue::menue() const {
	return "[1] - Sofort Spielen(KI)\n[2] - Mehrspieler\n[0] - Beenden\n";
}

void Menue::start() {
	int auswahl;
	cout << "!!!!    4 GEWINNT    !!!!\n";
	do{
		cout << menue();
		cin >> auswahl;
		menueauswahl(auswahl);
	}while (auswahl != 0);
}

void Menue::menueauswahl(int auswahl) {
	switch(auswahl){
	case 1:
		sofortspielen();
		break;
	case 2:
		mehrspieler();
		break;
	case 0:
		break;
	default:
		cout << "Fehlerhafte Eingaben\n";
	}

}

void Menue::sofortspielen() {
	// spiel.startKI();
}

void Menue::mehrspieler() {
	spiel.startMP();
}

Menue::~Menue() {
	// TODO Auto-generated destructor stub
}
