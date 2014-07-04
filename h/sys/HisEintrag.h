#ifndef HISEINTRAG_H
#define HISEINTRAG_H
#include "../h/sys/Spieler.h"
#include <ctime>
#include <string>
/**
 * @brief The HisEintrag class
 * Klasse, die einen HistorieEintrag im System repraesentiert.
 */
class HisEintrag{
public:
    /**
     * HisEintrag   Konstruktor
     */
    HisEintrag();
    /**
     * @HisEintrag  Konstruktor
     * @param spieler Spieler, der diesem Eintrag zugeordnet werden soll
     * @param zeile   Zeile in die geworfen wurde
     * @param spalte  Spalte in die geworfen wurde
     * @param runde   Aktuelle Runde
     */
    HisEintrag(Spieler* spieler, unsigned short zeile=0, unsigned short spalte=0, unsigned short runde=0);
    ~HisEintrag();

    /**
     * getSpieler Getter fuer Spieler
     * @return Spieler
     */
    Spieler* getSpieler() const;

    /**
     * setSpieler Setter fuer Spieler
     * @param value Wert
     */
    void setSpieler(Spieler* value);

    /**
     * getZeile Getter fuer Zeile
     * @return Zeile
     */
    unsigned short getZeile() const;

    /**
     * setZeile Setter fuer Zeile
     * @param value Wert
     */
    void setZeile(unsigned short value);

    /**
     * getSpalte Getter fuer Spalte
     * @return Spalte
     */
    unsigned short getSpalte() const;

    /**
     * setSpalte    Setter fuer Spalte
     * @param value wert
     */
    void setSpalte(unsigned short value);

    /**
     * getTimestamp Getter fuer Timestamp
     * @return Timestamp
     */
    time_t getTimestamp() const;

    /**
     * setTimestamp Setter fuer Timestamp
     * @param value Wert
     */
    void setTimestamp(const time_t &value);

    /**
     * zeitStempel Getter fuer den Zeitstempel als String
     * @return Timestamp als String
     */
    string zeitStempel();

    /**
    * getRunde Getter fuer Runde
    * @return Runde
    */
    unsigned short getRunde() const;

    /**
     * setRunde Setter fuer Runde
     * @param value Wert
     */
    void setRunde(unsigned short value);

    /**
     * fromCsvString        Funktion, um das Objekt von einem CSV-String zu initialisieren
     * @param csvString     CSV-String
     */
    void fromCsvString(string csvString);

    /**
     * toString Funktion, um das Objekt als String zurueckzugeben
     * @return Objekt als String
     */
    string toString();

    /**
     * @brief operator <<  Funktion, zum ueberladen des << Operators
     * @param out          OstreamObjekt
     * @param object       HisEintragObjekt
     * @return             ostream mit HisEintrag
     */
    friend ostream& operator<<(ostream& out, HisEintrag& object);

    /**
     * @brief operator >>   Funktion, zum ueberladen des >> Operators
     * @param in            IstreamObjekt
     * @param object        HisEintragObjekt
     * @return              Istream mit HisEintrag
     */
    friend istream& operator>>(istream& in, HisEintrag &object );

private:
    /**
     * spieler Spieler fuer den Eintrag
     */
    Spieler* spieler;
    /**
     * zeile Zeile in die geworfen wurde
     */
    unsigned short zeile;

    /**
     * spalte Spalte in die geworfen wurde
     */
    unsigned short spalte;

    /**
     * runde Aktuelle Runde
     */
    unsigned short runde;

    /**
     * timestamp Timestamp
     */
    time_t timestamp;

};

#endif // HISEINTRAG_H
