#ifndef HISEINTRAG_H
#define HISEINTRAG_H
#include "../h/sys/Spieler.h"
#include <ctime>
#include <string>

class HisEintrag{
public:
    HisEintrag(Spieler* spieler, unsigned short zeile=0, unsigned short spalte=0, unsigned short runde=0);
    ~HisEintrag();

    Spieler* getSpieler() const;
    void setSpieler(Spieler* value);

    unsigned short getZeile() const;
    void setZeile(unsigned short value);

    unsigned short getSpalte() const;
    void setSpalte(unsigned short value);

    time_t getTimestamp() const;
    void setTimestamp(const time_t &value);

    string zeitStempel();

    unsigned short getRunde() const;
    void setRunde(unsigned short value);

    string toString();

    friend ostream& operator<<(ostream& out, HisEintrag& object);
    friend istream& operator>>(istream& in, HisEintrag &object );

private:
    Spieler* spieler;
    unsigned short zeile;
    unsigned short spalte;
    unsigned short runde;
    time_t timestamp;

};

#endif // HISEINTRAG_H
