#include "ui_mainwindow.h"
#include "../h/gui/mainwindow.h"
#include "../h/gui/settings.h"
#include "../h/gui/test.h"
#include "../h/gui/gameinfo.h"
#include "../h/gui/bord.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->move(START_POSITION_X,START_POSITION_Y);
    this->setFixedSize(this->size().width(),this->size().height());
    this->setStyleSheet("MainWindow {border-image: url(:/image/back3.png); };");
    load4WinWidgets();
}

void MainWindow::load4WinWidgets()
{
    this->gameInfoWidget = new GameInfo(ui->pluginWidget);

    this->bordWidget = new Bord();
    bordWidget->show();
    bordWidget->setFocus(Qt::ActiveWindowFocusReason);


}

void MainWindow::closeAllWidgets()
{
    if(settingsWidget != 0)
        settingsWidget->close();

    if(bordWidget != 0)
        bordWidget->close();

    if(gameInfoWidget != 0)
        gameInfoWidget->close();

    this->close();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete settingsWidget;
    delete bordWidget;
    delete gameInfoWidget;
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

    this->settingsWidget = new Settings();
    settingsWidget->show();
}
