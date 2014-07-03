#ifndef LOGINREQUEST_H
#define LOGINREQUEST_H

#include "../h/net/netmessage.h"
#include <string>

using namespace std;

/**
 * @brief The LoginRequest class
 * Klasse, die eine Netzwerknachricht darstellt, um sich an einem offenen Spiel anzumelden
 */
class LoginRequest //: public NetworkMessage
{
public:
    /**
     * @brief LoginRequest Konstruktor
     * @param playerName Spielername, von demjenigen der sich anmelden will
     */
    LoginRequest(string playerName="Player");
    ~LoginRequest();

    /**
     * @brief getPlayerName Getter fuer Spielername
     * @return Spielername
     */
    string getPlayerName() const;

    /**
     * @brief setPlayerName Setter fuer Spielername
     * @param value Wert
     */
    void setPlayerName(string value);

    /**
     * @brief operator <<   Funktion, zum ueberladen des << Operators
     * @param out           OstreamObjekt
     * @param object        LoginRequestObjekt
     * @return              ostream mit Loginrequest
     */
    friend ostream& operator<< (ostream& out, LoginRequest& object);
    /**
     * @brief operator >>   Funktion, zum ueberladen des >> Operators
     * @param in            IstreamObjekt
     * @param object        LoginRequestObjekt
     * @return              Istream mit Loginrequest
     */
    friend istream& operator>>(istream& in, LoginRequest &object );

    /**
     * @brief fromCsvString nicht verwendet
     * @param csv
     */
    void fromCsvString(string csv);

    /**
     * @brief toString Funktion, um diese Klasse als String zu repraesentieren
     * @return Klasse als String
     */
    string toString();

private:
    /**
     * @brief playerName Spielername
     */
    string playerName;
};

#endif // LOGINREQUEST_H
