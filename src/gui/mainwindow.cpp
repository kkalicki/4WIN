#include "ui_mainwindow.h"
#include "../h/gui/mainwindow.h"
#include "../h/gui/settings.h"
#include "../h/gui/test.h"
#include "../h/gui/gameinfo.h"
#include "../h/gui/bord.h"
#include "../h/sys/FourWinExceptions.h"
#include "../h/sys/NetzwerkSpiel.h"

#include "../h/sys/Spieler.h"

#include <QMessageBox>
#include <sstream>

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

    delete ui;
}


void MainWindow::init()
{
    this->move(START_POSITION_X,START_POSITION_Y);
    this->setFixedSize(this->size().width(),this->size().height());
    this->setStyleSheet("MainWindow {border-image: url(:/image/back3.png); };");
    load4WinWidgets();
    this->game = 0;

    connect( settingsWidget, SIGNAL(resultSettings(GameSettings*)), this, SLOT(on_resultSettings(GameSettings*)));
    connect( gameInfoWidget, SIGNAL(loose(Spieler*)), this, SLOT(on_endGame(Spieler*)));
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
    bordWidget->preExecute();
    gameInfoWidget->preExecute();
    historyWidget->preExecute();
}

void MainWindow::postExecute()
{
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
    delete bordWidget;
    this->bordWidget = new Bord(gameSettings->getBordRows(),gameSettings->getBordColumns(),gameSettings->getCellSize());
    connect(bordWidget, SIGNAL(executeMove(unsigned short)), this, SLOT(on_executeMove(unsigned short)));
    bordWidget->updatesEnabled(true);
    bordWidget->show();

    //game init...
    if(game != 0)
        delete game;

    switch(gameSettings->getNetworkMode())
    {
    case LOCAL:
            this->game = new Spiel(gameSettings->getBordRows(), gameSettings->getBordColumns());
            game->starteSpiel(gameSettings->getPlayer1Name(),gameSettings->getPlayer2Name());
            startGame();
        break;
    case OPEN:
            this->game = new NetzwerkSpiel(gameSettings->getBordRows(), gameSettings->getBordColumns());
            dynamic_cast<NetzwerkSpiel*>(game)->starteNetzwerkSpiel(gameSettings->getPlayer1Name());
            dynamic_cast<NetzwerkSpiel*>(game)->RemoteMoveSignal.connect(boost::bind(&MainWindow::update, this,_1,_2));
            dynamic_cast<NetzwerkSpiel*>(game)->StartGameSignal.connect(boost::bind(&MainWindow::startGame, this));
            gameInfoWidget->setSysMsg("Warte auf Gegner...");
        break;
    case JOIN:
            this->game = new NetzwerkSpiel(gameSettings->getBordRows(), gameSettings->getBordColumns());
            dynamic_cast<NetzwerkSpiel*>(game)->anmeldenNetzwerk(gameSettings->getPlayer2Name());
            dynamic_cast<NetzwerkSpiel*>(game)->RemoteMoveSignal.connect(boost::bind(&MainWindow::update, this,_1,_2));
            dynamic_cast<NetzwerkSpiel*>(game)->StartGameSignal.connect(boost::bind(&MainWindow::startGame,this));
            gameInfoWidget->setSysMsg("Warte auf Antwort...");
        break;
    default: // Do Nothing...
    break;
    }
}

void MainWindow::startGame()
{
    gameInfoWidget->initPlayer(game->getSp1(),game->getSp2());
    //fuer Alle preExecute aufrufen
    preExecute();
    gameInfoWidget->setSysMsg("Start!");
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
        QMessageBox msg;
        msg.setText(e.what());
        msg.exec();
    }
    catch(SpielFeldException& e){
        QMessageBox msg;
        msg.setText(e.what());
        msg.exec();
    }
}

void MainWindow::update(unsigned short column, int result)
{
    if(result == -1){
        //Spiel zu ende...
        on_endGame(game->getVerherigerSpieler());
    }
    else {  //else if Catch Spielfeld voll!! --> on_endGame(0);

       //Bord bedienen...
       bordWidget->setMove(game->getVerherigerSpieler(),result,column);
       bordWidget

       //GameInfo bedienen...
       ostringstream o;
       o<< (result) << " - "<< column;
       gameInfoWidget->changePlayer(game->getAktuellerSpieler(),game->getRunde(),o.str());
    }

    //history add..
    historyWidget->addHisItem(game->getHistorie()->getLetztenEintrag());
}

void MainWindow::on_endGame(Spieler* winner)
{
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
