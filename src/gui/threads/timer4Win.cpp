
#include "../h/gui/threads/timer4Win.h"

Timer4Win::Timer4Win()
{
isStop = false;
}


Timer4Win::~Timer4Win()
{

}


void Timer4Win::stop()
{
    isStop = true;
}

void Timer4Win::process()
{
    while(!isStop){
        sleep(SLEEP_TIME);
        emit timeChange();
    }
}



