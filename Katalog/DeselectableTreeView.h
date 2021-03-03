#ifndef DESELECTABLETREEVIEW_H
#define DESELECTABLETREEVIEW_H

#include <QObject>
#include <QTreeWidget>
#include <QMouseEvent>

/**
 * @brief Widget di un QTreeWidget che supporta la deselezione degli elementi
 */
class DeselectableTreeView: public QTreeWidget
{
Q_OBJECT
public:
    explicit DeselectableTreeView(QWidget *parent);
    ~DeselectableTreeView() = default;

signals:
    /**
     * @brief itemsDeselected Segnale emesso quando vengono deselezionati tutti gli elementi
     */
    void itemsDeselected();

protected:
    /**
     * @brief mousePressEvent Definizione delle azioni da intraprendere quando viene premuto il mouse sul widget
     * @param event
     */
    virtual void mousePressEvent(QMouseEvent *event);
};

#endif // DESELECTABLETREEVIEW_H
