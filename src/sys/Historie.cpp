#include "../h/sys/Historie.h"
#include <sstream>


Historie::Historie()
{
    this->hisList = new vector<HisEintrag>();
}

Historie::Historie(const Historie &rhs)
{
    this->hisList = new vector<HisEintrag>();

    for(int i=0;i<rhs.getHisList()->size(); i++){
        HisEintrag* copyItem = new HisEintrag(rhs.getHisList()->at(i));
        this->hinzufuegenEintrag(*copyItem);
    }
}

Historie &Historie::operator=(const Historie &rhs)
{
    this->hisList = new vector<HisEintrag>();

    for(int i=0;i<rhs.getHisList()->size(); i++){
        HisEintrag* copyItem = new HisEintrag(rhs.getHisList()->at(i));
        this->hinzufuegenEintrag(*copyItem);
    }
    return *this;
}

Historie::~Historie()
{
    loeschenHistorie();
    if(hisList != 0)
    {
        delete hisList;
        hisList = 0;
    }
}

void Historie::hinzufuegenEintrag(const HisEintrag& hisEintrag)
{
    hisList->push_back(hisEintrag);
}


void Historie::loeschenEintrag(int index)
{
    vector<HisEintrag>::iterator i = hisList->begin() + index;
    hisList->erase(i);
}

int Historie::loeschenEintrag(HisEintrag hisEintrag)
{
    //vector<HisEintrag>::iterator i = find(hisList.begin(), hisList.end(), hisEintrag);
    //hisList.erase(i);
}

void Historie::loeschenHistorie()
{
    hisList->clear();
}

HisEintrag* Historie::getEintragAt(int index)
{
    if(hisList->size() > (unsigned long)index)
      return &hisList->at(index);

    return NULL;
}

HisEintrag *Historie::getLetztenEintrag()
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
vector<HisEintrag> *Historie::getHisList() const
{
    return hisList;
}

void Historie::setHisList(vector<HisEintrag> *value)
{
    hisList = value;
}


ostream& operator<<(ostream& out, Historie& object) {
    int s = object.getHisList()->size();
    for(int i = 0; i < s; i++) {
        HisEintrag outitem = object.getHisList()->at(i);
        out << outitem << endl;
    }
    return out;
}
