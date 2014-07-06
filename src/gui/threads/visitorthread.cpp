#include "../h/gui/threads/visitorthread.h"


VisitorThread::VisitorThread(VisitorPackage vp, int lastround)
{
    this->vp = vp;
    this->lastround = lastround;
}

VisitorThread::~VisitorThread()
{
    //nix..
}

void VisitorThread::process()
{
    for(int i = lastround; i < (int)vp.getHistorie()->getHisList()->size(); i++){
        unsigned short col = vp.getHistorie()->getEintragAt(i)->getSpalte();
        updateGui(col);
    }
    emit finished();
}
