#include "Photo.h"
#include <QImage>
#include <QMediaMetaData>
#include <QMediaPlayer>
#include <sstream>

Katalog::Photo::Photo(string _name, string _path): Directory(_name, _path)
{
    QImage img = QImage(QString::fromStdString(_path));
    risoluzione.first = img.width();
    risoluzione.second = img.height();
    auto player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(QString::fromStdString(_path)));
    //viene fatto in 3 passaggi per evitare un warning
    camera = player->metaData(QMediaMetaData::CameraManufacturer).String;
    camera += " ";
    camera += player->metaData(QMediaMetaData::CameraModel).String;
    size = std::filesystem::file_size(getPath());
}

long Katalog::Photo::getSize() const
{
	return size;
}

long Katalog::Photo::getAllSize() const
{
	return getSize() + Directory::getAllSize();
}

string Katalog::Photo::getIcon() const
{
    return "/icons/photo.img";
}

std::string Katalog::Photo::getInfo() const
{
    std::stringstream s;
    s << "Risoluzione: " << risoluzione.first << "x" << risoluzione.second << std::endl;
    s << "Camera: " << camera << std::endl;
    s << "Dimensioni: " << size << " byte";
    return s.str();
}
