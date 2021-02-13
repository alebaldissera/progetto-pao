#include "GridView.h"

GridView::GridView(const FileList *fileVector, QWidget *parent) : QWidget(parent), files(fileVector)
{
    grid = new FlowLayout(this, 20, 10, 10);
    QScrollArea* scroll = new QScrollArea(this);
    scroll->setVisible(true);
    scroll->setWidgetResizable(true);
    //scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QWidget *aux = new QWidget(this);
    aux->setLayout(grid);
    scroll->setWidget(aux);

    if(files) {
        for(auto i = files->begin(); i != files->end(); i++)
        {
            PreviewWindow* icon = new PreviewWindow((*files)[i].pointer(), this);
            connect(icon, SIGNAL(mouseDoubleClicked(Katalog::BaseNode*)), this, SIGNAL(doubleClickedItem(Katalog::BaseNode*)));
            grid->addWidget(icon);
        }
    }

    QBoxLayout *l = new QBoxLayout(QBoxLayout::TopToBottom, this);
    l->setMargin(0);
    l->setSpacing(0);
    l->addWidget(scroll);
    setLayout(l);

    setAttribute(Qt::WA_DeleteOnClose, true);
}

void GridView::setFiles(const FileList* filesVector)
{
    if(filesVector == files) return;
    files = filesVector;
    redrawGrid();
}

void GridView::redrawGrid()
{
    QLayoutItem *item;
    while ((item = grid->takeAt(0)))
    {
        item->widget()->close();
        delete item;
    }
    if(files)
    {
        for(auto i = files->begin(); i != files->end(); i++)
        {
            PreviewWindow* icon = new PreviewWindow((*files)[i].pointer(), this);
            connect(icon, SIGNAL(mouseDoubleClicked(Katalog::BaseNode*)), this, SIGNAL(doubleClickedItem(Katalog::BaseNode*)));
            grid->addWidget(icon);
        }
    }

}




