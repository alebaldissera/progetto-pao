#include "MainWindow.h"

#include <Controller.h>

//debug stuff
#include <iostream>
using std::cout;
using std::endl;
//end debug stuff

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), controller(nullptr)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(5);
    mainLayout->setMargin(5);
    addMenus(mainLayout);

    //tree view per rappresentare la struttura ad albero del catalogo
    catalogView = new DeselectableTreeView(this);
    QSizePolicy catalogPolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    catalogPolicy.setHorizontalStretch(1);
    catalogView->setSizePolicy(catalogPolicy);
    catalogView->setHeaderHidden(true);
    catalogView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    connect(catalogView, SIGNAL(itemSelectionChanged()), this, SLOT(updatePathString()));
    mainLayout->addWidget(catalogView);

    QWidget *aux = new QWidget(this); //lo uso solo per determinare le proporzioni tra treewidget e seconda parte dello schermo
    QSizePolicy widgetPolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    widgetPolicy.setHorizontalStretch(3);
    aux->setSizePolicy(widgetPolicy);
    mainLayout->addWidget(aux);

    //creo il layout che conterrà la barra con la paht e la griglia con i file
    screenLayout = new QVBoxLayout(this);
    aux->setLayout(screenLayout);
    screenLayout->setMargin(0);

    stackLayout = new QStackedLayout(this);
    stackLayout->setMargin(0);
    stackLayout->setSpacing(0);
    pathEditor = new QLineEdit("/", this);

    screenLayout->addWidget(pathEditor);
    screenLayout->addLayout(stackLayout);

    grid = new GridView(nullptr, this);
    connect(grid, SIGNAL(doubleClickedItem(Katalog::BaseNode*)), this, SLOT(doubleClickOnGridItem(Katalog::BaseNode*)));


    stackLayout->addWidget(grid);

    player = new VideoPlayer(static_cast<Katalog::BaseNode*>(nullptr), this);
    stackLayout->addWidget(player);

    stackLayout->setCurrentIndex(0);

    setLayout(mainLayout);
    setMinimumSize(QSize(800, 600));
    setWindowIcon(QIcon(":/Icons/katalog.svg"));
    setWindowState(Qt::WindowMaximized);
}

void MainWindow::setController(Controller *c)
{
    controller = c;
    connect(this, SIGNAL(addFile(Katalog::BaseNode*,std::string)), controller, SLOT(addFile(Katalog::BaseNode*,std::string)));

    connect(SaveAction, SIGNAL(triggered(bool)), controller, SLOT(saveCatalog()));
    connect(GridViewAction, SIGNAL(triggered(bool)), controller, SLOT(requestForGridView()));
    connect(PlayViewAction, SIGNAL(triggered(bool)), controller, SLOT(requestForPlayView()));

    connect(catalogView, SIGNAL(itemExpanded(QTreeWidgetItem*)), controller, SLOT(openDirectory(QTreeWidgetItem*)));
    connect(catalogView, SIGNAL(itemCollapsed(QTreeWidgetItem*)), controller, SLOT(closeDirectory(QTreeWidgetItem*)));
    connect(catalogView, SIGNAL(itemClicked(QTreeWidgetItem*,int)), controller, SLOT(treeItemClicked(QTreeWidgetItem*,int)));
    connect(catalogView, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), controller, SLOT(treeItemDoubleClicked(QTreeWidgetItem*,int)));
    connect(catalogView, SIGNAL(itemsDeselected()), controller, SLOT(viewGridOnRoot()));
    connect(this, SIGNAL(fileCopied(std::string)), controller, SLOT(copyFile(std::string)));
    connect(this, SIGNAL(fileCutted(std::string)), controller, SLOT(cutFile(std::string)));
    connect(this, SIGNAL(filePasted(std::string)), controller, SLOT(pasteFile(std::string)));
    connect(this, SIGNAL(fileRemoved(std::string)), controller, SLOT(removeFile(std::string)));
    connect(this, SIGNAL(fileRenamed(std::string,std::string)), controller, SLOT(renameFile(std::string,std::string)));
    connect(pathEditor, SIGNAL(returnPressed()), controller, SLOT(pathTextChanged()));
    connect(controller, SIGNAL(catalogUpdated()), grid, SLOT(redrawGrid()));
}

