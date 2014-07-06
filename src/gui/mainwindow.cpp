#include "ui_mainwindow.h"
#include "../h/gui/mainwindow.h"
#include "../h/gui/settings.h"
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
    if(settingsWidget!=0)
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

    if(visitorThread == 0)
        delete visitorThread;

    delete ui;
}


void MainWindow::init()
{
    this->move(START_POSITION_X,START_POSITION_Y);
    this->setFixedSize(this->size().width(),this->size().height());
    this->setStyleSheet("MainWindow {border-image: url(:/image/back3.png); };");
    load4WinWidgets();
    this->game = 0;

    //Movethread init
    this->guiMoveThread=0;
    this->guiUpdaterThread = 0;
<<<<<<< HEAD

    //Giveuphtread init
    this->guiGiveUpThread=0;
=======
    this->guiMoveThread=0;
>>>>>>> 0fe6d77561603c9c1c58e42414c5c6dc7de91ae4
    this->giveUpThread = 0;

    //VisitorThread init
    this->visitorThread=0;
    this->guiVpThread = 0;

    connect( gameInfoWidget, SIGNAL(loose(Spieler*,bool)), this, SLOT(on_endGame(Spieler*,bool)));
    connect( gameInfoWidget, SIGNAL(exitVmMode()), this, SLOT(on_exitVisitorMode()));
}

void MainWindow::load4WinWidgets()
{
    this->gameInfoWidget = new GameInfo(ui->pluginWidget);

    this->bordWidget = new Bord();
    bordWidget->show();
    bordWidget->setFocus(Qt::ActiveWindowFocusReason);
    this->historyWidget = new History();
    historyWidget->show();

    this->settingsWidget=0;
}

void MainWindow::preExecute()
{
    //TODO ans Spiel...
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
    this->settingsWidget->hide();
    this->gameSettings = gameSettings;

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
    if(game != 0){
        delete game;
        game = 0;
    }

    try{
        switch(gameSettings->getNetworkMode()){
        case LOCAL:
                this->game = new Spiel(gameSettings->getBordRows(), gameSettings->getBordColumns(),gameSettings->getLevel());

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
                dynamic_cast<NetzwerkSpiel*>(game)->startClient(gameSettings->getRemoteIp());
                dynamic_cast<NetzwerkSpiel*>(game)->anmeldenNetzwerk(gameSettings->getPlayer2Name(),gameSettings->getGameId(),gameSettings->getVisitorMode());
                gameInfoWidget->setSysMsg("Warte auf Antwort...");
                gameInfoWidget->lockDisplaySp1();
                if(gameSettings->getVisitorMode())
                    gameInfoWidget->visitorMode();
                initNetworkSignalSlot();
            break;
        default: // Do Nothing...
        break;
        }
    }catch(Server4WinException& e){
        showException(e);
    }
    catch(ClientException& e){
        showException(e);
    }
    catch(exception& e){
        showException(e);
    }
}

void MainWindow::initNetworkSignalSlot()
{
    dynamic_cast<NetzwerkSpiel*>(game)->RemoteMoveSignal.connect(boost::bind(&MainWindow::incommingMove, this,_1,_2));
    dynamic_cast<NetzwerkSpiel*>(game)->VisitorPackageSignal.connect(boost::bind(&MainWindow::incommingVp, this,_1,_2));
    dynamic_cast<NetzwerkSpiel*>(game)->StartGameSignal.connect(boost::bind(&MainWindow::startGame, this));
    dynamic_cast<NetzwerkSpiel*>(game)->GiveUpRemotePlayerSignal.connect(boost::bind(&MainWindow::incommingGiveUp, this,_1,_2));
}

