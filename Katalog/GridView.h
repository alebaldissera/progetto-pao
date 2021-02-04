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

class GridView : public QWidget
{
    Q_OBJECT
public:
    explicit GridView(Katalog::vector<Katalog::DeepPtr<Katalog::BaseNode>> fileVector,QWidget *parent = nullptr);
    virtual ~GridView() = default;
signals:

};

#endif // GRIDVIEW_H
