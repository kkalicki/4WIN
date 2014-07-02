#ifndef LOGINREPLY_H
#define LOGINREPLY_H

#include "../h/net/netmessage.h"
#include "../h/sys/Spieler.h"
#include <string>

/**
 * @brief The LoginReply class
 * Klasse, um auf ein LoginRequest zu antworten. dient dazu um Daten zu uebertragen, wenn ein Spieler eine anfrage zum Anmelden gestellt hat
 */
class LoginReply //: public NetworkMessage
{
public:
    /**
     * @brief LoginReply Konstruktor
     */
    LoginReply();

    /**
     * @brief LoginReply Konstruktor
     * @param spieler eigenen Spieler zurueckgeben, damit Spiel welches sich anmelden will, die eigenen Daten bekommt
     */
    LoginReply(Spieler spieler);
    ~LoginReply();

    /**
     * @brief getSpieler Getter fuer Spieler
     * @return eigener Spieler
     */
    Spieler getSpieler() const;

    /**
     * @brief setSpieler Setter fuer Spieler
     * @param value Wert
     */
    void setSpieler(Spieler value);
    /**
     * @brief operator <<   Funktion, zum ueberladen des << Operators
     * @param out           OstreamObjekt
     * @param object        LoginReplyObjekt
     * @return              ostream mit Loginreply
     */
    friend ostream& operator<<(ostream& out, LoginReply& object);

    /**
     * @brief operator >>   Funktion, zum ueberladen des >> Operators
     * @param in            IstreamObjekt
     * @param object        LoginReplyObjekt
     * @return              Istream mit LoginReply
     */
    friend istream& operator>>(istream& in, LoginReply& object);

    /**
     * @brief fromCsvString Funktion, um Serialisiertes Objekt in eine Instanz zu konvertieren
     * @param csv CSV-String
     */
    void fromCsvString(string csv);

    /**
     * @brief toString Funktion, um diese Klasse als String zu repraesentieren
     * @return String der Klasse
     */
    string toString();

private:
    /**
     * @brief spieler Spielerobjekt, welches uebertragen wird
     */
    Spieler spieler;
};

#endif // LOGINREPLY_H


