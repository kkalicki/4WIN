#ifndef HISTORIE_H
#define HISTORIE_H
#include <../h/sys/HisEintrag.h>
#include <vector>
#include <string>

using namespace std;

class Historie{
public:
    Historie();
    ~Historie();
    void hinzufuegenEintrag(HisEintrag* hisEintrag);
    void loeschenEintrag(int index);
    int  loeschenEintrag(HisEintrag* hisEintrag);
    void loeschenHistorie();
    HisEintrag*  getEintrag(int index);
    HisEintrag* getLetztenEintrag();
    vector<HisEintrag> getEintraegeAb(HisEintrag* hisEintrag);

    string toString();
private:
    vector<HisEintrag>* hisList;
};

#endif // HISTORIE_H
