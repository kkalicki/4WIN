/*
 * Spielfeld.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/Spielfeld.h"
#include <sstream>

Spielfeld::Spielfeld() {
	for(int i = 0; i < Y;i++)
		for(int j = 0; j < X;j++){
			feld[i][j] = 2;
			aktuell[j] = 0;
		}
}



string Spielfeld::toString() const {
	ostringstream out;
	out << "Spielfeld: \n";
	char a = 'a';
	char wert;
	out << "   1  2  3  4  5  6  7 \n";

	for(int i = Y-1; i >= 0;i--){
		out << a++ << " ";
		for(int j = 0; j < X;j++){
			if (feld[i][j] == ROT)
				wert = 'R';
			else
				if (feld[i][j] == GELB)
					wert = 'G';
				else
					wert = ' ';
			out << "["<< wert <<"]";
		}
		out << "\n";
	}

	return out.str();
}

ostream& operator<<(ostream& out, Spielfeld& spf){
	out << spf.toString();
	return out;
}

Spielfeld::~Spielfeld() {
	// TODO Auto-generated destructor stub
}

