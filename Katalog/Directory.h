#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <BaseNode.h>
#include <string>
#include <sstream>

using std::string;

namespace Katalog {

	class Directory : public BaseNode {
	public:
		Directory(string nome, string path = "");
        virtual ~Directory() = default;
        /**
         * @brief clone Crea una copia dell'oggetto
         * @return Oggetto clonato
         */
        Directory* clone() const override;
        /**
         * @brief getSize ritorna la grandezza totale di tutti i file contenuti
         * @return grandezza del file
         */
        long getSize() const override;
        /**
         * @brief getAllSize ritorna la grandezza totale di tutti i file contenuti
         * @return grandezza totale dei file
         */
        long getAllSize() const override;
        /**
         * @brief getInfo costruisce una stringa formattata con informazioni sulla directory rappresentata
         * @return
         */
        string getInfo() const override;
	};

}

#endif // DIRECTORY_H
