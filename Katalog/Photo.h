#ifndef PHOTO_H
#define PHOTO_H

#include <Directory.h>
#include <string>
#include <QFile>
#include <utility>
#include <QImage>
#include <QMediaMetaData>
#include <QMediaPlayer>
#include <sstream>

using std::string;
typedef unsigned int u_int;

namespace Katalog {
    /**
     * @brief Classe che rappresenta un'immagine
     */
	class Photo : public Directory {
	public:
		Photo(string _name, string _path);
        virtual ~Photo() = default;
        /**
         * @brief clone Crea una copia dell'oggetto
         * @return Oggetto clonato
         */
        Photo* clone() const override;
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
        std::pair<int, int> risoluzione;
        string camera;
	};

}

#endif // PHOTO_H
