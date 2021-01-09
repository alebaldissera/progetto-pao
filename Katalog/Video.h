#ifndef VIDEO_H
#define VIDEO_H

#include <Directory.h>
#include <string>
#include <filesystem>

using std::string;

namespace Katalog {

	class Video : public Directory {
	public:
		Video(string _name, string _path);
		long getSize() const;
		long getAllSize() const;
		string getIcon() const;
	private:
	};

}

#endif // VIDEO_H
