#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include "ui_settings.h"
#include "../h/gui/gamesettings.h"
#include "../h/net/helloserver.h"
#include "../h/gui/threads/opengamesthread.h"

namespace Ui {
class settingsUi;
}

class Settings : public QWidget
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    GameMode getGameMode();
    NetworkMode getNetworkMode();
    void incomingGames(HelloReply incomingVal);
    void start();

private:
    Ui::settingsUi * ui;
    GameSettings * gameSettings;
    OpenGameThread* openGameThread;
    HelloServer* helloServer;
signals:
    void resultSettings(GameSettings* gameSettings);

public slots:

private slots:
    void on_rbsvs_toggled(bool checked);
    void on_rbsvc_toggled(bool checked);
    void on_rbcvc_toggled(bool checked);
    void on_rblocal_toggled(bool checked);
    void on_rbopen_toggled(bool checked);
    void on_rbenter_toggled(bool checked);
    void on_btnstart_clicked();
    void on_cbwatch_toggled(bool checked);
    void on_pbrefreshs_clicked();
    void openGamesUpdate(HelloReply *incomingVal);
    void on_lvgames_itemActivated(QListWidgetItem *item);
};

#endif // SETTINGS_H
