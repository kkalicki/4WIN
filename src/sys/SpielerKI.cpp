/*
 * SpielerKI.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/sys/SpielerKI.h"
#include "../h/sys/FourWinExceptions.h"


SpielerKI::SpielerKI(string name, Spielfeld* feld, unsigned short farbe):Spieler(name,farbe) {
    this->isKI = true;
    this->feld = feld;
    besteSpalte = 3;
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
        sp->besteSpalte = rand() % (sp->feld->getSpalten());
    }while(sp->feld->getSpalteSteine(sp->besteSpalte) == sp->feld->getZeilen());

    //int ergebnis = sp->pruefeZuege(sp);
int ergebnis = -1;
    if (ergebnis >=0)
        sp->WerfeSteinSignal(ergebnis+1);
    else{
        ergebnis = sp->denkeWeiter(sp,sp->feld->getSchwierigkeitsstufe(),sp->farbe,-10000000,10000000);
            sp->WerfeSteinSignal(sp->besteSpalte+1);

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
//            if (pruefeWinZug(gegnerFarbe,i,sp->feld)){ //zum Blocken
//                block = i;
//            }
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


int SpielerKI::denkeWeiter(SpielerKI *sp, int tiefe, unsigned short farbe, int alpha, int beta)
{
    unsigned short gegnerFarbe;
    (farbe == ROT) ? gegnerFarbe = GELB: gegnerFarbe = ROT;
    int maxWert = alpha;
    int bewertung = 0;
    int zeile=0;
    int ergebnis;
    int aktuell;
    int wert;



//    ergebnis = sp->pruefeZuege(sp);//WIN&BLOCK
//    if (ergebnis != -1){
//        maxWert = 10000000;
//        if (tiefe == sp->feld->getSchwierigkeitsstufe()){
//            sp->besteSpalte = ergebnis;
//        }
////        cout << "return WIN&BLOCK tiefe : " << tiefe << endl;
//        return maxWert;
//    }

    // Ende Rekursion
    if (sp->feld->pruefeSpielfeld() || tiefe == 0 ){
        bewertung = sp->bewerteFeld(sp->feld, gegnerFarbe, farbe);
        return bewertung;
    }
    if (!sp->feld->pruefeSpielfeld()){
        for (int i = 0;i<sp->feld->getSpalten();i++){
            aktuell = feld->getSpalteSteine(i);
            if(aktuell < sp->feld->getZeilen()){

                sp->feld->setFeldPos(i,aktuell,farbe);
                if (feld->pruefeStein(farbe,0)){
                    wert = 10000000;
                }
                else{
                    wert = -denkeWeiter(sp, tiefe-1, gegnerFarbe, -beta, -maxWert);
                }
                sp->feld->loescheStein(i,aktuell);
                if (wert > maxWert) {
                    maxWert = wert;

                    if (tiefe == sp->feld->getSchwierigkeitsstufe()){
                        cout << *feld << endl;
                        cout << i << endl;
                        sp->besteSpalte = i;
                    }
                    if (maxWert >= beta)
                        break;
                }
            }
        }
    }
//    cout << "return denkeweiter tiefe : " << tiefe << endl;
    return maxWert;
}

int SpielerKI::bewerteFeld(Spielfeld *feld, unsigned short farbe, unsigned short gegnerFarbe)
{
    int ergebnis = 0;
//    ergebnis = feld->pruefeStein(gegnerFarbe,0);
//    if (ergebnis){
//        return -10000000;
//    }
//    ergebnis = feld->pruefeStein(farbe,0);
//    if (ergebnis){
//        return 10000000;
//    }

    feld->bewerteSteine();
//    ergebnis += feld->checkHorizontal(farbe,0);
//    ergebnis -= feld->checkHorizontal(gegnerFarbe,0);
//    ergebnis += feld->checkDiagonal(farbe,0);
//    ergebnis -= feld->checkDiagonal(gegnerFarbe,0);
//    ergebnis += feld->checkVertikal(farbe,0);
//    ergebnis -= feld->checkVertikal(gegnerFarbe,0);
    ergebnis = feld->bewerteFarbe(farbe,0);
    int ergebnisGegner = feld->bewerteFarbe(gegnerFarbe,0);


//    if (ergebnis< ergebnisGegner){
//        return -ergebnisGegner;
//    }else{
        return ergebnis - ergebnisGegner;
//    }
}

SpielerKI::~SpielerKI() {
    close();

}
int SpielerKI::getBesteSpalte() const
{
    return besteSpalte;
}

void SpielerKI::setBesteSpalte(int value)
{
    besteSpalte = value;
}


