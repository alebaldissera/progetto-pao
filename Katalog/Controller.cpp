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
    }catch (std::runtime_error &e){
        cout << e.what() << endl;
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
    cout << "SALVATAGGIO CATALOGO" << endl;
    if(catalogo.isChanged())
        Katalog::IOManager::exportCatalogToFile(catalogo, "Katalog.xml");
}
