#include "icondelegate.h"


IconDelegate::IconDelegate(QObject *parent): QStyledItemDelegate(parent) {

}

void IconDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,    const QModelIndex & index ) const
{
    //判断是不是icon所在的index

    if(index.column()!=0 && index.row()!=0){
                 QStyledItemDelegate::paint(painter,option,index);
                         return;
    }

    QPixmap pixmap ;
    QVariant v= index.model()->data(index, Qt::DecorationRole);
    QIcon icon = v.value<QIcon>();
    pixmap = icon.pixmap(option.rect.width(),option.rect.height());
    if(pixmap.isNull()){
        QString data = index.model()->data(index, Qt::UserRole).toString();
        pixmap = QPixmap(data);
        pixmap = pixmap.scaled(option.rect.width(),option.rect.height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    }
    qApp->style()-> drawItemPixmap(painter, option.rect,  Qt::AlignCenter, QPixmap(pixmap));

    if (option.state & QStyle::State_Selected )   {
        //话选中框
        QPen pen(QColor("#FFD700"));
        pen.setWidth(1);
        painter->setPen(pen);
        painter->setBrush(QColor("#99BFEFFF"));
        painter->drawRect(option.rect.left(),option.rect.top(),option.rect.width()-1,option.rect.height()-1);
    }

}

