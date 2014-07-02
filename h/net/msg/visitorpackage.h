#ifndef VISITORPACKAGE_H
#define VISITORPACKAGE_H

#include "../h/sys/Spieler.h"
#include "../h/sys/Historie.h"

/**
 * @brief The VisitorPackage class
 * Klasse, die Informationen beinhaltet um im Zuschauermodus die Zuege druchzufuehren (Netzwerknachricht)
 */
class VisitorPackage{

public:
    /**
      * @brief VisitorPackage Konstruktor
      */
     VisitorPackage();

     /**
     * @brief VisitorPackage Konstruktor
     * @param sp1   Spieler1 als Objekt
     * @param sp2   Spieler2 als Objekt
     * @param historie  Historie als Objekt
     * @param gameId    GameId
     */
    VisitorPackage(Spieler *sp1, Spieler *sp2, Historie *historie, unsigned short gameId);
    ~VisitorPackage();

    /**
     * @brief getGameId Getter fuer GameId
     * @return GameID
     */
    int getGameId() const;

    /**
     * @brief setGameId Setter fuer GameId
     * @param value Wert
     */
    void setGameId(int value);

    /**
     * @brief getSp1 getter fuer Spieler1
     * @return Spieler1
     */
    Spieler getSp1() const;

    /**
     * @brief setSp1 Setter fuer Spieler 1
     * @param value Wert
     */
    void setSp1(const Spieler &value);

    /**
     * @brief getSp2 Getter fuer Spieler2
     * @return Spieler2
     */
    Spieler getSp2() const;

    /**
     * @brief setSp2 Setter fuer Spieler2
     * @param value Wert
     */
    void setSp2(const Spieler &value);

    /**
     * @brief getHistorie Getter fuer Historie
     * @return Historie
     */
    Historie* getHistorie();

    /**
     * @brief setHistorie Setter fuer Historie
     * @param value Wert
     */
    void setHistorie(const Historie &value);

    /**
     * @brief operator <<   Funktion, zum ueberladen des << Operators
     * @param out           OstreamObjekt
     * @param object        VisitorPackageObjekt
     * @return              ostream mit VisitorPackage
     */
    friend ostream& operator<< (ostream& out, VisitorPackage& object);
    /**
     * @brief operator >>   Funktion, zum ueberladen des >> Operators
     * @param in            IstreamObjekt
     * @param object        VisitorPackageObjekt
     * @return              Istream mit VisitorPackage
     */
    friend istream& operator>>(istream& in, VisitorPackage& object);

    /**
     * @brief fromStream Funktion, um Serialisiertes Objekt in ein Objekt zu konvertieren
     * @param stream String
     */
    void fromStream(string stream);

    /**
     * @brief toString Funktion, um Klasse als String zu repraesentieren
     * @return Klasse alsString
     */
    string toString();

private:
    /**
     * @brief gameId SpielId
     */
    unsigned short gameId;

    /**
     * @brief sp1 Spieler 1
     */
    Spieler sp1;

    /**
     * @brief sp2 Spieler 2
     */
    Spieler sp2;

    /**
     * @brief historie Historie
     */
    Historie historie;
};

#endif // VISITORPACKAGE_H
