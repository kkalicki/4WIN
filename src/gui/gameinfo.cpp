#include "../h/gui/gameinfo.h"



GameInfo::GameInfo(QWidget *parent) : QWidget(parent),
    ui(new Ui::gameinfoUi)
{
    ui->setupUi(this);
    this->move(START_POSITION_X,START_POSITION_Y);
    this->setFixedSize(this->size().width(),this->size().height());
    lock();

    /*QPalette p(palette());
    p.setColor(QPalette::Ba);
    this->setAutoFillBackground(false);
    this->setPalette(p);*/

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
