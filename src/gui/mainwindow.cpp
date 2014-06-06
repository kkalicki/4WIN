#include "ui_mainwindow.h"
#include "../h/gui/mainwindow.h"
#include "../h/gui/settings.h"
#include "../h/gui/test.h"
#include "../h/gui/gameinfo.h"
#include "../h/gui/bord.h"
#include "../h/sys/FourWinExceptions.h"
#include "../h/sys/NetzwerkSpiel.h"

#include "../h/sys/SpielerKI.h"
#include "../h/sys/Spieler.h"

#include <QMessageBox>
#include <sstream>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete settingsWidget;
    delete bordWidget;
    delete historyWidget;
    delete gameInfoWidget;

    if(game != 0)
        delete game;

    if(guiUpdaterThread == 0)
        delete guiUpdaterThread;

    if(giveUpThread == 0)
        delete giveUpThread;

    delete ui;
}


void MainWindow::init()
{
    this->move(START_POSITION_X,START_POSITION_Y);
    this->setFixedSize(this->size().width(),this->size().height());
    this->setStyleSheet("MainWindow {border-image: url(:/image/back3.png); };");
    load4WinWidgets();
    this->game = 0;
    this->guiUpdaterThread = 0;
    this->giveUpThread = 0;

    connect( settingsWidget, SIGNAL(resultSettings(GameSettings*)), this, SLOT(on_resultSettings(GameSettings*)));
    connect( gameInfoWidget, SIGNAL(loose(Spieler*,bool)), this, SLOT(on_endGame(Spieler*,bool)));
}

void MainWindow::load4WinWidgets()
{
    this->gameInfoWidget = new GameInfo(ui->pluginWidget);

    this->bordWidget = new Bord();
    bordWidget->show();
    bordWidget->setFocus(Qt::ActiveWindowFocusReason);

    this->settingsWidget = new Settings();

    this->historyWidget = new History();
    historyWidget->show();
}

void MainWindow::preExecute()
{
    setIsActiveGame(true);
    bordWidget->preExecute();
    gameInfoWidget->preExecute();
    historyWidget->preExecute();
}

void MainWindow::postExecute()
{
    setIsActiveGame(false);
    bordWidget->postExecute();
    gameInfoWidget->postExecute();
    historyWidget->postExecute();
}


void MainWindow::on_resultSettings(GameSettings* gameSettings)
{
    this->gameSettings = gameSettings;
    settingsWidget->hide();

    //Bord init...
    bordWidget->hide();
    if(bordWidget !=0){
        delete bordWidget;
        bordWidget = 0;
    }

    this->bordWidget = new Bord(gameSettings->getBordRows(),gameSettings->getBordColumns(),gameSettings->getCellSize());
    connect(bordWidget, SIGNAL(executeMove(unsigned short)), this, SLOT(on_executeMove(unsigned short)));
    bordWidget->setUpdatesEnabled(true);
    bordWidget->show();

    //game init...
    if(game != 0)
        delete game;

    try{
        switch(gameSettings->getNetworkMode()){
        case LOCAL:
                this->game = new Spiel(gameSettings->getBordRows(), gameSettings->getBordColumns());

                switch (gameSettings->getMode()) {
                case SVS:
                    game->starteSpiel(gameSettings->getPlayer1Name(),gameSettings->getPlayer2Name(),false,false);
                    break;
                case SVC:
                    game->starteSpiel(gameSettings->getPlayer1Name(),gameSettings->getPlayer2Name(),false,true);
                    game->RemoteZugSignal.connect(boost::bind(&MainWindow::incommingMove, this,_1,_2));
                    break;
                case CVC:
                    game->starteSpiel(gameSettings->getPlayer1Name(),gameSettings->getPlayer2Name(),true,true);
                    game->RemoteZugSignal.connect(boost::bind(&MainWindow::incommingMove, this,_1,_2));
                    break;
                default:
                    break;
                }
                startGame();
                lockBoad();
            break;
        case OPEN:
                this->game = new NetzwerkSpiel(gameSettings->getBordRows(), gameSettings->getBordColumns());
                dynamic_cast<NetzwerkSpiel*>(game)->starteNetzwerkSpiel(gameSettings->getPlayer1Name());
                gameInfoWidget->setSysMsg("Warte auf Gegner...");

                initNetworkSignalSlot();
            break;
        case JOIN:
                this->game = new NetzwerkSpiel(gameSettings->getBordRows(), gameSettings->getBordColumns());
                dynamic_cast<NetzwerkSpiel*>(game)->anmeldenNetzwerk(gameSettings->getPlayer2Name());
                gameInfoWidget->setSysMsg("Warte auf Antwort...");
                gameInfoWidget->lockDisplaySp1();
                initNetworkSignalSlot();
            break;
        default: // Do Nothing...
        break;
        }
    }catch(TcpServerException& e){
        showException(e);
    }
}

