#include "../h/gui/settings.h"
#include <QMessageBox>

Settings::Settings(QWidget *parent) :
    QWidget(parent), ui(new Ui::settingsUi)
{
    ui->setupUi(this);
    this->gameSettings = new GameSettings();
}

Settings::~Settings()
{
    delete gameSettings;
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
    }
}

void Settings::on_rbenter_toggled(bool checked)
{
    if(checked){
        ui->lvgames->setEnabled(true);
        ui->cbwatch->setEnabled(true);
    }
    else
    {
        ui->cbwatch->setEnabled(false);
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

            emit resultSettings(gameSettings);
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

    if(ui->rbsvc->isChecked())
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
