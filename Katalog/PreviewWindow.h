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
 */

class PreviewWindow : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief PreviewWindow: mostra l'anteprima del file a seconda del tipo del file
     * @param sel_file: è il file selezionato dall'utente
     * @param parent: è il parent del widget
     */
    explicit PreviewWindow(Katalog::BaseNode* sel_file, QWidget *parent);

signals:

};

#endif // PREVIEWWINDOW_H
