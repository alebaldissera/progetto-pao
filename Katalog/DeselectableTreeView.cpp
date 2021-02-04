#include "DeselectableTreeView.h"

//debug stuff
#include <iostream>
using std::cout;
using std::endl;
//end debug stuff

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
