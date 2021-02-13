#include "Controller.h"

Controller::Controller(Katalog::Catalogo &cat, MainWindow &mw, QObject *parent) : QObject(parent), catalogo(cat), mainwindow(mw)
{
    LoadingView lv;
    lv.show();

    mainwindow.setController(this);

    catalogo = Katalog::IOManager::importCatalogFromFile("Katalog.xml");
    mainwindow.updateTree(catalogo.getRoot().pointer());
    mainwindow.showGrid(&catalogo.getRoot()->getFiles());

    mainwindow.show();
    lv.close();
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
    if(file->getFilesCount() > 0){
        mainwindow.showGrid(&file->getFiles());
    }
}

void Controller::treeItemDoubleClicked(QTreeWidgetItem *item, int col)
{
    Katalog::BaseNode* file = catalogo.getFile(getItemPath(item));
    if(file->getFilesCount() == 0 && (dynamic_cast<Katalog::Photo*>(file) || dynamic_cast<Katalog::Audio*>(file) || dynamic_cast<Katalog::Video*>(file)))
        mainwindow.showPlayWindow(file);
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
        mainwindow.showPlayWindow(static_cast<Katalog::BaseNode*>(nullptr));
        mainwindow.showGrid(nullptr);
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
        mainwindow.showGrid(&catalogo.getFile(dest)->getFiles());
        emit catalogUpdated();
    }
}

void Controller::removeFile(std::string file)
{
    try {
        //prima tolgo tutti i riferimenti agli elementi della view in modo da evitare di dereferenziare del garbage quando si fa un update
        mainwindow.showGrid(nullptr);
        mainwindow.showPlayWindow(static_cast<Katalog::BaseNode*>(nullptr)); //devo fare la conversione per non avere ambiguità con gli overload delle funzioni
        catalogo.remove(file);
        mainwindow.updateTree(catalogo.getRoot().pointer());
        mainwindow.showGrid(&catalogo.getRoot()->getFiles());
        emit catalogUpdated();
    } catch (std::runtime_error &e){
        QMessageBox::critical(nullptr, "Errore", e.what());
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
        if(catalogo.getFile(path)->getFilesCount())
           mainwindow.showGrid(&catalogo.getFile(path)->getFiles());
        else
           mainwindow.showPlayWindow(catalogo.getFile(path));
        mainwindow.selectFileOnTree(path);
    }  catch (std::runtime_error &e) { //il file non esiste resetto la path
        mainwindow.resetTextPath();
        QMessageBox::critical(nullptr, "File non valido", "Path inserita non valida");
    }

}

void Controller::requestForGridView()
{
    std::string path = mainwindow.getTextPath();
    if(catalogo.getFile(path)->getFilesCount() > 0){
        mainwindow.showGrid(&catalogo.getFile(path)->getFiles());
    }
}

void Controller::requestForPlayView()
{
    std::string path = mainwindow.getTextPath();
    mainwindow.showPlayWindow(&catalogo.getFile(path)->getFiles());
}

std::string Controller::getItemPath(QTreeWidgetItem *item)
{
    string path = "/" + item->text(0).toStdString();
    while((item = item->parent()))
        path = "/" + item->text(0).toStdString() + path;
    return path;
}
