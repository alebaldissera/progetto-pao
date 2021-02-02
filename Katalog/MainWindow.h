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
#include <QShortcut>
#include <QFileDialog>

#include <BaseNode.h>

class Controller;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void setController(Controller *c);
    void updateTree(Katalog::BaseNode* root);
    void clearTree();

private:
    QTreeWidget *catalogView;
    QWidget *screen;

    //menu actions
    QAction *SaveAction;

    Controller *controller;

    void addMenus(QLayout *layout);
    void updateTreeRecursive(Katalog::BaseNode* root, QTreeWidgetItem *itemParent);
    static std::string getFileName(std::string &sou0rce);
    std::string getSelectedFilePath() const;

signals:
    void addFile(Katalog::BaseNode*, std::string destination);

private slots:
    void addPhoto();
    void addAudio();
    void addVideo();

};

#endif // MAINWINDOW_H
