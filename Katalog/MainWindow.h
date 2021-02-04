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
#include <DeselectableTreeView.h>
#include <QShortcut>
#include <QFileDialog>
#include <GridView.h>

#include <BaseNode.h>

class Controller;

typedef Katalog::vector<std::string> PathList;
typedef Katalog::vector<Katalog::DeepPtr<Katalog::BaseNode>> FileList;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void setController(Controller *c);
    void updateTree(const Katalog::BaseNode* root);
    void clearTree();
    void showGrid(const FileList& files);

private:
    DeselectableTreeView *catalogView;
    QWidget *screen;
    QHBoxLayout *screenLayout;

    //menu actions
    QAction *SaveAction;

    Controller *controller;

    void addMenus(QLayout *layout);
    void updateTreeRecursive(const Katalog::BaseNode* root, QTreeWidgetItem *itemParent);
    static std::string getFileName(std::string &source);
    std::string getSelectedFilePath() const;
    void setTreeWidgetItemExtras(QTreeWidgetItem *item, Katalog::BaseNode* file);
    static std::string getItemPath(QTreeWidgetItem* item);

signals:
    void addFile(Katalog::BaseNode*, std::string destination);

private slots:
    void addPhoto();
    void addAudio();
    void addVideo();
    void doubleClickOnGridItem(Katalog::BaseNode*);
};

#endif // MAINWINDOW_H
