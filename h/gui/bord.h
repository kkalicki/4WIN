#ifndef BORD_H
#define BORD_H

#include <QWidget>
#include "ui_bord.h"
#include <../h/gui/I4WinWidget.h>
#include <../h/sys/Spieler.h>
#include <../h/sys/Konstanten.h>

namespace Ui {
class bordUi;
}

/**
 * @brief The Bord class
 * Klasse, die in der GUI das Spielfeld repraesentiert. Die Klasse beinhaltet eine Tabelle die das Spielfeld visualisiert
 */
class Bord : public QWidget, public I4WinWidget
{
    Q_OBJECT
public:
    /**
     * @brief Bord
     * @param rowCount  Anzahl der Zeilen
     * @param colCount  Anzahl der Spalten
     * @param cellSize  Groesse der einzelnen Zelle
     * @param parent    Widget, welches als Parent deklariert ist. HIER keins, da alle Fenster unabhaengig voneinander sind.
     *
     * Konstruktor der Klasse
     */
    explicit Bord(unsigned short rowCount = Y, unsigned short colCount = X,unsigned short cellSize=CELL_SIZE, QWidget *parent=0);
    ~Bord();

    /**
     * @brief setMove   Funktion um einen Zug in dem Spielfeld (GUI) zu taetigen
     * @param player    Spieler, welcher den wurf taetigt
     * @param row       Zeile in die geworfen wird
     * @param col       Spalte in die geworfen wird
     */
    void setMove(Spieler* player, int row, int col);

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
     * @brief getRowCount Getter fuer Zeilen
     * @return Anzahl der Zeilen
     */
    unsigned short getRowCount() const{
        return rowCount;
    }

    /**
     * @brief setRowCount Setter fuer Zeilen
     * @param value Wert zum setzten
     */
    void setRowCount(unsigned short value){
        rowCount = value;
    }

    /**
     * @brief getColCount Getter fuer Spalten
     * @return Anzahl der Spalten
     */
    unsigned short getColCount() const{
        return colCount;
    }

    /**
     * @brief setColCount Setter fuer Spalten
     * @param value Wert zum setzten
     */
    void setColCount(unsigned short value){
        colCount = value;
    }

    /**
     * @brief getIsLocked Getter fuer das Flag, ob Bord gesperrt ist
     * @return true/false
     */
    int getIsLocked() const;

    /**
     * @brief setIsLocked Setter fuer das Flag, ob Bord gesperrt ist
     * @param value  Wert zum setzten
     */
    void setIsLocked(int value);

private:
    int isLocked;
    unsigned short rowCount;
    unsigned short colCount;
    unsigned short cellSize;
    /**
     * @brief defaultImage Standardbild, keinen Inhalt nur Bordrahmen
     */
    QPixmap *defaultImage ;
    /**
     * @brief redImage Rotes Bild, zeigt einen roten Stein an
     */
    QPixmap *redImage ;
    /**
     * @brief yellowImage Gelbes Bild, zeigt einen gelben Stein an
     */
    QPixmap *yellowImage ;
    Ui::bordUi* ui;

    /**
     * @brief START_POSITION_X Konstante fuer Startposition auf dem Bildschirm (X-Position)
     */
    static const int START_POSITION_X = 230;
    /**
     * @brief START_POSITION_Y Konstante fuer Startposition auf dem Bildschirm (Y-Position)
     */
    static const int START_POSITION_Y = 180;

    /**
     * @brief clear Funktion, um Spielfeld zu loeschen (setzt nochmal Standardbild)
     */
    void clear();

signals:
    /**
     * @brief executeMove Signal, welches die die Information besitzt, welche Zeile geklickt wurde
     * @param column Spalte in die geworfen wird
     */
    void executeMove(unsigned short column);

public slots:

private slots:
    /**
     * @brief on_tblbord_doubleClicked Klickereignis des Tabelle
     * @param index Klasse mit informationen, wohin in der Tabelle geklickt wurde
     */
    void on_tblbord_doubleClicked(const QModelIndex &index);
};

#endif // BORD_H
