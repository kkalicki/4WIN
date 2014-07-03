#ifndef FOURWINITEMDELEGATE_H
#define FOURWINITEMDELEGATE_H
#include <QAbstractItemDelegate>
#include <QStandardItemModel>
#include <QPainter>

/**
 * @brief The FourWinItemDelegate class
 * Klasse mit deren Hilfe die Zeichenroutine des Speilfeldes bestimmt wird
 */
class FourWinItemDelegate : public QAbstractItemDelegate
{
public:
    /**
     * @brief FourWinItemDelegate Konstruktor feur den Delegaten
     * @param parent Parentobject
     */
    FourWinItemDelegate(QObject *parent=0);
    /**
     * @brief paint Funktion, die bestimmt, wie eine Zelle in dem Spielfeld aussieht
     * @param painter   Painterobject
     * @param option    Obtionen
     * @param index     Index der Zelle
     */
    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    /**
     * @brief sizeHint muss an der Stelle implementiert werden, da rein Virtuell, in dem Fall aber ohne Bedeurtung
     * @param option Obtionen
     * @param index Index der Zelle
     * @return  QSize
     */
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
};

#endif // FOURWINITEMDELEGATE_H
