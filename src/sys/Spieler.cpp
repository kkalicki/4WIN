/*
 * Spieler.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/sys/Spieler.h"
#include "../h/sys/FourWinExceptions.h"
#include <sstream>
#include <cstring>

Spieler::Spieler(string name, unsigned short farbe) {
	this->name=name;
    this->farbe = farbe;
    this->istAmZug = false;
    this->isKI = false;
}

Spieler::Spieler(const Spieler &rhs) {
    this->name=rhs.getName();
    this->farbe = rhs.getFarbe();
    this->istAmZug = rhs.getIstAmZug();
    this->isKI = rhs.getIsKI();
}


void Spieler::fromCsvString(string csv)
{
    char * buffer = new char[csv.length()];
    strcpy(buffer,csv.c_str());

    char delimiter[] = ";";
    char *ptr;

    ptr = strtok(buffer, delimiter);
    if(ptr == NULL){
        cout << "Fehler beim parsen des names (SPieler)" << endl;
        throw Server4WinException("Fehler beim parsen des names (HisEintrag)");
    }
    this->name = ptr;

    ptr = strtok(NULL, delimiter);
    if(ptr == NULL){
        cout << "Fehler beim parsen der farbe (SPieler)" << endl;
        throw Server4WinException("Fehler beim parsen des farbe (HisEintrag)");
    }
    this->farbe = atoi(ptr);

    ptr = strtok(NULL, delimiter);
    if(ptr == NULL){
        cout << "Fehler beim parsen istAmZug (SPieler)" << endl;
        throw Server4WinException("Fehler beim parsen des istAmZug (HisEintrag)");
    }
    this->istAmZug = atoi(ptr);

}

string Spieler::toString() const{
    ostringstream o;
    o << "Spieler: " << name << endl;
    o << "Farbe  : " << (farbe == ROT ? "ROT" : "GELB") << endl;
    o << "Zug    : " << (istAmZug == true ? "Ist am Zug" : "Ist nicht Zug") << endl;
    return o.str();
}
bool Spieler::getIsKI() const
{
    return isKI;
}

Spieler::~Spieler()
{

}

