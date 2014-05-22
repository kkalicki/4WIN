/*
 * Spieler.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/sys/Spieler.h"

Spieler::Spieler() {
}
Spieler::Spieler(string name, short farbe) {
	this->name=name;
    this->farbe = farbe;
}

Spieler::~Spieler() {
	// TODO Auto-generated destructor stub
}