void MainWindow::updateTree(const Katalog::BaseNode *root)
{
    clearTree();
    if(!root) return;
    auto &files = root->getFiles();
    Katalog::vector<QTreeWidgetItem*> openItem;
    for(auto i = files.begin(); i != files.end(); i++){
        QTreeWidgetItem *item = new QTreeWidgetItem(catalogView);
        setTreeWidgetItemExtras(item, files[i].pointer());
        item->setText(0, QString::fromStdString(files[i]->getName()));
        if(files[i]->getFilesCount() > 0){
            updateTreeRecursive(files[i].pointer(), item);
        }
        item->setExpanded(files[i]->isOpen());
    }
}

void MainWindow::clearTree()
{
    catalogView->clear();
}

void MainWindow::showGrid(const FileList *files)
{
    player->setFile(nullptr);
    stackLayout->setCurrentWidget(grid);
    grid->setFiles(files);
}

void MainWindow::selectFileOnTree(std::string path)
{
    std::string filename = getFileName(path);
    auto nodes = catalogView->findItems(QString::fromStdString(filename), Qt::MatchFixedString | Qt::MatchCaseSensitive, 0);
    for(auto i = nodes.begin(); i != nodes.end(); ++i){
        if(getItemPath(*i) == path){
            catalogView->clearSelection();
            (*i)->setSelected(true);
        }
    }
}

void MainWindow::showPlayWindow(const Katalog::BaseNode *file)
{
    //grid->setFiles(nullptr);
    stackLayout->setCurrentWidget(player);
    player->setFile(file);
}

void MainWindow::showPlayWindow(const FileList *files)
{
    //grid->setFiles(nullptr);
    stackLayout->setCurrentWidget(player);
    player->setFolder(files);
}

void MainWindow::resetTextPath()
{
    pathEditor->setText(QString::fromStdString(getSelectedFilePath()));
}

std::string MainWindow::getTextPath()
{
    return pathEditor->text().toStdString();
}

