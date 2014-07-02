#ifndef VISITORTHREAD_H
#define VISITORTHREAD_H

#include <QObject>
#include "../h/net/msg/visitorpackage.h"
class VisitorThread : public QObject
{
   Q_OBJECT

public:
   VisitorThread(VisitorPackage vp, int lastround);
   ~VisitorThread();

public slots:
    void process();

private:
    VisitorPackage vp;
    int lastround;
signals:
   void updateGui(unsigned short col);
};

#endif // VISITORTHREAD_H
