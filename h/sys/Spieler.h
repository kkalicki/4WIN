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

class Spieler {
public:
    Spieler(string name="Spieler",unsigned short farbe=ROT);
    Spieler(const Spieler &rhs);
	const string& getName() const {
		return name;
	}

	void setName(const string& name) {
		this->name = name;
	}

    short getFarbe() const{
        return farbe;
    }

    void setFarbe(const short farbe){
        this->farbe = farbe;
    }

    int getIstAmZug() const
    {
        return istAmZug;
    }

    void setIstAmZug(int value)
    {
        istAmZug = value;
    }

    void fromCsvString(string csv);

    friend ostream& operator<<(ostream& out, Spieler& object)
    {
        out << object.name << ";";
        out << object.farbe<< ";";
        out << object.istAmZug;
        return out;
    }

    friend istream &operator>>( istream  &input, Spieler &object )
    {
        input >> object.name;
        input >> object.farbe;
        input >> object.istAmZug;
        return input;
    }

    string toString() const;
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
