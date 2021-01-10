#include "Video.h"
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <sstream>

Katalog::Video::Video(string _name, string _path): Directory(_name, _path)
{
    auto player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(QString::fromStdString(_path)));
    bitrate = player->metaData(QMediaMetaData::VideoBitRate).Int;
    framerate = player->metaData(QMediaMetaData::VideoFrameRate).Double;
    titolo = player->metaData(QMediaMetaData::Title).String;
    autore = player->metaData(QMediaMetaData::Author).String;
    size = std::filesystem::file_size(getPath());
}

long Katalog::Video::getSize() const
{
	return size;
}

long Katalog::Video::getAllSize() const
{
	return getSize() + Directory::getAllSize();
}

string Katalog::Video::getIcon() const
{
    return "/icons/video.ico";
}

std::string Katalog::Video::getInfo() const
{
    std::stringstream s;
    s << "Titolo: " << titolo << std::endl;
    s << "Autore: " << autore << std::endl;
    s << "Bitrate: " << bitrate << std::endl;
    s << "Framerate: " << framerate << std::endl;
    s << "Dimensioni: " << size << std::endl;
    return s.str();
}
