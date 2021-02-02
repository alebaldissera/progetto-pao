#ifndef CATALOGO_H
#define CATALOGO_H
#include "BaseNode.h"
#include "DeepPtr.h"
#include <regex>
#include <iostream>
#include <Directory.h>

namespace Katalog{

class Catalogo
{
private:
    DeepPtr<BaseNode> root;
    /**
     * @brief remove_aux: si occupa di ritornare il puntatore alla directory che conteneva il file che è stato eliminato
     * @param string: è il percorso del file da rimuovere
     * @return puntatore alla directory che conteneva il file eliminato
     */
    DeepPtr<BaseNode> remove_aux(std::string);
    bool isModified = false;
public:
    Catalogo();
    Catalogo(DeepPtr<BaseNode>); //necessario per costruzione catalogo da radice
    ~Catalogo();

    /**
     * @brief regex_fun: funzione che permette il controllo del percorso di un file con il metodo della regex
     * @param   string: è il percorso che si vuole esaminare per vedere se esiste o meno
     * @return  BaseNode*: ritorna il nodo trovato corrispondente al percorso inserito, se esiste, altrimenti ritorna un nullptr
     */
    BaseNode* regex_fun(std::string);
    /**
     * @brief   add: aggiunge un file alla directory scelta
     * @param   string: è il name del file da inserire
     * @param   BaseNode*: è la directory di destinazione in cui si aggiunge il file (da rivedere)
     */
    void add(BaseNode*, std::string);
    /**
     * @brief   remove: rimuove un file dalla sua posizione
     * @param   string: path del file da rimuovere
     */
    void remove(std::string);
    /**
     * @brief   move: permette di spostare un file da una directory all'altra
     * @param   string: path dell'oggetto da spostare
     * @param   string: path della destinazione in cui spostare l'oggetto
     */
    void move(std::string, std::string);
    /**
     * @brief   getSize: ritorna la dimensione del file/directory
     * @return  long
     */
    long getSize();
    /**
     * @brief   getFileCount: ritorna il numero di file presenti nella directory
     * @return  int
     */
    int getFileCount();
    /**
     * @brief copy: copia di un file in memoria
     * @param string: path dell'oggetto da copiare in memoria
     * @param string: path della destinazione in cui copiare l'oggetto
     */
    void copy(std::string, std::string);
    /**
     * @brief getRoot: ritorna il puntatore alla radice
     * @return pointer alla radice
     */
    const DeepPtr<BaseNode>& getRoot();
    /**
     * @brief isChanged: bool per vedere se è avvenuta una modifica dei file
     * @return true se è avvenuta una modifica ai file, false altrimenti
     */
    bool isChanged();

};

}
#endif // CATALOGO_H
