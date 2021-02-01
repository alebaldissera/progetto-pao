#include "BaseNode.h"
#include "DeepPtr.h"
#include "Vector.h"

using namespace Katalog; //messo per comodità, da rimuovere una volta finito

BaseNode::BaseNode(string _nome, string _path) : name(_nome), path(_path), size(-1), allSize(-1) {}

string BaseNode::getName() const
{
   return name;
}

string Katalog::BaseNode::getPath() const
{
	return path;
}

void BaseNode::setName(string &_nome)
{
    name = _nome;
}

int BaseNode::getFilesCount() const
{
	return files.size();
}

void BaseNode::addFile(DeepPtr<BaseNode> insert_file)
{
	for (u_int i = 0; i < files.size(); i++)
	{
        if (&(*files[i]) == insert_file.pointer()) //penso basti ma è da controllare
			return;
	}
	files.push_back(insert_file);
}

DeepPtr<BaseNode> BaseNode::removeFile(DeepPtr<BaseNode> file_to_remove)
{
    for (auto i = files.begin(); i != files.end(); i++)
    {   
        if (&(*files[i]) == file_to_remove.pointer())
        {
            DeepPtr<BaseNode> retPtr = files[i];
			files.erase(i, i + 1);
			return retPtr;
		}
	}
    return DeepPtr<BaseNode>(nullptr);
}

const vector<DeepPtr<BaseNode>> &BaseNode::getFiles() const
{
    return files;
}

DeepPtr<BaseNode> &BaseNode::getFileByName(std::string &filename)
{
    for(auto i = files.begin(); i != files.end(); i++){
        if(files[i]->getName() == filename){
            return files[i];
        }
    }
    throw std::runtime_error("Il file non esiste");
}
