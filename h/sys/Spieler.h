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
    Spieler(string name="Spieler", short farbe=0);

	virtual ~Spieler();

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

    friend ostream& operator<<(ostream& out, Spieler& object)
    {
        out << object.name;
        out << object.farbe;
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
private:
    string name;
    short farbe;
    int istAmZug;
};

#endif /* SPIELER_H_ */
