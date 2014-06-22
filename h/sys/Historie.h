#ifndef HISTORIE_H
#define HISTORIE_H
#include <../h/sys/HisEintrag.h>
#include <vector>
#include <string>

using namespace std;

class Historie{
public:
    Historie();
    Historie(const Historie& rhs);
    ~Historie();
    void hinzufuegenEintrag(HisEintrag* hisEintrag);
    void loeschenEintrag(int index);
    int  loeschenEintrag(HisEintrag* hisEintrag);
    void loeschenHistorie();
    HisEintrag*  getEintrag(int index);
    HisEintrag* getLetztenEintrag();
    vector<HisEintrag> getEintraegeAb(HisEintrag* hisEintrag);
    friend ostream& operator<<(ostream& out, Historie& object);
    string toString();
    vector<HisEintrag> *getHisList() const;
    void setHisList(vector<HisEintrag> *value);

private:
    vector<HisEintrag>* hisList;
};

#endif // HISTORIE_H
