#include "ui_mainwindow.h"
#include "../h/gui/mainwindow.h"
#include "../h/gui/settings.h"
#include "../h/gui/test.h"
#include "../h/gui/gameinfo.h"
#include "../h/gui/bord.h"
#include "../h/sys/FourWinExceptions.h"

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

void MainWindow::init()
{
    this->move(START_POSITION_X,START_POSITION_Y);
    this->setFixedSize(this->size().width(),this->size().height());
    this->setStyleSheet("MainWindow {border-image: url(:/image/back3.png); };");
    load4WinWidgets();

    connect( settingsWidget, SIGNAL(resultSettings(GameSettings*)), this, SLOT(on_resultSettings(GameSettings*)));
    //connect( bordWidget, SIGNAL(executeMove(unsigned short)), this, SLOT(on_executeMove(unsigned short)));
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

void MainWindow::end()
{
    //Messagebox show wer hat gewonnen und so weiter...

    postExecute();
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


MainWindow::~MainWindow()
{
    delete ui;
    delete settingsWidget;
    delete bordWidget;
    delete gameInfoWidget;
    delete historyWidget;

    delete game;
}

void MainWindow::on_executeMove(unsigned short column)
{
    Spieler currentPlayer = game->getAktuellerSpieler();
    int rslt;
    try
    {
        rslt = game->naechsterZug(currentPlayer,column);
        if(rslt == -1){
            //Gewonnen
            //MessageBox show!!!!! sound abspielen: WE ARE THE CHAMPIONS :-D

            //fuer alle postExecute aufrufen...
            postExecute();
        }
        else{

           //Bord bedienen...
           bordWidget->setMove(currentPlayer,rslt,column);

           //GameInfo bedienen...
           ostringstream o;
           o<< (rslt) << " - "<< column;
           gameInfoWidget->changePlayer(currentPlayer,game->getRunde(),o.str());
        }
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

    //Catch Spielfeld voll!! --> Messagebox --> postExecute()


}

void MainWindow::on_resultSettings(GameSettings* gameSettings)
{
    settingsWidget->hide();

    //Bord init...
    bordWidget->hide();
    delete bordWidget;
    this->bordWidget = new Bord(gameSettings->getBordRows(),gameSettings->getBordColumns(),gameSettings->getCellSize());
    connect( bordWidget, SIGNAL(executeMove(unsigned short)), this, SLOT(on_executeMove(unsigned short)));
    bordWidget->show();

    //game init...
    this->game = new Spiel(gameSettings->getBordRows(), gameSettings->getBordColumns());
    game->startMP(gameSettings->getPlayer1Name(),gameSettings->getPlayer2Name());

    //gameinfo init..
    gameInfoWidget->initPlayerDisplays(game->getSp1(),game->getSp2());
    gameInfoWidget->initfirstPlayer(game->getAktuellerSpieler());

    //fuer Alle preExecute aufrufen
    preExecute();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    closeAllWidgets();
}

void MainWindow::on_actionBeenden_triggered()
{
     closeAllWidgets();
}

void MainWindow::on_actionNeu_triggered()
{
    if(settingsWidget != 0)
        settingsWidget->close();

    settingsWidget->show();
}
