#ifndef HELLOREPLY_H
#define HELLOREPLY_H

#include <string>
#include <sstream>

using namespace std;

class HelloReply{

public:
    HelloReply();
    HelloReply(string ipAdress, string name, unsigned int rows, unsigned int columns);
    ~HelloReply();
    string getIpAdress() const;
    void setIpAdress(const string &value);

    string getName() const;
    void setName(const string &value);

    unsigned int getRows() const;
    void setRows(unsigned int value);

    unsigned int getColumns() const;
    void setColumns(unsigned int value);

    friend ostream& operator<<(ostream& out, HelloReply& object);
    friend istream& operator>>(istream& in, HelloReply& object);

    void fromCsvString(string csv);
    string toString();
private:
    string ipAdress;
    string name;
    unsigned int rows;
    unsigned int columns;
};
#endif // HELLOREPLY_H
