/*
 * Das Spielfeld besteht in diesem Spiel aus einem zweidimensionalen Array aus Steinen
 * Der Stein besitzt einen Wert f�r die
 */

#include "../h/sys/Stein.h"
#include <sstream>

Stein::Stein() {
	this->farbe = ROT;
    this->wert = 0;
}

Stein::Stein(const Stein& rhs) {
	farbe = rhs.getFarbe();
    this->wert = rhs.wert;

}

Stein::Stein(short int farbe, short int x, short int y) {
	if ((farbe == ROT) || farbe == GELB)
		this->farbe=farbe;
	else this->farbe = 3;
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
  return *this; //Referenz auf das Objekt selbst zur�ckgeben
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
