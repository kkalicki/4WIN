#ifndef VISITORPACKAGE_H
#define VISITORPACKAGE_H

#include "../h/sys/Spieler.h"
#include "../h/sys/Historie.h"

class VisitorPackage{

public:
    VisitorPackage(Spieler sp1, Spieler sp2, Historie historie, int gameId);
    ~VisitorPackage();

    int getGameId() const;
    void setGameId(int value);

    Spieler getSp1() const;
    void setSp1(const Spieler &value);

    Spieler getSp2() const;
    void setSp2(const Spieler &value);

    Historie getHistorie() const;
    void setHistorie(const Historie &value);

    friend ostream& operator<< (ostream& out, VisitorPackage& object);
    friend istream& operator>>(istream& in, VisitorPackage& object);

    void fromStream(string stream);
    string toString();

private:
    int gameId;
    Spieler sp1;
    Spieler sp2;
    Historie historie;
};

#endif // VISITORPACKAGE_H
