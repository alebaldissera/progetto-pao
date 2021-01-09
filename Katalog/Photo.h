#ifndef PHOTO_H
#define PHOTO_H

#include <Directory.h>
#include <string>
#include <filesystem>

using std::string;

namespace Katalog {

	class Photo : public Directory {
	public:
		Photo(string _name, string _path);
		long getSize() const;
		long getAllSize() const;
		string getImage() const;
	private:
	};

}

#endif // !PHOTO_H
