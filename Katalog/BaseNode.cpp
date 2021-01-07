#include "BaseNode.h"
#include "DeepPtr.h"
#include "Vector.h"

using namespace Katalog;

BaseNode::BaseNode(string _nome, string _path): name(_nome), size(-1), allSize(-1), path(_path) {}

string BaseNode::getName()
{
   return name;
}

void BaseNode::setName(string _nome)
{
    name = _nome;
}

int BaseNode::getFilesCount()
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
}
