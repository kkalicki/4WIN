#ifndef LOGINREQUEST_H
#define LOGINREQUEST_H

#include "../h/net/netmessage.h"
#include <string>

using namespace std;

class LoginRequest //: public NetworkMessage
{
public:
    LoginRequest(string playerName="Player");
    ~LoginRequest();
    string getPlayerName() const;
    void setPlayerName(const string &value);

    string toString();

    friend ostream& operator<< (ostream& out, LoginRequest& object) {
    out << object.playerName;
    return out;
    }

    friend istream &operator>>( istream  &input, LoginRequest &object )
    {
        input >> object.playerName;
        return input;
    }

private:
    string playerName;
};

#endif // LOGINREQUEST_H
