#include "modelsong.h"

namespace Model{

Song::Song(){}

Song::Song(QString songPath, QString title, QString artistName, QString albumName, int albumNr, QString addedTime, int playCount):
    m_songPath(songPath), m_title(title), m_artistName(artistName), m_albumName(albumName), m_albumNr(albumNr), m_addedTime(addedTime), m_playCount(playCount)
{

}

Song::Song(QString songPath, QString title, QString artistName, QString albumName):
    m_songPath(songPath), m_title(title), m_artistName(artistName), m_albumName(albumName)
{

}

//Song::Song(Song &copySong):
//     m_songPath(copySong.getSongPath()), m_title(copySong.getTitle()), m_artistName(copySong.getArtistName()), m_albumName(copySong.getAlbumName()), m_albumNr(copySong.getAlbumNr()), m_addedTime(copySong.getAddedTime()), m_playCount(copySong.getPlayCount())
//{
//}


QString Song::getTitle() const
{
    return m_title;
}

void Song::setTitle(const QString &value)
{
    m_title = value;
}

QString Song::getSongPath() const
{
    return m_songPath;
}

void Song::setSongPath(const QString &songPath)
{
    m_songPath = songPath;
}

QString Song::getArtistName() const
{
    return m_artistName;
}

void Song::setArtistName(const QString &artistName)
{
    m_artistName = artistName;
}

QString Song::getLabelName() const
{
    return m_labelName;
}

void Song::setLabelName(const QString &labelName)
{
    m_labelName = labelName;
}

QString Song::getAddedTime() const
{
    return m_addedTime;
}

void Song::setAddedTime(const QString &addedTime)
{
    m_addedTime = addedTime;
}

int Song::getPlayCount() const
{
    return m_playCount;
}

void Song::setPlayCount(int playCount)
{
    m_playCount = playCount;
}

QString Song::getAlbumName() const
{
    return m_albumName;
}

void Song::setAlbumName(const QString &albumName)
{
    m_albumName = albumName;
}

int Song::getAlbumNr() const
{
    return m_albumNr;
}

void Song::setAlbumNr(int albumNr)
{
    m_albumNr = albumNr;
}

QString Song::getLabelNr() const
{
    return m_labelNr;
}

void Song::setLabelNr(const QString &labelNr)
{
    m_labelNr = labelNr;
}

}

