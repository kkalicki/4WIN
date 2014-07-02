#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <string>
#include "../h/sys/Konstanten.h"
#include "../h/net/msg/helloreply.h"

using namespace std;

enum GameMode {SVS,SVC,CVC};
enum NetworkMode {LOCAL,OPEN,JOIN};
enum Level {EASY=3,MEDIUM=6,HARD=10,ULTIMATE=12};

/**
 * @brief The GameSettings class
 * Klasse, Welche Informationen beinhaltet um ein Spiel zu starten. Hier werden die Einstellungen des Settingformular gespeichert und an das System gegeben.
 */
class GameSettings{
public:
    /**
     * @brief GameSettings  Konstruktor der Klasse
     * @param mode          In welchem Spielmodus gespielt werden soll (SVS,SVC,CVC)
     * @param level         Schwierigkeitsgrad fuer Computerspieler
     * @param player1Name   Name Spieler1
     * @param player2Name   Name Spieler2
     * @param bordId        ID des Spiels fuere Zuschauermodus
     * @param bordRows      Anzahl der Zeilen die eingestellt wurden
     * @param bordColumns   Anzahl der Spalten die eingestellt wurden
     * @param cellSize      Groeße des Spielfelds
     * @param networkMode   Weche art von Netzwerkmodus (LOCAL, OPEN, JOIN)
     * @param visitorMode   Auswahl, ob Visitormodus aktiv ist
     */
    GameSettings(GameMode mode=SVS,Level level=MEDIUM, string player1Name="Player1", string player2Name="Player2", int bordId=4711,
                 unsigned short bordRows=Y, unsigned short bordColumns=X, unsigned short cellSize=CELL_SIZE, NetworkMode networkMode=LOCAL, bool visitorMode=false);
    ~GameSettings();

    /**
     * @brief getMode Getter fuer Modus
     * @return Modus
     */
    GameMode getMode() const;

    /**
     * @brief setMode Setter fuer Modus
     * @param value Wert
     */
    void setMode(const GameMode &value);

    /**
     * @brief getPlayer1Name Getter fuer Spieler1name
     * @return Name Spieler1
     */
    string getPlayer1Name() const;

    /**
     * @brief setPlayer1Name Setter fuer Spieler1name
     * @param value Wert
     */
    void setPlayer1Name(const string &value);

    /**
     * @brief getPlayer2Name Getter fuer Spieler2name
     * @return Name Spieler2
     */
    string getPlayer2Name() const;

    /**
     * @brief setPlayer2Name Setter fuer Spieler2name
     * @param value Wert
     */
    void setPlayer2Name(const string &value);

    /**
     * @brief getBordId Getter fuer BordID
     * @return Id des Bords
     */
    int getBordId() const;

    /**
     * @brief setBordId Setter fuer BordID
     * @param value Wert
     */
    void setBordId(int value);

    /**
     * @brief getBordRows Getter fuer Zeilen
     * @return Anzahl der Zeilen
     */
    unsigned short getBordRows() const;

    /**
     * @brief setBordRows Setter fuer Spalten
     * @param value Wert
     */
    void setBordRows(unsigned short value);

    /**
     * @brief getBordColumns Getter fuer Spalten
     * @return Anzahl der Spalten
     */
    unsigned short getBordColumns() const;

    /**
     * @brief setBordColumns Setter fuer Spalten
     * @param value Wert
     */
    void setBordColumns(unsigned short value);

    /**
     * @brief getCellSize Getter fuer Zellengroesse
     * @return Zellengroesse
     */
    unsigned short getCellSize() const;

    /**
     * @brief setCellSize Setter fuer Zellengroesse
     * @param value Wert
     */
    void setCellSize(unsigned short value);

    /**
     * @brief getNetworkMode Getter fuer Netzwerkmodus
     * @return Modus
     */
    NetworkMode getNetworkMode() const;

    /**
     * @brief setNetworkMode Setter fuer Netzwerkmodus
     * @param value Wert
     */
    void setNetworkMode(const NetworkMode &value);

    /**
     * @brief getRemoteIp Getter fuer RemoteIp
     * @return Ip des Remoteplayers
     */
    string getRemoteIp() const;

    /**
     * @brief setRemoteIp Setter fuer RemoteIp
     * @param value Wert
     */
    void setRemoteIp(const string &value);

    /**
     * @brief getVisitorMode Getter fuer Visitormodus
     * @return true/false
     */
    bool getVisitorMode() const;
    /**
     * @brief setVisitorMode Setter fuer Visitormodus
     * @param value Wert
     */
    void setVisitorMode(bool value);

    /**
     * @brief getGameId Getter fuer SpielID
     * @return Id des Spiels
     */
    int getGameId() const;

    /**
     * @brief setGameId Setter fuer SpielID
     * @param value Wert
     */
    void setGameId(int value);

    /**
     * @brief getLevel Getter fuer Schwierigkeitsgrad
     * @return Schwierigkeitsgrad
     */
    Level getLevel() const;

    /**
     * @brief setLevel Setter fuer Schwierigkeitsgrad
     * @param value Wert
     */
    void setLevel(const Level &value);

private:
    /**
     * @brief mode Spielmodus
     */
    GameMode mode;

    /**
     * @brief level Schwierigkeitsgrad
     */
    Level level;

    /**
     * @brief player1Name Spieler1name
     */
    string player1Name;

    /**
     * @brief player2Name Spieler2name
     */
    string player2Name;

    /**
     * @brief bordId ID
     */
    int bordId;

    /**
     * @brief bordRows Anzahl der Zeilen
     */
    unsigned short bordRows;

    /**
     * @brief bordColumns Anzahl der Spalten
     */
    unsigned short bordColumns;

    /**
     * @brief cellSize Groesse der Zelle
     */
    unsigned short cellSize;

    /**
     * @brief networkMode Art des Spielmodus
     */
    NetworkMode networkMode;

    /**
     * @brief gameId SpielID
     */
    int gameId;

    /**
     * @brief visitorMode Visitormodus aktivieren
     */
    bool visitorMode;

    /**
     * @brief remoteIp RemoteIpadresse
     */
    string remoteIp;
};

#endif // GAMESETTINGS_H






