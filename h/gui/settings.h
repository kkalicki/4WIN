#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include "ui_settings.h"

namespace Ui {
class settingsUi;
}

class Settings : public QWidget
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = 0);

private:
    Ui::settingsUi * ui;
signals:

public slots:

private slots:
    void on_rbsvs_toggled(bool checked);
    void on_rbsvc_toggled(bool checked);
    void on_rbcvc_toggled(bool checked);
    void on_rblocal_toggled(bool checked);
    void on_rbopen_toggled(bool checked);
    void on_rbenter_toggled(bool checked);
    void on_btnstart_clicked();
};

#endif // SETTINGS_H
