#include "../h/gui/gameinfo.h"
#include "../h/sys/Konstanten.h"
#include <sstream>
#include <QMessageBox>


GameInfo::GameInfo(QWidget *parent) : QWidget(parent),
    ui(new Ui::gameinfoUi)
{
    ui->setupUi(this);
    init();
}

GameInfo::~GameInfo()
{
    if(timer != 0)
        delete timer;

    if(timerWorker != 0)
        delete timerWorker;

    //delete &imgRed;
    //delete &imgYellow;
    delete gifRedMovie;
    delete gifYellowMovie;
}


void GameInfo::init()
{
    //this->imgRed = *new QPixmap(":/image/red_point.png");
    //this->imgYellow = *new QPixmap(":/image/yellow_point.png");;
    this->move(START_POSITION_X,START_POSITION_Y);
    this->setFixedSize(this->size().width(),this->size().height());
    ui->lblleft->setVisible(false);
    ui->lblright->setVisible(false);
    timer = 0;
    timerWorker = 0;
    timePlayer1 = 0;
    timePlayer2 = 0;
    lock();

    ui->lblimg1->setVisible(false);
    ui->lblimg2->setVisible(false);

    gifRedMovie = new QMovie(":/image/recright_red.gif");
    gifYellowMovie = new QMovie(":/image/recright_yellow.gif");
}

void GameInfo::preExecute()
{
    unlock();
    setRound(1);
    ui->lblmove1->setText("0 - 0");
    ui->lblmove2->setText("0 - 0");

    clearTimePlayer1();
    clearTimePlayer2();

    timer = new QThread;
    timerWorker = new Timer4Win();
    timerWorker->moveToThread(timer);
    connect(timer, SIGNAL(started()), timerWorker, SLOT(process()));
    connect( timerWorker, SIGNAL(timeChange()), this, SLOT(on_timeChange()));
    timer->start();
}

void GameInfo::postExecute()
{
    lock();
    if(timerWorker != 0){
        timerWorker->stop();
    }
    if(timer != 0){
        timer->quit();
        timer->wait();
        delete timer;
        timer = 0;

        delete timerWorker;
        timerWorker = 0;
    }
    ui->lblleft->setVisible(false);
    ui->lblright->setVisible(false);
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

void GameInfo::initPlayer(Spieler *player1,Spieler* player2)
{
    this->player1 = player1;
    this->player2 = player2;

    if(player1->getIstAmZug()){
       currentPlayer = player1;
       ui->lblleft->setVisible(true);
    }
    else{
        currentPlayer = player2;
        ui->lblright->setVisible(true);
    }
    initPlayerDisplays();

}

void GameInfo::changePlayer(Spieler* currentPlayer, unsigned short round, string lastMove)
{
    setRound(round);
    setLastMove(lastMove);
    this->currentPlayer = currentPlayer;
    if(ui->lblleft->isVisible()){
         ui->lblleft->setVisible(false);
         ui->lblright->setVisible(true);
    }
    else{
        ui->lblleft->setVisible(true);
        ui->lblright->setVisible(false);
    }
}

void GameInfo::setSysMsg(string msg)
{
    ui->lblsysmsg->setText(QString::fromStdString(msg));
}

void GameInfo::initPlayerDisplays()
{
    //init player1...
    ui->lblplayer1->setText(QString::fromStdString(player1->getName()));

    if(player1->getFarbe() == ROT){
        //ui->lblimg1->setPixmap(imgRed);
        ui->lblleft->setMovie(gifRedMovie);
    }
    else{
        //ui->lblimg1->setPixmap(imgYellow);
        ui->lblleft->setMovie(gifYellowMovie);
    }

    //init player2...
    ui->lblplayer2->setText(QString::fromStdString(player2->getName()));

    if(player2->getFarbe() == ROT){
        //ui->lblimg2->setPixmap(imgRed);
        ui->lblright->setMovie(gifRedMovie);
    }
    else{
        //ui->lblimg2->setPixmap(imgYellow);
        ui->lblright->setMovie(gifYellowMovie);
    }

    gifRedMovie->start();
    gifYellowMovie->start();
}

void GameInfo::setLastMove(string move)
{
    if(player1->getFarbe() == currentPlayer->getFarbe())
        ui->lblmove1->setText(QString::fromStdString(move));
    else
        ui->lblmove2->setText(QString::fromStdString(move));
}

void GameInfo::setRound(unsigned short round)
{
    ostringstream o;
    o << "Runde " << round;
    ui->lblround->setText(QString::fromStdString(o.str()));
}

void GameInfo::on_btnlooseleft_clicked()
{
    emit loose(player2);
}

void GameInfo::on_btnlooseright_clicked()
{
    emit loose(player1);
}

void GameInfo::on_timeChange()
{
    if(player1->getFarbe() == currentPlayer->getFarbe()){
        setTimePlayer1();
    }
    else{
        setTimePlayer2();
    }
}

void GameInfo::setTimePlayer1()
{
    timePlayer1 += SEC_IN_MS;
    ui->lbltime1->setText(QString::fromStdString(convertMillToTime(timePlayer1)));
}

void GameInfo::setTimePlayer2()
{
     timePlayer2 += SEC_IN_MS;
     ui->lbltime2->setText(QString::fromStdString(convertMillToTime(timePlayer2)));
}

void GameInfo::clearTimePlayer1()
{
    timePlayer1 = 0;
    ui->lbltime1->setText(QString::fromStdString(convertMillToTime(timePlayer1)));
}

void GameInfo::clearTimePlayer2()
{
    timePlayer2 = 0;
    ui->lbltime2->setText(QString::fromStdString(convertMillToTime(timePlayer2)));
}

string GameInfo::convertMillToTime(unsigned long ms)
{
    int seconds = (int) (ms / 1000) % 60 ;
    int minutes = (int) ((ms / (1000*60)) % 60);
    int hours   = (int) ((ms / (1000*60*60)) % 24);

    ostringstream strsec;
    if(seconds < 10){
        strsec << 0 << seconds;
    }
    else{
        strsec << seconds;
    }
    string sec = strsec.str();

    ostringstream strmin;
    if(minutes < 10){
        strmin << 0 << minutes;
    }
    else{
        strmin << minutes;
    }
    string min = strmin.str();

    ostringstream strh;
    if(hours < 10){
        strh << 0 << hours;
    }
    else{
        strh << hours;
    }
    string std = strh.str();

    ostringstream rslt;
    rslt << std << ":" << min << ":" << sec;

    return rslt.str();
}
