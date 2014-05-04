/*
 * Stein.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/Stein.h"

Stein::Stein(int farbe) {
	if ((farbe == ROT) || farbe == GELB)
		this->farbe=farbe;
}

Stein::~Stein() {
	// TODO Auto-generated destructor stub
}

string Stein::toString() {
	string stein;
	stein = (farbe == ROT ? "Rot" : "Gelb");
	return stein;
}
