/*
 * Menue.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/sys/Menue.h"
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
	string name1;
	string name2;
	switch(auswahl){
	case 1:
		cout << "Name Spieler 1: ";
		cin >> name1;
		sofortspielen(name1);
		break;
	case 2:
//		cout << "Name Spieler 1: ";
//		cin >> name1;
//		cout << "Name Spieler 2: ";
//		cin >> name2;
		mehrspieler("asdf", "fdas");
		break;
	case 0:
		break;
	default:
		cout << "Fehlerhafte Eingaben\n";
	}

}

void Menue::sofortspielen(string name1) {
	// spiel.startKI();
}

void Menue::mehrspieler(string name1,string name2) {
	spiel.startMP(name1, name2);
}

Menue::~Menue() {
	// TODO Auto-generated destructor stub
}
