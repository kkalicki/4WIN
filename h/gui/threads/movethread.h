#ifndef GUIUPDATER_H
#define GUIUPDATER_H

#include   <QObject>

/**
 * @brief The MoveThread class
 * Klasse, mit deren Hilfe die GUI aktualisiert wird, wenn der Gegner einen Remotezug gesendet hat
 * Die Klasse triggert das Signal an die GUI und. Dies muss in einem eigenen Thread passieren, da nicht von dem Netwzerkthread direkt auf die GUI
 * zugefriffen werden darf!
 */
class MoveThread : public QObject
{
   Q_OBJECT

public:
    /**
     * Konstruktor der Klasse
     * @brief MoveThread
     * @param column    Spalte, in die geworfen wird
     * @param row       Zeile, in die geworfen wird
     */
    MoveThread(unsigned short column, int row);
public slots:
    /**
     * @brief process
     * Funktion die in dem Thread ausgeführt wird, um den Remote-Zug an die GUI weiter zu leiten
     */
    void process();
signals:
    /**
     * @brief updateGui
     * @param column    Spalte, in die geworfen wird
     * @param row       Zeile, in die geworfen wird
     * Signal, welches die Funktion, on_incomingMove in der GUI ausloest
     */
    void updateGui(unsigned short column, int row);

private:
    /**
     * @brief column
     * Spalte, in die geworfen wird
     */
    unsigned short column;
    /**
     * @brief row
     * Zeile, in die geworfen wird
     */
    int row;
};
#endif // GUIUPDATER_H
