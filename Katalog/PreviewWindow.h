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

/*
 * View per mostrare l'anteprima del file aggiunto: cambia a seconda del tipo del file inserito.
 */
class ImageLoader;

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
private:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    QColor defaultColor;
    Katalog::BaseNode *filePtr;
    QLabel *icon;
    ImageLoader *il;
signals:
    void mouseDoubleClicked(Katalog::BaseNode*);
};

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
