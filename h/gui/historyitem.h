#ifndef HISTORYITEM_H
#define HISTORYITEM_H

#include "../h/sys/HisEintrag.h"
#include <QPixmap>
#include "ui_historyitem.h"

namespace Ui {
class historyItemUi;
}

class HistoryItem : public QWidget
{
    Q_OBJECT
public:
    HistoryItem(HisEintrag* item, QWidget* parent=0);
    ~HistoryItem();

    HisEintrag getHisEintrag() const;
    void setHisEintrag(const HisEintrag &value);
    void initControls();

private:
    HisEintrag* hisEintrag;
    QPixmap* image;
    Ui::historyItemUi *ui;
};

#endif // HISTORYITEM_H
