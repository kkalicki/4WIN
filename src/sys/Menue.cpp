/*
 * Menue.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/sys/Menue.h"
#include "../h/sys/FourWinExceptions.h"
#include <sstream>

Menue::Menue() {

    this->spiel = 0;
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
        mehrspieler("sp1", "sp2");
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

    erstelleSpiel();
    cout<< "********STARTE SPIEL**********" << endl;
    spiel->starteSpiel(name1, name2,false,false);

    cout<<"Spieler " << spiel->getAktuellerSpieler()->getName()
                     << "[" << (spiel->getAktuellerSpieler()->getFarbe() == ROT ? "ROT" : "GELB")
                     <<"] faengt an!" << endl << endl;


    cout << *spiel << flush;

    int spalte, ende = 0;
    do{
        try{
            cout<<"Spalte eingeben!" << endl;
            cin >> spalte;
            ende = spiel->naechsterZug(spiel->getAktuellerSpieler(),spalte);
            if(ende == -1){
                cout << "GEWONNEN (YEAHHH!)" << endl;
            }
            cout << *spiel << endl;
            cout <<"ROW: " << ende << endl;
        }catch(EingabeException& e){
            cout << e.what() << endl;
        }catch(SpielFeldException& e){
            cout << e.what() << endl;
        }
    }while(ende != -1);
    clear();
}

void Menue::erstelleSpiel()
{
    int zeilen, spalten;

    cout<<"Anzahl Zeilen: " << endl;
    cin >> zeilen;

    cout<<"Anzahl Spalten: "<< endl;
    cin >> spalten;

    //erstelle Spiel
    this->spiel = new Spiel(zeilen, spalten);
}

void Menue::clear()
{
    if(spiel != 0)
        delete spiel;

    this->spiel = 0;
}

Menue::~Menue() {
	// TODO Auto-generated destructor stub
}
