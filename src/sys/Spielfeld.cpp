/*
 * Spielfeld.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/sys/Spielfeld.h"
#include <sstream>
#include "../h/sys/FourWinExceptions.h"

Spielfeld::Spielfeld(unsigned short zeilen, unsigned short spalten)
{
    this->zeilen = zeilen;
    this->spalten = spalten;
    init();
}

Spielfeld::~Spielfeld() {

   for (int j = 0; j < zeilen ; j++){
       delete [] feld[j];
   }
   delete [] feld;
}

void Spielfeld::init()
{
    //Array dynamisch im Speicher anlegen..
    feld = new Stein*[zeilen];
    for (int i = 0; i < zeilen ; i++){
         feld[i] = new Stein[spalten];
    }

    //Array initialisieren...
    for(int i = 0; i < zeilen;i++){
        for(int j = 0; j < spalten;j++){
            feld[i][j].setFarbe(2);
            feld[i][j].setPos(j,i);
            aktuell[j] = 0;
        }
    }
}

int Spielfeld::werfeStein(Spieler spieler, int spalte)
{
     if (spalte > 0 && spalte <= spalten){
        int aktuell = getSpalteSteine(spalte-1);
        if (aktuell < zeilen){
            setFeldPos(spalte-1,aktuell,spieler.getFarbe());

            if(pruefeStein(spieler.getFarbe(), spalte))
            return -1;

            return spalte;
        }
        else{
            throw SpielFeldException("Spalte ist Voll!");
        }
    }
    else
    {
        throw EingabeException("Fehlerhafte Eingabe!");
     }
}

int Spielfeld::pruefeStein(int farbe, int spalte) {
    if (checkHorizontal(farbe,spalte) || checkVertikal(farbe,spalte) || checkDiagonal(farbe,spalte))
        return true;
    else
        return false;
}

int Spielfeld::checkHorizontal(int farbe, int spalte) {
    int wert = (farbe==ROT) ? ROT : GELB;
    int zeile = getSpalteSteine(spalte);


    return false;
}

int Spielfeld::checkVertikal(int farbe, int spalte) {
    int wert = (farbe==ROT) ? ROT : GELB;
    int zeile = getSpalteSteine(spalte-1);

    Stein aktuell = getFeldPos(zeile, spalte-1);
    const short int *pos = aktuell.getPos();

    //cout << "\npos x: " << pos[0]  << " y: " << pos[1] << "\n";
    //cout << "CHECK VERTIKAL AKTUELL :" << aktuell << " Zeile: " << zeile  << " Spalte: " << spalte << "\n";
    return false;
}

int Spielfeld::checkDiagonal(int farbe, int spalte) {
    int wert = (farbe==ROT) ? ROT : GELB;
    for(int i = zeilen-1; i >= 3;i--){
        for(int j = 0; j < spalten-3;j++){
            if (getFeldPos(j,i) == wert){
                if (getFeldPos(j+1,i-1) == wert){
                    if (getFeldPos(j+2,i-2) == wert){
                        if (getFeldPos(j+3,i-3) == wert){
                            return true;
                        }

                    }

                }

            }
        }
    }
    for(int i = zeilen-1; i >= 3;i--){
        for(int j = 3; j < spalten;j++){
            if (getFeldPos(j,i) == wert){
                if (getFeldPos(j-1,i-1) == wert){
                    if (getFeldPos(j-2,i-2) == wert){
                        if (getFeldPos(j-3,i-3) == wert){
                            return true;
                        }

                    }

                }

            }
        }
    }
    return false;
}

ostream& operator<<(ostream& out, Spielfeld& spf){
    out << spf.toString();
    return out;
}

string Spielfeld::toString() const {
    ostringstream out;
    out << "Spielfeld: \n";
    char a = 'a';
    out << "   1  2  3  4  5  6  7 \n";

    for(int i = zeilen-1; i >= 0;i--){
        out << a++ << " ";
        for(int j = 0; j < spalten;j++){
            Stein aktuell = feld[i][j];
            //(aktuell == ROT) || (aktuell == GELB) ? out << "["<< aktuell <<"]" : out << "[X]";
            out << "["<< aktuell <<"]";
        }
        out << "\n";
    }

    return out.str();
}