void MainWindow::addMenus(QLayout *layout)
{
    QMenuBar *MenuBar = new QMenuBar(this);
    layout->setMenuBar(MenuBar);

    //File menu
    QMenu *FileMenu = new QMenu("File", MenuBar);
    MenuBar->addMenu(FileMenu);

    QAction *ImportPhoto = new QAction("Importa foto", MenuBar);
    QAction *ImportAudio = new QAction("Importa audio", MenuBar);
    QAction *ImportVideo = new QAction("Importa video", MenuBar);
    QAction *CreateDirectory = new QAction("Crea cartella", MenuBar);

    ImportPhoto->setShortcut(QKeySequence("Ctrl+I"));
    ImportPhoto->setShortcutVisibleInContextMenu(true);
    ImportAudio->setShortcut(QKeySequence("Ctrl+A"));
    ImportAudio->setShortcutVisibleInContextMenu(true);
    ImportVideo->setShortcut(QKeySequence("Ctrl+M"));
    ImportVideo->setShortcutVisibleInContextMenu(true);
    CreateDirectory->setShortcut(QKeySequence("Ctrl+N"));
    CreateDirectory->setShortcutVisibleInContextMenu(true);

    FileMenu->addAction(ImportPhoto);
    FileMenu->addAction(ImportAudio);
    FileMenu->addAction(ImportVideo);
    FileMenu->addAction(CreateDirectory);

    connect(ImportPhoto, SIGNAL(triggered(bool)), this, SLOT(addPhoto()));
    connect(ImportAudio, SIGNAL(triggered(bool)), this, SLOT(addAudio()));
    connect(ImportVideo, SIGNAL(triggered(bool)), this, SLOT(addVideo()));
    connect(CreateDirectory, SIGNAL(triggered(bool)), this, SLOT(addDirectory()));

    FileMenu->addSeparator();
    SaveAction = new QAction("Salva catalogo", FileMenu);

    SaveAction->setShortcut(QKeySequence("Ctrl+S"));
    SaveAction->setShortcutVisibleInContextMenu(true);

    FileMenu->addAction(SaveAction);

    FileMenu->addSeparator();
    QAction *ExitAction = new QAction("Esci", FileMenu);

    ExitAction->setShortcut(QKeySequence("Ctrl+Q"));
    ExitAction->setShortcutVisibleInContextMenu(true);

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
    QAction *RenameAction = new QAction("Rinomina", EditMenu);

    CopyAction->setShortcut(QKeySequence("Ctrl+C"));
    CopyAction->setShortcutVisibleInContextMenu(true);
    CutAction->setShortcut(QKeySequence("Ctrl+X"));
    CutAction->setShortcutVisibleInContextMenu(true);
    PasteAction->setShortcut(QKeySequence("Ctrl+V"));
    PasteAction->setShortcutVisibleInContextMenu(true);
    RemoveAction->setShortcut(QKeySequence("Delete"));
    RemoveAction->setShortcutVisibleInContextMenu(true);
    RenameAction->setShortcut(QKeySequence("F2"));
    RenameAction->setShortcutVisibleInContextMenu(true);

    EditMenu->addAction(CopyAction);
    EditMenu->addAction(PasteAction);
    EditMenu->addAction(CutAction);
    EditMenu->addAction(RemoveAction);
    EditMenu->addAction(RenameAction);

    connect(CopyAction, SIGNAL(triggered(bool)), this, SLOT(copy()));
    connect(CutAction, SIGNAL(triggered(bool)), this, SLOT(cut()));
    connect(PasteAction, SIGNAL(triggered(bool)), this, SLOT(paste()));
    connect(RemoveAction, SIGNAL(triggered(bool)), this, SLOT(remove()));
    connect(RenameAction, SIGNAL(triggered(bool)), this, SLOT(rename()));

    //end edit menu

    //view menu

    QMenu *ViewMenu = new QMenu("Visualizza", MenuBar);
    MenuBar->addMenu(ViewMenu);

    GridViewAction = new QAction("Griglia", ViewMenu);
    PlayViewAction = new QAction("Riproduzione", ViewMenu);

    GridViewAction->setShortcut(QKeySequence("Ctrl+G"));
    GridViewAction->setShortcutVisibleInContextMenu(true);
    PlayViewAction->setShortcut(QKeySequence("Ctrl+P"));
    PlayViewAction->setShortcutVisibleInContextMenu(true);


    ViewMenu->addAction(GridViewAction);
    ViewMenu->addAction(PlayViewAction);

    //end view menu
}

