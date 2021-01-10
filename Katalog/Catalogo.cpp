#include "Catalogo.h"
#include "BaseNode.h"

using namespace Katalog;
using namespace std;

Catalogo::Catalogo() : root(nullptr) {} //non sono sicuro

/*
void Catalogo::add(string path, BaseNode* destination_dir)
{
    std::regex rgx("(?=\/)(.*?)(?<=\/)");
        std::smatch match;
        if(std::regex_search(s.begin(), s.end(), match, rgx)){
            std::cout<< match[1] << endl; //stamperà: miacartella
            path = path.substring(match[1].end(), path.end()); //path = "/miofile.jpg"
        }
        return 0;
}
*/

void Catalogo::move(string path_start, string path_end)
{
    /*   idea1: controllo se le due stringhe esistono: sostituisco a path_end la parte finale, così che possa puntare al file in path_start.
     *          Successivamente elimino dal path start il nome del file appena spostato.
     *   idea2: controllo se esistono le due stringhe scorrendo con un for il catalogo: successivamente copio il file nel path di destinazione,
     *          ne modifico il path facendolo combaciare con la destinazione, elimino il file dal path iniziale.
     */

}

long Catalogo::getSize()
{
   return root->getAllSize();
}

int Catalogo::getFileCount()
{
    return root->getFilesCount();
}

