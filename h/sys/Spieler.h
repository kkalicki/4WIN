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
	Spieler();
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

private:
    string name;
    short farbe;
};

#endif /* SPIELER_H_ */
