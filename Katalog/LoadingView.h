#ifndef LOADINGVIEW_H
#define LOADINGVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QLabel>
#include <QIcon>

#include <QScreen>
#include <QGuiApplication>

/*
 * View da mostrare nei caricamenti dal filesystem e da distruggere una volta completati
 * Pensata per essere gestita completamente dal controller
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
