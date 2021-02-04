#include "Controller.h"

//debug stuff
#include <iostream>
using std::cout;
using std::endl;
//end debug stuff

Controller::Controller(Katalog::Catalogo &cat, MainWindow &mw, QObject *parent) : QObject(parent), catalogo(cat), mainwindow(mw)
{
    LoadingView *lw = new LoadingView;
    lw->show();
    mainwindow.setController(this);

    try{
        catalogo = Katalog::IOManager::importCatalogFromFile("Katalog.xml");
        mainwindow.updateTree(catalogo.getRoot().pointer());
    }catch (std::runtime_error &e){
        QMessageBox m(QMessageBox::Critical, "Errore lettura catalog", e.what(), QMessageBox::Cancel);
    }

    mainwindow.show();
    delete lw;
}

void Controller::addFile(Katalog::BaseNode *file, std::string destination)
{
    catalogo.add(file, destination);
    mainwindow.updateTree(catalogo.getRoot().pointer());
}

void Controller::saveCatalog()
{
    if(catalogo.isChanged())
        Katalog::IOManager::exportCatalogToFile(catalogo, "Katalog.xml");
}

void Controller::openDirectory(QTreeWidgetItem *node)
{
    std::string path = getItemPath(node);
    catalogo.setFileAsOpened(path);
}

void Controller::closeDirectory(QTreeWidgetItem *node)
{
    std::string path = getItemPath(node);
    catalogo.setFileAsClosed(path);
}

std::string Controller::getItemPath(QTreeWidgetItem *item)
{
    string path = "/" + item->text(0).toStdString();
    while((item = item->parent()))
        path = "/" + item->text(0).toStdString() + path;
    return path;
}
