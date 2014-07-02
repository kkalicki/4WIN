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

    int ergebnis = sp->pruefeZuege(sp); //Prinzipielle Pruefung auf Win und Block
    if (ergebnis >=0)
        sp->WerfeSteinSignal(ergebnis+1);
    else{
        if (sp->feld->getSchwierigkeitsstufe() == 0){ // Leicht wirft KI nur Random-Werte
            do{
                spalte = rand() % (sp->feld->getSpalten());
            }while(sp->feld->getSpalteSteine(spalte) == sp->feld->getZeilen());
            sp->WerfeSteinSignal(spalte+1);
        }
        else{
            sp->denkeWeiter(sp,sp->feld->getSchwierigkeitsstufe(),sp->farbe,MINWERT,MAXWERT); //AlphaBeta
            if (sp->feld->getSpalteSteine(sp->besteSpalte) < sp->feld->getZeilen())
                sp->WerfeSteinSignal(sp->besteSpalte+1);
            else{ // Falls kein guter Zug gefunden wurde -> Erkennt das jeder Zug zum verlust führt
                do{
                    spalte = rand() % (sp->feld->getSpalten());
                }while(sp->feld->getSpalteSteine(spalte) == sp->feld->getZeilen());
                sp->WerfeSteinSignal(spalte+1);
            }
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


int SpielerKI::denkeWeiter(SpielerKI *sp, int tiefe, unsigned short farbe, int alpha, int beta)
{
    unsigned short gegnerFarbe;
    (farbe == ROT) ? gegnerFarbe = GELB: gegnerFarbe = ROT;

    // Ende Rekursion Bewertung jeder Endsituation
    if (sp->feld->pruefeSpielfeld() || tiefe == 0 ){
        int bewertung = sp->bewerteFeld(sp->feld, farbe, gegnerFarbe);
        return bewertung;
    }


    int maxWert = alpha;
    int aktuell;
    int wert;

    if (!sp->feld->pruefeSpielfeld()){
        for (int i = 0;i<sp->feld->getSpalten();i++){
            aktuell = feld->getSpalteSteine(i);
            if(aktuell < sp->feld->getZeilen()){

                sp->feld->setFeldPos(i,aktuell,farbe); //Wirft einen Teststein
                if (feld->pruefeStein(farbe)){ // prueft ob der Stein zum Gewinn fuehrt
                    wert = MAXWERT;
                }
                else{
                    wert = -denkeWeiter(sp, tiefe-1, gegnerFarbe, -beta, -maxWert); //bewertet die Beste Situation des gegner als eigene schlechteste
                }
                sp->feld->loescheStein(i,aktuell); //Loescht jeden gesetzten Stein wieder
                if (wert > maxWert) {
                    maxWert = wert;

                    if (tiefe == sp->feld->getSchwierigkeitsstufe()){
                        cout << *feld << endl;
                        cout << i << endl;
                        sp->besteSpalte = i; // Ueberschreibt die beste gefundene Spalte
                    }
                    if (maxWert >= beta)
                        break;
                }
            }
        }
    }
    return maxWert;
}

int SpielerKI::bewerteFeld(Spielfeld *feld, unsigned short farbe, unsigned short gegnerFarbe)
{
    int ergebnis = 0;

    feld->bewerteSteine();
    if (farbe == ROT){
        if (feld->getGelbWin()){
            ergebnis =  MINWERT;
        }
        else{ if (feld->getRotWin())
            ergebnis = MAXWERT;
        }
    }
    else{
        if (feld->getRotWin()){
            ergebnis =  MINWERT;
        }
        else{ if (feld->getGelbWin())
            ergebnis = MAXWERT;
        }
    }

    feld->setRotWin(false);
    feld->setGelbWin(false);
    if (ergebnis!=0)
        return ergebnis;

    ergebnis = feld->bewerteFarbe(farbe);
    int ergebnisGegner = feld->bewerteFarbe(gegnerFarbe);

        return ergebnis - ergebnisGegner;
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


