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
        long getSize() override;
        long getAllSize() override;
        string getIcon() const override;
	private:
	};

}

#endif // !PHOTO_H
