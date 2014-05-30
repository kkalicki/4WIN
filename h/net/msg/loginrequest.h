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

    friend ostream& operator<< (ostream& out, LoginRequest& object);
    friend istream& operator>>(istream& in, LoginRequest &object );

    string toString();

private:
    string playerName;
};

#endif // LOGINREQUEST_H
