#ifndef STEIN_H_
#define STEIN_H_
#include <string>
#include "../h/sys/Konstanten.h"
#include <iostream>

using namespace std;

/**
 * Der Stein des Spielfeldes. Nimmt die Farbe eines Spielers an. Besitzt einen Wert, wie gut der Stein in Bezug zu seinen umliegenden Nachbarn ist
 * zur
 */
class Stein {
public:
	/**
	 * Standardkonstruktor
	 */
	Stein();

	Stein(const Stein& rhs);
	/**
	 * Konstruktor zum erstellen eines Steins
	 * @param farbe Entweder ROT oder GELB(Konstanten)
	 */
	Stein(short int farbe, short int x, short int y);


    /**
     * Destruktor
     */
	virtual ~Stein();

	/**
	 * Gibt die Farbe eines Steines aus
	 * @return string Farbe des Steines
	 */
	string toString() const;

	/**
	 * Ueberladung des << Operators fuer toString-Methode
	 * @param out Variable des Outstreams
	 * @param st Variable der Klasse Stein
	 * @return manipulierter outstream
	 */
	friend ostream& operator<<(ostream& out, Stein& st);

	/**
	 * Ueberladung des >> Operators
	 * @param in Variable des Instreams
	 * @param st Variable der Klasse Stein
	 * @return manipulierter instream
	 */
	friend istream& operator>>(istream& in, Stein& st);

    /**
     * Überladung des '=' Operators
     * @brief operator =
     * @param rhs
     * @return
     */
	Stein& operator= (Stein const& rhs);

    /**
      Überladung des '==' Operators
     * @brief operator ==
     * @param lhs
     * @param rhs
     * @return
     */
	friend bool operator==(Stein const& lhs, short int const& rhs){
        return (&lhs.farbe == &rhs);
	}
	/**
	 * Uebergibt den Wert des Steines
	 * @return short int farbe (ROT oder GELB)
	 */
	short int getFarbe() const {
		return farbe;
	}

	/**
	 * Setzt die Farbe eines Steines entweder auf ROT oder GELB
	 * @param farbe Farbe des Steines
	 */
	void setFarbe(short int farbe) {
		//if ((farbe == GELB) || (farbe == ROT))
		this->farbe = farbe;
	}

    /**
     * Getter fuer Wert
     * @return
     */
    int getWert() const;

    /**
     * Setter fuer Wert
     * @param value
     */
    void setWert(int value);

private:

    /**
     * Farbe des Spielsteins, entweder ROT oder GELB (Konstanten)
	 */
    short int farbe;
    int wert;

};


#endif /* STEIN_H_ */
