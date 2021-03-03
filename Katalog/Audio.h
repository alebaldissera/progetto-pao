#ifndef AUDIO_H
#define AUDIO_H

#include <Directory.h>
#include <string>
#include <QFile>
#include <QMediaMetaData>
#include <sstream>
#include <QMediaPlayer>

using std::string;

namespace Katalog {
	
	class Audio : public Directory {
	public:
		Audio(string _name, string _path);
        virtual ~Audio() = default;
        /**
         * @brief clone Crea una copia dell'oggetto
         * @return Oggetto clonato
         */
        Audio* clone() const override;
        /**
         * @brief getSize ritorna la grandezza del file rappresentato
         * @return grandezza del file
         */
        long getSize() const override;
        /**
         * @brief getAllSize ritorna la grandezza del file rappresentato e ricorsivamente di tutti i file in esso contenuti
         * @return grandezza totale dei file
         */
        long getAllSize() const override;
        /**
         * @brief getInfo costruisce una stringa formattata con informazioni sul file rappresentato
         * @return
         */
        string getInfo() const override;
    private:
        int bitrate;
        string codec, titolo, autore;
	};
}

#endif
