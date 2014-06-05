/*
 * SpielerKI.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/sys/SpielerKI.h"
#include <pthread.h>

SpielerKI::SpielerKI(string name, Spielfeld* feld, unsigned short farbe):Spieler("KI",farbe) {
    this->isKI = true;
    this->feld = feld;
    time(&t);
    srand((unsigned int)t);
}

void SpielerKI::denken()
{
    pthread_create(&spielerKIThread, 0, starteDenkprozess, this);
    pthread_detach(spielerKIThread);


}
void *SpielerKI::starteDenkprozess(void *ptr)
{
    //((SpielerKI*)ptr)->
    sleep(1);


    unsigned short spalte;
    //do{
    spalte = rand() % (((SpielerKI*)ptr)->feld->getSpalten());
    //}while(((SpielerKI*)ptr)->feld->getSpalteSteine(spalte) < ((SpielerKI*)ptr)->feld->getZeilen());

    ((SpielerKI*)ptr)->WerfeSteinSignal(spalte+1);
}




SpielerKI::~SpielerKI() {
	// TODO Auto-generated destructor stub
}

