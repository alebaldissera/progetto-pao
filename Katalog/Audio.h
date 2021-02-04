#ifndef AUDIO_H
#define AUDIO_H

#include <Directory.h>
#include <string>
#include <filesystem>

#include <QMediaPlayer>

using std::string;

namespace Katalog {
	
	class Audio : public Directory {
	public:
		Audio(string _name, string _path);
        Audio* clone() const override;
        long getSize() const override; //possibile integrazione con un getSize() const per ottimizzare
        long getAllSize() const override;
        string getInfo() const override;
    private:
        int bitrate;
        string codec, titolo, autore;
	};
}

#endif
