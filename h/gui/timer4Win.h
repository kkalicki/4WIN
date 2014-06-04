#ifndef TIMER4WIN_H
#define TIMER4WIN_H
#include <QObject>
class Timer4Win : public QObject
{
   Q_OBJECT

public:
   Timer4Win();
   ~Timer4Win();
   void stop();

public slots:
    void process();
private:
    static const unsigned long SLEEP_TIME = 1;
    int isStop;

signals:
    void timeChange();
};

#endif // TIMER4WIN_H
