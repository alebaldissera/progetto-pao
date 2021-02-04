#include "GridView.h"

GridView::GridView(Katalog::vector<Katalog::DeepPtr<Katalog::BaseNode>> fileVector, QWidget *parent) : QWidget(parent)
{
    FlowLayout* grid = new FlowLayout(this);

    for(auto i = fileVector.begin(); i != fileVector.end(); i++)
    {
        PreviewWindow* icon = new PreviewWindow(fileVector[i].pointer(), this);
        grid->addWidget(icon);
    }

    setLayout(grid);
}




