#ifndef LOGINREPLY_H
#define LOGINREPLY_H

#include "../h/net/netmessage.h"
#include "../h/sys/Spieler.h"

class LoginReply //: public NetworkMessage
{
public:
    LoginReply();
    LoginReply(const Spieler& spieler);
    ~LoginReply();

    Spieler getSpieler() const;
    void setSpieler(const Spieler &value);

    friend ostream& operator<< (ostream& out, LoginReply& object) {
    out << object.spieler;
    return out;
    }

    friend istream &operator>>( istream  &input, LoginReply &object )
    {
        input >> object.spieler;
        return input;
    }

private:
    Spieler spieler;
};

#endif // LOGINREPLY_H


