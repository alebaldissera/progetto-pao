#include "Audio.h"

Katalog::Audio::Audio(string _name, string _path): Directory(_name, _path){}

long Katalog::Audio::getSize() const
{
	if (size != -1)
		return size;
	size = std::filesystem::file_size(getPath());
	return size;
}

long Katalog::Audio::getAllSize() const
{
	return getSize() + Directory::getAllSize();
}

string Katalog::Audio::getIcon() const
{
	return "/icons/audio.h";
}