void MainWindow::updateTreeRecursive(const Katalog::BaseNode *root, QTreeWidgetItem *itemParent)
{
    auto &files = root->getFiles();
    for(auto i = files.begin(); i != files.end(); i++){
        QTreeWidgetItem *item = new QTreeWidgetItem(itemParent);;
        item->setText(0, QString::fromStdString(files[i]->getName()));
        setTreeWidgetItemExtras(item, files[i].pointer());
        if(files[i]->getFilesCount() > 0){
            updateTreeRecursive(files[i].pointer(), item);
        }
        item->setExpanded(files[i]->isOpen());
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

void MainWindow::setTreeWidgetItemExtras(QTreeWidgetItem *item, Katalog::BaseNode* file)
{
    if(dynamic_cast<Katalog::Photo*>(file))
        item->setIcon(0, QIcon(":/Icons/image-gallery.svg"));
    else if(dynamic_cast<Katalog::Audio*>(file))
        item->setIcon(0, QIcon(":/Icons/speaker.svg"));
    else if(dynamic_cast<Katalog::Video*>(file))
        item->setIcon(0, QIcon(":/Icons/video.svg"));
    else
        item->setIcon(0, QIcon(":/Icons/folder.svg"));

    item->setToolTip(0, QString::fromStdString(file->getInfo()));
}

std::string MainWindow::getItemPath(QTreeWidgetItem *item)
{
    string path = "/" + item->text(0).toStdString();
    while((item = item->parent()))
        path = "/" + item->text(0).toStdString() + path;
    return path;
}

void MainWindow::addPhoto()
{
    QStringList sources = QFileDialog::getOpenFileNames(this, tr("Apri foto"), "/home", tr("Immagini (*.png *.jpg)"));
    std::string destination = getSelectedFilePath();
    if(!sources.empty()) {
        for(auto i = sources.begin(); i != sources.end(); ++i){
            std::string source = i->toStdString();
            std::string filename = getFileName(source);
            emit addFile(new Katalog::Photo(filename, source), destination);
        }
    }
}

void MainWindow::addAudio()
{
    QStringList sources = QFileDialog::getOpenFileNames(this, tr("Apri foto"), "/home", tr("Audio (*.mp3 *.flac)"));
    std::string destination = getSelectedFilePath();
    if(!sources.empty()) {
        for(auto i = sources.begin(); i != sources.end(); ++i){
            std::string source = i->toStdString();
            std::string filename = getFileName(source);
            emit addFile(new Katalog::Audio(filename, source), destination);
        }
    }
}

void MainWindow::addVideo()
{
    QStringList sources = QFileDialog::getOpenFileNames(this, tr("Apri foto"), "/home", tr("Immagini (*.mp4 *.avi)"));
    std::string destination = getSelectedFilePath();
    if(!sources.empty()) {
        for(auto i = sources.begin(); i != sources.end(); ++i){
            std::string source = i->toStdString();
            std::string filename = getFileName(source);
            emit addFile(new Katalog::Video(filename, source), destination);
        }
    }
}

void MainWindow::addDirectory()
{
    std::string name = QInputDialog::getText(this, "Crea cartella", "Nome nuova cartella: ").toStdString();
    if(name != ""){
        std::string destination = getSelectedFilePath();
        emit addFile(new Katalog::Directory(name), destination);
    }
}

void MainWindow::doubleClickOnGridItem(Katalog::BaseNode *file)
{
    //update del file selezionato nel treewidget

    if(!catalogView->selectedItems().empty()) {
        QTreeWidgetItem *item = catalogView->selectedItems().at(0); //sufficiente perchè si può selezionare un file solo
        bool goToParent = true;
        while(goToParent){
            for(int i = 0; i < item->childCount(); i++){
                if(item->child(i)->text(0).toStdString() == file->getName()){
                    catalogView->clearSelection();
                    item->child(i)->setSelected(true);
                    goToParent = false;
                }
            }
            if(goToParent && item->parent()) item = item->parent();
            else goToParent = false;
        }
    } else { //sto vedendo la root
        QList<QTreeWidgetItem*> items = catalogView->findItems(QString::fromStdString(file->getName()), Qt::MatchFlag::MatchFixedString | Qt::MatchFlag::MatchCaseSensitive, 0);
        for(auto i = items.begin(); i != items.end(); i++){
            if(!(*i)->parent())
            {
                catalogView->clearSelection();
                (*i)->setSelected(true);
                break;
            }
        }
    }

    if(file && (file->getFilesCount() > 0 || (dynamic_cast<Katalog::Audio*>(file) == 0 && dynamic_cast<Katalog::Photo*>(file) == 0 && dynamic_cast<Katalog::Video*>(file) == 0)))
        showGrid(&file->getFiles());
    else
        showPlayWindow(file);
}

void MainWindow::updatePathString()
{
    pathEditor->setText(QString::fromStdString(getSelectedFilePath()));
}

void MainWindow::copy()
{
    std::string dest = getSelectedFilePath();
    if(dest != "/")
        emit fileCopied(dest);
}

void MainWindow::cut()
{
    std::string dest = getSelectedFilePath();
    if(dest != "/")
        emit fileCutted(dest);
}

void MainWindow::paste()
{
    emit filePasted(getSelectedFilePath());
}

void MainWindow::remove()
{
    std::string dest = getSelectedFilePath();
    if(dest != "/")
        emit fileRemoved(dest);
}

void MainWindow::rename()
{
    std::string destination = getSelectedFilePath();
    if(destination != "/"){
        std::string name = QInputDialog::getText(this, "Rinomina", "Nuovo nome: ").toStdString();
        if(name != ""){
            emit fileRenamed(destination, name);
        }
    }

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    controller->saveCatalog();
    QWidget::closeEvent(event);
}

