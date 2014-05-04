/*
 * Stein.h
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#ifndef STEIN_H_
#define STEIN_H_
#include <string>

using namespace std;

class Stein {
public:
	Stein(int farbe);

	virtual ~Stein();

	string toString();

	short int getFarbe() const {
		return farbe;
	}

	void setFarbe(short int farbe) {
		this->farbe = farbe;
	}

	//noch Auslagern
	const static unsigned short int ROT = 1;
	const static unsigned short int GELB = 0;

private:

	short int farbe;
};


#endif /* STEIN_H_ */
