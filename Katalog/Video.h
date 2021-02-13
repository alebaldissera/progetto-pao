#ifndef VIDEO_H
#define VIDEO_H

#include <Directory.h>
#include <string>
#include <QFile>

using std::string;

namespace Katalog {

	class Video : public Directory {
	public:
		Video(string _name, string _path);
        virtual ~Video() = default;
        Video* clone() const override;
        long getSize() const override;
        long getAllSize() const override;
        string getInfo() const override;
	private:
        int bitrate;
        double framerate;
        string codec, titolo, autore;
	};

}

#endif // VIDEO_H
