/*
 * Stein.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/sys/Stein.h"
#include <sstream>

Stein::Stein() {
	this->farbe = ROT;
    this->wert = 0;
}

Stein::Stein(const Stein& rhs) {
	farbe = rhs.getFarbe();
	*pos=*rhs.pos;
    this->wert = rhs.wert;

}

Stein::Stein(short int farbe, short int x, short int y) {
	if ((farbe == ROT) || farbe == GELB)
		this->farbe=farbe;
	else this->farbe = 3;
	this->setPos(x,y);
}

Stein::~Stein() {
	// TODO Auto-generated destructor stub
}

string Stein::toString() const {

	string steinfarbe;
	if (this->farbe == ROT)
		steinfarbe = "O";
	else if (this->farbe == GELB)
		steinfarbe = "X";
	else steinfarbe = " ";
	ostringstream out;
	out << steinfarbe;
	return out.str();
}



Stein& Stein::operator= (Stein const& rhs)
{
  if (this != &rhs)  //oder if (*this != rhs)
  {
	 Stein tmp(rhs);
  }
  return *this; //Referenz auf das Objekt selbst zurückgeben
}
int Stein::getWert() const
{
    return wert;
}

void Stein::setWert(int value)
{
    wert = value;
}


istream& operator>>(istream& in, Stein& st){
    return in;
}

ostream& operator<<(ostream& out, Stein& st){
	out << st.toString();
	return out;
}
