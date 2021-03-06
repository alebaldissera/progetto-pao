#include "Catalogo.h"

using namespace Katalog;
using namespace std;

Catalogo::Catalogo() : root(new Directory("")) {}

Catalogo::Catalogo(DeepPtr<BaseNode> catalog_root) : root(catalog_root) {}

Catalogo::~Catalogo()
{

}

BaseNode* Catalogo::regex_fun(string path)
{
    BaseNode* node = root.pointer();
    if(path == "/"){
        return node;
    }
    std::regex rgx ("(?:/)([\\w\\-\\s\\{\\}\\(\\)\\[\\]@#§\\+=_&%$£!\\.àèéìòù]+)");
    std::smatch match;
    while(std::regex_search(path, match, rgx)){
            std::string matched = match[1].str();
            node = node->getFileByName(matched).pointer();
            path = path.substr(match[0].str().length(), path.length() + 1);
    }
    if(path.empty())
    {
        return node;
    }
    throw std::runtime_error("File non trovato");
}

DeepPtr<BaseNode> Catalogo::remove_aux(std::string path_file_to_remove)
{
    BaseNode* node_aux = root.pointer();
    std::regex rgx ("(?:/)([\\w\\-\\s\\{\\}\\(\\)\\[\\]@#§\\+=_&%$£!\\.àèéìòù]+)");
    std::smatch match;
    while(std::regex_search(path_file_to_remove, match, rgx)){
        if(match[0].str() == path_file_to_remove)
        {
            std::string matchstr = match[1].str();
            return node_aux->removeFile(node_aux->getFileByName(matchstr).pointer());
        }
        else{
            std::string matched = match[1].str();
            node_aux = node_aux->getFileByName(matched).pointer();
            path_file_to_remove = path_file_to_remove.substr(match[0].str().length(), path_file_to_remove.length() + 1);
        }
      }
        throw std::runtime_error("Non esiste il file da rimuovere");
}


void Catalogo::add(BaseNode* ins_filename, std::string path_final_dir)
{
    isModified = true;
    BaseNode* ins_node(nullptr);
    ins_node = regex_fun(path_final_dir);
    if(ins_node)
    {
        ins_node->addFile(ins_filename);
    }
    else
        throw std::runtime_error("Non esiste il percorso in cui inserire il file desiderato");
}

void Catalogo::remove(std::string file_to_remove)
{
    isModified = true;
    remove_aux(file_to_remove);
}

void Catalogo::move(string path_start, string path_end)
{
    isModified = true;
    if(path_start != path_end)
    {
        add(remove_aux(path_start).pointer()->clone(), path_end);
    }
    else
        throw std::runtime_error("Impossibile spostare il file nella stessa cartella");
}

long Catalogo::getSize()
{
   return root->getAllSize();
}

int Catalogo::getFileCount()
{
    return root->getFilesCount();
}

void Catalogo::copy(string sorgente, string destinazione)
{
    isModified = true;
    regex_fun(destinazione)->addFile(regex_fun(sorgente)->clone());
}

const DeepPtr<BaseNode>& Catalogo::getRoot()
{
    return root;
}

bool Catalogo::isChanged()
{
    return isModified;
}

void Catalogo::setFileAsOpened(string &path)
{
    isModified = true;
    regex_fun(path)->open();
}
BaseNode *Catalogo::getFile(std::string path_file)
{
    return regex_fun(path_file);
}

void Catalogo::setFileName(string path_file, string name)
{
    regex_fun(path_file)->setName(name);
}

void Catalogo::setFileAsClosed(string &path)
{
    isModified = true;
    regex_fun(path)->close();
}

bool Catalogo::getFileOpenState(string &path)
{
    return regex_fun(path)->isOpen();
}
