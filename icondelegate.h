#ifndef ICONDELEGATE_H
#define ICONDELEGATE_H

#include <QObject>
#include<QStyledItemDelegate>
#include<QApplication>
#include<QPainter>
class IconDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    public:
    IconDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,   const QModelIndex & index ) const;

};


#endif // ICONDELEGATE_H
