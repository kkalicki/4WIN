
#include "../h/sys/HisEintrag.h"
#include <sstream>

HisEintrag::HisEintrag()
{
    //nix
}

HisEintrag::HisEintrag(Spieler* spieler, unsigned short zeile, unsigned short spalte, unsigned short runde)
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

Spieler* HisEintrag::getSpieler() const
{
    return spieler;
}

void HisEintrag::setSpieler(Spieler* value)
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

void HisEintrag::fromCsvString(string csvString)
{
    char * buffer = new char[csvString.length()];
    strcpy(buffer,csvString.c_str());

    char delimiter1[] = ":";
    char delimiter2[] = ";";
    char *ptr;

    ptr = strtok(buffer, delimiter1);
    this->spieler = new Spieler();
    string spstr = ptr;

    ptr = strtok(NULL, delimiter1);
    string hisValues(ptr);
    char * buffer2 = new char[hisValues.length()];
    strcpy(buffer2,hisValues.c_str());

    ptr = strtok(buffer2, delimiter2);
    this->zeile = atoi(ptr);

    ptr = strtok(NULL, delimiter2);
    this->spalte = atoi(ptr);

    ptr = strtok(NULL, delimiter2);
    this->runde = atoi(ptr);

    spieler->fromCsvString(spstr);
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
    o << "Name : " << spieler->getName() << endl;
    o << "Farbe: " << spieler->getFarbe() << endl;
    o << "Zug  : " << zeile << " - " << spalte << endl;
    o << "Runde: " << runde << endl;
    o << "Zeit : " << zeitStempel() << endl;
    return o.str();
}

ostream& operator<<(ostream& out, HisEintrag& object) {
    out << *object.spieler << ":";
    out << object.zeile << ";";
    out << object.spalte<< ";";
    out << object.runde;
    return out;
}



