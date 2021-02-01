#include "Catalogo.h"
#include "BaseNode.h"

using namespace Katalog;
using namespace std;

Catalogo::Catalogo() : root() {}

Catalogo::Catalogo(DeepPtr<BaseNode> catalog_root) : root(catalog_root) {}

BaseNode* Catalogo::regex_fun(string path)
{
    BaseNode* node = root.pointer();
    std::regex rgx ("(?:/)([a-zA-Z0-9\\.\\s]+)");
    std::smatch match;
    while(std::regex_search(path, match, rgx)){
            std::string matched = match[1].str();
            node = node->getFileByName(matched).pointer();
            path = path.substr(match[1].str().length(), path.length() + 1);
    }
    if(path.empty())
    {
        return node;
    }
    return nullptr;
}

DeepPtr<BaseNode> Catalogo::remove_aux(std::string path_file_to_remove)
{
    BaseNode* node_aux = root.pointer();
    std::regex rgx ("(?:/)([a-zA-Z0-9\\.\\s]+)");
    std::smatch match;
    while(std::regex_search(path_file_to_remove, match, rgx)){
        if(match[0].str() == path_file_to_remove)
        {
            std::string matchstr = match[0].str();
            return node_aux->getFileByName(matchstr).pointer();
        }
        else{
            std::string matched = match[1].str();
            node_aux = node_aux->getFileByName(matched).pointer();
            path_file_to_remove = path_file_to_remove.substr(match[1].str().length(), path_file_to_remove.length() + 1);
        }
      }
        throw std::runtime_error("Non esiste il file da rimuovere");
}


void Catalogo::add(BaseNode* ins_filename, std::string path_final_dir)
{

    BaseNode* ins_node(nullptr);
    ins_node = regex_fun(path_final_dir);
    if(ins_node)
    {
        ins_node->addFile(ins_filename);
    }
    else
        throw std::runtime_error("Non esiste il percorso in cui inserire il file desiderato");
}

void Catalogo::remove(std::string file_to_remove) //modificato da void
{
    remove_aux(file_to_remove).pointer();
}

void Catalogo::move(string path_start, string path_end)
{
    add(remove_aux(path_start).pointer(), path_end);
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
    if (root->getName() == file_path)
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



