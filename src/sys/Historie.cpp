#include "../h/sys/Historie.h"
#include <sstream>


Historie::Historie()
{
    this->hisList = new vector<HisEintrag>();
}

Historie::~Historie()
{
    loeschenHistorie();
    delete hisList;
}

void Historie::hinzufuegenEintrag(HisEintrag* hisEintrag)
{
    hisList->push_back(*hisEintrag);
}


void Historie::loeschenEintrag(int index)
{
    vector<HisEintrag>::iterator i = hisList->begin() + index;
    hisList->erase(i);
}

int Historie::loeschenEintrag(HisEintrag* hisEintrag)
{
    //vector<HisEintrag>::iterator i = find(hisList.begin(), hisList.end(), hisEintrag);
    //hisList.erase(i);
}

void Historie::loeschenHistorie()
{
    hisList->clear();
}

HisEintrag* Historie::getEintrag(int index)
{
    if(hisList->size() > (unsigned long)index)
      return &hisList->at(index);

    return NULL;
}

HisEintrag* Historie::getLetztenEintrag()
{
    if(hisList->size() > 0)
       return &hisList->at(hisList->size() - 1);

    return NULL;
}

vector<HisEintrag> Historie::getEintraegeAb(HisEintrag *hisEintrag)
{
    //noch zu implementieren..
}

string Historie::toString()
{
    int s = hisList->size();
    ostringstream o;
    for(int i = 0; i < s; i++) {
        HisEintrag out = hisList->at(i);
        o << out.toString() << endl;
    }
    return o.str();
}

ostream& operator<<(ostream& out, Historie& object) {
    out << object.toString();
    return out;
}
