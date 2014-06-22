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
    int isActive;
};

string RemoteGamesListItem::toString()
{
    string activeString = "";

    if(isActive)
        activeString = "Nur Zuschauen!";

    ostringstream o;
    o << "IP: "<< ipAdress << " NAME: " << name << " [" << rows << "-" << columns << "] "<< activeString << flush;
    return o.str();
}

Q_DECLARE_METATYPE(RemoteGamesListItem)

#endif // REMOTEGAMESLISTITEM_H
