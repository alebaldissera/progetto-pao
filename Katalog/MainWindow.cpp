#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
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

    FileMenu->addSeparator();
    QAction *SaveAction = new QAction("Salva catalogo", FileMenu);
    FileMenu->addAction(SaveAction);

    FileMenu->addSeparator();
    QAction *ExitAction = new QAction("Esci", FileMenu);
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
    //end edit menu
}
