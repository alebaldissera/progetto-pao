#include "BaseNode.h"
#include "DeepPtr.h"
#include "Vector.h"

using namespace Katalog;

BaseNode::BaseNode(string _nome, string _path) : name(_nome), path(_path), size(-1), allSize(-1) {}

string BaseNode::getName() const
{
   return name;
}

string Katalog::BaseNode::getPath() const
{
	return path;
}

void BaseNode::setName(string _nome)
{
    name = _nome;
}

int BaseNode::getFilesCount() const
{
	return files.size();
}

void BaseNode::addFile(BaseNode * insert_file)
{
	for (u_int i = 0; i < files.size(); i++)
	{
		if (&(*files[i]) == insert_file) //penso basti ma è da controllare
			return;
	}
	files.push_back(insert_file);
}

BaseNodePtr BaseNode::removeFile(BaseNode* file_to_remove) 
{
    for (auto i = files.begin(); i != files.end(); i++)
    {   
        if (&(*files[i]) == file_to_remove)
        {
			BaseNodePtr retPtr = files[i];
			files.erase(i, i + 1);
			return retPtr;
		}
	}
    return BaseNodePtr(nullptr);
}
