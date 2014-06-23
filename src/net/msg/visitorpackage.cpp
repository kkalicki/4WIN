#include "../h/net/msg/visitorpackage.h"
#include "../h/sys/HisEintrag.h"

#include <sstream>

VisitorPackage::VisitorPackage()
{
   this->historie = *new Historie();
}

VisitorPackage::VisitorPackage(Spieler* sp1, Spieler* sp2, Historie* historie, unsigned short gameId)
{
    this->gameId = gameId;
    this->sp1 = *sp1;
    this->sp2 = *sp2;
    this->historie = *historie;
}

VisitorPackage::~VisitorPackage()
{
    //if(historie != 0){
      //  delete historie;
    //}
}

Spieler VisitorPackage::getSp1() const
{
    return sp1;
}

void VisitorPackage::setSp1(const Spieler &value)
{
    sp1 = value;
}
Spieler VisitorPackage::getSp2() const
{
    return sp2;
}

void VisitorPackage::setSp2(const Spieler &value)
{
    sp2 = value;
}

Historie *VisitorPackage::getHistorie()
{
    return &historie;
}

void VisitorPackage::setHistorie(const Historie& value)
{
    historie = value;
}

void VisitorPackage::fromStream(string stream)
{
    istringstream in(stream);
    string line;

    //id
    getline(in,line);
    this->gameId = atoi(line.c_str());
    //sp1
    getline(in,line);
    Spieler sp1;
    sp1.fromCsvString(line);
    this->sp1 = sp1;
    //sp2
    getline(in,line);
    Spieler sp2;
    sp2.fromCsvString(line);
    this->sp2 = sp2;

    //historie
    while(getline(in,line))
    {
        HisEintrag* incomingEntry = new HisEintrag();
        incomingEntry->fromCsvString(line);
        this->historie.hinzufuegenEintrag(*incomingEntry);
    }
}

string VisitorPackage::toString()
{
    ostringstream o;
    o << this;
    return o.str();
}
int VisitorPackage::getGameId() const
{
    return gameId;
}

void VisitorPackage::setGameId(int value)
{
    gameId = value;
}


ostream& operator<<(ostream& out, VisitorPackage& object) {
    out << object.gameId << endl;
    out << object.sp1 << endl;
    out << object.sp2 << endl;
    out << object.historie;
    return out;
}


