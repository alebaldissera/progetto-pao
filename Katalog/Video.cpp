#include "Video.h"

Katalog::Video::Video(string _name, string _path): Directory(_name, _path) {}

long Katalog::Video::getSize()
{
	if (size != -1)
		return size;
    size = std::filesystem::file_size(getPath());
	return size;
}

long Katalog::Video::getAllSize()
{
	return getSize() + Directory::getAllSize();
}

string Katalog::Video::getIcon() const
{
	return "/icons/video.ico";
}
