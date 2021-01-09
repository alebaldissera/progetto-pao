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
        long getSize() override;
        long getAllSize() override;
        string getIcon() const override;
	private:
	};

}

#endif // VIDEO_H
