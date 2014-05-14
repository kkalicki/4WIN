#include "../h/gui/settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent), ui(new Ui::settingsUi)
{
     ui->setupUi(this);
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
    }
}

void Settings::on_btnstart_clicked()
{
    //auswerten der Settings und spiel starten....
}
