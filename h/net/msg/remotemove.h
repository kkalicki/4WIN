#ifndef NETMOVE_H
#define NETMOVE_H

#include <string>
using namespace std;

/**
 * @brief The RemoteMove class
 * Klasse, die in einem Netzwerkspiel den Wurf dem GegnerSpiel uebermittelt
 */
class RemoteMove{
public:
    /**
     * @brief RemoteMove Konstruktor
     * @param column Spalte in die geworfen wurde
     */
    RemoteMove(unsigned short column=0);
    ~RemoteMove();

    /**
     * @brief getColumn Getter fuer Spalte
     * @return Spalte
     */
    unsigned short getColumn() const;

    /**
     * @brief setColumn Setter fuer Spalte
     * @param value Wert
     */
    void setColumn(unsigned short value);

    /**
     * @brief operator <<   Funktion, zum ueberladen des << Operators
     * @param out           OstreamObjekt
     * @param object        RemoteMoveObjekt
     * @return              ostream mit RemoteMove
     */
    friend ostream& operator<< (ostream& out, RemoteMove& object);

    /**
     * @brief operator >>   Funktion, zum ueberladen des >> Operators
     * @param in            IstreamObjekt
     * @param object        RemoteMoveObjekt
     * @return              Istream mit RemoteMove
     */
    friend istream& operator>>(istream& in, RemoteMove& object);

    /**
     * @brief toString Funktion, um die Klasse als string zu repraesentieren
     * @return Klasse als String
     */
    string toString();

private:
    /**
     * @brief column Spalte in die geworfen wurde
     */
    unsigned short column;
};

#endif // NETMOVE_H
