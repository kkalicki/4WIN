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
#include <pthread.h>

class SpielerKI : public Spieler{
public:
    /**
     * Konstruktor fuer SpielerKI
     * @param name Name des Spielers
     * @param feld Spielfeld des Spiels
     * @param farbe Farbe des Spielers
     */
    SpielerKI(string name, Spielfeld* feld, unsigned short farbe = ROT);

    /**
     * starteDenkprozess neuer Thread um ueber folgende zuege nachzudenken
     * @param ptr Parameter um im Thread auf die eigene Klasse zuzugreifen
     * @return
     */
    static void * starteDenkprozess(void * ptr);

    /**
     * werfeSteinSignal sendet ein Signal an die GUI, fuehrt einen Zug aus
     */
    void werfeSteinSignal();

    /**
     * Prueft ob Win/Block Situationen vorliegen
     * @param sp
     * @return
     */
    int pruefeZuege(SpielerKI *sp);

    /**
     *Prueft ob man mit dem Zug gewinnen kann
     * @param farbe
     * @param spalte
     * @param feld
     * @return
     */
    int pruefeWinZug(unsigned short farbe, int spalte, Spielfeld *feld);

    /**
     * Rekursiver Alpha-Beta algorithmus, baut rekursiv alle moeglichen Spielsituationen auf bis zur angegebenen tiefe (schwierigkeitsgrad)
     * bewertet die Situationen und verändert den Wert besteSpalte
     * @param sp Spieler
     * @param tiefe Schwierigkeitsgrad wieviel Zuege die KI vorausdenken Soll
     * @param farbe Farbe des gerade Ziehenden
     * @param alpha Maxwert
     * @param beta Minimalwert
     * @return Bewertung der Spielsituation
     */
    int denkeWeiter(SpielerKI *sp, int tiefe, unsigned short farbe, int alpha, int beta);

    /**
     * erzeugt einen neuen Thread um den Denkprozess zu starten
     */
    void denken();

    /**
     * bewertet die aktuell gelegte Spielsituation
     * @param feld
     * @param farbe
     * @param gegnerFarbe
     * @return
     */
    int bewerteFeld(Spielfeld* feld, unsigned short farbe, unsigned short gegnerFarbe);
	virtual ~SpielerKI();

    /**
     * Schließt den Thread, wird vom destruktor aufgerufen
     */
    void close(){
        pthread_cancel(spielerKIThread);
    }

    /**
     * Boost WerfeSteinSignal
     */
    boost::signals2::signal<void(unsigned short)> WerfeSteinSignal;
    //boost::signals2::signal<void(int)> KIZugSignal;

    /**
     * Getter fuer die beste Spalte
     * @return
     */
    int getBesteSpalte() const;

    /**
     * Setter fuer die beste Spalte
     * @param value
     */
    void setBesteSpalte(int value);

private:
    pthread_t spielerKIThread;
    Spielfeld* feld;
    time_t t;

    int besteSpalte;
};

#endif /* SPIELERKI_H_ */
