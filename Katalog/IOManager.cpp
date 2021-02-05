#include "IOManager.h"

//debug stuf
#include <iostream>
using std::cout;
using std::endl;
//end debug stuff

using namespace Katalog;

void IOManager::exportCatalogToFile(Katalog::Catalogo &catalogo, std::string pathToXmlFile)
{
    const NodePtr root = catalogo.getRoot();

    QFile xmlFile(QString::fromStdString(pathToXmlFile));
    QDomDocument xml;
    if(!xmlFile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw std::runtime_error("Impossibile aprire il file");

    QDomElement DocumentRoot = xml.createElement("Katalog");
    xml.appendChild(DocumentRoot);
    //attributo per controllare la versione del software in cui il catalogo è stato generato e per capire se il file xml creato è di questo software
    QDomElement xmlVersion = xml.createElement("KatalogVersion");
    xmlVersion.setAttribute("SoftwareVersion", 1);
    DocumentRoot.appendChild(xmlVersion);
    //attributo per salvare la sruttura del catalogo
    QDomElement el = xml.createElement("FileStructure");

    auto files = root->getFiles();
    for(auto i = files.begin(); i != files.end(); i++){
        populateXmlDocument(xml, el, files[i]);

        DocumentRoot.appendChild(el);
    }

    QTextStream stream(&xmlFile);
    stream << xml.toString().toUtf8();

    xmlFile.close();
}

Catalogo IOManager::importCatalogFromFile(std::string pathToXmlFile)
{
    QFile file(QString::fromStdString(pathToXmlFile));
    QDomDocument xml;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        //throw std::runtime_error("Impossibile aprire il file");
        return Catalogo();
    if(!xml.setContent(&file)){
        file.close();
        //throw std::runtime_error("Impossibile leggere il contenuto del file");
        return Catalogo();
    }
    QDomNode DocumentRoot = xml.namedItem("Katalog");
    QDomNode kv = DocumentRoot.namedItem("KatalogVersion");
    if(kv.isElement()){
        QDomNode sv = kv.attributes().namedItem("SoftwareVersion");
        if(sv.isAttr() && sv.toAttr().value() == "1"){
            //il file è ok e nella versione corretta. posso procedere a leggere la struttura dati
            QDomNode fs = DocumentRoot.namedItem("FileStructure");
            if(fs.isElement()){
                DeepPtr<BaseNode> root = new Directory("");
                if(fs.hasChildNodes()){
                    //scorro tra tutti i sottonodi del tag
                    QDomNodeList list = fs.childNodes();
                    for(int i = 0; i < list.count(); ++i){
                        QDomNode node = list.at(i);
                        root->addFile(readNodeInfo(node));
                    }
                }
                return root;
            } else
                throw std::runtime_error("Formato file errato");
        } else
            throw std::runtime_error("Formato file errato");
    } else
        throw std::runtime_error("Formato file errato");
}

void IOManager::populateXmlDocument(QDomDocument &doc, QDomElement &element, NodePtr &node)
{
    auto files = node->getFiles();
    QDomElement el = createCreateElement(doc, node); //creo me stesso
    for(auto i = files.begin(); i != files.end(); i++){
        QDomElement childs = doc.createElement("Childs");

        populateXmlDocument(doc, childs, files[i]); //chiamata ricorsiva sui figli

        el.appendChild(childs);
    }
    element.appendChild(el);
}

QDomElement IOManager::createCreateElement(QDomDocument &doc, NodePtr &node)
{
    bool file = dynamic_cast<Katalog::Photo*>(node.pointer()) != 0 ||
            dynamic_cast<Katalog::Audio*>(node.pointer()) != 0 ||
            dynamic_cast<Katalog::Video*>(node.pointer()) != 0;
    QDomElement el = doc.createElement(file ? "KFile" : "KDirectory");
    el.setAttribute("Name", QString::fromStdString(node->getName()));
    el.setAttribute("IsOpen", QString::fromStdString((node->isOpen() ? "True" : "False")));
    if(file){
        QString type;
        if(dynamic_cast<Katalog::Photo*>(node.pointer())) type = "KPhoto";
        else if (dynamic_cast<Katalog::Audio*>(node.pointer())) type = "KAudio";
        else type = "KVideo";
        el.setAttribute("FileType", type);
        el.setAttribute("PathToDisk", QString::fromStdString(node->getPath()));
    }
    return el;
}

BaseNode* IOManager::readNodeInfo(QDomNode &node){
    //funzione ricorsiva che si occupa di leggere la struttura ad albero dei file
    BaseNode *ptr;
    if(node.nodeName() == "KDirectory")
        ptr = new Directory(node.toElement().attribute("Name").toStdString());
    else if(node.nodeName() == "KFile") {
        std::string fileType = node.toElement().attribute("FileType").toStdString();
        std::string name = node.toElement().attribute("Name").toStdString();
        std::string pathToDisk = node.toElement().attribute("PathToDisk").toStdString();
        if(!QFile::exists(QString::fromStdString(pathToDisk)))
            ptr = new Directory(name);
        else {
            if(fileType == "KPhoto")
                ptr = new Photo(name, pathToDisk);
            else if(fileType == "KAudio")
                ptr = new Audio(name, pathToDisk);
            else if (fileType == "KVideo")
                ptr = new Video(name, pathToDisk);
            else
                throw std::runtime_error("Tipo file specificato non supportato");
        }
    } else
        throw std::runtime_error("Formato file errato");
    if(node.toElement().attribute("IsOpen").toStdString() == "True")
        ptr->open();
    else
        ptr->close();
    if(node.hasChildNodes() && node.firstChildElement("Childs").isElement()){
        QDomNode childs = node.firstChildElement("Childs");
        for(int i = 0; i < childs.childNodes().count(); i++){
            QDomNode sub = childs.childNodes().at(i);
            ptr->addFile(readNodeInfo(sub));
        }
    }
    return ptr;
}
