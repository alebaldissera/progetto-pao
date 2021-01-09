#include <Directory.h>

using namespace Katalog;

Directory::Directory(string nome, string path) : BaseNode(nome, path) {}

long Katalog::Directory::getSize()
{
	long size = 0;

    //questo è da rivedere
    for (auto i = files.begin(); i != files.end(); i++) {
		size += **i.getSize();
	}

	return size;
}

long Katalog::Directory::getAllSize()
{
	return getSize();
}

string Katalog::Directory::getIcon() const 
{
    return "/icons/string.ico";	//path da cui prelevare l'icona generica della cartella
}

