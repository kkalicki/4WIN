#ifndef LOGINREPLY_H
#define LOGINREPLY_H

#include "../h/net/netmessage.h"
#include "../h/sys/Spieler.h"
#include <string>

class LoginReply //: public NetworkMessage
{
public:
    LoginReply();
    LoginReply(Spieler spieler);
    ~LoginReply();

    Spieler getSpieler() const;
    void setSpieler(Spieler value);

    friend ostream& operator<<(ostream& out, LoginReply& object);
    friend istream& operator>>(istream& in, LoginReply& object);

    string toString();

private:
    Spieler spieler;
};

#endif // LOGINREPLY_H


