/**
  Soluzione trovata tra le risposte di questo forum:
  https://www.generacodice.com/en/articolo/899637/Is-it-possible-to-deselect-in-a-QTreeView-by-clicking-off-an-itema=r
  */

#ifndef DESELECTABLETREEVIEW_H
#define DESELECTABLETREEVIEW_H

#include <QObject>

#include <QTreeWidget>
#include <QMouseEvent>

class DeselectableTreeView: public QTreeWidget
{
Q_OBJECT
public:
    explicit DeselectableTreeView(QWidget *parent);
    ~DeselectableTreeView() = default;

signals:
    void itemsDeselected();

private:
    virtual void mousePressEvent(QMouseEvent *event);
};

#endif // DESELECTABLETREEVIEW_H
