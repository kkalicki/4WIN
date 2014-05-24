#include "../h/gui/gameinfo.h"
#include "../h/sys/Konstanten.h"
#include <sstream>


GameInfo::GameInfo(QWidget *parent) : QWidget(parent),
    ui(new Ui::gameinfoUi)
{
    ui->setupUi(this);
    init();
}

GameInfo::~GameInfo()
{
    delete &imgRed;
    delete &imgYellow;
}


void GameInfo::init()
{
    this->imgRed = *new QPixmap(":/image/red_point.png");
    this->imgYellow = *new QPixmap(":/image/yellow_point.png");;
    this->move(START_POSITION_X,START_POSITION_Y);
    this->setFixedSize(this->size().width(),this->size().height());
    ui->lblleft->setVisible(false);
    ui->lblright->setVisible(false);
    lock();
}

void GameInfo::preExecute()
{
    unlock();

    //zeit auf 0 Stellen...

    //Wurf loeschen

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

void GameInfo::changePlayer()
{
    if(ui->lblleft->isVisible()){
         ui->lblleft->setVisible(false);
         ui->lblright->setVisible(true);
    }
    else{
        ui->lblleft->setVisible(true);
        ui->lblright->setVisible(false);
    }

    //Uhren stoppen und starten
}

void GameInfo::initPlayerDisplays(const Spieler& player1,const Spieler& player2)
{
    this->player1 = player1;
    this->player2 = player2;

    //init player1...
    ui->lblplayer1->setText(QString::fromStdString(player1.getName()));

    if(player1.getFarbe() == ROT)
        ui->lblimg1->setPixmap(imgRed);
    else
        ui->lblimg1->setPixmap(imgYellow);

    //init player1...
    ui->lblplayer2->setText(QString::fromStdString(player2.getName()));

    if(player2.getFarbe() == ROT)
        ui->lblimg2->setPixmap(imgRed);
    else
        ui->lblimg2->setPixmap(imgYellow);
}

void GameInfo::initfirstPlayer(const Spieler& firstPlayer)
{
    //hier ganz dringen == ueberladen
    this->currentPlayer = firstPlayer;
    if(player1.getFarbe() == currentPlayer.getFarbe())
        ui->lblleft->setVisible(true);
    else
        ui->lblleft->setVisible(true);
}

void GameInfo::setLastMove(string move)
{
    if(player1.getFarbe() == currentPlayer.getFarbe())
        ui->lblmove1->setText(QString::fromStdString(move);
    else
        ui->lblmove2->setText(QString::fromStdString(move);
}

void GameInfo::setRound(unsigned short round)
{
    ostringstream o;
    o << "Runde " << round;
    ui->lblround->setText(QString::fromStdString(o.str()));
}

void GameInfo::on_btnlooseleft_clicked()
{

}

void GameInfo::on_btnlooseright_clicked()
{

}
