#include "../h/net/msg/remotemove.h"
#include <sstream>

RemoteMove::RemoteMove(unsigned short column)
{
    this->column = column;
}

RemoteMove::~RemoteMove()
{
    //--> kein new
}

unsigned short RemoteMove::getColumn() const
{
    return column;
}

void RemoteMove::setColumn(unsigned short value)
{
    column = value;
}

ostream& operator<<(ostream& out, RemoteMove& object){
    out << object.column;
    return out;
}

istream& operator>>(istream& in, RemoteMove& object ){
    in >> object.column;
    return in;
}

string RemoteMove::toString()
{
    ostringstream o;
    o << "Column: " << column << endl;
    return o.str();
}

