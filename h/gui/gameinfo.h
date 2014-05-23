#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <QWidget>
#include "ui_gameinfo.h"
#include "../h/gui/I4WinWidget.h"

namespace Ui {
class gameinfoUi;
}

class GameInfo : public QWidget, public I4WinWidget
{
    Q_OBJECT
public:
    explicit GameInfo(QWidget * parent=0);
    virtual void preExecute();
    virtual void postExecute();
    void lock();
    void unlock();
    void changePlayer();
    ~GameInfo();

private slots:

private:
     Ui::gameinfoUi *ui;
     static const int START_POSITION_X = 0;
     static const int START_POSITION_Y = 0;
};

#endif // GAMEINFO_H
