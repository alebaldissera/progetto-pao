#ifndef PREVIEWWINDOW_H
#define PREVIEWWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QLabel>
#include <QIcon>
#include "DeepPtr.h"
#include "BaseNode.h"
#include "Photo.h"
#include "Video.h"
#include "Audio.h"

/*
 * View per mostrare l'anteprima del file aggiunto: cambia a seconda del tipo del file inserito.
 * Pensata per essere gestita completamente dal controller
 */

class PreviewWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PreviewWindow(Katalog::BaseNode* sel_file, QWidget *parent);

signals:

};

#endif // PREVIEWWINDOW_H
