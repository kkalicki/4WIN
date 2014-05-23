/*
 * Spieler.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/sys/Spieler.h"
#include <sstream>

Spieler::Spieler(string name, short farbe) {
	this->name=name;
    this->farbe = farbe;
    this->istAmZug = false;
}

Spieler::~Spieler() {
}

ostream& operator<<(ostream& out, Spieler& spieler)
{
    out << spieler.toString();
    return out;
}

string Spieler::toString()
{
    ostringstream o;
    o << "Spieler: " << name << endl;
    o << "Farbe  : " << (farbe == ROT ? "ROT" : "GELB") << endl;
    o << "Zug    : " << (istAmZug == true ? "Ist am Zug" : "Ist nicht Zug") << endl;
    return o.str();
}


