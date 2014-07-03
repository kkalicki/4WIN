/*
 * Spiel.h
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#ifndef SPIEL_H_
#define SPIEL_H_
#include <string>
#include "../h/sys/Konstanten.h"
#include "../h/sys/Spielfeld.h"
#include "../h/sys/Spieler.h"
#include "../h/sys/Historie.h"
#include "boost/signals2.hpp"
#include <iostream>

class Spiel {

public:
    /**
     * Konstruktor des Spiels
     * @param zeilen
     * @param spalten
     * @param schwierigkeitsstufe
     */
    Spiel(unsigned short zeilen=Y, unsigned short spalten=X, int schwierigkeitsstufe = 0);

    virtual ~Spiel();

    /**
     * Startet das Spiel, Initialisiert die Spieler und lost aus wer anfängt und welche Farbe hat
     * @param nameSpieler1
     * @param nameSpieler2
     * @param sp1KI
     * @param sp2KI
     */
    void starteSpiel(string nameSpieler1, string nameSpieler2, bool sp1KI, bool sp2KI);

    /**
     * fuehrt den naechstern Zug einens Spielers aus
     * @param spieler
     * @param spalte
     * @return
     */
    virtual int naechsterZug(Spieler* spieler, unsigned short spalte);

    /**
     * fuehrt den Zug eines Netzwerkspielers aus
     * @param spalte
     */
    virtual void naechsterZugRemote(int spalte);

    /**
     * Beendet das spiel...
     */
    virtual void aufgeben();

    /**
     * Beendet das Spiel
     */
    virtual void beenden();

    /**
     * Getter fuer den letzten Historie Eintrag
     * @return
     */
    HisEintrag* getLetztenHisEintrag();

    /**
     * Erstellt einen neuen Historie Eintrag fur den Zug der gespielt wurde
     * @param spieler
     * @param zeile
     * @param spalte
     * @param runde
     */
    void erstelleNeuenHisEintrag(Spieler* spieler,
                                 unsigned short zeile,
                                 unsigned short spalte,
                                 unsigned short runde);


    /**
     * Getter fuer die aktuelle Zeile
     * @param spalte
     * @return
     */
    int getAktuelleZeile(int spalte);

    /**
     * Getter fuer die ID des Spiels
     * @return
     */
    int getId() const
    {
        return id;
    }

    /**
     * Setter fuer die ID des Spiels
     * @param value
     */
    void setId(int value)
    {
        id = value;
    }

    /**
     * Getter fuer den aktuellen Spieler
     * @return
     */
    Spieler* getAktuellerSpieler() const {
        return aktuellerSpieler;
    }

    /**
     * Getter fuer vorherigen Spieler
     * @return
     */
    Spieler* getVerherigerSpieler() const {
        return vorherigerSpieler;
    }

    /**
     * Getter fuer Spieler 2
     * @return
     */
    Spieler* getSp1() const{
        return sp1;
    }

    /**
     * Setter fuer Spieler 1
     * @param value
     */
    void setSp1(Spieler* value){
        sp1 = value;
    }

    /**
     * Getter fuer Spieler 2
     * @return
     */
    Spieler* getSp2() const{
        return sp2;
    }

    /**
     * Setter fuer Spieler 2
     * @param value
     */
    void setSp2(Spieler* value){
        sp2 = value;
    }

    /**
     * Getter fuer die Runde
     * @return
     */
    unsigned short getRunde() const{
        return runde;
    }

    /**
     * Setter fuer die Runde
     * @param value
     */
    void setRunde(unsigned short value){
        runde = value;
    }

    /**
     * Getter fuer die Historie
     * @return
     */
    Historie *getHistorie() const
    {
        return historie;
    }

    /**
     * Setter fuer die Historie
     * @param value
     */
    void setHistorie(Historie *value)
    {
        historie = value;
    }

    /**
     * Ueberladung des operator << Operators
     * @param out
     * @param sp
     * @return
     */
    friend ostream& operator<<(ostream& out, Spiel& sp);

    /**
     * toString Methode der Klasse
     */
    string toString() const;

    /**
     * fuert einen Spielerwechsel durch
     */
    void wechselSpieler();

    /**
     * RemoteZugSignal Signal mit der Spalte an die GUI wenn ein Netzwerkspieler gezogen hat
     */
    boost::signals2::signal<void(unsigned short,int)> RemoteZugSignal;

protected:
    unsigned short id;
    Spielfeld *spielfeld;
    Historie *historie;
    Spieler *sp1;
    Spieler *sp2;
    Spieler *aktuellerSpieler;
    Spieler *vorherigerSpieler;
    unsigned short runde;
    bool istAktiv;

};

#endif /* SPIEL_H_ */
