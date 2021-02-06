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
        mainwindow.showGrid(&catalogo.getRoot()->getFiles());
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
    emit catalogUpdated();
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

void Controller::treeItemClicked(QTreeWidgetItem *item, int col)
{
    Katalog::BaseNode* file = catalogo.getFile(getItemPath(item));
    if(file->getFilesCount()){
        mainwindow.showGrid(&file->getFiles());
    }
}

void Controller::viewGridOnRoot()
{
    mainwindow.showGrid(&catalogo.getRoot()->getFiles());
}

void Controller::copyFile(std::string file)
{
    clip = file;
    operation = true;
}

void Controller::cutFile(std::string file)
{
    clip = file;
    operation = false;
}

void Controller::pasteFile(std::string dest)
{
    if(clip != ""){
        if(operation) //copia
        {
            auto* file = catalogo.getFile(clip);
            catalogo.add(file->clone(), dest);
        }
        else
        {
            if(clip != dest)
                catalogo.move(clip, dest);
        }
        clip = "";
        mainwindow.updateTree(catalogo.getRoot().pointer());
        emit catalogUpdated();
    }
}

void Controller::removeFile(std::string file)
{
    try {
        catalogo.remove(file);
        mainwindow.updateTree(catalogo.getRoot().pointer());
        emit catalogUpdated();
    } catch (std::runtime_error &e){
        cout << e.what() << endl;
    }
}

void Controller::renameFile(std::string file, std::string newName)
{
    catalogo.setFileName(file, newName);
    mainwindow.updateTree(catalogo.getRoot().pointer());
    emit catalogUpdated();
}

void Controller::pathTextChanged()
{
    std::string path = mainwindow.getTextPath();
    try {
        mainwindow.showGrid(&catalogo.getFile(path)->getFiles());
        mainwindow.selectFileOnTree(path);
    }  catch (std::runtime_error &e) { //il file non esiste resetto la path
        mainwindow.resetTextPath();
        QMessageBox::critical(nullptr, "File non valido", "Path inserita non valida");
    }

}

std::string Controller::getItemPath(QTreeWidgetItem *item)
{
    string path = "/" + item->text(0).toStdString();
    while((item = item->parent()))
        path = "/" + item->text(0).toStdString() + path;
    return path;
}
