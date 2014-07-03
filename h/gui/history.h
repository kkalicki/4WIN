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

/**
 * @brief The History class
 * Klasse, die Anzeigt wie der Zugverlauf waehrend eines Spiels ist
 */
class History: public QWidget, public I4WinWidget
{
    Q_OBJECT
public:
    /**
     * @brief History Konstruktor
     * @param parent ParentWidget
     */
    History(QWidget *parent=0);
    ~History();

    /**
     * @brief init Funktion, welche zum Initilisieren des Widgets erforderlich ist. Vererbung durch Interface
     */
    virtual void init();

    /**
     * @brief preExecute Funktion, welche ausgefueht wird bevor das Spiel beginnt. Vererbung durch Interface
     */
    virtual void preExecute();

    /**
     * @brief postExecute Funktion, welche ausgefueht wird nachdem ein Spiel beendet wurde, Vererbung durch Interface
     */
    virtual void postExecute();

    /**
     * @brief addHisItem Funktion um ein HisItem zur Ansicht hinzuzufuegen
     * @param addItem
     */
    void addHisItem(HisEintrag* addItem);

    /**
     * @brief clear Funktion, um die History zu loeschen
     */
    void clear();
    //void setHistoryEntry(historyItem addItem)

private:
    Ui::historyUi *ui;
    //QStandardItemModel * model;
    /**
     * @brief START_POSITION_X Konstante fuer Startposition auf dem Bildschirm (X-Position)
     */
    static const int START_POSITION_X = 20;
    /**
     * @brief START_POSITION_Y Konstante fuer Startposition auf dem Bildschirm (Y-Position)
     */
    static const int START_POSITION_Y = 0;
};

#endif // HISTORY_H
