#include "Video.h"

long Katalog::getSize() const
{
	if (size != -1)
		return size;
	size = std::filesystem::file_size(getPath());
	return size;
}

Katalog::Video::Video(string _name, string _path): Directory(_name, _path) {}

long Katalog::Video::getSize() const
{
	if (size != -1)
		return size;
	size = std::filesystem::file_size(path);
	return size;
}

long Katalog::Video::getAllSize() const
{
	return getSize() + Directory::getAllSize();
}

string Katalog::Video::getIcon() const
{
	return "/icons/video.ico";
}