void MainWindow::initNetworkSignalSlot()
{
    dynamic_cast<NetzwerkSpiel*>(game)->RemoteMoveSignal.connect(boost::bind(&MainWindow::incommingMove, this,_1,_2));
    dynamic_cast<NetzwerkSpiel*>(game)->StartGameSignal.connect(boost::bind(&MainWindow::startGame, this));
    dynamic_cast<NetzwerkSpiel*>(game)->GiveUpRemotePlayerSignal.connect(boost::bind(&MainWindow::incommingGiveUp, this,_1,_2));
}

void MainWindow::lockBoad()
{
    switch(gameSettings->getNetworkMode()){
    case LOCAL:
            switch (gameSettings->getMode()) {
            case SVC:
                if(game->getSp1()->getIstAmZug()){
                    bordWidget->setIsLocked(false);
                }
                else{
                    bordWidget->setIsLocked(true);
                }
                break;
            case CVC:
                 bordWidget->setIsLocked(false);
                break;
            default:
                break;
            }
            startGame();
        break;
    case OPEN:
            if(game->getSp1()->getIstAmZug()){
                bordWidget->setIsLocked(false);
            }
            else{
                bordWidget->setIsLocked(true);
            }
        break;
    case JOIN:
            if(game->getSp2()->getIstAmZug()){
                bordWidget->setIsLocked(false);
            }
            else{
                bordWidget->setIsLocked(true);
            }
        break;
    default: // Do Nothing...
    break;
    }
}

void MainWindow::startGame()
{
    gameInfoWidget->initPlayer(game->getSp1(),game->getSp2());
    gameInfoWidget->setSysMsg("Start!");
    preExecute();
    lockBoad();

    switch(gameSettings->getNetworkMode()){
    case OPEN:gameInfoWidget->lockDisplaySp2();
        break;
    case JOIN:gameInfoWidget->lockDisplaySp1();
        break;
    }
}

void MainWindow::on_executeMove(unsigned short column)
{
    Spieler* currentPlayer = game->getAktuellerSpieler();
    int rslt;
    try
    {
       rslt = game->naechsterZug(currentPlayer,column);
       update(column, rslt);

    }
    catch(EingabeException& e){
        showException(e);
    }
    catch(SpielFeldException& e){
        showException(e);
    }
}

void MainWindow::update(unsigned short column, int result)
{

    bordWidget->setMove(game->getAktuellerSpieler(),game->getAktuelleZeile(column),column);

    if(result == WIN){
        //Spiel zu ende...
        on_endGame(game->getAktuellerSpieler(),false);
    }
    else if (result == VOLL){
        //Spiel unentschieden...
        on_endGame(0,false);
    }
    else{
       game->wechselSpieler();
       lockBoad();
       ostringstream o;
       o<< (game->getAktuelleZeile(column)) << " - "<< column;
       gameInfoWidget->changePlayer(game->getAktuellerSpieler(),game->getRunde(),o.str());
    }

    //history add..
    historyWidget->addHisItem(game->getHistorie()->getLetztenEintrag());
}

void MainWindow::on_endGame(Spieler* winner,bool giveUp)
{
    if(giveUp)
        game->aufgeben();

    postExecute();
    if(winner == 0)
    {
        //UNENTSCHIEDEN...
        QMessageBox msg;
        msg.setText("Unentschieden!");
        msg.exec();
    }
    else
    {
        //Gewonnen
        //MessageBox show!!!!! sound abspielen: WE ARE THE CHAMPIONS :-D
        QMessageBox msg;
        string strmsg = winner->getName() + " hat gewonnen!";
        msg.setText(QString::fromStdString(strmsg));
        msg.exec();
    }
}

void MainWindow::incommingMove(unsigned short column,int row)
{
    QThread* guiThread = new QThread;
    guiUpdaterThread = new MoveThread(column,row);
    guiUpdaterThread->moveToThread(guiThread);
    connect(guiThread, SIGNAL(started()), guiUpdaterThread, SLOT(process()));
    connect(guiUpdaterThread, SIGNAL(updateGui(unsigned short,int)), this, SLOT(update(unsigned short, int)));
    guiThread->start();
}

void MainWindow::incommingGiveUp(Spieler *remoteSpieler, bool giveUp)
{
    QThread* guiThread = new QThread;
    giveUpThread = new GiveUpThread(remoteSpieler,giveUp);
    giveUpThread->moveToThread(guiThread);
    connect(guiThread, SIGNAL(started()), giveUpThread, SLOT(process()));
    connect(giveUpThread, SIGNAL(updateGui(Spieler*,bool)), this, SLOT(on_endGame(Spieler*, bool)));
    guiThread->start();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    postExecute();
    closeAllWidgets();
}

void MainWindow::on_actionBeenden_triggered()
{
     closeAllWidgets();
}

void MainWindow::closeAllWidgets()
{
    if(settingsWidget != 0)
        settingsWidget->close();

    if(bordWidget != 0)
        bordWidget->close();

    if(gameInfoWidget != 0)
        gameInfoWidget->close();

    if(historyWidget != 0)
        historyWidget->close();

    this->close();
}

void MainWindow::on_actionNeu_triggered()
{
    if(settingsWidget != 0)
        settingsWidget->close();

    settingsWidget->show();
}

void MainWindow::showException(exception& e)
{
    QMessageBox msg;
    msg.setText(e.what());
    msg.exec();
}

