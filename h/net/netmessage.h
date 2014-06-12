#ifndef NETMESSAGE_H
#define NETMESSAGE_H
#include <iostream>
using namespace std;

enum NetMessageType{NOTYPE=0, LOGINREQUEST=1, LOGINREPLY=2, REMOTEMOVE=3, GIVEUP=4, UDPHELLO=5, HELLOREPLY=6};

class NetworkMessage{
public:

    NetworkMessage(NetMessageType msgType=NOTYPE);
    ~NetworkMessage();

    NetMessageType getId() const;
    void setId(const NetMessageType &value);

    char* toCharArray();
    void fromCharArray(char* buffer);

    friend ostream& operator<< (ostream& out, NetworkMessage& object) {
    out << object.id;
    return out;
    }

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
          default:
            break;
        }
        return input;
    }


protected:
    NetMessageType id;
};

#endif // NETMESSAGE_H
