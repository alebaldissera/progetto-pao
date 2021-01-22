#include "Catalogo.h"
#include "BaseNode.h"

using namespace Katalog;
using namespace std;

Catalogo::Catalogo() : root() {} //non sono sicuro

Catalogo::Catalogo(DeepPtr<BaseNode> catalog_root) : root(catalog_root) {}

void Catalogo::add(string path, BaseNode* destination_dir)
{
        vector<DeepPtr<BaseNode>> _list = root->getFiles();
        //std::regex rgx("(?:/)(.+)(?:/)");
        std::regex rgx ("(?:/)(.+[a-zA-z0-9\\s]\\..+[a-zA-z0-9\\s])");
        std::smatch match;
        //std::regex_search(path.begin(), path.end(), match, rgx)
        if(std::regex_search(path, match, rgx)){
            std::cout<< match[1] << std::endl; //stamperà: miacartella
            path = path.substr(match[1].str().length(), path.length() + 1); //path = "/miofile.jpg"
        }
        else
        {
            //non so cosa fare altrimenti: scorre i match?
        }
        for (unsigned int i = 0; i < _list.size(); i++)
        {
            if(_list[i]->getPath() == path)
            {
                destination_dir->addFile(&(*_list[i]));
                return;
            }
        }
}


void Catalogo::move(string path_start, string path_end)
{
    /*  idea2: controllo se esistono le due stringhe scorrendo con un for il catalogo: successivamente copio il file nel path di destinazione,
     *         ne modifico il path facendolo combaciare con la destinazione, elimino il file dal path iniziale.
     */
     vector<DeepPtr<BaseNode>> lista_file = root->getFiles();
     for (unsigned int i = 0; i < lista_file.size(); i++)
     {
        if (lista_file[i]->getPath() == path_start)
        {
            DeepPtr<BaseNode> file_to_move;
            file_to_move->removeFile(&(*lista_file[i]));
            for (unsigned int ii = i; ii < lista_file.size(); ii++)
            {
                if (lista_file[ii]->getPath() == path_end)
                {
                   lista_file[ii]->addFile(&(*file_to_move));
                   return;
                }
            }
        }
     }
    return;
}

DeepPtr<BaseNode> Catalogo::remove(string path_remove_file)
{
    vector<DeepPtr<BaseNode>> lista_file = root->getFiles();
    for (auto i = lista_file.begin(); i != lista_file.end(); i++)
    {
        if (lista_file[i]->getPath() == path_remove_file)
        {
            DeepPtr<BaseNode> retPtr = lista_file[i];
            lista_file.erase(i, i + 1);
            return retPtr;
        }
    }
    return DeepPtr<BaseNode>(nullptr);
}

long Catalogo::getSize()
{
   return root->getAllSize();
}

int Catalogo::getFileCount()
{
    return root->getFilesCount();
}

void Catalogo::copy(string file_path)
{
    if (root->getPath() == file_path) //cosa fare se non è corretta?
        {
            root->clone();
            return;
        }
    return;
}

const DeepPtr<BaseNode>& Catalogo::getRoot()
{
    return root;
}



