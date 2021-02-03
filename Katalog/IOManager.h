#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <QDomElement>
#include <Catalogo.h>
#include <string>
#include <QFile>
#include <BaseNode.h>
#include <DeepPtr.h>
#include <Directory.h>
#include <Audio.h>
#include <Photo.h>
#include <Video.h>

namespace Katalog {

    typedef DeepPtr<BaseNode> NodePtr;

    class IOManager
    {
    public:
        /**
         * @brief exportCatalogToFile Esporta su un file tutta la struttura del catalog
         * @param catalogo  Oggetto catalogo da esportare
         * @param pathToXmlFile Path al file su disco
         * @throw runtime_error
         */
        static void exportCatalogToFile(Catalogo &catalogo, std::string pathToXmlFile);
        /**
         * @brief importCatalogFromFile Importa un catalogo da un file xml
         * @param pathToXmlFile Path al file su disco
         * @return Oggetto catalogo correttamente inizializzato
         * @throw runtime_error
         */
        static Catalogo importCatalogFromFile(std::string pathToXmlFile);

    private:
        /**
         * @brief populateXmlDocument funzione ricorsiva per i sottonodi della radice
         * @param doc il documento xml in cui inserire la struttura
         * @param element l'elemento in cui si inserisce la struttura
         * @param node la radice alla struttura delle directory
         * @throw runtime_error
         */
        static void populateXmlDocument(QDomDocument &doc, QDomElement &element, NodePtr &node);
        /**
         * @brief createCreateElement crea il nodo (directory o file) e ne imposta gli attributi
         * @param doc il documento in cui verrà inserito l'elemento creato
         * @param node il nodo alla struttura
         * @return elemento xml che rappresenta un nodo della struttura del catalogo
         * @throw runtime_error
         */
        static QDomElement createCreateElement(QDomDocument &doc, NodePtr &node);
        /**
         * @brief readNodeInfo Legge la struttura di un nodo del file xml e ne ritorna l'equivalenete struttura
         * @param node Nodo di base della struttura
         * @return Un DeepPtr alla base della struttura
         * @throw runtime_error
         */
        static BaseNode* readNodeInfo(QDomNode &node);
    };

};
#endif // IOMANAGER_H
