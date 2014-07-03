#ifndef HISTORYITEM_H
#define HISTORYITEM_H

#include "../h/sys/HisEintrag.h"
#include <QPixmap>
#include "ui_historyitem.h"

namespace Ui {
class historyItemUi;
}

/**
 * @brief The HistoryItem class
 * Klasse, welche ein Historieeintrag in der Gui repraesentiert. Jeder Historieeintrag wird durch diese Klasse definiert
 */
class HistoryItem : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief HistoryItem Konstruktor
     * @param item         HisEintrag aus dem System
     * @param parent       ParentWidget
     */
    HistoryItem(HisEintrag* item, QWidget* parent=0);
    ~HistoryItem();

    /**
     * @brief getHisEintrag Getter fuer den HisEintrag
     * @return HisEintrag
     */
    HisEintrag getHisEintrag() const;
    /**
     * @brief setHisEintrag Setter fuer HisEintrag
     * @param value Wert
     */
    void setHisEintrag(const HisEintrag &value);

    /**
     * @brief initControls Funktion, um ein die Controlls in der History zu initialisieren
     */
    void initControls();

private:
    /**
     * @brief hisEintrag HistorieEintrag
     */
    HisEintrag* hisEintrag;
    /**
     * @brief image Bild, welches hinter jedem Eintrag angezeigt wird
     */
    QPixmap* image;
    Ui::historyItemUi *ui;
};

#endif // HISTORYITEM_H
