#include <Directory.h>
#include <sstream>

using namespace Katalog;

Directory::Directory(string nome, string path) : BaseNode(nome, path) {}

Katalog::Directory* Katalog::Directory::clone() const
{
    return new Directory(*this);
}

long Katalog::Directory::getSize() const
{
	long size = 0;

    //questo è da rivedere
    for (vector<DeepPtr<BaseNode>>::const_iterator i = getFiles().begin(); i != getFiles().end(); i++) {
        size += (**i).getSize();
	}

	return size;
}

long Katalog::Directory::getAllSize() const
{
	return getSize();
}

string Katalog::Directory::getIcon() const 
{
    return "/icons/string.ico";	//path da cui prelevare l'icona generica della cartella
}

std::string Directory::getInfo() const
{
    std::stringstream s;
    s << "Files: " << getFilesCount() << std::endl << "Size: " << getSize();
    return s.str();
}

