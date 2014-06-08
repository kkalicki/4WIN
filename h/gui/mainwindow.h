#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <../4WIN/h/gui/I4WinWidget.h>
#include <../4WIN/h/gui/threads/movethread.h>
#include <../4WIN/h/gui/threads/giveupthread.h>
#include <../h/gui/bord.h>
#include <../h/gui/settings.h>
#include <../h/gui/gameinfo.h>
#include <../h/gui/gamesettings.h>
#include <../h/gui/history.h>
#include <../h/sys/spiel.h>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public I4WinWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void load4WinWidgets();
    void closeAllWidgets();
    void initNetworkSignalSlot();
    void lockBoad();
    virtual void init();
    virtual void preExecute();
    virtual void postExecute();
    void showException(exception &e);
    ~MainWindow();

private slots:
    void on_endGame(Spieler* winner, bool giveUp);
    void on_executeMove(unsigned short column);
    void on_resultSettings(GameSettings* gameSettings);
    void on_actionBeenden_triggered();
    void on_actionNeu_triggered();
    void update(unsigned short column, int result);

    void startGame();
    void incommingMove(unsigned short column, int row);
    void incommingGiveUp(Spieler* remoteSpieler, bool giveUp);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    Settings *settingsWidget;
    Bord *bordWidget;
    GameInfo *gameInfoWidget;
    History * historyWidget;
    GameSettings * gameSettings;
    MoveThread *guiUpdaterThread;
    GiveUpThread *giveUpThread;
    QThread * guiThread;
    static const int START_POSITION_X = 230;
    static const int START_POSITION_Y = 0;

    Spiel *game;
};

#endif // MAINWINDOW_H
