#ifndef AUDIO_H
#define AUDIO_H

#include <Directory.h>
#include <string>
#include <filesystem>

using std::string;

namespace Katalog {
	
	class Audio : public Directory {
	public:
		Audio(string _name, string _path);
		long getSize() const;
		long getAllSize() const;
		string getIcon() const;
	};
}

#endif