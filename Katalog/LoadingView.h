#ifndef LOADINGVIEW_H
#define LOADINGVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QLabel>
#include <QIcon>

#include <QScreen>
#include <QGuiApplication>

/**
 * @brief Finestra di caricamento
 */
class LoadingView : public QWidget
{
    Q_OBJECT
public:
    explicit LoadingView(QWidget *parent = nullptr);
    ~LoadingView() = default;

signals:

};

#endif // LOADINGVIEW_H
