#include "../h/gui/fourwinitemdelegate.h"

FourWinItemDelegate::FourWinItemDelegate(QObject *parent) : QAbstractItemDelegate(parent){

}

void FourWinItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const{

    if(option.state & QStyle::State_Selected){
        painter->fillRect(option.rect, option.palette.color(QPalette::Highlight));
    }

    QIcon ic = QIcon(qvariant_cast<QPixmap>(index.data(Qt::DecorationRole)));
    QString txt = index.data(Qt::DisplayRole).toString();
    QRect r = option.rect.adjusted(0, 0, 0, 0);
    ic.paint(painter, r, Qt::AlignVCenter|Qt::AlignLeft);
    r = r.adjusted(r.height()+20, 0, 0, 0);
    painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignVCenter|Qt::AlignLeft|Qt::TextWordWrap, txt, &r);
}

QSize FourWinItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const{

    return QSize();
}
