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

typedef Katalog::vector<Katalog::DeepPtr<Katalog::BaseNode>> FileList;

class GridView : public QWidget
{
    Q_OBJECT
public:
    explicit GridView(const FileList &fileVector, QWidget *parent = nullptr);
    virtual ~GridView() = default;
public slots:
    void redrawGrid();

signals:
    void doubleClickedItem(Katalog::BaseNode*);

private:
    const FileList &files;
    FlowLayout* grid;
};

#endif // GRIDVIEW_H
