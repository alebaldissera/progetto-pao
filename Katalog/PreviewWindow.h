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
#include <QPainter>
#include <QStyleOption>
#include <QMouseEvent>
#include <sstream>
#include <QThread>

class ImageLoader;

/**
 * @brief Widget che si occupa di mostrare un'anteprima del file
 */
class PreviewWindow : public QWidget
{
    Q_OBJECT
    friend class ImageLoader;
public:
    /**
     * @brief PreviewWindow: mostra l'anteprima del file a seconda del tipo del file
     * @param sel_file: è il file selezionato dall'utente
     * @param parent: è il parent del widget
     */
    explicit PreviewWindow(Katalog::BaseNode* sel_file, QWidget *parent = nullptr);
    ~PreviewWindow();

signals:
    /**
     * @brief mouseDoubleClicked Segnale emesso quando si fa doppio click sul widget
     */
    void mouseDoubleClicked(Katalog::BaseNode*);

private:
    /**
     * @brief enterEvent Gestore dell'evento generato quando il puntatore del mouse entra nel widget
     * @param event
     */
    void enterEvent(QEvent *event);
    /**
     * @brief leaveEvent Gestore dell'evento generato quando il puntatore del mouse esce dal widget
     * @param event
     */
    void leaveEvent(QEvent *event);
    /**
     * @brief paintEvent gestore dell'evento generato quando si cambia l'aspetto del widget
     * @param event
     */
    void paintEvent(QPaintEvent *event);
    /**
     * @brief mouseDoubleClickEvent gestore dell'evento di doppio click
     * @param event
     */
    void mouseDoubleClickEvent(QMouseEvent *event);

    QColor defaultColor;
    Katalog::BaseNode *filePtr;
    QLabel *icon;
    ImageLoader *il;
};

/*
 * Classe per caricare attraverso un thread secondario le immagini delle PreviewWindow
 * Si è scelto di usare l'amicizia tra classi in quanto le due sono strettamente legate tra loro
 * Purtroppo non può esser creata come sotto-classe di PreviewWindow essendo un Q_OBJECT
 */
class ImageLoader: public QThread {
    friend class PreviewWindow;
    Q_OBJECT
private:
    ImageLoader(PreviewWindow *w, QString file, QWidget *parent = nullptr);
    ~ImageLoader();
    void run() override;
    PreviewWindow *obj;
    QString path;
    QImage *img;
};

#endif // PREVIEWWINDOW_H
