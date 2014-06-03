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

void LoginRequest::setPlayerName(string value)
{
    playerName = value;
}

char *LoginRequest::toCharArray()
{
   char* buffer = static_cast<char*>(static_cast<void*>(this));
   return buffer;
}

void LoginRequest::fromCharArray(char * buffer)
{
  LoginRequest* temp = static_cast<LoginRequest *>(static_cast<void*>(buffer));
  this->playerName = temp->playerName;
}

ostream& operator<<(ostream& out, LoginRequest& object) {

    out << object.playerName;
    return out;
}

istream& operator>>(istream& in, LoginRequest& object)
{
    in >> object.playerName;
    return in;
}

string LoginRequest::toString()
{
    ostringstream o;
    o << "PlayerName: " << playerName << endl;
}

