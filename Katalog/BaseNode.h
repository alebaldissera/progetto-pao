#ifndef BASENODE_H
#define BASENODE_H
#include <string>
#include "Vector.h"
#include "DeepPtr.h"
using std::string;

typedef unsigned int u_int;

namespace Katalog {

typedef vector<DeepPtr<BaseNode>> FilesContainer;
typedef DeepPtr<BaseNode> BaseNodePtr;

class BaseNode
{
private:
    string name;
    long size;
    long allSize;
    FilesContainer files;
    string path;

public:
    BaseNode(string _name, string _path = "");
    virtual ~BaseNode() = default;
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
    void setName(string _nome);
    /** 
     * @brief getFilesCount: ritorna il numero dei file presenti nella directory
     * @return int
     */
    int getFilesCount() const;
	/**
     * @brief addFile: permette di aggiungere un file alla directory
     */
	void addFile(BaseNode *insert_file);
    /**
     * @brief removeFile: permette la rimozione di un file dalla directory
     * @param insert_file file da inserire
     */
    BaseNodePtr removeFile(BaseNode *file_to_remove);
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
     * @brief getIcon: ritona la path ad una risorsa che specifica un'icona generica per il tipo di file
     * @return string
     */
    virtual string getIcon() const = 0;
};

}
#endif // BASENODE_H
