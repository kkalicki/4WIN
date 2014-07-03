#ifndef GAMEINFO_H
#define GAMEINFO_H

#include "../h/gui/I4WinWidget.h"
#include "../h/sys/Spieler.h"
#include "../h/gui/threads//timer4Win.h"
#include <QWidget>
#include <QPixmap>
#include <string>
#include <QThread>
#include <QMovie>

#include "ui_gameinfo.h"

namespace Ui {
class gameinfoUi;
}

/**
 * @brief The GameInfo class Widget, welches Informationen zu dem Spiel anzeigt. Bspw. Uhr, letzter zug, Namen usw.
 */
class GameInfo : public QWidget, public I4WinWidget
{
    Q_OBJECT
public:
    /**
     * @brief GameInfo Konstruktor fuer Klasse zu erstellen
     * @param parent    Parentwidget, hier ist es das MainWindow
     */
    explicit GameInfo(QWidget * parent=0);


    /**
     * @brief init Funktion, welche zum initilisieren des Widgets erforderlich ist. Vererbung durch Interface
     */
    virtual void init();

    /**
     * @brief preExecute Funktion, welche ausgefueht wird bevor das Spiel beginnt. Vererbung durch Interface
     */
    virtual void preExecute();

    /**
     * @brief postExecute Funktion, welche ausgefueht wird nachdem ein Spiel beendet wurde, Vererbung durch Interface
     */
    virtual void postExecute();

    /**
     * @brief lock Funktion, um das Spielerinfowidget zu sperren.Keine Klicks mehr zulaessig
     */
    void lock();
    /**
     * @brief unlock Funktion, um das Spielerinfowidget zu entsperren
     */
    void unlock();

    /**
     * @brief lockDisplaySp1 funktion um Spieler1-Infodisplay zu sperren
     */
    void lockDisplaySp1();

    /**
     * @brief lockDisplaySp2 funktion um Spieler2-Infodisplay zu sperren
     */
    void lockDisplaySp2();

    /**
     * @brief visitorMode Funktion, welche angibt wie sich das widget im Visitormode zu verhalten hat
     */
    void visitorMode();

    /**
     * @brief initPlayer Funktion, um die Spieler zu initialisieren
     * @param player1   Klasse Spieler1
     * @param player2   Klasse Spieler2
     */
    void initPlayer(Spieler* player1,Spieler* player2);

    /**
     * @brief changePlayer funktion um im Widget den Spieler zu wechseln
     * @param currentPlayer Aktueller Spieler der an der Reihe ist
     * @param round         Aktuelle Runde
     * @param lastMove      Letzter Zug
     */
    void changePlayer(Spieler* currentPlayer, unsigned short round, string lastMove);

    /**
     * @brief initPlayerDisplays Funktion, um die Spielerdisplays zu initialisieren
     * @param player1    Klasse Spieler1
     * @param player2    Klasse Spieler2
     */
    void initPlayerDisplays(Spieler* player1,Spieler* player2);

    /**
     * @brief initfirstPlayer Funktion, um den ersten Spieler zu initialisieren
     * @param firstPlayer   Klasse Spieler
     */
    void initfirstPlayer(Spieler* firstPlayer);

    /**
     * @brief setSysMsg Funktion um Systemmeldungen anzuzeigen
     * @param msg   Nachricht als String
     */
    void setSysMsg(string msg);
    ~GameInfo();

private slots:
    /**
     * @brief on_btnlooseleft_clicked Funktion, wenn auf aufgeben gelickt wird von Spieler1
     */
    void on_btnlooseleft_clicked();

    /**
     * @brief on_btnlooseright_clicked Funktion, wenn auf aufgeben gelickt wird von Spieler1
     */
    void on_btnlooseright_clicked();

    /**
     * @brief on_timeChange Funktion, die die Zeit des jeweiligen Spielers aendert
     */
    void on_timeChange();

    /**
     * @brief on_pbvmexit_clicked Funktion, um den Zuschauermodus zu verlassen wenn auf den Button Ende geklickt wird
     */
    void on_pbvmexit_clicked();

signals:
    /**
     * @brief loose Signal, welches Informationen an das System gibt, wenn jemand aufgibt
     * @param winner    Klasse Spieler, der gewonnen hat
     */
    void loose(Spieler* winner,bool);

    /**
     * @brief exitVmMode Signal, welches beim verlassen des Zuschauermodus getriggert wird
     */
    void exitVmMode();

private:
     //QPixmap imgRed;
     //QPixmap imgYellow;

     Spieler *player1;
     Spieler *player2;
     Spieler *currentPlayer;

     /**
      * @brief timer Thread fuer die Zeitanzeige des jeweiligen spielers laufen zu lassen
      */
     QThread *timer;

     /**
      * @brief timerWorker Worker fuer o.g. Thread
      */
     Timer4Win *timerWorker;

     /**
      * @brief gifRedMovie Objekt, mit welchem ein GIF angespielt werden kann zu anzeige wer an der Reihe ist
      */
     QMovie* gifRedMovie;

     /**
      * @brief gifYellowMovie Objekt, mit welchem ein GIF angespielt werden kann zu anzeige wer an der Reihe ist
      */
     QMovie* gifYellowMovie;

     /**
      * @brief timePlayer1 Zeit des Spieler1
      */
     unsigned long timePlayer1;

     /**
      * @brief timePlayer2 Zeit des Spieler2
      */
     unsigned long timePlayer2;
     Ui::gameinfoUi *ui;

     /**
      * @brief START_POSITION_X Konstante fuer Startposition auf dem Bildschirm (X-Position)
      */
     static const int START_POSITION_X = 0;

     /**
      * @brief START_POSITION_Y Konstante fuer Startposition auf dem Bildschirm (Y-Position)
      */
     static const int START_POSITION_Y = 0;

     /**
      * @brief setLastMove Funktion, um den Letzten Wurf anzuzeigen
      * @param move String mit Zeile und Spalte
      */
     void setLastMove(string move);

     /**
      * @brief setRound Funktion, um aktuelle Runde anzuzeigen
      * @param round aktuelle Runde
      */
     void setRound(unsigned short round);

     /**
      * @brief initPlayerDisplays interne Funktion um Playerdisplays zu initialisieren
      */
     void initPlayerDisplays();

     /**
      * @brief setTimePlayer1 Funktion, um Spieler1 Zeit anzuzeigen
      */
     void setTimePlayer1();

     /**
      * @brief setTimePlayer2 Funktion, um Spieler2 Zeit anzuzeigen
      */
     void setTimePlayer2();

     /**
      * @brief clearTimePlayer1 Funktion, um Zeit von Spieler1 zu loeschen
      */
     void clearTimePlayer1();

     /**
      * @brief clearTimePlayer2 Funktion, um Zeit von Spieler2 zu loeschen
      */
     void clearTimePlayer2();

     /**
      * @brief convertMillToTime Funktion um Zeit von Millisekunden in Format HH:MM:SS zu konvertieren
      * @param ms
      * @return
      */
     string convertMillToTime(unsigned long ms);
};

#endif // GAMEINFO_H
