#include "Photo.h"
#include <QImage>
#include <QMediaMetaData>
#include <QMediaPlayer>
#include <sstream>

#include <iostream>

Katalog::Photo::Photo(string _name, string _path): Directory(_name, _path)
{
    QImage *img = new QImage(QString::fromStdString(_path));
    risoluzione.first = img->width();
    risoluzione.second = img->height();
    delete img;
    auto player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(QString::fromStdString(_path)));
    //viene fatto in 3 passaggi per evitare un warning    
    camera = player->metaData(QMediaMetaData::CameraManufacturer).String;
    camera += " ";
    camera += player->metaData(QMediaMetaData::CameraModel).String;
    if(camera == "\n \n") camera = "N/D";
    QFile f(QString::fromStdString(getPath()));
    if(f.open(QFile::ReadOnly)){
        size = f.size();
        f.close();
    }
}

Katalog::Photo* Katalog::Photo::clone() const
{
    return new Photo(*this);
}

long Katalog::Photo::getSize() const
{
	return size;
}

long Katalog::Photo::getAllSize() const
{
	return getSize() + Directory::getAllSize();
}

std::string Katalog::Photo::getInfo() const
{
    std::stringstream s;
    s << "Risoluzione: " << risoluzione.first << "x" << risoluzione.second << std::endl;
    s << "Camera: " << camera << std::endl;
    s << "Dimensioni: " << size << " byte";
    return s.str();
}
