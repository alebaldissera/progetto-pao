#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include <QWidget>
#include <QLabel>
#include <QIcon>
#include "DeepPtr.h"
#include "BaseNode.h"
#include "Photo.h"
#include "Video.h"
#include "Audio.h"
#include "FlowLayout.h"
#include "PreviewWindow.h"
#include <QScrollArea>
#include <QBoxLayout>

typedef Katalog::vector<Katalog::DeepPtr<Katalog::BaseNode>> FileList;

/**
 * @brief Il widget che si occupa di rappresentare la griglia delle anteprime dei file
 */
class GridView : public QWidget
{
    Q_OBJECT
public:
    explicit GridView(const FileList *fileVector, QWidget *parent = nullptr);
    virtual ~GridView() = default;

public slots:
    /**
     * @brief redrawGrid Richiesta di ridesegnare la griglia
     */
    void redrawGrid();
    /**
     * @brief setFiles Imposta la lista dei file da visualizzare
     * @param filesVector Lista dei file
     */
    void setFiles(const FileList* filesVector);

signals:
    /**
     * @brief doubleClickedItem segnale emesso quando avviene un doppio click su un oggetto della griglia
     */
    void doubleClickedItem(Katalog::BaseNode*);

private:
    const FileList *files;
    FlowLayout* grid;
};

#endif // GRIDVIEW_H
