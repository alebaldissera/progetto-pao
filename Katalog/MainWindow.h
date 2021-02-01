#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLayout>
#include <QSizePolicy> //necessaria per la divisione in percentuale dei widget in un layout

#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include <QTreeWidget>


class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void addMenus(QLayout *layout);
    QTreeWidget *catalogView;
    QWidget *screen;


signals:

};

#endif // MAINWINDOW_H
