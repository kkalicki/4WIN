#include "../h/net/msg/visitorpackage.h"
#include "../h/sys/HisEintrag.h"

#include <sstream>

VisitorPackage::VisitorPackage(Spieler sp1, Spieler sp2, Historie historie)
{
    this->sp1 = sp1;
    this->sp2 = sp2;
    this->historie = historie;
}

VisitorPackage::~VisitorPackage()
{
    //nix...
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
Historie VisitorPackage::getHistorie() const
{
    return historie;
}

void VisitorPackage::setHistorie(const Historie &value)
{
    historie = value;
}

void VisitorPackage::fromStream(string stream)
{

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


