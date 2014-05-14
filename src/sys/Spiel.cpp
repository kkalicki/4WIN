/*
 * Spiel.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/sys/Spiel.h"
#include <stdlib.h>
#include <sstream>

Spiel::Spiel() {
	spf = erstelleSpielfeld(0,0);
	runde = 1;
}

Spiel::Spiel(int ki) {
	spf = erstelleSpielfeld(0,0);
	runde = 1;
}

//TODO Farbe abfangen;
int Spiel::werfeStein(Spieler sp, int farbe) {
	int spalte;

	cout << spf;
	cout << "Runde: " << this->runde << "\n";
	string name = sp.getName();
	(farbe == ROT ) ? cout << "Spieler 1 (ROT) = " << name : cout << "Spieler 2 (GELB) = " << name;
	cout << "\n";
	cout << "Spalte: ";
	cin >> spalte;
	if (spalte > 0 && spalte <= X){
		int aktuell = spf.getSpalteSteine(spalte-1);
		if (aktuell < Y){
			spf.setFeldPos(spalte-1,aktuell,farbe);
			return spalte;
		}
		else
			cout << "!!!!    Spalte voll    !!!!\n";
	}
	else
		cout << "!!!!    Fehlerhafte Eingabe    !!!!\n";


	return werfeStein(sp,farbe);

}

int Spiel::spielrunde(Spieler spieler1, Spieler spieler2) {
	bool check = false;
	int spalte;
	do{
		spalte = werfeStein(spieler1, ROT);
		check = pruefeStein(ROT, spalte);
		if (check == true)
			return ROT;
		spalte = werfeStein(spieler2, GELB);
		check = pruefeStein(GELB, spalte);
		if (check == true)
			return GELB;

		runde++;
	}while(check == false);
	return -1;
}

int Spiel::pruefeStein(int farbe, int spalte) {
	if (checkHorizontal(farbe,spalte) || checkVertikal(farbe,spalte) || checkDiagonal(farbe,spalte))
		return true;
	else
		return false;
}

int Spiel::checkHorizontal(int farbe, int spalte) {
	int wert = (farbe==ROT) ? ROT : GELB;
	int zeile = spf.getSpalteSteine(spalte);


	return false;
}

int Spiel::checkVertikal(int farbe, int spalte) {
	int wert = (farbe==ROT) ? ROT : GELB;
	int zeile = spf.getSpalteSteine(spalte-1);

	Stein aktuell = spf.getFeldPos(zeile, spalte-1);
	const short int *pos = aktuell.getPos();

	cout << "\npos x: " << pos[0]  << " y: " << pos[1] << "\n";
	cout << "CHECK VERTIKAL AKTUELL :" << aktuell << " Zeile: " << zeile  << " Spalte: " << spalte << "\n";
	return false;
}

int Spiel::checkDiagonal(int farbe, int spalte) {
	int wert = (farbe==ROT) ? ROT : GELB;
	for(int i = Y-1; i >= 3;i--){
		for(int j = 0; j < X-3;j++){
			if (spf.getFeldPos(j,i) == wert){
				if (spf.getFeldPos(j+1,i-1) == wert){
					if (spf.getFeldPos(j+2,i-2) == wert){
						if (spf.getFeldPos(j+3,i-3) == wert){
							return true;
						}

					}

				}

			}
		}
	}
	for(int i = Y-1; i >= 3;i--){
		for(int j = 3; j < X;j++){
			if (spf.getFeldPos(j,i) == wert){
				if (spf.getFeldPos(j-1,i-1) == wert){
					if (spf.getFeldPos(j-2,i-2) == wert){
						if (spf.getFeldPos(j-3,i-3) == wert){
							return true;
						}

					}

				}

			}
		}
	}
	return false;
}

Spiel::~Spiel() {
	//delete spf;
}


void Spiel::startKI(int ki) {
}


void Spiel::startMP(string name1,string name2) {
	sp1.setName(name1);
	sp2.setName(name2);
	int zufall = rand() % (2-1);
	int gewinner;
	if (zufall == 0)
		gewinner = spielrunde(sp1,sp2);
	else
		gewinner = spielrunde(sp2,sp1);

	cout << spf;
	if (gewinner == ROT)
		cout << "ROT HAT GEWONNEN\n";
	else
		cout << "GELB HAT GEWONNEN\n";




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
