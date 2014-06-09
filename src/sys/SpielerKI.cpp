/*
 * SpielerKI.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/sys/SpielerKI.h"
#include "../h/sys/FourWinExceptions.h"
#include <pthread.h>

SpielerKI::SpielerKI(string name, Spielfeld* feld, unsigned short farbe):Spieler(name,farbe) {
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
    SpielerKI* sp = ((SpielerKI*)ptr);

    unsigned short spalte;
    do{
        spalte = rand() % (sp->feld->getSpalten());
    }while(sp->feld->getSpalteSteine(spalte) == sp->feld->getZeilen());

    int ergebnis = sp->pruefeZuege(sp);

    if (ergebnis >=0)
        spalte = ergebnis;

    sp->WerfeSteinSignal(spalte+1);
}

int SpielerKI::pruefeZuege(SpielerKI* sp)
{
    unsigned short gegnerFarbe;
    (sp->getFarbe() == ROT) ? gegnerFarbe = GELB: gegnerFarbe = ROT;
    int spalten = sp->feld->getSpalten();
    int zeilen = sp->feld->getZeilen();
    int aktuell;
    int block = -1;


    for (int i = 0;i<spalten;i++){
        aktuell = sp->feld->getSpalteSteine(i);
        if (aktuell < zeilen){
            if (pruefeWinZug(sp->farbe,i,sp->feld)){
                return i;
            }
            if (pruefeWinZug(gegnerFarbe,i,sp->feld)){ //zum Blocken
                block = i;
            }
        }
    }
    return block;
}

bool SpielerKI::pruefeWinZug(unsigned short farbe, int spalte, Spielfeld* feld)
{
    bool ergebnis = false;
    if (feld->werfeTestStein(farbe,spalte) == WIN){
        ergebnis =  true;
    }
    feld->loescheStein(spalte,feld->getSpalteSteine(spalte)-1);
    return ergebnis;
}

SpielerKI::~SpielerKI() {

}

