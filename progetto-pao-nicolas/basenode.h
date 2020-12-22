#ifndef BASENODE_H
#define BASENODE_H
#include <string>
using std::string;

class BaseNode
{
private:
    string name;
    BaseNode* file;
    long size;
    long allSize;
    string path;
public:
    /**
     * @brief getName: ritorna il nome del file/directory
     * @return string
     */
    string getName();
    /**
     * @brief setName: permette la rinomina del file/directory
     */
    void setName(string);
    /**
     * @brief getFilesCount: ritorna il numero dei file presenti nella directory
     * @return int
     */
    int getFilesCount();
    /**
     * @brief addFile: permette di aggiungere un file alla directory
     */
    void addFile(BaseNode*);
    /**
     * @brief removeFile: permette la rimozione di un file dalla directory
     * @return BaseNode* puntatore alla directory da cui si è eliminato il file
     */
    BaseNode* removeFile(BaseNode*);
    /**
     * @brief getSize: ritorna la dimensione di un file/directory
     * @return virtual long
     */
    virtual long getSize();
    /**
     * @brief getAllSize: ritorna la dimensione intera della directory e dei figli sotto di essa
     * @return virtual long
     */
    virtual long getAllSize();
    //virtual getIcon();
    ~BaseNode();
    BaseNode(string);
};

#endif // BASENODE_H
