/*
 * Spiel.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/sys/Spiel.h"
#include "../h/sys/FourWinExceptions.h"
#include <stdlib.h>
#include <sstream>

/*
 * Kommentare/Aenderungen:
 * - Funktion werfeStein(): keine Ein- und Ausgaben innerhalb der Logikklassen. Alles muss von der Menuestruktur bedient werden,
 *   sonst besteht keine Chance mit der GUI an die Informationen zu kommen.
 * - Funktion starteSpiel(), s.o.
 * - Klasse Spieler bekommt Attribut INT FARBE;
 * - Klasse spieler bekommt Attribut BOOL istAmZug;
 * - Parameter werfeStein(): Spieler sp (ok), int farbe (unnötig, da ueber spieler die Farbe gefunden werden kann), int spalte RETURN int row
 * - Funktion Spielrunde wird erstmal auf Eis gelegt: Ablauf der Routinen: Menue bedient --> Spiel erfüllt, gibt zurück --> Menue bedient wieder --> Spiel erfüllt, gibt zurüeck usw...
 *   (der Schlenker geht immer nach aussen in die Menuestruktur, da nur hier auch von der GUI eingegriffen werden kann)
 * - Alle Pruef- und Checkroutinen --> OK! (Müsste so auch weiterhin Funktionieren)
 * - Funktion erstelleSpielfeld() mit Variablen x,y --> OK!
 * - Spiel bekommt ein neues Attribut SPIELER aktuellerSpieler;
 * - Spiel erhaelt funktion wechselSpieler() --> wechselt nach jedem Ordnungsgemäßen Zug aktuellerSpieler auf den jeweilig anderen; switched das Attribut istAmZug an den Spielern um
 * - Funktion werfeStein() in Klasse Spielfeld; Pruef und CheckRoutinen in eigene Klasse auslagern bzw. in Spielfeld implementieren (Interfaces->Reinreelefunktionen: ILogik4WinSpielfeld)
 * - kein Attribut Spielfeld mehr am Spiel, sondern nur noch ein Objekt des Interfaces ILogik4WinSpielfeld (hierdurch abstrahiert und austauschbar...)
 * - eigentliche KI-Logik als Objekt an Spielfeld --> erster Step --> zweiter Stepp evtl. vererbungshirarchie über ILogik4WinSpielfeld oder direkt an Spielfeld implementieren (erst Überblick der bis dahin implementierten Stuktur schaffen --> Klassendiagramm spätestens jetzt bis zum aktuellen Stand vervollständigen)
 * - Testen mit Menuestruktur... Wenn ein Spiel nur mit Ein- und Ausgaben der Menüstruktur bedienbar ist --> Menuestrukur ersetzen durch GUI!
 */


Spiel::Spiel()
{

}

Spiel::~Spiel() {

    if(spielfeld != 0)
        delete spielfeld;
}

void Spiel::erstelleSpielfeld(unsigned short zeilen, unsigned short spalten) {
    this->spielfeld = new Spielfeld(zeilen,spalten);
}


int Spiel::naechsterZug(Spieler spieler, int spalte)
{
    if(spielfeld == 0)
    {
        // -->RuntimeException, sollte eigentlich von RuntimeException abgeleitet werden.. //TODO String in Konstante
        throw SpielFeldException("Spielfeld ist nit initialisiert -> erst Funktion erstelleSpielfeld() aufrufen!");
    }

    int rslt = spielfeld->werfeStein(spieler,spalte);
    if(rslt > -1)            //sonst kann nur -1 kommen, dann isses Spiel eh rum oder ne Exception, dann throwt der automatisch nach aussen....
        wechselSpieler();

    return rslt;
}



void Spiel::wechselSpieler()
{
    runde++;

    //spieler wechsel... zuweisungen, instanzuebergabe an aktuellen spieler, bool switchen , blaa blubb...

    //hier werden alle Events gefeuert die bei einem Spielerwechsel erforderlich sind... bspweise: broadcast füer zuschauen mit den daten, die wir noch nicht haben :-D
    //...
    //..
    //..
}

string Spiel::toString() const{

    //ein aufruf nach jeder runde von aussen und alles wird auf einmal ausgegeben....
    //beide Spieler toString()
    //rounde toString()

    ostringstream out;
    out << spielfeld->toString();

    return out.str();
}


//------------------------------------------KOMMT WEG--------------------------------------
/*
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
*/

/*
void Spiel::startKI(int ki) {
}
*/


/*
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
*/


