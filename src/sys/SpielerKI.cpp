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
        sp->WerfeSteinSignal(ergebnis+1);
    else{
        ergebnis = sp->denkeWeiter(sp,sp->feld->getSchwierigkeitsstufe(),sp->farbe);
        if (ergebnis >= 1 )
            sp->WerfeSteinSignal(sp->besteSpalte+1);
        else{
            sp->WerfeSteinSignal(spalte+1);
        }
    }

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

int SpielerKI::pruefeWinZug(unsigned short farbe, int spalte, Spielfeld* feld)
{
    int ergebnis = false;
    if (feld->werfeTestStein(farbe,spalte) == WIN){
        ergebnis =  true;
    }
    feld->loescheStein(spalte,feld->getSpalteSteine(spalte)-1);
    return ergebnis;
}

int SpielerKI::denkeWeiter(SpielerKI *sp, int tiefe, unsigned short farbe)
{
    unsigned short gegnerFarbe;
    (farbe == ROT) ? gegnerFarbe = GELB: gegnerFarbe = ROT;
    int maxWert = -10000000;
    int bewertung;
    if (sp->feld->pruefeSpielfeld() || tiefe == 0 ){


        bewertung = sp->bewerteFeld(sp->feld, sp->farbe, gegnerFarbe);
        if (bewertung >= 1){
            cout << *feld << endl;
            cout << bewertung << endl;
        }
        return bewertung;
    }
    int zeile=0;

    int wert = 0;
    if (!sp->feld->pruefeSpielfeld()){
        for (int i = 0;i<sp->feld->getSpalten();i++){
            if(sp->feld->getSpalteSteine(i) < sp->feld->getZeilen()){

                sp->feld->werfeTestStein(farbe,i);
                zeile = sp->feld->getSpalteSteine(i);

                wert = denkeWeiter(sp, tiefe-1, gegnerFarbe);

                sp->feld->loescheStein(i,zeile-1);

            }
            if (wert > maxWert) {
                maxWert = wert;
                if (tiefe == sp->feld->getSchwierigkeitsstufe()){
                    sp->besteSpalte = i;
                }
           }
        }
    }
    return maxWert;
}

int SpielerKI::bewerteFeld(Spielfeld *feld, unsigned short farbe, unsigned short gegnerFarbe)
{
    int ergebnis = feld->pruefeStein(gegnerFarbe,0);
    if (ergebnis)
            return -10000000;
    ergebnis = feld->pruefeStein(farbe,0);
    if (ergebnis){
        return 1;
    }
    return 0; // :-)
}

SpielerKI::~SpielerKI() {

}
int SpielerKI::getBesteSpalte() const
{
    return besteSpalte;
}

void SpielerKI::setBesteSpalte(int value)
{
    besteSpalte = value;
}


