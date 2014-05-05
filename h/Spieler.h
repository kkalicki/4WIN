/*
 * Spieler.h
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#ifndef SPIELER_H_
#define SPIELER_H_
#include <string>
#include "../h/Konstanten.h"
#include <iostream>

using namespace std;

class Spieler {
public:
	Spieler();
	Spieler(string name);

	virtual ~Spieler();

	const string& getName() const {
		return name;
	}

	void setName(const string& name) {
		this->name = name;
	}

private:
	string name;
};

#endif /* SPIELER_H_ */
