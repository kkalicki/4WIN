#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include "ui_settings.h"
#include "../h/gui/gamesettings.h"

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

private:
    Ui::settingsUi * ui;
    GameSettings * gameSettings;
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
};

#endif // SETTINGS_H
