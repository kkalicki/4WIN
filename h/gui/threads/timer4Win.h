#ifndef TIMER4WIN_H
#define TIMER4WIN_H
#include <QObject>

/**
 * @brief The Timer4Win class
 * Klasse, mit deren Hilfe die GUI aktualisiert wird. Mit dieser Klasse wird die Zeit in dem Spielerinfo formular aktualisiert
 * Die Klasse triggert das Signal an die GUI und. Dies muss in einem eigenen Thread passieren, da nicht von dem Netwzerkthread direkt auf die GUI
 * zugefriffen werden darf!
 */
class Timer4Win : public QObject
{
   Q_OBJECT

public:
    /**
    * @brief Timer4Win
    * Konstruktor der Klasse
    */
   Timer4Win();
   ~Timer4Win();

   /**
    * @brief stop
    * Funktion, um die Aktualisierung und damit auch die Uhr zu stoppen
    */
   void stop();

public slots:
   /**
     * @brief process
     * Funktion in dem Thread die die Uhr aktualisiert
     */
    void process();
private:
    /**
     * @brief SLEEP_TIME
     * Konstante, die gewartet werden soll, hier 1 sekunde, danach die naechste Aktualisierung
     */
    static const unsigned long SLEEP_TIME = 1;

    /**
     * @brief isStop
     * Flag um zu pruefen, ob die Uhr am laufen ist
     */
    int isStop;

signals:
    /**
     * @brief timeChange
     * Signal, welches die Funktion zum aktualisieren der Zeit in der GUI aufruft
     */
    void timeChange();
};

#endif // TIMER4WIN_H
