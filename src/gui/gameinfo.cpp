#include "../h/gui/gameinfo.h"



GameInfo::GameInfo(QWidget *parent) : QWidget(parent),
    ui(new Ui::gameinfoUi)
{
    ui->setupUi(this);
    this->move(START_POSITION_X,START_POSITION_Y);
    this->setFixedSize(this->size().width(),this->size().height());

    /*QPalette p(palette());
    p.setColor(QPalette::Ba);
    this->setAutoFillBackground(false);
    this->setPalette(p);*/

}

GameInfo::~GameInfo()
{

}
