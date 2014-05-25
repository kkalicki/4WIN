#ifndef HISTORY_H
#define HISTORY_H

#include "../h/gui/I4WinWidget.h"
#include "../h/sys/HisEintrag.h"
#include <QWidget>
#include <QStandardItemModel>
#include "ui_history.h"

namespace Ui {
class historyUi;
}

class History: public QWidget, public I4WinWidget
{
    Q_OBJECT
public:
    History(QWidget *parent=0);
    ~History();
    virtual void init();
    virtual void preExecute();
    virtual void postExecute();
    void addHisItem(HisEintrag* addItem);
    void clear();

    //void setHistoryEntry(historyItem addItem)

private:
    Ui::historyUi *ui;
    QStandardItemModel * model;
    static const int START_POSITION_X = 20;
    static const int START_POSITION_Y = 0;
};

#endif // HISTORY_H
