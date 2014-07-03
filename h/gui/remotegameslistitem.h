#ifndef REMOTEGAMESLISTITEM_H
#define REMOTEGAMESLISTITEM_H

#include <QMetaType>
#include <string>

using namespace std;

/**
 * @brief The RemoteGamesListItem class
 * Klasse die zur anzeige von Remotegames (offene Spiele zum Beitreten) dient.
 * Diese Klasse wird nur zur Anzeige der Daten in einer QListview benoetigt.
 * Hinter Jedem Eintrag der Liste verbirgt sich diese Klasse.
 */
class RemoteGamesListItem
{
public:
    /**
     * @brief RemoteGamesListItem Konstruktor
     */
    RemoteGamesListItem(){}
    ~RemoteGamesListItem(){}
    /**
     * @brief toString Klasse als String
     * @return String der die Klasse repraesentiert
     */
    string toString();

    /**
     * @brief ipAdress IpAdresse des Remotegames
     */
    string ipAdress;

    /**
     * @brief name Spielername des Spielers der das Spiel eroeffnet hat
     */
    string name;
    /**
     * @brief rows anzahl der Zeilen des Remotegames
     */
    unsigned int rows;

    /**
     * @brief columns Anzahl der Spalten des Remotegames
     */
    unsigned int columns;

    /**
     * @brief isActive Flag,ob das remotegame bereits aktiv ist, dann nur Zuschauermodus moeglich
     */
    int isActive;

    /**
     * @brief gameId ID des Remotegames
     */
    int gameId;
};

string RemoteGamesListItem::toString()
{
    string activeString = "";

    if(isActive)
        activeString = "Nur Zuschauen!";

    ostringstream o;
    o << "IP: "<< ipAdress << " NAME: " << name << " [" << rows << "-" << columns << "] "<< activeString << flush;
    return o.str();
}

Q_DECLARE_METATYPE(RemoteGamesListItem)

#endif // REMOTEGAMESLISTITEM_H
