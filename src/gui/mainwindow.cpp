#include "ui_mainwindow.h"
#include "../h/gui/mainwindow.h"
#include "../h/gui/settings.h"
#include "../h/gui/test.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadSettingWidget();
    Bord *test = new Bord();
    test->show();
}

void MainWindow::loadSettingWidget()
{
    settingsWidget = new Settings();
    settingsWidget->show();

    Test *t = new Test();
    t->show();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete settingsWidget;
    delete bordWidget;
}
