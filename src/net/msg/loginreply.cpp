#include "../h/net/msg/loginreply.h"
#include "../h/net/netmessage.h"

LoginReply::LoginReply() //: NetworkMessage(LOGINREPLY)
{
    //this->spieler = new Spieler();
}

LoginReply::LoginReply(Spieler spieler) //: NetworkMessage(LOGINREPLY)
{
    this->spieler = spieler;
}

LoginReply::~LoginReply()
{
   //kein new
}

Spieler LoginReply::getSpieler() const
{
    return spieler;
}

void LoginReply::setSpieler(Spieler value)
{
    spieler = value;
}

ostream& operator<<(ostream& out, LoginReply& object) {

    out << object.spieler;
    return out;
}

istream& operator>>(istream & in, LoginReply& object)
{
    in >> object.spieler;
    return in;
}
