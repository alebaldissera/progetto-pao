#ifndef PHOTO_H
#define PHOTO_H

#include <Directory.h>
#include <string>
#include <filesystem>
#include <utility>

using std::string;
typedef unsigned int u_int;

namespace Katalog {

	class Photo : public Directory {
	public:
		Photo(string _name, string _path);
        long getSize() const override;
        long getAllSize() const override;
        string getIcon() const override;
        string getInfo() const override;
	private:
        std::pair<int, int> risoluzione;
        string camera;
	};

}

#endif // PHOTO_H
