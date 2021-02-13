#include "BaseNode.h"
#include "DeepPtr.h"
#include "Vector.h"

using namespace Katalog; //messo per comodità, da rimuovere una volta finito

BaseNode::BaseNode(string _nome, string _path) : name(_nome), path(_path), directoryOpened(false), size(-1) {}

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

void BaseNode::addFile(BaseNode* insert_file)
{
	for (u_int i = 0; i < files.size(); i++)
	{
        if (files[i]->getName() == insert_file->getName())
			return;
	}
	files.push_back(insert_file);
}

DeepPtr<BaseNode> BaseNode::removeFile(BaseNode* file_to_remove)
{
    for (auto i = files.begin(); i != files.end(); i++)
    {   
        if (files[i]->getName() == file_to_remove->getName())
        {
            DeepPtr<BaseNode> retPtr = files[i];
			files.erase(i, i + 1);
            return retPtr;
		}
	}
    return nullptr;
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

bool BaseNode::isOpen() const
{
    return directoryOpened;
}

void BaseNode::open()
{
    directoryOpened = true;
}

void BaseNode::close()
{
    directoryOpened = false;
}
