/*
 * SpielerKI.h
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#ifndef SPIELERKI_H_
#define SPIELERKI_H_
#include "../h/sys/Spieler.h"
#include "../h/sys/Spielfeld.h"
#include "boost/signals2.hpp"

class SpielerKI : public Spieler{
public:
    SpielerKI(string name, Spielfeld* feld, unsigned short farbe = ROT);
    void denken();
    static void * starteDenkprozess(void * ptr);
    void werfeSteinSignal();
    int pruefeZuege(SpielerKI *sp);
    int pruefeWinZug(unsigned short farbe, int spalte, Spielfeld *feld);
    int denkeWeiter(SpielerKI *sp, int tiefe, unsigned short farbe);
    int bewerteFeld(Spielfeld* feld, unsigned short farbe, unsigned short gegnerFarbe);
	virtual ~SpielerKI();

    boost::signals2::signal<void(unsigned short)> WerfeSteinSignal;
    //boost::signals2::signal<void(int)> KIZugSignal;
    int getBesteSpalte() const;
    void setBesteSpalte(int value);

private:
    pthread_t spielerKIThread;
    Spielfeld* feld;
    time_t t;
    int besteSpalte;
};

#endif /* SPIELERKI_H_ */
