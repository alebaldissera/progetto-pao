#include "DeselectableTreeView.h"

DeselectableTreeView::DeselectableTreeView(QWidget *parent): QTreeWidget(parent) {}

DeselectableTreeView::~DeselectableTreeView() {}

void DeselectableTreeView::mousePressEvent(QMouseEvent *event)
{
    QModelIndex item = indexAt(event->pos());
    bool selected = selectionModel()->isSelected(item);
    QTreeView::mousePressEvent(event);
    if(!selected)
        selectionModel()->clearSelection();
}
