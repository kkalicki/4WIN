/*
 * Spielfeld.h
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#ifndef SPIELFELD_H_
#define SPIELFELD_H_
#include <string>
#include "../h/sys/Konstanten.h"
#include "../h/sys/Stein.h"
#include "../h/sys/Spieler.h"
#include <iostream>

using namespace std;

/**
 * The Spielfeld class
 * Die Spielfeldklasse Besteht aus einem zweidimensionalen Array des Typs Stein.
 * Spieler werfen Ihre Steine in das Spielfeld. Das Spielfeld besitzt die Spiellogik, Gewinnprüfung und Bewertungsmechanismen.
 */
class Spielfeld {
public:
	/**
	 * Standardkonstruktor
	 */
    Spielfeld(unsigned short zeilen=Y, unsigned short spalten=X, int schwierigkeitsstufe=0);

	/**
	 * Gibt die Groesse des Feldes als String aus
	 * @return string groesse des Feldes
	 */
	string toString() const;

	/**
	 * Ueberladung des << Operators f�r toString-Methode
	 * @param out Variable des Outstreams
	 * @param spf Variable der Klasse Spielfeld
	 * @return manipulierter outstream
	 */
	friend ostream& operator<<(ostream& out, Spielfeld& spf);

	virtual ~Spielfeld();

	/**
	 * gibt das komplette Feld zurueck
	 * @return feld komplettes Feld
	 */
	Stein getFeld() {
		return **feld;
	}
	/**
	 * gibt den wert an der gefragten Stelle
	 * @param x Wert der x-Achse
	 * @param y Wert der y-Achse
	 * @return
	 */
    Stein* getFeldPos(int x, int y) {
        return &feld[y][x];
	}

    int werfeStein(Spieler* spieler, int spalte);

    int werfeTestStein(unsigned short farbe, int spalte);

    /**
     * Gibt Anzahl der schon gelegten Steine in einer Spalte zurueck
     * @param x gibt an welche Spalte gemeint ist
     * @return gibt die Anzahl der Steine in der Spalte zurueck
     */
    int getSpalteSteine(int x) const{
        return aktuell[x];
    }

    /**
     * Getter fuer die Anzahl der Spalten
     * @return
     */
    unsigned short getSpalten() const{
        return this->spalten;
    }

    /**
     * Getter fuer die Anzahl der Zeilen
     * @return
     */
    unsigned short getZeilen() const{
        return this->zeilen;
    }

    /**
     * Loescht einen Stein und zahlt die variable fur die Anzahl der Steine in der Spalte runter
     * @param x
     * @param y
     */
    void loescheStein(int x, int y) {
        feld[y][x].setFarbe(2);
        aktuell[x]--;
    }

    /**
     * Getter fuer den schwierigkeitsgrad
     * @return
     */
    unsigned short getSchwierigkeitsstufe() const;

    /**
     * Setter fuer den Schwierigkeitsgrad
     * @param value
     */
    void setSchwierigkeitsstufe(unsigned short value);

    /**
     * Prueft ob noch Zuege Moeglich sind
     * @return
     */
    bool pruefeSpielfeld();

    /**
     * Prueft ob ob die Farbe gewonnen hat
     * @param farbe
     * @param spalte
     * @return
     */
    int pruefeStein(int farbe);

    /**
     * bewertet das Spielfeld
     * @return
     */
    int bewerteSteine();

    /**
     * bewertet den Stein mit allen umliegenden Richtugen und nachbarn
     * @param x
     * @param y
     * @return
     */
    int bewerteStein(int x, int y);

    /**
     * vergleicht zwei felder miteinander
     * @param farbe
     * @param steinFarbe
     * @return
     */
    int bewerteSteinFarbe(int farbe, int steinFarbe);

    /**
     * prueft alle horizontale verbindungen
     * @param farbe
     * @param spalte
     * @return
     */
    int checkHorizontal(int farbe);

    /**
     * prueft alle vertikale verbindungen
     * @param farbe
     * @param spalte
     * @return
     */
    int checkVertikal(int farbe);

    /**
     * prueft alle diagonale verbindungen
     * @param farbe
     * @param spalte
     * @return
     */
    int checkDiagonal(int farbe);

    /**
     * Addiert alle Werte der Steine einer Farbe
     * @param farbe
     * @param spalte
     * @return
     */
    int bewerteFarbe(int farbe);

    /**
     * Setzt einen Stein in das Feld
     * @param x wert der x-Achse
     * @param y Wert der y-Achse
     * @param wert Wert der gesetzt wird
     */
    void setFeldPos(int x, int y, int wert) {
        feld[y][x].setFarbe(wert);
        aktuell[x]++;
    }

    /**
     * Getter fuer rotWin
     * @return
     */
    bool getRotWin() const;

    /**
     * Setter fuer rotWin
     * @param value
     */
    void setRotWin(bool value);

    /**
     * Getter fuer gelbWin
     * @return
     */
    bool getGelbWin() const;

    /**
     * Setter fuer gelbWin
     * @param value
     */
    void setGelbWin(bool value);

private:

    void init();

    /**
     * das Spielfeld als mehrdimensionales Array
	 */
    Stein **feld;
    int *aktuell;
    unsigned short schwierigkeitsstufe;
    unsigned short zeilen;
    unsigned short spalten;
    bool rotWin;
    bool gelbWin;
};

#endif /* SPIELFELD_H_ */
