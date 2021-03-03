#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedLayout>
#include <QLayout>
#include <QSizePolicy> //necessaria per la divisione in percentuale dei widget in un layout
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QShortcut>
#include <QFileDialog>
#include <GridView.h>
#include <QInputDialog>
#include <VideoPlayer.h>
#include <QScrollArea>

#include <DeselectableTreeView.h>
#include <VideoPlayer.h>
#include <BaseNode.h>
#include <LoadingView.h>

class Controller;

typedef Katalog::vector<std::string> PathList;
typedef Katalog::vector<Katalog::DeepPtr<Katalog::BaseNode>> FileList;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    /**
     * @brief setController Permette di impostare un puntatore al controller
     * @param c punatore al controller
     */
    void setController(Controller *c);
    /**
     * @brief updateTree Aggiorna il QTreeWidget mostrando la nuova struttura del catalogo
     * @param root puntatore alla root del catalogo
     */
    void updateTree(const Katalog::BaseNode* root);
    /**
     * @brief clearTree Rimuove tutti gli elementi dal QTreeWidget
     */
    void clearTree();
    /**
     * @brief showGrid Mostra la visualizzazione a griglia
     * @param files Punatore alla lista di file da visualizzare
     */
    void showGrid(const FileList* files);
    /**
     * @brief getTextPath Ritorna la path scritta sulla QLineEdit
     * @return path scritta sulla QLineEdit
     */
    std::string getTextPath();
    /**
     * @brief selectFileOnTree Seleziona a partire da una path al catalogo il corretto elemento del QTreeWidget
     * @param path path al catalogo
     */
    void selectFileOnTree(std::string path);
    /**
     * @brief showPlayWindow Mostra il player multimediale con un singolo file in riproduzione
     * @param file puntatore al file da riprodurre
     */
    void showPlayWindow(const Katalog::BaseNode* file);
    /**
     * @brief showPlayWindow Mostra il player multimediale con una lista di file da riprodurre
     * @param files puntatore alla lista di file da riprodurre
     */
    void showPlayWindow(const FileList* files);

public slots:
    /**
     * @brief resetTextPath Imposta la path dell QLineEdit a quella dell'elemento selezionato sul QTreeWidget
     */
    void resetTextPath();

signals:
    /**
     * @brief addFile Segnale emesso quando si vuole aggiungere un file al catalogo
     * @param file puntatore al file da aggiungere
     * @param destination destinazione sul catalogo in cui aggiungere il file
     */
    void addFile(Katalog::BaseNode *file, std::string destination);
    /**
     * @brief fileCopied segnale emesso quando si vuole intraprendere un'azione di copia
     */
    void fileCopied(std::string);
    /**
     * @brief fileCutted segnale emesso quando si vuole intraprendere un'azione di taglia
     */
    void fileCutted(std::string);
    /**
     * @brief filePasted segnale emesso quando si vuole intraprendere un'azione di incolla
     */
    void filePasted(std::string);
    /**
     * @brief fileRemoved segnale emesso quando si vuole intraprendere un'azione di rimozione
     */
    void fileRemoved(std::string);
    /**
     * @brief fileRenamed segnale emesso quando si vuole intraprendere un'azione di rinominazione
     */
    void fileRenamed(std::string, std::string);
    /**
     * @brief pathTextChanged segnale emesso quando si cambia la path sul QLineEdit e si preme invio
     */
    void pathTextChanged();

protected:
    /**
     * @brief closeEvent Funzione che gestisce l'evento di chiusura della finestra
     * @param event
     */
    void closeEvent(QCloseEvent *event);

private slots:
    /*
     * Abbiamo scelto di usare 4 slot differenti per importare i file, e gestire la creazione
     * per ogni tipo con la view per rendere trasparente la differenza di file al controller
     * Questa scelta arriva dalla possibilità di inserire nuovi tipi di file alla gerarchia e quindi
     * non gestendo le differenze dei file a livello di controller, l'aggiunta di nuovi tipi sarà più veloce
     */
    /**
     * @brief addPhoto Gestore dell'aggiunta di immagini
     */
    void addPhoto();
    /**
     * @brief addAudio gestore dell'aggiunta di audio
     */
    void addAudio();
    /**
     * @brief addVideo gestore dell'aggiunta di video
     */
    void addVideo();
    /**
     * @brief addDirectory gestore dell'aggiunta di cartelle
     */
    void addDirectory();
    /**
     * @brief doubleClickOnGridItem Gestore del doppio click su un elemento della griglia
     */
    void doubleClickOnGridItem(Katalog::BaseNode*);
    /**
     * @brief updatePathString gestore dell'aggiornamento della path sul QLineEdit a partire dalla selezione sul QTreeWidget
     */
    void updatePathString();
    /**
     * @brief copy gestore dell'azione di copia
     */
    void copy();
    /**
     * @brief cut gestore dell'azione di taglia
     */
    void cut();
    /**
     * @brief paste gestore dell'azione di incolla
     */
    void paste();
    /**
     * @brief remove gestore dell'azione di rimozione
     */
    void remove();
    /**
     * @brief rename gestore dell'azione di rinominazione
     */
    void rename();
    /**
      * @brief switchView scambia la vista tra griglia e player
      */
    void switchView();

private:
    /**
     * @brief addMenus Funzione che crea il menù della finestra
     * @param layout il QLayout in cui aggiungere il menu
     */
    void addMenus(QLayout *layout);
    /**
     * @brief updateTreeRecursive parte ricorsiva della funzione per aggiornare la struttura del QTreeWidget
     * @param root puntatore alla root della struttura sorgente
     * @param itemParent puntatore all'elemento del QTreeWidget a cui aggiungere gli altri file
     */
    void updateTreeRecursive(const Katalog::BaseNode* root, QTreeWidgetItem *itemParent);
    /**
     * @brief getFileName funzione che ritorna solamente il nome di un file a partire dalla path
     * @param source la path al file di cui si vuole sapre il nome
     * @return il nome del file
     */
    static std::string getFileName(std::string &source);
    /**
     * @brief getSelectedFilePath ricava a partire dalla selezione del catalogo la path del file
     * @return la path al catalogo del file selezionato
     */
    std::string getSelectedFilePath() const;
    /**
     * @brief setTreeWidgetItemExtras imposta icona e tooltip di un elemento del QTreeWidget
     * @param item Elemento del QTreeWidget da personalizzare
     * @param file puntatore al file da cui prelevare le informazioni
     */
    void setTreeWidgetItemExtras(QTreeWidgetItem *item, Katalog::BaseNode* file);
    /**
      * @brief updateSwitchButtonText aggiorna la scritta sul pulsante nell'header a seconda della vista corrente
      */
    void updateSwitchButtonText();
    /**
     * @brief getItemPath Ottiene la path al catalogo a partire da un elemento del QTreeWidget
     * @param item Puntatore all'oggeto del QTreeWidget
     * @return path al catalogo del file selezionato
     */
    static std::string getItemPath(QTreeWidgetItem* item);

    DeselectableTreeView *catalogView;
    QStackedLayout *stackLayout;
    GridView *grid;
    VideoPlayer *player;
    QVBoxLayout *screenLayout;
    QLineEdit *pathEditor;
    QPushButton *switchViewButton;

    //menu actions
    QAction *SaveAction;
    QAction *GridViewAction;
    QAction *PlayViewAction;

    bool currentView; //indica quale delle due viste attualmente è attiva true = griglia, false = player;

    Controller *controller;

};

#endif // MAINWINDOW_H
