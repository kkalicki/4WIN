#ifndef NETMOVE_H
#define NETMOVE_H

#include <string>
using namespace std;

class RemoteMove{
public:
    RemoteMove(unsigned short column=0);
    ~RemoteMove();

    unsigned short getColumn() const;
    void setColumn(unsigned short value);

    friend ostream& operator<< (ostream& out, RemoteMove& object);
    friend istream& operator>>(istream& in, RemoteMove& object);

    string toString();

private:
    unsigned short column;
};

#endif // NETMOVE_H
