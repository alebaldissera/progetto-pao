#ifndef VIDEO_H
#define VIDEO_H

#include <Directory.h>
#include <string>
#include <QFile>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <sstream>

using std::string;

namespace Katalog {
    /**
     * @brief Classe che rappresenta un video
     */
	class Video : public Directory {
	public:
		Video(string _name, string _path);
        virtual ~Video() = default;
        /**
         * @brief clone Crea una copia dell'oggetto
         * @return Oggetto clonato
         */
        Video* clone() const override;
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
        double framerate;
        string codec, titolo, autore;
	};

}

#endif // VIDEO_H
