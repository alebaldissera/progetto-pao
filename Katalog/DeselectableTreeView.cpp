#include "DeselectableTreeView.h"

DeselectableTreeView::DeselectableTreeView(QWidget *parent): QTreeWidget(parent) {}

void DeselectableTreeView::mousePressEvent(QMouseEvent *event)
{
    QModelIndex item = indexAt(event->pos());
    if(item.isValid()){
        QTreeView::mousePressEvent(event);
    } else {
        clearSelection();
        emit itemsDeselected();
    }
}
