#include "../h/net/msg/loginrequest.h"
#include <sstream>

LoginRequest::LoginRequest(string playerName) //: NetworkMessage(LOGINREQUEST)
{
    this->playerName = playerName;
}

LoginRequest::~LoginRequest()
{
    //nicht implementiert -> kein new...
}
string LoginRequest::getPlayerName() const
{
    return playerName;
}

void LoginRequest::setPlayerName(const string &value)
{
    playerName = value;
}

string LoginRequest::toString()
{
    ostringstream o;
    o << "PlayerName: " << playerName << endl;
}

