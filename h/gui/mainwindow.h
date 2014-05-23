#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <../4WIN/h/gui/I4WinWidget.h>
#include <QMainWindow>
#include <./h/gui/bord.h>
#include <./h/gui/settings.h>
#include <./h/gui/gameinfo.h>

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
    void end();
    virtual void preExecute();
    virtual void postExecute();

    ~MainWindow();

private slots:
    void on_resultSettings(int t);
    void on_actionBeenden_triggered();
    void on_actionNeu_triggered();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    Settings *settingsWidget;
    Bord *bordWidget;
    GameInfo *gameInfoWidget;
    static const int START_POSITION_X = 200;
    static const int START_POSITION_Y = 0;
};

#endif // MAINWINDOW_H
