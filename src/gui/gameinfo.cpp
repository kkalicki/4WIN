#include "../h/gui/gameinfo.h"



GameInfo::GameInfo(QWidget *parent) : QWidget(parent),
    ui(new Ui::gameinfoUi)
{
    ui->setupUi(this);
    init();
}

void GameInfo::init()
{
    this->move(START_POSITION_X,START_POSITION_Y);
    this->setFixedSize(this->size().width(),this->size().height());
    lock();
}

void GameInfo::preExecute()
{
    unlock();
}

void GameInfo::postExecute()
{
    lock();
}

void GameInfo::lock()
{
    ui->btnlooseleft->setEnabled(false);
    ui->btnlooseright->setEnabled(false);
}

void GameInfo::unlock()
{
    ui->btnlooseleft->setEnabled(true);
    ui->btnlooseright->setEnabled(true);

}

GameInfo::~GameInfo()
{

}
