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
    this->aktuell = new int[spalten];
    init();
}

Spielfeld::~Spielfeld() {

   for (int j = 0; j < zeilen ; j++){
       delete [] feld[j];
   }
   delete [] feld;
   delete aktuell;
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

int Spielfeld::werfeStein(Spieler* spieler, int spalte)
{
     if (spalte > 0 && spalte <= spalten){
        int aktuell = getSpalteSteine(spalte-1);
        if (aktuell < zeilen){
            setFeldPos(spalte-1,aktuell,spieler->getFarbe());

            if(pruefeStein(spieler->getFarbe(), spalte)){
              return WIN;
            }

            return 0;
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
    short int wert = (farbe==ROT) ? ROT : GELB;
        for(int i = Y-1; i >= 0;i--){
            for(int j = 0; j < X-3;j++){
                if (getFeldPos(j,i).getFarbe() == wert){
                    if (getFeldPos(j+1,i).getFarbe() == wert){
                        if (getFeldPos(j+2,i).getFarbe() == wert){
                            if (getFeldPos(j+3,i).getFarbe() == wert){
                                return true;
                            }

                        }

                    }

                }
            }
        }
        return false;
}


int Spielfeld::checkVertikal(int farbe, int spalte) {
    short int wert = (farbe==ROT) ? ROT : GELB;
        for(int j = 0; j < X;j++){
            for(int i = Y-1; i >= 3;i--){
                if (getFeldPos(j,i).getFarbe() == wert){
                    if (getFeldPos(j,i-1).getFarbe() == wert){
                        if (getFeldPos(j,i-2).getFarbe() == wert){
                            if (getFeldPos(j,i-3).getFarbe() == wert){
                                return true;
                            }

                        }

                    }

                }
            }
        }
        return false;
    }

int Spielfeld::checkDiagonal(int farbe, int spalte) {
    short int wert = (farbe==ROT) ? ROT : GELB;
    for(int i = zeilen-1; i >= 3;i--){
        for(int j = 0; j < spalten-3;j++){
            if (getFeldPos(j,i).getFarbe() == wert){
                if (getFeldPos(j+1,i-1).getFarbe() == wert){
                    if (getFeldPos(j+2,i-2).getFarbe() == wert){
                        if (getFeldPos(j+3,i-3).getFarbe() == wert){
                            return true;
                        }

                    }

                }

            }
        }
    }
    for(int i = zeilen-1; i >= 3;i--){
        for(int j = 3; j < spalten;j++){
            if (getFeldPos(j,i).getFarbe() == wert){
                if (getFeldPos(j-1,i-1).getFarbe() == wert){
                    if (getFeldPos(j-2,i-2).getFarbe() == wert){
                        if (getFeldPos(j-3,i-3).getFarbe() == wert){
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
    char a = 'a';
    int headercount = 0;

    //erstelle header...
    out << "  ";
    do{
     out <<" "<< ++headercount << " ";
    }while(headercount < spalten);

    out << endl;

    for(int i = zeilen-1; i >= 0;i--){
        out << a++ << " ";
        for(int j = 0; j < spalten;j++){
            Stein aktuell = feld[i][j];
            out << "["<< aktuell <<"]";
        }
        out << "\n";
    }

    return out.str();
}

