#include "Photo.h"

Katalog::Photo::Photo(string _name, string _path): Directory(_name, _path) {}

long Katalog::Photo::getSize()
{
	if (size != -1)
		return size;
	size = std::filesystem::file_size(getPath());
	return size;
}

long Katalog::Photo::getAllSize()
{
	return getSize() + Directory::getAllSize();
}

string Katalog::Photo::getIcon() const
{
    return "/icons/photo.img";
}
