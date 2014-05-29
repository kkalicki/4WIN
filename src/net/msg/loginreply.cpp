#include "../h/net/msg/loginreply.h"

#include "../h/net/netmessage.h"
LoginReply::LoginReply() //: NetworkMessage(LOGINREPLY)
{
    //do Nothing...
}

LoginReply::LoginReply(const Spieler& spieler) //: NetworkMessage(LOGINREPLY)
{
    this->spieler = spieler;
}

LoginReply::~LoginReply()
{
    //nix implementieren... kein new
}

Spieler LoginReply::getSpieler() const
{
    return spieler;
}

void LoginReply::setSpieler(const Spieler &value)
{
    spieler = value;
}
