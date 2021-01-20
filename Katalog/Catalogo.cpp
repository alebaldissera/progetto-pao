#include "Catalogo.h"
#include "BaseNode.h"

using namespace Katalog;
using namespace std;

Catalogo::Catalogo() : root() {} //non sono sicuro

Catalogo::Catalogo(DeepPtr<BaseNode> catalog_root) : root(catalog_root) {}


void Catalogo::add(string path, BaseNode* destination_dir)
{
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

        }
        return ;
}


void Catalogo::move(string path_start, string path_end)
{
    /*   idea1: controllo se le due stringhe esistono: sostituisco a path_end la parte finale, così che possa puntare al file in path_start.
     *          Successivamente elimino dal path start il nome del file appena spostato.
     *   idea2: controllo se esistono le due stringhe scorrendo con un for il catalogo: successivamente copio il file nel path di destinazione,
     *          ne modifico il path facendolo combaciare con la destinazione, elimino il file dal path iniziale.
     */
     //if (path_start == root->getPath())

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
    for (auto i = 0; i < root->getFilesCount(); i++)
    {
        if (root->getPath() == file_path)
        {

        }
    }
}

const DeepPtr<BaseNode>& Catalogo::getRoot()
{
    return root;
}

