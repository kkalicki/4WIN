#ifndef FOURWINITEMDELEGATE_H
#define FOURWINITEMDELEGATE_H
#include <QAbstractItemDelegate>
#include <QStandardItemModel>
#include <QPainter>

class FourWinItemDelegate : public QAbstractItemDelegate
{
public:
    FourWinItemDelegate(QObject *parent=0);
    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
};

#endif // FOURWINITEMDELEGATE_H
