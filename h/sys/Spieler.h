/*
 * Spieler.h
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#ifndef SPIELER_H_
#define SPIELER_H_
#include <string>
#include "../h/sys/Konstanten.h"
#include <iostream>

using namespace std;

/**
 * Der Spieler besitzt eine Farbe und einen Namen. Der Spieler kann ueberprueft werden, ob er dran ist und ob er ein realer Spieler ist oder KI
 */
class Spieler {
public:
    /**
     * Konstruktor
     * @param name Name des Spielers
     * @param farbe Farbe des Spielers, wenn keine Farbe angegeben wird -> ROT
     */
    Spieler(string name="Spieler",unsigned short farbe=ROT);
    /**
     * Kopierkonstruktor
     * @param rhs
     */
    Spieler(const Spieler &rhs);

    /**
     * Getter fuer Name
     * @return
     */
	const string& getName() const {
		return name;
	}

    /**
     * Setter fuer Name
     * @param name
     */
	void setName(const string& name) {
		this->name = name;
	}

    /**
     * Getter fuer Farbe
     * @return
     */
    short getFarbe() const{
        return farbe;
    }

    /**
     * Setter fuer farbe
     * @param farbe
     */
    void setFarbe(const short farbe){
        this->farbe = farbe;
    }

    /**
     * Pruefung Ob Spieler am zug ist
     * @return
     */
    int getIstAmZug() const
    {
        return istAmZug;
    }

    /**
     * Stellt ein ob der Spieler an der Reihe ist
     * @param value True oder False
     */
    void setIstAmZug(int value)
    {
        istAmZug = value;
    }

    void fromCsvString(string csv);

    /**
     * Ueberladung des << Operators fuer toString Methode
     * @param out
     * @param object
     * @return out-stream
     */
    friend ostream& operator<<(ostream& out, Spieler& object)
    {
        out << object.name << ";";
        out << object.farbe<< ";";
        out << object.istAmZug;
        return out;
    }

    /**
     * Ueberladung des >> Operators
     * @param input
     * @param object
     * @return
     */
    friend istream &operator>>( istream  &input, Spieler &object )
    {
        input >> object.name;
        input >> object.farbe;
        input >> object.istAmZug;
        return input;
    }

    /**
     * toString Methode
     * @return
     */
    string toString() const;

    /**
     * Getter zur Prüfung ob Spieler der Computer ist
     * @return
     */
    bool getIsKI() const;

    virtual ~Spieler();

protected:
    bool isKI;
    short farbe;
private:
    string name;
    int istAmZug;

};

#endif /* SPIELER_H_ */
