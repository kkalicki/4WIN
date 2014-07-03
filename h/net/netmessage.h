#ifndef NETMESSAGE_H
#define NETMESSAGE_H
#include <iostream>
using namespace std;

enum NetMessageType{NOTYPE=0, LOGINREQUEST=1, LOGINREPLY=2, REMOTEMOVE=3, GIVEUP=4, UDPHELLO=5, HELLOREPLY=6, VISITORPACKAGE=7};

/**
 * @brief The NetworkMessage class
 * Klasse, die die einzelnen Nachrichten als ID sendet. Daran kann erkannt werden, welcher Nachrichtentyp folgt
 */
class NetworkMessage{
public:

    /**
     * @brief NetworkMessage Konstruktor
     * @param msgType Nachrichtentyp zum initialisieren
     */
    NetworkMessage(NetMessageType msgType=NOTYPE);
    ~NetworkMessage();

    /**
     * @brief getId Getter fuer NachrichtenId
     * @return NachrichtenId
     */
    NetMessageType getId() const;

    /**
     * @brief setId Setter fuer NachrichtenId
     * @param value Wert
     */
    void setId(const NetMessageType &value);

    /**
     * @brief toCharArray funktion um Klasse in ein CharArray zu konvertieren
     * @return Array
     */
    char* toCharArray();
    /**
     * @brief fromCharArray Funktion um Klasse von einem Chararray zu laden
     * @param buffer
     */
    void fromCharArray(char* buffer);

    /**
     * @brief operator <<   Funktion, zum ueberladen des << Operators
     * @param out           OstreamObjekt
     * @param object       NetworkMessageObjekt
     * @return              ostream mit NetworkMessage
     */
    friend ostream& operator<< (ostream& out, NetworkMessage& object) {
    out << object.id;
    return out;
    }

    /**
     * @brief operator >>   Funktion, zum ueberladen des >> Operators
     * @param in            IstreamObjekt
     * @param object        NetworkMessageObjekt
     * @return              Istream mit NetworkMessage
     */
    friend istream &operator>>( istream  &input, NetworkMessage& object )
    {
        int type;
        input >> type;

        switch(type)
        {
        case LOGINREQUEST:
            object.id = LOGINREQUEST;
           break;
        case LOGINREPLY:
            object.id = LOGINREPLY;
            break;
        case REMOTEMOVE:
            object.id = REMOTEMOVE;
            break;
        case GIVEUP:
            object.id = GIVEUP;
            break;
        case UDPHELLO:
            object.id = UDPHELLO;
            break;
        case HELLOREPLY:
            object.id = HELLOREPLY;
            break;
        case VISITORPACKAGE:
            object.id = VISITORPACKAGE;
            break;
          default:
            object.id = NOTYPE;
            break;
        }
        return input;
    }


protected:
    /**
     * @brief id Nachrichtentyp
     */
    NetMessageType id;
};

#endif // NETMESSAGE_H
