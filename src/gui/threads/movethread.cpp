#include "../h/gui/threads/movethread.h"


MoveThread::MoveThread(unsigned short column, int row)
{
    this->column = column;
    this->row = row;
}

void MoveThread::process()
{
     emit updateGui(column, row);
}
