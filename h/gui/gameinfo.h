#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <QWidget>
#include "ui_gameinfo.h"

namespace Ui {
class gameinfoUi;
}

class GameInfo : public QWidget
{
    Q_OBJECT
public:
    explicit GameInfo(QWidget * parent=0);
    ~GameInfo();

private slots:

private:
     Ui::gameinfoUi *ui;
     static const int START_POSITION_X = 0;
     static const int START_POSITION_Y = 0;
};

#endif // GAMEINFO_H
