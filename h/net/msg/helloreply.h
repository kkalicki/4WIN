#ifndef HELLOREPLY_H
#define HELLOREPLY_H

#include <string>
#include <sstream>

using namespace std;

/**
 * @brief The HelloReply class
 * Klassen, die eine Netzwerknachricht darstellt, um auf eine Anfrage zu antworten, ob ein Spiel offen ist
 */
class HelloReply{

public:
    /**
     * @brief HelloReply Konstruktor
     */
    HelloReply();

    /**
     * @brief HelloReply Konstruktor
     * @param ipAdress  eigene Ip-Adresse
     * @param name      eigener Name
     * @param rows      anzahl der Zeilen
     * @param columns   anzahl der Spalten
     * @param isActive  Flag,ob Spiel bereits aktiv ist
     * @param gameId    SpielId
     */
    HelloReply(string ipAdress, string name, unsigned int rows, unsigned int columns, int isActive, int gameId);
    ~HelloReply();

    /**
     * @brief getIpAdress Getter fuer IpAdresse
     * @return IpAdresse
     */
    string getIpAdress() const;

    /**
     * @brief setIpAdress Setter fuer IpAdresse
     * @param value Wert
     */
    void setIpAdress(const string &value);

    /**
     * @brief getName Getter fuer Name
     * @return Name
     */
    string getName() const;

    /**
     * @brief setName Setter fuer Name
     * @param value Wert
     */
    void setName(const string &value);

    /**
     * @brief getRows getter fuer Zeilen
     * @return Zeilen
     */
    unsigned int getRows() const;

    /**
     * @brief setRows Setter fuer Zeilen
     * @param value Wert
     */
    void setRows(unsigned int value);

    /**
     * @brief getColumns Getter fuer Spalten
     * @return Spalten
     */
    unsigned int getColumns() const;

    /**
     * @brief setColumns Setter fuer Spalten
     * @param value Wert
     */
    void setColumns(unsigned int value);

    /**
     * @brief getIsActive Getter, ob Spiel aktiv ist
     * @return true/false
     */
    int getIsActive() const;

    /**
     * @brief setIsActive Setter, ob Spiel aktiv ist
     * @param value Wert
     */
    void setIsActive(int value);

    /**
     * @brief getGameId Getter, fuer SpielId
     * @return SpielId
     */
    int getGameId() const;

    /**
     * @brief setGameId Setter, fuer SpielID
     * @param value Wert
     */
    void setGameId(int value);

    friend ostream& operator<<(ostream& out, HelloReply& object);
    friend istream& operator>>(istream& in, HelloReply& object);

    /**
     * @brief fromCsvString funktion um aus dem Serialisiert string ein Objekt zu erstellen
     * @param csv csvString
     */
    void fromCsvString(string csv);

    /**
     * @brief toString Funktion, die diese Klasse als String repraesentiert
     * @return String der Klasse
     */
    string toString();

private:
    /**
     * @brief ipAdress IP-Adresse
     */
    string ipAdress;
    /**
     * @brief name Name des spielers
     */
    string name;

    /**
     * @brief rows anzahl der Zeilen
     */
    unsigned int rows;

    /**
     * @brief columns anzahl der Spalten
     */
    unsigned int columns;

    /**
     * @brief isActive Flag, ob Spiel aktiv ist
     */
    int isActive;

    /**
     * @brief gameId GameId
     */
    int gameId;
};
#endif // HELLOREPLY_H
