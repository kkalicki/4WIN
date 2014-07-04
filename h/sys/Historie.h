#ifndef HISTORIE_H
#define HISTORIE_H
#include <../h/sys/HisEintrag.h>
#include <vector>
#include <string>

using namespace std;

/**
 * The Historie class
 * Klasse, die eine Historie im System repraesentiert. In der Historie wird der gesamte Spielverlauf gespeichert
 */
class Historie{
public:
    /**
     * Historie Konstruktor
     */
    Historie();

    /**
     * Historie Kopierkonstruktor
     * @param rhs Objekt, welches kopiert werden soll
     */
    Historie(const Historie& rhs);
    ~Historie();

    /**
     * operator = Zuweisungskonstruktor
     * @param rhs   Objekt, welches zugewiesen werden soll
     * @return      zugewiesenes Objekt
     */
    Historie& operator= (Historie const& rhs);

    /**
     * hinzufuegenEintrag Funktion, um einen Eintrag in die Historie einzutragen
     * @param hisEintrag Eintrag, welches hinzugefuegt werden soll
     */
    void hinzufuegenEintrag(const HisEintrag &hisEintrag);

    /**
     * loeschenEintrag Funktion, um einen Historieeintrag an einem bestimmten Index zu löschen
     * @param index Index der geloescht werden soll
     */
    void loeschenEintrag(int index);

    /**
     * loeschenEintrag Funktion, um einen HistorieEintrag zu loeschen
     * @param hisEintrag HisEintrag der geloescht werden soll
     * @return index der geloescht wurde
     */
    int  loeschenEintrag(HisEintrag hisEintrag);

    /**
     * loeschenHistorie Funktion, um die gesamte Historie zu loeschen
     */
    void loeschenHistorie();

    /**
     * getEintragAt Funktion, um einen Eintrag zurueckzugeben
     * @param index Index, welcher Eintrag zurueckgegeben werden soll
     * @return HisEintrag
     */
    HisEintrag*  getEintragAt(int index);

    /**
     * getLetztenEintrag Funktion, um den letzten Eintrag in der Historie zurueckzugeben
     * @return HisEintrag
     */
    HisEintrag* getLetztenEintrag();

    /**
     * getEintraegeAb Funktion, um eine Liste aller Eintraege ab einem bestimmten Objekt zurueckzugeben
     * @param hisEintrag Objekt ab dem die Liste erstellt werden soll
     * @return Liste mit allen Eintraegen ab einem Objekt
     */
    vector<HisEintrag> getEintraegeAb(HisEintrag* hisEintrag);

    /**
     * @brief operator <<   Funktion, zum ueberladen des << Operators
     * @param out           OstreamObjekt
     * @param object        HistorieObjekt
     * @return              ostream mit Historie
     */
    friend ostream& operator<<(ostream& out, Historie& object);

    /**
     * toString Funktion, um das Objekt als String zurueckzugeben
     * @return Objekt als String
     */
    string toString();

    /**
     * getHisList Funktion, um die komplette Historie als Liste zurueckzugeben
     * @return Historie
     */
    vector<HisEintrag> *getHisList() const;

    /**
     * setHisList   Setter fuer HisListe
     * @param value
     */
    void setHisList(vector<HisEintrag> *value);

private:
    /**
     * hisList Vector in dem die HistorienEintraege gespeichert werden
     */
    vector<HisEintrag>* hisList;
};

#endif // HISTORIE_H
