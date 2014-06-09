#ifndef REMOTEGAMESLISTITEM_H
#define REMOTEGAMESLISTITEM_H

#include <QMetaType>
#include <string>

using namespace std;

class RemoteGamesListItem
{
public:
    RemoteGamesListItem(){}
    ~RemoteGamesListItem(){}
    string toString();
    string ipAdress;
    string name;
    unsigned int rows;
    unsigned int columns;
};

string RemoteGamesListItem::toString()
{
    ostringstream o;
    o << "IP: "<< ipAdress << " NAME: " << name << " [" << rows << "-" << columns << "]" << flush;
    return o.str();
}

Q_DECLARE_METATYPE(RemoteGamesListItem)

#endif // REMOTEGAMESLISTITEM_H
