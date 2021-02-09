#ifndef BASENODE_H
#define BASENODE_H

#include <string>
#include "Vector.h"
#include "DeepPtr.h"
#include <stdexcept>

using std::string;

typedef unsigned int u_int;

namespace Katalog {

//non si può usare il typedef con un oggetto non acora definito quando viene usato un una classe (a meno di rif e ptr), in questo caso DeepPtr

class BaseNode
{
private:
    string name;
    vector<DeepPtr<BaseNode>> files;
    string path;
    bool directoryOpened;

protected:
    long size;

public:
    BaseNode(string _name, string _path = "");
    virtual ~BaseNode() = default;
    /**
     * @brief clone: ritorna una copia della classe derivata
     * @return puntatore alla classe derivata copiata
     */
    virtual BaseNode* clone() const = 0;
    /**
     * @brief getName: ritorna il nome del file/directory
     * @return string
     */
    string getName() const;
    /**
    * @brief getPath: ritorna la path al filesystem se si tratta di una directory ritorna stringa vuota
    * @retrun string
    */
    string getPath() const;
    /**
     * @brief setName: permette la rinomina del file/directory
     */
    void setName(string &_nome);
    /**
     * @brief getFilesCount: ritorna il numero dei file presenti nella directory
     * @return int
     */
    int getFilesCount() const;
    /**
     * @brief addFile: permette di aggiungere un file alla directory
     */
    void addFile(BaseNode* insert_file);
    /**
     * @brief removeFile: permette la rimozione di un file dalla directory
     * @param file_to_remove file da rimuovere
     */
    DeepPtr<BaseNode> removeFile(BaseNode* file_to_remove);
    /**
     * @brief getSize: ritorna la dimensione di un file/directory
     * @return DeepPtr<BaseNode>
     */
    virtual long getSize() const = 0;
    /**
     * @brief getAllSize: ritorna la dimensione intera della directory e dei figli sotto di essa
     * @return long
     */
    virtual long getAllSize() const = 0;
    /**
      * @brief getFiles: ritorna un riferimento costante alla lista dei file contenuti nel nodo
      * @return Katalog::vector<Katalog::DeepPtr<Katalog::BaseNode>>
      */
    const vector<DeepPtr<BaseNode>>& getFiles() const;
    /**
     * @brief getFileByName ritorna un riferimento costante al file con il nome passato come parametro per riferimento
     * @param filename il nome del file da cercare
     * @return riferimento costante al file
     * @throw std::runtime_error
     */
    DeepPtr<BaseNode>& getFileByName(string &filename);
    /**
     * @brief getInfo: ritorna una stringa formattata con le informazioni del nodo
     * @return string
     */
    virtual string getInfo() const = 0;
    /**
     * @brief isOpen: ritorna true sse il nodo è stato aperto
     * @return bool
     */
    bool isOpen() const;
    /**
     * @brief open imposta il nodo come aperto, rende visibili le sue directory
     */
    void open();
    /**
     * @brief close imposta il nodo come chiuso, rende visibili le sue direcotory
     */
    void close();
};

}
#endif // BASENODE_H
