#ifndef VISITORTHREAD_H
#define VISITORTHREAD_H

#include <QObject>
#include "../h/net/msg/visitorpackage.h"

/**
 * @brief The VisitorThread class
 * Klasse, mit deren Hilfe die GUI aktualisiert wird, wenn das System sich im Zuschauermodus befindet.
 * Die Klasse triggert das Signal an die GUI und. Dies muss in einem eigenen Thread passieren, da nicht von dem Netwzerkthread direkt auf die GUI
 * zugefriffen werden darf!
 */
class VisitorThread : public QObject
{
   Q_OBJECT

public:
    /**
    * @brief VisitorThread
    * @param vp             VisitorPackage Klasse, mit allen Informationen fuer den Zuschauermodus
    * @param lastround      Letzte Rounde, die im lokalen System gezogen wurde
    */
   VisitorThread(VisitorPackage vp, int lastround);
   ~VisitorThread();

public slots:
   /**
     * @brief process
     * Funktion in dem Thread, die im Zuschauermodus die GUI aktualisiert
     */
    void process();

private:
    /**
     * @brief vp
     * VisitorPackage Klasse, welche alle Informationen fuer den Zuschauermodus beinhaltet
     */
    VisitorPackage vp;
    /**
     * @brief lastround
     * Letzte Rounde, die im lokalen System gezogen wurde
     */
    int lastround;
signals:
    /**
    * @brief updateGui
    * @param col
    * Signal, welches die Funktion fuer die Zuege in der GUI aufruft
    */
   void updateGui(unsigned short col);
};

#endif // VISITORTHREAD_H
