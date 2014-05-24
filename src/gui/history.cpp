#include "../h/gui/history.h"

History::History(QWidget *parent)  : QWidget(parent),
    ui(new Ui::historyUi)
{
    ui->setupUi(this);
    init();
}


History::~History()
{

}


void History::init()
{
    this->move(START_POSITION_X,START_POSITION_Y);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint);
    this->setFixedSize(this->size().width(),this->size().height());
}


void History::preExecute()
{

}


void History::postExecute()
{

}
