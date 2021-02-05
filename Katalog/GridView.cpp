#include "GridView.h"

GridView::GridView(const FileList *fileVector, QWidget *parent) : QWidget(parent), files(fileVector)
{
    grid = new FlowLayout(this, 20, 10, 10);

    /*for(auto i = files.begin(); i != files.end(); i++)
    {
        PreviewWindow* icon = new PreviewWindow(files[i].pointer(), this);
        connect(icon, SIGNAL(mouseDoubleClicked(Katalog::BaseNode*)), this, SIGNAL(doubleClickedItem(Katalog::BaseNode*)));
        grid->addWidget(icon);
    }*/
    setLayout(grid);

    setAttribute(Qt::WA_DeleteOnClose, true);
}

void GridView::redrawGrid()
{
    delete grid;
    grid = new FlowLayout(this, 20, 10, 10);

    setLayout(grid);
    for(auto i = files->begin(); i != files->end(); i++)
    {
        PreviewWindow* icon = new PreviewWindow((*files)[i].pointer(), this);
        connect(icon, SIGNAL(mouseDoubleClicked(Katalog::BaseNode*)), this, SIGNAL(doubleClickedItem(Katalog::BaseNode*)));
        grid->addWidget(icon);
    }

}




