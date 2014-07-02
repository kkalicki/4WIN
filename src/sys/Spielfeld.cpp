/*
 * Spielfeld.cpp
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#include "../h/sys/Spielfeld.h"
#include <sstream>
#include "../h/sys/FourWinExceptions.h"

Spielfeld::Spielfeld(unsigned short zeilen, unsigned short spalten, int schwierigkeitsstufe)
{
    this->zeilen = zeilen;
    this->spalten = spalten;
    this->aktuell = new int[spalten];
    this->schwierigkeitsstufe = schwierigkeitsstufe;
    this->rotWin = false;
    this->gelbWin = false;
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
            aktuell[j] = 0;
        }
    }
}
bool Spielfeld::getGelbWin() const
{
    return gelbWin;
}

void Spielfeld::setGelbWin(bool value)
{
    gelbWin = value;
}

bool Spielfeld::getRotWin() const
{
    return rotWin;
}

void Spielfeld::setRotWin(bool value)
{
    rotWin = value;
}


int Spielfeld::werfeStein(Spieler* spieler, int spalte)
{
    if (spalte > 0 && spalte <= spalten){
        int aktuell = getSpalteSteine(spalte-1);
        if (aktuell < zeilen){
            setFeldPos(spalte-1,aktuell,spieler->getFarbe());
            bewerteSteine();
            if(pruefeStein(spieler->getFarbe())){
              return WIN;
            }
            if(pruefeSpielfeld()){
                return VOLL;
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

int Spielfeld::werfeTestStein(unsigned short farbe, int spalte)
{
    int ergebnis = 0;
    int aktuell=0;
    if (spalte+1 > 0 && spalte < spalten){
       aktuell = getSpalteSteine(spalte);
       if (aktuell < zeilen){
            setFeldPos(spalte,aktuell,farbe);
            if(pruefeStein(farbe)){
                ergebnis = WIN;
            }
        }
    }
    return ergebnis;
}

int Spielfeld::pruefeStein(int farbe) {
    if ((checkHorizontal(farbe,spalte)) || (checkVertikal(farbe,spalte)) || (checkDiagonal(farbe,spalte)))
        return true;
    else
        return false;
}

int Spielfeld::bewerteSteine()
{
    for(int i = 0; i < zeilen;i++){
        for(int j = 0; j < spalten-1;j++){
            if (this->getFeldPos(j,i)->getFarbe() != 2)
                    bewerteStein(j,i);
        }
    }
}

int Spielfeld::bewerteStein(int x, int y)
{
   Stein* stein = getFeldPos(x,y);
   unsigned short farbe = stein->getFarbe();
   int wert = 0;
   int ergebnis = 0;


   if (x-3 >=0){

       if((bewerteSteinFarbe(farbe,getFeldPos(x-1,y)->getFarbe()) == 2
           && bewerteSteinFarbe(farbe,getFeldPos(x-2,y)->getFarbe()) == 2)
               && (bewerteSteinFarbe(farbe,getFeldPos(x-3,y)->getFarbe()) == 2)){
           getFeldPos(x,y)->setWert(MAXWERT);
           (farbe== ROT) ? this->rotWin = true : this->gelbWin = true;
           return true;
       }
       if((bewerteSteinFarbe(farbe,getFeldPos(x-1,y)->getFarbe())!=0
           && bewerteSteinFarbe(farbe,getFeldPos(x-2,y)->getFarbe())!= 0)
               && (bewerteSteinFarbe(farbe,getFeldPos(x-3,y)->getFarbe())!= 0)){
           wert += 10;

           if((bewerteSteinFarbe(farbe,getFeldPos(x-1,y)->getFarbe()) == 2)){
               wert *= 5;
           }
           if((bewerteSteinFarbe(farbe,getFeldPos(x-2,y)->getFarbe()) == 2)){
              wert *= 5;
           }
           if((bewerteSteinFarbe(farbe,getFeldPos(x-3,y)->getFarbe()) == 2)){
            wert *= 5;
           }
       }
   }
   ergebnis += wert;
   wert = 0;

   if ((x+3 < spalten)){

       if((bewerteSteinFarbe(farbe,getFeldPos(x+1,y)->getFarbe()) == 2
           && bewerteSteinFarbe(farbe,getFeldPos(x+2,y)->getFarbe()) == 2)
               && (bewerteSteinFarbe(farbe,getFeldPos(x+3,y)->getFarbe()) == 2)){
           getFeldPos(x,y)->setWert(MAXWERT);
           (farbe== ROT) ? this->rotWin = true : this->gelbWin = true;
           return farbe;

       }
       if((bewerteSteinFarbe(farbe,getFeldPos(x+1,y)->getFarbe())!=0
           && bewerteSteinFarbe(farbe,getFeldPos(x+2,y)->getFarbe())!= 0)
               && (bewerteSteinFarbe(farbe,getFeldPos(x+3,y)->getFarbe())!= 0)){
                      wert += 10;

           if((bewerteSteinFarbe(farbe,getFeldPos(x+1,y)->getFarbe()) == 2)){
               wert *= 5;
           }
           if((bewerteSteinFarbe(farbe,getFeldPos(x+2,y)->getFarbe()) == 2)){
              wert *= 5;
           }
           if((bewerteSteinFarbe(farbe,getFeldPos(x+3,y)->getFarbe()) == 2)){
            wert *= 5;
           }
       }
   }
   ergebnis += wert;
   wert = 0;

   if ((x-3 >= 0)&&(y-3 >= 0)){

       if((bewerteSteinFarbe(farbe,getFeldPos(x-1,y-1)->getFarbe()) == 2
           && bewerteSteinFarbe(farbe,getFeldPos(x-2,y-2)->getFarbe()) == 2)
               && (bewerteSteinFarbe(farbe,getFeldPos(x-3,y-3)->getFarbe()) == 2)){
           getFeldPos(x,y)->setWert(MAXWERT);
           (farbe== ROT) ? this->rotWin = true : this->gelbWin = true;
           return farbe;
       }
       if((bewerteSteinFarbe(farbe,getFeldPos(x-1,y-1)->getFarbe())!=0
           && bewerteSteinFarbe(farbe,getFeldPos(x-2,y-2)->getFarbe())!= 0)
               && (bewerteSteinFarbe(farbe,getFeldPos(x-3,y-3)->getFarbe())!= 0)){
           wert += 10;

           if((bewerteSteinFarbe(farbe,getFeldPos(x-1,y-1)->getFarbe()) == 2)){
               wert *= 5;
           }
           if((bewerteSteinFarbe(farbe,getFeldPos(x-2,y-2)->getFarbe()) == 2)){
              wert *= 5;
           }
           if((bewerteSteinFarbe(farbe,getFeldPos(x-3,y-3)->getFarbe()) == 2)){
            wert *= 5;
           }
       }
   }
   ergebnis += wert;
   wert = 0;

   if ((x-3 >= 0)&&(y+3 < zeilen)){

       if((bewerteSteinFarbe(farbe,getFeldPos(x-1,y+1)->getFarbe()) == 2
           && bewerteSteinFarbe(farbe,getFeldPos(x-2,y+2)->getFarbe()) == 2)
               && (bewerteSteinFarbe(farbe,getFeldPos(x-3,y+3)->getFarbe()) == 2)){
           getFeldPos(x,y)->setWert(MAXWERT);
           (farbe== ROT) ? this->rotWin = true : this->gelbWin = true;

       }
       if((bewerteSteinFarbe(farbe,getFeldPos(x-1,y+1)->getFarbe())!=0
           && bewerteSteinFarbe(farbe,getFeldPos(x-2,y+2)->getFarbe())!= 0)
               && (bewerteSteinFarbe(farbe,getFeldPos(x-3,y+3)->getFarbe())!= 0)){
           wert += 10;

           if((bewerteSteinFarbe(farbe,getFeldPos(x-1,y+1)->getFarbe()) == 2)){
               wert *= 5;
           }
           if((bewerteSteinFarbe(farbe,getFeldPos(x-2,y+2)->getFarbe()) == 2)){
             wert *= 5;
           }
           if((bewerteSteinFarbe(farbe,getFeldPos(x-3,y+3)->getFarbe()) == 2)){
            wert *= 5;
           }
       }
   }
   ergebnis += wert;
   wert = 0;

    if ((x+3 < spalten)&&(y-3 >= 0)){

        if((bewerteSteinFarbe(farbe,getFeldPos(x+1,y-1)->getFarbe()) == 2
            && bewerteSteinFarbe(farbe,getFeldPos(x+2,y-2)->getFarbe()) == 2)
                && (bewerteSteinFarbe(farbe,getFeldPos(x+3,y-3)->getFarbe()) == 2)){
            getFeldPos(x,y)->setWert(MAXWERT);
            (farbe== ROT) ? this->rotWin = true : this->gelbWin = true;
        }
        if((bewerteSteinFarbe(farbe,getFeldPos(x+1,y-1)->getFarbe())!=0
            && bewerteSteinFarbe(farbe,getFeldPos(x+2,y-2)->getFarbe())!= 0)
                && (bewerteSteinFarbe(farbe,getFeldPos(x+3,y-3)->getFarbe())!= 0)){
           wert += 10;

            if((bewerteSteinFarbe(farbe,getFeldPos(x+1,y-1)->getFarbe()) == 2)){
                wert *= 5;
            }
            if((bewerteSteinFarbe(farbe,getFeldPos(x+2,y-2)->getFarbe()) == 2)){
               wert *= 5;
            }
            if((bewerteSteinFarbe(farbe,getFeldPos(x+3,y-3)->getFarbe()) == 2)){
             wert *= 5;
            }
        }
    }
    ergebnis += wert;
    wert = 0;

    if ((x+3 < spalten)&&(y+3 < zeilen)){

        if((bewerteSteinFarbe(farbe,getFeldPos(x+1,y+1)->getFarbe()) == 2
            && bewerteSteinFarbe(farbe,getFeldPos(x+2,y+2)->getFarbe()) == 2)
                && (bewerteSteinFarbe(farbe,getFeldPos(x+3,y+3)->getFarbe()) == 2)){
            getFeldPos(x,y)->setWert(MAXWERT);
            (farbe== ROT) ? this->rotWin = true : this->gelbWin = true;
        }
        if((bewerteSteinFarbe(farbe,getFeldPos(x+1,y+1)->getFarbe())!=0
            && bewerteSteinFarbe(farbe,getFeldPos(x+2,y+2)->getFarbe())!= 0)
                && (bewerteSteinFarbe(farbe,getFeldPos(x+3,y+3)->getFarbe())!= 0)){
            wert += 10;

            if((bewerteSteinFarbe(farbe,getFeldPos(x+1,y+1)->getFarbe()) == 2)){
               wert *= 5;
            }
            if((bewerteSteinFarbe(farbe,getFeldPos(x+2,y+2)->getFarbe()) == 2)){
               wert *= 5;
            }
            if((bewerteSteinFarbe(farbe,getFeldPos(x+3,y+3)->getFarbe()) == 2)){
             wert *= 5;
            }
        }
    }

    ergebnis += wert;
    wert = 0;

   if ((y-3 >= 0)){

       if((bewerteSteinFarbe(farbe,getFeldPos(x,y-1)->getFarbe()) == 2
           && bewerteSteinFarbe(farbe,getFeldPos(x,y-2)->getFarbe()) == 2)
               && (bewerteSteinFarbe(farbe,getFeldPos(x,y-3)->getFarbe()) == 2)){
           getFeldPos(x,y)->setWert(MAXWERT);
           (farbe== ROT) ? this->rotWin = true : this->gelbWin = true;

       }
       if((bewerteSteinFarbe(farbe,getFeldPos(x,y-1)->getFarbe())!=0
           && bewerteSteinFarbe(farbe,getFeldPos(x,y-2)->getFarbe())!= 0)
               && (bewerteSteinFarbe(farbe,getFeldPos(x,y-3)->getFarbe())!= 0)){
            wert += 10;

           if((bewerteSteinFarbe(farbe,getFeldPos(x,y-1)->getFarbe()) == 2)){
               wert *= 5;
           }
           if((bewerteSteinFarbe(farbe,getFeldPos(x,y-2)->getFarbe()) == 2)){
              wert *= 5;
           }
           if((bewerteSteinFarbe(farbe,getFeldPos(x,y-3)->getFarbe()) == 2)){
           wert *= 5;
           }
       }
   }
   ergebnis += wert;
   wert = 0;
   if ((y+3 < zeilen)){

       if((bewerteSteinFarbe(farbe,getFeldPos(x,y+1)->getFarbe()) == 2
           && bewerteSteinFarbe(farbe,getFeldPos(x,y+2)->getFarbe()) == 2)
               && (bewerteSteinFarbe(farbe,getFeldPos(x,y+3)->getFarbe()) == 2)){
           getFeldPos(x,y)->setWert(MAXWERT);
           (farbe== ROT) ? this->rotWin = true : this->gelbWin = true;

       }
       if((bewerteSteinFarbe(farbe,getFeldPos(x,y+1)->getFarbe())!=0
           && bewerteSteinFarbe(farbe,getFeldPos(x,y+2)->getFarbe())!= 0)
               && (bewerteSteinFarbe(farbe,getFeldPos(x,y+3)->getFarbe())!= 0)){
           wert += 10;

           if((bewerteSteinFarbe(farbe,getFeldPos(x,y+1)->getFarbe()) == 2)){
               wert *= 5;
           }
           if((bewerteSteinFarbe(farbe,getFeldPos(x,y+2)->getFarbe()) == 2)){
              wert *= 5;
           }
           if((bewerteSteinFarbe(farbe,getFeldPos(x,y+3)->getFarbe()) == 2)){
            wert *= 5;
           }
       }
   }
   ergebnis += wert;
   getFeldPos(x,y)->setWert(ergebnis);
   return false;
}

int Spielfeld::bewerteSteinFarbe(int farbe, int steinFarbe)
{
    int wert = 0;
    if (steinFarbe != 2){
        if (steinFarbe == farbe){
            return 2;
        }
        else {
            return 0;
        }
    }
    else{
        return 1;
    }

}

bool Spielfeld::pruefeSpielfeld()
{
    for (int i=0; i<this->spalten; i++){
        if (this->aktuell[i] < this->zeilen)
            return false;
    }
    return true;
}

int Spielfeld::checkHorizontal(int farbe, int spalte) {
    short int wert = (farbe==ROT) ? ROT : GELB;

        for(int i = zeilen-1; i >= 0;i--){
            for(int j = 0; j < spalten-3;j++){
                if (getFeldPos(j,i)->getFarbe() == wert
                    && (getFeldPos(j+1,i)->getFarbe() == wert)
                    && (getFeldPos(j+2,i)->getFarbe() == wert)
                    && (getFeldPos(j+3,i)->getFarbe() == wert)){
                        return true;
                    }

                }

            }
        return false;
}


int Spielfeld::checkVertikal(int farbe, int spalte) {
    short int wert = (farbe==ROT) ? ROT : GELB;
        for(int j = 0; j < spalten;j++){
            for(int i = zeilen-1; i >= 3;i--){
                if ((getFeldPos(j,i)->getFarbe() == wert)
                    && (getFeldPos(j,i-1)->getFarbe() == wert)
                    && (getFeldPos(j,i-2)->getFarbe() == wert)
                    && (getFeldPos(j,i-3)->getFarbe() == wert)){
                    return true;
                }

            }

        }
        return false;
    }

int Spielfeld::checkDiagonal(int farbe, int spalte) {
    short int wert = (farbe==ROT) ? ROT : GELB;
    for(int i = zeilen-1; i >= 3;i--){
        for(int j = 0; j < spalten-3;j++){
            if ((getFeldPos(j,i)->getFarbe() == wert)
                && (getFeldPos(j+1,i-1)->getFarbe() == wert)
                && (getFeldPos(j+2,i-2)->getFarbe() == wert)
                && (getFeldPos(j+3,i-3)->getFarbe() == wert)){
                     return true;
            }

        }

    }




    for(int i = zeilen-1; i >= 3;i--){
        for(int j = 3; j < spalten;j++){
            if ((getFeldPos(j,i)->getFarbe() == wert)
                && (getFeldPos(j-1,i-1)->getFarbe() == wert)
                && (getFeldPos(j-2,i-2)->getFarbe() == wert)
                && (getFeldPos(j-3,i-3)->getFarbe() == wert)){
                     return true;
            }

        }

    }
    return false;
}
int Spielfeld::bewerteFarbe(int farbe)
{
    int wert = 0;
    for(int i = 0; i < zeilen;i++){
        for(int j = 0; j < spalten;j++){
            if (this->getFeldPos(j,i)->getFarbe() == farbe)
                    wert += this->getFeldPos(j,i)->getWert();

        }
    }
    return wert;

}
unsigned short Spielfeld::getSchwierigkeitsstufe() const
{
    return schwierigkeitsstufe;
}

void Spielfeld::setSchwierigkeitsstufe(unsigned short value)
{
    schwierigkeitsstufe = value;
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
        out << endl;
    }

    return out.str();
}
