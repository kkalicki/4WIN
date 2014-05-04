/*
 * Stein.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/Stein.h"
#include <sstream>

Stein::Stein() {
	this->farbe = ROT;
}

Stein::Stein(short int farbe) {
	if ((farbe == ROT) || farbe == GELB)
		this->farbe=farbe;
}

Stein::~Stein() {
	// TODO Auto-generated destructor stub
}

string Stein::toString() const {

	string steinfarbe;
	steinfarbe = (this->farbe == ROT ? "Rot" : "Gelb");
	ostringstream out;
	out << "Farbe des Steines: " << steinfarbe;
	return out.str();
}

istream& operator>>(istream& in, Stein& st){
	return in;
}

ostream& operator<<(ostream& out, Stein& st){
	out << st.toString();
	return out;
}
