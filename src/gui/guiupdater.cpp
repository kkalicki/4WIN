#include "../h/gui/guiupdater.h"


GuiUpdater::GuiUpdater(unsigned short column, int row)
{
    this->column = column;
    this->row = row;
}

void GuiUpdater::process()
{
     emit updateGui(column, row);
}
