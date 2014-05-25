
#include "../h/sys/HisEintrag.h"
#include <sstream>

HisEintrag::HisEintrag(const Spieler& spieler, unsigned short zeile, unsigned short spalte, unsigned short runde)
{
    this->spieler = spieler;
    this->zeile = zeile;
    this->spalte = spalte;
    this->runde = runde;
    this->timestamp = time(0);
}

HisEintrag::~HisEintrag()
{
    //nix...
}

Spieler HisEintrag::getSpieler() const
{
    return spieler;
}

void HisEintrag::setSpieler(const Spieler &value)
{
    spieler = value;
}

unsigned short HisEintrag::getZeile() const
{
    return zeile;
}

void HisEintrag::setZeile(unsigned short value)
{
    zeile = value;
}

unsigned short HisEintrag::getSpalte() const
{
    return spalte;
}

void HisEintrag::setSpalte(unsigned short value)
{
    spalte = value;
}

string HisEintrag::zeitStempel()
{
     string rslt(ctime(&timestamp));
     return rslt;
}
unsigned short HisEintrag::getRunde() const
{
    return runde;
}

void HisEintrag::setRunde(unsigned short value)
{
    runde = value;
}

time_t HisEintrag::getTimestamp() const
{
    return timestamp;
}

void HisEintrag::setTimestamp(const time_t &value)
{
    timestamp = value;
}

string HisEintrag::toString()
{
    ostringstream o;
    o << "Name : " << spieler.getName() << endl;
    o << "Farbe: " << spieler.getFarbe() << endl;
    o << "Zug  : " << zeile << " - " << spalte << endl;
    o << "Runde: " << runde << endl;
    o << "Zeit : " << zeitStempel() << endl;
    return o.str();
}


