#include "../h/gui/settings.h"
#include <QMessageBox>
#include <QThread>
#include <boost/signals2.hpp>
#include "boost/bind.hpp"
#include "../h/gui/remotegameslistitem.h"
#include "../h/sys/FourWinExceptions.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent), ui(new Ui::settingsUi)
{
    ui->setupUi(this);
    this->gameSettings = new GameSettings();
    this->openGameThread=0;
    this->helloServer = 0;

}

Settings::~Settings()
{
    if(gameSettings != 0)
        delete gameSettings;

    if(openGameThread != 0)
        delete openGameThread;

   closeHelloServer();

}

void Settings::on_rbsvs_toggled(bool checked)
{
    if(checked){
        ui->gbplayer1->setEnabled(true);
        ui->leplayer1->setText("Spieler 1");
        ui->gbplayer2->setEnabled(true);
        ui->leplayer2->setText("Spieler 2");

        ui->gbnetwork->setEnabled(true);
    }
}

void Settings::on_rbsvc_toggled(bool checked)
{
    if(checked){
        ui->gbplayer1->setEnabled(true);
        ui->leplayer1->setText("Spieler 1");
        ui->gbplayer2->setEnabled(false);
        ui->leplayer2->setText("Computer 2");

        ui->gbnetwork->setEnabled(false);
        ui->rblocal->setChecked(true);
    }
}

void Settings::on_rbcvc_toggled(bool checked)
{
    if(checked){
        ui->gbplayer1->setEnabled(false);
        ui->leplayer1->setText("Computer 1");
        ui->gbplayer2->setEnabled(false);
        ui->leplayer2->setText("Computer 2");

        ui->gbnetwork->setEnabled(false);
        ui->rblocal->setChecked(true);
    }
}

void Settings::on_rblocal_toggled(bool checked)
{
    if(checked){
        ui->lvgames->setEnabled(false);
    }
}

void Settings::on_rbopen_toggled(bool checked)
{
    if(checked){
        ui->lvgames->setEnabled(false);
        ui->leplayer1->setEnabled(true);
        ui->leplayer2->setEnabled(false);
    }
}

void Settings::on_rbenter_toggled(bool checked)
{
    if(checked){
        ui->lvgames->setEnabled(true);
        ui->cbwatch->setEnabled(true);
        ui->leplayer1->setEnabled(false);
        ui->leplayer2->setEnabled(true);
        ui->gbgamefieldsetting->setEnabled(false);
        this->helloServer = new HelloServer();
        ui->pbrefresh->setEnabled(true);
        try
        {
            helloServer->HelloReplySignal.connect(boost::bind(&Settings::incomingGames, this,_1));
            helloServer->start();
        }catch(Server4WinException& e)
        {
            QMessageBox info;
            info.setText(e.what());
            info.exec();
        }

    }
    else
    {
        ui->pbrefresh->setEnabled(false);
        ui->gbgamefieldsetting->setEnabled(true);
        ui->cbwatch->setEnabled(false);

        if(helloServer != 0)
        {
            if(helloServer->getIsActive())
                helloServer->stop();

            delete helloServer;
            helloServer=0;
        }

    }
}

void Settings::on_btnstart_clicked()
{
    if(!ui->leplayer1->text().isEmpty()){
       if(!ui->leplayer2->text().isEmpty()){

            //create setting-Object
            gameSettings->setMode(getGameMode());
            gameSettings->setPlayer1Name(ui->leplayer1->text().toStdString());
            gameSettings->setPlayer2Name(ui->leplayer2->text().toStdString());
            gameSettings->setBordRows(ui->sbrow->text().toShort());
            gameSettings->setBordColumns(ui->sbcolumn->text().toShort());
            gameSettings->setCellSize(ui->sbcellsize->text().toShort());
            gameSettings->setNetworkMode(getNetworkMode());
            gameSettings->setIsFollow(ui->cbwatch->isChecked());

            if(gameSettings->getNetworkMode() == JOIN)
            {
               if(gameSettings->getRemoteIp().empty())
               {
                   QMessageBox info;
                   info.setText("Spiel muss ausgewaehlt sein für beitritt!");
                   info.exec();
               }
               else
               {
                   start();
               }
            }
            else
            {
                start();
            }


       }
       else{
           QMessageBox info;
           info.setText("Namen für Player2 eingeben!");
           info.exec();
       }
    }
    else{
        QMessageBox info;
        info.setText("Namen für Player1 eingeben!");
        info.exec();
    }
}

void Settings::start()
{
    closeHelloServer();
    emit resultSettings(gameSettings);
}

void Settings::closeHelloServer()
{
    if(helloServer != 0)
    {
        if(helloServer->getIsActive())
            helloServer->stop();

        delete helloServer;
        helloServer=0;
    }

}

void Settings::on_cbwatch_toggled(bool checked)
{
    if(checked)
    {
        //zuschauer optionen...
    }
}

GameMode Settings::getGameMode()
{
    if(ui->rbsvs->isChecked())
        return SVS;

    if(ui->rbsvc->isChecked())
        return SVC;

    if(ui->rbcvc->isChecked())
        return CVC;
}

NetworkMode Settings::getNetworkMode()
{
    if(ui->rblocal->isChecked())
        return LOCAL;

    if(ui->rbopen->isChecked())
        return OPEN;

    if(ui->rbenter->isChecked())
        return JOIN;
}

void Settings::incomingGames(HelloReply incomingVal)
{
    guiThread = new QThread;
    openGameThread = new OpenGameThread(incomingVal);
    openGameThread->moveToThread(guiThread);
    connect(guiThread, SIGNAL(started()), openGameThread, SLOT(process()));
    connect(openGameThread, SIGNAL(updateGui(HelloReply*)), this, SLOT(openGamesUpdate(HelloReply*)));
    guiThread->start();
}

void Settings::openGamesUpdate(HelloReply* incomingVal)
{
    RemoteGamesListItem entry;
    entry.ipAdress = incomingVal->getIpAdress();
    entry.name = incomingVal->getName();
    entry.rows = incomingVal->getRows();
    entry.columns = incomingVal->getColumns();

    QVariant qv;
    qv.setValue(entry);
    QListWidgetItem *item = new QListWidgetItem();
    item->setText(QString::fromStdString(entry.toString()));
    item->setData(Qt::UserRole,qv);
    ui->lvgames->addItem(item);
    ui->lvgames->scrollToBottom();

    guiThread->exit();
    guiThread->quit();
}

void Settings::on_lvgames_itemActivated(QListWidgetItem *item)
{
    QVariant qv = item->data(Qt::UserRole);
    RemoteGamesListItem entry = qv.value<RemoteGamesListItem>();

    ui->sbrow->setValue(entry.rows);
    ui->sbcolumn->setValue(entry.columns);
    ui->leplayer1->setText(QString::fromStdString(entry.name));
    gameSettings->setRemoteIp(entry.ipAdress);
}

void Settings::on_pbrefresh_clicked()
{
    ui->lvgames->clear();
    helloServer->sendHelloBroadcast();
}

void Settings::closeEvent(QCloseEvent *event)
{
    closeHelloServer();
}