void MainWindow::killNetworkSignalSlot()
{
    dynamic_cast<NetzwerkSpiel*>(game)->RemoteMoveSignal.disconnect(&MainWindow::incommingMove);
    dynamic_cast<NetzwerkSpiel*>(game)->VisitorPackageSignal.disconnect(&MainWindow::incommingVp);
    dynamic_cast<NetzwerkSpiel*>(game)->StartGameSignal.disconnect(&MainWindow::startGame);
    dynamic_cast<NetzwerkSpiel*>(game)->GiveUpRemotePlayerSignal.disconnect(&MainWindow::incommingGiveUp);
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
            if(!gameSettings->getVisitorMode()){
                if(game->getSp2()->getIstAmZug()){
                    bordWidget->setIsLocked(false);
                }
                else{
                    bordWidget->setIsLocked(true);
                }
            }else
            {
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

    if(!gameSettings->getVisitorMode()){
        switch(gameSettings->getNetworkMode()){
        case OPEN:gameInfoWidget->lockDisplaySp2();
            break;
        case JOIN:gameInfoWidget->lockDisplaySp1();
            break;
        }
    }
    else
    {
        gameInfoWidget->lockDisplaySp1();
        gameInfoWidget->lockDisplaySp2();
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
    catch(ClientException& e){
        showException(e);
    }
    catch(Server4WinException& e){
        showException(e);
    }
    catch(exception& e){
         showException(e);
    }
}

void MainWindow::update(unsigned short column, int result)
{

    bordWidget->setMove(game->getAktuellerSpieler(),game->getAktuelleZeile(column),column);

    //history add..
    historyWidget->addHisItem(game->getHistorie()->getLetztenEintrag());

    if(result == WIN){
        //Spiel zu ende...
        on_endGame(game->getAktuellerSpieler(),false);
        std::cout << "Nach on_endGame destruieren!" << endl;
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

    std::cout << "Nach guiMoveThread destruieren!" << endl;
}

void MainWindow::on_endGame(Spieler* winner,bool giveUp)
{

     postExecute();

     try{
         if(giveUp)
             game->aufgeben();

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

         if(gameSettings->getNetworkMode() == JOIN ||  gameSettings->getNetworkMode() == OPEN)
             killNetworkSignalSlot();

        if(game != 0)
        {
             delete game;
             game=0;
        }

<<<<<<< HEAD
          std::cout << "Nach GAME destruieren!" << endl;

           if(guiGiveUpThread != 0)
           {
               guiGiveUpThread->terminate();
               guiGiveUpThread->wait();
               delete guiGiveUpThread;
               delete giveUpThread;
               guiGiveUpThread=0;
           }

          if(guiMoveThread != 0){
               guiMoveThread->terminate();
               guiMoveThread->wait();
               delete guiMoveThread;
               delete guiUpdaterThread;
               guiMoveThread=0;
           }

          if(guiVpThread != 0){
               guiVpThread->terminate();
               guiVpThread->wait();
               delete guiVpThread;
               delete visitorThread;
               guiVpThread=0;
               visitorThread=0;
           }
           std::cout << "Nach guiGiveUpThread destruieren!" << endl;
     }
     catch(TcpServerException& e){
         showException(e);

     }catch(ClientException& e){
          showException(e);

     }catch(Server4WinException& e){
         showException(e);

     }
     catch(exception& e){
          showException(e);
     }
=======
   if(game != 0)
   {
        delete game;
        game=0;
   }

     std::cout << "Nach GAME destruieren!" << endl;

      if(guiGiveUpThread != 0)
      {
          guiGiveUpThread->terminate();
          guiGiveUpThread->wait();
          delete guiGiveUpThread;
          delete giveUpThread;
          guiGiveUpThread=0;
      }

     if(guiMoveThread != 0){
          guiMoveThread->terminate();
          guiMoveThread->wait();
          delete guiMoveThread;
          delete guiUpdaterThread;
          guiMoveThread=0;
      }
      std::cout << "Nach guiGiveUpThread destruieren!" << endl;
>>>>>>> 0fe6d77561603c9c1c58e42414c5c6dc7de91ae4
}

void MainWindow::on_exitVisitorMode()
{
    postExecute();
    if(game != 0){
         delete game;
         game=0;
    }
}

void MainWindow::incommingMove(unsigned short column,int row)
{
    guiMoveThread = new QThread;
    guiUpdaterThread = new MoveThread(column,row);
    guiUpdaterThread->moveToThread(guiMoveThread);
    connect(guiMoveThread, SIGNAL(started()), guiUpdaterThread, SLOT(process()));
    connect(guiUpdaterThread, SIGNAL(finished()), this, SLOT(stopMoveThread()));
    connect(guiUpdaterThread, SIGNAL(updateGui(unsigned short,int)), this, SLOT(update(unsigned short, int)));
    guiMoveThread->start();
}

void MainWindow::incommingVp(VisitorPackage vp, int lastround)
{
    guiVpThread = new QThread;
    visitorThread = new VisitorThread(vp,lastround);
    visitorThread->moveToThread(guiVpThread);
    connect(guiVpThread, SIGNAL(started()), visitorThread, SLOT(process()));
    connect(visitorThread, SIGNAL(finished()), this, SLOT(stopVpThread()));
    connect(visitorThread, SIGNAL(updateGui(unsigned short)), this, SLOT(on_executeMove(unsigned short)));
    guiVpThread->start();
}

void MainWindow::incommingGiveUp(Spieler *remoteSpieler, bool giveUp)
{
    guiGiveUpThread = new QThread;
    giveUpThread = new GiveUpThread(remoteSpieler,giveUp);
    giveUpThread->moveToThread(guiGiveUpThread);
    connect(guiGiveUpThread, SIGNAL(started()), giveUpThread, SLOT(process()));
    connect(giveUpThread, SIGNAL(finished()), this, SLOT(stopGiveUpThread()));
    connect(giveUpThread, SIGNAL(updateGui(Spieler*,bool)), this, SLOT(on_endGame(Spieler*, bool)));
    guiGiveUpThread->start();
}

void MainWindow::stopMoveThread()
{
    if(guiMoveThread != 0){
       guiMoveThread->terminate();
    }
}

void MainWindow::stopGiveUpThread()
{
   if(guiGiveUpThread != 0){
        guiGiveUpThread->terminate();
        guiGiveUpThread=0;
        giveUpThread=0;
    }
}

void MainWindow::stopVpThread()
{
   if(guiVpThread != 0){
        guiVpThread->terminate();
        guiVpThread=0;
        visitorThread=0;
    }
    std::cout << "Nach stopVpThread destruieren!" << endl;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    try{
        if(getIsActiveGame())
            game->aufgeben();
    }
    catch(ClientException& e){
        //Do Nothing... ist korrekt, wenn Exception auftritt...
    }


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
    if(getIsActiveGame())
    {
        QMessageBox msg;
        msg.setText("ein Spiel ist noch aktiv! erst BEENDEN oder AUFGEBEN");
        msg.exec();

    }else
    {
        if(settingsWidget != 0)
        {
            settingsWidget->close();
            delete settingsWidget;
            settingsWidget=0;
        }

        this->settingsWidget = new Settings();
        connect( settingsWidget, SIGNAL(resultSettings(GameSettings*)), this, SLOT(on_resultSettings(GameSettings*)));
        settingsWidget->show();
    }

}

void MainWindow::showException(exception& e)
{
    QMessageBox msg;
    msg.setText(e.what());
    msg.exec();
}

