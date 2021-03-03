#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QMessageBox>
#include <MainWindow.h>
#include <Catalogo.h>
#include <Vector.h>
#include <DeepPtr.h>
#include <BaseNode.h>
#include <Photo.h>
#include <Audio.h>
#include <Video.h>
#include <IOManager.h>
#include <LoadingView.h>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(Katalog::Catalogo &cat, MainWindow &mw, QObject *parent = nullptr);

signals:
    /**
     * @brief catalogUpdated segnale emesso quando un catalogo subisce una modifica e deve essere aggiornata la view
     */
    void catalogUpdated();

public slots:
    /**
     * @brief addFile Aggiunge un file al catalogo
     * @param file Il nuovo file da aggiungere
     * @param destination La destinazione in cui aggiungere il file (inserito come sotto-file)
     */
    void addFile(Katalog::BaseNode *file, std::string destination);
    /**
     * @brief saveCatalog salva la struttura del catalogo su disco
     */
    void saveCatalog();
    /**
     * @brief openDirectory Indica che la directory è stata espansa e ne è stato letto il conenuto
     * @param node Nodo del QTreeWidetet che è stato espanso
     */
    void openDirectory(QTreeWidgetItem *node);
    /**
     * @brief closeDirectory Indica che la directory è stata chiusa e non si vuole leggere il contenuto
     * @param node Nodo del QTreeWidget che è stato chiuso
     */
    void closeDirectory(QTreeWidgetItem *node);
    /**
     * @brief treeItemClicked Metodo che gestisce il singolo click su un elemento del QTreeWidget
     * @param node Puntatore al nodo
     * @param col Numero di colonna premuto
     */
    void treeItemClicked(QTreeWidgetItem *node, int col);
    /**
     * @brief treeItemClicked Metodo che gestisce il doppio click su un elemento del QTreeWidget
     * @param node Puntatore al nodo
     * @param col Numero di colonna premuto
     */
    void treeItemDoubleClicked(QTreeWidgetItem *node, int col);
    /**
     * @brief viewGridOnRoot Mostra la griglia direttamente nella root del catalogo
     */
    void viewGridOnRoot();
    /**
     * @brief copyFile Indica che è stata richiesta un'azione di copia di un file
     * @param file path al catalogo del file
     */
    void copyFile(std::string file);
    /**
     * @brief cutFile Indica che è stata richiesta un'azione di taglia di un file
     * @param file path al catalogo del file
     */
    void cutFile(std::string file);
    /**
     * @brief pasteFile Esegue l'azione di incolla se prima è stata richiesta una copia o taglia
     * @param dest destinazione in cui inserire il file copiato o tagliato
     */
    void pasteFile(std::string dest);
    /**
     * @brief removeFile Esegue l'azione di rimozione di un file dal catalogo senza rimuoverlo dal disco
     * @param file path al file da rimuovere
     */
    void removeFile(std::string file);
    /**
     * @brief renameFile Esegue l'azione di rinominazione di un file del catalogo, rinomina solo a livello di catalogo
     * @param file path al file da rinominare
     * @param newName il nuovo nome da assegnare al file
     */
    void renameFile(std::string file, std::string newName);
    /**
     * @brief pathTextChanged Handler per agire quando la path sulla QLineEdit cambia
     */
    void pathTextChanged();
    /**
     * @brief requestForGridView mostra la GridView alla path indicata sulla QLineEdit
     */
    void requestForGridView();
    /**
     * @brief requestForPlayView mostra il VideoPlayer alla path indicata sulla QLineEdit
     */
    void requestForPlayView();

private:
    /**
     * @brief getItemPath Dato un nodo del QTreeWidget ne ritorna l'equivalente path al catalogo
     * @param item Puntatore al nodo del QTreeWidget
     * @return ritorna l'equivalente path al catalogo
     */
    static std::string getItemPath(QTreeWidgetItem* item);

    Katalog::Catalogo &catalogo;
    MainWindow &mainwindow;
    std::string clip;
    bool operation; //true copia, false taglia
};


#endif // CONTROLLER_H
