#include "Audio.h"
#include <QMediaMetaData>
#include <sstream>

Katalog::Audio::Audio(string _name, string _path): Directory(_name, _path)
{
    auto player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(QString::fromStdString(_path)));
    bitrate = player->metaData(QMediaMetaData::AudioBitRate).Int;
    codec = player->metaData(QMediaMetaData::AudioCodec).String;
    titolo = player->metaData(QMediaMetaData::Title).String;
    autore = player->metaData(QMediaMetaData::Author).String;
    QFile f(QString::fromStdString(getPath()));
    if(f.open(QFile::ReadOnly)){
        size = f.size();
        f.close();
    }
    delete player;
}

Katalog::Audio* Katalog::Audio::clone() const
{
    return new Audio(*this);
}

long Katalog::Audio::getSize() const
{
	return size;
}

long Katalog::Audio::getAllSize() const
{
	return getSize() + Directory::getAllSize();
}

std::string Katalog::Audio::getInfo() const
{
    std::stringstream s;
    s << "Titolo: " << titolo << std::endl;
    s << "Autore: " << autore << std::endl;
    s << "Bitrate: " << bitrate << std::endl;
    s << "Codec: " << codec << std::endl;
    s << "Dimensioni: " << size << std::endl;
    return s.str();
}

