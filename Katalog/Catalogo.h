#ifndef CATALOGO_H
#define CATALOGO_H
#include "BaseNode.h"
#include <regex>
#include <iostream>

namespace Katalog{

class Catalogo
{
private:
    BaseNodePtr root;
public:
    /**
     * @brief   add: aggiunge un file alla directory scelta
     * @param   string: è il path del file da inserire
     * @param   BaseNode*: è la directory di destinazione in cui si aggiunge il file
     */
    void add(std::string, BaseNode*);
    /**
     * @brief   remove: rimuove un file dalla sua posizione
     * @return  directory da cui è stato eliminato il file
     * @param   string: path del file da rimuovere
     */
    BaseNode* remove(std::string);
    /**
     * @brief   move: permette di spostare un file da una directory all'altra
     * @param   string: path dell'oggetto da spostare
     * @param   string: path della destinazione in cui spostare l'oggetto
     */
    void move(string, string);
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
    Catalogo();
    ~Catalogo();
};

}
#endif // CATALOGO_H
