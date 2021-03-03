#include "Video.h"

Katalog::Video::Video(string _name, string _path): Directory(_name, _path)
{
    auto player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(QString::fromStdString(_path)));
    bitrate = player->metaData(QMediaMetaData::VideoBitRate).Int;
    framerate = player->metaData(QMediaMetaData::VideoFrameRate).Double;
    titolo = player->metaData(QMediaMetaData::Title).String;
    autore = player->metaData(QMediaMetaData::Author).String;
    QFile f(QString::fromStdString(getPath()));
    if(f.open(QFile::ReadOnly)){
        size = f.size();
        f.close();
    }
    delete player;
}

Katalog::Video* Katalog::Video::clone() const
{
    return new Video(*this);
}

long Katalog::Video::getSize() const
{
	return size;
}

long Katalog::Video::getAllSize() const
{
	return getSize() + Directory::getAllSize();
}

std::string Katalog::Video::getInfo() const
{
    std::stringstream s;
    s << "Nome: " << getName() << std::endl;
    s << "Titolo: " << titolo << std::endl;
    s << "Autore: " << autore << std::endl;
    s << "Bitrate: " << bitrate << std::endl;
    s << "Framerate: " << framerate << std::endl;
    s << "Dimensioni: " << size << std::endl;
    return s.str();
}
