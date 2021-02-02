#include "MainWindow.h"

#include <Controller.h>

//debug stuff
#include <iostream>
using std::cout;
using std::endl;
//end debug stuff

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), controller(nullptr)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    addMenus(mainLayout);

    QHBoxLayout *screenLayout = new QHBoxLayout(this);
    mainLayout->addLayout(screenLayout);


    //tree view per rappresentare la struttura ad albero del catalogo
    catalogView = new QTreeWidget(this);
    QSizePolicy catalogPolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    catalogPolicy.setHorizontalStretch(1);
    catalogView->setSizePolicy(catalogPolicy);
    catalogView->setHeaderHidden(true);
    catalogView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    screenLayout->addWidget(catalogView);

    //widget fittizio solo per vedere le proporzioni
    //da sostituire con un widget adatto
    screen = new QWidget(this);
    QSizePolicy widgetPolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    widgetPolicy.setHorizontalStretch(3);
    screen->setSizePolicy(widgetPolicy);
    screenLayout->addWidget(screen);

    setLayout(mainLayout);
    setMinimumSize(QSize(800, 600));
    setWindowIcon(QIcon(":/Icons/katalog.svg"));
    setWindowState(Qt::WindowMaximized);
}

void MainWindow::setController(Controller *c)
{
    controller = c;
    connect(this, SIGNAL(addFile(Katalog::BaseNode*, std::string)), controller, SLOT(addFile(Katalog::BaseNode*, std::string)));
    connect(SaveAction, SIGNAL(triggered(bool)), controller, SLOT(saveCatalog()));
}

void MainWindow::updateTree(Katalog::BaseNode *root)
{
    clearTree();
    if(!root) return;
    auto &files = root->getFiles();
    for(auto i = files.begin(); i != files.end(); i++){
        QTreeWidgetItem *item = new QTreeWidgetItem(catalogView);
        item->setText(0, QString::fromStdString(files[i]->getName()));
        if(files[i]->getFilesCount() > 0){
            updateTreeRecursive(files[i].pointer(), item);
        }
    }
}

void MainWindow::clearTree()
{
    catalogView->clear();
}

void MainWindow::addMenus(QLayout *layout)
{
    QMenuBar *MenuBar = new QMenuBar(this);
    layout->addWidget(MenuBar);

    //File menu
    QMenu *FileMenu = new QMenu("File", MenuBar);
    MenuBar->addMenu(FileMenu);

    QAction *ImportPhoto = new QAction("Importa foto", MenuBar);
    QAction *ImportAudio = new QAction("Importa audio", MenuBar);
    QAction *ImportVideo = new QAction("Importa video", MenuBar);

    FileMenu->addAction(ImportPhoto);
    FileMenu->addAction(ImportAudio);
    FileMenu->addAction(ImportVideo);

    connect(ImportPhoto, SIGNAL(triggered(bool)), this, SLOT(addPhoto()));
    connect(ImportAudio, SIGNAL(triggered(bool)), this, SLOT(addAudio()));
    connect(ImportVideo, SIGNAL(triggered(bool)), this, SLOT(addVideo()));

    FileMenu->addSeparator();
    SaveAction = new QAction("Salva catalogo", FileMenu);
    FileMenu->addAction(SaveAction);

    FileMenu->addSeparator();
    QAction *ExitAction = new QAction("Esci", FileMenu);

    QShortcut *ExitShorcut = new QShortcut(QKeySequence("Ctrl+Q"), this);

    connect(ExitShorcut, SIGNAL(activated()), ExitAction, SIGNAL(triggered()));

    connect(ExitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
    FileMenu->addAction(ExitAction);
    //end file menu

    //edit menu
    QMenu *EditMenu = new QMenu("Modifica", MenuBar);
    MenuBar->addMenu(EditMenu);

    QAction *CopyAction = new QAction("Copia", EditMenu);
    QAction *PasteAction = new QAction("Incolla", EditMenu);
    QAction *CutAction = new QAction("Taglia", EditMenu);
    QAction *RemoveAction = new QAction("Elimina", EditMenu);

    EditMenu->addAction(CopyAction);
    EditMenu->addAction(PasteAction);
    EditMenu->addAction(CutAction);
    EditMenu->addAction(RemoveAction);

    QMenu *ViewMenu = new QMenu("Visualizza", MenuBar);
    MenuBar->addMenu(ViewMenu);

    QAction *GridView = new QAction("Griglia", ViewMenu);
    QAction *PlayView = new QAction("Riproduzione", ViewMenu);

    ViewMenu->addAction(GridView);
    ViewMenu->addAction(PlayView);

    //end edit menu
}

void MainWindow::updateTreeRecursive(Katalog::BaseNode *root, QTreeWidgetItem *itemParent)
{
    auto &files = root->getFiles();
    for(auto i = files.begin(); i != files.end(); i++){
        QTreeWidgetItem *item = new QTreeWidgetItem(itemParent);;
        item->setText(0, QString::fromStdString(files[i]->getName()));
        if(files[i]->getFilesCount() > 0){
            updateTreeRecursive(files[i].pointer(), item);
        }
    }
}

std::string MainWindow::getFileName(std::string &source)
{
    return source.substr(source.find_last_of("/") + 1, source.length());
}

std::string MainWindow::getSelectedFilePath() const
{
    std::string destination = "";
    if(catalogView->selectedItems().empty()) destination = "/";
    else {
        QTreeWidgetItem *item = catalogView->selectedItems()[0];
        destination = "/" + item->text(0).toStdString();
        while((item = item->parent())){
            destination = "/" + item->text(0).toStdString() + destination;
        }
    }
    return destination;
}

void MainWindow::addPhoto()
{
    std::string source = QFileDialog::getOpenFileName(this, tr("Apri foto"), "/home", tr("Immagini (*.png *.jpg)")).toStdString();
    if(source != "") {
        std::string filename = getFileName(source);
        std::string destination = getSelectedFilePath();
        emit addFile(new Katalog::Photo(filename, source), destination);
    }
}

void MainWindow::addAudio()
{
    std::string source = QFileDialog::getOpenFileName(this, tr("Apri foto"), "/home", tr("Audio (*.mp3 *.flac)")).toStdString();
    if(source != "") {
        std::string filename = getFileName(source);
        std::string destination = getSelectedFilePath();
        emit addFile(new Katalog::Audio(filename, source), destination);
    }
}

void MainWindow::addVideo()
{
    std::string source = QFileDialog::getOpenFileName(this, tr("Apri foto"), "/home", tr("Immagini (*.mp4 *.avi)")).toStdString();
    if(source != "") {
        std::string filename = getFileName(source);
        std::string destination = getSelectedFilePath();
        emit addFile(new Katalog::Video(filename, source), destination);
    }
}