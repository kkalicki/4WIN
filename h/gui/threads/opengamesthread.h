#ifndef OPENGAMESTHREAD_H
#define OPENGAMESTHREAD_H

#include <../h/net/msg/helloreply.h>
#include   <QObject>

/**
 * @brief The OpenGameThread class
 * Klasse, mit deren Hilfe die GUI aktualisiert wird, wenn ein Spieler alle offnen Spiele sucht
 * Die Klasse triggert das Signal an die GUI und. Dies muss in einem eigenen Thread passieren, da nicht von dem Netwzerkthread direkt auf die GUI
 * zugefriffen werden darf!
 */
class OpenGameThread : public QObject
{
   Q_OBJECT

public:
    /**
     * @brief OpenGameThread
     * @param incomingGame      Nachricht, welche zurueck kommt mit allen Informationen zu einem offenen Spiel
     * Konstruktor der Klasse
     */
    OpenGameThread(HelloReply incomingGame);
public slots:
    /**
     * @brief process
     * Funktion die in dem Thread ausgeführt wird, um die Informationen des offen Spiels an die GUI weiter zu leiten
     */
    void process();
signals:
    /**
     * @brief updateGui
     * @param incomingGame Informationen eines offenen Spiels
     * Signal, welches die Funktion on_incomingGames in dem SettingsFormular aufruft
     */
    void updateGui(HelloReply* incomingGame);

private:
    /**
     * @brief incomingGame
     * Informationen eines offenen Spiels
     */
    HelloReply incomingGame;
};
#endif // OPENGAMESTHREAD_H
