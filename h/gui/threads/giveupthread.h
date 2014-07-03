#ifndef GIVEUPTHREAD_H
#define GIVEUPTHREAD_H
#include "../h/sys/Spieler.h"
#include   <QObject>

/**
 * @brief The GiveUpThread class
 * Klasse, mit deren Hilfe die GUI aktualisiert wird, wenn ein Gegner im Netzwerkmodus aufgegeben hat!
 * Die Klasse triggert das Signal an die GUI und. Dies muss in einem eigenen Thread passieren, da nicht von dem Netwzerkthread direkt auf die GUI
 * zugefriffen werden darf!
 */
class GiveUpThread : public QObject{
    Q_OBJECT
public:
    /**
     * @brief GiveUpThread
     * Konstruktor der Klasse
     * @param remotePlayer Spieler der aufgegeben hat
     * @param giveUp       Parameter, der für die GUI zwingend erforderlich ist.
     */
    GiveUpThread(Spieler* remotePlayer, bool giveUp=false);
public slots:
    /**
     * @brief process
     * Funktion die in dem Thread ausgeführt wird, um das Signal "Aufgeben" an die GUI weiter zu leiten
     */
    void process();
signals:
    /**
     * @brief updateGui
     * Signal, welches die Funktion, Aufgeben in der GUI ausloest
     * @param remotePlayer  Spieler der aufgegeben hat
     * @param giveUp        Parameter, der für die GUI zwingend erforderlich ist.
     */
    void updateGui(Spieler* remotePlayer, bool giveUp);
private:
    /**
     * @brief remotePlayer
     * Spieler der aufgegeben hat
     */
    Spieler* remotePlayer;
    /**
     * @brief giveUp
     * flag, welches vom remote PC gesendet wird.
     */
    bool giveUp;
};

#endif // GIVEUPTHREAD_H
