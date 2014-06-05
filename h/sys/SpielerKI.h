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
	virtual ~SpielerKI();

    boost::signals2::signal<void(unsigned short)> WerfeSteinSignal;
    //boost::signals2::signal<void(int)> KIZugSignal;
private:
    pthread_t spielerKIThread;
    Spielfeld* feld;
    time_t t;
};

#endif /* SPIELERKI_H_ */
